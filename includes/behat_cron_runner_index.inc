<?php

use Drupal\BehatRunner;

/**
 * Output a table of items marked critical
 *
 */

function behat_cron_runner_index() {
    composer_manager_register_autoloader();
    $res = new Drupal\BehatRunner\Runner();
    $criticalTests = $res->getCriticalTests();
    dpm($criticalTests);

    $build['intro'] = array(
        '#markup' => t('Tests found on the system with the Critical Tag'),
    );

    return $build;
}