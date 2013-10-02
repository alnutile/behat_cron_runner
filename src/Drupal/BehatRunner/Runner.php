<?php

namespace Drupal\BehatRunner;

use Drupal\BehatEditor\Files;

class Runner {
    public $allCriticalTests = array();

    public function __construct() {
        $this->allCriticalTests = self::getCriticalTests();
    }

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
        return $data;
    }

}