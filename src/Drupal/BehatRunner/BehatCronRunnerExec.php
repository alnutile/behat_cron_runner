<?php

namespace Drupal\BehatRunner;
use Drupal\BehatEditor\BehatEditorRun;

class BehatCronRunnerExec extends BehatEditorRun {
    public $saucelabs = FALSE;

    public function __construct($file_object) {
        parent::__construct($file_object);
        /**
         * Quick check to see if we should force this to SauceLabs
         */
        if(module_exists('behat_editor_saucelabs')) {
            $path = drupal_get_path('module', 'behat_editor_saucelabs');
            $this->yml_path = drupal_realpath($path) . '/behat/behat.yml';
            $this->saucelabs = TRUE;
        }
        watchdog('test_sl_exists', print_r(module_exists('behat_editor_saucelabs'), 1));
        watchdog('test_sl_path', print_r($this->yml_path, 1));

    }

    public function exec($javascript = FALSE) {
        if($javascript == TRUE || $this->saucelabs == TRUE) {
            $tags = '';
        } else {
            $tags = "--tags '~@javascript'";
        }

        if($this->saucelabs == TRUE) {
            $profile = '--profile=Webdriver-saucelabs';
        } else {
            $profile = '';
        }
        exec("cd $this->behat_path && ./bin/behat --config=\"$this->yml_path\" $profile --no-paths $tags $this->absolute_file_path", $output, $results);
        variable_set('behat_cron_runner_last_run', REQUEST_TIME);
        return array('results' => $results, 'output' => $output);
    }

}