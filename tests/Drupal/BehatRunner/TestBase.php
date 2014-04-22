<?php namespace Drupal\BehatRunner;

use Mockery;
use Symfony\Component\Filesystem\Filesystem;
use Symfony\Component\Finder\Finder;

class TestBase extends \PHPUnit_Framework_TestCase {
    public $fileSystem;
    public $finder;

    function setUp()
    {
        $this->finder                       = new Finder();
        $this->fileSystem                   = new Filesystem();

        if(!$this->fileSystem->exists('/tmp/wormly')) {
            $this->fileSystem->mkdir('/tmp/wormly');
        }
    }

    function tearDown()
    {
        if($this->fileSystem->exists('/tmp/wormly')) {
            $this->fileSystem->remove('/tmp/wormly');
        }
    }
}