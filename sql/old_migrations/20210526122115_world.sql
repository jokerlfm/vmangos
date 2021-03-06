DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20210526122115');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20210526122115');
-- Add your query below.


-- Correct ID of existing Copper Vein spawns in The Barrens.
UPDATE `gameobject` SET `id`=3763, `position_x`=94.9738, `position_y`=-1945.36, `position_z`=79.6132, `orientation`=4.03171, `rotation0`=0, `rotation1`=0, `rotation2`=-0.902585, `rotation3`=0.430512 WHERE `guid`=4723;
UPDATE `gameobject` SET `id`=3763, `position_x`=-101.218, `position_y`=-2886.92, `position_z`=91.6667, `orientation`=4.20625, `rotation0`=0, `rotation1`=0, `rotation2`=-0.861628, `rotation3`=0.507539 WHERE `guid`=5253;
UPDATE `gameobject` SET `id`=3763, `position_x`=-1019.65, `position_y`=-2055.23, `position_z`=63.3198, `orientation`=4.88692, `rotation0`=0, `rotation1`=0, `rotation2`=-0.642787, `rotation3`=0.766045 WHERE `guid`=4685;
UPDATE `gameobject` SET `id`=3763, `position_x`=-1069.42, `position_y`=-2112.45, `position_z`=56.0496, `orientation`=1.5708, `rotation0`=0, `rotation1`=0, `rotation2`=0.707107, `rotation3`=0.707107 WHERE `guid`=5129;
UPDATE `gameobject` SET `id`=3763, `position_x`=-1823.53, `position_y`=-1875.67, `position_z`=97.7162, `orientation`=6.24828, `rotation0`=0, `rotation1`=0, `rotation2`=-0.0174522, `rotation3`=0.999848 WHERE `guid`=5020;
UPDATE `gameobject` SET `id`=3763, `position_x`=-1900.59, `position_y`=-1747.52, `position_z`=92.6143, `orientation`=4.34587, `rotation0`=0, `rotation1`=0, `rotation2`=-0.824126, `rotation3`=0.566406 WHERE `guid`=4778;
UPDATE `gameobject` SET `id`=3763, `position_x`=-1958.45, `position_y`=-2686.12, `position_z`=94.873, `orientation`=3.99681, `rotation0`=0, `rotation1`=0, `rotation2`=-0.909961, `rotation3`=0.414694 WHERE `guid`=4780;
UPDATE `gameobject` SET `id`=3763, `position_x`=-2056.05, `position_y`=-2825.92, `position_z`=95.1547, `orientation`=4.27606, `rotation0`=0, `rotation1`=0, `rotation2`=-0.843391, `rotation3`=0.5373 WHERE `guid`=5134;

-- Add missing Copper Vein (Entry: 3763) spawns.
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecsmin`, `spawntimesecsmax`, `state`, `animprogress`) VALUES 
(5292, 3763, 1, -1919.06, -2721.38, 91.8313, 4.15388, 0, 0, -0.874619, 0.48481, 900, 900, 1, 100),
(5293, 3763, 1, -2080.55, -2800.56, 97.923, 0.837758, 0, 0, 0.406736, 0.913545, 900, 900, 1, 100),
(5294, 3763, 1, -1994.19, -2817.67, 95.5165, 2.87979, 0, 0, 0.991445, 0.130528, 900, 900, 1, 100),
(5295, 3763, 1, -1970.99, -2801.34, 91.8729, 3.12412, 0, 0, 0.999962, 0.00873464, 900, 900, 1, 100),
(5296, 3763, 1, -2241.22, -2552.48, 92.1614, 4.10152, 0, 0, -0.887011, 0.461749, 900, 900, 1, 100),
(5297, 3763, 1, 52.788, -1923.76, 80.1537, 0.90757, 0, 0, 0.438371, 0.898794, 900, 900, 1, 100),
(5298, 3763, 1, 299.283, -1414.12, 93.4663, 3.90954, 0, 0, -0.927183, 0.374608, 900, 900, 1, 100),
(5299, 3763, 1, 669.423, -1542.82, 106.891, 5.60251, 0, 0, -0.333807, 0.942641, 900, 900, 1, 100),
(5300, 3763, 1, -1844.55, -1955.4, 94.9395, 6.14356, 0, 0, -0.0697555, 0.997564, 900, 900, 1, 100),
(5301, 3763, 1, -3956.45, -1863.94, 97.3947, 4.46804, 0, 0, -0.788011, 0.615662, 900, 900, 1, 100),
(5302, 3763, 1, -141.477, -3034.68, 91.7, 5.25344, 0, 0, -0.492423, 0.870356, 900, 900, 1, 100),
(5303, 3763, 1, -1397.27, -1521.42, 117.744, 3.73501, 0, 0, -0.956305, 0.292372, 900, 900, 1, 100),
(5304, 3763, 1, -1462.52, -1464.5, 102.557, 0.750491, 0, 0, 0.366501, 0.930418, 900, 900, 1, 100),
(5305, 3763, 1, -3672.36, -1631.22, 95.3799, 2.33874, 0, 0, 0.920505, 0.390732, 900, 900, 1, 100),
(5306, 3763, 1, -3720.6, -1553.41, 96.1831, 4.4855, 0, 0, -0.782608, 0.622515, 900, 900, 1, 100),
(5307, 3763, 1, -3925.95, -1621.06, 91.8752, 0.279252, 0, 0, 0.139173, 0.990268, 900, 900, 1, 100),
(5308, 3763, 1, -3991.88, -1883.89, 97.9145, 5.41052, 0, 0, -0.422618, 0.906308, 900, 900, 1, 100),
(5309, 3763, 1, -1874.54, -2720.51, 95.3035, 1.06465, 0, 0, 0.507538, 0.861629, 900, 900, 1, 100),
(5310, 3763, 1, -2067.9, -1745.81, 105.385, 5.42798, 0, 0, -0.414693, 0.909962, 900, 900, 1, 100),
(5311, 3763, 1, -229.327, -2982.14, 92.0946, 3.75246, 0, 0, -0.953716, 0.300708, 900, 900, 1, 100),
(5312, 3763, 1, -116.853, -3193.63, 93.3306, 3.10665, 0, 0, 0.999847, 0.0174693, 900, 900, 1, 100),
(5313, 3763, 1, -223.339, -3348.09, 91.6667, 0.331611, 0, 0, 0.165047, 0.986286, 900, 900, 1, 100),
(5325, 3763, 1, -261.772, -3343.72, 99.7645, 1.81514, 0, 0, 0.788011, 0.615662, 900, 900, 1, 100),
(5489, 3763, 1, 697.511, -1628.27, 92.4118, 2.42601, 0, 0, 0.936672, 0.350207, 900, 900, 1, 100),
(5490, 3763, 1, 336.791, -1647.45, 105.217, 2.40855, 0, 0, 0.93358, 0.358368, 900, 900, 1, 100),
(5495, 3763, 1, -3980.38, -1706.46, 94.8775, 2.42601, 0, 0, 0.936672, 0.350207, 900, 900, 1, 100),
(5501, 3763, 1, -3701.07, -1621.85, 96.2469, 3.90954, 0, 0, -0.927183, 0.374608, 900, 900, 1, 100),
(5503, 3763, 1, -2102.36, -1711.07, 93.8962, 1.50098, 0, 0, 0.681998, 0.731354, 900, 900, 1, 100),
(5504, 3763, 1, -1252.58, -2998.96, 76.7928, 1.81514, 0, 0, 0.788011, 0.615662, 900, 900, 1, 100),
(5507, 3763, 1, -2287.26, -2533.56, 95.5277, 0.541051, 0, 0, 0.267238, 0.963631, 900, 900, 1, 100);
INSERT INTO `pool_gameobject` (`guid`, `pool_entry`, `chance`, `description`) VALUES
(5292, 1033, 0, 'Copper Vein'),
(5293, 1033, 0, 'Copper Vein'),
(5294, 1033, 0, 'Copper Vein'),
(5295, 1033, 0, 'Copper Vein'),
(5296, 1033, 0, 'Copper Vein'),
(5297, 1033, 0, 'Copper Vein'),
(5298, 1033, 0, 'Copper Vein'),
(5299, 1033, 0, 'Copper Vein'),
(5300, 1033, 0, 'Copper Vein'),
(5301, 1033, 0, 'Copper Vein'),
(5302, 1033, 0, 'Copper Vein'),
(5303, 1033, 0, 'Copper Vein'),
(5304, 1033, 0, 'Copper Vein'),
(5305, 1033, 0, 'Copper Vein'),
(5306, 1033, 0, 'Copper Vein'),
(5307, 1033, 0, 'Copper Vein'),
(5308, 1033, 0, 'Copper Vein'),
(5309, 1033, 0, 'Copper Vein'),
(5310, 1033, 0, 'Copper Vein'),
(5311, 1033, 0, 'Copper Vein'),
(5312, 1033, 0, 'Copper Vein'),
(5313, 1033, 0, 'Copper Vein'),
(5325, 1033, 0, 'Copper Vein'),
(5489, 1033, 0, 'Copper Vein'),
(5490, 1033, 0, 'Copper Vein'),
(5495, 1033, 0, 'Copper Vein'),
(5501, 1033, 0, 'Copper Vein'),
(5503, 1033, 0, 'Copper Vein'),
(5504, 1033, 0, 'Copper Vein'),
(5507, 1033, 0, 'Copper Vein');


-- End of migration.
END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;
