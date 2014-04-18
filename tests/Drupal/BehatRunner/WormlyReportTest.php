<?php namespace Drupal\BehatRunner;

function variable_get($params) {
    return 120000;
}

function file_build_uri() {
    return '/tmp/wormly';
}

class WormlyReportTest extends TestBase {
    public $results;
    public $pages;

    public function setUp()
    {
        parent::setUp();

        $this->results['test1.feature']['filename'] = 'test1.feature';
        $this->results['test1.feature']['time']     = time();
        $this->results['test1.feature']['status']   = 1;
        $this->results['test2.feature']['filename'] = 'test2.feature';
        $this->results['test2.feature']['time']     = time();
        $this->results['test2.feature']['status']   = 0;

        $this->pages['test1.feature']['result']     = "You score hear test1.feature FAIL";
        $this->pages['test1.feature']['filename']   = "test1.feature";
        $this->pages['test2.feature']['result']     = "You score hear test2.feature PASS";
        $this->pages['test2.feature']['filename']   = "test2.feature";
    }

    //1. can we make the page
    //2. how about the name?
    //3. what if there is an issue
    function testCreatePageContent()
    {
        $wormly = new WormlyReport();

        $output = $wormly->createWormlyPages($this->results);
        $this->assertArrayHasKey('test1.feature', $output);
        $this->assertContains('FAIL', $output['test1.feature']['result']);
    }

    function testCreateHTMLFile()
    {
        $html = "Test Report";
        $wormly = new WormlyReport();
        $wormly->create_html_file($html, 'test.html');
        $this->assertFileExists('/tmp/wormly/wormly/test.html');
    }

    function testCreateManyFiles()
    {
        $wormly = new WormlyReport();

        $wormly->createManyFiles($this->pages);
        $this->assertFileExists('/tmp/wormly/wormly/test1.feature.html');
        $this->assertFileExists('/tmp/wormly/wormly/test2.feature.html');
        $this->assertContains('PASS', file_get_contents('/tmp/wormly/wormly/test2.feature.html'));
    }

}