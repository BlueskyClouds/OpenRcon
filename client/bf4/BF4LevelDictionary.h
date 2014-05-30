/*
 * Copyright (C) 2014 The OpenRcon Project.
 *
 * This file is part of OpenRcon.
 *
 * OpenRcon is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * OpenRcon is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with OpenRcon.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef BF4LEVELDICTIONARY_H
#define BF4LEVELDICTIONARY_H

#include "LevelDictionary.h"
#include "BF4GameModeEntry.h"

typedef LevelDictionary<3, TeamEntry, LevelEntry, BF4GameModeEntry> BF4LevelDictionary;

template<> QList<TeamEntry> BF4LevelDictionary::teamList;
template<> QList<LevelEntry> BF4LevelDictionary::levelList;
template<> QList<BF4GameModeEntry> BF4LevelDictionary::gameModeList;
template<> QMultiHash<int, int> BF4LevelDictionary::levelMap;

#endif // BF4LEVELDICTIONARY_H