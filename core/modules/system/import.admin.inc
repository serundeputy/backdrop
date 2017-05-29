<?php

/**
 * @file
 * Import form to import content from another Backdrop or Wordpress site.
 */

/**
 * Callback function for /admin/config/import.
 */
function system_import_settings($form, &$form_state) {
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
 * Validate handler for system_import_settings().
 */
function system_import_settings_validate($form, &$form_state) {
  $file = file_save_upload('import-file', array(
    // // Validates file is really an image.
    // 'file_validate_is_image' => array(),f
    // Validate extensions.
    'file_validate_extensions' => array('xml', 'json'),
  ));

  // If the file passed validation:
  if ($file) {
    // Move the file into the backdrop file system.
    if ($file = file_move($file, 'public://')) {
      // Save the file for use in the submit handler.
      $form_state['storage']['import-file'] = $file;
    }
    else {
      form_set_error('import-file',
        t("Failed to write the uploaded file to the site's file folder.")
      );
    }
  }
  else {
    form_set_error('import-file', t('The import could not be completed.'));
  }
}

/**
 * Submit handler for the system_import_settings form.
 */
function system_import_settings_submit(&$form, &$form_state) {
  $file = $form_state['storage']['import-file'];
  // We are done with the file, remove it from storage.
  unset($form_state['storage']['import-file']);
  // Make the storage of the file permanent.
  $file->status = FILE_STATUS_PERMANENT;
  // Save file status.
  file_save($file);
  dpm($file);

  $real_path = backdrop_realpath($file->path['source']);
  dpm($real_path, 'real path');

  // Get the XML Data.
  $xml_data = simplexml_load_file($real_path);
  //dpm($xml_data, 'data');
  print_r($xml_data);

  foreach ($xml_data as $channel) {
    //dpm($channel->title, 'title');
    print_r($channel);
  }

 //  try {
 //   $xml = new SimpleXMLElement($xml_data);
 // }
 // catch (Exception $e) {
 //   // SimpleXMLElement::__construct produces an E_WARNING error message for
 //   // each error found in the XML data and throws an exception if errors
 //   // were detected. Catch any exception and return failure (NULL).
 //   return;
 // }

 dpm($xml, 'xml');

  // Set a response to the user.
  backdrop_set_message(
    t(
      'The import has been saved, filename: @filename. Check the /admin/content
      page for a listing of content',
      array('@filename' => $file->filename)
    )
  );
}
