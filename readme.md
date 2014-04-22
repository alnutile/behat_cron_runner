# Behat Cron Runner


This module will add a cron job that will run all
Features and Scenarios marked @critical

## Install

There is a feature to take care of most of it BUT there are variables to change as needed
-Private path

#### Configure

There somre notes here as well

[admin/config/behat/settings]

## Drush Multi Thread

You will need
https://github.com/johnennewdeeson/drush-multi-processing/blob/master/mt.drush.inc
And install those as needed so your drush can access the commands

so when you run

```
drush cc all
drush help
```

You should have access to mt commands

## Ultimate Cron

[admin/config/system/cron]
Ultimate cron is in place as well as a dependency so you will need to follow its instructions for setting up Cron

## Queue View

[admin/behat_cron_queue]