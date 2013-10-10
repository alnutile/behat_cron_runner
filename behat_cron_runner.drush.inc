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
    if(func_num_args() > 0) {
        $javascript = func_get_arg(0);
    } else {
        $javascript = 0;
    }

    //@todo validate args
    composer_manager_register_autoloader();
    //@todo get composer to load this

    $res = new Drupal\BehatRunner\Tests();
    $criticalTests = $res->getCriticalTests();
    $results = $res->runTests($javascript);
    $wormlyReport = new Drupal\BehatRunner\WormlyReport();
    $html = $wormlyReport->createWormlyPage($results);

    if(func_num_args() > 1) {
        if(func_get_arg(1) == 1) {
            //Update the wormly HTML
            $wormlyReport->create_html_file($html);
        }
    }

    return drush_html_to_text("\n\r" . $html);
}
