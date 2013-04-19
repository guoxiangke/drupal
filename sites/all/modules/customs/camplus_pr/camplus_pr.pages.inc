<?php
/**
 * return a form setting of PR roles involved.
 */
function camplus_pr_roles_involved_settings_form($form, &$form_state) {
  $roles = user_roles(TRUE, 'camplus purchase request approvable');
  $count = 0;
  $camplus_pr_approvable_role_involved = variable_get('camplus_pr_approvable_role_involved','');
  $default_value = 0;
	foreach ($roles as $key => $role_name) {
		if (in_array($role_name, array('administrator'))) continue;

    if($camplus_pr_approvable_role_involved){
      $default_value =  $camplus_pr_approvable_role_involved[$role_name];
    }
    $form['involved'][$role_name] =  array(
        '#type' => 'checkbox',
        '#title' => $role_name,
        '#default_value' => $default_value,
      );
    $count++;
	}
  $form['warning_info'] = array('#markup' => t('注意:一经设置，不可取消,可添加不可删减,请管理员慎重操作!'),
    '#weight'=>-10,'#prefix' => '<div class="messages warning">',
    '#suffix' => '</div>');

  if(!$count) {
  	$form['empty_text'] = array('#markup' => t('没有可用的角色！请为相关角色'.l('添加权限','admin/people/permissions').'“Camplus Purchase Request approvable”'));
  	return $form;
  }
	// Add the buttons.
	$form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
    '#weight' => 5,
  );
	return  $form;
}

function camplus_pr_roles_involved_settings_form_submit($form, &$form_state) {
  $roles = user_roles(TRUE, 'camplus purchase request approvable');

  foreach ($form_state['values'] as $role_name => $value) {
    if(in_array($role_name, $roles)) {
      $camplus_pr_approvable_role_involved[$role_name] = $value;
    }
  }
  variable_set('camplus_pr_approvable_role_involved',$camplus_pr_approvable_role_involved);
}

function camplus_pr_roles_weight_settings_form($form, &$form_state) {
  $roles = user_roles(TRUE, 'camplus purchase request approvable');
  $count = 0;
  $camplus_pr_approvable_role_weight = variable_get('camplus_pr_approvable_role_weight','');
  $default_value = 'NULL';
  foreach ($roles as $key => $role_name) {
    if (in_array($role_name, array('administrator'))) continue;
      if($camplus_pr_approvable_role_weight){
        $default_value =  $camplus_pr_approvable_role_weight[$role_name];
      }
    $form[$role_name]['approvable_role_weight'][$role_name] = array(
      '#type' => 'textfield',
      '#size' => 20, 
      '#default_value' => $default_value,
    );
    $count++;
  }

  if(!$count) {
    $form['empty_text'] = array('#markup' => t('没有可用的角色！请为相关角色'.l('添加权限','admin/people/permissions').'“Camplus Purchase Request approvable”'));
    return $form;
  }
  // Add the buttons.
  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
    '#weight' => 5,
  );
  return  $form;
}

function camplus_pr_roles_weight_settings_form_submit($form, &$form_state) {
  $roles = user_roles(TRUE, 'camplus purchase request approvable');
  foreach ($form_state['values'] as $role_name => $value) {
    if(in_array($role_name, $roles)) {
      $camplus_pr_approvable_role_weight[$role_name] = $value;
    }
  }
  variable_set('camplus_pr_approvable_role_weight', $camplus_pr_approvable_role_weight);
}
/**
 * Returns HTML
 */
function theme_camplus_pr_roles_weight_settings_form($variables) {
  $form = $variables['form'];
  // $errors = form_get_errors() != FALSE ? form_get_errors() : array();
  $rows = array();
  foreach (element_children($form) as $role_name) { //dpm($key);
    if (isset($form[$role_name]['approvable_role_weight'])) {
      $row = array();
      $row[] = $role_name;
      $row[] = drupal_render($form[$role_name]['approvable_role_weight']);
      $row = array('data' => $row);
      $rows[] = $row;
    }
  }
  if (empty($rows)) {
    $rows[] = array(array('data' => $form['#empty_text'], 'colspan' => '2'));
  }
	$rows[] = array(array('data' => drupal_render($form['name']) .drupal_render($form['add']), 'colspan' => 4));
  $header = array(t('Role'), t('Weight for approvable role'));
  $output = theme('table', array('header' => $header, 'rows' => $rows, 'attributes' => array('id' => 'approvable_role')));
  $output .= drupal_render_children($form);
  $warning = '<div class="messages warning">The first role(Min number weight) must be The Department specific role. </div>';
  return $warning . $output;
}

function camplus_pr_range_settings_form() {
 $i=0;
 $range = variable_get('camplus_pr_settings_range', '5');
 $range_settings = variable_get('camplus_pr_range_settings', ''); 
 while($i<$range){
    $form[$i]['range']["pr_range_begin_$i"] = array(
      '#type' => 'textfield',
      '#default_value' =>$range_settings[$i]["begin"],
      '#prefix' => 'HK$',
      '#size' => 20, 
    );
    $form[$i]['range']["pr_range_end_$i"] = array(
      '#type' => 'textfield',
      '#default_value' =>$range_settings[$i]["end"],
      '#prefix' => 'HK$',
      '#size' => 20, 
    );
    $i++;
  }
// Add the buttons.
  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
    '#weight' => 5,
  );
  return  $form;
}

function camplus_pr_range_settings_form_submit($form, &$form_state) {
  $pattern = '/\d+/';
  $return = array();

  foreach ($form_state['values'] as $key => $value) {
    $subject = $key;
    if(strstr($key, 'pr_range_begin')) {
      // $range_settings[$key] = $form_state['values'][$key];
      preg_match($pattern, $subject, $matches);
      $range_settings[$matches[0]]['begin'] = $form_state['values'][$key];
    }elseif(strstr($key, 'pr_range_end')) {
      // $range_settings[$key] = $form_state['values'][$key];
      preg_match($pattern, $subject, $matches);
      $range_settings[$matches[0]]['end'] = $form_state['values'][$key];
    }
  }

  dpm($range_settings,'$range_settings');
  variable_set('camplus_pr_range_settings', $range_settings);
}

function theme_camplus_pr_range_settings_form($variables) {
  $form = $variables['form'];
  // $errors = form_get_errors() != FALSE ? form_get_errors() : array();
  $rows = array();
  foreach (element_children($form) as $i) { //dpm($key);
    if (isset($form[$i]['range'])) {
      $row = array();
      $row[] = $i+1;
      $row[] = drupal_render($form[$i]['range']["pr_range_begin_$i"]);
      $row[] = drupal_render($form[$i]['range']["pr_range_end_$i"]);
      $row = array('data' => $row);
      $rows[] = $row;
    }
  }
  if (empty($rows)) {
    $rows[] = array(array('data' => $form['#empty_text'], 'colspan' => '2'));
  }
  $rows[] = array(array('data' => drupal_render($form['name']) .drupal_render($form['add']), 'colspan' => 4));
  $header = array(t('No'), t('Begin'), t('End'));
  $output = theme('table', array('header' => $header, 'rows' => $rows, 'attributes' => array('id' => 'approvable_role')));
  $output .= drupal_render_children($form);


  $warning = '<div class="messages warning">一经设置，请审慎更改! </div>';
  return $warning.$output;
}

function camplus_pr_settings_form() {
  $form['camplus_pr_settings_range'] = array(
    '#type' => 'textfield',
    '#title' => t('Range Number'),
    '#default_value' => variable_get('camplus_pr_settings_range', '5'),
    '#description' => 'how many group of settings',
    '#required' => TRUE,
  );
  $form['camplus_pr_financial_year_begin'] = array(
    '#type' => 'textfield',
    '#title' => t('FINANCIAL YEAR Begin'),
    '#default_value' => variable_get('camplus_pr_financial_year_begin', '09-01'),
    '#required' => TRUE,
  );  
  $form['camplus_pr_financial_year_end'] = array(
    '#type' => 'textfield',
    '#title' => t('FINANCIAL YEAR ENd'),
    '#default_value' => variable_get('camplus_pr_financial_year_end', '08-31'),
    '#required' => TRUE,
  );    
  $form['camplus_pr_enable_mixable_key'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable mixable key'),
    '#default_value' => variable_get('camplus_pr_enable_mixable_key', 1),
    '#description' => '是否允许通用,默认允许',
  );  
  $form['camplus_pr_show_budget_history'] = array(
    '#type' => 'textfield',
    '#title' => t('Show Budget History'),
    '#default_value' => variable_get('camplus_pr_show_budget_history', '1'),
    '#description' => '显示最近几年的预算报表？',
    '#required' => TRUE,
  );   
  $form['warning_info'] = array('#markup' => t('注意:一经设置，请管理员慎重更改!'),
  '#weight'=>-10,'#prefix' => '<div class="messages warning">',
  '#suffix' => '</div>');
  return system_settings_form($form);
}

function camplus_pr_approve_settings_form() {

  $count_rows =  variable_get('camplus_pr_settings_range', '5');
  $roles = user_roles(TRUE, 'camplus purchase request approvable');

  $camplus_pr_approvable_role_weight = variable_get('camplus_pr_approvable_role_weight','');
  $camplus_pr_approvable_role_involved = variable_get('camplus_pr_approvable_role_involved','');
  foreach ($roles as $rid => $role_name) {
    if (in_array($role_name, array('administrator'))) continue;
    if(!$camplus_pr_approvable_role_involved[$role_name]) continue;
    $weight = $camplus_pr_approvable_role_weight[$role_name];
    $order[$weight] = array('rid'=>$rid,'name'=>$role_name);
  }
  ksort($order,SORT_NUMERIC);

  $workflow_settings = variable_get('camplus_pr_workflow_settings', '');
  dpm($workflow_settings);
  for($i = 0; $i < $count_rows; $i++) {
    foreach ($order as $key => $role) {
      $default_value = 0;
      if(isset($workflow_settings[$i][$role['rid']])) {
        $default_value = $workflow_settings[$i][$role['rid']];
      }
      $form[$i][$i.'-workflow-'.$role['rid']] = array(
        '#type' => 'checkbox',
        '#default_value' => $default_value,
      );
    }
  }


  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
    '#weight' => 5,
  );
  return  $form;
}

function camplus_pr_approve_settings_form_submit($form, &$form_state) {
  // foreach ($form_state['values'] as $key => $value) {
  //   if(strstr($key, '-workflow-')) {
  //     $workflow_settings[$key] = $form_state['values'][$key];
  //   }
  // }

  foreach ($form_state['values'] as $key => $value) {
    $subject = $key;
    if(strstr($key, '-workflow-')) {
      // $range_settings[$key] = $form_state['values'][$key];
      preg_match('/\d+-/', $subject, $matches);
      $index = str_replace('-', '', $matches[0]);
      preg_match('/-\d+/', $subject, $matches);
      $rid = str_replace('-', '', $matches[0]);
      $workflow_settings[$index][$rid] = $form_state['values'][$key];
    }
  }
  variable_set('camplus_pr_workflow_settings', $workflow_settings);

}

function theme_camplus_pr_approve_settings_form($variables) {
  $form = $variables['form'];
  // $errors = form_get_errors() != FALSE ? form_get_errors() : array();
  $rows = array();
  $count_rows =  variable_get('camplus_pr_settings_range', '5');
  $roles = user_roles(TRUE, 'camplus purchase request approvable');

  $camplus_pr_approvable_role_weight = variable_get('camplus_pr_approvable_role_weight','');
  $camplus_pr_approvable_role_involved = variable_get('camplus_pr_approvable_role_involved','');
  foreach ($roles as $rid => $role_name) {
    if (in_array($role_name, array('administrator'))) continue;
    if(!$camplus_pr_approvable_role_involved[$role_name]) continue;
    $weight = $camplus_pr_approvable_role_weight[$role_name];
    $order[$weight] = array('rid'=>$rid,'name'=>$role_name);
  }
  ksort($order,SORT_NUMERIC);  

 $range_settings =  variable_get('camplus_pr_range_settings');

  for($i = 0; $i < $count_rows; $i++) {
    $row = array();
    $row[] = $range_settings[$i]["begin"] .'--'. $range_settings[$i]["end"];
    foreach ($order as $key => $role) {
      $row[] = drupal_render($form[$i][$i.'-workflow-'.$role['rid']]);
    }
    $row = array('data' => $row);
    $rows[] = $row;
  }
  $header[] = 'Range'.'(HK$)';
  foreach ($order as $key => $role) {
    $header[] = $role['name'];
  }

  if (empty($rows)) {
    $rows[] = array(array('data' => $form['#empty_text'], 'colspan' => '2'));
  }
  $output = theme('table', array('header' => $header, 'rows' => $rows, 'attributes' => array('id' => 'approvable_role')));
  $output .= drupal_render_children($form);
  $warning = '<div class="messages warning">一经设置，请审慎更改! </div>';
  return $warning.$output;
}




function camplus_pr_budget_settings_form() {
  if(isset($_REQUEST['financial_year'])){
    // $financial_year = $_REQUEST['financial_year'];
    $financial_year = $_REQUEST['financial_year'].'-01-01 00:00:00';
  }else {
    $financial_year = NULL;
  }
  $public_groups = druedu_user_get_nodes_by_group('school_department');
  foreach ($public_groups as $g_nid => $g_node) {
    $groups[$g_nid]['gid'] = $g_nid;
    $groups[$g_nid]['depth'] = 0;
    $groups[$g_nid]['parent'] = 0;
    $groups[$g_nid]['type'] = 'school_department';
    $groups[$g_nid]['name'] = $g_node->title; 
    //($grade, $subject = null, $class = null, $grade_group_content = 'subject', $subject_group_content = 'class')
    // $all_subjects_node = druedu_user_get_nodes_by_group($g_nid, $subject = null, $class = null, $grade_group_content = 'budget_item');
    $all_subjects_node = camplus_pr_get_bis_by_year($g_nid,$financial_year);
    foreach ($all_subjects_node as $s_nid => $s_node) {
      $groups[$s_nid]['gid'] = $s_nid;
      $groups[$s_nid]['depth'] = 1;
      $groups[$s_nid]['parent'] = $g_nid;
      $groups[$g_nid]['type'] = 'budget_item';
      $groups[$s_nid]['name'] = $s_node->title;
    }
  }

  $form['#tree'] = TRUE;
  $form['groups'] = array(
    '#tree' => TRUE,
  );
  $years_count = variable_get('camplus_pr_show_budget_history', '1');//this year & next year
  $history_link = '';
  while ($years_count) {
    $history_link .= l(date('Y')-$years_count,'admin/people/advanced_management/budget/settings',array ('query' => array ('financial_year' =>date('Y')-$years_count)) ).'&nbsp;&nbsp;';
    $years_count--;
  }
  $form['financial_year'] = array(
    '#markup' => $history_link.'&nbsp;&nbsp;'.l(date('Y'),'admin/people/advanced_management/budget/settings').'&nbsp;&nbsp;'.l(date('Y')+1,'admin/people/advanced_management/budget/settings',array ('query' => array ('financial_year' =>date('Y')+1)) ),
  );
  // l($text = 10, $path = 'search/all', $options = array ('path' => '/search/all', 'query' => array ('s' => 'teacher', 'items_per_page' => 10)));
  $order = 1;
  if(isset($groups['-1']))unset($groups['-1']);
  foreach ($groups as $gid => $group) {
      $form['groups'][$gid]['gid'] = array(
        '#type' => 'hidden',
        '#value' => $groups[$gid]['gid'],
      );
      $form['groups'][$gid]['parent'] = array(
        '#type' => 'hidden',
        // Yes, default_value on a hidden. It needs to be changeable by the javascript.
        '#default_value' => $groups[$gid]['parent'],
      );
      $form['groups'][$gid]['depth'] = array(
        '#type' => 'hidden',
        // Same as above, the depth is modified by javascript, so it's a default_value.
        '#default_value' =>  $groups[$gid]['depth'],
      );
      $form['groups'][$gid]['title'] = array(
        '#type' => 'hidden',
        // Same as above, the depth is modified by javascript, so it's a default_value.
        '#default_value' =>   $groups[$gid]['name'],
      );

    $form['groups'][$gid]['#group'] = $groups[$gid];
    $form['groups'][$gid]['#weight'] = $order;
    $form['groups'][$gid]['weight'] = array(
      '#type' => 'textfield',
      '#title' => t('Weight for @title', array('@title' => $group['name'])),
      '#title_display' => 'invisible',
      '#size' => 4,
      '#default_value' => $order,
      '#attributes' => array('class' => array('role-weight')),
    );
    $order++;

  }
  camplus_pr_get_prs(4, $uid = NULL);
  return $form;
}



/**
 * Returns HTML for the role order and new role form.
 *
 * @param $variables
 *   An associative array containing:
 *   - form: A render element representing the form.
 *
 * @ingroup themeable
 */
function theme_camplus_pr_budget_settings_form($variables) {
  $form = $variables['form'];
  $header = array(
    t('Budget item'),
    t('Weight'),
    t('Amount'),
    t('已批支出'),
    t('待批支出'),
    t('预算余额'),
    t('Allowance'),
    t('max余额'),
    t('Mixable Key'),
    t('通用余额'),
    t('Operations')
    // array('data' => , 'colspan' => 2)
    );

  foreach (element_children($form['groups']) as $key=>$gid) {

    $group = &$form['groups'][$gid];
    $name = $group['#group']['name'];
    $row = array();
    $node = node_load($gid);
    {//in_array($gid, array(DRUPAL_ANONYMOUS_RID, DRUPAL_AUTHENTICATED_RID))
     

      $row[] = (isset($group['#group']['depth']) && $group['#group']['depth'] > 0 ? theme('indentation', array('size' => $group['#group']['depth'])) : ''). t('@name', array('@name' => $name));

      $group['gid']['#attributes']['class'] = array('group-id');
      $group['parent']['#attributes']['class'] = array('group-parent');
      $group['depth']['#attributes']['class'] = array('group-depth');

      $row[0] .= drupal_render($group['parent']) . drupal_render($group['gid']) . drupal_render($group['depth']);
      //$group['weight']['#attributes']['class'] = array('term-weight');
      $form['groups'][$gid]['weight']['#attributes']['class'] = array('group-weight');
      $row[] = drupal_render($form['groups'][$gid]['weight']);
      if($node->type == 'budget_item'){
        if(isset($node->field_pr_budget[LANGUAGE_NONE])) {
          $field_pr_budget = $node->field_pr_budget[LANGUAGE_NONE][0]['value'];
          $row[] = $field_pr_budget;
        }else{ 
          $field_pr_budget = 0;
          $row[] = '-';
        }
       //已批支出 get all PRs
        $budget_nid = $gid;
        $prs = camplus_pr_get_prs($budget_nid);
         // $prs = druedu_user_get_nodes_by_group($gid, $subject = null, $class = null, $grade_group_content = 'purchase_request');

         $pending = 0;
         $approved = 0;
         $rejectd = 0;
         // get  approved appending and rejectd
         foreach ($prs as $nid => $pr_node) {
            // 排除canceled PRs
            $flags = flag_get_counts('node', $nid, $reset = FALSE);
            if(isset($flags['cancel']) && $flags['cancel']){
               dpm('canceled pr:'.$nid,__LINE__);
               continue;
            }

           $widgets = rate_get_active_widgets('node', $pr_node->type);
           //get pr item
           foreach ($pr_node->field_budget_items[LANGUAGE_NONE] as $key => $value) {
            if($value['target_id'] ==  $budget_nid) {
              //field_budget_items_amount_index
              $bi_index = $key;
              break;
            }
           }
            foreach ($widgets as $widget_id => $widget) {
              if($widget->name == 'approve'){
                $widget->id = $widget_id;
                $approve_status = _rate_pr_check_permissions($pr_node,$widget);
                switch ($approve_status['workflow_status']) {
                  case 'pending':
                    $pending += $pr_node->field_budget_items_amount[LANGUAGE_NONE][$bi_index]['value'];
                    break;
                  case 'approved':
                    $approved += $pr_node->field_budget_items_amount[LANGUAGE_NONE][$bi_index]['value'];
                    break;
                  default: //rejectd FALSE
                    $rejectd += $pr_node->field_budget_items_amount[LANGUAGE_NONE][$bi_index]['value'];
                    break;
                }
                break;
              }else{
                continue;
              }
            }
         }
        $row[] = sprintf("%01.2f", $approved);

        $row[] = sprintf("%01.2f", $pending);
        $row_d = $field_pr_budget - $approved - $pending;
        $row[] = sprintf("%01.2f", $field_pr_budget - $approved - $pending);// '预算余额';
        if(isset($node->field_pr_allowance[LANGUAGE_NONE])) {
          $row_e = $node->field_pr_allowance[LANGUAGE_NONE][0]['value'];
          $row[] = $row_e;
        }else{
          $row_e = 0;
          $row[] = '-';
        }
        $row[] = sprintf("%01.2f", $row_d + $row_e);//max余额
        if(isset($node->field_mixable_key[LANGUAGE_NONE])) {
          $row[] = $node->field_mixable_key[LANGUAGE_NONE][0]['value'];
        }else{
          $row[] = '-';
        }
        $row[] = get_bi_mixable_amount($gid);//'通用余额';
        $row[] = l(t('setting'), 'node/' . $gid.'/edit');
      }else {
        $row[] ='';//Amount
        $row[] ='';//已批支出
        $row[] ='';//待批支出
        $row[] ='';//预算余额
        $row[] ='';//Allowance
        $row[] ='';//max余额
        $row[] ='';//Mixable Key
        $row[] ='';//通用余额
        $row[] ='';//l(t('edit'), 'node/' . $gid.'/edit');
      }

      $rows[$gid] = array('data' => $row, 'class' => array('draggable','locked'));
    }
  }
    
  // Add drag and drop if parent fields are present in the form.
    drupal_add_tabledrag('groups_tree', 'match', 'parent', 'group-parent', 'group-parent', 'group-id', FALSE);
    drupal_add_tabledrag('groups_tree', 'depth', 'group', 'group-depth', NULL, NULL, FALSE);
    drupal_add_tabledrag('groups_tree', 'order', 'sibling', 'group-weight');
    drupal_add_js(drupal_get_path('module', 'druedu_user_tree') . '/druedu_user_tree.js');
  
 

  $output = theme('table', array('header' => $header, 'rows' => $rows, 'attributes' => array('id' => 'groups_tree')));
  $output = drupal_render_children($form).$output;
  return $output;
}