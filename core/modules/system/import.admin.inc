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
    '#submit' => array('system_import_settings_submit'),
  );

  return $form;
}

/**
 *
 */
function system_import_settings_submit(&$form, &$form_state) {
  //dpm(file_directory_path()); return;
  $filedir = config_get('system.core', 'file_public_path');
  dpm($filedir);
  $file = file_save_upload(
    'import-file',
    array('file_validate_extensions' => array('xml', 'json')),
    $filedir . '/'
  );
  //dpm($file);
  $realpath = backdrop_realpath($file->uri);
  dpm($realpath, 'realpath');
  $xml = xmlsimple_load_file($realpath);
  dpm($xml);
  // foreach ($xml->channel as $channel) {
  //   dpm($channel);
  // }
  // $xml = simplexml_load_file('/Users/geoff/bups/wp-export/wpexport.wordpress.2017-05-22.xml');
  // //$xml = backdrop_xml_parser_create($xml);
  // //dpm($xml);
  // var_dump($xml->channel[0]->title);
  // foreach ($xml->channel as $key => $channel) {
  //   //dpm($channel[$key]->title);
  //   var_dump($channel->title);
  // }
}
