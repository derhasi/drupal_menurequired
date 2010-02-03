<?php
// $Id$

/**
 * @file
 *   settings page for datetoday module.
 */

/**
 * Callback for datetoday admin form.
 */
function datetoday_admin_form($form) {
  $settings = datetoday_settings();
  $fields = content_fields();
  $levels = datetoday_levels('label');

  $form = array();
  // run each field (collected in datetoday_settings)
  foreach ($settings as $type => $set) {

    $form[$type] = array(
      '#type' => 'fieldset',
      '#title' => ($type == 'default') ? t('Default') : $fields[$type]['widget']['label'] ." [$type]",
      '#collapsible' => TRUE,
      '#collapsed' => ($type == 'default'),
    );

    $selected_levels = array_filter((array) $set['levels']);

    $form[$type]['levels'] = array(
      '#type' => 'checkboxes',
      '#default_value' => $selected_levels,
      '#options' => $levels,
    );

    $selected_levels[] = 'fallback';

    foreach($selected_levels as $level) {
      $form[$type][$level] = array(
        '#type' => 'fieldset',
        '#title' => ($level == 'fallback') ? t('fallback') : $levels[$level],
        '#collapsible' => TRUE,
        '#collapsed' => ($set[$level]['text']), // do not collapse for empty values
      );
      $form[$type][$level]['text'] = array(
        '#type' => 'textfield',
        '#title' => t('Text'),
        '#description' => t('This text will be used to present the date for the current mode.<br/> "@date" can be used to be replaced with the formatted date. For example: "<em>Today @date</em>".'),
        '#default_value' => $set[$level]['text'],
      );
       $form[$type][$level]['format'] = array(
        '#type' => 'textfield',
        '#title' => t('Format'),
        '#description' => t('Select a format the additional "@date" parameter will be formatted with. For example <em>"H:i"</em>. See php !date function for available values.', array('!date' => l('date()', 'http://php.net/manual/function.date.php'))),
        '#default_value' => $set[$level]['format'],
      );
    }
  }

  // Set form as fields in subarray
  $form = array(
    '#tree' => TRUE,
    'fields' => $form,
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
  );
  // Revert overwrites default submit function
  $form['revert'] = array(
    '#type' => 'submit',
    '#value' => t('Revert'),
    '#submit' => array('datetoday_admin_form_revert'),
  );
  return $form;
}

/**
 * Default validation function for datetoday_admin_form().
 */
function datetoday_admin_form_validate($form, &$form_state) {
  $clicked_button = current($form_state['clicked_button']['#parents']);
  // Do not validate for  revert button
  if ($clicked_button == 'revert') return ;

  $new = $form_state['values']['fields'];

  $setting = datetoday_settings();

  foreach ($new as $field => $set) {
    $old_set = $setting[$field];
    foreach ($set['levels'] as $level => $is) {
      if ($is && $old_set['levels'][$level] && !$set[$level]['text']) {
        form_set_error("fields][$field][$level][text", t('You have to set a value for %field - %level', array('%field' => $field, '%level' => $level)));
      }
      elseif($is && !$old_set['levels'][$level] && !$set[$level]['text']) {
        drupal_set_message(t('Be sure to set a value for %field - %level.',  array('%field' => $field, '%level' => $level)), 'warning');
      }
    }
  }
}

/**
 * Callback function for revert button.
 */
function datetoday_admin_form_revert() {
  variable_del('datetoday');
  drupal_set_message(t('Reverted datetoday settings to module default!'));
}

/**
 * Default submit function.
 */
function datetoday_admin_form_submit($form, &$form_state) {
  $new = $form_state['values']['fields'];
  variable_set('datetoday', $new);
}