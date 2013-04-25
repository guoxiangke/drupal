<?php

/**
 * @file
 * Administrative page callbacks for the role tree module.
 */

/**
 * Form builder for the roles overview.
 * @see role_tree_overview_roles_submit()
 * @see theme_role_tree_overview_roles()
 */
function role_tree_overview_roles($form, &$form_state) {
  global $pager_page_array, $pager_total, $pager_total_items;

  $form['#tree'] = TRUE;
  $form['#parent_fields'] = FALSE;

  $page            = isset($_GET['page']) ? $_GET['page'] : 0;
  $page_increment  = 50;  // Number of terms per page.
  $page_entries    = 0;   // Elements shown on this page.
  $before_entries  = 0;   // Elements at the root level before this page.
  $after_entries   = 0;   // Elements at the root level after this page.
  $root_entries    = 0;   // Elements at the root level on this page.

  // Terms from previous and next pages are shown if the term tree would have
  // been cut in the middle. Keep track of how many extra terms we show on each
  // page of terms.
  $back_step    = NULL;
  $forward_step = 0;

  // An array of the terms to be displayed on this page.
  $current_page = array();

  $delta = 0;
  $role_deltas = array();
  $tree = role_tree_get_tree();
  //var_dump($tree);exit;
  $role = current($tree);
  do {
    // In case this tree is completely empty.
    if (empty($role)) {
      break;
    }
    $delta++;
    // Count entries before the current page.
    if ($page && ($page * $page_increment) > $before_entries && !isset($back_step)) {
      $before_entries++;
      continue;
    }
    // Count entries after the current page.
    elseif ($page_entries > $page_increment && isset($complete_tree)) {
      $after_entries++;
      continue;
    }

    // Do not let a term start the page that is not at the root.
    if (isset($role->depth) && ($role->depth > 0) && !isset($back_step)) {
      $back_step = 0;
      while ($prole = prev($tree)) {
        $before_entries--;
        $back_step++;
        if ($prole->depth == 0) {
          prev($tree);
          continue 2; // Jump back to the start of the root level parent.
       }
      }
    }
    $back_step = isset($back_step) ? $back_step : 0;

    // Continue rendering the tree until we reach the a new root item.
    if ($page_entries >= $page_increment + $back_step + 1 && $role->depth == 0 && $root_entries > 1) {
      $complete_tree = TRUE;
      // This new item at the root level is the first item on the next page.
      $after_entries++;
      continue;
    }
    if ($page_entries >= $page_increment + $back_step) {
      $forward_step++;
    }

    // Finally, if we've gotten down this far, we're rendering a term on this page.
    $page_entries++;
    $role_deltas[$role->rid] = isset($role_deltas[$role->rid]) ? $role_deltas[$role->rid] + 1 : 0;
    $key = 'rid:' . $role->rid . ':' . $role_deltas[$role->rid];

    // Keep track of the first term displayed on this page.
    if ($page_entries == 1) {
      $form['#first_rid'] = $role->rid;
    }
    // Keep a variable to make sure at least 2 root elements are displayed.
    if ($role->parents[0] == 0) {
      $root_entries++;
    }
    $current_page[$key] = $role;
  } while ($role = next($tree));

  // Because we didn't use a pager query, set the necessary pager variables.
  $total_entries = $before_entries + $page_entries + $after_entries;
  $pager_total_items[0] = $total_entries;
  $pager_page_array[0] = $page;
  $pager_total[0] = ceil($total_entries / $page_increment);

  // If this form was already submitted once, it's probably hit a validation
  // error. Ensure the form is rebuilt in the same order as the user submitted.
  if (!empty($form_state['input'])) {
    $order = array_flip(array_keys($form_state['input'])); // Get the $_POST order.
    $current_page = array_merge($order, $current_page); // Update our form with the new order.
    foreach ($current_page as $key => $role) {
      // Verify this is a term for the current page and set at the current depth.
      if (is_array($form_state['input'][$key]) && is_numeric($form_state['input'][$key]['rid'])) {
        $current_page[$key]->depth = $form_state['input'][$key]['depth'];
      }
      else {
        unset($current_page[$key]);
      }
    }
  }

  // Build the actual form.
  foreach ($current_page as $key => $role) {
    // Save the term for the current page so we don't have to load it a second time.
    $form[$key]['#role'] = (array) $role;
    if (isset($role->parents)) {
      $form[$key]['#role']['parent'] = $role->parent = $role->parents[0];
      unset($form[$key]['#role']['parents'], $role->parents);
    }
  	if (in_array($role->rid, array(DRUPAL_ANONYMOUS_RID, DRUPAL_AUTHENTICATED_RID))) {
      $form[$key]['view'] = array('#markup' => t('@name <em>(locked)</em>', array('@name' => $role->name)));
    }
    else {
    	$form[$key]['view'] = array('#markup' => check_plain($role->name));
    }
    if (count($tree) > 1) {
      $form['#parent_fields'] = TRUE;
      $form[$key]['rid'] = array(
        '#type' => 'hidden',
        '#value' => $role->rid
      );
      $form[$key]['parent'] = array(
        '#type' => 'hidden',
        // Yes, default_value on a hidden. It needs to be changeable by the javascript.
        '#default_value' => $role->parent,
      );
      $form[$key]['depth'] = array(
        '#type' => 'hidden',
        // Same as above, the depth is modified by javascript, so it's a default_value.
        '#default_value' => $role->depth,
      );
      $form[$key]['weight'] = array(
        '#type' => 'weight',
        '#delta' => $delta,
        '#title_display' => 'invisible',
        '#title' => t('Weight for added role'),
        '#default_value' => $role->weight,
      );
    }
    if (in_array($role->rid, array(DRUPAL_ANONYMOUS_RID, DRUPAL_AUTHENTICATED_RID))) {
    	$form[$key]['edit'] = array('#markup' => '');
    }
    else {
    	$form[$key]['edit'] = array('#type' => 'link', '#title' => t('edit role'), '#href' => 'admin/people/permissions/roles/edit/' . $role->rid, '#options' => array('query' => drupal_get_destination()));
    }
    $form[$key]['permissions'] = array('#type' => 'link', '#title' => t('edit permissions'), '#href' => 'admin/people/permissions/' . $role->rid, '#options' => array('query' => drupal_get_destination()));
  }
	
  $form['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Name'),  
    '#title_display' => 'invisible',
    '#size' => 32,
    '#maxlength' => 64,
  );
  $form['add'] = array(
    '#type' => 'submit',
    '#value' => t('Add role'),
    '#validate' => array('role_tree_admin_role_validate'),
    '#submit' => array('role_tree_admin_role_submit'),
  );
  $form['#total_entries'] = $total_entries;
  $form['#page_increment'] = $page_increment;
  $form['#page_entries'] = $page_entries;
  $form['#back_step'] = $back_step;
  $form['#forward_step'] = $forward_step;
  $form['#empty_text'] = t('没有可用的角色！');

  if (count($tree) > 1) {
    $form['actions'] = array('#type' => 'actions', '#tree' => FALSE);
    $form['actions']['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Save')
    );
    $form_state['redirect'] = array($_GET['q'], (isset($_GET['page']) ? array('query' => array('page' => $_GET['page'])) : array()));
  }

  return $form;
}

/**
 * Submit handler for roles overview form.
 */
function role_tree_overview_roles_submit($form, &$form_state) {
  uasort($form_state['values'], 'drupal_sort_weight');
  $hierarchy = 0; // Update the current hierarchy type as we go.

  $changed_roles = array();
  $tree = role_tree_get_tree();

  if (empty($tree)) {
    return;
  }

  // Build a list of all terms that need to be updated on previous pages.
  $weight = 0;
  $role = (array) $tree[0];
  while ($role['rid'] != $form['#first_rid']) {
    if ($role['parents'][0] == 0 && $role['weight'] != $weight) {
      $role['parent'] = $role['parents'][0];
      $role['weight'] = $weight;
      $changed_roles[$role['rid']] = $role;
    }
    $weight++;
    $hierarchy = $role['parents'][0] != 0 ? 1 : $hierarchy;
    $role = (array) $tree[$weight];
  }

  // Renumber the current page weights and assign any new parents.
  $level_weights = array();
  foreach ($form_state['values'] as $rid => $values) {
    if (isset($form[$rid]['#role'])) {
      $role = $form[$rid]['#role'];
      // Give terms at the root level a weight in sequence with terms on previous pages.
      if ($values['parent'] == 0 && $role['weight'] != $weight) {
        $role['weight'] = $weight;
        $changed_roles[$role['rid']] = $role;
      }
      // Terms not at the root level can safely start from 0 because they're all on this page.
      elseif ($values['parent'] > 0) {
        $level_weights[$values['parent']] = isset($level_weights[$values['parent']]) ? $level_weights[$values['parent']] + 1 : 0;
        if ($level_weights[$values['parent']] != $role['weight']) {
          $role['weight'] = $level_weights[$values['parent']];
          $changed_roles[$role['rid']] = $role;
        }
      }
      // Update any changed parents.
      if ($values['parent'] != $role['parent']) {
        $role['parent'] = $values['parent'];
        $changed_roles[$role['rid']] = $role;
      }
      $hierarchy = $role['parent'] != 0 ? 1 : $hierarchy;
      $weight++;
    }
  }

  // Build a list of all terms that need to be updated on following pages.
  for ($weight; $weight < count($tree); $weight++) {
    $role = (array) $tree[$weight];
    if ($role['parents'][0] == 0 && $role['weight'] != $weight) {
      $role['parent'] = $role['parents'][0];
      $role['weight'] = $weight;
      $changed_roles[$role['tid']] = $role;
    }
    $hierarchy = $role['parents'][0] != 0 ? 1 : $hierarchy;
  }

  // Save all updated terms.
  foreach ($changed_roles as $changed) {
    $role = (object) $changed;
    // Update term_hierachy and term_data directly since we don't have a
    // fully populated term object to save.
    db_update('role_hierarchy')
      ->fields(array('parent' => $role->parent))
      ->condition('rid', $role->rid, '=')
      ->execute();

    db_update('role')
      ->fields(array('weight' => $role->weight))
      ->condition('rid', $role->rid, '=')
      ->execute();
  }
  
  drupal_set_message(t('The configuration options have been saved.'));
}

/**
 * Returns HTML for a roles overview form as a sortable list of roles.
 */
function theme_role_tree_overview_roles($variables) {
  $form = $variables['form'];

  $page_increment  = $form['#page_increment'];
  $page_entries    = $form['#page_entries'];
  $back_step     = $form['#back_step'];
  $forward_step  = $form['#forward_step'];

  // Add drag and drop if parent fields are present in the form.
  if ($form['#parent_fields']) {
    drupal_add_tabledrag('role_tree', 'match', 'parent', 'term-parent', 'term-parent', 'term-id', FALSE);
    drupal_add_tabledrag('role_tree', 'depth', 'group', 'term-depth', NULL, NULL, FALSE);
    drupal_add_js(drupal_get_path('module', 'role_tree') . '/role_tree.js');
    drupal_add_js(array('role_tree' => array('backStep' => $back_step, 'forwardStep' => $forward_step)), 'setting');
    drupal_add_css(drupal_get_path('module', 'role_tree') . '/role_tree.css');
  }
  drupal_add_tabledrag('role_tree', 'order', 'sibling', 'term-weight');

  $errors = form_get_errors() != FALSE ? form_get_errors() : array();
  $rows = array();
  foreach (element_children($form) as $key) {
    if (isset($form[$key]['#role'])) {
      $role = &$form[$key];

      $row = array();
      $row[] = (isset($role['#role']['depth']) && $role['#role']['depth'] > 0 ? theme('indentation', array('size' => $role['#role']['depth'])) : ''). drupal_render($role['view']);
      if ($form['#parent_fields']) {
        $role['rid']['#attributes']['class'] = array('term-id');
        $role['parent']['#attributes']['class'] = array('term-parent');
        $role['depth']['#attributes']['class'] = array('term-depth');
        $row[0] .= drupal_render($role['parent']) . drupal_render($role['rid']) . drupal_render($role['depth']);
      }
      $role['weight']['#attributes']['class'] = array('term-weight');
      $row[] = drupal_render($role['weight']);
      $row[] = drupal_render($role['edit']);
      $row[] = drupal_render($role['permissions']);
      $row = array('data' => $row);
      $rows[$key] = $row;
    }
  }

  // Add necessary classes to rows.
  $row_position = 0;
  foreach ($rows as $key => $row) {
    $rows[$key]['class'] = array();
    if (isset($form['#parent_fields'])) {
      $rows[$key]['class'][] = 'draggable';
    }

    // Add classes that mark which terms belong to previous and next pages.
    if ($row_position < $back_step || $row_position >= $page_entries - $forward_step) {
      $rows[$key]['class'][] = 'taxonomy-term-preview';
    }

    if ($row_position !== 0 && $row_position !== count($rows) - 1) {
      if ($row_position == $back_step - 1 || $row_position == $page_entries - $forward_step - 1) {
        $rows[$key]['class'][] = 'taxonomy-term-divider-top';
      }
      elseif ($row_position == $back_step || $row_position == $page_entries - $forward_step) {
        $rows[$key]['class'][] = 'taxonomy-term-divider-bottom';
      }
    }

    // Add an error class if this row contains a form error.
    foreach ($errors as $error_key => $error) {
      if (strpos($error_key, $key) === 0) {
        $rows[$key]['class'][] = 'error';
      }
    }
    $row_position++;
  }

  if (empty($rows)) {
    $rows[] = array(array('data' => $form['#empty_text'], 'colspan' => '3'));
  }
	$rows[] = array(array('data' => drupal_render($form['name']) .drupal_render($form['add']), 'colspan' => 4));
  $header = array(t('Name'), t('Weight'), array('data' => t('Operations'), 'colspan' => 2));
  $output = theme('table', array('header' => $header, 'rows' => $rows, 'attributes' => array('id' => 'role_tree')));
  $output .= drupal_render_children($form);
  $output .= theme('pager');

  return $output;
}

function role_tree_admin_role_validate($form, &$form_state) {
  if (!empty($form_state['values']['name'])) {
    if ($form_state['values']['op'] == t('Save role')) {
      $role = user_role_load_by_name($form_state['values']['name']);
      if ($role && $role->rid != $form_state['values']['rid']) {
        form_set_error('name', t('The role name %name already exists. Choose another role name.', array('%name' => $form_state['values']['add_role']['name'])));
      }
    }
    elseif ($form_state['values']['op'] == t('Add role')) {
      if (user_role_load_by_name($form_state['values']['name'])) {
        form_set_error('name', t('The role name %name already exists. Choose another role name.', array('%name' => $form_state['values']['name'])));
      }
    }
  }
  else {
    form_set_error('name', t('You must specify a valid role name.'));
  }
}

function role_tree_admin_role_submit($form, &$form_state) {
  $role = (object) $form_state['values'];
  if ($form_state['values']['op'] == t('Save role')) {
    user_role_save($role);
    drupal_set_message(t('The role has been renamed.'));
  }
  elseif ($form_state['values']['op'] == t('Add role')) {
    user_role_save($role);
    drupal_set_message(t('The role has been added.'));
  }
  $form_state['redirect'] = 'admin/people/permissions/roles';
  return;
}

function role_tree_user_role_insert($role) {
  db_insert('role_hierarchy')
    ->fields(array(
      'rid' => $role->rid,
      'parent' => 0,
    ))
    ->execute();
}

function role_tree_user_admin($callback_arg = '') {
  $op = isset($_POST['op']) ? $_POST['op'] : $callback_arg;

  switch ($op) {
    case t('Create new account'):
    case 'create':
      $build['user_register'] = drupal_get_form('role_tree_user_register_form');
      break;
    default:
      if (!empty($_POST['accounts']) && isset($_POST['operation']) && ($_POST['operation'] == 'cancel')) {
        $build['user_multiple_cancel_confirm'] = drupal_get_form('user_multiple_cancel_confirm');
      }
      else {
        $build['user_filter_form'] = drupal_get_form('user_filter_form');
        $build['user_admin_account'] = drupal_get_form('user_admin_account');
      }
  }
  return $build;
}
