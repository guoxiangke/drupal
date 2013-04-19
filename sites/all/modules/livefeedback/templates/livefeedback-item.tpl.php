<?php
/**
 * @file
 * This file defines the template for a single feedback item. Available
 * variables:
 *
 *   $content->id         - The database row ID.
 *   $content->message    - The message sent by the user.
 *   $content->url        - The URL the feedback was provided on.
 *   $content->date       - The date the feedback was sent, in the format
 *                          Y m d - H:ia.
 *   $content->data       - The user's browser info submitted with the image.                     
 *   $content->created    - The timestamp used to generate $content->date.
 *   $content->image_url  - The URL to the screenshot associated with this
 *                          feedback.
 *   $content->image_link - An HTML link to the full size image.
 *   $content->image      - The rendered image of the screenshot.
 *   $content->uid        - The user ID of the feedback user.
 *   $content->user       - The username of the feedback user.
 */
?>
<h2>Feedback</h2>
<h4>User's message</h4>
<p><?php print $content->message ?></p>
<dl>
  <dt>URL</dt>
  <dd><?php print l($content->url, $content->url) ?></dd>
  <dt>Date</dt>
  <dd><?php print $content->date ?></dd>
  <dt>User</dt>
  <dd><?php print l($content->user, 'user/' . $content->uid) ?></dd>
</dl>
<p><?php print $content->image ?></p>
<p><?php print $content->image_link ?></p>
<h4>Browser info</h4>
<dl>
  <?php foreach ($content->data as $key => $value) { ?>
  <dt><?php print $key; ?>:</dt>
  <dd><?php print $value; ?></dd>
  <?php } ?>
</dl>