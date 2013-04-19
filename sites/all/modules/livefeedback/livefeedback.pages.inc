<?php

/**
 * Callback for ajax response
 *
 */
function livefeedback_ajax_responder() {

  if (!isset($_POST['url']) ) {
    drupal_json_output(array(
      'status'  => FALSE,
      'message' => t('No data submitted, nothing to process.'),
    ));
    exit;
  }

  global $user;

  $image = isset($_POST['image']) ? $_POST['image'] : NULL;
  $file  = NULL;

  if ($image) {
    $decoded = base64_decode(str_replace('data:image/png;base64,', '', $image) );
    $path    = 'public://' . variable_get('livefeedback_file_path', 'livefeedback');
    file_prepare_directory($path, FILE_CREATE_DIRECTORY | FILE_MODIFY_PERMISSIONS);
    $file    = file_save_data($decoded, $path);
  }

  if ($file) {

    $data = array(
      'url'       => $_POST['url'],
      'message'   => isset($_POST['message']) ? $_POST['message'] : NULL,
      'fid'       => isset($file->fid) ? $file->fid : NULL,
      'uid'       => $user->uid,
      'data'      => json_encode(isset($_POST['browserSpecs']) ? $_POST['browserSpecs'] : array() ),
      'timestamp' => REQUEST_TIME,
    );
    $id = db_insert('livefeedback')
      ->fields($data)
      ->execute();

    if (variable_get('livefeedback_send_mail', TRUE)) {
      livefeedback_email_send($id);
    }

    drupal_json_output(array(
      'status'  => TRUE,
      'message' => t('Feedback submitted'),
    ));
    exit;

  }
  else {
    watchdog('livefeedback', t('Unable to save file'), array(), WATCHDOG_WARNING);
    drupal_json_output(array(
      'status'  => FALSE,
      'message' => t('Sorry, we were unable to save the screenshot.'),
    ));
    exit;
  }

}
