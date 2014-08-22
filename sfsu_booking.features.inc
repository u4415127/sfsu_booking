<?php
/**
 * @file
 * sfsu_booking.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function sfsu_booking_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "context" && $api == "context") {
    return array("version" => "3");
  }
  list($module, $api) = func_get_args();
  if ($module == "page_manager" && $api == "pages_default") {
    return array("version" => "1");
  }
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function sfsu_booking_views_api() {
  return array("version" => "3.0");
}

/**
 * Implements hook_flag_default_flags().
 */
function sfsu_booking_flag_default_flags() {
  $flags = array();
  // Exported flag: "Appointment Booking".
  $flags['appointment_booking'] = array(
    'content_type' => 'node',
    'title' => 'Appointment Booking',
    'global' => '1',
    'types' => array(
      0 => 'appointment',
    ),
    'flag_short' => 'Book time slot',
    'flag_long' => '',
    'flag_message' => '',
    'unflag_short' => 'Cancel appointment',
    'unflag_long' => '',
    'unflag_message' => '',
    'unflag_denied_text' => 'now allowed',
    'link_type' => 'confirm',
    'roles' => array(
      'flag' => array(
        0 => '2',
        1 => '3',
        2 => '4',
        3 => '9',
        4 => '5',
        5 => '6',
        6 => '7',
        7 => '8',
      ),
      'unflag' => array(
        0 => '2',
        1 => '3',
        2 => '4',
        3 => '9',
        4 => '5',
        5 => '6',
        6 => '7',
        7 => '8',
      ),
    ),
    'weight' => 0,
    'show_on_form' => 0,
    'access_author' => '',
    'show_on_page' => 1,
    'show_on_teaser' => 0,
    'show_contextual_link' => FALSE,
    'i18n' => 0,
    'flag_confirmation' => 'Do you want to book this time slot? If so, please click the button below and fill out the form on the next page.',
    'unflag_confirmation' => 'Are you sure that you want to cancel this appointment?',
    'module' => 'sfsu_booking',
    'locked' => array(
      0 => 'name',
    ),
    'api_version' => 2,
  );
  return $flags;

}

/**
 * Implements hook_node_info().
 */
function sfsu_booking_node_info() {
  $items = array(
    'appointment' => array(
      'name' => t('Appointment'),
      'base' => 'node_content',
      'description' => t('A custom type created and managed by Features -- sfsu_booking'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
