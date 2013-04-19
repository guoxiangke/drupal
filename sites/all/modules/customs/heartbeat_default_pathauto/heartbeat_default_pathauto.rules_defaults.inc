<?php

/**
 * Alter default rules configurations.
 *
 * The implementation should be placed into the file
 * MODULENAME.rules_defaults.inc, which gets automatically included when the
 * hook is invoked.
 *
 * @param $configs
 *   The default configurations of all modules as returned from
 *   hook_default_rules_configuration().
 *
 * @see hook_default_rules_configuration()
 */
function heartbeat_default_pathauto_default_rules_configuration_alter(&$configs) {
  // Add custom condition.
  //$configs['foo']->condition('bar');

  foreach ($configs as $name => $RulesReactionRule) {
  	# code...
  	if($RulesReactionRule->module == 'heartbeat_rules'){
  		dpm($configs);
  		$RulesReactionRule->active = FALSE;
  	}
  }
}