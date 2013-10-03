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
    $results = $res->runTests(1);
    $wormlyReport = new Drupal\BehatRunner\WormlyReport();
    $html = $wormlyReport->createWormlyPage($results);
    $wormlyReport->create_html_file($html);

    $behat_table = _behat_runner_table($criticalTests);
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
                $module_name,
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

