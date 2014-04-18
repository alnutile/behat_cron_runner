<?php

namespace Drupal\BehatRunner;
use Symfony\Component\Filesystem\Filesystem;

class WormlyReport {
    public $rows = array();
    public $feature_name = 'Not Found..';
    private $table_array = array();
    public $filesystem;
    public $path;


    function __construct(Filesystem $filesystem = null, $path = null)
    {
        $this->filesystem = ($filesystem == null) ? new Filesystem() : $filesystem;
        $this->path = ($path == null) ? drupal_realpath(file_build_uri("/") . '/wormly') : $path;
        if(!$this->filesystem->exists($this->path)){
            $this->filesystem->mkdir($this->path, $mode = 0777);
        };
    }


    public function createWormlyPages($results) {
        $pages = array();
        foreach($results as $value) {
            $timezone = 'America/New_York';
            $class = ($value['status'] == 1) ? 'fail' : 'pass';
            $status = strtoupper($class);
            $date = date('M-d-Y h:i:s', $value['time']);
            $header = "<h1>Last Run: {$date} in $timezone</h1>";

            $pages[$value['filename']]['result'] = "$header <p>{$value['filename']} &nbsp; $status</p>";
            $pages[$value['filename']]['filename'] = $value['filename'];
        }

        return $pages;
    }

    public function create_html_file($html, $report_name = 'wormly.html') {
        $destination = $this->path . '/' . $report_name;
        $write = @file_put_contents($destination, $html);
        if ($write) { $this->filesystem->chmod($destination, 0755); }
    }

    public function createManyFiles($pages)
    {
        foreach($pages as $value) {
            $filename = $value['filename'] . '.html';
            $this->create_html_file($value['result'], $filename);
        }
    }
}