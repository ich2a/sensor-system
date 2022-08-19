-- phpMyAdmin SQL Dump
-- version 5.0.4deb2+deb11u1
-- https://www.phpmyadmin.net/
--
-- Host: localhost:3306
-- Erstellungszeit: 19. Aug 2022 um 23:06
-- Server-Version: 10.5.15-MariaDB-0+deb11u1
-- PHP-Version: 7.4.30

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Datenbank: `DB`
--

-- --------------------------------------------------------

--
-- Tabellenstruktur für Tabelle `dataOut`
--

CREATE TABLE `dataOut` (
  `id` int(11) NOT NULL,
  `temp` float DEFAULT NULL,
  `hum` float DEFAULT NULL,
  `press` float DEFAULT NULL,
  `time` datetime NOT NULL DEFAULT current_timestamp()
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Daten für Tabelle `dataOut`
--

INSERT INTO `dataOut` (`id`, `temp`, `hum`, `press`, `time`) VALUES
(1, 27.2, 59, NULL, '2022-08-19 22:45:59');

-- --------------------------------------------------------

--
-- Tabellenstruktur für Tabelle `dataRoom`
--

CREATE TABLE `dataRoom` (
  `id` int(11) NOT NULL,
  `temp` float DEFAULT NULL,
  `hum` float DEFAULT NULL,
  `press` float DEFAULT NULL,
  `time` datetime NOT NULL DEFAULT current_timestamp()
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Daten für Tabelle `dataRoom`
--

INSERT INTO `dataRoom` (`id`, `temp`, `hum`, `press`, `time`) VALUES
(1, 27.2, 59, NULL, '2022-08-19 22:45:59'),
(2, 25.6, 59, NULL, '2022-08-19 22:54:02');

-- --------------------------------------------------------

--
-- Tabellenstruktur für Tabelle `dataRoom2`
--

CREATE TABLE `dataRoom2` (
  `id` int(11) NOT NULL,
  `temp` float DEFAULT NULL,
  `hum` float DEFAULT NULL,
  `press` float DEFAULT NULL,
  `time` datetime NOT NULL DEFAULT current_timestamp()
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Daten für Tabelle `dataRoom2`
--

INSERT INTO `dataRoom2` (`id`, `temp`, `hum`, `press`, `time`) VALUES
(1, 27.2, 59, NULL, '2022-08-19 22:45:59');

-- --------------------------------------------------------

--
-- Tabellenstruktur für Tabelle `offsets`
--

CREATE TABLE `offsets` (
  `id` int(11) NOT NULL,
  `location` varchar(11) NOT NULL,
  `temp` float DEFAULT NULL,
  `hum` float DEFAULT NULL,
  `press` float DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Daten für Tabelle `offsets`
--

INSERT INTO `offsets` (`id`, `location`, `temp`, `hum`, `press`) VALUES
(1, 'Room', -2, 0, 0),
(2, 'Room2', 0, 0, 0),
(3, 'Out', 0, 0, 0);

--
-- Indizes der exportierten Tabellen
--

--
-- Indizes für die Tabelle `dataOut`
--
ALTER TABLE `dataOut`
  ADD PRIMARY KEY (`id`);

--
-- Indizes für die Tabelle `dataRoom`
--
ALTER TABLE `dataRoom`
  ADD PRIMARY KEY (`id`);

--
-- Indizes für die Tabelle `dataRoom2`
--
ALTER TABLE `dataRoom2`
  ADD PRIMARY KEY (`id`);

--
-- Indizes für die Tabelle `offsets`
--
ALTER TABLE `offsets`
  ADD PRIMARY KEY (`id`);

--
-- AUTO_INCREMENT für exportierte Tabellen
--

--
-- AUTO_INCREMENT für Tabelle `dataOut`
--
ALTER TABLE `dataOut`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=2;

--
-- AUTO_INCREMENT für Tabelle `dataRoom`
--
ALTER TABLE `dataRoom`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=3;

--
-- AUTO_INCREMENT für Tabelle `dataRoom2`
--
ALTER TABLE `dataRoom2`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=2;

--
-- AUTO_INCREMENT für Tabelle `offsets`
--
ALTER TABLE `offsets`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=4;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
