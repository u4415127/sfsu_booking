<?php

if(stristr(request_uri(), 'booking/all')){
  $guest = user_load($node->field_user_guest['und']['0']['uid']);
  
  print 'Guest: ';
  if(isset($guest->field_firstname['und']) && isset($guest->field_lastname['und'])){
    print $guest->field_firstname['und'][0]['value'] . ' ' . $guest->field_lastname['und'][0]['value'] . "\n";
  }
  else{
    print 'N/A' . "\n";
  }
  print 'SFSU ID: ' . $guest->name . "\n";
  print 'Email: ' . $guest->mail . "\n";
  
  $comment = comment_load($node->cid); 
  print 'Phone Number: ' . $comment->field_phone_number['und'][0]['safe_value'] . "\n";
  print 'Purpose: ' . $comment->comment_body['und'][0]['safe_value'] . "\n";
}
else{
  $host = user_load($node->field_user_host['und']['0']['uid']);
  print 'Host: ' . $host->field_firstname['und'][0]['value'] . ' ' . $host->field_lastname['und'][0]['value'];
}

?>
