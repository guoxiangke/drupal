<?php
/**
 * 
 * 
 */
function open_users_synch_setting($value=''){
	$form = array();
	$form['titles'] = array(
		'#markup' => t('Please choose which content type you prefer to sync.')
	);
	$synch_types = variable_get('synch_types', NULL);
  if(!$synch_types){
    $synch_types = array();
  }else{
    $synch_types = array_filter(unserialize($synch_types));
  }
  $node_types = node_type_get_types();
  foreach ($node_types as $node_type => $node_type_obj) {
    $form['node_types']["$node_type"] = array(
      '#title'=>$node_type_obj->name,
      '#type' => 'checkbox',
      '#default_value' =>key_exists($node_type_obj->type, $synch_types)?TRUE:FALSE,
      '#description' => $node_type_obj->description,
    );
  }
	// Add the buttons.
	$form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
    '#weight' => 5,
  );
	$form['actions']['reset'] = array(
    '#type' => 'button',
    '#value' => t('reset'),
    '#weight' => 6,
  );
	return $form;
}

/**
 * Form submit handler for the open_users_synch_setting() form.
 */
function open_users_synch_setting_submit($form, &$form_state){
	$node_types = node_type_get_types();
	$setting = array();
	foreach ($node_types as $node_type => $node_type_obj){
		$setting[$node_type] = $form_state['values'][$node_type];
	}
	$synch_types = serialize($setting);
	if(variable_get('synch_types', null)==$synch_types){
  	drupal_set_message(t('设置未更改！'),'status');
	}else{
	  variable_set('synch_types', $synch_types);
		drupal_set_message(t('设置成功！'),'status');
	}
}