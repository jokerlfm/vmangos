DROP TABLE IF EXISTS `nier`;
CREATE TABLE `nier` (
  `entry` int(11) NOT NULL AUTO_INCREMENT,
  `nier_id` int(11) NOT NULL DEFAULT '0',
  `account_name` varchar(50) COLLATE utf8_unicode_ci NOT NULL,
  `account_id` int(11) NOT NULL DEFAULT '0',
  `character_id` int(11) NOT NULL DEFAULT '0',
  `target_level` int(11) NOT NULL DEFAULT '0',
  `target_race` int(11) NOT NULL DEFAULT '0',
  `target_class` int(11) NOT NULL DEFAULT '0',
  `target_specialty` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`entry`)
) ENGINE=InnoDB AUTO_INCREMENT=1476 DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;
