<?php namespace Drupal\BehatRunner;

use BehatWrapper\BehatWrapper;
use BehatWrapper\BehatCommand;
use Symfony\Component\Process;

class BehatEditorRun {

    public $behat_yml_path;
    public $full_path_and_test_name;
    public $bin_path;
    public $command;
    public $behatCommand;

    public function __construct($behat_yml_path, BehatWrapper $command = null, $bin_path, BehatCommand $behatCommand = null) {
        $this->behat_yml_path   = $behat_yml_path;
        $this->behatCommand     = ($behatCommand == null) ? BehatCommand::getInstance() : $behatCommand;
        $this->command          = ($command == null) ? new BehatWrapper() : $command;
        $this->bin_path         = $bin_path;
        $this->command->setBehatBinary($bin_path);
    }

    public function run($full_path_and_test_name, $profile = 'default') {
        $this->full_path_and_test_name = $full_path_and_test_name;
        $run = $this->command->behat("--config=" . $this->behat_yml_path . ' --profile=' . $profile . " " . $this->full_path_and_test_name, $this->bin_path);
        return $run;
    }

    public function buildResults($result, $file = null, $status) {
        $file = ($file == null) ? $file->getFilename() : $file;
        $results[$file]['filename'] = $file;
        $results[$file]['time'] = time();
        $results[$file]['status'] = $status;
        return $results;
    }

    public function runMany($iterator) {
        $results = array();
        $count = 0;
        foreach($iterator as $file) {
            try {
                $result = $this->run($file->getRealpath());
                $results = array_merge($results, $this->buildResults($result, $file, 0));
            }
            catch(\BehatWrapper\BehatException $e) {
                try {
                    $result = $this->run($file->getRealpath());
                    $results = array_merge($results, $this->buildResults($result, $file, 0));
                }
                catch(\BehatWrapper\BehatException $e) {
                    $results = array_merge($results, $this->buildResults(false, $file, 1));
                }
            }
        }
        return $results;
    }

}

