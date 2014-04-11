<?php

use Drupal\BehatRunner;
/**
 * @file
 * Drush hook implementations for BehatEditor
 */

/**
 * Implements hook_drush_command().
 */
function behat_cron_runner_drush_command() {
    $items = array();

    $items['behat-cron-run'] = array(
        'description' => 'Run the cron job for critical jobs pass 1 for javascript TRUE and 1 for update wormly.html',
        'allow-additional-options' => TRUE,
        'aliases' => array('bcr'),
        'examples' => array(
            'drush bcr 1 1' => 'This will cause it to run all tests and the 1 will turn on @javascript tags. The final 1 would update the wormly report'
        ),
        'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_FULL,
        'arguments' => array(
            'javascript' => '1 if you want to run javascript based tests 0 if not. Javascript means you are running this locally.',
            'wormly' => 'Update the wormly report 1 = yes update that page',
        ),
    );

    return $items;
}


function drush_behat_cron_runner_behat_cron_run() {
    print "Running Tests...\n\r";

    variable_set('behat_cron_runner_last_run', time());

    //1. get files
    $root_test_path = variable_get('file_private_path') . '/behat_tests/';
    $getTests = new BehatRunner\GetTests($root_test_path);

    $iterator = $getTests->finder->files()
        ->name('*.feature')
        ->contains('@critical')
        ->in($root_test_path);

    $yml_path = variable_get('file_private_path') . '/behat.yml';
    $bin_path = drupal_realpath(variable_get('composer_manager_vendor_dir')) . '/bin/';
    $runner = new BehatRunner\BehatEditorRun($yml_path, null, $bin_path);

    //2. Iterate over files and run
    $results = $runner->runMany($iterator);

    //3. Build report
    $wormlyReport = new Drupal\BehatRunner\WormlyReport();
    $html = $wormlyReport->createWormlyPage($results);
    $wormlyReport->create_html_file($html);

    print drush_html_to_text("\n\r" . $html);
    return;
}
