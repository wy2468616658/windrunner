DELETE FROM escort_waypoints WHERE entry = 349;
INSERT INTO escort_waypoints VALUES
(349, 0, -8768.282227, -2185.591553, 141.882187, 0, ''),
(349, 1, -8825.373047, -2187.282227, 138.417282, 0, ''),
(349, 2, -8791.032227, -2253.971680, 146.722656, 0, ''),
(349, 3, -8736.863281, -2250.483154, 154.011612, 0, ''),
(349, 4, -8705.439453, -2245.367676, 154.528366, 0, ''),
(349, 5, -8692.488281, -2238.561768, 153.090363, 0, ''),
(349, 6, -8666.933594, -2255.388672, 155.292053, 0, ''),
(349, 7, -8674.903320, -2279.676025, 155.577026, 0, ''),
(349, 8, -8689.582031, -2329.724609, 156.008133, 0, ''),
(349, 9, -8770.818359, -2394.301758, 155.917343, 0, ''),
(349, 10, -8815.596680, -2481.997559, 132.953339, 0, ''),
(349, 11, -8915.981445, -2580.220703, 132.447632, 0, ''),
(349, 12, -8959.246094, -2600.650146, 132.483994, 0, '');

UPDATE creature_template SET ScriptName = "npc_corporal_keeshan" WHERE entry = 349;

UPDATE quest_template SET SpecialFlags = 2 WHERE entry = 219;
