<?php
// $Id$


/**
 * @file
 * Checklist handler functions.
 */

/**
 * Callback for 'node' item type to give options.
 */
function checklist_checklist_item_node_admin_form_form(&$form, &$form_state, $cl, $item = NULL) {
  $form['node-type'] = array(
    '#type' => 'select',
    '#title' => t('Node type to create'),
    '#options' => node_type_get_names(),
    '#default_value' => $item && $item->data && isset($item->data['node-type']) ? $item->data['node-type'] : NULL,
    '#description' => t('Make sure that whichever node type you select, the user has permission to create the type.'),
    '#required' => TRUE,
  );
  $form['node-published'] = array(
    '#type' => 'checkbox',
    '#title' => t('Require published node'),
    '#default_value' => $item && $item->data && isset($item->data['node-published']) ? $item->data['node-published'] : NULL,
    '#description' => t('Require the node to be published before marking the item off. Note that this will only work if the user that has the item on their checklist publishes the node.'),
  );
  return $form;
}

/**
 * Callback for 'node' item type to process the admin form.
 */
function checklist_checklist_item_node_admin_form_submit(&$form, &$form_state, $cl, $item = NULL) {
  return array('node-type' => $form_state['values']['node-type'], 'node-published' => $form_state['values']['node-published']);
}

/**
 * Callback for 'node' item type to provide allowed_paths.
 */
function checklist_checklist_item_node_allowed_paths($instance, $item, $account) {
  $paths = array('node/add/' . $item->data['node-type']);
  if (!empty($item->data['node-published'])) {
    $nodes = _checklist_checklist_item_node_load_nodes($account->uid, $item->data['node-type']);
    foreach ($nodes as $node) {
      // Allow a user to visit the node as well as to edit the node.
      $paths[] = 'node/' . $node->nid;
      $paths[] = 'node/' . $node->nid . '/edit';
    }
  }
  return $paths;
}

/**
 * Callback for 'node' item type to provide to modify how the item is displayed.
 */
function checklist_checklist_item_node_display_options($instance, $item, $account) {
  $info = array('path' => 'node/add/' . $item->data['node-type']);
  if (!empty($item->data['node-published'])) {
    $nodes = _checklist_checklist_item_node_load_nodes($account->uid, $item->data['node-type']);
    foreach ($nodes as $node) {
      // Send the user to the edit page since they probably need to publish the node.
      $info['path'] = 'node/' . $node->nid . '/edit';
      break;
    }
  }
  return $info;
}

/**
 * Helper function to load the nodes that have yet to be published by a user.
 */
function _checklist_checklist_item_node_load_nodes($uid, $node_type) {
  $nodes = node_load_multiple(array(), array('type' => $node_type, 'status' => 0, 'uid' => $uid));
  /*$query = new EntityFieldQuery();
  $entities = $query->entityCondition('entity_type', 'node')
                    ->entityCondition('bundle', $node_type)
                    ->propertyCondition('status', 0)
                    ->propertyCondition('uid', 1)
                    ->execute();

  $nodes = node_load_multiple(array_keys($entities['node']));*/
  return $nodes;
}

/**
 * Callback for 'node' item type to process it.
 */
function checklist_checklist_item_node_process_item($instance, $item, $account = NULL) {
  static $items = array();

  // $instance is NULL when a return is requested.
  if (!$instance) {
    return isset($items[$item]) ? $items[$item] : array(0, 0);
  }

  // Store the item so hook_nodeapi() can call this function later.
  $items[$item->data['node-type']] = array($instance, $item);
  return FALSE;
}



/**
 * Callback for 'user' item type to provide allowed_paths.
 */
function checklist_checklist_item_user_allowed_paths($instance, $item, $account) {
  return array('checklist/check/' . $instance->instance_id . '/' . $item->cliid);
}

/**
 * Callback for 'user' item type to provide values to modify how the item is displayed.
 */
function checklist_checklist_item_user_display_options($instance, $item, $account) {
  // Don't display anything if the item can't be unchecked.
  if (empty($item->checked_on) || $item->allow_uncheck) {
    $i = array(
      'path' => 'checklist/check/' . $instance->instance_id . '/' . $item->cliid,
    );
    // Only add the javascript if this item is supposed to be linked.
    if ($item->link) {
      $i += array(
        'attributes' => array('onclick' => 'return checklist_check(' . $item->cliid . ', "' . url('checklist/check', array('absolute' => TRUE)) . '/");', 'title' => $item->checked_on ? t('Click to uncheck') : t('Click to check')),
        'div_class' => array('clUser'),
      );
      checklist_item_add_js($account);
    }
    return $i;
  }
}

/**
 * Callback for 'user' item type to process it.
 */
function checklist_checklist_item_user_process_item($instance, $item, $account) {
  $result = 1;
  // User already checked the item.
  if ($item->checked_on) {
    if ($item->allow_uncheck) {
      $query = db_delete('checklist_user_checks')
        //->condition('uid', $account->uid)
        ->condition('instance_id', $instance->instance_id)
        ->condition('cliid', $item->cliid);
      // If this is a group instance, then don't limit by uid.
      if (!$instance->group_complete) {
        $query->condition('uid', $account->uid);
      }
      $query->execute();
      $result = 0;
    }
  }
  $result &= !$item->checked_on;
  if (isset($_REQUEST['ajax'])) {
    // Call this since this is an ajax call.
    if ($result) {
      _checklist_complete_user_item($instance->instance_id, $item, $account, TRUE, FALSE);
    }
    print(drupal_json_encode(array('instance_id' => $instance->instance_id, 'cliid' => $item->cliid, 'checked' => $result, 'uncheck' => $item->allow_uncheck)));
    exit();
  }
  // This will complete the checklist item (if TRUE) if it makes it here.
  return $result;
}




/**
 * Callback for 'user' item type to provide values to modify how the item is displayed.
 */
function checklist_checklist_item_admin_display_options($instance, $item, $account) {
  // Don't display anything if the item can't be unchecked.
  if (user_access('manage user checklist') && (empty($item->checked_on) || $item->allow_uncheck)) {
    checklist_item_add_js($account, 'admin');
    return array(
      'path' => 'checklist/admin/check/' . $account->uid . '/' . $instance->instance_id . '/' . $item->cliid,
      'attributes' => array('onclick' => 'return checklist_check(' . $instance->instance_id . ', ' . $item->cliid . ', "' . url('checklist/admin/check/' . $account->uid, array('absolute' => TRUE)) . '/");', 'title' => $item->checked_on ? t('Click to uncheck') : t('Click to check')),
      'div_class' => array('clAdmin'),
    );
  }
}

/**
 * Helper function to add the javascript needed to a checklist page.
 */
function checklist_item_add_js($account, $type = 'user') {
  static $js_types_added = array();
  if (empty($js_types_added)) {
    drupal_add_js('(function ($) {
  Drupal.checklist_check = function(instance_id, cliid, url) {
    $("#checklistItem"+instance_id+"-"+cliid).addClass(\'clWaiting\');
    $.ajax({url: url+instance_id+"/"+cliid, success: Drupal.checklist_receive, data: {ajax: 1}, dataType: "json"});
    return false;
  }
  Drupal.checklist_receive = function(data) {
    if (data["cliid"]) {
      var box = $("#checklistItem"+data["instance_id"]+"-"+data["cliid"]);
      if (data["checked"]) {
        box.addClass("clChecked");
        if (data["uncheck"] == 1) {
          box.siblings("a").attr("title", "' . t('Click to uncheck') . '");
        }
        else {
          box.siblings("a").attr("title", "");
        }
      }
      else {
        box.removeClass("clChecked");
        box.siblings("a").attr("title", "' . t('Click to check') . '");
      }
      box.removeClass("clWaiting");
    }
  }
}(jQuery));', array('type' => 'inline', 'scope' => JS_DEFAULT));
  }
  if (!isset($js_types_added[$type])) {
    $js_types_added[$type] = TRUE;
    if ($type == 'admin') {
      drupal_add_js('(function ($) {
    Drupal.behaviors.ajaxChecklistAdminCheck = {
      attach: function(context) {
        $(".clAdmin").click(function() {
          var ids = $(this).attr("id").substr(13).split("-");
          return Drupal.checklist_check(ids[0], ids[1], "' . url('checklist/admin/check/' . $account->uid, array('absolute' => TRUE)) . '/");
        });
      }
    };
  }(jQuery));', array('type' => 'inline', 'scope' => JS_DEFAULT));
    }
    elseif ($type == 'user') {
      drupal_add_js('(function ($) {
    Drupal.behaviors.ajaxChecklistUserCheck = {
      attach: function(context) {
        $(".clUser").click(function() {
          var ids = $(this).attr("id").substr(13).split("-");
          return Drupal.checklist_check(ids[0], ids[1], "' . url('checklist/check', array('absolute' => TRUE)) . '/");
        });
      }
    };
  }(jQuery));', array('type' => 'inline', 'scope' => JS_DEFAULT));
    }
  }
}




/**
 * Callback for 'page_view' item type to give options.
 */
function checklist_checklist_item_page_view_admin_form_form(&$form, &$form_state, $cl, $item = NULL) {
  $form['page-path'] = array(
    '#type' => 'textfield',
    '#title' => t('Page to visit'),
    '#default_value' => $item && $item->data && isset($item->data['page-path']) ? $item->data['page-path'] : '',
    '#description' => t('Enter the url of the internal drupal page the user must visit.' . (module_exists('token') ? ' You can also use any global tokens in the path.' : '')),
    '#required' => TRUE,
  );
  $form['page-path_tokens'] = _checklist_token_help(NULL, array('user'));
  return $form;
}

/**
 * Callback for 'page_view' item type to give options.
 */
function checklist_checklist_item_page_view_admin_form_validate(&$form, &$form_state, $cl, $item = NULL) {
  global $user;
  $path = trim($form_state['values']['page-path']);
  if (module_exists('token')) {
    $replaced_path = token_replace($path, array('user' => $user) + token_get_global_token_types());
  }
  else {
    $replaced_path = $path;
  }

  // Use the source path becuase an alias can change without notice.
  $normal_path = drupal_lookup_path('source', $replaced_path);
  if ($normal_path) {
    $path = $normal_path;
    drupal_set_message(t('The path entered is an alias. All paths are stored as the base path.'));
  }

  // Make sure the menu item exists.
  if (!($item = menu_get_item($replaced_path))) {
    form_set_error('page-path', t('The path must be a recognized internal drupal path.'));
  }
  else {
    $form_state['values']['page-path'] = $path;
  }
}

/**
 * Callback for 'page_view' item type to process the admin form.
 */
function checklist_checklist_item_page_view_admin_form_submit(&$form, &$form_state, $cl, $item = NULL) {
  return array('page-path' => $form_state['values']['page-path']);
}

/**
 * Callback for 'page_view' item type to provide allowed_paths.
 */
function checklist_checklist_item_page_view_allowed_paths($instance, $item, $account) {
  return array(module_exists('token') ? token_replace($item->data['page-path'], array('user' => $account) + token_get_global_token_types()) : $item->data['page-path']);
}

/**
 * Callback for 'page_view' item type to provide to modify how the item is displayed.
 */
function checklist_checklist_item_page_view_display_options($instance, $item, $account) {
  return array('path' => module_exists('token') ? token_replace($item->data['page-path'], array('user' => $account) + token_get_global_token_types()) : $item->data['page-path']);
}

/**
 * Callback for 'page_view' item type to process it.
 */
function checklist_checklist_item_page_view_process_item($instance, $item, $account = NULL) {
  // By visiting the page, the item is checked off.
  return TRUE;
}




/**
 * Callback for 'node_agree' item type to give options.
 */
function checklist_checklist_item_node_agree_admin_form_form(&$form, &$form_state, $cl, $item = NULL) {
  $default = '';
  if ($item && $item->data && isset($item->data['nid']) && ($node = node_load($item->data['nid']))) {
    $default = "$node->title [nid:$node->nid]";
  }
  $form['nid'] = array(
    '#type' => 'textfield',
    '#title' => t('Agreement node'),
    '#default_value' => $default,
    '#description' => t('Begin entering the title of the node that a user must agree to. Note, you must make sure the user\'s to complete this checklist have the correct permissions to access the node.'),
    '#autocomplete_path' => 'autocomplete/checklist/node_agree',
    '#required' => TRUE,
  );
  return $form;
}

/**
 * Callback for 'node_agree' item type to give options.
 */
function checklist_checklist_item_node_agree_admin_form_validate(&$form, &$form_state, $cl, $item = NULL) {
  $entry = trim($form_state['values']['nid']);
  // Add 5 for '[nid:'.
  $pos_open = strrpos($entry, '[') + 5;
  $pos_close = strrpos($entry, ']');
  $nid = drupal_substr($entry, $pos_open, $pos_close -($pos_open));
  if (!is_numeric($nid) || !($node = node_load($nid))) {
    form_set_error('nid', t('Please enter a valid node title and select the corrseponding entry.'));
  }
  else {
    $form_state['values']['nid'] = $nid;
  }
}

/**
 * Callback for 'node_agree' item type to process the admin form.
 */
function checklist_checklist_item_node_agree_admin_form_submit(&$form, &$form_state, $cl, $item = NULL) {
  return array('nid' => $form_state['values']['nid']);
}

/**
 * Callback for 'node_agree' item type to provide allowed_paths.
 */
function checklist_checklist_item_node_agree_allowed_paths($instance, $item, $account) {
  return array('node/' . $item->data['nid']);
}

/**
 * Callback for 'node_agree' item type to provide to modify how the item is displayed.
 */
function checklist_checklist_item_node_agree_display_options($instance, $item, $account) {
  return array('path' => 'node/' . $item->data['nid']);
}

/**
 * Callback for 'node_agree' item type to process it.
 */
function checklist_checklist_item_node_agree_process_item($instance, $item, $account = NULL) {
  static $items = array();

  // If item is the nid of the node, return the item.
  if (!$instance) {
    return isset($items[$item]) ? $items[$item] : array(0, 0);
  }

  // Store the item so hook_nodeapi() can call this function later.
  $items[$item->data['nid']] = array($instance, $item);
  return FALSE;
}

/**
 * Autocomplete callback for node_agree item type.
 */
function checklist_item_autocomplete_node($string = '') {
  $options = array();
  if ($string) {
    $results = db_select('node', 'n')
      ->fields('n', array('nid', 'title'))
      ->condition('status', 1)
      ->where('LOWER(title) LIKE LOWER(:lookup_string)', array(':lookup_string' => '%%'. db_like($string) .'%%'))
      ->orderBy('title', 'ASC')
      ->addTag('node_access')
      ->execute();
    foreach ($results as $row) {
      $title = check_plain($row->title);
      $options[$title . ' [nid:' . $row->nid . ']'] = $title;
    }
  }
  print drupal_json_encode($options);
  exit();
}

/**
 * Form to Agree to a Node
 */
function checklist_node_agree_form($form, &$form_state, $instance, $item) {
  $form['#checklist_instance'] = $instance;
  $form['#checklist_item'] = $item;
  $form['checklist_submit'] = array(
    '#type' => 'submit',
    '#value' => t('I Agree'),
    '#weight' => 10,
  );
  return $form;
}

/**
 * Submit function for the checklist_agree_form form
 * Checks the Checklist item box off
 */
function checklist_node_agree_form_submit($form, &$form_state) {
  _checklist_complete_user_item($form['#checklist_instance']->instance_id, $form['#checklist_item']);
}


/**
 * Callback for 'entity' item type to give options.
 */
function checklist_checklist_item_entity_admin_form_form(&$form, &$form_state, $cl, $item = NULL) {
  $form['important'] = array(
    '#type' => 'markup',
    '#value' => t('Whichever entity type selected below should have the allowed url entered above. The url to create the entity cannot be determined dynamically and if the allowed url is not set above, then the user will not be able to complete. The first url in the list is used for creating the link on the checklist page.'),
  );
  $bundles = array();
  foreach (entity_get_info() as $name => $data) {
    $bundles[$data['label']] = array();
    foreach ($data['bundles'] as $n => $bundle) {
      $bundles[$data['label']][$name . '||' . $n] = $bundle['label'];
    }
  }
  $form['entity_bundle'] = array(
    '#type' => 'select',
    '#title' => t('Entity - Bundle'),
    '#options' => $bundles,
    '#default_value' => $item && $item->data && isset($item->data['entity_bundle']) ? $item->data['entity_bundle'] : NULL,
    '#description' => t('The bundle of the entity that a user must create. Please make sure the user has permissions to create this entity and bundle type.'),
    '#required' => TRUE,
  );
  return $form;
}

/**
 * Callback for 'entity' item type to process the admin form.
 */
function checklist_checklist_item_entity_admin_form_submit(&$form, &$form_state, $cl, $item = NULL) {
  list($entity_type, $bundle) = explode('||', $form_state['values']['entity_bundle'], 2);
  return array('entity_bundle' => $form_state['values']['entity_bundle'], 'entity_type' => $entity_type, 'bundle' => $bundle);
}

/**
 * Callback for 'entity' item type to provide allowed_paths.
 * Handled by base handler.
 */
/*function checklist_checklist_item_entity_allowed_paths($instance, $item, $account) {
}*/

/**
 * Callback for 'entity' item type to provide to modify how the item is displayed.
 */
function checklist_checklist_item_entity_display_options($instance, $item, $account) {
  $info = array();
  // First item in this list is used as the path.
  if (isset($item->data['_checklist_internal_allowed_urls'])) {
    $info = array('path' => reset($item->data['_checklist_internal_allowed_urls']));
  }
  return $info;
}

/**
 * Callback for 'entity' item type to process it.
 */
function checklist_checklist_item_entity_process_item($instance, $item, $account = NULL) {
  static $items = array();

  // $instance is NULL when a return is requested.
  if (!$instance) {
    return isset($items[$item]) ? $items[$item] : array(0, 0);
  }

  // Store the item so hook_entity_insert() can call this function later.
  $items[$item->data['entity_bundle']] = array($instance, $item);
  return FALSE;
}
