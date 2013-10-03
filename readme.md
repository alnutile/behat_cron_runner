# Behat Cron Runner

The report page is here
admin/behat/index/critical


Using Behat Editor module and Behat SauceLabs module.

This module will add a cron job that will run all 
Features and Scenarios marked @critical

If Saucelabs is enabled it will use that modules Run class
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