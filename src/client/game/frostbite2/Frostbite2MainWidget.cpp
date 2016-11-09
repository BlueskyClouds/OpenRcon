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

#include <QTimer>
#include <QMessageBox>

#include "Frostbite2MainWidget.h"
#include "ui_Frostbite2MainWidget.h"

#include "FrostbiteEventsWidget.h"
#include "FrostbiteChatWidget.h"
#include "FrostbiteBanListWidget.h"
#include "Frostbite2ReservedSlotsWidget.h"
#include "FrostbiteConsoleWidget.h"
#include "Frostbite2ServerInfo.h"
#include "TabWidget.h"
#include "ServerEntry.h"
#include "GameType.h"
#include "LevelEntry.h"
#include "GameModeEntry.h"
#include "BF4GameModeEntry.h"
#include "BF3LevelDictionary.h"
#include "BF4LevelDictionary.h"
#include "Time.h"

Frostbite2MainWidget::Frostbite2MainWidget(Frostbite2Client *client, QWidget *parent) :
    Frostbite2Widget(client, parent),
    ui(new Ui::Frostbite2MainWidget)
{
    ui->setupUi(this);

    /* User Inferface */
    // ServerInfo
    timerServerInfoRoundTime = new QTimer(this);
    timerServerInfoRoundTime->start(1000);

    timerServerInfoUpTime = new QTimer(this);
    timerServerInfoUpTime->start(1000);

    connect(timerServerInfoRoundTime, &QTimer::timeout, this, &Frostbite2MainWidget::updateRoundTime);
    connect(timerServerInfoUpTime,    &QTimer::timeout, this, &Frostbite2MainWidget::updateUpTime);

    // Create tabs from widgets.
    eventsWidget = new FrostbiteEventsWidget(getClient(), this);
    chatWidget = new FrostbiteChatWidget(getClient(), this);
    banListWidget = new FrostbiteBanListWidget(getClient(), this);
    reservedSlotsWidget = new Frostbite2ReservedSlotsWidget(getClient(), this);
    consoleWidget = new FrostbiteConsoleWidget(getClient(), commandList, this);

    ui->tabWidget->addTab(eventsWidget, QIcon(":/frostbite/icons/events.png"), tr("Events"));
    ui->tabWidget->addTab(chatWidget, QIcon(":/frostbite/icons/chat.png"), tr("Chat"));
    ui->tabWidget->addTab(banListWidget, QIcon(":/frostbite/icons/ban.png"), tr("Banlist"));
    ui->tabWidget->addTab(reservedSlotsWidget, QIcon(":/frostbite/icons/reserved.png"), tr("Reserved Slots"));
    ui->tabWidget->addTab(consoleWidget, QIcon(":/frostbite/icons/console.png"), tr("Console"));
    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(eventsWidget), false);
    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(chatWidget), false);
    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(banListWidget), false);
    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(reservedSlotsWidget), false);
    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(consoleWidget), false);
    ui->tabWidget->setCurrentIndex(0);

    /* Connection */
    connect(getClient()->getConnection(),     &Connection::onConnected,                      this,                             &Frostbite2MainWidget::onConnected);
    connect(getClient()->getConnection(),     &Connection::onConnected,                      getClient()->getCommandHandler(), &Frostbite2CommandHandler::sendServerInfoCommand);
    connect(getClient()->getConnection(),     &Connection::onDisconnected,                   this,                             &Frostbite2MainWidget::onDisconnected);

    /* Client */
    connect(getClient(),                      &Client::onAuthenticated,                      this,                             &Frostbite2MainWidget::onAuthenticated);

    /* Events */
    connect(getClient()->getCommandHandler(), &Frostbite2CommandHandler::onPlayerJoinEvent,                                    &Frostbite2CommandHandler::sendServerInfoCommand);
    connect(getClient()->getCommandHandler(), &Frostbite2CommandHandler::onPlayerLeaveEvent,                                   &Frostbite2CommandHandler::sendServerInfoCommand);
    connect(getClient()->getCommandHandler(), &Frostbite2CommandHandler::onServerLevelLoadedEvent,                             &Frostbite2CommandHandler::sendServerInfoCommand);
    connect(getClient()->getCommandHandler(), &Frostbite2CommandHandler::onServerMaxPlayerCountChangeEvent,                    &Frostbite2CommandHandler::sendServerInfoCommand);

    /* Commands */
    // Misc
    connect(getClient()->getCommandHandler(), static_cast<void (FrostbiteCommandHandler::*)(bool)>(&FrostbiteCommandHandler::onLoginHashedCommand),
            this, &Frostbite2MainWidget::onLoginHashedCommand);
    connect(getClient()->getCommandHandler(), static_cast<void (Frostbite2CommandHandler::*)(const Frostbite2ServerInfo&)>(&FrostbiteCommandHandler::onServerInfoCommand),
            this, &Frostbite2MainWidget::onServerInfoCommand);
    connect(getClient()->getCommandHandler(), &Frostbite2CommandHandler::onVersionCommand,   this,                             &Frostbite2MainWidget::onVersionCommand);

    // Admin

    // FairFight

    // Player

    // Punkbuster

    // Squad

    // Variables

    /* User Interface */
    // Server Information
    connect(ui->pushButton_si_restartRound,   &QPushButton::clicked,                         this,                             &Frostbite2MainWidget::pushButton_si_restartRound_clicked);
    connect(ui->pushButton_si_runNextRound,   &QPushButton::clicked,                         this,                             &Frostbite2MainWidget::pushButton_si_runNextRound_clicked);
}

Frostbite2MainWidget::~Frostbite2MainWidget()
{
    delete ui;
}

/* Connection */
void Frostbite2MainWidget::onConnected()
{
    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(eventsWidget), true);
    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(consoleWidget), true);
}

void Frostbite2MainWidget::onAuthenticated()
{
    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(chatWidget), true);
    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(banListWidget), true);
    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(reservedSlotsWidget), true);
}

void Frostbite2MainWidget::onDisconnected()
{
    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(eventsWidget), false);
    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(chatWidget), false);
    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(banListWidget), false);
    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(reservedSlotsWidget), false);
    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(consoleWidget), false);
}

/* Commands */
// Misc
void Frostbite2MainWidget::onLoginHashedCommand(bool authenticated)
{
    if (!authenticated) {
        int result = QMessageBox::warning(0, tr("Error"), tr("Wrong password, make sure you typed in the right password and try again."));

        if (result) {
            client->getConnection()->hostDisconnect();
        }
    }
}

void Frostbite2MainWidget::onServerInfoCommand(const Frostbite2ServerInfo &serverInfo)
{
    // Update the title of the this sessions tab.
    TabWidget *tabWidget = TabWidget::getInstance();
    tabWidget->setTabText(tabWidget->indexOf(this), serverInfo.getServerName());

    GameTypeEnum gameType = getClient()->getServerEntry()->getGameType();
    LevelEntry level;
    GameModeEntry gameMode;

    switch (gameType) {
    case GameTypeEnum::BF3:
        level = BF3LevelDictionary::getLevel(serverInfo.getCurrentMap());
        gameMode = BF3LevelDictionary::getGameMode(serverInfo.getGameMode());
        break;

    case GameTypeEnum::BF4:
        level = BF4LevelDictionary::getLevel(serverInfo.getCurrentMap());
        gameMode = BF4LevelDictionary::getGameMode(serverInfo.getGameMode());
        break;

    default:
        break;
    }

    // Update the roundTime and serverUpTime.
    roundTime = serverInfo.getRoundTime();
    upTime = serverInfo.getServerUpTime();
    updateRoundTime();
    updateUpTime();

    // Update the server information.
    ui->label_si_level->setPixmap(level.getIcon());
    ui->label_si_status->setText(QString("%1 - %2").arg(level.getName(), gameMode.getName()));

    // Update the players and round information.
    ui->label_si_players->setText(tr("<b>Players</b>: %1 of %2").arg(serverInfo.getPlayerCount()).arg(serverInfo.getMaxPlayerCount()));
    ui->label_si_round->setText(tr("<b>Round</b>: %1 of %2").arg(serverInfo.getRoundsPlayed() + 1).arg(serverInfo.getRoundsTotal()));
}

void Frostbite2MainWidget::onVersionCommand(const QString &type, int build)
{
    Q_UNUSED(type);

    ui->label_si_version->setText(tr("<b>Version</b>: %1").arg(getClient()->getVersionFromBuild(build)));
    ui->label_si_version->setToolTip(QString::number(build));
}

// Admin

// FairFight

// Player

// Punkbuster

// Squad

// Variables

/* User Interface */
// ServerInfo
void Frostbite2MainWidget::pushButton_si_restartRound_clicked()
{
    int result = QMessageBox::question(this, tr("Restart round"), tr("Are you sure you want to restart the round?"));

    if (result == QMessageBox::Yes) {
        getClient()->getCommandHandler()->sendMapListRestartRoundCommand();
    }
}

void Frostbite2MainWidget::pushButton_si_runNextRound_clicked()
{
    int result = QMessageBox::question(this, tr("Run next round"), tr("Are you sure you want to run the next round?"));

    if (result == QMessageBox::Yes) {
        getClient()->getCommandHandler()->sendMapListRunNextRoundCommand();
    }
}

void Frostbite2MainWidget::updateRoundTime()
{
    ui->label_si_round->setToolTip(Time::fromSeconds(roundTime++).toShortString());
}

void Frostbite2MainWidget::updateUpTime()
{
    ui->label_si_upTime->setText(tr("<b>Uptime:</b> %1").arg(Time::fromSeconds(upTime++).toShortString()));
}
