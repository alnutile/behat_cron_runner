<?php

function behat_cron_runner_wormly() {
    $build['notice'] = array(
        '#markup' => variable_get('behat_cron_runner_status', 'Nothing to show here...'),
    );

    return $build;
}
