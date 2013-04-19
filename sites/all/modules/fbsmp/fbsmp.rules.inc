<?php

/**
 * @file
 *   Provides Rules integration for Facebook-style Micropublisher.
 */

/**
 * Implements hook_rules_event_info().
 */
function fbsmp_rules_event_info() {
  return array(
    'fbsmp_delete_status' => array(
      'label' => t('User deletes a FBSS status which has a FBSMP attachment'),
      'group' => t('Facebook-style Micropublisher'),
      'variables' => array(
        'status' => array('type' => 'statuses', 'label' => t('The FBSS status object')),
        'attachment' => array('type' => 'fbsmp', 'label' => t('The FBSMP attachment object')),
      ),
    ),
    'fbsmp_edit_status' => array(
      'label' => t('User edits a FBSS status which has a FBSMP attachment'),
      'group' => t('Facebook-style Micropublisher'),
      'variables' => array(
        'status' => array('type' => 'statuses', 'label' => t('The old FBSS status object.')),
        'attachment' => array('type' => 'fbsmp', 'label' => t('The old FBSMP attachment object')),
      ),
    ),
    'fbsmp_add_status' => array(
      'label' => t('User adds a FBSS status which has a FBSMP attachment'),
      'group' => t('Facebook-style Micropublisher'),
      'variables' => array(
        'status' => array('type' => 'statuses', 'label' => t('The FBSS status object')),
        'attachment' => array('type' => 'fbsmp', 'label' => t('The FBSMP attachment object')),
      ),
    ),
  );
}

/**
 * Implements hook_rules_condition_info().
 */
function fbsmp_rules_condition_info() {

  $plugins = fbsmp_get_plugins();
  $items = array();

  foreach ($plugins as $plugin => $info) {
    $name = isset($info['name']) ? $info['name'] : $plugin;
    $items['fbsmp_attachment_is_' . $plugin] = array(
      'label' => t('The FBSS status has !pluginobject attachment', array('!pluginobject' => $name)),
      'arguments' => array(
        'plugin' => array('type' => 'value', 'default value' => $plugin),
        'attachment' => array('type' => 'fbsmp', 'label' => t('The FBSMP attachment object.')),
      ),
      'base' => 'fbsmp_check_attachment_condition',
      'group' => t('Facebook-style Micropublisher'),
    );
  }

  return $items;
}

/**
 * Checks if the attachment is of given plugin type.
 */
function fbsmp_check_attachment_condition($plugin, $attachment) {
  return ($plugin == $attachment->type);
}

/**
 * Implements hook_rules_action_info().
 */
function fbsmp_rules_action_info() {
  return array(
    'fbsmp_load_action' => array(
      'label' => t('Load a FBSMP attachment object'),
      'new variables' => array(
        'attachment_loaded' => array('type' => 'fbsmp', 'label' => t('The loaded FBSMP attachment')),
      ),
      'help' => t('Enter the Status ID of the status for which attachment should be loaded.'),
      'group' => t('Facebook-style Micropublisher'),
      'parameter' => array(
        'sid' => array(
          'type' => 'integer',
          'label' => t('Status ID'),
          'description' => t("Enter the Status ID"),
        ),
      ),
    ),
  );
}

/**
 * Loads a status.
 */
function fbsmp_load_action($sid) {
  return array('attachment_loaded' => fbsmp_load($sid));
}

/**
 * Implements hook_rules_data_type_info().
 */
function fbsmp_rules_data_type_info() {
  return array(
    'fbsmp' => array(
      'label' => t('FBSMP attachment to FBSS status'),
      'wrapper class' => 'FBSMPRulesDataWrapper',
      'wrap' => TRUE,
    ),
  );
}

/**
 * Defines the rules node data type.
 */
class FBSMPRulesDataWrapper extends RulesIdentifiableDataWrapper implements RulesDataWrapperSavableInterface {
  public function save() {
    //@TODO Implement this functionality
    return TRUE;
  }

  protected function load($sid) {
    return fbsmp_load($sid);
  }

  protected function extractIdentifier($attachment) {
    return $attachment->sid;
  }
}
