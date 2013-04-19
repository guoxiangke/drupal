<?php

/**
 * Settings configuration form for Live Feedback.
 *
 */
function livefeedback_configure() {

  $form['livefeedback_send_mail'] = array(
    '#type'          => 'checkbox',
    '#title'         => t('Send an email when feedback is submitted'),
    '#default_value' => variable_get('livefeedback_send_mail', TRUE),
    '#description'   => t('Select this option to send an email to the address configured below whenever a feedback report is submitted.'),
  );
  $form['livefeedback_response_mail'] = array(
    '#type'          => 'textfield',
    '#title'         => t('Email address'),
    '#default_value' => variable_get('livefeedback_response_mail', variable_get('site_mail', '')),
    '#description'   => t('If enabled, email will be sent to this address on feedback submission.'),
  );
  $form['livefeedback_file_path'] = array(
    '#type'          => 'textfield',
    '#title'         => t('File path'),
    '#default_value' => variable_get('livefeedback_screenshot_path', 'livefeedback'),
    '#description'   => t('Screenshots will be saved within this directory. Screenshots are saved in the public files folder.'),
  );
  // Check whether the livefeedback directory exists.
  if (variable_get('livefeedback_screenshot_path', 'livefeedback')) {
    $livefeedback_path = file_default_scheme() . '://' . variable_get('livefeedback_screenshot_path', 'livefeedback');
    if (!file_prepare_directory($livefeedback_path, FILE_CREATE_DIRECTORY | FILE_MODIFY_PERMISSIONS)) {
      form_set_error('livefeedback_file_path', t('The directory %directory does not exist or is not writable.', array('%directory' => $livefeedback_path)));
      watchdog('file system', 'The directory %directory does not exist or is not writable.', array('%directory' => $livefeedback_path), WATCHDOG_ERROR);
    }
  }
  return system_settings_form($form);
}

/**
 * Get livefeedback data and pass it to be exported as CSV.
 */
function livefeedback_export() {
  $query = db_select('livefeedback', 'lf');
  $query->fields('lf');
  $num_rows = $query->countQuery()->execute()->fetchField();
  // Export the results to CSV.
  export_to_csv($query->execute());
}

/**
 * Convert DB results to a CSV file and send a file attachment to the user agent.
 */
function export_to_csv($result, $filename = 'results.csv') {
  drupal_add_http_header('Content-Type', 'text/csv');
  drupal_add_http_header('Content-Disposition', 'attachment; filename=' . $filename);

  $printColumns = TRUE;
  while ($row = $result->fetchAssoc()) {
    // Print the column names at the top of the document.
    if ($printColumns) {
      print implode(',', array_keys($row)) . "\r\n";
      $printColumns = FALSE;
    }
    print implode(',', $row) . "\r\n";
  }
}


/**
 * Displays the Live Feedback Entries.
 */
function livefeedback_viewentries() {
  // Creating the header.
  $header = array(
    array('data' => t('User'), 'field' => 'uid'),
    array('data' => t('URL'), 'field' => 'url'),
    array('data' => t('Message'), 'field' => 'message'),
    array('data' => t('Date'), 'field' => 'timestamp', 'sort' => 'desc'),
    array('data' => t('Details'), 'field' => 'lid'),
  );

  // Get the data from the livefeedback table. Note that join() doesn't return
  // a SelectQuery for some reason, making chaining not possible.
  $query = db_select('livefeedback', 'lf');
  $query->join('users', 'u', 'lf.uid = u.uid');
  $query->fields('lf', array('lid', 'uid', 'url', 'message', 'timestamp'));
  $query->fields('u', array('name'));
  $results = $query->extend('PagerDefault')
    ->extend('TableSort')
    ->orderByHeader($header)
    ->limit(10)
    ->execute();

  // Preparing the display table.
  $rows = array();
  foreach ($results as $feedback) {
    $rows[] = array(
      l($feedback->name, 'user/' . $feedback->uid),
      l($feedback->url, $feedback->url),
      substr(check_plain($feedback->message), 0, 25) . '...',
      format_date($feedback->timestamp),
      l(t('View'), 'admin/reports/livefeedback/' . $feedback->lid),
    );
  }

  // Displaying the table.
  $output['list'] = array(
    '#theme'   => 'table',
    '#header'  => $header,
    '#rows'    => $rows,
    '#caption' => t('Feedback Reports'),
    '#sticky'  => TRUE,
    '#empty'   => t('No feedback entries yet.'),
  );

  return $output;

}

/**
 * Displays the Live Feedback Individual Entry.
 *
 */
function livefeedback_viewentry($id) {

  $query = db_select('livefeedback', 't');
  $query->join('users', 'u', 'u.uid = t.uid');
  $query->fields('t');
  $query->fields('u', array('name'));
  $query->condition('lid', $id, '=');

  $result    = $query->execute()->fetchObject();

  $image_url = file_create_url(file_load($result->fid)->uri);
  $size      = getimagesize($image_url);
  $entry     = (object) array(
    'id'         => $result->lid,
    'message'    => check_plain($result->message),
    'url'        => $result->url,
	'data'		 => json_decode($result->data),
    'date'       => format_date($result->timestamp),
    'created'    => $result->timestamp,
    'image_link' => l(t('See full size screenshot'), $image_url),
    'image_url'  => $image_url,
    'image'      => theme('image', array(
      'path'   => $image_url,
      'width'  => 800,
      'height' => $size[1] / ($size[0] / 800),
    )),
    'uid'        => $result->uid,
    'user'       => $result->name,
  );

  return theme('livefeedback_item', array('content' => $entry));

}
