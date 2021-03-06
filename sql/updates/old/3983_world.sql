UPDATE creature_template SET unit_flags = unit_flags | 0x2, ScriptName = "npc_dalinda" WHERE entry = 5644;

DELETE FROM escort_waypoints WHERE entry = 5644;
INSERT INTO escort_waypoints VALUES
(5644, 1, -339.679, 1752.04, 139.482, 0, ''),
(5644, 2, -328.957, 1734.95, 139.327, 0, ''),
(5644, 3, -350.747, 1731.12, 139.338, 0, ''),
(5644, 4, -365.064, 1739.04, 139.376, 0, ''),
(5644, 5, -371.105, 1746.03, 139.374, 0, ''),
(5644, 6, -383.141, 1738.62, 138.93, 0, ''),
(5644, 7, -390.445, 1733.98, 136.353, 0, ''),
(5644, 8, -401.368, 1726.77, 131.071, 0, ''),
(5644, 9, -416.016, 1721.19, 129.807, 0, ''),
(5644, 10, -437.139, 1709.82, 126.342, 0, ''),
(5644, 11, -459.862, 1687.92, 116.059, 0, ''),
(5644, 12, -460.686, 1679.55, 111.976, 0, ''),
(5644, 13, -461.485, 1670.94, 109.033, 0, ''),
(5644, 14, -468.53, 1645.51, 102.811, 0, ''),
(5644, 15, -474.529, 1615.97, 97.228, 0, ''),
(5644, 16, -474.329, 1590.01, 94.4982, 0, '');

UPDATE locales_quest SET EndText_loc2 = "Sauver Dalinda Malem" WHERE entry = 1440;
