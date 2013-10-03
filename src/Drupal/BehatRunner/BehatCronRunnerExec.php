<?php

namespace Drupal\BehatRunner;
use Drupal\BehatEditor\BehatEditorRun;

class BehatCronRunnerExec extends BehatEditorRun {

    public function __construct($file_object) {
        parent::__construct($file_object);
    }

    public function exec($javascript = FALSE) {
        if($javascript == TRUE) {
            $tags = '';
        } else {
            $tags = "--tags '~@javascript'";
        }
        //Needed just 1 or 0 for results
        // could not get the $results value of exec to do that
        exec("cd $this->behat_path && ./bin/behat --config=\"$this->yml_path\" --no-paths $tags $this->absolute_file_path", $output, $results);
        variable_set('behat_cron_runner_last_run', REQUEST_TIME);
        return array('results' => $results, 'output' => $output);
    }

}