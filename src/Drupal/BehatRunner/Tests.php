<?php

namespace Drupal\BehatRunner;

use Drupal\BehatEditor\Files,
    Drupal\BehatRunner,
    Drupal\BehatEditor;

class Tests {
    public $allCriticalTests = array();

    public function __construct() {
        composer_manager_register_autoloader();
        $this->allCriticalTests = self::getCriticalTests();

        watchdog('test_line_16', print_r($this->allCriticalTests, 1));
    }

    /**
     * Find all tests marked @critical
     *
     * this will store them in cache
     * if they are not there.
     *
     */
    public function getCriticalTests() {

        $cache = cache_get('behat_runner_tests');
        if(cache_get('behat_runner_tests')) {
            return $cache->data;
        } else {
            watchdog('test_line_32', print_r(self::_setCriticalTestsCache(), 1));
            return self::_setCriticalTestsCache();
        }
    }

    /**
     * Run the tests but if fail (status = 1)
     * run a second time.
     *
     * @param int $javascript
     * @return array
     */
    public function runTests($javascript = 0) {
        $results = array();
        foreach($this->allCriticalTests as $key) {
            $run = 1;
            $test = self::_test_each($key, 1, $javascript);
            $status = $test['results'];
            $fail = 1;
            if($status === $fail && $run == 1) {
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
        //$res = new BehatCronRunnerExec($key);
        $res = new BehatEditor\BehatEditorRun($key);
        $test = $res->exec($javascript);
        return $test;
    }


    private function _setCriticalTestsCache(){
        $get = new Files();
        $data = $get->getFilesArray();
        $dataTmp = self::_filterCritical($data);
        return $dataTmp;
    }

    private function _filterCritical($files_array) {
        $criticals = array();
        foreach($files_array as $key => $value) {
            watchdog('test_line_83', print_r($key, 1));
            foreach($value as $file_path => $values) {
                watchdog('test_line_84', print_r($values['tags_array'], 1));
                foreach($values['tags_array'] as $tag) {
                    //in_array not working for some reason?
                    watchdog("tag", print_r(substr($tag, 1), 1));
                    if(substr($tag, 1) == 'critical') {
                        watchdog("found_in_array", print_r('test'));
                        $criticals[$file_path] = $values;
                    }
                }
            }
        }
        return $criticals;
    }



}