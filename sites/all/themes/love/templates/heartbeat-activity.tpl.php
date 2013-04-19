<?php foreach ($content as $key => $value) {
	$$key = $value;
}?>

<div class="<?php print $classes;?>"<?php print $attributes; ?>>
	<div class="h-avatar"><?php print render($avatar); ?></div>
	<div class="h-main">
		<div class="h-content">
			<span class="h-msg"><?php print render($message); ?></span>
		</div>
		
		<div class="h-attachs">
			<?php print render($time ); ?>
			<span class="h-actions"><?php print render($buttons); ?></span>
		</div>
		<?php print render($attachments); ?>
	</div>
</div>