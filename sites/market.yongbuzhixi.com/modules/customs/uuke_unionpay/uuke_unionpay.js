(function($){
	Drupal.behaviors.unionpayAutoSubmit = {
		attach: function(context, settings) {
		  $(document).ajaxComplete(function(event, xhr, settings) {
		  	if($('#uuke-unionpay-form--2')) {
		  		$('#uuke-unionpay-form--2').submit();
		  	}
			 
			});

		}

}
})(jQuery);
