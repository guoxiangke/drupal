(function($){
Drupal.behaviors.uukepad = {
 //  attach: function(context) {
	//   	$('a[href$=".apk"]').click(function(e) {
	//   		e.preventDefault();
	// 			console.log('android give me whether this app was installed?');
	// 			if(isInstall(app_id)) {
	// 				window.open($(this).attr('href'),'download');
	// 			}
	// 		});
	//   }
	// }
	// function isInstall(app_id)
	// {
	// 	return true;
	// }
	function disableAppInstallButton()
	{

	  	$('.ui-content a[href$=".apk"]').addClass('ui-disabled');
		// $(' a[href$=".apk"]').click(function(e) {
	 //  		e.preventDefault();
	 //  		$('this').addClass('ui-disabled');
		// 		console.log('disableAppInstallButton');
		// 	});
	}
	
})(jQuery);

