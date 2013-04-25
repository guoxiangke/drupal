(function ($) {
  Drupal.behaviors.approverLogics = {
    attach: function(context, settings) {
      // alert('a');

      //add required class and *, as it only shows when "Need approver" is checked
      $('#edit-field-approver label').append('<span class="form-required" title="This field is required.">*</span>');
      $('#edit-field-approver-und').addClass('required');

      //default hide approver field, only shows when "Need approval" is checked
      if(!$('#edit-field-need-approval-und:checked').length) {
          $('#edit-field-approver').hide();
      }
      $('#edit-field-need-approval-und').change(function(){
          $('#edit-field-approver').slideToggle();
      });

      //add required class and *, as it only shows when "Venue" is checked
      $('#edit-field-resource-category label').append('<span class="form-required" title="This field is required.">*</span>');
      $('#edit-field-resource-category-und').addClass('required');

      if($('#edit-field-resource-type-und').val()!=settings.tabbed_room_selector.resource_type_venue_term.tid) {
        $('#edit-field-resource-category').hide();
      }

      $('#edit-field-resource-type-und').change(function() {
        if($('#edit-field-resource-type-und').val()!=settings.tabbed_room_selector.resource_type_venue_term.tid) {
          $('#edit-field-resource-category').slideUp();
        } else {
          $('#edit-field-resource-category').slideDown();
        }
      });

    }
  }
})(jQuery);
