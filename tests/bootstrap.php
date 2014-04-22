<?php
$autoloadFile   = __DIR__;
$autoloadFile   = explode("/", $autoloadFile);
//sites/vendor
//$autoloadFile   = array_slice($autoloadFile, 0, -4);
//sites/default/files/vendor
$autoloadFile   = array_slice($autoloadFile, 0, -5);
$autoloadFile   = implode("/", $autoloadFile);
$autoloadFile   = $autoloadFile . "/default/files/vendors/autoload.php";

if (!file_exists($autoloadFile)) {
    throw new RuntimeException('Install dependencies to run test suite.');
}
require_once $autoloadFile;

$loader = new \Composer\Autoload\ClassLoader();
$loader->add('Drupal\\BehatRunner\\', 'tests/');
$loader->register();
