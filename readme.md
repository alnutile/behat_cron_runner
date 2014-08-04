# Behat Cron Runner


This module will add a cron job that will run all
Features and Scenarios marked @critical

## Install

There is a feature to take care of most of it BUT there are variables to change as needed
-Private path

#### Configure

There some notes here as well

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

## Example of interactive

You would ideally do this by running the cron and putting files in the private/behat_tests folder with the tag @critical

But let's run some at the command line

If you look here /admin/behat_cron_queue you will see a simple view into the drupal queue. Most likely nothing there.

At the command line we will add some jobs

~~~
/usr/bin/drush bcq
~~~

This will add some jobs  to the queue. You can run it a number of times to add numerous jobs to the queue.

Now when you go to /admin/behat_cron_queue you should see the cmd to run.

Instead of waiting for cron we will force it to happen.

~~~
/usr/bin/drush bcr
~~~

That should output something like

~~~
Running Tests...
Going to run 6 from queue 6 tests with 4 threads
Thread 0 starts at offset 0. Jobs remaining: 6
Thread 0 finished. Average speed is 3 jobs/minute. Estimated completion at 9:40:57 04/08/14
~~~

### Is your queue working

This default job should show it working

~~~
/usr/bin/drush mtq-process
~~~
