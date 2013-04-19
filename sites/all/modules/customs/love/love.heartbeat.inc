<?php
/**
 * Implements hook_heartbeat_template_info().
 */
function love_heartbeat_template_info() {

  $heartbeatmessagetemplates = array();
  /**
   * heartbeat_become_friends.
   * custom for ur.
   */
  if (module_exists('user_relationships')) {

  // Get a list of selected relationship types
  $all_rtypes = user_relationships_types_load();

  foreach ($all_rtypes as $rtype) {

    $heartbeatmessagetemplate = new HeartbeatMessageTemplate();
    $heartbeatmessagetemplate->disabled = FALSE; /* Edit this to true to make a default heartbeatmessagetemplate disabled initially */
    $heartbeatmessagetemplate->api_version = 1;

    if(!$rtype->requires_approval && $rtype->is_oneway){
      //follow 不需要批准&& is_oneway 得关系，谁成为谁的粉丝

      $heartbeatmessagetemplate->message_id = 'heartbeat_become_'.$rtype->name;
      $heartbeatmessagetemplate->description = 'When a user becomes '.$rtype->name.' of another user (UR-love)';
      $heartbeatmessagetemplate->message = t('!username becomes '.$rtype->name.' of !user2.');
      $heartbeatmessagetemplate->message_concat = t('!username becomes '.$rtype->name.' of %user2%.');//'!username is now friends with %user2%.';
    }
    if($rtype->requires_approval && !$rtype->is_oneway ) {
      //
      $heartbeatmessagetemplate->message_id = 'heartbeat_become_'.$rtype->plural_name;
      $heartbeatmessagetemplate->description = 'When a user approve another request of '.$rtype->plural_name.'(UR-love)';
      $heartbeatmessagetemplate->message = t('!username approved !user2  '.$rtype->plural_name.' request.');
      $heartbeatmessagetemplate->message_concat = t('!username approved %user2% '.$rtype->plural_name.' request.');//'!username is now friends with %user2%.';
    }

    $heartbeatmessagetemplate->perms = 4;
    $heartbeatmessagetemplate->group_type = 'summary';
    $heartbeatmessagetemplate->concat_args = array(
      'group_by' => 'user-user',
      'group_target' => 'user2',
      'group_by_target' => 'username',
      'group_num_max' => '4',
      'merge_separator' => ', ',
      'merge_end_separator' => ' and ',
    );
    $heartbeatmessagetemplate->variables = array(
      '!username' => '',
      '!user2' => '',
    );
    $heartbeatmessagetemplate->attachments = array(
      'buttons' => array(
        'weight' => array(
          'activitycomments' => -9,
          'flagattachment:like' => -10,
        ),
        'settings' => array(
          'activitycomments' => array(
            'activitycomments_node' => 0,
          ),
        ),
        'enabled' => array(
          'activitycomments' => 'activitycomments',
          'flagattachment:like' => 'flagattachment:like',
        ),
      ),
      'content' => array(
        'weight' => array(
          'activitycomments' => -9,
          'flagattachment:like' => -10,
        ),
        'enabled' => array(
          'activitycomments' => 'activitycomments',
          'flagattachment:like' => 'flagattachment:like',
        ),
      ),
    );
    $heartbeatmessagetemplates['heartbeat_become_'.$rtype->name] = $heartbeatmessagetemplate;
  }
  //request
  foreach ($all_rtypes as $rtype) {

    $heartbeatmessagetemplate = new HeartbeatMessageTemplate();
    $heartbeatmessagetemplate->disabled = FALSE; /* Edit this to true to make a default heartbeatmessagetemplate disabled initially */
    $heartbeatmessagetemplate->api_version = 1;

    if(!$rtype->requires_approval && $rtype->is_oneway){
      //follow 不需要批准&& is_oneway 得关系，谁成为谁的粉丝

      // $heartbeatmessagetemplate->message_id = 'heartbeat_become_'.$rtype->name;
      // $heartbeatmessagetemplate->description = 'When a user becomes '.$rtype->name.' of another user (UR-love)';
      // $heartbeatmessagetemplate->message = t('!username becomes '.$rtype->name.' of !user2.');
      // $heartbeatmessagetemplate->message_concat = t('!username becomes '.$rtype->name.' of %user2%.');//'!username is now friends with %user2%.';
    }
    if($rtype->requires_approval && !$rtype->is_oneway ) {
      //
      $heartbeatmessagetemplate->message_id = 'heartbeat_request_'.$rtype->plural_name;
      $heartbeatmessagetemplate->description = 'When a user request '.$rtype->plural_name.' of another(UR-love)';
      $heartbeatmessagetemplate->message = t('!username request '.$rtype->plural_name.' of !user2 .');
      $heartbeatmessagetemplate->message_concat = t('!username request '.$rtype->plural_name.' of %user2%.');// t('!username and %user2% becomes '.$rtype->plural_name.'.');
    }

    $heartbeatmessagetemplate->perms = 4;
    $heartbeatmessagetemplate->group_type = 'summary';
    $heartbeatmessagetemplate->concat_args = array(
      'group_by' => 'user-user',
      'group_target' => 'user2',
      'group_by_target' => 'username',
      'group_num_max' => '4',
      'merge_separator' => ', ',
      'merge_end_separator' => ' and ',
    );
    $heartbeatmessagetemplate->variables = array(
      '!username' => '',
      '!user2' => '',
    );
    $heartbeatmessagetemplate->attachments = array(
      'buttons' => array(
        'weight' => array(
          'activitycomments' => -9,
          'flagattachment:like' => -10,
        ),
        'settings' => array(
          'activitycomments' => array(
            'activitycomments_node' => 0,
          ),
        ),
        'enabled' => array(
          'activitycomments' => 'activitycomments',
          'flagattachment:like' => 'flagattachment:like',
        ),
      ),
      'content' => array(
        'weight' => array(
          'activitycomments' => -9,
          'flagattachment:like' => -10,
        ),
        'enabled' => array(
          'activitycomments' => 'activitycomments',
          'flagattachment:like' => 'flagattachment:like',
        ),
      ),
    );
    $heartbeatmessagetemplates['heartbeat_request_'.$rtype->name] = $heartbeatmessagetemplate;
  }
  }
  return $heartbeatmessagetemplates;
}