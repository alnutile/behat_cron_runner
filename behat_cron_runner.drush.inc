<?php

use Drupal\BehatRunner;
use BehatWrapper\BehatCommand;
use Drupal\BehatRunner\Events\BehatCronRunnerEventListener;
use BehatWrapper\BehatWrapper;

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
    $items['behat-run-one'] = array(
        'description' => 'Run the cron job for critical jobs pass 1 for javascript TRUE and 1 for update wormly.html',
        'allow-additional-options' => TRUE,
        'aliases' => array('bcro'),
        'examples' => array(
            'drush brco $file' => 'This will cause it to run all tests and the 1 will turn on @javascript tags. The final 1 would update the wormly report'
        ),
        'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_FULL,
        'arguments' => array(
            'filepath' => 'absolute path',
            'filename' => "File name"
        ),
    );

    return $items;
}
//1 get the files and count the #
//2

function drush_behat_cron_runner_behat_cron_run() {
    print "Running Tests...\n\r";

    variable_set('behat_cron_runner_last_run', time());

    $iterator = _get_files();

    $count = count($iterator);

    $thread_limit = variable_get('behat_cron_runner_thread_limit', 2);
    $threads = drush_get_option('thread', $thread_limit);

    drush_print("Going to run {$count} tests with {$threads} threads");
    drush_thread_manager($count, 1, $threads, '_run_each_test');
}

function _run_each_test($thread_id, $batch_size, $offset) {
    $iterator = _get_files();
    $count = 0;
    foreach($iterator as $file) {
        if ($count === $offset) {
            $cms = "drush behat-run-one {$file->getRealpath()} {$file->getFilename()}";
            return $cms;
        }
        $count++;
    }
}

/**
 * Ideally I would pass the $file object
 * @param $filepath
 * @param $filename
 */
function drush_behat_cron_runner_behat_run_one($filepath, $filename) {
    $yml_path = variable_get('file_private_path') . '/behat.yml';
    $bin_path = drupal_realpath(variable_get('composer_manager_vendor_dir')) . '/bin/';
    $wormlyReport = new BehatRunner\WormlyReport();
    $runner = new BehatRunner\BehatEditorRun($yml_path, null, $bin_path);
    $profile = variable_get('behat_cron_runner_profile', 'default');
    
    try {
        $runner->run($filepath, $profile);
        $result     = array('status' => 0, 'filename' => $filename);
        $html       = $wormlyReport->createOneWormlyPage($result);
        $wormlyReport->write_html_file($html, $filename . '.html');
    }
    catch(\BehatWrapper\BehatException $e) {
            try {
                $runner->run($filepath, $profile);
                $result     = array('status' => 0, 'filename' => $filename);
                $html       = $wormlyReport->createOneWormlyPage($result);
                $wormlyReport->write_html_file($html, $filename . '.html');
            }
            catch(\BehatWrapper\BehatException $e) {
                $result = array('status' => 1, 'filename' => $filename);
                $html       = $wormlyReport->createOneWormlyPage($result);
                $wormlyReport->write_html_file($html, $filename . '.html');
            }
    }
}

function _get_files() {
    $root_test_path = variable_get('file_private_path') . '/behat_tests/';
    $getTests = new BehatRunner\GetTests($root_test_path);
    $iterator = $getTests->finder->files()
        ->name('*.feature')
        ->contains('@critical')
        ->in($root_test_path);
    return $iterator;
}

function _event_listener() {
    return "DONE";
}