(function($){
/**
 * To make a form auto submit, all you have to do is 3 things:
 *
 * ctools_add_js('auto-submit');
 *
 * Currently only 'select', 'radio', 'checkbox' and 'textfield' types are supported. We probably
 * could use additional support for HTML5 input types.
 */

Drupal.behaviors.PhotoAutoSubmit = {
  attach: function(context) {
	    $('#edit-field-photo input.form-file').change(function() {
	        var show = $(this).parent().find('button').mousedown();
	    });
	    $('#edit-field-photo .help-block').hide();
  }
}
})(jQuery);
