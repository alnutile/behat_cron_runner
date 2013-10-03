<?php

use Drupal\BehatRunner,
    Drupal\BehatEditor;

/**
 * Output a table of items marked critical
 *
 */

function behat_cron_runner_index() {
    composer_manager_register_autoloader();
    $res = new Drupal\BehatRunner\Runner();
    $criticalTests = $res->getCriticalTests();

    _behat_cron_runner_test($criticalTests, 1);

    $behat_table = _behat_cron_runner_table($criticalTests);
    $build['intro'] = array(
        '#markup' => $behat_table,
    );

    return $build;
}
