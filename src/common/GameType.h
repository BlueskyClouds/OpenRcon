/*
 * Copyright (C) 2016 The OpenRcon Project.
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

 * You should have received a copy of the GNU General Public License
 * along with OpenRcon.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef GAMETYPE_H
#define GAMETYPE_H

#include <QMetaType>

class QString;
template<class T>
class QList;
class QStringList;

enum class GameTypeEnum {
    BFBC2,
    BF3,
    BF4,
    Unsupported
};

class GameType
{
public:
    static GameTypeEnum fromString(const QString &gameName);
    static QString toString(const GameTypeEnum &gameType);
    static GameTypeEnum fromInt(int gameTypeId);
    static int toInt(const GameTypeEnum &gameType);
    static QList<GameTypeEnum> asList();
    static QStringList asStringList();

private:
    static QList<GameTypeEnum> list;
    static QStringList stringList;

};

// For use with QVariant
Q_DECLARE_METATYPE(GameTypeEnum)

#endif // GAMETYPE_H
