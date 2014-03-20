/*
 * Copyright (C) 2011 The OpenRcon Project.
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

#ifndef ABOUT_H
#define ABOUT_H

#include <QObject>
#include <QFile>
#include <QTextStream>
#include <QString>

#include "ui_About.h"

#include "Constants.h"

using namespace Constants;

class About : public QDialog
{
    Q_OBJECT

public:
    explicit About(QObject *parent = 0);
    ~About();

private:
    Ui::About *ui;

    QString getFile(const QString &fileName);

};

#endif // ABOUT_H
