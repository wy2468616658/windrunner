DROP TABLE IF EXISTS smart_scripts;
CREATE TABLE `smart_scripts` (
  `entryorguid` mediumint(11) NOT NULL,
  `source_type` mediumint(5) unsigned NOT NULL DEFAULT '0',
  `id` mediumint(11) unsigned NOT NULL DEFAULT '0',
  `link` mediumint(11) unsigned NOT NULL DEFAULT '0',
  `event_type` mediumint(5) unsigned NOT NULL DEFAULT '0',
  `event_phase_mask` mediumint(11) unsigned NOT NULL DEFAULT '0',
  `event_chance` mediumint(5) unsigned NOT NULL DEFAULT '100',
  `event_flags` mediumint(11) unsigned NOT NULL DEFAULT '0',
  `event_param1` mediumint(11) unsigned NOT NULL DEFAULT '0',
  `event_param2` mediumint(11) unsigned NOT NULL DEFAULT '0',
  `event_param3` mediumint(11) unsigned NOT NULL DEFAULT '0',
  `event_param4` mediumint(11) unsigned NOT NULL DEFAULT '0',
  `action_type` mediumint(5) unsigned NOT NULL DEFAULT '0',
  `action_param1` mediumint(11) unsigned NOT NULL DEFAULT '0',
  `action_param2` mediumint(11) unsigned NOT NULL DEFAULT '0',
  `action_param3` mediumint(11) unsigned NOT NULL DEFAULT '0',
  `action_param4` mediumint(11) unsigned NOT NULL DEFAULT '0',
  `action_param5` mediumint(11) unsigned NOT NULL DEFAULT '0',
  `action_param6` mediumint(11) unsigned NOT NULL DEFAULT '0',
  `target_type` mediumint(11) unsigned NOT NULL DEFAULT '0',
  `target_param1` mediumint(11) unsigned NOT NULL DEFAULT '0',
  `target_param2` mediumint(11) unsigned NOT NULL DEFAULT '0',
  `target_param3` mediumint(11) unsigned NOT NULL DEFAULT '0',
  `target_x` float NOT NULL DEFAULT '0',
  `target_y` float NOT NULL DEFAULT '0',
  `target_z` float NOT NULL DEFAULT '0',
  `target_o` float NOT NULL DEFAULT '0',
  `comment` varchar(255) NOT NULL DEFAULT '' COMMENT 'Event Comment',
  PRIMARY KEY (`entryorguid`,`source_type`,`id`,`link`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=FIXED;

DROP TABLE IF EXISTS waypoints;
CREATE TABLE `waypoints` (
  `entry` mediumint(8) unsigned NOT NULL DEFAULT '0',
  `pointid` mediumint(8) unsigned NOT NULL DEFAULT '0',
  `position_x` float NOT NULL DEFAULT '0',
  `position_y` float NOT NULL DEFAULT '0',
  `position_z` float NOT NULL DEFAULT '0',
  `point_comment` text,
  PRIMARY KEY (`entry`,`pointid`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=FIXED COMMENT='Creature waypoints';
