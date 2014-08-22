<?php
/**
 * @file
 * Template to display a view as a calendar day, grouped by time
 * and optionally organized into columns by a field value.
 * 
 * @see template_preprocess_calendar_day.
 *
 * $rows: The rendered data for this day.
 * $rows['date'] - the date for this day, formatted as YYYY-MM-DD.
 * $rows['datebox'] - the formatted datebox for this day.
 * $rows['empty'] - empty text for this day, if no items were found.
 * $rows['all_day'] - an array of formatted all day items.
 * $rows['items'] - an array of timed items for the day.
 * $rows['items'][$time_period]['hour'] - the formatted hour for a time period.
 * $rows['items'][$time_period]['ampm'] - the formatted ampm value, if any for a time period.
 * $rows['items'][$time_period][$column]['values'] - An array of formatted 
 *   items for a time period and field column.
 * 
 * $view: The view.
 * $columns: an array of column names.
 * $min_date_formatted: The minimum date for this calendar in the format YYYY-MM-DD HH:MM:SS.
 * $max_date_formatted: The maximum date for this calendar in the format YYYY-MM-DD HH:MM:SS.
 * 
 * The width of the columns is dynamically set using <col></col> 
 * based on the number of columns presented. The values passed in will
 * work to set the 'hour' column to 10% and split the remaining columns 
 * evenly over the remaining 90% of the table.
 */
//dsm('Display: '. $display_type .': '. $min_date_formatted .' to '. $max_date_formatted);
//dsm($rows);
/*
 <a href="#" 
  onclick="javascript:printContent('calendar-week-view','Calendar week view', '<?php print $GLOBALS['base_url'] ?>/', new Array(<?php print $css_array ?>))" 
  >Print View</a>

drupal_add_js(drupal_get_path('module', 'sfsu_booking') . '/scripts/scripts.js');         
*/  

if(empty($rows['items'])){
  print '<div class=calendar-no-results-text><h4>No time slots for the selected day</h4></div>';
  return;  
}

// get system short time format
$system_time_format = variable_get('date_format_short', 'm/d/Y - H:i');
$system_time_format = substr($system_time_format, strpos($system_time_format, ':') - 1);
$meridian = strstr($system_time_format, 'a');
if(!$meridian){
  $meridian = strstr($system_time_format, 'A');
}
if($meridian){
  $system_time_format = str_replace($meridian,'', $system_time_format);
}


// construct time from 8am to 5pm
$slot_length = variable_get('sfsu_booking_time_slot_length', 30);
$time_1 = new DateTime('08:00:00');
$time_2 = new DateTime('16:30:00');
$noon = new DateTime('12:00:00');

$all_time = array();
while($time_1 <= $time_2){
        $all_time[$time_1->format('H:i:s')] = array('ampm'=> ($meridian ? $time_1->format($meridian) : ''),
                                                'hour'=> $time_1->format($system_time_format),
                                                'time'=> $time_1->format('H:i:s'),
                                               );
  $time_1->modify("+$slot_length min");                             
}
  
foreach ($rows['items'] as $key => $value) {
    $hour = substr($key, 0, strpos($key, ':')) . ':00:00';
    $hour = array_key_exists($key, $all_time)? $key : $hour;
  
  if(empty($all_time[$hour]['values'])){
        $all_time[$hour]['values'] = array('items'=>array());
  }
  $all_time[$hour]['values'] = array_merge_recursive($all_time[$hour]['values'], $value['values']);
}

?>
<div class="calendar-calendar">
<div class="calendar-calendar">
  <?php if(!stristr(request_uri(), 'booking/cal')): ?>
  <div id="calendar-aux-links" class="links">
      <div class="feed-icon">
        <a href="all/appt.ics" class="ical-icon" title="ical"><img id="ical-icon" typeof="foaf:Image" src="<?php print $GLOBALS['base_url'] . '/'. drupal_get_path('module', 'date_ical')?>/images/ical-feed-icon-34x14.png" alt="feed-icon" title="Add to calendar"></a>
      </div>
      <div class="print-view">
        <a href="print" target="_blank">Print View</a>
      </div>
  </div>
  <?php endif; ?>
  <div id="calendar-day-view" class="day-view">
    <table class="full">
      <col width="<?php print $first_column_width?>"></col>
      <thead>
        <?php foreach ($columns as $column): ?>
        <col width="<?php print $column_width; ?>%"></col>
        <?php endforeach; ?>
        <tr>
          <th class="calendar-dayview-hour"><?php print $by_hour_count > 0 ? t('Time') : ''; ?></th>
          <?php foreach ($columns as $column): ?>
          <th class="calendar-agenda-items"><?php print $column; ?></th>
          <?php endforeach; ?>
        </tr>
      </thead>
      <tbody>
    
        
        <?php foreach ($all_time as $hour): ?>
        <tr>
          <td class="calendar-agenda-hour">
            <span class="calendar-hour"><?php print $hour['hour']; ?></span><span class="calendar-ampm"><?php print $hour['ampm']; ?></span>
          </td>
          <?php foreach ($columns as $column): ?>
            <td class="calendar-agenda-items single-day">
              <div class="calendar">
              <div class="inner">
                <?php print isset($hour['values'][$column]) ? implode($hour['values'][$column]) : '&nbsp;'; ?>
              </div>
              </div>
            </td>
          <?php endforeach; ?>   
        </tr>
       <?php endforeach; ?>   
      </tbody>
    </table>
  </div>
</div>
