<?php namespace Drupal\BehatRunner;

use Symfony\Component\Finder\Finder;

class GetTests {

    public $finder;

    public function __construct($test_folder_root, Finder $finder = null) {
        $this->finder       = ($finder == null) ? new Finder() : $finder;
    }

}