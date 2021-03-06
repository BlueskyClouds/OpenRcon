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
 *
 * You should have received a copy of the GNU General Public License
 * along with OpenRcon.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef BANTYPE_H
#define BANTYPE_H

#include <QMetaType>

class QString;
template<class T>
class QList;
class QStringList;

enum class BanTypeEnum {
    Perm,
    Rounds,
    Seconds
};

class BanType
{
public:
    static BanTypeEnum fromString(const QString &banTypeString);
    static QString toString(const BanTypeEnum &banType);
    BanTypeEnum fromInt(int banTypeId);
    static int toInt(const BanTypeEnum &banType);
    static QList<BanTypeEnum> asList();
    static QStringList asStringList();

private:
    static QList<BanTypeEnum> list;
    static QStringList stringList;

};

// For use with QVariant
Q_DECLARE_METATYPE(BanTypeEnum)

#endif // BANTYPE_H
