<?php
/**
 * @file
 * behat_cron_runner.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function behat_cron_runner_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'queue';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'queue';
  $view->human_name = 'Queue';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Behat Cron Runner Queue';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '100';
  $handler->display->display_options['style_plugin'] = 'table';
  /* Header: Global: Text area */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['empty'] = TRUE;
  $handler->display->display_options['header']['area']['content'] = 'This will show the pending queue items for Behat Cron Jobs ie jobs marked @critical
You can see the cron job status that setups up this queue <a href=\'/admin/config/system/cron\'>here</a>

The two Crons are 
Behat Cron Runner : _behat_cron_runner_run
and 
Behat Cron Runner : _behat_cron_runner_queue_setup';
  $handler->display->display_options['header']['area']['format'] = 'filtered_html';
  /* Field: SystemQueue: Item ID */
  $handler->display->display_options['fields']['item_id']['id'] = 'item_id';
  $handler->display->display_options['fields']['item_id']['table'] = 'queue';
  $handler->display->display_options['fields']['item_id']['field'] = 'item_id';
  /* Field: SystemQueue: Creation */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'queue';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['date_format'] = 'long';
  /* Field: SystemQueue: Data */
  $handler->display->display_options['fields']['data']['id'] = 'data';
  $handler->display->display_options['fields']['data']['table'] = 'queue';
  $handler->display->display_options['fields']['data']['field'] = 'data';
  /* Field: SystemQueue: Expire */
  $handler->display->display_options['fields']['expire']['id'] = 'expire';
  $handler->display->display_options['fields']['expire']['table'] = 'queue';
  $handler->display->display_options['fields']['expire']['field'] = 'expire';
  $handler->display->display_options['fields']['expire']['date_format'] = 'long';
  /* Field: SystemQueue: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'queue';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  /* Filter criterion: SystemQueue: Name */
  $handler->display->display_options['filters']['name']['id'] = 'name';
  $handler->display->display_options['filters']['name']['table'] = 'queue';
  $handler->display->display_options['filters']['name']['field'] = 'name';
  $handler->display->display_options['filters']['name']['value'] = 'bcr';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'admin/behat_cron_queue';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Queue';
  $handler->display->display_options['menu']['name'] = 'main-menu';
  $export['queue'] = $view;

  return $export;
}
