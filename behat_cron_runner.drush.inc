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
    $items['behat-cron-qup'] = array(
        'description' => 'Put the jobs in to DrupalQ',
        'aliases' => array('bcq'),
        'allow-additional-options' => FALSE,
        'examples' => array(
            'drush bcq' => 'This will find all tests and place into q'
        ),
        'arguments' => array(),
        'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_FULL
    );
    $items['behat-run-consumer'] = array(
        'description' => 'Run the jobs in the DrupalQ',
        'aliases' => array('bcc'),
        'allow-additional-options' => TRUE,
        'examples' => array(
            'drush bcc 7' => 'Run 7 items in the queue'
        ),
        'arguments' => array(
            'items' => 'items to batch'
        ),
        'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_FULL
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

    $queue = DrupalQueue::get('bcr', TRUE);
    $queue_size = $queue->numberOfItems();
    $limit = variable_get('behat_cron_runner_q_limit', 5);
    $limit_this_run = ($queue_size > $limit) ? $limit : $queue_size;

    $thread_limit = variable_get('behat_cron_runner_thread_limit', 2);
    $threads = drush_get_option('thread', $thread_limit);
    drush_print("Going to run {$limit_this_run} from queue {$queue_size} tests with {$threads} threads");
    try {
        drush_thread_manager($queue_size, $limit_this_run, $threads, '_run_each_test');
    }
    catch(\BehatWrapper\BehatException $e) {
        drush_set_error($e->getMessage());
    }
}

function _run_each_test($thread_id, $batch_size, $offset) {
    return "drush behat-run-consumer $batch_size";
}

function drush_behat_cron_runner_behat_run_consumer($limit = 5) {
    $queue = DrupalQueue::get('bcr', TRUE);
    for ($count = 0; $count < $limit; $count++) {

        if ($item = $queue->claimItem()) {
            $transaction = db_transaction(__FUNCTION__);

            try {
                // Do something with the item.
                $cmd = $item->data['cmd'];
                exec($cmd);
            }
            catch (Exception $e) {
                $transaction->rollback();
                drush_set_error($e->getMessage());
                return;
            }

            unset($transaction);
            $queue->deleteItem($item);
        }

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


function drush_behat_cron_runner_behat_cron_qup() {
    $queue = DrupalQueue::get('bcr', TRUE);
    $queue_size = $queue->numberOfItems();

    $iterator = _get_files();
    foreach($iterator as $file) {
        $path = $file->getRealpath();
        $name = $file->getFilename();
        $cmd = "drush behat-run-one $path $name";
        $record = array(
            'cmd' => $cmd
        );
        $queue->createItem($record);
    }
    $queue_size = $queue->numberOfItems();
    drush_print("behat_cron_runner has $queue_size items to process");
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