<?php

namespace Drupal\BehatRunner;


class WormlyReport {
    public $rows = array();
    private $table_array = array();

    /**
     * Construct the row
     *
     */

    /**
     * Public
     * Make array of results array from row(s) coming in
     * @row = array()
     *   @file_object coming
     *   @status PASS / FAIL
     *   @length of test
     *   @time run
     *
     */

    /**
     * Private
     * Make table from Row(s)
     *
     * @params = array(
     *   file_object
     *   status
     *   duration
     *   time
     * )
     */
    public function row($result) {
        $this->rows = $result;
    }

    /**
     * Private
     * Output table to files/wormly.html
     *
     * 1. The name of the file
     * 2. The name of the feature
     * 3. The duration
     * 4. The status
     * 5. The time done
     *
     * into a format I can feed the theme_table function
     */
    public function createWormlyPage() {
        $headers = array(
            'File Name',
            'Feature',
            'Duration',
            'Time Ran',
            'Status'
        );

        foreach($this->rows as $value) {
            $class = ($value['status'] == 1) ? 'fail' : 'pass';
            watchdog('test_value', print_r($value, 1));
            $rows[] = array(
                'data' => array(
                        $value['file_object']['filename'],
                        'coming soon...',
                        $value['duration'],
                        $value['time'],
                        $value['status']
                )
            );
        }

        $table = theme('table', array('header' => $headers, 'rows' => $rows));
        watchdog('test_table', print_r($rows, 1));
        watchdog('test_table', print_r($table, 1));

    }

    /**
     * Private
     * Check for wormly.html and make it not there
     */
}