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

#ifndef PLAYERLISTWIDGET_H
#define PLAYERLISTWIDGET_H

#include <QTreeWidget>

#include "LevelEntry.h"

class QTimer;
class QClipboard;
class QMenu;
class QAction;
class QIcon;
class QDragEnterEvent;
class QDragEvent;
template<class T>
class QList;
class QPoint;

class Frostbite2Client;
class FrostbiteServerInfo;
class BF4PlayerEntry;

class BF4PlayerListWidget : public QTreeWidget
{
    Q_OBJECT

public:
    BF4PlayerListWidget(Frostbite2Client *client, QWidget *parent = nullptr);
    ~BF4PlayerListWidget();

private:
    Frostbite2Client *client;
    LevelEntry levelEntry;

    /* User Interface */
    // Players
    QTimer *timer;
    bool updateLock;
    QClipboard *clipboard;
    QMenu *menu_player;
    QAction *action_player_kill;
    QAction *action_player_kick;
    QAction *action_player_ban;
    QAction *action_player_chat;
    QAction *action_player_yell;
    QAction *action_player_reserveSlot;
    QMenu *menu_player_move;
    QAction *action_player_move_team;
    QAction *action_player_move_squad;
    QMenu *menu_player_copyTo;
    QAction *action_player_copyTo_name;
    QAction *action_player_copyTo_guid;

    void clear();
    QTreeWidgetItem *currentItem() const;
    void dragEnterEvent(QDragEnterEvent *event) final;
    void dropEvent(QDropEvent *event) final;
    void resizeColumnsToContents();

private slots:
    /* Client */
    void onAuthenticated();

    /* Commands */
    void onServerInfoCommand(const FrostbiteServerInfo &serverInfo);
    void onListPlayersCommand(const QList<BF4PlayerEntry> &playerList);

    /* User Interface */
    void customContextMenuRequested(const QPoint &pos);
    void action_player_kill_triggered();
    void action_player_kick_triggered();
    void action_player_ban_triggered();
    void action_player_chat_triggered();
    void action_player_yell_triggered();
    void action_player_reserveSlot_triggered();
    void action_player_copyTo_name_triggered();
    void action_player_copyTo_guid_triggered();
    void menu_player_move_triggered(QAction *action);
    void updatePlayerList();

};

#endif // PLAYERLISTWIDGET_H
