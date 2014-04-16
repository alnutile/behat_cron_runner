<?php

namespace Drupal\BehatRunner;


class WormlyReport {
    public $rows = array();
    public $feature_name = 'Not Found..';
    private $table_array = array();

    public function createWormlyPage($results) {
        $headers = array(
            'File Name',
            'Time Ran',
            'Status',
        );

        foreach($results as $value) {
            $timezone = 'America/New_York';
            $class = ($value['status'] == 1) ? 'fail' : 'pass';
            $status = strtoupper($class);
            $rows[] = array(
                'data' => array(
                        $value['filename'],
                        format_date($value['time'], 'long', $format = '',  $timezone),
                        $status
                ),
                'class' => array($class)
            );
        }

        $last_run = variable_get('behat_cron_runner_last_run', 0);
        if(empty($last_run)) {
            $last_run = t('NEVER!');
        } else {
            $last_run = format_date($last_run, 'long', $format = '',  $timezone);
        }
        $header = "<h1>Last Run: {$last_run} in $timezone";
        $table_html = theme('table', array('header' => $headers, 'rows' => $rows));
        return $header . '<br>' . $table_html;
    }

    public function create_html_file($html, $report_name = '/wormly.html') {
        $path = file_build_uri("/");
        $response = file_unmanaged_save_data($html, $path . '/' . $report_name, $replace = FILE_EXISTS_REPLACE);
        drupal_chmod($path . '/' . $report_name, $mode = 0666);
        return $response;
    }


}