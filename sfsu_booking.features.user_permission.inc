<?php
/**
 * @file
 * sfsu_booking.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function sfsu_booking_user_default_permissions() {
  $permissions = array();

  // Exported permission: administer flags.
  $permissions['administer flags'] = array(
    'name' => 'administer flags',
    'roles' => array(),
    'module' => 'flag',
  );

  // Exported permission: create appointment content.
  $permissions['create appointment content'] = array(
    'name' => 'create appointment content',
    'roles' => array(
      0 => 'administrator',
      1 => 'host',
    ),
    'module' => 'node',
  );

  // Exported permission: delete any appointment content.
  $permissions['delete any appointment content'] = array(
    'name' => 'delete any appointment content',
    'roles' => array(
      0 => 'administrator',
      1 => 'full administrator',
      2 => 'host',
      3 => 'publisher',
    ),
    'module' => 'node',
  );

  // Exported permission: delete own appointment content.
  $permissions['delete own appointment content'] = array(
    'name' => 'delete own appointment content',
    'roles' => array(
      0 => 'administrator',
      1 => 'authenticated user',
      2 => 'full administrator',
      3 => 'host',
      4 => 'publisher',
    ),
    'module' => 'node',
  );

  // Exported permission: edit any appointment content.
  $permissions['edit any appointment content'] = array(
    'name' => 'edit any appointment content',
    'roles' => array(
      0 => 'administrator',
      1 => 'full administrator',
      2 => 'host',
      3 => 'publisher',
    ),
    'module' => 'node',
  );

  // Exported permission: edit own appointment content.
  $permissions['edit own appointment content'] = array(
    'name' => 'edit own appointment content',
    'roles' => array(
      0 => 'administrator',
      1 => 'authenticated user',
      2 => 'full administrator',
      3 => 'host',
      4 => 'publisher',
    ),
    'module' => 'node',
  );

  // Exported permission: use flag import.
  $permissions['use flag import'] = array(
    'name' => 'use flag import',
    'roles' => array(),
    'module' => 'flag',
  );

  return $permissions;
}
