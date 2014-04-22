<?php


function behat_cron_runner_admin_form($form, &$form_state) {
    $message = <<<HEREDOC
<p>
Make sure to set your private drupal path since this is key to storing information.
In there should be this folder structure
<br>
private/behat/feature/bootstrap
<br>
private/behat.yml
<br>
Your Tests will be in
<br>
private/behat/features
<br>
Your FeatureContext.php if you have hooks
<br>
private/behat/features/bootstrap
<br>
See readme.md for drush notes
</p>
HEREDOC;
    $form['notice'] = array(
        '#markup' => "$message"
    );
    $form['behat_cron_runner_profile'] = array(
        '#title' => 'Behat.yml profile to default to',
        '#type' => 'textfield',
        '#default_value' => variable_get('behat_cron_runner_profile', 'default'),
        '#description' => t('You may have one called production or dev or saucelabs'),
    );

    $form['behat_cron_runner_q_limit'] = array(
        '#title' => 'How many items to process per Queue run',
        '#type' => 'textfield',
        '#default_value' => variable_get('behat_cron_runner_q_limit', 10),
        '#description' => t('Not sure what is best here. If it is not clear by the next behat run it is no big deal'),
    );

    $form['behat_cron_runner_thread_limit'] = array(
        '#title' => 'How many threads',
        '#type' => 'textfield',
        '#default_value' => variable_get('behat_cron_runner_thread_limit', 2),
        '#description' => t('Start with 2 then work your way up to see if it goes faster without bogging down the server.'),
    );

    return system_settings_form($form);
}
