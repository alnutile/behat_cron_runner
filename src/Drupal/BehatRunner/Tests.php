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
            $status = $test['response'];
            $fail = 1;
            if($status === $fail && $run == 1) {
                $run = 2;
                $test = self::_test_each($key, $run, $javascript);
                $duration = array_pop($test['output_array']);
                $status = $test['response'];
                $results[] = array('file_object' => $key, 'status' => $status, 'duration' => $duration, 'time' => time());
            } else {
                $duration = array_pop($test['output_array']);
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
            foreach($value as $file_path => $values) {
                foreach($values['tags_array'] as $tag) {
                    //in_array not working do to spaces
                    if(trim($tag) == '@critical') {
                        $criticals[$file_path] = $values;
                    }
                }
            }
        }
        return $criticals;
    }



}