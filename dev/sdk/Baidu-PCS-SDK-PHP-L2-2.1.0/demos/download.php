<?php

require_once '../libs/BaiduPCS.class.php';
//请根据实际情况更新$access_token与$appName参数
$access_token = '3.4cc5353b1139e5e69c8347302d484c69.2592000.1369729715.3892728416-742997';
//应用目录名
$appName = 'liangyou';
//应用根目录
$root_dir = '/apps' . '/' . $appName . '/';

$fileName = '1.jpg';

//文件路径
$path = $root_dir . $fileName;

$pcs = new BaiduPCS($access_token);

header('Content-Disposition:attachment;filename="' . $fileName . '"');
header('Content-Type:application/octet-stream');
$result = $pcs->download($path);
echo $result;
?>