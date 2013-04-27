(function($){
	// $('#uuke-paylink-form').submit();
	Drupal.behaviors.YourBehaviour = {
		attach: function(context, settings) {  
	  	// $('#uuke-paylink-form').ajaxComplete(function(event, xhr, settings) {
		  //    console.log('finished');
		  //    // $(this).submit();
		  //    // $('#uuke-paylink-form').submit();
		  // });
		  $(document).ajaxComplete(function(event, xhr, settings) {
		  	if($('#uuke-unionpay-form--2')) {
		  		$('#uuke-unionpay-form--2').submit();
		  	}
			 
			});

		}

}
// $('#edit-alipay-link').click(function(e){
// 	e.preventdefault();
// })
// $.fn.autoSubmitUnionpay = function(){
// 	console.log('autoSubmitUnionpay');
// 	console.log($('#uuke-paylink-form--2'));
// 	// $('#uuke-paylink-form').submit();
// };

})(jQuery);
