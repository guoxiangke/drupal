<?php

/**
* Implements hook_js_alter().
*
* This function swap out jQuery to use an updated version of the library.
*/
function love_js_alter(&$javascript) {
  //$javascript['misc/jquery.js']['data'] = drupal_get_path('theme', 'love').'/js/jquery.js';
}
/**
 * Preprocess variables for page.tpl.php
 *
 * @see page.tpl.php
 */
function love_preprocess_page(&$vars) {
  // Move secondary tabs into a separate variable.
  $vars['tabs2'] = array(
    '#theme' => 'menu_local_tasks',
    '#secondary' => $vars['tabs']['#secondary'],
  );
  unset($vars['tabs']['#secondary']);

  if (isset($vars['main_menu'])) {
    $vars['primary_nav'] = theme('links__system_main_menu', array(
      'links' => $vars['main_menu'],
      'attributes' => array(
        'class' => array('links', 'inline', 'main-menu','clearfix'),
      ),
      'heading' => array(
        'text' => t('Main menu'),
        'level' => 'h2',
        'class' => array('element-invisible'),
      )
    ));
  }
  else {
    $vars['primary_nav'] = FALSE;
  }
   
  if (isset($vars['secondary_menu'])) {
    //TODO: XXX Docy menu @see love_menu_alter() love_dynamic_menu_call()
    //dynamic menu of userName in navbar.
    global $user;
    //if($user->uid)
    //$vars['secondary_menu']['menu-2']['title'] = $user->name;
    $vars['secondary_nav'] = theme('links__system_secondary_menu', array(
      'links' => $vars['secondary_menu'],
      'attributes' => array(
        'class' => array('links', 'inline', 'secondary-menu','clearfix'),
      ),
      'heading' => array(
        'text' => t('Secondary menu'),
        'level' => 'h2',
        'class' => array('element-invisible'),
      )
    ));

  }
  else {
    $vars['secondary_nav'] = FALSE;
  }

  $account = user_load($user->uid);
  if($account->uid){
    if(isset($account->picture->uri)){
      $filepath = $account->picture->uri;
    }elseif (variable_get('user_picture_default', '')) {
      $filepath = variable_get('user_picture_default', '');
    }
    $vars['menu_user_picture'] = theme('image_style', array('style_name' => 'canvas30', 'path' => $filepath, 'getsize' => TRUE, 'attributes' => array('class' => 'thumb', 'width' => '30', 'height' => '30')));
  
  }

  // Prepare header.
  $site_fields = array();
  if (!empty($vars['site_name'])) {
    $site_fields[] = $vars['site_name'];
  }
  if (!empty($vars['site_slogan'])) {
    $site_fields[] = $vars['site_slogan'];
  }
  $vars['site_title'] = implode(' ', $site_fields);
  if (!empty($site_fields)) {
    $site_fields[0] = '<span>' . $site_fields[0] . '</span>';
  }
  $vars['site_html'] = implode(' ', $site_fields);

  // Set a variable for the site name title and logo alt attributes text.
  $slogan_text = $vars['site_slogan'];
  $site_name_text = $vars['site_name'];
  $vars['site_name_and_slogan'] = $site_name_text . ' ' . $slogan_text;

  //Page Template Suggestions per Node Type
  if (isset($vars['node'])) {
  // If the node type is "blog" the template suggestion will be "page--blog.tpl.php".
   $vars['theme_hook_suggestions'][] = 'page__'. str_replace('_', '--', $vars['node']->type);
  }
}

/**
 * Process variables for user-picture.tpl.php.
 *
 * The $variables array contains the following arguments:
 * - $account: A user, node or comment object with 'name', 'uid' and 'picture'
 *   fields.
 *
 * @see user-picture.tpl.php
 */
function love_preprocess_user_picture(&$variables) {
  $variables['user_picture'] = '';
  if (variable_get('user_pictures', 0)) {
    $account = $variables['account'];
    if (!empty($account->picture)) {
      // @TODO: Ideally this function would only be passed file objects, but
      // since there's a lot of legacy code that JOINs the {users} table to
      // {node} or {comments} and passes the results into this function if we
      // a numeric value in the picture field we'll assume it's a file id
      // and load it for them. Once we've got user_load_multiple() and
      // comment_load_multiple() functions the user module will be able to load
      // the picture files in mass during the object's load process.
      if (is_numeric($account->picture)) {
        $account->picture = file_load($account->picture);
      }
      if (!empty($account->picture->uri)) {
        $filepath = $account->picture->uri;
      }
    }
    elseif (variable_get('user_picture_default', '')) {
      $filepath = variable_get('user_picture_default', '');
    }
    if (isset($filepath)) {
      $alt = t("@user's picture", array('@user' => format_username($account)));
      // If the image does not have a valid Drupal scheme (for eg. HTTP),
      // don't load image styles.
      if (module_exists('image') && file_valid_uri($filepath) && $style = variable_get('user_picture_style', '')) {
        $variables['user_picture'] = theme('image_style', array('style_name' => $style, 'path' => $filepath, 'alt' => $alt, 'title' => $alt));
      }
      else {
        $variables['user_picture'] = theme('image', array('path' => $filepath, 'alt' => $alt, 'title' => $alt));
      }
      if (!empty($account->uid) && user_access('access user profiles')) {
        $attributes = array('attributes' => array('title' => t('View user profile.')), 'html' => TRUE);
        //XXX dale user/uid =>profile-main/uid
        $variables['user_picture'] = l($variables['user_picture'], "user/$account->uid", $attributes);
      }
    }
  }
}
function love_preprocess_user_profile(&$variables) {
  if($variables['elements']['#view_mode'] == 'full') {
    //remove displayed of user picture on user page
    unset($variables['elements']['user_picture']);
    unset($variables['user_profile']['user_picture']);
  }
}
/**
 * love_form_BASE_FORM_ID_alter
 */
 
function love_form_node_form_alter(&$form, &$from_state, $form_id) {
  
  if($form_id == 'photo_node_form' || $form_id == 'status_node_form'){ //node/add/photo
      $form['author']['#access'] = FALSE;
      $form['options']['#access'] = FALSE; 
      $form['comment_settings']['#access'] = FALSE; 
      
      $form['path']['#access'] = FALSE;
      $form['revision_information']['#access'] = FALSE; 
      $form['menu']['#access'] = FALSE; 
      $form['actions']['preview']['#access'] = FALSE; 
      $form['book']['#access'] = FALSE;     
  }
  if($form_id == 'photo_node_form') {
    $form['og_group_ref'][LANGUAGE_NONE][0]['admin']['#access'] = FALSE;
    // $form['field_status_tags']['#access'] = FALSE;
    if(isset($form['og_group_ref'][LANGUAGE_NONE][0]['default'])) {
      // $options = $form['og_group_ref'][LANGUAGE_NONE][0]['default']['#options'];
      //2 is the love group gid.
      $form['og_group_ref'][LANGUAGE_NONE][0]['default']['#default_value'] = 2;  

      $form['og_group_ref']['#prefix'] = '<div class="hide">';
      $form['og_group_ref']['#suffix'] = '</div>';
    }
  }
}

/**
 * add link to login -custom page.
 */
function love_form_user_login_alter(&$form, &$form_state, $form_id) {

      $form['name']['#title'] = '邮箱';
      if(isset( $form['open_weibo_login'])){
        $form['actions']['weibo'] = $form['open_weibo_login'];
        $form['open_weibo_login']['#access'] = FALSE;
      }
      $items = array();
      $items[] = l(t('Request new password'), 'user/password', array('attributes' => array('title' => t('Request new password via e-mail.'))));

      $form['actions']['links'] = array('#markup' => theme('item_list', array('items' => $items)));
}

function love_form_user_register_form_alter(&$form, &$from_state, $form_id) {
  $form['account']['mail']['#disabled']=TRUE;
  $form['relationship_invite_approve']['#default_value']='';
  $form['relationship_invite_approve']['#required']=TRUE;
  $form['relationship_invite_approve']['#weight']=-100;

  if(isset($form['relationship_invite_requester']['#value'])) {

    $inviter = profile2_load_by_user($form['relationship_invite_requester']['#value']);
    if(isset($inviter['main']->field_name[LANGUAGE_NONE][0]['value'])) {
      $inviter_name = $inviter['main']->field_name[LANGUAGE_NONE][0]['value'];
    }else{
      $inviter_name = $form['relationship_invite_requester']['#value']->name;//['name'];
    }
    $form['relationship_invite_approve']['#title']='您认识'.$inviter_name.'吗？';
    # 
    $form['relationship_invite_approve']['#description'] = t('为了营造良好的本站环境，请您如实选择您和邀请者之间的关系，谢谢合作！');

  }
    $form['account']['name']['#title'] = t('昵称');
    $form['account']['mail']['#title'] = t('邮箱');
    $form['signature_settings']['#access'] = TRUE;
    $form['signature_settings']['#weight'] = 11;
    $form['signature_settings']['#title'] = t('爱情宣言');
    $form['signature_settings']['#description'] = t('120字以内，将显示在个人主页～');
    unset($form['signature_settings']['signature']['#description']);
    $form['picture']['#weight'] = -40;
    $form['picture']['#description'] = '请使用正方形相片作为头像，显示效果更佳。';
    $form['picture']['picture_upload']['#title'] = '';
    //$form['picture']['picture_upload']['#required']=TRUE; 
    
}

function love_form_invite_form_alter(&$form, &$from_state, $form_id) {
    //dpm($form);

    $form['submit']['#value'] = t('发送邀请');
    $form['submit_show']['#value'] = t('生成邀请链接');;
    //$form['subject_markup']['#title'] = t('标题');
    $form['subject_markup']['#access'] = FALSE;
    $form['message']['#disabled'] = TRUE;
    //$form['message']['#title'] = t('邀请函');
    $form['from']['#access'] = FALSE;
    if(!user_access('administer users')) {
     $form['submit']['#access'] = FALSE;
     $form['email']['#type'] = 'textfield';
    }
    $form['message']['#access'] = FALSE; 
    if(isset($form['rtid'])) {
      $form['rtid']['#default_value'] = 2;//$form['rtid']['#options'][2];//#options 熟人
      $form['rtid']['#access'] = FALSE;  
    }

}

function love_preprocess_block(&$variables, $hook) {
// Add a count to all the blocks in the region.
 $variables['classes_array'][] = 'clearfix';

// By default, Zen will use the block--no-wrapper.tpl.php for the main
// content. This optional bit of code undoes that:
//if ($variables['block_html_id'] == 'block-system-main') {
//  $variables['theme_hook_suggestions'] = array_diff($variables['theme_hook_suggestions'], array('block__no_wrapper'));
//}
}
/**
 *  fixed private msg bug [user]
 *  http://drupal.org/node/1749106  #3
 */

function love_privatemsg_username($variables) {
  $recipient = $variables['recipient'];
  $options = $variables['options'];
  if (!isset($recipient->uid)) {
    $recipient->uid = $recipient->recipient;
  }
  if (!empty($options['plain'])) {
    $name = check_plain(format_username($recipient));
    if (!empty($options['unique'])) {
      //$name .= ' [user]'; //CHANGED: do not addd user
    }
    return $name;
  }
  else {
    return theme('username', array('account' => $recipient));
  }
}


/**
 * Theme function for a list of heartbeat activity messages.
 */
function love_heartbeat_list($variables) {
  $heartbeatStream = $variables['stream'];

  if (!$heartbeatStream || !$heartbeatStream->hasAccess()) {
    return '';
  }

  global $user, $language;
  $content = '';

  $content .= $heartbeatStream->prefix;

  if (!isset($heartbeatStream->config) || empty($heartbeatStream->config->class)) {

    $content .= drupal_render($variables['content']);

  }
  else {

    $content .= '<div id="heartbeat-stream-' . $heartbeatStream->config->class . '" class="heartbeat-' . ($heartbeatStream->isPage() ? 'page' : 'block')  . ' heartbeat-stream heartbeat-stream-' . $heartbeatStream->config->class . '">';
    $content .= '<ul class="heartbeat-messages-wrapper">';

    if (empty($heartbeatStream->messages)) {

      $content .= '<p class="heartbeat-empty"><em>' . t('No activity yet.') . '</em></p>';

    }
    else {

      $content .= drupal_render($variables['content']);

    }

    $content .= '</ul></div>';

  }

  $content .= $heartbeatStream->suffix;

  return $content;
}