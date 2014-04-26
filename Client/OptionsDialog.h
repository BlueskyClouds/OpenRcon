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

#ifndef OPTIONSDIALOG_H
#define OPTIONSDIALOG_H

#include <QObject>
#include <QSettings>
#include <QPushButton>

#include "Constants.h"
#include "LanguageManager.h"

#include "ui_OptionsDialog.h"

using namespace Constants;

class OptionsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OptionsDialog(QWidget *parent = 0);
    ~OptionsDialog();

private:
    Ui::OptionsDialog *ui;

    QSettings *settings;

    LanguageManager *languageManager;

    QPushButton *pushButton_ok;
    QPushButton *pushButton_cancel;
    QPushButton *pushButton_apply;

    void readSettings();
    void writeSettings();

private slots:
    void listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);
    void pushButton_ok_clicked();

};

#endif // OPTIONSDIALOG_H