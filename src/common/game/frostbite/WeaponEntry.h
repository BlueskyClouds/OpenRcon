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

#ifndef WEAPONENTRY_H
#define WEAPONENTRY_H

class QString;

class WeaponEntry
{
public:
    WeaponEntry(const QString &className, const QString &name, const QString &priority, const QString &type);
    WeaponEntry();
    ~WeaponEntry();

    QString getClassName() const;
    QString getName() const;
    QString getPriority() const;
    QString getType() const;

private:
    QString className;
    QString name;
    QString priority;
    QString type;

};

#endif // WEAPONENTRY_H
