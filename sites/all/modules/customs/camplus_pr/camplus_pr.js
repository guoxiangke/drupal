 jQuery(function($){ // select change show notice.
 			$('#fgm_node_purchase_request_form_group_budgets-add-more-wrapper select').change(function(){
			  	if($(this).parents('.multiple-inline-element').find('.multiple-field-budget-items-amount input').attr('placeholder',Drupal.settings.camplus_pr[$(this).context.value])) {
			  		// $(this).parents('.fieldset-wrapper').prepend('<div id="op-notice" class="messages warning" style="display: block; ">* Please click \'Filter\' to see your changes, and if the filter button is not here: Please click \'Refine\' to see your changes.</div>');
			  		
			  	}
			});

	Drupal.behaviors.pr = {
		attach: function(context, settings) {
			$('#fgm_node_purchase_request_form_group_budgets-add-more-wrapper select').change(function(){
			  	if($(this).parents('.multiple-inline-element').find('.multiple-field-budget-items-amount input').attr('placeholder',Drupal.settings.camplus_pr[$(this).context.value])) {
			  	}
			});
		}
	}

});