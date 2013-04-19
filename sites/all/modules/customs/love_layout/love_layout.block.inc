<?php
/**
 * blocks info of custom love.
 */


/**
 * Get relate user info , context will be  used.
 */
function love_block_user_info() {
  global $user;
  //TODO: 
  // if(arg(0) == 'user'){
  //   $account = user_load(arg(1));
  //   $account = $account->uid?$account:$user;
  // }else {
  //   $account = $user;
  // }
  // $account = $account->uid?$account:$user;
  $account = $user;
  $variables['account'] = $account;
  $variables['image_style'] = 'sc250';
  $picture = love_layout_template_preprocess_user_picture($variables);
  if($account->uid)
  $signature = $account->signature?$account->signature:"这家伙很懒，还没写签名....这家伙很懒，还没写签名....这家伙很懒，还没写签名....";
  $variables['account'] = $account;
  // '.l('<em class="icon-setting"></em>完善资料','user/'.$account->uid.'/edit/believes',array('html'=>TRUE,'attributes'=>array('class'=>'link-mt','target'=>"_blank"))).'
  //'.l('<em class="icon-upload"></em>进入相册','user/'.$account->uid.'',array('html'=>TRUE,'attributes'=>array('class'=>'link-mt','target'=>"_blank"))).'
  $focus_num = user_relationships_load(array('rtid' => array(1),'requester_id' => array($account->uid)),array('count'=>TRUE));
  $follow_num = user_relationships_load(array('rtid' => array(1),'requestee_id' => array($account->uid)),array('count'=>TRUE));
  $friends_num = user_relationships_load(array('rtid' => array(2),'approved'=>array(1),'user' => array($account->uid)),array('count'=>TRUE));
  $photo_nodes = love_get_nodes_by_type('photo',$account);
  if(isset( $photo_nodes['node']))
   $photo_nodes = $photo_nodes['node']; 
  $output = '<div class="right-module module-selfInfo" data-log="userIntro">
            '.$picture.'
            <div class="module-selfInfo-inner">
               <div class="module-selfInfo-arrow">
                  <b class="triangle_top"></b>
               </div>
               <div class="module-selfInfo-title">
                  <h2><a class="link-mt" data-log="nickname" target="_blank" href="/601017">'.$account->name.'</a></h2>
               </div>
               <div id="selfInfo" class="module-selfInfo-setting">
                      <div class="user-total">
                      <div class="t-focus"> 
                        <div class="num">'. $focus_num .'</div>
                        <div>关注</div>
                       </div>
                      <div class="t-follow">
                        <div class="num">'. $follow_num .'</div>
                        <div>粉丝</div>
                      </div>
                      <div class="t-nodes">
                        <div class="num">'. count($photo_nodes).'</div>
                        <div>照片</div>
                      </div>
                      <div class="t-friends">
                        <div class="num">'. $friends_num .'</div>
                        <div>熟人</div>
                      </div>
                    </div>
               </div>
            </div>
         </div>';
         
  return $output;//.drupal_render(menu_local_tasks());
}

function love_block_profile_info() {
    //TODO: 
  global $user;
  if(arg(0) == 'user'){
    $account = user_load(arg(1));
    $account = $account->uid?$account:$user;
  }else {
    $account = $user;
  }
  $account = $account->uid?$account:$user;
  // $account = $user;
  $variables['account'] = $account;
  $variables['image_style'] = 'sc250';
  $picture = love_layout_template_preprocess_user_picture($variables);
  if($account->uid)
  $signature = $account->signature?$account->signature:"这家伙很懒，还没写签名....这家伙很懒，还没写签名....这家伙很懒，还没写签名....";

  $profile = profile2_load_by_user($account);

  //dpm($profile);
  
  if(isset($profile['main']->field_name[LANGUAGE_NONE][0]['safe_value']))
  $display_name = $profile['main']->field_name[LANGUAGE_NONE][0]['safe_value'];
  //$display_name = $field_name;
  $field_birthday = $profile['main']->field_birthday[LANGUAGE_NONE][0]['value'];
  $year_now =  date("Y",time());
  $year_born =  date("Y",strtotime($field_birthday));
  $field_height  = $profile['main']->field_height[LANGUAGE_NONE][0]['value'];
  //TODO more....
  if(isset($profile['main']->field_character[LANGUAGE_NONE])){
    foreach ($profile['main']->field_character[LANGUAGE_NONE] as $key => $value) {
      $tids[] = $value['tid'];
    }
    $ts = taxonomy_term_load_multiple($tids);
    $field_character ='';
    foreach ($ts as $key => $term) {
      $field_character .= ' '.$term->name;
    }
  }
  if(isset($profile['believes'])){
    $province = $profile['believes']->field_address[LANGUAGE_NONE][0]['province'];
    $city = $profile['believes']->field_address[LANGUAGE_NONE][0]['city'];
    $county = $profile['believes']->field_address[LANGUAGE_NONE][0]['county'];

    $province = china_address_get_region_name($province);
    $city = china_address_get_region_name($city);
    $county = china_address_get_region_name($county);
    if($province==$city){
      $now_local = $province.$county;
    }else{
      $now_local = $province.$city;
    }
  }

  {//if(isset($profile['main']))
    $province = $profile['main']->field_address[LANGUAGE_NONE][0]['province'];
    $city = $profile['main']->field_address[LANGUAGE_NONE][0]['city'];
    $county = $profile['main']->field_address[LANGUAGE_NONE][0]['county'];

    $province = china_address_get_region_name($province);
    $city = china_address_get_region_name($city);
    $county = china_address_get_region_name($county);
    if($province==$city){
      $home_local = $province.$county;
    }else{
      $home_local = $province.$city;
    }

  }

  $all_fields_on_my_website = field_info_fields();
  if(isset($profile['main']->field_degree[LANGUAGE_NONE][0])){
    $field_degree = $profile['main']->field_degree[LANGUAGE_NONE][0]['value'];
    $degree_value = list_allowed_values($all_fields_on_my_website["field_degree"]);
    $field_degree = $degree_value[$field_degree];
  }
  if(isset($profile['main']->field_links[LANGUAGE_NONE][0])){
    $field_links = $profile['main']->field_links[LANGUAGE_NONE][0]['value'];
    $field_links_title = $profile['main']->field_links[LANGUAGE_NONE][0]['title'];
  }

  $field_marriage = $profile['main']->field_marriage[LANGUAGE_NONE][0]['value'];
  $marriage_value = list_allowed_values($all_fields_on_my_website["field_marriage"]);
  $field_marriage = $marriage_value[$field_marriage];

  if(isset($profile['main']->field_industry[LANGUAGE_NONE][0])){
    $field_industry = $profile['main']->field_industry[LANGUAGE_NONE][0]['value'];
    $industry_value = list_allowed_values($all_fields_on_my_website["field_industry"]);
    $field_industry = $industry_value[$field_industry];
  }
  if(isset($profile['main']->field_salary[LANGUAGE_NONE][0])){
    $field_salary = $profile['main']->field_salary[LANGUAGE_NONE][0]['value'];
    $values = list_allowed_values($all_fields_on_my_website["field_salary"]);
    $field_salary = $values[$field_salary];
  }
  if($account->uid != $user->uid){
   $my_space = FALSE;
   $ur = love_ur_between($account);
   if($ur == 'friends'){//<->
    $ur = user_relationships_load(array('rtid' => array(1),'between' => array($user->uid,$account->uid)));
    $rid = array_keys($ur);$rid =$rid[0];
    $ur_output = '<i class="icon-retweet"></i>互相关注';
    $ur_action =l('<i class="icon-minus"></i>取消关注',"user/{$user->uid}/relationships/$rid/remove",array('html'=>TRUE,'query' => drupal_get_destination(),'attributes'=>array('class' => array('love-icon','love-icon-action','btn-fav', 'mess-trigger'),'title'=>'取消关注')));
   }elseif($ur == 'follow'){//->
      $ur = user_relationships_load(array('rtid' => array(1),'between' => array($user->uid,$account->uid)));
     $rid = array_keys($ur);$rid =$rid[0];
    $ur_output = '<i class="icon-arrow-left"></i>你关注了Ta';

    $ur_action =l('<i class="icon-minus"></i>取消关注',"user/{$user->uid}/relationships/$rid/remove",array('html'=>TRUE,'query' => drupal_get_destination(),'attributes'=>array('class' => array('love-icon','love-icon-action','btn-fav', 'mess-trigger'),'title'=>'取消关注')));
   }elseif($ur == 'follower'){//<-
    $ur_output = '<i class="icon-arrow-right"></i>Ta关注了你';
    $ur_action =l('<i class="icon-plus"></i>关注Ta',"ajax/relationship/$account->uid/request/1",array('html'=>TRUE,'query' => drupal_get_destination(),'attributes'=>array('class' => array('love-icon','love-icon-action','btn-fav', 'mess-trigger'),'title'=>'关注Ta')));
   }else{
    $ur_action =l('<i class="icon-plus"></i>关注Ta',"ajax/relationship/$account->uid/request/1",array('html'=>TRUE,'query' => drupal_get_destination(),'attributes'=>array('class' => array('love-icon','love-icon-action','btn-fav', 'mess-trigger'),'title'=>'关注Ta')));
    $ur_output = '<a href="#" rel="tooltip" data-placement="right" title="暂无关系"><i class="icon-eye-close"></i></a>';
   }
   $privite_msg = '<a class="btn-mess mess-trigger" href="/messages/new/'.$account->uid.'">
           <span class="btn-mess-txt"><i class="icon-envelope"></i>私信</span>
          </a> ';
  }else{
    $ur_action =l('<i class="icon-cogs"></i>完善信息',"user/$account->uid/edit/believes",array('html'=>TRUE,'query' => drupal_get_destination(),'attributes'=>array('class' => array('love-icon','love-icon-action','btn-fav', 'mess-trigger'),'title'=>'关注Ta')));
    $privite_msg = '<a class="btn-mess mess-trigger" href="/messages/recent">
           <span class="btn-mess-txt"><i class="icon-envelope"></i>私信</span>
          </a> ';

    $ur_output = '';//'<a href="javascript:void(0)" rel="tooltip" data-placement="right" title="'.t('My account').'"><i class="icon-eye-open"></i></a>';
    $my_space = TRUE;
    $edit_profile_main_link = l('－－','user/'.$account->uid.'/edit/main',array('attributes'=>array('title'=>'现在完善','rel'=>'tooltip','data-placement'=>'right')));
    $edit_profile_believes_link = l('－－','user/'.$account->uid.'/edit/believes',array('attributes'=>array('title'=>'现在完善','rel'=>'tooltip','data-placement'=>'right')));
    $edit_profile_love_link = l('－－','user/'.$account->uid.'/edit/requirements',array('attributes'=>array('title'=>'现在完善','rel'=>'tooltip','data-placement'=>'right')));
  }

  // online status
  // Count users active within the defined period.
  $online_status = FALSE;
  $interval = REQUEST_TIME - variable_get('user_block_seconds_online', 900);
  $authenticated_count = db_query("SELECT COUNT(DISTINCT s.uid) FROM {sessions} s WHERE s.timestamp >= :timestamp AND s.uid > 0", array(':timestamp' => $interval))->fetchField();
  // Display a list of currently online users.
  if ($authenticated_count) {
    $items = db_query('SELECT u.uid FROM {users} u INNER JOIN {sessions} s ON u.uid = s.uid WHERE u.uid = :uid AND s.timestamp >= :interval AND s.uid > 0', array(':uid'=>$account->uid,':interval' => $interval))->fetchAll();
    if(count($items)){
      $online_status = TRUE;
    };
  }

  //sex
  $field_sex = FALSE;
  $profile = profile2_load_by_user($account);
  if(isset($profile['main']->field_sex[LANGUAGE_NONE]))
  $field_sex = $profile['main']->field_sex[LANGUAGE_NONE][0]['value'];
//icon-female-gray
  //icon-female
  $field_telephone = FALSE;
  if(isset($profile['main']->field_telephone[LANGUAGE_NONE][0])){
    $field_telephone = $profile['main']->field_telephone[LANGUAGE_NONE][0]['value'];
  }
if($my_space){
  if($field_telephone){
    $telphone_links = '<a title="手机已填写" target="_blank" href="#" class="icon-mobile"></a>';
  }else{
    //$edit_profile_main_link
    $telphone_links = l('','user/'.$account->uid.'/edit/main',array('fragment' => 'profile2_main_form_group_contact','attributes'=>array('title'=>'现在完善','rel'=>'tooltip','data-placement'=>'right','class'=>array('icon-mobile-disabled'))));
  }
}else{
  $telphone_links = '';
}
  $variables['account'] = $account;

	$output = '<div id="basicInfoBox" class="profile-basic profile-basic-edit">
         <div class="profile-avatar">'.$picture.'</div>
         <div class="profile-basic-main">
                              <!--div class="profile-elite elite-school js-eliteTag">
                           <div class="profile-elite-school" title="">神的</div>
                           <div class="profile-elite-corp" title="">宝贝</div>
                  <div class="profile-elite-arrow">
            <em class="profile-arrow-income"></em>
            <em class="profile-arrow-school"></em>
            <em class="profile-arrow-corp"></em>
         </div>
      </div-->
            <div class="profile-verify">
                     <em title="'.($online_status?'在线':'离线').'" class="icon-'.($field_sex?'':'fe').'male'.($online_status?'':'-gray').'"></em>
         <span id="profileVerifyName" class="profile-name">'.(isset($display_name)?truncate_utf8($display_name, $max_length=8, $wordsafe = FALSE, $add_ellipsis = TRUE):$account->name).'</span><span class="profile-age">'.($year_now-$year_born).'岁</span>
                                 <a title="身份已认证" target="_blank" href="" class="icon-verify"></a>
         
                           '.$telphone_links.$ur_output.'
                     </div>
            <div class="js-preview">
         <ul class="profileList">
            <li><span class="profile-label">身高：</span>'.$field_height.'cm</li>
             <li><span class="profile-label">性格特点：</span>'.(isset($field_character)?truncate_utf8($field_character, $max_length=8, $wordsafe = FALSE, $add_ellipsis = TRUE):($my_space?$edit_profile_main_link:'<a href="#" rel="tooltip" data-placement="right" title="这家伙很懒，还在空着！">－－</a>')).' </li>
            <li><span class="profile-label">恋爱状态：</span>'.$field_marriage.'</li>
            <li><span class="profile-label">来自：</span>'.(isset($now_local)?$now_local:($my_space?$edit_profile_believes_link:'<a href="#" rel="tooltip" data-placement="right" title="这家伙神秘，没有留下踪迹！">－－</a>')).'</li>
            <li><span class="profile-label">学历：</span>'.(isset($field_degree)?$field_degree:($my_space?$edit_profile_main_link:'<a href="#" rel="tooltip" data-placement="right" title="这家伙很懒，还在空着！">－－</a>')).'</li>
            <li><span class="profile-label">籍贯：</span>'.(isset($home_local)?$home_local:($my_space?$edit_profile_main_link:'<a href="#" rel="tooltip" data-placement="right" title="这家伙很懒，还在空着！">－－</a>')).'<i class="icon-unlock"></i></li>
            <li><span class="profile-label">行业：</span>'.(isset($field_industry)?$field_industry:($my_space?$edit_profile_main_link:'<a href="#" rel="tooltip" data-placement="right" title="这家伙很懒，还在空着！">－－</a>')).'</li>
            <li title=""><span class="profile-label">链接：</span>'.(isset($field_links)?($field_links_title?$field_links_title:'暂不公开'):($my_space?$edit_profile_main_link:'<a href="#" rel="tooltip" data-placement="right" title="这家伙很懒，还在空着！">－－</a>')).'</li>
           
            <!--li><span class="profile-label">月均收入：</span>'.(isset($field_salary)?$field_salary:($my_space?$edit_profile_main_link:'<a href="#" rel="tooltip" data-placement="right" title="这家伙很懒，还在空着！">－－</a>')).'</li-->
         </ul>
      </div>
            <div class="js-edit"></div>
        <div class="profile-relation-btn">
          '.$privite_msg.$ur_action.'
        </div>
        <div class="profile-ur-op">'._love_user_relationships_link($variables).'</div>
               </div>
</div>';
	return $output;
}


function love_block_about_us() {

  $output =  '
      <ul class="about-us">
        <li>1.我们坚信婚姻是神所设立的，是对我们幸福生活的美好设计。</li>
        <li>2.我们认为组建家庭是神对人的一项呼召，在家庭中彰显神的荣耀。</li>
        <li>3.基于圣经，我们认为神所设立的美好婚姻是：一男一女、一夫一妻、一生一世,信与不信原不相配。</li>
        <li>4.我们确信神在创世之先已未我们预备了另一半。</li>
        <li>5.我们相信神对我们的爱永不止息。</li>
      <div>【永不止息】只接受熟人间邮箱邀请注册，请为您邀请的肢体祷告，您在熟人之间互相介绍时，应慎重，严谨，并为之代祷。</div>
      <div>爱是永不止息，是互相激励成长，需要公众见证，公开交往，接受监督的，让更多的肢体在婚恋交友，及组建家庭上彰显神的荣耀</div>
      </ul>';
  return $output;
}

function love_block_weichat_qr() {
  return '永不止息动态早知道<img src="/'.(drupal_get_path('module','love_layout').'/weichat_qr.jpg').'"/>';
}
function love_fm_block() {//<?php echo date("ymd");? >
  return '恋爱季节:我们一起学习如何去爱吧！'//<?php echo 'http://'.$_SERVER['HTTP_HOST'].'/'.drupal_get_path('module','love')? >
          .'
          <div class="player"><embed type="application/x-shockwave-flash" width="208" height="24" src="'.('http://'.$_SERVER['HTTP_HOST'].'/'.drupal_get_path('module','love')).'/player.swf?soundFile=http://liangyou.nissigz.com/media/se/se'.(date("ymd")).'.mp3&amp;bg=0xCDDFF3&amp;leftbg=0x357DCE&amp;lefticon=0xF2F2F2&amp;rightbg=0x357DCE&amp;rightbghover=0x4499EE&amp;righticon=0xF2F2F2&amp;righticonhover=0xFFFFFF&amp;text=0x357DCE&amp;slider=0x357DCE&amp;track=0xFFFFFF&amp;border=0xFFFFFF&amp;loader=0x8EC2F4&amp;autostart=no&amp;loop=no" wmode="transparent" quality="high">
          <div class="fm-on">其他：
<a href="http://audio.liangyou.net/download.php?t=2&c=bc&f=bc'.(date("ymd")).'.wma" id="book-radio">书香园地</a>
<strong>'.l('灵命日粮','ybreads').'</strong>
<a href="http://audio.liangyou.net/download.php?t=2&c=bf&f=bf'.(date("ymd")).'.wma" id="radio-home">幸福满家园</a>  </div>
</div>';
}

function love_signature_block() {
  global $user;
  $account = $user;
  if(arg(0) == 'user' && is_numeric(arg(1))){
    $account = user_load(arg(1));
  }
  $edit_link = '';
  if($account->uid == $user->uid || user_access('administer users') ){//#edit-signature-settings
    $edit_link = '<div id="edit-love-signature">'.l('<i class="icon-pencil"></i>'.t('edit'),"user/$account->uid/edit",array('fragment' => 'edit-signature-settings','html'=>TRUE)).'</div>';
  }
  if(isset($account->signature) && strlen($account->signature)) {
    $signature = $account->signature;
  }else {
    $signature ='这家伙或许很懒，或许是个空心菜，这么好展示自我得机会都无语^_^';
  }//truncate_utf8($signature, $max_length=255, $wordsafe = FALSE, $add_ellipsis = TRUE)
  return '<div id="love-signature">'.$signature.'</div>'.$edit_link;
}

function love_user_timeline() {
  drupal_add_css(drupal_get_path('module', 'love_layout').'/jQueryTimelinr_0952/css/style_v.css');
  drupal_add_js(drupal_get_path('module', 'love_layout').'/jQueryTimelinr_0952/js/jquery.timelinr-0.9.52.js');

  global $user;
  $account = $user;
  if(arg(0) == 'user' && is_numeric(arg(1))){
    $account = user_load(arg(1));
  }
  $profile = profile2_load_by_user($account);

  //dpm($profile);
  
  if(isset($profile['main']->field_name[LANGUAGE_NONE][0]['safe_value']))
  $display_name = $profile['main']->field_name[LANGUAGE_NONE][0]['safe_value'];
  //$display_name = $field_name;
  $field_birthday = $profile['main']->field_birthday[LANGUAGE_NONE][0]['value'];
  $year_now =  date("Y",time());
  $year_born =  date("Y",strtotime($field_birthday));
  $field_height  = $profile['main']->field_height[LANGUAGE_NONE][0]['value'];
  //TODO more....
  $dates[$field_birthday] = $field_birthday;
  $photos = love_get_nodes_by_type($type='photo',$account);
  //add default pic of timeline.
  $photos = $photos?$photos:array('node'=>array('107'));
  $photos = node_load_multiple(array_keys($photos['node']));

  $dates_li = '';
  $issues_li = '';
  // dpm($photos);
  foreach ($photos as $key => $node) {
    if(!isset($node->field_photo[LANGUAGE_NONE])) continue;
     $dates_li .= '<li><a href="#'.$node->changed.'">'.date('n-j',$node->changed).'</a><span>'.date('Y',$node->changed).'</span></li>';
     $variables = array(
      'path' => $node->field_photo[LANGUAGE_NONE][0]['uri'], 
      'alt' => 'Test alt',
      'title' => 'Test title',
      'attributes' => array('class' => 'some-img', 'id' => 'my-img'),
      );
     $style = 's550';
     $img = theme('image_style', array('style_name' => $style, 'path' => $node->field_photo[LANGUAGE_NONE][0]['uri']));//theme('image', $variables);
     $issues_li .= '<li id="'.$node->changed.'">
        '.$img.'
        <p>'.$node->body[LANGUAGE_NONE][0]['value'].'</p>
      </li>';
  }
  $dates_li .= '<li><a href="#'.strtotime($field_birthday).'">'.date('n-j',strtotime($field_birthday)).'</a><span>'.date('Y',strtotime($field_birthday)).'</span></li>';

  $issues_li .= '<li id="'.strtotime($field_birthday).'">
        <img src="/'.drupal_get_path('module','love_layout').'/birth-default.jpg" width="256" height="256" />

        <h1>'.date('Y-m-d',strtotime($field_birthday)).'</h1>
        <p>'.date('Y-m-d',strtotime($field_birthday)).'我出生啦！</p>
      </li>';

  $output = '<script>
  (function ($) {
    $(function(){
      $().timelinr({
        orientation:  "vertical",
        issuesSpeed:  300,
        datesSpeed:   100,
        arrowKeys:    "true",
        startAt:    3
      })
    });
})(jQuery);
</script>
  <div id="timeline" class="row-fluid">
    <ul id="dates" class="span3">
    '.$dates_li.'
    </ul>
    <ul id="issues" class="span9">
    '.$issues_li.'
    </ul>
    
    <a href="#" id="next">+</a>
    <a href="#" id="prev">-</a>
  </div>';
  // <div id="grad_top"></div>
  //   <div id="grad_bottom"></div>
  return '镌刻您的真爱之旅<br/>时间就像一条长长的线，空间就像一个大大的圆，我们的故事发生在它们中间～'.$output;
}
?>