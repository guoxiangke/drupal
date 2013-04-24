
if (Drupal.jsEnabled) {
  $(document).ready(function () {
		$("#toggle_index").click(function () {
			if($("#c_index").attr('style')=='display: none;'||$("#c_index").attr('style')=='display: none; ')
				{$("#c_index").slideDown('slow'); 
				//$("#toggle_index a").after('¡ý');
				}
			else
				{$("#c_index").slideUp('slow');
				//$("#toggle_index a").after('¡ü');
				}
		});
	});
}