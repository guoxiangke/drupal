// $Id: sina_open.js,v 1.2 2011/02/11 03:52:44 eastcn Exp $

(function($) {
	Drupal.behaviors.saesms ={
		attach:function (context, settings) {			
			function c() {
				var _c = 65;
				var b = $('#edit-sms-text').val();
                               if (typeof(b) == "undefined") {
                               
                               }else{
                               	if (b.length < _c) {
					_c -= b.length;
				} else if (b.length > _c) {
					_c -= b.length;
					//
				} else {
					_c = 0;
				};
                               
                               }  
				
				
				$('#text_count_limits').text(_c);
			}
			c();
			$('#edit-sms-text').bind('keyup', c);
			$('#edit-sms-text').bind('mouseup', c);
		}		
		
	};
		
})(jQuery);