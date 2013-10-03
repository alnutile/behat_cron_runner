<?php

namespace Drupal\BehatRunner;

use Drupal\BehatEditor\Files;

class Runner {
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