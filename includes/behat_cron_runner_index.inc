<?php

use Drupal\BehatRunner,
    Drupal\BehatEditor;

/**
 * Output a table of items marked critical
 *
 */

function behat_cron_runner_index() {
    composer_manager_register_autoloader();
    $res = new Drupal\BehatRunner\Tests();
    $criticalTests = $res->getCriticalTests();

    $behat_table = _behat_runner_table($criticalTests);

    $last_run = variable_get('behat_cron_runner_last_run', 0);
    $diff = REQUEST_TIME - $last_run;
    dpm($last_run);

    dpm($diff);

    $path = file_build_uri("/");

    $build['link'] = array(
        '#markup' => l('Wormly Page', file_create_url($path . '/wormly.html'), array('attributes' => array('class' => 'btn btn-info'))),
    );

    $build['intro'] = array(
        '#markup' => $behat_table,
    );

    return $build;
}


/**
 * Output for the Admin area
 *
 * @param $files_array
 * @return string
 */
function _behat_runner_table($files_array) {
    $rows = array();
    foreach($files_array as $key => $value) {
        $file_name = $value['filename'];
        $module_name = $value['module'];
        $tags = implode(', ', $value['tags_array']);
        $rows[] = array(
            'data' =>
            array
            (
                _show_file_link($file_name, $module_name),
                _show_module_name($module_name),
                $tags,
                _show_link($file_name, $module_name, $link_text = 'view'),
                _show_link($file_name, $module_name, $link_text = 'edit'),
                _show_link($file_name, $module_name, $link_text = 'delete'),
            )
        );
    };

    $header = array(
        'Name',
        'Module',
        'Tags',
        'View',
        'Edit',
        'Delete',
    );

    $behat_table = theme('table', array(
        'header' => $header,
        'rows' => $rows,
        'attributes' => array('class' => array('table-hover'), 'id' => 'admin-features')
    ));

    return $behat_table;
}

