# Behat Cron Runner


This module will add a cron job that will run all
Features and Scenarios marked @critical


### Install

It uses composer_manager to set the autoload but that does not work as noted below.

#### BUG

**install composer manager not picking up my composer file and adding it to the autoload_namespace
file so right now I add it my self to the vendor/composer/autoload_namespaces.php under BehatEditor**

Once this is installed it should just run with each cron job.
You can run the drush commands to try it out
drush cc drush
drush bcr 0 1

The final command will skip the javascript tags but still run and udpate wormly.

### Now what

The final report page is here
admin/behat/index/critical

#### Using Behat Editor module and Behat SauceLabs module.

If BehatEditorSauceLabs [https://github.com/alnutile/behat_editor_saucelabs] is enabled it will use that modules Run class
else it will just use the Behat Module run non @javascript tests

It will track the last_run and only run every 3600 seconds.

On a Fail it will run again immediately and on the second fail it will 
trigger a Wormly based notice.

### Drush

drush bcr 1 1
this would that tests including the @javascript tags (first 1)
and update wormly (second 1)


You can run
drush help bcr
for more info