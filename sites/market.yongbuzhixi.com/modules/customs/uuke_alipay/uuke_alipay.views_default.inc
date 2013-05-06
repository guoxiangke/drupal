<?php
/**
 * Implements hook_views_default_views().
 */
function uuke_alipay_views_default_views() {
 
	// exported view goes here
{
	$view = new view;
	$view->name = 'uuke_order_list';
	$view->description = '';
	$view->tag = 'default';
	$view->base_table = 'node';
	$view->human_name = 'uuke Order LIst';
	$view->core = 7;
	$view->api_version = '3.0';
	$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

	/* Display: Master */
	$handler = $view->new_display('default', 'Master', 'default');
	$handler->display->display_options['title'] = 'All Order LIst';
	$handler->display->display_options['access']['type'] = 'perm';
	$handler->display->display_options['access']['perm'] = 'access my orders';
	$handler->display->display_options['cache']['type'] = 'none';
	$handler->display->display_options['query']['type'] = 'views_query';
	$handler->display->display_options['query']['options']['query_comment'] = FALSE;
	$handler->display->display_options['exposed_form']['type'] = 'basic';
	$handler->display->display_options['exposed_form']['options']['reset_button_label'] = '重置';
	$handler->display->display_options['pager']['type'] = 'full';
	$handler->display->display_options['pager']['options']['items_per_page'] = '10';
	$handler->display->display_options['style_plugin'] = 'table';
	/* No results behavior: Global: Text area */
	$handler->display->display_options['empty']['area']['id'] = 'area';
	$handler->display->display_options['empty']['area']['table'] = 'views';
	$handler->display->display_options['empty']['area']['field'] = 'area';
	$handler->display->display_options['empty']['area']['empty'] = TRUE;
	$handler->display->display_options['empty']['area']['content'] = '暂无数据';
	$handler->display->display_options['empty']['area']['format'] = 'filtered_html';
	/* Relationship: Entity Reference: Referenced Entity */
	$handler->display->display_options['relationships']['field_uuke_alipay_product_nid_target_id']['id'] = 'field_uuke_alipay_product_nid_target_id';
	$handler->display->display_options['relationships']['field_uuke_alipay_product_nid_target_id']['table'] = 'field_data_field_uuke_alipay_product_nid';
	$handler->display->display_options['relationships']['field_uuke_alipay_product_nid_target_id']['field'] = 'field_uuke_alipay_product_nid_target_id';
	$handler->display->display_options['relationships']['field_uuke_alipay_product_nid_target_id']['required'] = TRUE;
	/* Relationship: 内容: 作者 */
	$handler->display->display_options['relationships']['uid']['id'] = 'uid';
	$handler->display->display_options['relationships']['uid']['table'] = 'node';
	$handler->display->display_options['relationships']['uid']['field'] = 'uid';
	/* 字段: 内容: 标题 */
	$handler->display->display_options['fields']['title']['id'] = 'title';
	$handler->display->display_options['fields']['title']['table'] = 'node';
	$handler->display->display_options['fields']['title']['field'] = 'title';
	$handler->display->display_options['fields']['title']['label'] = '订单号';
	$handler->display->display_options['fields']['title']['alter']['alter_text'] = 0;
	$handler->display->display_options['fields']['title']['alter']['make_link'] = 0;
	$handler->display->display_options['fields']['title']['alter']['absolute'] = 0;
	$handler->display->display_options['fields']['title']['alter']['external'] = 0;
	$handler->display->display_options['fields']['title']['alter']['replace_spaces'] = 0;
	$handler->display->display_options['fields']['title']['alter']['trim_whitespace'] = 0;
	$handler->display->display_options['fields']['title']['alter']['nl2br'] = 0;
	$handler->display->display_options['fields']['title']['alter']['word_boundary'] = 0;
	$handler->display->display_options['fields']['title']['alter']['ellipsis'] = 0;
	$handler->display->display_options['fields']['title']['alter']['strip_tags'] = 0;
	$handler->display->display_options['fields']['title']['alter']['trim'] = 0;
	$handler->display->display_options['fields']['title']['alter']['html'] = 0;
	$handler->display->display_options['fields']['title']['element_label_colon'] = 1;
	$handler->display->display_options['fields']['title']['element_default_classes'] = 1;
	$handler->display->display_options['fields']['title']['hide_empty'] = 0;
	$handler->display->display_options['fields']['title']['empty_zero'] = 0;
	$handler->display->display_options['fields']['title']['hide_alter_empty'] = 1;
	$handler->display->display_options['fields']['title']['link_to_node'] = 0;
	/* 字段: 内容: Product Nid */
	$handler->display->display_options['fields']['field_uuke_alipay_product_nid']['id'] = 'field_uuke_alipay_product_nid';
	$handler->display->display_options['fields']['field_uuke_alipay_product_nid']['table'] = 'field_data_field_uuke_alipay_product_nid';
	$handler->display->display_options['fields']['field_uuke_alipay_product_nid']['field'] = 'field_uuke_alipay_product_nid';
	$handler->display->display_options['fields']['field_uuke_alipay_product_nid']['label'] = 'Product';
	$handler->display->display_options['fields']['field_uuke_alipay_product_nid']['alter']['alter_text'] = 0;
	$handler->display->display_options['fields']['field_uuke_alipay_product_nid']['alter']['make_link'] = 0;
	$handler->display->display_options['fields']['field_uuke_alipay_product_nid']['alter']['absolute'] = 0;
	$handler->display->display_options['fields']['field_uuke_alipay_product_nid']['alter']['external'] = 0;
	$handler->display->display_options['fields']['field_uuke_alipay_product_nid']['alter']['replace_spaces'] = 0;
	$handler->display->display_options['fields']['field_uuke_alipay_product_nid']['alter']['trim_whitespace'] = 0;
	$handler->display->display_options['fields']['field_uuke_alipay_product_nid']['alter']['nl2br'] = 0;
	$handler->display->display_options['fields']['field_uuke_alipay_product_nid']['alter']['word_boundary'] = 1;
	$handler->display->display_options['fields']['field_uuke_alipay_product_nid']['alter']['ellipsis'] = 1;
	$handler->display->display_options['fields']['field_uuke_alipay_product_nid']['alter']['strip_tags'] = 0;
	$handler->display->display_options['fields']['field_uuke_alipay_product_nid']['alter']['trim'] = 0;
	$handler->display->display_options['fields']['field_uuke_alipay_product_nid']['alter']['html'] = 0;
	$handler->display->display_options['fields']['field_uuke_alipay_product_nid']['element_label_colon'] = 1;
	$handler->display->display_options['fields']['field_uuke_alipay_product_nid']['element_default_classes'] = 1;
	$handler->display->display_options['fields']['field_uuke_alipay_product_nid']['hide_empty'] = 0;
	$handler->display->display_options['fields']['field_uuke_alipay_product_nid']['empty_zero'] = 0;
	$handler->display->display_options['fields']['field_uuke_alipay_product_nid']['hide_alter_empty'] = 1;
	$handler->display->display_options['fields']['field_uuke_alipay_product_nid']['settings'] = array(
	  'link' => 1,
	);
	$handler->display->display_options['fields']['field_uuke_alipay_product_nid']['field_api_classes'] = 0;
	/* 字段: 内容: 商品价格 */
	$handler->display->display_options['fields']['field_uuke_alipay_product_price']['id'] = 'field_uuke_alipay_product_price';
	$handler->display->display_options['fields']['field_uuke_alipay_product_price']['table'] = 'field_data_field_uuke_alipay_product_price';
	$handler->display->display_options['fields']['field_uuke_alipay_product_price']['field'] = 'field_uuke_alipay_product_price';
	$handler->display->display_options['fields']['field_uuke_alipay_product_price']['settings'] = array(
	  'thousand_separator' => ' ',
	  'decimal_separator' => '.',
	  'scale' => '2',
	  'prefix_suffix' => 1,
	);
	/* 字段: 内容: Updated date */
	$handler->display->display_options['fields']['changed']['id'] = 'changed';
	$handler->display->display_options['fields']['changed']['table'] = 'node';
	$handler->display->display_options['fields']['changed']['field'] = 'changed';
	$handler->display->display_options['fields']['changed']['date_format'] = 'custom';
	$handler->display->display_options['fields']['changed']['custom_date_format'] = 'Y-m-d h:i:s';
	/* 字段: 内容: 订单状态 */
	$handler->display->display_options['fields']['field_uuke_alipay_trade_status']['id'] = 'field_uuke_alipay_trade_status';
	$handler->display->display_options['fields']['field_uuke_alipay_trade_status']['table'] = 'field_data_field_uuke_alipay_trade_status';
	$handler->display->display_options['fields']['field_uuke_alipay_trade_status']['field'] = 'field_uuke_alipay_trade_status';
	/* 字段: 用户: 名称 */
	$handler->display->display_options['fields']['name']['id'] = 'name';
	$handler->display->display_options['fields']['name']['table'] = 'users';
	$handler->display->display_options['fields']['name']['field'] = 'name';
	$handler->display->display_options['fields']['name']['relationship'] = 'uid';
	$handler->display->display_options['fields']['name']['label'] = 'User';
	$handler->display->display_options['fields']['name']['alter']['alter_text'] = 0;
	$handler->display->display_options['fields']['name']['alter']['make_link'] = 0;
	$handler->display->display_options['fields']['name']['alter']['absolute'] = 0;
	$handler->display->display_options['fields']['name']['alter']['external'] = 0;
	$handler->display->display_options['fields']['name']['alter']['replace_spaces'] = 0;
	$handler->display->display_options['fields']['name']['alter']['trim_whitespace'] = 0;
	$handler->display->display_options['fields']['name']['alter']['nl2br'] = 0;
	$handler->display->display_options['fields']['name']['alter']['word_boundary'] = 1;
	$handler->display->display_options['fields']['name']['alter']['ellipsis'] = 1;
	$handler->display->display_options['fields']['name']['alter']['more_link'] = 0;
	$handler->display->display_options['fields']['name']['alter']['strip_tags'] = 0;
	$handler->display->display_options['fields']['name']['alter']['trim'] = 0;
	$handler->display->display_options['fields']['name']['alter']['html'] = 0;
	$handler->display->display_options['fields']['name']['element_label_colon'] = 1;
	$handler->display->display_options['fields']['name']['element_default_classes'] = 1;
	$handler->display->display_options['fields']['name']['hide_empty'] = 0;
	$handler->display->display_options['fields']['name']['empty_zero'] = 0;
	$handler->display->display_options['fields']['name']['hide_alter_empty'] = 1;
	$handler->display->display_options['fields']['name']['link_to_user'] = 1;
	$handler->display->display_options['fields']['name']['overwrite_anonymous'] = 0;
	$handler->display->display_options['fields']['name']['format_username'] = 1;
	/* Sort criterion: 内容: Post date */
	$handler->display->display_options['sorts']['created']['id'] = 'created';
	$handler->display->display_options['sorts']['created']['table'] = 'node';
	$handler->display->display_options['sorts']['created']['field'] = 'created';
	$handler->display->display_options['sorts']['created']['order'] = 'DESC';
	/* Filter criterion: 内容: 已发表 */
	$handler->display->display_options['filters']['status']['id'] = 'status';
	$handler->display->display_options['filters']['status']['table'] = 'node';
	$handler->display->display_options['filters']['status']['field'] = 'status';
	$handler->display->display_options['filters']['status']['value'] = 1;
	$handler->display->display_options['filters']['status']['group'] = 1;
	$handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
	/* Filter criterion: 内容: 类型 */
	$handler->display->display_options['filters']['type']['id'] = 'type';
	$handler->display->display_options['filters']['type']['table'] = 'node';
	$handler->display->display_options['filters']['type']['field'] = 'type';
	$handler->display->display_options['filters']['type']['value'] = array(
	  'uuke_alipay_order' => 'uuke_alipay_order',
	);

	/* Display: All order list page */
	$handler = $view->new_display('page', 'All order list page', 'all_order_list');
	$handler->display->display_options['defaults']['access'] = FALSE;
	$handler->display->display_options['access']['type'] = 'perm';
	$handler->display->display_options['access']['perm'] = 'access all orders';
	$handler->display->display_options['defaults']['fields'] = FALSE;
	/* 字段: 内容: 标题 */
	$handler->display->display_options['fields']['title']['id'] = 'title';
	$handler->display->display_options['fields']['title']['table'] = 'node';
	$handler->display->display_options['fields']['title']['field'] = 'title';
	$handler->display->display_options['fields']['title']['label'] = '订单号';
	$handler->display->display_options['fields']['title']['alter']['alter_text'] = 0;
	$handler->display->display_options['fields']['title']['alter']['make_link'] = 0;
	$handler->display->display_options['fields']['title']['alter']['absolute'] = 0;
	$handler->display->display_options['fields']['title']['alter']['external'] = 0;
	$handler->display->display_options['fields']['title']['alter']['replace_spaces'] = 0;
	$handler->display->display_options['fields']['title']['alter']['trim_whitespace'] = 0;
	$handler->display->display_options['fields']['title']['alter']['nl2br'] = 0;
	$handler->display->display_options['fields']['title']['alter']['word_boundary'] = 0;
	$handler->display->display_options['fields']['title']['alter']['ellipsis'] = 0;
	$handler->display->display_options['fields']['title']['alter']['strip_tags'] = 0;
	$handler->display->display_options['fields']['title']['alter']['trim'] = 0;
	$handler->display->display_options['fields']['title']['alter']['html'] = 0;
	$handler->display->display_options['fields']['title']['element_label_colon'] = 1;
	$handler->display->display_options['fields']['title']['element_default_classes'] = 1;
	$handler->display->display_options['fields']['title']['hide_empty'] = 0;
	$handler->display->display_options['fields']['title']['empty_zero'] = 0;
	$handler->display->display_options['fields']['title']['hide_alter_empty'] = 1;
	$handler->display->display_options['fields']['title']['link_to_node'] = 0;
	/* 字段: 内容: Product Nid */
	$handler->display->display_options['fields']['field_uuke_alipay_product_nid']['id'] = 'field_uuke_alipay_product_nid';
	$handler->display->display_options['fields']['field_uuke_alipay_product_nid']['table'] = 'field_data_field_uuke_alipay_product_nid';
	$handler->display->display_options['fields']['field_uuke_alipay_product_nid']['field'] = 'field_uuke_alipay_product_nid';
	$handler->display->display_options['fields']['field_uuke_alipay_product_nid']['label'] = 'Product';
	$handler->display->display_options['fields']['field_uuke_alipay_product_nid']['alter']['alter_text'] = 0;
	$handler->display->display_options['fields']['field_uuke_alipay_product_nid']['alter']['make_link'] = 0;
	$handler->display->display_options['fields']['field_uuke_alipay_product_nid']['alter']['absolute'] = 0;
	$handler->display->display_options['fields']['field_uuke_alipay_product_nid']['alter']['external'] = 0;
	$handler->display->display_options['fields']['field_uuke_alipay_product_nid']['alter']['replace_spaces'] = 0;
	$handler->display->display_options['fields']['field_uuke_alipay_product_nid']['alter']['trim_whitespace'] = 0;
	$handler->display->display_options['fields']['field_uuke_alipay_product_nid']['alter']['nl2br'] = 0;
	$handler->display->display_options['fields']['field_uuke_alipay_product_nid']['alter']['word_boundary'] = 1;
	$handler->display->display_options['fields']['field_uuke_alipay_product_nid']['alter']['ellipsis'] = 1;
	$handler->display->display_options['fields']['field_uuke_alipay_product_nid']['alter']['strip_tags'] = 0;
	$handler->display->display_options['fields']['field_uuke_alipay_product_nid']['alter']['trim'] = 0;
	$handler->display->display_options['fields']['field_uuke_alipay_product_nid']['alter']['html'] = 0;
	$handler->display->display_options['fields']['field_uuke_alipay_product_nid']['element_label_colon'] = 1;
	$handler->display->display_options['fields']['field_uuke_alipay_product_nid']['element_default_classes'] = 1;
	$handler->display->display_options['fields']['field_uuke_alipay_product_nid']['hide_empty'] = 0;
	$handler->display->display_options['fields']['field_uuke_alipay_product_nid']['empty_zero'] = 0;
	$handler->display->display_options['fields']['field_uuke_alipay_product_nid']['hide_alter_empty'] = 1;
	$handler->display->display_options['fields']['field_uuke_alipay_product_nid']['settings'] = array(
	  'link' => 1,
	);
	$handler->display->display_options['fields']['field_uuke_alipay_product_nid']['field_api_classes'] = 0;
	/* 字段: 用户: 名称 */
	$handler->display->display_options['fields']['name']['id'] = 'name';
	$handler->display->display_options['fields']['name']['table'] = 'users';
	$handler->display->display_options['fields']['name']['field'] = 'name';
	$handler->display->display_options['fields']['name']['relationship'] = 'uid';
	$handler->display->display_options['fields']['name']['label'] = 'User';
	$handler->display->display_options['fields']['name']['alter']['alter_text'] = 0;
	$handler->display->display_options['fields']['name']['alter']['make_link'] = 0;
	$handler->display->display_options['fields']['name']['alter']['absolute'] = 0;
	$handler->display->display_options['fields']['name']['alter']['external'] = 0;
	$handler->display->display_options['fields']['name']['alter']['replace_spaces'] = 0;
	$handler->display->display_options['fields']['name']['alter']['trim_whitespace'] = 0;
	$handler->display->display_options['fields']['name']['alter']['nl2br'] = 0;
	$handler->display->display_options['fields']['name']['alter']['word_boundary'] = 1;
	$handler->display->display_options['fields']['name']['alter']['ellipsis'] = 1;
	$handler->display->display_options['fields']['name']['alter']['more_link'] = 0;
	$handler->display->display_options['fields']['name']['alter']['strip_tags'] = 0;
	$handler->display->display_options['fields']['name']['alter']['trim'] = 0;
	$handler->display->display_options['fields']['name']['alter']['html'] = 0;
	$handler->display->display_options['fields']['name']['element_label_colon'] = 1;
	$handler->display->display_options['fields']['name']['element_default_classes'] = 1;
	$handler->display->display_options['fields']['name']['hide_empty'] = 0;
	$handler->display->display_options['fields']['name']['empty_zero'] = 0;
	$handler->display->display_options['fields']['name']['hide_alter_empty'] = 0;
	$handler->display->display_options['fields']['name']['link_to_user'] = 1;
	$handler->display->display_options['fields']['name']['overwrite_anonymous'] = 0;
	$handler->display->display_options['fields']['name']['format_username'] = 1;
	/* 字段: 内容: 商品价格 */
	$handler->display->display_options['fields']['field_uuke_alipay_product_price']['id'] = 'field_uuke_alipay_product_price';
	$handler->display->display_options['fields']['field_uuke_alipay_product_price']['table'] = 'field_data_field_uuke_alipay_product_price';
	$handler->display->display_options['fields']['field_uuke_alipay_product_price']['field'] = 'field_uuke_alipay_product_price';
	$handler->display->display_options['fields']['field_uuke_alipay_product_price']['settings'] = array(
	  'thousand_separator' => ' ',
	  'decimal_separator' => '.',
	  'scale' => '2',
	  'prefix_suffix' => 1,
	);
	/* 字段: 内容: Updated date */
	$handler->display->display_options['fields']['changed']['id'] = 'changed';
	$handler->display->display_options['fields']['changed']['table'] = 'node';
	$handler->display->display_options['fields']['changed']['field'] = 'changed';
	$handler->display->display_options['fields']['changed']['date_format'] = 'custom';
	$handler->display->display_options['fields']['changed']['custom_date_format'] = 'Y-m-d h:i:s';
	/* 字段: 内容: 订单状态 */
	$handler->display->display_options['fields']['field_uuke_alipay_trade_status']['id'] = 'field_uuke_alipay_trade_status';
	$handler->display->display_options['fields']['field_uuke_alipay_trade_status']['table'] = 'field_data_field_uuke_alipay_trade_status';
	$handler->display->display_options['fields']['field_uuke_alipay_trade_status']['field'] = 'field_uuke_alipay_trade_status';
	$handler->display->display_options['path'] = 'order-list';
	$handler->display->display_options['menu']['type'] = 'normal';
	$handler->display->display_options['menu']['title'] = 'All Order LIst';
	$handler->display->display_options['menu']['weight'] = '0';
	$handler->display->display_options['menu']['name'] = 'main-menu';
	$handler->display->display_options['menu']['context'] = 0;

	/* Display: My order list page */
	$handler = $view->new_display('page', 'My order list page', 'my_order_list');
	$handler->display->display_options['defaults']['title'] = FALSE;
	$handler->display->display_options['title'] = 'My Order LIst';
	$handler->display->display_options['defaults']['fields'] = FALSE;
	/* 字段: 内容: 标题 */
	$handler->display->display_options['fields']['title']['id'] = 'title';
	$handler->display->display_options['fields']['title']['table'] = 'node';
	$handler->display->display_options['fields']['title']['field'] = 'title';
	$handler->display->display_options['fields']['title']['label'] = '订单号';
	$handler->display->display_options['fields']['title']['alter']['alter_text'] = 0;
	$handler->display->display_options['fields']['title']['alter']['make_link'] = 0;
	$handler->display->display_options['fields']['title']['alter']['absolute'] = 0;
	$handler->display->display_options['fields']['title']['alter']['external'] = 0;
	$handler->display->display_options['fields']['title']['alter']['replace_spaces'] = 0;
	$handler->display->display_options['fields']['title']['alter']['trim_whitespace'] = 0;
	$handler->display->display_options['fields']['title']['alter']['nl2br'] = 0;
	$handler->display->display_options['fields']['title']['alter']['word_boundary'] = 0;
	$handler->display->display_options['fields']['title']['alter']['ellipsis'] = 0;
	$handler->display->display_options['fields']['title']['alter']['strip_tags'] = 0;
	$handler->display->display_options['fields']['title']['alter']['trim'] = 0;
	$handler->display->display_options['fields']['title']['alter']['html'] = 0;
	$handler->display->display_options['fields']['title']['element_label_colon'] = 1;
	$handler->display->display_options['fields']['title']['element_default_classes'] = 1;
	$handler->display->display_options['fields']['title']['hide_empty'] = 0;
	$handler->display->display_options['fields']['title']['empty_zero'] = 0;
	$handler->display->display_options['fields']['title']['hide_alter_empty'] = 1;
	$handler->display->display_options['fields']['title']['link_to_node'] = 0;
	/* 字段: 内容: Product Nid */
	$handler->display->display_options['fields']['field_uuke_alipay_product_nid']['id'] = 'field_uuke_alipay_product_nid';
	$handler->display->display_options['fields']['field_uuke_alipay_product_nid']['table'] = 'field_data_field_uuke_alipay_product_nid';
	$handler->display->display_options['fields']['field_uuke_alipay_product_nid']['field'] = 'field_uuke_alipay_product_nid';
	$handler->display->display_options['fields']['field_uuke_alipay_product_nid']['label'] = 'Product';
	$handler->display->display_options['fields']['field_uuke_alipay_product_nid']['alter']['alter_text'] = 0;
	$handler->display->display_options['fields']['field_uuke_alipay_product_nid']['alter']['make_link'] = 0;
	$handler->display->display_options['fields']['field_uuke_alipay_product_nid']['alter']['absolute'] = 0;
	$handler->display->display_options['fields']['field_uuke_alipay_product_nid']['alter']['external'] = 0;
	$handler->display->display_options['fields']['field_uuke_alipay_product_nid']['alter']['replace_spaces'] = 0;
	$handler->display->display_options['fields']['field_uuke_alipay_product_nid']['alter']['trim_whitespace'] = 0;
	$handler->display->display_options['fields']['field_uuke_alipay_product_nid']['alter']['nl2br'] = 0;
	$handler->display->display_options['fields']['field_uuke_alipay_product_nid']['alter']['word_boundary'] = 1;
	$handler->display->display_options['fields']['field_uuke_alipay_product_nid']['alter']['ellipsis'] = 1;
	$handler->display->display_options['fields']['field_uuke_alipay_product_nid']['alter']['strip_tags'] = 0;
	$handler->display->display_options['fields']['field_uuke_alipay_product_nid']['alter']['trim'] = 0;
	$handler->display->display_options['fields']['field_uuke_alipay_product_nid']['alter']['html'] = 0;
	$handler->display->display_options['fields']['field_uuke_alipay_product_nid']['element_label_colon'] = 1;
	$handler->display->display_options['fields']['field_uuke_alipay_product_nid']['element_default_classes'] = 1;
	$handler->display->display_options['fields']['field_uuke_alipay_product_nid']['hide_empty'] = 0;
	$handler->display->display_options['fields']['field_uuke_alipay_product_nid']['empty_zero'] = 0;
	$handler->display->display_options['fields']['field_uuke_alipay_product_nid']['hide_alter_empty'] = 1;
	$handler->display->display_options['fields']['field_uuke_alipay_product_nid']['settings'] = array(
	  'link' => 1,
	);
	$handler->display->display_options['fields']['field_uuke_alipay_product_nid']['field_api_classes'] = 0;
	/* 字段: 内容: 商品价格 */
	$handler->display->display_options['fields']['field_uuke_alipay_product_price']['id'] = 'field_uuke_alipay_product_price';
	$handler->display->display_options['fields']['field_uuke_alipay_product_price']['table'] = 'field_data_field_uuke_alipay_product_price';
	$handler->display->display_options['fields']['field_uuke_alipay_product_price']['field'] = 'field_uuke_alipay_product_price';
	$handler->display->display_options['fields']['field_uuke_alipay_product_price']['settings'] = array(
	  'thousand_separator' => ' ',
	  'decimal_separator' => '.',
	  'scale' => '2',
	  'prefix_suffix' => 1,
	);
	/* 字段: 内容: Updated date */
	$handler->display->display_options['fields']['changed']['id'] = 'changed';
	$handler->display->display_options['fields']['changed']['table'] = 'node';
	$handler->display->display_options['fields']['changed']['field'] = 'changed';
	$handler->display->display_options['fields']['changed']['date_format'] = 'custom';
	$handler->display->display_options['fields']['changed']['custom_date_format'] = 'Y-m-d h:i:s';
	/* 字段: 内容: 订单状态 */
	$handler->display->display_options['fields']['field_uuke_alipay_trade_status']['id'] = 'field_uuke_alipay_trade_status';
	$handler->display->display_options['fields']['field_uuke_alipay_trade_status']['table'] = 'field_data_field_uuke_alipay_trade_status';
	$handler->display->display_options['fields']['field_uuke_alipay_trade_status']['field'] = 'field_uuke_alipay_trade_status';
	$handler->display->display_options['defaults']['filters'] = FALSE;
	/* Filter criterion: 内容: 已发表 */
	$handler->display->display_options['filters']['status']['id'] = 'status';
	$handler->display->display_options['filters']['status']['table'] = 'node';
	$handler->display->display_options['filters']['status']['field'] = 'status';
	$handler->display->display_options['filters']['status']['value'] = 1;
	$handler->display->display_options['filters']['status']['group'] = 1;
	$handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
	/* Filter criterion: 内容: 类型 */
	$handler->display->display_options['filters']['type']['id'] = 'type';
	$handler->display->display_options['filters']['type']['table'] = 'node';
	$handler->display->display_options['filters']['type']['field'] = 'type';
	$handler->display->display_options['filters']['type']['value'] = array(
	  'uuke_alipay_order' => 'uuke_alipay_order',
	);
	/* Filter criterion: 用户: Current */
	$handler->display->display_options['filters']['uid_current']['id'] = 'uid_current';
	$handler->display->display_options['filters']['uid_current']['table'] = 'users';
	$handler->display->display_options['filters']['uid_current']['field'] = 'uid_current';
	$handler->display->display_options['filters']['uid_current']['relationship'] = 'uid';
	$handler->display->display_options['filters']['uid_current']['value'] = '1';
	$handler->display->display_options['path'] = 'my-order-list';
	$handler->display->display_options['menu']['type'] = 'normal';
	$handler->display->display_options['menu']['title'] = 'My Order List';
	$handler->display->display_options['menu']['weight'] = '0';
	$handler->display->display_options['menu']['name'] = 'main-menu';
	$handler->display->display_options['menu']['context'] = 0;

	/* Display: Waiting paid */
	$handler = $view->new_display('page', 'Waiting paid', 'my_waiting_paid_order_list');
	$handler->display->display_options['defaults']['title'] = FALSE;
	$handler->display->display_options['title'] = 'My Waiting paid Order List';
	$handler->display->display_options['defaults']['fields'] = FALSE;
	/* 字段: 内容: 标题 */
	$handler->display->display_options['fields']['title']['id'] = 'title';
	$handler->display->display_options['fields']['title']['table'] = 'node';
	$handler->display->display_options['fields']['title']['field'] = 'title';
	$handler->display->display_options['fields']['title']['label'] = '订单号';
	$handler->display->display_options['fields']['title']['alter']['alter_text'] = 0;
	$handler->display->display_options['fields']['title']['alter']['make_link'] = 0;
	$handler->display->display_options['fields']['title']['alter']['absolute'] = 0;
	$handler->display->display_options['fields']['title']['alter']['external'] = 0;
	$handler->display->display_options['fields']['title']['alter']['replace_spaces'] = 0;
	$handler->display->display_options['fields']['title']['alter']['trim_whitespace'] = 0;
	$handler->display->display_options['fields']['title']['alter']['nl2br'] = 0;
	$handler->display->display_options['fields']['title']['alter']['word_boundary'] = 0;
	$handler->display->display_options['fields']['title']['alter']['ellipsis'] = 0;
	$handler->display->display_options['fields']['title']['alter']['strip_tags'] = 0;
	$handler->display->display_options['fields']['title']['alter']['trim'] = 0;
	$handler->display->display_options['fields']['title']['alter']['html'] = 0;
	$handler->display->display_options['fields']['title']['element_label_colon'] = 1;
	$handler->display->display_options['fields']['title']['element_default_classes'] = 1;
	$handler->display->display_options['fields']['title']['hide_empty'] = 0;
	$handler->display->display_options['fields']['title']['empty_zero'] = 0;
	$handler->display->display_options['fields']['title']['hide_alter_empty'] = 1;
	$handler->display->display_options['fields']['title']['link_to_node'] = 0;
	/* 字段: 内容: Product Nid */
	$handler->display->display_options['fields']['field_uuke_alipay_product_nid']['id'] = 'field_uuke_alipay_product_nid';
	$handler->display->display_options['fields']['field_uuke_alipay_product_nid']['table'] = 'field_data_field_uuke_alipay_product_nid';
	$handler->display->display_options['fields']['field_uuke_alipay_product_nid']['field'] = 'field_uuke_alipay_product_nid';
	$handler->display->display_options['fields']['field_uuke_alipay_product_nid']['label'] = 'Product';
	$handler->display->display_options['fields']['field_uuke_alipay_product_nid']['alter']['alter_text'] = 0;
	$handler->display->display_options['fields']['field_uuke_alipay_product_nid']['alter']['make_link'] = 0;
	$handler->display->display_options['fields']['field_uuke_alipay_product_nid']['alter']['absolute'] = 0;
	$handler->display->display_options['fields']['field_uuke_alipay_product_nid']['alter']['external'] = 0;
	$handler->display->display_options['fields']['field_uuke_alipay_product_nid']['alter']['replace_spaces'] = 0;
	$handler->display->display_options['fields']['field_uuke_alipay_product_nid']['alter']['trim_whitespace'] = 0;
	$handler->display->display_options['fields']['field_uuke_alipay_product_nid']['alter']['nl2br'] = 0;
	$handler->display->display_options['fields']['field_uuke_alipay_product_nid']['alter']['word_boundary'] = 1;
	$handler->display->display_options['fields']['field_uuke_alipay_product_nid']['alter']['ellipsis'] = 1;
	$handler->display->display_options['fields']['field_uuke_alipay_product_nid']['alter']['strip_tags'] = 0;
	$handler->display->display_options['fields']['field_uuke_alipay_product_nid']['alter']['trim'] = 0;
	$handler->display->display_options['fields']['field_uuke_alipay_product_nid']['alter']['html'] = 0;
	$handler->display->display_options['fields']['field_uuke_alipay_product_nid']['element_label_colon'] = 1;
	$handler->display->display_options['fields']['field_uuke_alipay_product_nid']['element_default_classes'] = 1;
	$handler->display->display_options['fields']['field_uuke_alipay_product_nid']['hide_empty'] = 0;
	$handler->display->display_options['fields']['field_uuke_alipay_product_nid']['empty_zero'] = 0;
	$handler->display->display_options['fields']['field_uuke_alipay_product_nid']['hide_alter_empty'] = 1;
	$handler->display->display_options['fields']['field_uuke_alipay_product_nid']['settings'] = array(
	  'link' => 1,
	);
	$handler->display->display_options['fields']['field_uuke_alipay_product_nid']['field_api_classes'] = 0;
	/* 字段: 内容: 商品价格 */
	$handler->display->display_options['fields']['field_uuke_alipay_product_price']['id'] = 'field_uuke_alipay_product_price';
	$handler->display->display_options['fields']['field_uuke_alipay_product_price']['table'] = 'field_data_field_uuke_alipay_product_price';
	$handler->display->display_options['fields']['field_uuke_alipay_product_price']['field'] = 'field_uuke_alipay_product_price';
	$handler->display->display_options['fields']['field_uuke_alipay_product_price']['settings'] = array(
	  'thousand_separator' => ' ',
	  'decimal_separator' => '.',
	  'scale' => '2',
	  'prefix_suffix' => 1,
	);
	/* 字段: 内容: Updated date */
	$handler->display->display_options['fields']['changed']['id'] = 'changed';
	$handler->display->display_options['fields']['changed']['table'] = 'node';
	$handler->display->display_options['fields']['changed']['field'] = 'changed';
	$handler->display->display_options['fields']['changed']['date_format'] = 'custom';
	$handler->display->display_options['fields']['changed']['custom_date_format'] = 'Y-m-d h:i:s';
	/* 字段: 内容: 订单状态 */
	$handler->display->display_options['fields']['field_uuke_alipay_trade_status']['id'] = 'field_uuke_alipay_trade_status';
	$handler->display->display_options['fields']['field_uuke_alipay_trade_status']['table'] = 'field_data_field_uuke_alipay_trade_status';
	$handler->display->display_options['fields']['field_uuke_alipay_trade_status']['field'] = 'field_uuke_alipay_trade_status';
	$handler->display->display_options['defaults']['filters'] = FALSE;
	/* Filter criterion: 内容: 已发表 */
	$handler->display->display_options['filters']['status']['id'] = 'status';
	$handler->display->display_options['filters']['status']['table'] = 'node';
	$handler->display->display_options['filters']['status']['field'] = 'status';
	$handler->display->display_options['filters']['status']['value'] = 1;
	$handler->display->display_options['filters']['status']['group'] = 1;
	$handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
	/* Filter criterion: 内容: 类型 */
	$handler->display->display_options['filters']['type']['id'] = 'type';
	$handler->display->display_options['filters']['type']['table'] = 'node';
	$handler->display->display_options['filters']['type']['field'] = 'type';
	$handler->display->display_options['filters']['type']['value'] = array(
	  'uuke_alipay_order' => 'uuke_alipay_order',
	);
	/* Filter criterion: 内容: 订单状态 (field_uuke_alipay_trade_status) */
	$handler->display->display_options['filters']['field_uuke_alipay_trade_status_value']['id'] = 'field_uuke_alipay_trade_status_value';
	$handler->display->display_options['filters']['field_uuke_alipay_trade_status_value']['table'] = 'field_data_field_uuke_alipay_trade_status';
	$handler->display->display_options['filters']['field_uuke_alipay_trade_status_value']['field'] = 'field_uuke_alipay_trade_status_value';
	$handler->display->display_options['filters']['field_uuke_alipay_trade_status_value']['value'] = '等待处理';
	/* Filter criterion: 用户: Current */
	$handler->display->display_options['filters']['uid_current']['id'] = 'uid_current';
	$handler->display->display_options['filters']['uid_current']['table'] = 'users';
	$handler->display->display_options['filters']['uid_current']['field'] = 'uid_current';
	$handler->display->display_options['filters']['uid_current']['relationship'] = 'uid';
	$handler->display->display_options['filters']['uid_current']['value'] = '1';
	$handler->display->display_options['path'] = 'my-order-list-wait';
	$handler->display->display_options['menu']['type'] = 'normal';
	$handler->display->display_options['menu']['title'] = 'Waiting Paid';
	$handler->display->display_options['menu']['weight'] = '0';
	$handler->display->display_options['menu']['name'] = 'main-menu';
	$handler->display->display_options['menu']['context'] = 0;
	$handler->display->display_options['tab_options']['type'] = 'normal';
	$handler->display->display_options['tab_options']['weight'] = '0';
	$handler->display->display_options['tab_options']['name'] = 'main-menu';
	$translatables['uuke_order_list'] = array(
	  t('Master'),
	  t('All Order LIst'),
	  t('more'),
	  t('确定'),
	  t('重置'),
	  t('Sort by'),
	  t('Asc'),
	  t('Desc'),
	  t('Items per page'),
	  t('- All -'),
	  t('Offset'),
	  t('暂无数据'),
	  t('内容 entity referenced from field_uuke_alipay_product_nid'),
	  t('author'),
	  t('订单号'),
	  t('Product'),
	  t('商品价格'),
	  t('Updated date'),
	  t('订单状态'),
	  t('User'),
	  t('All order list page'),
	  t('My order list page'),
	  t('My Order LIst'),
	  t('Waiting paid'),
	  t('My Waiting paid Order List'),
	);
}
	$views[$view->name] = $view;
	// return views
	return $views;
}

	
