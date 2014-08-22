<?php
/**
 * @file
 * sfsu_booking.features.user_role.inc
 */

/**
 * Implements hook_user_default_roles().
 */
function sfsu_booking_user_default_roles() {
  $roles = array();

  // Exported role: host.
  $roles['host'] = array(
    'name' => 'host',
    'weight' => '4',
  );

  return $roles;
}
