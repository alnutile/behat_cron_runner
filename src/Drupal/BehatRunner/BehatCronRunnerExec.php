<?php

namespace Drupal\BehatRunner;


/**
 * @todo remove this class since now the BehatEditorRun comes with a drupal_alter.
 *   just need to see if it is enough
 *
 * Class BehatCronRunnerExec
 * @package Drupal\BehatRunner
 */
class BehatCronRunnerExec extends BehatEditorRun {
    public $saucelabs = FALSE;

    public function __construct($behat_yml_path, $command, $bin_path) {
        parent::__construct($behat_yml_path, $command, $bin_path);
    }

//    public function exec() {
//        if($javascript == TRUE || $this->saucelabs == TRUE) {
//            $tags = '';
//        } else {
//            $tags = "--tags '~@javascript'";
//        }
//
//        if($this->saucelabs == TRUE) {
//            $profile = '--profile=Webdriver-saucelabs';
//        } else {
//            $profile = '';
//        }
//        exec("cd $this->behat_path && ./bin/behat --config=\"$this->yml_path\" $profile --no-paths $tags $this->absolute_file_path", $output, $results);
//        variable_set('behat_cron_runner_last_run', REQUEST_TIME);
//        return array('results' => $results, 'output' => $output);
//    }

}