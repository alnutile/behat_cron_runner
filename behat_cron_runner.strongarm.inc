<?php
/**
 * @file
 * behat_cron_runner.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function behat_cron_runner_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'behat_cron_runner_profile';
  $strongarm->value = 'default';
  $export['behat_cron_runner_profile'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'behat_cron_runner_q_limit';
  $strongarm->value = 10;
  $export['behat_cron_runner_q_limit'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'behat_cron_runner_thread_limit';
  $strongarm->value = 4;
  $export['behat_cron_runner_thread_limit'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'composer_manager_autobuild_file';
  $strongarm->value = 0;
  $export['composer_manager_autobuild_file'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'composer_manager_autobuild_packages';
  $strongarm->value = 0;
  $export['composer_manager_autobuild_packages'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'composer_manager_file_dir';
  $strongarm->value = 'public://composer';
  $export['composer_manager_file_dir'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'composer_manager_vendor_dir';
  $strongarm->value = 'sites/default/files/vendors';
  $export['composer_manager_vendor_dir'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'default_ultimate_cron_job__behat_cron_runner_run';
  $strongarm->value = TRUE;
  $export['default_ultimate_cron_job__behat_cron_runner_run'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'file_public_path';
  $strongarm->value = 'sites/default/files';
  $export['file_public_path'] = $strongarm;

  return $export;
}
