<?php

/**
 * @file
 * Hooks provided by the Checklist module.
 */

/**
 * @addtogroup hooks
 * @{
 */

/**
 * Retrieve a list of groups defined.
 *
 * @return
 *   An array of associative arrays. Each inner array has elements:
 *   - "type": The internal type of the item.
 *   - "title": The human-readable, localized name of the item type.
 *   - "description": (optional) A short description of what the item
 *      type will do or require.
 *   - "file": (optional) The path to the file to include before calling
 *     additional hooks related to this item type. Path should be relative to
 *     module.
 */
function hook_checklist_item_type() {
  return array(
    array(
      'type' => 'user',
      'title' => t('User check'),
      'description' => t('A checkbox must be checked by the user.'),
      'file' => 'includes/checklist.handlers.inc',
    ),
  );
}

/**
 * When a checklist limits navigation of users this function is
 * called to determine valid paths that the user should be able
 * to access to complete the checklist item.
 *
 * @param $instance
 *   The checklist instance that is being checked.
 * @param $item
 *   The checklist item specific to the user. Data specific
 *   to the implementing module is stored in 'data'.
 * $param $account
 *   The user that the paths are being checked for.
 *
 * @return
 *   An array of paths that the user is allowed to access.
 */
function hook_checklist_item_ITEM_TYPE_allowed_paths($instance, $item, $account) {
  return array('node/add/' . $item->data['node-type']);
}

/**
 * Checklist item is going to be displayed to the end user.
 * Provide styling values and other information for displaying
 * to the user.
 *
 * @param $instance
 *   The checklist instance that is being checked.
 * @param $item
 *   The checklist item specific to the user. Data specific
 *   to the implementing module is stored in 'data'.
 * $param $account
 *   The user that the paths are being checked for.
 *
 * @return
 *   An associative array of values to theme the item for display. All
 *   values are optional.
 *   - "path": the url path to link the item to. Used with l().
 *   - "div_class": an array of classes to add to the div surrounding the
 *     checklist item.
 *   - "query": addtional query string values, passed to l()
 *
 */
function hook_checklist_item_ITEM_TYPE_display_options($instance, $item, $account) {
  return array('path' => 'node/add/' . $item->data['node-type']);
}

/**
 * Based off of the paths returned by
 * hook_checklist_item_ITEM_TYPE_allowed_paths(), the currently viewed
 * page is equal to one of the paths. The item is being processed
 * in that sense, but this does not mean that your item is being
 * completed.
 *
 * @param $instance
 *   The checklist instance that is being checked.
 * @param $item
 *   The checklist item specific to the user. Data specific
 *   to the implementing module is stored in 'data'.
 * $param $account
 *   The user that the paths are being checked for.
 *
 * @return
 *   TRUE if the item is completed simply by visiting the path/page.
 *   If the item is not completed, then you must define another way
 *   for the user to complete the item, and once completed, call
 *   _checklist_complete_user_item().
 *
 * @see _checklist_complete_user_item()
 */
function hook_checklist_item_ITEM_TYPE_process_item($instance, $item, $account) {
  static $items = array();

  // This specific implementation will be called by hook_nodeapi() when a
  // node is created to see if it should mark off the item. hook_nodeapi()
  // acutally calls _checklist_complete_user_item().
  if (!is_object($item)) {
    return isset($items[$item]) ? $items[$item] : array(0, 0);
  }

  // Store the item so hook_nodeapi() can call this function later.
  $items[$item->data['node-type']] = array($instance, $item);
  return FALSE;
}

/**
 * Define additional form items for the item edit form of the checklist.
 * This hook is not required if there are no additional options for this
 * item type.
 *
 * @param $form
 *   The $form array to put the new form items in. The form will
 *   be blank by default and the added fields are put inside of
 *   a fieldset.
 * @param $form_state
 *   The standard $form_state array for any form.
 * @param $cl
 *   The checklist that the item is being added to.
 * @param $item
 *   The checklist item that is being edited. Data specific
 *   to the implementing module is stored in 'data'.
 *
 * @return
 *   NONE REQUIRED. Any additional fields stored in the $form
 *   array will be added to the form.
 */
function hook_checklist_item_ITEM_TYPE_admin_form_form($form, $form_state, $cl, $item) {
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
 * Validation of the form items added for this item type.
 *
 * @param $form
 *   The full $form array. All item specific form items are
 *   under the 'specific' key: $form['specific'].
 * @param $form_state
 *   The standard $form_state array for any form.
 * @param $cl
 *   The checklist that the item is being added to.
 * @param $item
 *   The checklist item that is being edited. Data specific
 *   to the implementing module is stored in 'data'.
 *
 * @see hook_checklist_item_ITEM_TYPE_admin_form_form()
 */
function hook_checklist_item_ITEM_TYPE_admin_form_validate($form, $form_state, $cl, $item) {
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
 * Submission of the form items added for this item type. This
 * must be implemented if any data should be stored for this
 * item.
 *
 * @param $form
 *   The full $form array. All item specific form items are
 *   under the 'specific' key: $form['specific'].
 * @param $form_state
 *   The standard $form_state array for any form.
 * @param $cl
 *   The checklist that the item is being added to.
 * @param $item
 *   The checklist item that is being edited. Data specific
 *   to the implementing module is stored in 'data'.
 *
 * @return
 *   Array of data that will be added to the checklist
 *   item object under the 'data' key.
 *
 * @see hook_checklist_item_ITEM_TYPE_admin_form_form()
 * @see hook_checklist_item_ITEM_TYPE_admin_form_validate()
 */
function hook_checklist_item_ITEM_TYPE_admin_form_submit($form, $form_state, $cl, $item) {
  return array('nid' => $form_state['values']['nid']);
}
