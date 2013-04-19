<?php
/**
 * Rules integration.
 */

/**
 * Implements hook_rules_event_info().
 */
function checklist_rules_event_info() {
  return array(
    'checklist_item_complete' => array(
      'label' => t('Checklist item completed'),
      'group' => 'Checklist',
      'arguments' => array(
        'checklist_instance' => array('type' => 'checklist_instance', 'label' => t('The checklist that the item is completed for.')),
        'checklist_item' => array('type' => 'checklist_item', 'label' => t('The checklist item completed.')),
        'completing_user' => array('type' => 'user', 'label' => t('User that completed the item.')),
      ),
    ),
    'checklist_complete' => array(
      'label' => t('Checklist completed'),
      'group' => 'Checklist',
      'arguments' => array(
        'checklist_instance' => array('type' => 'checklist_instance', 'label' => t('The checklist that is completed.')),
        'completing_user' => array('type' => 'user', 'label' => t('User that completed the completed.')),
      ),
    ),
  );
}

/**
 * Implements hook_rules_data_info().
 */
function checklist_rules_data_info() {
  return array(
    'checklist_instance' => array(
      'label' => t('Checklist'),
      'group' => 'Checklist',
      'token type' => 'checklist_instance',
    ),
    'checklist_item' => array(
      'label' => t('Checklist Item'),
      'group' => 'Checklist',
      'token type' => 'checklist_item',
    ),
  );
}

/**
 * Implements hook_rules_action_info()
 */
/*function checklist_rules_condition_info() {
  return array(
    'checklist_rules_condition_has_users' => array(
      'label' => t('Has users'),
      'parameter' => array(
        'instance' => array('label' => t('Instance'), 'type' => 'checklist_instance'),
      ),
      'group' => t('Checklist'),
    ),
  );
}*/
