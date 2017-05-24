<?php

/**
 * @file
 *  Import form to import content from another Backdrop or Wordpress site.
 */

/**
 * Callback function for /admin/config/import.
 */
function system_import_settings($form, &$form_state) {
  //$xml = simplexml_load_file('/Users/geoff/bups/wp-export/wpexport.wordpress.2017-05-22.xml');
  // var_dump($xml);
  // print_r($xml->channel->title);
  $form = array();
  $form['import'] = array(
    '#type' => 'fieldset',
    '#title' => t('Import Content'),
  );
  $form['import']['type-of-import'] = array(
    '#type' => 'select',
    '#title' => 'Source of import data:',
    '#description' => 'Select the source of the import i.e. the data came from a Backdrop site.',
    '#options' => array(
      'backdrop' => 'Backdrop CMS',
      'wordrpress' => 'WordPress',
    ),
  );
  $form['import']['import-file'] = array(
    '#type' => 'file',
    '#title' => 'Upload an XML or JSON file:',
    '#description' => 'Upload a file export from a Backdrop or WordPress content export.',
  );
  $form['import']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Import Content'),
    '#submit' => array(),
  );
  // dpm($xml);
  // dpm($xml->channel, 'channel');
  //print_r($xml->channel->item);
  $xml = simplexml_load_file('/Users/geoff/bups/wp-export/wpexport.wordpress.2017-05-22.xml');

  //dpm($content);
  //dpm($xml->channel);
  foreach ($xml->channel as $item) {
    dpm($item->title);
  }

  return $form;
}
