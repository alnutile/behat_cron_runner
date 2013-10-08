<?php

namespace Drupal\BehatRunner;


class WormlyReport {
    public $rows = array();
    public $feature_name = 'Not Found..';
    private $table_array = array();

    /**
     * Public
     * Output table to html formatted content
     *
     * 1. The name of the file
     * 2. The name of the feature
     * 3. The duration
     * 4. The status
     * 5. The time done
     *
     * into a format I can feed the theme_table function
     */
    public function createWormlyPage($results) {
        $headers = array(
            'File Name',
            'Feature',
            'Duration',
            'Time Ran',
            'Status',
        );

        foreach($results as $value) {
            $timezone = 'America/New_York';
            $class = ($value['status'] == 1) ? 'fail' : 'pass';
            $status = strtoupper($class);
            $this->feature_name = self::grab_feature($value['file_object']['scenario']);
            $rows[] = array(
                'data' => array(
                        $value['file_object']['filename'],
                        $this->feature_name,
                        $value['duration'],
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

    /**
     * Take html and write to the file
     * @param $table_html
     */
    public function create_html_file($html) {
        $path = file_build_uri("/");
        $response = file_unmanaged_save_data($html, $path . '/wormly.html', $replace = FILE_EXISTS_REPLACE);
        drupal_chmod($path . '/wormly.html', $mode = 0666);
        return $response;
    }

    /**
     * Private
     * Check for wormly.html and make it not there
     */
    public function grab_feature($file_text) {
        $feature_to_array = explode("\n", $file_text);
        $results = self::find_feature_line($feature_to_array, 0);
        return $results;
    }

    /**
     * Find Feature
     */
    public function find_feature_line($array, $step) {
        $total = count($array);
        for($i = $step; $i <= $total; $i++) {
            if(strpos($array[$i], 'Feature:') !== false) {
                return $array[$i];
                break;
            }
        }
    }

}