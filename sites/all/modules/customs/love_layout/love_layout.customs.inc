<?php

/**
 * Menu callback; view a single node.
 * no title4love
 */
function _node_page_view4love($node) {
  // If there is a menu link to this node, the link becomes the last part
  // of the active trail, and the link name becomes the page title.
  // Thus, we must explicitly set the page title to be the node title.
  //drupal_set_title($node->title);
  $uri = entity_uri('node', $node);
  // Set the node path as the canonical URL to prevent duplicate content.
  drupal_add_html_head_link(array('rel' => 'canonical', 'href' => url($uri['path'], $uri['options'])), TRUE);
  // Set the non-aliased path as a default shortlink.
  drupal_add_html_head_link(array('rel' => 'shortlink', 'href' => url($uri['path'], array_merge($uri['options'], array('alias' => TRUE)))), TRUE);
  return node_show($node);
}

/**
 * Returns a node submission form.
 * no title4love
 */
function _node_add4love($type) {
  global $user;

  $types = node_type_get_types();
  $node = (object) array('uid' => $user->uid, 'name' => (isset($user->name) ? $user->name : ''), 'type' => $type, 'language' => LANGUAGE_NONE);
  //drupal_set_title(t('Create @name', array('@name' => $types[$type]->name)), PASS_THROUGH);
  $output = drupal_get_form($type . '_node_form', $node);

  return $output;
}