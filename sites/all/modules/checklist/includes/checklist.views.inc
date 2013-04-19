<?php
// $Id$

/**
 * @file
 * Views integration.
 */

/**
 * Implements the hook_views_data function
 */
function checklist_views_data() {
  $data = array();

  $data['checklist_lists'] = array();
  $data['checklist_lists']['table'] = array(
    'group' => t('Checklist'),
    'base' => array(
      'field' => 'clid',
      'title' => t('Checklist'),
    ),
  );
  $data['checklist_lists']['title'] = array(
    'title' => t('Checklist title'),
    'help' => t('The title of the checklist.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );
  $data['checklist_lists']['description'] = array(
    'title' => t('Checklist description'),
    'help' => t('The description of the checklist.'),
    'field' => array(
      'handler' => 'views_handler_field_markup',
      'click sortable' => TRUE,
      'additional fields' => array('format'),
    ),
  );
  $data['checklist_lists']['weight'] = array(
    'title' => t('Checklist weight'),
    'help' => t('The weight of the checklist.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
      'allow empty' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  $data['checklist_lists']['status'] = array(
    'title' => t('Checklist status'),
    'help' => t('The status of the checklist.'),
    'field' => array(
      'handler' => 'views_handler_field_boolean',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_boolean_operator',
      'allow empty' => TRUE,
      'type' => 'yes-no',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  $data['checklist_instances'] = array();
  $data['checklist_instances']['table'] = array(
    'group' => t('Checklist'),
    'base' => array(
      'field' => 'instance_id',
      'title' => t('Checklist'),
    ),
    'join' => array(
      'checklist_lists' => array(
        'left_field' => 'clid',
        'field' => 'clid',
      ),
    ),
  );
  $data['checklist_instances']['clid'] = array(
    'title' => t('Checklist'),
    'help' => t('The checklist that the instance belongs to.'),
    'relationship' => array(
      'base' => 'checklist_lists',
      'base field' => 'clid',
      'handler' => 'views_handler_relationship',
      'label' => t('Checklist'),
    ),
  );
  $data['checklist_instances']['title'] = array(
    'title' => t('Instance title'),
    'help' => t('The title of the checklist instance.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );
  $data['checklist_instances']['group_complete'] = array(
    'title' => t('Group/Team instance'),
    'help' => t('Whether this instance is a group/team version of the checklist.'),
    'field' => array(
      'handler' => 'views_handler_field_boolean',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_boolean_operator',
      'allow empty' => TRUE,
      'type' => 'yes-no',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  $data['checklist_instances']['status'] = array(
    'title' => t('Instance status'),
    'help' => t('The status of the checklist instance.'),
    'field' => array(
      'handler' => 'views_handler_field_boolean',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_boolean_operator',
      'allow empty' => TRUE,
      'type' => 'yes-no',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  $data['checklist_items'] = array();
  $data['checklist_items']['table'] = array(
    'group' => t('Checklist'),
    'join' => array(
      'checklist_lists' => array(
        'left_field' => 'clid',
        'field' => 'clid',
      ),
    ),
    'base' => array(
      'field' => 'cliid',
      'title' => t('Checklist items'),
    ),
  );
  $data['checklist_items']['clid'] = array(
    'title' => t('Checklist'),
    'help' => t('The checklist that the item belongs to.'),
    'relationship' => array(
      'base' => 'checklist_lists',
      'base field' => 'clid',
      'handler' => 'views_handler_relationship',
      'label' => t('Checklist'),
    ),
  );
  $data['checklist_items']['title'] = array(
    'title' => t('Item title'),
    'help' => t('The checklist item title'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );
  $data['checklist_items']['description'] = array(
    'title' => t('Item description'),
    'help' => t('The description of the item.'),
    'field' => array(
      'handler' => 'views_handler_field_markup',
      'click sortable' => TRUE,
      'additional fields' => array('format'),
    ),
  );
  $data['checklist_items']['weight'] = array(
    'title' => t('Item weight'),
    'help' => t('The weight of the item.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
      'allow empty' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  $data['checklist_items']['status'] = array(
    'title' => t('Item status'),
    'help' => t('The status of the item.'),
    'field' => array(
      'handler' => 'views_handler_field_boolean',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_boolean_operator',
      'allow empty' => TRUE,
      'type' => 'yes-no',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  $data['checklist_groups'] = array();
  $data['checklist_groups']['table'] = array(
    'group' => t('Checklist'),
    'join' => array(
      'users' => array(
        'left_table' => 'usergroups_api',
        'left_field' => 'group_id',
        'field' => 'group_id',
      ),
      'checklist_instances' => array(
        'left_field' => 'instance_id',
        'field' => 'instance_id',
      ),
    ),
  );
  $data['checklist_groups']['instance_id'] = array(
    'title' => t('Checklist group instance'),
    'help' => t('Join groups to the corresponding checklist instances they should be completing.'),
    'relationship' => array(
      'handler' => 'views_handler_relationship',
      'base' => 'checklist_instances',
      'base field' => 'instance_id',
      'label' => t('Checklist instance.'),
    ),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  $data['checklist_user_checks'] = array();
  $data['checklist_user_checks']['table'] = array(
    'group' => t('Checklist'),
    'join' => array(
      'checklist_items' => array(
        'left_field' => 'cliid',
        'field' => 'cliid',
        'type' => 'LEFT',
      ),
      'checklist_instances' => array(
        'left_field' => 'instance_id',
        'field' => 'instance_id',
      ),
      'users' => array(
        'left_field' => 'uid',
        'field' => 'uid',
        'type' => 'LEFT',
      ),
    ),
  );
  $data['checklist_user_checks']['instance_id'] = array(
    'title' => t('Checklist instance'),
    'help' => t('Join user checks to the instances that they came from.'),
    'relationship' => array(
      'handler' => 'views_handler_relationship',
      'base' => 'checklist_instances',
      'base field' => 'instance_id',
      'label' => t('Checklist instance'),
    ),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  $data['checklist_user_checks']['uid'] = array(
    'title' => t('Checked by'),
    'help' => t('The user who completed the checklist.'),
    'relationship' => array(
      'base' => 'users',
      'base field' => 'uid',
      'handler' => 'views_handler_relationship',
      'label' => t('Checked by'),
    ),
  );
  $data['checklist_user_checks']['checked_on'] = array(
    'title' => t('Checked On'),
    'help' => t('The date that the checklist item was checked on.'),
    'field' => array(
    'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
  );

  $data['checklist_complete'] = array();
  $data['checklist_complete']['table'] = array(
    'group' => t('Checklist'),
    'join' => array(
      'users' => array(
        'left_field' => 'uid',
        'field' => 'uid',
      ),
      'checklist_lists' => array(
        'left_field' => 'clid',
        'field' => 'clid',
      ),
    ),
  );
  $data['checklist_complete']['instance_id'] = array(
    'title' => t('Checklist instance completed'),
    'help' => t('Join the completed checklist instance.'),
    'relationship' => array(
      'handler' => 'views_handler_relationship',
      'base' => 'checklist_instances',
      'base field' => 'instance_id',
      'label' => t('Checklist instance'),
    ),
  );
  $data['checklist_complete']['completed'] = array(
    'title' => t('Completed On'),
    'help' => t('The date that the checklist was completed.'),
    'field' => array(
    'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
  );

  return $data;
}
