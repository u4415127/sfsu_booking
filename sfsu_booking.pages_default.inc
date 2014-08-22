<?php
/**
 * @file
 * sfsu_booking.pages_default.inc
 */

/**
 * Implements hook_default_page_manager_pages().
 */
function sfsu_booking_default_page_manager_pages() {
  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'appointment_calendar';
  $page->task = 'page';
  $page->admin_title = 'Appointment Calendar';
  $page->admin_description = 'From sfsu_booking.
This is the only visible appointment calendar for users.';
  $page->path = 'booking/cal';
  $page->access = array(
    'plugins' => array(
      0 => array(
        'name' => 'role',
        'settings' => array(
          'rids' => array(
            0 => 2,
          ),
        ),
        'context' => 'logged-in-user',
        'not' => FALSE,
      ),
    ),
    'logic' => 'and',
  );
  $page->menu = array(
    'type' => 'normal',
    'title' => 'Appointment Calendar',
    'name' => 'main-menu',
    'weight' => '1',
    'parent' => array(
      'type' => 'none',
      'title' => '',
      'name' => 'navigation',
      'weight' => '0',
    ),
  );
  $page->arguments = array();
  $page->conf = array(
    'admin_paths' => FALSE,
  );
  $page->default_handlers = array();
  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'page_appointment_calendar_panel_context';
  $handler->task = 'page';
  $handler->subtask = 'appointment_calendar';
  $handler->handler = 'panel_context';
  $handler->weight = 0;
  $handler->conf = array(
    'title' => 'Panel',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => '',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
  );
  $display = new panels_display();
  $display->layout = 'omega_12_onecol';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'contentmain' => NULL,
      'middle' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '';
  $display->uuid = '718e17f0-c467-4c1a-b6d1-c4a19968eaa2';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-642ce894-9b3c-4a4f-86e9-b6156020a507';
    $pane->panel = 'middle';
    $pane->type = 'views_panes';
    $pane->subtype = 'booking_calendar-main_booking_cal';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'view_mode' => 'teaser',
      'widget_title' => NULL,
      'items_per_page' => NULL,
      'exposed' => array(
        'sort_by' => NULL,
        'sort_order' => NULL,
      ),
      'use_pager' => NULL,
      'pager_id' => NULL,
      'offset' => NULL,
      'link_to_view' => NULL,
      'more_link' => NULL,
      'path' => NULL,
      'view_settings' => 'fields',
      'header_type' => 'none',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '642ce894-9b3c-4a4f-86e9-b6156020a507';
    $display->content['new-642ce894-9b3c-4a4f-86e9-b6156020a507'] = $pane;
    $display->panels['middle'][0] = 'new-642ce894-9b3c-4a4f-86e9-b6156020a507';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['appointment_calendar'] = $page;

  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'appointment_calendar_day';
  $page->task = 'page';
  $page->admin_title = 'Appointment Calendar Day';
  $page->admin_description = 'From sfsu_booking.
This is a day calendar for admin';
  $page->path = 'booking/day';
  $page->access = array(
    'plugins' => array(
      0 => array(
        'name' => 'role',
        'settings' => array(
          'rids' => array(
            0 => 2,
          ),
        ),
        'context' => 'logged-in-user',
        'not' => FALSE,
      ),
    ),
    'logic' => 'and',
  );
  $page->menu = array(
    'type' => 'normal',
    'title' => 'Day calendar',
    'name' => 'main-menu',
    'weight' => '1',
    'parent' => array(
      'type' => 'none',
      'title' => '',
      'name' => 'navigation',
      'weight' => '0',
    ),
  );
  $page->arguments = array();
  $page->conf = array(
    'admin_paths' => FALSE,
  );
  $page->default_handlers = array();
  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'page_appointment_calendar_day_panel_context';
  $handler->task = 'page';
  $handler->subtask = 'appointment_calendar_day';
  $handler->handler = 'panel_context';
  $handler->weight = 0;
  $handler->conf = array(
    'title' => 'Panel',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => '',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
  );
  $display = new panels_display();
  $display->layout = 'omega_12_onecol';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'contentmain' => NULL,
      'middle' => NULL,
      'left' => NULL,
      'right' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '';
  $display->uuid = '42d45ff6-9880-4c01-b3ee-28342be416e5';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-9482a97f-2750-47c2-8a9a-0f366f06e5d4';
    $pane->panel = 'middle';
    $pane->type = 'views_panes';
    $pane->subtype = 'booking_calendar-admin_cal_day';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'view_mode' => 'teaser',
      'widget_title' => NULL,
      'items_per_page' => NULL,
      'exposed' => array(
        'sort_by' => NULL,
        'sort_order' => NULL,
      ),
      'use_pager' => NULL,
      'pager_id' => NULL,
      'offset' => NULL,
      'link_to_view' => NULL,
      'more_link' => NULL,
      'path' => NULL,
      'view_settings' => 'fields',
      'header_type' => 'none',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '9482a97f-2750-47c2-8a9a-0f366f06e5d4';
    $display->content['new-9482a97f-2750-47c2-8a9a-0f366f06e5d4'] = $pane;
    $display->panels['middle'][0] = 'new-9482a97f-2750-47c2-8a9a-0f366f06e5d4';
    $pane = new stdClass();
    $pane->pid = 'new-f422a94b-c69d-4804-bfd9-471732baa951';
    $pane->panel = 'middle';
    $pane->type = 'block';
    $pane->subtype = 'formblock-appointment';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 0,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = 'f422a94b-c69d-4804-bfd9-471732baa951';
    $display->content['new-f422a94b-c69d-4804-bfd9-471732baa951'] = $pane;
    $display->panels['middle'][1] = 'new-f422a94b-c69d-4804-bfd9-471732baa951';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['appointment_calendar_day'] = $page;

  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'appointment_calendar_week';
  $page->task = 'page';
  $page->admin_title = 'Appointment Calendar Week';
  $page->admin_description = 'From sfsu_booking.
This is a week calendar for admin.';
  $page->path = 'booking/week';
  $page->access = array(
    'plugins' => array(
      0 => array(
        'name' => 'role',
        'settings' => array(
          'rids' => array(
            0 => 2,
          ),
        ),
        'context' => 'logged-in-user',
        'not' => FALSE,
      ),
    ),
    'logic' => 'or',
  );
  $page->menu = array(
    'type' => 'normal',
    'title' => 'Week calendar',
    'name' => 'main-menu',
    'weight' => '1',
    'parent' => array(
      'type' => 'none',
      'title' => '',
      'name' => 'navigation',
      'weight' => '0',
    ),
  );
  $page->arguments = array();
  $page->conf = array(
    'admin_paths' => FALSE,
  );
  $page->default_handlers = array();
  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'page_appointment_calendar_week_panel_context';
  $handler->task = 'page';
  $handler->subtask = 'appointment_calendar_week';
  $handler->handler = 'panel_context';
  $handler->weight = 0;
  $handler->conf = array(
    'title' => 'Panel',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => '',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
  );
  $display = new panels_display();
  $display->layout = 'omega_12_onecol';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'contentmain' => NULL,
      'middle' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '';
  $display->uuid = '87ab5880-67c2-46ae-a764-ee731c279b75';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-a2b1fe0b-d4cc-404e-8c0b-372fb7ad67bf';
    $pane->panel = 'middle';
    $pane->type = 'views_panes';
    $pane->subtype = 'booking_calendar-admin_cal_week';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'path' => NULL,
      'view_mode' => 'teaser',
      'widget_title' => NULL,
      'items_per_page' => NULL,
      'exposed' => array(
        'sort_by' => NULL,
        'sort_order' => NULL,
      ),
      'use_pager' => NULL,
      'pager_id' => NULL,
      'offset' => NULL,
      'link_to_view' => NULL,
      'more_link' => NULL,
      'view_settings' => 'fields',
      'header_type' => 'none',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = 'a2b1fe0b-d4cc-404e-8c0b-372fb7ad67bf';
    $display->content['new-a2b1fe0b-d4cc-404e-8c0b-372fb7ad67bf'] = $pane;
    $display->panels['middle'][0] = 'new-a2b1fe0b-d4cc-404e-8c0b-372fb7ad67bf';
    $pane = new stdClass();
    $pane->pid = 'new-c389e8aa-572b-4bf7-a713-b0c0d931c539';
    $pane->panel = 'middle';
    $pane->type = 'block';
    $pane->subtype = 'formblock-appointment';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 0,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = 'c389e8aa-572b-4bf7-a713-b0c0d931c539';
    $display->content['new-c389e8aa-572b-4bf7-a713-b0c0d931c539'] = $pane;
    $display->panels['middle'][1] = 'new-c389e8aa-572b-4bf7-a713-b0c0d931c539';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['appointment_calendar_week'] = $page;

  return $pages;

}
