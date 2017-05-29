<?php

/**
 * @file
 * Import form to import content from another Backdrop or Wordpress site.
 */

/**
 * Callback function for /admin/config/import.
 */
function system_export_settings($form, &$form_state) {
  $form = array();
  $form['export'] = array(
    '#type' => 'fieldset',
    '#title' => t('Export Content'),
  );
  $types = node_type_get_types();
  foreach ($types as $type) {
    $type_options[$type->type] = $type->name;
  }
  dpm($types);
  $form['export']['content'] = array(
    '#type' => 'checkboxes',
    '#options' => $type_options,
    '#attributes' => array(
      'checked' => 'checked',
    ),
    '#default_value' => array_keys($type_options),
    '#description' => t('Check the content types you would like to export.'),
  );
  $form['export']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Export Content'),
    '#attributes' => array(
      'class' => array('button-primary'),
    ),
    '#submit' => array('system_export_settings_submit'),
  );

  return $form;
}
