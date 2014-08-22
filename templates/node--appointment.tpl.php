<?php

/**
 * @file
 * Bartik's theme implementation to display a node.
 *
 * Available variables:
 * - $title: the (sanitized) title of the node.
 * - $content: An array of node items. Use render($content) to print them all,
 *   or print a subset such as render($content['field_example']). Use
 *   hide($content['field_example']) to temporarily suppress the printing of a
 *   given element.
 * - $user_picture: The node author's picture from user-picture.tpl.php.
 * - $date: Formatted creation date. Preprocess functions can reformat it by
 *   calling format_date() with the desired parameters on the $created variable.
 * - $name: Themed username of node author output from theme_username().
 * - $node_url: Direct url of the current node.
 * - $display_submitted: Whether submission information should be displayed.
 * - $submitted: Submission information created from $name and $date during
 *   template_preprocess_node().
 * - $classes: String of classes that can be used to style contextually through
 *   CSS. It can be manipulated through the variable $classes_array from
 *   preprocess functions. The default values can be one or more of the
 *   following:
 *   - node: The current template type, i.e., "theming hook".
 *   - node-[type]: The current node type. For example, if the node is a
 *     "Blog entry" it would result in "node-blog". Note that the machine
 *     name will often be in a short form of the human readable label.
 *   - node-teaser: Nodes in teaser form.
 *   - node-preview: Nodes in preview mode.
 *   The following are controlled through the node publishing options.
 *   - node-promoted: Nodes promoted to the front page.
 *   - node-sticky: Nodes ordered above other non-sticky nodes in teaser
 *     listings.
 *   - node-unpublished: Unpublished nodes visible only to administrators.
 * - $title_prefix (array): An array containing additional output populated by
 *   modules, intended to be displayed in front of the main title tag that
 *   appears in the template.
 * - $title_suffix (array): An array containing additional output populated by
 *   modules, intended to be displayed after the main title tag that appears in
 *   the template.
 *
 * Other variables:
 * - $node: Full node object. Contains data that may not be safe.
 * - $type: Node type, i.e. story, page, blog, etc.
 * - $comment_count: Number of comments attached to the node.
 * - $uid: User ID of the node author.
 * - $created: Time the node was published formatted in Unix timestamp.
 * - $classes_array: Array of html class attribute values. It is flattened
 *   into a string within the variable $classes.
 * - $zebra: Outputs either "even" or "odd". Useful for zebra striping in
 *   teaser listings.
 * - $id: Position of the node. Increments each time it's output.
 *
 * Node status variables:
 * - $view_mode: View mode, e.g. 'full', 'teaser'...
 * - $teaser: Flag for the teaser state (shortcut for $view_mode == 'teaser').
 * - $page: Flag for the full page state.
 * - $promote: Flag for front page promotion state.
 * - $sticky: Flags for sticky post setting.
 * - $status: Flag for published status.
 * - $comment: State of comment settings for the node.
 * - $readmore: Flags true if the teaser content of the node cannot hold the
 *   main body content.
 * - $is_front: Flags true when presented in the front page.
 * - $logged_in: Flags true when the current user is a logged-in member.
 * - $is_admin: Flags true when the current user is an administrator.
 *
 * Field variables: for each field instance attached to the node a corresponding
 * variable is defined, e.g. $node->body becomes $body. When needing to access
 * a field's raw values, developers/themers are strongly encouraged to use these
 * variables. Otherwise they will have to explicitly specify the desired field
 * language, e.g. $node->body['en'], thus overriding any language negotiation
 * rule that was previously applied.
 *
 * @see template_preprocess()
 * @see template_preprocess_node()
 * @see template_process()
 */
//dsm($content);

  global $user;
  $current_user_is_host = (isset($content['field_user_host']) && $user->uid == $content['field_user_host']['#items'][0]['uid']) ? TRUE:FALSE;
  $current_user_is_guest = (isset($content['field_user_guest']) && $user->uid == $content['field_user_guest']['#items'][0]['uid'])?
                           TRUE:FALSE;
                           
  if(isset($content['field_time'])){
    $appt_date = new DateTime($content['field_time']['#items'][0]['value'], new DateTimeZone($content['field_time']['#items'][0]['timezone_db']));
    $now = new DateTime('now', new DateTimeZone('UTC'));
    $expired = ($appt_date < $now)? TRUE:FALSE;    
  }

  
  $display_guest_info = ($is_admin || $current_user_is_host || $current_user_is_guest)? TRUE:FALSE;
?>

<article id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?> clearfix"<?php print $attributes; ?> role="article">

  <?php print render($title_prefix); ?>
  <?php if (!$page): ?>
    <h2<?php print $title_attributes; ?>>
      <a href="<?php print $node_url; ?>"><?php print $title; ?></a>
    </h2>
  <?php endif; ?>
  <?php print render($title_suffix); ?>

  <?php if ($display_submitted): ?>
    <footer class="meta submitted">
      <?php print $user_picture; ?>
      <?php print $submitted; ?>
    </footer>
  <?php endif; ?>

  <div class="content clearfix"<?php print $content_attributes; ?>>
    <?php
      // We hide the comments and links now so that we can render them later.
      hide($content['comments']);
      hide($content['links']);
//      print render($content);   //trying using this when theme is fixed
    ?>
    <?php if(isset($content['field_time'])): ?>
      <div class="field field-label-inline clearfix">
        <div class="field-label">Time:&nbsp;</div>
        <div class="field-items even"><?php print $content['field_time'][0]['#markup']; ?></div>      
      </div>
    <?php endif; ?>  

    <?php if(isset($content['field_location'])): ?>
      <div class="field field-label-inline clearfix">
        <div class="field-label">Location:&nbsp;</div>
        <div class="field-items even"><?php print $content['field_location'][0]['#markup']; ?></div>      
      </div>
    <?php endif; ?>
    
    <?php if(isset($content['field_user_host'])): ?>
      <div class="field field-label-inline clearfix">
        <div class="field-label">Host:&nbsp;</div>
        <div class="field-items even"><?php print $content['field_user_host'][0]['#title']; ?></div>      
      </div>
    <?php endif; ?>
    
    <?php if(isset($content['field_status'])): ?>
      <div class="field field-label-inline clearfix">
        <div class="field-label">Status:&nbsp;</div>
        <div class="field-items even"><?php print ($expired)?'Expired':$content['field_status'][0]['#markup']; ?></div>
      </div>
    <?php endif; ?>

    <?php if (user_access('administer booking features')): ?>
    <?php if($logged_in && isset($content['field_user_guest'])): ?>
      <br />
      <div class="field field-label-inline clearfix">
        <div class="field-label">Guest:&nbsp;</div>
        <div class="field-items even"><?php print $content['field_user_guest'][0]['#title']; ?></div>      
      </div>
      <?php if(isset($content['comments']['comments'])): ?>
        <?php foreach ($content['comments']['comments'] as $key => $value): ?>
          <?php
            if(!is_numeric($key)){
              continue;
            }
          ?>
          <div class="field field-label-inline clearfix">
            <div class="field-label">Phone Number:&nbsp;</div>
            <div class="field-items even">
              <?php print $value['field_phone_number'][0]['#markup']; ?>
            </div>      
          </div>    
          <div class="field field-label-inline clearfix">
            <div class="field-label">Purpose:&nbsp;</div>
            <div class="field-items even">
              <?php print $value['comment_body'][0]['#markup']; ?>
            </div>      
          </div>
          <div class="field field-label-inline clearfix">
              <?php print render($value['field_item_list']); ?>
          </div>
          <div class="field field-label-inline clearfix">
           <br/>
           <br/>
              <?php print '<a href="'.url('comment/'.$key.'/edit',array('absolute'=>TRUE)).'" title="Edit Appointment" class="flag unflag-action flag-link-confirm">Edit appointment<a>'; ?>
          </div>
        <?php endforeach; ?>
      <?php endif; ?>  
    <?php endif; ?>
    <?php endif; ?>

    <br />
    <?php
    $path = current_path();
    if(isset($content['links']['flag']) && !$expired && !strstr($path, 'comment')){
      foreach ($content['links']['flag']['#links'] as $key => $value){
        if(!strstr($value['title'], 'Cancel') || user_access('administer booking features') || $current_user_is_guest){
          print $value['title'];
        }
      }
    }   
    ?>
  </div>

</article>
