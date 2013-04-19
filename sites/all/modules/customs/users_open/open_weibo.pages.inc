<?php
/**
 * weibo login process...
 */
function weibo_login() {
	//TODO weibo用户已经绑定B账户，但他在A账户里又进行绑定，此时跳转到用户B了，需要组织并提示。
  $weibo_config = open_weibo_get_config();
	if(is_null($weibo_config['open_weibo_app_key']) || is_null($weibo_config['open_weibo_app_secret'])){
		 drupal_set_message(t('请配置appkey&app_secret'),'error');
		 drupal_goto('admin/config/openusers/weibo');
		 return;
	}
	require_once("weibo_sdk/saetv2.ex.class.php");
	global $o;
  $o = new SaeTOAuthV2( $weibo_config['open_weibo_app_key'] , $weibo_config['open_weibo_app_secret'], $access_token = NULL, $refresh_token = NULL) ;//($client_id, $client_secret, $access_token = NULL, $refresh_token = NULL) 

	if (!isset($_REQUEST['code'])){
		$aurl = $o->getAuthorizeURL( $weibo_config['open_weibo_redirect_uri']);
		header("Location:$aurl");
    return;
	}else{
		$keys = array();
		$keys['code'] = $_REQUEST['code'];
		$keys['redirect_uri'] = $weibo_config['open_weibo_redirect_uri'];
		try {
			$token = $o->getAccessToken( 'code', $keys ) ;
		} catch (OAuthException $e) {
			//dpm($e,'OAuthException');			 
			drupal_set_message('新浪微博帐号验证失败', 'error');
			drupal_goto('user');
		} 
		$_SESSION['open_weibo_access_token'] = $token;
		$open_weibo_uid = $token['uid'];
		// 存储session 创建用户，已有用户，使用户登录，update token.
    $c = new SaeTClientV2( $weibo_config['open_weibo_app_key'], $weibo_config['open_weibo_app_secret'],$token['access_token']);
    
    $userInfo = $c->show_user_by_id($open_weibo_uid);
    $open_weibo_user = array(
      'open_uid'=> $open_weibo_uid,
      'open_name'=> $userInfo['screen_name'],
      'open_token' => $token['access_token'],
      'open_type'=>'weibo',
      'open_gender'=>$userInfo['gender'],
      //profile_image_url format http://tp1.sinaimg.cn/1691862500/50/1267524211/1
      'open_picture'=>$userInfo['profile_image_url'].'.jpg',        
      'open_signature'=>$userInfo['description'],
      'open_location'=>array('city'=>$userInfo['city'],'province'=>$userInfo['province'],'location'=>$userInfo['location'],'blog'=>$userInfo['url']),
      'open_info'=>$userInfo
    );
    open_users_bandapi($open_weibo_user);
	}
  return '';  
}
/**
 * 用户微博绑定或取消绑定
 * @param (object) $ac
 * @see open_weibo_remove_confirm()
 * @see open_weibo_remove_confirm_submit()
 */
function open_weibo_user_config($ac) {
  $output = '';
  //$datas = db_query("SELECT * FROM {open_users} WHERE uid = :uid and open_type=:open_type", array(':uid'=>$ac->uid,':open_type'=>'weibo'))->fetchAllKeyed();
  $result = db_select('open_users', 'c')
    ->fields('c')
		->condition('uid', $ac->uid,'=')
		->condition('open_type', 'weibo','=')
    ->execute()
    ->fetchAssoc();
  
  	if($result['uid']){
  		$items[]=t('Bound account: @name ',array('@name'=>$result['open_name']))
    
    . l('Unbind', 'user/'.$ac->uid.'/open_users/weibo/remove', array('attributes' => array('class' => 'sina_open_user_remove')));
    
    if ($GLOBALS['user']->uid == $ac->uid) {
      //$items[] = drupal_get_form('open_weibo_test_form');
    }
  } else {
    $items[] = t('Not binding yet.') . l(t('Binding?'), 'open_users/weibo');
  }

  $output = theme('item_list', array('items' => $items));
  //theme('item_list', $items);//, '新浪微博', 'ul', array('id' => 'weibo_login_page_config')
  
  return $output;
}

/**
 * Unbind weibo.
 */
function open_weibo_remove_confirm() {
	global $user;
  $result = db_select('open_users', 'c')
	  ->fields('c')
		->condition('uid', $user->uid,'=')
		->condition('open_type', 'weibo','=')
	  ->execute()
	  ->fetchAssoc();
  if ($result) {
    $form = array();
    $form['uid'] = array('#type' => 'hidden', '#value' => $user->uid);
    $output = confirm_form($form,
                    t('Unbind weibo'),
                    'user/'.$user->uid.'/weibo/config',
                    t('The current account bound: @name, are you sure unbind it?<br/>This action can not be restored, but will not affect the already synchronized to weibo.com.',array('@name'=>$result['open_name'])),
                    t('Unbind'),
                    t('Cancle'));
    return $output;
  } else {
    drupal_access_denied();
    exit;
  }
}

function open_weibo_remove_confirm_submit($form, &$form_state) {
		
	db_delete('open_users')
  ->condition('uid', $form_state['values']['uid'])
  ->execute();
	
	db_delete('authmap')
  ->condition('uid', $form_state['values']['uid'])
	->condition('module', 'open_users')
  ->execute();
	
  unset($_SESSION['open_weibo_access_token']);
	drupal_set_message(t('Unbind success！'),'status');
  $form_state['redirect'] = 'user/'.$form_state['values']['uid'];  
  return;
}

function open_weibo_admin_config(){
	global $base_url;
  $form['open_weibo_enabled'] = array(
    '#type' => 'radios',
    '#title' => '启用新浪微博登录本站',
    '#default_value' => variable_get('open_weibo_enabled', 0),
    //TODO need test the default vaule 0
    '#options' => array(t("禁用"), t('启用')),
    '#required' => TRUE,
  );
  $form['open_weibo_app_key'] = array(
    '#type' => 'textfield',
    '#title' => t('新浪微博APP_KEY'),
    '#default_value' => variable_get('open_weibo_app_key', '213710***1'),
    '#description' => 'http://api.weibo.com',
    '#required' => TRUE,
  );
  $form['open_weibo_app_secret'] = array(
    '#type' => 'textfield',
    '#title' => t('新浪微博APP_SECRET'),
    '#default_value' => variable_get('open_weibo_app_secret', '25d717c8bddc*****bc374f33f2ca84b'),
    '#required' => TRUE,
  );
  $form['open_weibo_redirect_uri'] = array(
    '#type' => 'textfield',
    '#title' => t('App回调地址redirect_uri'),
    '#default_value' => $base_url.'?q=open_users/weibo',
    '#required' => TRUE,
  );
	//optional
  /*$form['open_weibo_auto_post'] = array(
    '#type' => 'select',
    '#title' => t('自动发送微博？'),
    '#options' => array('0' => '否', '1' => '是'),
    '#default_value' => variable_get('open_weibo_auto_post', '0'),
    '#description' => '登录时是否自动发送微博',
    '#required' => FALSE,
  );
  $form['open_weibo_auto_post_text'] = array(
    '#type' => 'textarea',
    '#title' => t('自动发送微博微博内容'),
    '#default_value' => variable_get('open_weibo_auto_post_text', '@user已登录@site，赶快去看看吧！http://...'),
    '#description' => '自动发送微博的内容',
    '#required' => FALSE,
  );*/
  return system_settings_form($form);
}
