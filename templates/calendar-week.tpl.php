<?php
/**
 * @file
 * Template to display a view as a calendar week.
 * 
 * @see template_preprocess_calendar_week.
 *
 * $day_names: An array of the day of week names for the table header.
 * $rows: The rendered data for this week.
 * 
 * For each day of the week, you have:
 * $rows['date'] - the date for this day, formatted as YYYY-MM-DD.
 * $rows['datebox'] - the formatted datebox for this day.
 * $rows['empty'] - empty text for this day, if no items were found.
 * $rows['all_day'] - an array of formatted all day items.
 * $rows['items'] - an array of timed items for the day.
 * $rows['items'][$time_period]['hour'] - the formatted hour for a time period.
 * $rows['items'][$time_period]['ampm'] - the formatted ampm value, if any for a time period.
 * $rows['items'][$time_period]['values'] - An array of formatted items for a time period.
 * 
 * $view: The view.
 * $min_date_formatted: The minimum date for this calendar in the format YYYY-MM-DD HH:MM:SS.
 * $max_date_formatted: The maximum date for this calendar in the format YYYY-MM-DD HH:MM:SS.
 * 
 */
//dsm('Display: '. $display_type .': '. $min_date_formatted .' to '. $max_date_formatted);
//dsm($rows);
//dsm($rows);
//dsm($day_names);
//dsm($vars);
//dsm(get_defined_vars());
///dvm($rows);
//dsm($items);
//<?php print $GLOBALS['base_url'] . '/'. drupal_get_path('module','calendar').'/css/calendar_multiday.css' ?\>
/*
 <a href="#" 
  onclick="javascript:printContent('calendar-week-view','Calendar week view', '<?php print $GLOBALS['base_url'] ?>/', new Array(<?php print $css_array ?>))" 
  >Print View</a>

drupal_add_js(drupal_get_path('module', 'sfsu_booking') . '/scripts/scripts.js');
$css_array = "'" . drupal_get_path('module', 'calendar') . "/css/calendar_multiday.css'," . 
             "'" . drupal_get_path('module', 'calendar') . "/css/calendar.css'," .
             "'" . drupal_get_path('module', 'sfsu_booking') . "/css/sfsu_booking.css'";           
*/             

if(empty($items)){
  print '<div class=calendar-no-results-text><h4>No time slots for the selected week</h4></div>';
  return;
}


$all_time = sfsu_booking_templ_processor($items);

$index = 0;
$header_ids = array();
foreach ($day_names as $key => $value) {
  $header_ids[$key] = $value['header_id'];
}
?>
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
<div id="calendar-week-view" class="week-view">
<table class="full">
  <caption class=accessiblity-only>Internal Audit - Appointment Calendar</caption>
  <thead>
    <tr>
      <?php if($by_hour_count > 0 || !empty($start_times)) :?>
      <th class="calendar-agenda-hour"><?php print t('Time')?></th>
      <?php endif;?>
      <?php foreach ($day_names as $cell): ?>
        <?php if(stristr($cell['header_id'], 'Sunday') ||  stristr($cell['header_id'], 'Saturday')): ?>
          <?php continue; ?>
        <?php endif ?>
        <th class="<?php print $cell['class']; ?>" id="<?php print $cell['header_id']; ?>">
          <?php print $cell['data']; ?>
        </th>
      <?php endforeach; ?>
    </tr>
  </thead>
  <tbody>
    <?php for ($i = 0; $i < $multiday_rows; $i++): ?>
    <?php 
      $colpos = 0; 
      $rowclass = "all-day";
      if( $i == 0) {
        $rowclass .= " first";
      }
      if( $i == $multiday_rows - 1) {
        $rowclass .= " last";
      }
    ?>
    <tr class="<?php print $rowclass?>">
      <?php if($i == 0 && ($by_hour_count > 0 || !empty($start_times))) :?>
      <td class="<?php print $agenda_hour_class ?>" rowspan="<?php print $multiday_rows?>">
        <span class="calendar-hour"><?php print t('All day', array(), array('context' => 'datetime'))?></span>
      </td>
      <?php endif; ?>
      <?php for($j = 0; $j < 6; $j++): ?>
        <?php $cell = (empty($all_day[$j][$i])) ? NULL : $all_day[$j][$i]; ?>
        <?php if($cell != NULL && $cell['filled'] && $cell['wday'] == $j): ?>
          <?php for($k = $colpos; $k < $cell['wday']; $k++) : ?>
          <td class="multi-day no-entry"><div class="inner">&nbsp;</div></td>
          <?php endfor;?>
          <td colspan="<?php print $cell['colspan']?>" class="multi-day">
            <div class="inner">
            <?php print $cell['entry']?>
            </div>
          </td>
          <?php $colpos = $cell['wday'] + $cell['colspan']; ?>
        <?php endif; ?>
      <?php endfor; ?>  
      <?php for($j = $colpos; $j < 7; $j++) : ?>
      <td class="multi-day no-entry"><div class="inner">&nbsp;</div></td>
      <?php endfor;?>
    </tr>
    <?php endfor; ?>
    
    <?php
    
      foreach($all_time as $time){  
        if(isset($time['values'])){
            print '<tr class="not-all-day">';
            print ' <th class="calendar-agenda-hour">';
            print '   <span class="calendar-hour">' . $time['hour'] . '</span><span class="calendar-ampm">' . $time['ampm'] . '</span>';
            print ' </td>';
              $curpos = 1;
              foreach ($columns as $index => $column){
                if(stristr($header_ids[$index], 'Sunday') ||  stristr($header_ids[$index], 'Saturday')){
                  continue;
                }
                $colpos = (isset($time['values'][$column][0])) ? $time['values'][$column][0]['wday'] : $index;
                for ($i = $curpos; $i < $colpos; $i++){
                  print '<td class="calendar-agenda-items single-day">';
                    print '<div class="calendar">';
                      print '<div class="inner">&nbsp;</div>';
                    print '</div>';
                  print '</td>';
                }//for
                $curpos = $colpos + 1;
                print '<td class="calendar-agenda-items single-day ' . $header_ids[$index] . '" headers="' . $header_ids[$index] . '">';
                  print '<div class="calendar">';
                    print '<div class="inner">';
                    if(!empty($time['values'][$column])){
                      foreach($time['values'][$column] as $item){
                        if(preg_match('/<a.*">(.*Expired.*)<\/a>/', $item['entry'], $match)){
                          $item['entry'] = str_replace($match[0], $match[1], $item['entry']);
                        }
                        print $item['entry'];
                      }//foreach
                    }//if
                    print '</div>';
                  print '</div>';
                print '</td>';
              }//foreach   
              for ($i = $curpos; $i < 5; $i++){
                print '<td class="calendar-agenda-items single-day">';
                  print '<div class="calendar">';
                    print '<div class="inner">&nbsp;</div>';
                  print '</div>';
                print '</td>';
              }   
            
        }
        else{ // print empty time
            print '<tr class="not-all-day">';
            print ' <th class="calendar-agenda-hour">';
            print '   <span class="calendar-hour">' . $time['hour'] . '</span><span class="calendar-ampm">' . $time['ampm'] . '</span>';
            print ' </td>';
            for ($i = 0; $i < 5; $i++){
              print '<td class="calendar-agenda-items single-day">';
                print '<div class="calendar">';
                  print '<div class="inner">&nbsp;</div>';
                print '</div>';
              print '</td>';
            }
         }//if-else

         print '</tr>';             
        
      }//foreach
    
    ?>
   
  </tbody>
</table>
</div></div>
