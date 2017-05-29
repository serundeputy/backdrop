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

  // Prepare options array.
  foreach ($types as $type) {
    $type_options[$type->type] = $type->name;
  }

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

/**
 * Submit handler for system_export_settings().
 */
function system_export_settings_submit($form, &$form_state) {
  $query = db_select('node', 'n')
    ->fields('n', array('nid'));
  $or = db_or();
  if ($form_state['values']['content']) {
    foreach ($form_state['values']['content'] as $type) {
      if ($type) {
        $or->condition('type', $type);
      }
    }
  }
  $query->condition($or);
  $result = $query->orderBy('nid')->execute();
  $nids = [];
  foreach($result as $r) {
    $nids[] = $r->nid;
  }
  $nodes = node_load_multiple($nids);
  $content = json_encode($nodes);
  var_dump($content);

  backdrop_set_message('Export successful!');
}
