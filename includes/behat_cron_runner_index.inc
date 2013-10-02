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

    $behat_table = _behat_cron_runner_table($criticalTests);
    $build['intro'] = array(
        '#markup' => $behat_table,
    );

    return $build;
}

function _behat_cron_runner_table($files_array) {
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

function _show_file_link($file_name, $module_name) {
    if(strpos($file_name, 'private_') === FALSE ) {
        $results = l($file_name, 'admin/behat/view/' . $module_name . '/' . $file_name);
    } else {
        $results = $file_name;
    }
    return $results;
}

function _show_link($file_name, $module_name, $link_text = 'view') {
    if(strpos($file_name, 'private_') === FALSE ) {
        $results = l($link_text, 'admin/behat/'.$link_text.'/' . $module_name . '/' . $file_name);
    } else {
        $results = 'not allowed';
    }
    return $results;
}