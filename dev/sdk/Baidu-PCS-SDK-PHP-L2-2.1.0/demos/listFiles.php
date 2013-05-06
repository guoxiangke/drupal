<?php

require_once '../libs/BaiduPCS.class.php';
//请根据实际情况更新$access_token与$appName参数
//https://openapi.baidu.com/oauth/2.0/authorize?response_type=token&client_id= ??? &redirect_uri=oob&scope=netdisk
//access_token=3.4cc5353b1139e5e69c8347302d484c69.2592000.1369729715.3892728416-742997
//https://pcs.baidu.com/rest/2.0/pcs/quota?method=info&access_token=3.4cc5353b1139e5e69c8347302d484c69.2592000.1369729715.3892728416-742997
//{"quota":126311464960,"used":66237819,"request_id":3944621475}
$access_token = '3.4cc5353b1139e5e69c8347302d484c69.2592000.1369729715.3892728416-742997';
//应用目录名
$appName = 'liangyou';
//应用根目录
$root_dir = '/apps' . '/' . $appName . '/';

//文件路径，此处列出的是应用根目录
$path = $root_dir;
//根据time排序
$by = 'time';
//升序或降序
$order = 'asc';
//记录区间
$limit = '0-9';

$pcs = new BaiduPCS($access_token);
$result = $pcs->listFiles($path, $by, $order, $limit);
echo $result;
?>
