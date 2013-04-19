(function ($) {

/**
 * Move a block in the blocks table from one region to another via select list.
 *
 * This behavior is dependent on the tableDrag behavior, since it uses the
 * objects initialized in that behavior to update the row.
 */
Drupal.behaviors.groupsDrag = {
  attach: function (context, settings) {
    $('.locked .tabledrag-handle').hide();
    $('.tabledrag-toggle-weight-wrapper').hide();

   
  $('#op-warning').hide();
  $('.op-warning').click(function(){
  	if($('#op-warning').html() == 'Operate Message'){
  		$('#op-warning').html('* Changes made in this table will not be saved until the form is submitted by clicking on "Confirm settings".').show();
  	}
  });


  }
}
})(jQuery);
