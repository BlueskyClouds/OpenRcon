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

#ifndef OPENRCON_H
#define OPENRCON_H

#include <QObject>
#include <QDebug>
#include <QMainWindow>
#include <QDesktopServices>
#include <QIcon>
#include <QEvent>
#include <QCloseEvent>
#include <QSettings>
#include <QComboBox>
#include <QMessageBox>
#include <QPushButton>

#include "ui_OpenRcon.h"
#include "Constants.h"
#include "GameManager.h"
#include "ServerManager.h"
#include "ServerListDialog.h"
#include "OptionsDialog.h"
#include "AboutDialog.h"

#include "ConnectionTabWidget.h"

using namespace Constants;

namespace Ui {
    class MainWindow;
}

class ServerListDialog;
class OpenRcon : public QMainWindow
{
    Q_OBJECT

public:
    OpenRcon(QWidget *parent = nullptr);
    ~OpenRcon();

    void addTab(ServerEntry *serverEntry);
    GameManager *getGameManager();
    ServerManager *getServerManager();

private:
    Ui::OpenRcon *ui;

    QSettings *settings;

    GameManager *gameManager;
    ServerManager *serverManager;
    ServerListDialog *serverListDialog;
    OptionsDialog *optionsDialog;
    AboutDialog *aboutDialog;

    QComboBox *comboBox_quickConnect_server;
    QPushButton *pushButton_quickConnect_connect;

    QAction *actionServerManager;
    QAction *actionExit;

    QAction *actionQuickConnect;

    QAction *actionOptions;

    QAction *actionDocumentation;
    QAction *actionVisitWebsite;
    QAction *actionReportBug;
    QAction *actionAbout;
    QAction *actionAboutQt;

    void readSettings();
    void writeSettings();

private slots:
    void closeTab(int index);
    void updateServerList();

    // Application menu
    void actionServerManager_triggered();

    // View menu
    void actionQuickConnect_triggered();

    // Setting menu
    void actionOptions_triggered();

    // Help menu
    void actionDocumentation_triggered();
    void actionVisitWebsite_triggered();
    void actionReportBug_triggered();
    void actionAbout_triggered();
    void actionAboutQt_triggered();

    // ServerManager
    void pushButton_quickConnect_connect_clicked();

};

#endif // OPENRCON_H
