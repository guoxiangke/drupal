<?php
// echo kprint_r($form);
echo drupal_render($form['title']);
echo drupal_render($form['field_date']);
?>
<div class="field-group-htabs-wrapper field-group-htabs group-rooms ">
  <h2 class="element-invisible">Rooms</h2>
  <a href="#" id="checkall">Check all</a>
  <div class="horizontal-tabs-panes">
    <?php foreach(taxonomy_get_tree(taxonomy_vocabulary_machine_name_load("resource_category")->vid) as $term): ?>
    <fieldset class="field-group-htab group-floor-<?php echo $term->tid;?> collapsible required-fields  form-wrapper" id="node_reservation_form_group_floor_<?php echo $term->tid;?>">
      <legend>
      <span class="fieldset-legend"><?php echo $term->name;?></span>
      </legend>
      <div class="fieldset-wrapper">
        <?php // echo $term->name;?>
      </div>
    </fieldset>
    <?php endforeach; ?>
  </div>
</div>
<?php
echo drupal_render_children($form);
?>
