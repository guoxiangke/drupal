<?php

function uuke_alipay_configue_form($form, &$form_state) {
  $form['uuke_alipay_partner'] = array(
    '#type' => 'textfield',
    '#title' => t('支付宝的PID'),
    '#description' => t('合作者身份-你的支付宝商家服务中的合作者身份.'),
    // '#default_value' => variable_get('uuke_alipay_partner', ''),
    '#size' => 16,
  );
  $form['uuke_alipay_key'] = array(
    '#type' => 'textfield',
    '#title' => t('交易安全校验码'),
    '#description' => t('你的支付宝商家服务中的交易安全校验码.'),
    // '#default_value' => variable_get('uuke_alipay_key', ''),
    '#size' => 16,
  );
  $form['uuke_alipay_seller_email'] = array(
    '#type' => 'textfield',
    '#title' => t('支付宝帐户.'),
    '#description' => t('卖家支付宝帐户.'),
    // '#default_value' => variable_get('uuke_alipay_seller_email', ''),
  );
  $form['uuke_alipay_service'] = array(
    '#title' => t('支付方法'),
    '#type' => 'radios',
    '#default_value' => variable_get('uuke_alipay_service', 'create_partner_trade_by_buyer'),
    '#description' => t('您需要在支付宝商家服务中申请相关的服务.'),
    '#options' => array(
      'create_direct_pay_by_user' => t('支付宝即时到账交易接口'),
      'create_partner_trade_by_buyer' => t('支付宝纯担保交易接口'),
    )
  );  
  return system_settings_form($form);
}

/**
 * 
 * 
 */
function uuke_alipay_content_types_setting_form($value=''){
	$form = array();
	$form['titles'] = array(
		'#markup' => t('可以购买的节点的类型,自动添加Price字段field_uuke_price to the content type')
	);
	$synch_types = variable_get('uuke_alipay_content_types', NULL);
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
function uuke_alipay_content_types_setting_form_submit($form, &$form_state){
	$node_types = node_type_get_types();
	$setting = array();
	foreach ($node_types as $node_type => $node_type_obj){
		$setting[$node_type] = $form_state['values'][$node_type];
	}
	$synch_types = serialize($setting);
	if(variable_get('uuke_alipay_content_types', null)==$synch_types){
  	drupal_set_message(t('设置未更改！'),'status');
	}else{
	  variable_set('uuke_alipay_content_types', $synch_types);
    foreach ($setting as $content_type => $value) {
      $data = array(
        'instances' => array(
          'field_uuke_price' => array(
            0 => array(
              'label' => 'Price',
              'widget' => array(
                'type' => 'number',
                'weight' => '5',
                'settings' => array(),
                'module' => 'number',
              ),
              'settings' => array(
                'min' => '',
                'max' => '',
                'prefix' => '',
                'suffix' => '',
                'user_register_form' => FALSE,
              ),
              'display' => array(
                'default' => array(
                  'label' => 'above',
                  'type' => 'number_decimal',
                  'settings' => array(
                    'thousand_separator' => ' ',
                    'decimal_separator' => '.',
                    'scale' => 2,
                    'prefix_suffix' => TRUE,
                  ),
                  'module' => 'number',
                  'weight' => 9,
                ),
                'teaser' => array(
                  'type' => 'hidden',
                  'label' => 'above',
                  'settings' => array(),
                  'weight' => 0,
                ),
              ),
              'required' => FALSE,
              'description' => '',
              'field_name' => 'field_uuke_price',
              'entity_type' => 'node',
              'bundle' => $content_type,
              'deleted' => '0',
              'default_value' => NULL,
            ),
          ),
        ),
      );
      if($value){//add instances
        foreach ($data['instances'] as $instances_name => $instances) {
          foreach ($instances as $key => $instance) {
            //$instance = field_info_instance('node', 'body', $type->type);
            $ori_instance = field_info_instance('node', $instances_name, $instance['bundle']);
            if (empty($ori_instance)) {
               $instance = field_create_instance($instance);
               watchdog('uuke_alipay', 'created instance for '.$content_type.': '.$instances_name);
            }
          }
        }
      }else{//del instances

        // foreach ($data['instances'] as $instances_name => $instances) {
        //   foreach ($instances as $key => $instance) {
        //     //$instance = field_info_instance('node', 'body', $type->type);
        //     $ori_instance = field_info_instance('node', $instances_name, $instance['bundle']);
        //     if (empty($ori_instance)) {
        //        $instance = field_delete_instance($instance,FALSE);
        //        watchdog('uuke_alipay', 'delete instance for '.$content_type.': '.$instances_name);
        //     }
        //   }
        // }
      }
    }
		drupal_set_message(t('设置成功！'),'status');
    // drupal_set_message(t('请手动删除取消的content_typ field_uuke_price字段'),'status');
	}
}

  /**
   * @file
   *集成支付宝的支付服务.
   *zhupou.cn制作
   */

  function uuke_alipay_notify() {
    //$output = "uc_alipay_return test";
    $partner = variable_get('uuke_alipay_partner', '');
    $security_code = variable_get('uuke_alipay_key', '');
    $sign_type = "MD5";
    $_input_charset = 'UTF-8';
    $transport = 'https';
    watchdog('uc_alipay_notify_called at1', REQUEST_TIME);
    if(!isset($_POST['out_trade_no'])) {
      echo 'fail';
      watchdog('uc_alipay_notify_called at2', REQUEST_TIME);
      return;
    }
    $alipay = new alipay_notify($partner,$security_code,$sign_type,$_input_charset,$transport);
    $verify_result = $alipay->notify_verify();
    watchdog('uc_alipay_notify_called at3 verify_result=', $verify_result);
    if($verify_result) {  //认证合格
     //获取支付宝的反馈参数
      $out_trade_no   = $_POST['out_trade_no'];   //获取支付宝传递过来的订单号
      $order_node = node_load($out_trade_no-0);
      $product_node = node_load($order_node->field_uuke_alipay_product_nid[LANGUAGE_NONE][0]['target_id']);
      $nid = $order_node->nid;
      $uid = $order_node->uid;
      $buy_timestamp = $order_node->created;

      // preg_match('/n\d+/', $out_trade_no, $matches, PREG_OFFSET_CAPTURE);
     //  $nid = str_replace('n', '',$matches[0][0]);//order_id=200 将前面的11位删除 1365500773_n200_u1  n\d+
     //  $product_node = node_load($nid);//product_type
      // preg_match('/u\d+/', $out_trade_no, $matches, PREG_OFFSET_CAPTURE);
     //  $uid = str_replace('u', '',$matches[0][0]);//200 将前面的11位删除 1365500773_n200_u1  n\d+
      // preg_match('/\d+/', $out_trade_no, $matches, PREG_OFFSET_CAPTURE);
      // $buy_timestamp = $matches[0][0];//下单时间
      
      $trade_no =  $_POST['trade_no'];
      $total_fee     = $_POST['total_fee'];      //获取支付宝传递过来的总价格
      $price =  $_POST['price'];
      $quantity =  $_POST['quantity'];
      $trade_status = $_POST['trade_status'];//WAIT_BUYER_PAY
      $trade_status_array = array(
        'WAIT_BUYER_PAY',
        'TRADE_FINISHED',
        'TRADE_SUCCESS',
        'WAIT_SELLER_SEND_GOODS',
        'WAIT_BUYER_CONFIRM_GOODS',
        'TRADE_CLOSED',
      );
      if(!in_array($trade_status,$trade_status_array)) {
          watchdog('uc_alipay_notify', $trade_status.':验证失败1,状态未知 out_trade_no='.$out_trade_no.'&trade_no='.$trade_no);
          echo "fail";
          watchdog('uc_alipay_notify_called at4 验证失败1,状态未知 ', REQUEST_TIME);
          return;
          //log_result ("verify_failed");
      }
      // $receive_name    =$_POST['receive_name'];    //获取收货人姓名
      // $receive_address =$_POST['receive_address']; //获取收货人地址
      // $receive_zip     =$_POST['receive_zip'];     //获取收货人邮编
      // $receive_phone   =$_POST['receive_phone'];   //获取收货人电话
      // $receive_mobile  =$_POST['receive_mobile'];  //获取收货人手机
      /* 
         获取支付宝反馈过来的状态,根据不同的状态来更新数据库 
         WAIT_BUYER_PAY(表示等待买家付款);
         TRADE_FINISHED(表示交易已经成功结束);
        */
      //执行自动发货 begin
      uuke_alipay_auto_send_goods($trade_no,$out_trade_no);
      //执行自动发货 end
      //更新订单
      $request = $_POST;
      $order = uuke_alipay_order_save($request);
      // $query = db_select('uuke_alipay', 'h');
      // $result = $query
      //   ->fields('h', array('uid','nid','trade_no','status'))
      //   ->condition('h.trade_no ',$trade_no)
      //   ->execute()
      //   ->fetchAssoc();
      //这里放入你自定义代码,比如根据不同的trade_status进行不同操作
      // if($result['status'] != $trade_status_in_db) {
      //  // 交易状态改变
      //  // $query = db_update('uuke_alipay')
      //  //  ->fields(array(
      //  //      'status' => $trade_status_in_db,
      //  //    ))
     //  //     ->condition('h.trade_no ',$trade_no)
      //  //  ->execute();
      //  watchdog('uc_alipay_notify', $trade_status.':已经记录,交易状态改变,out_trade_no='.$out_trade_no.'&trade_no='.$trade_no);
      // }else{
      //  watchdog('uc_alipay_notify', $trade_status.':已经记录,交易wei改变,out_trade_no='.$out_trade_no.'&trade_no='.$trade_no);
      // }
      // else{
      //  // db_insert('uuke_alipay', array())
    //  //    ->fields(array(
      //  //   'trade_no' => $trade_no,
      //  //   'out_trade_no' => $out_trade_no,
      //  //   'uid' => $uid,
      //  //   'nid' => $nid,
      //  //   'paid_time' => REQUEST_TIME,
      //  //   'buy_time' => $buy_timestamp,
      //  //   'price' => $price,
      //  //   'quantity' => $quantity,           
      //  //   'type' => $product_node->type,
      //  //   'status' => $trade_status_in_db,
      //  //  ))
      //  // ->execute();
      //  // create a now order node begin
      //  $request = $_POST;
      //  $order = uuke_alipay_order_save($request);
      //  // create a now order node end
      //  // drupal_set_message(t('付款成功!.'), 'status', FALSE);
      //  watchdog('uc_alipay_notify', $trade_status.':交易 added to db!,out_trade_no='.$out_trade_no.'&trade_no='.$trade_no);
      // }
      echo 'success';return;
    }else {    //认证不合格
      watchdog('uc_alipay_notify', $trade_status.':认证不合格,out_trade_no='.$out_trade_no.'&trade_no='.$trade_no);
      echo "fail";return;
      //log_result ("verify_failed");
    }
  }

function uuke_alipay_return() {
  //获取支付宝的反馈参数
  $out_trade_no   = $_GET['out_trade_no'];   //获取支付宝传递过来的订单号
  $order_node = node_load($out_trade_no-0);
  $product_node = node_load($order_node->field_uuke_alipay_product_nid[LANGUAGE_NONE][0]['target_id']);
  $trade_no =  $_GET['trade_no'];
  $trade_status = $_GET['trade_status'];
  // $body = $_GET['body'];

  $partner = variable_get('uuke_alipay_partner', '');
  $security_code = variable_get('uuke_alipay_key', '');
  $sign_type = "MD5";
  $_input_charset = 'UTF-8';
  $transport = 'https';
  $alipay = new alipay_notify($partner,$security_code,$sign_type,$_input_charset,$transport);
  $verify_result = $alipay->return_verify();
  dpm($_GET,'$_GET');
  if($verify_result) {    //认证合格
    if($trade_status == 'WAIT_SELLER_SEND_GOODS') {
      // create a now order node begin
      $request = $_GET;

      $order = uuke_alipay_order_save($request);
  //执行自动发货 begin
  uuke_alipay_auto_send_goods($trade_no,$out_trade_no);
  //执行自动发货 end
      // create a now order node end
      drupal_set_message(t('付款成功!.'), 'status', FALSE);
      drupal_goto('node/'.$product_node->nid);
  }elseif($trade_status == 'TRADE_FINISHED' || $trade_status == 'TRADE_SUCCESS') {
    //这里放入你自定义代码,比如根据不同的trade_status进行不同操作
    //log_result("verify_success"); 
      drupal_set_message(t('已购买，请点此下载安装App.'), 'status', FALSE);
      drupal_goto('node/'.$product_node->nid);
    }else{
      drupal_set_message(t('unknow error: Please conneect admin. trade_status:'.$_GET['trade_status']), 'warning', FALSE);
      drupal_goto('node/'.$product_node->nid);
    }
  }
  else {//认证不合格
    $output = t('您的交易信息是无效的，如果你使用的是已有的返回信息的话，那么交易已经成立，你可以查看订单历史。如果你是黑客的话，俺是守法的好公民，希望你能饶了我这个小店');
    //echo "fail";
    //log_result ("verify_failed");
  }
  return '';
}

