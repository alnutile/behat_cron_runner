<?php

namespace Drupal\BehatRunner;

use Drupal\BehatEditor\Files,
    Drupal\BehatRunner;

class Tests {
    public $allCriticalTests = array();

    public function __construct() {
        $this->allCriticalTests = self::getCriticalTests();
    }

    /**
     * Find all tests marked @critical
     *
     * this will store them in cache
     * if they are not there.
     *
     */
    public function getCriticalTests() {
        if($cache = cache_get('behat_runner_tests')) {
            return $cache->data;
        } else {
            return self::_setCriticalTestsCache();
        }
    }

    public function runTests($javascript = 0) {
        $results = array();
        foreach($this->allCriticalTests as $key) {
            $run = 1;
            $test = self::_test_each($key, 1, $javascript);
            $status = $test['results'];
            if($status === 1 && $run == 1) {
                $run = 2;
                $test = self::_test_each($key, $run, $javascript);
                $duration = array_pop($test['output']);
                $status = $test['results'];
                $results[] = array('file_object' => $key, 'status' => $status, 'duration' => $duration, 'time' => time());
            } else {
                $duration = array_pop($test['output']);
                $results[] = array('file_object' => $key, 'status' => $status, 'duration' => $duration, 'time' => time());
            }
        }
        return $results;
    }

    private function _test_each($key, $run, $javascript) {
        $res = new BehatCronRunnerExec($key);
        $test = $res->exec($javascript);
        return $test;
    }


    private function _setCriticalTestsCache(){
        composer_manager_register_autoloader();

        $get = new Files();
        $data = $get->getFilesArray();
        $dataTmp = self::_filterCritical($data);
        return $dataTmp;
    }

    private function _filterCritical($files_array) {
        $criticals = array();
        foreach($files_array as $key => $value) {
            foreach($value as $file_path => $values) {
                if(in_array('@critical', $values['tags_array'])) {
                    $criticals[$file_path] = $values;
                }
            }
        }
        return $criticals;
    }



}