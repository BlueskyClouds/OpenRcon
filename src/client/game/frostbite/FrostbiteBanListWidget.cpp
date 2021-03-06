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
#include <QStringList>
#include <QCompleter>
#include <QMenu>
#include <QAction>
#include <QList>
#include <QString>

#include "FrostbiteBanListWidget.h"
#include "ui_FrostbiteBanListWidget.h"

#include "BanListEntry.h"
#include "BanType.h"
#include "BanIdType.h"
#include "FrostbiteUtils.h"
#include "Time.h"

FrostbiteBanListWidget::FrostbiteBanListWidget(FrostbiteClient *client, QWidget *parent) :
    FrostbiteWidget(client, parent),
    ui(new Ui::FrostbiteBanListWidget)
{
    ui->setupUi(this);

    timer = new QTimer(this);
    timer->setInterval(1000);
    timer->start();
    connect(timer, &QTimer::timeout, this, &FrostbiteBanListWidget::update);

    for (BanIdTypeEnum banIdType : BanIdType::asList()) {
        ui->comboBox_type->addItem(BanIdType::toString(banIdType), QVariant::fromValue(banIdType));
    }

    QStringList reasonList = {
        "Hacking/Cheating",
        "Admin abuse",
        "Make room for reserved slots",
        "Being disrespectful",
        "Teamkilling",
        "Spawnkilling",
        "Camping",
        "Team balance",
        "Switching to winning team"
    };

    QCompleter *completer = new QCompleter(reasonList, this);
    completer->setCompletionMode(QCompleter::UnfilteredPopupCompletion);
    ui->lineEdit_reason->setCompleter(completer);

    // Create actions and menus.
    menu_bl_banList = new QMenu(ui->tableWidget_bl_banList);
    action_bl_banList_remove = new QAction(tr("Remove"), menu_bl_banList);

    menu_bl_banList->addAction(action_bl_banList_remove);

    /* Client */
    connect(getClient(),                      &Client::onAuthenticated,                                               this, &FrostbiteBanListWidget::onAuthenticated);

    /* Commands */
    // BanList
    connect(getClient()->getCommandHandler(), &FrostbiteCommandHandler::onBanListListCommand,                         this, &FrostbiteBanListWidget::onBanListListCommand);

    /* User Interface */
    connect(ui->tableWidget_bl_banList,       &QTableWidget::customContextMenuRequested,                              this, &FrostbiteBanListWidget::tableWidget_bl_banList_customContextMenuRequested);
    connect(action_bl_banList_remove,         &QAction::triggered,                                                    this, &FrostbiteBanListWidget::action_bl_banList_remove_triggered);
    connect(ui->pushButton_load,              &QPushButton::clicked,                                                  getClient()->getCommandHandler(), &FrostbiteCommandHandler::sendBanListLoadCommand);
    connect(ui->pushButton_save,              &QPushButton::clicked,                                                  getClient()->getCommandHandler(), &FrostbiteCommandHandler::sendBanListSaveCommand);
    connect(ui->pushButton_clear,             &QPushButton::clicked,                                                  this, &FrostbiteBanListWidget::pushButton_clear_clicked);
    connect(ui->lineEdit_value,               &QLineEdit::textChanged,                                                this, &FrostbiteBanListWidget::validate);
    connect(ui->lineEdit_reason,              &QLineEdit::textChanged,                                                this, &FrostbiteBanListWidget::validate);
    connect(ui->radioButton_permanent,        &QRadioButton::clicked,                                                 this, &FrostbiteBanListWidget::radioButton_permanent_clicked);
    connect(ui->radioButton_temporary,        &QRadioButton::clicked,                                                 this, &FrostbiteBanListWidget::radioButton_temporary_clicked);
    connect(ui->comboBox_by,                  static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &FrostbiteBanListWidget::comboBox_by_currentIndexChanged);
    connect(ui->pushButton_ban,               &QPushButton::clicked,                                                  this, &FrostbiteBanListWidget::pushButton_ban_clicked);
}

FrostbiteBanListWidget::~FrostbiteBanListWidget()
{
    delete ui;
}

void FrostbiteBanListWidget::setBanlist(const QList<BanListEntry> &banList)
{
    ui->tableWidget_bl_banList->clearContents();
    ui->tableWidget_bl_banList->setRowCount(0);

    for (BanListEntry banListEntry : banList) {
        addBanListItem(banListEntry.getIdType(), banListEntry.getId(), banListEntry.getType(), banListEntry.getSeconds(), banListEntry.getRounds(), banListEntry.getReason());
    }

    ui->tableWidget_bl_banList->resizeColumnsToContents();
}

void FrostbiteBanListWidget::setTemporaryEnabled(bool enabled)
{
    ui->comboBox_by->setEnabled(enabled);
    ui->spinBox_timeout->setEnabled(enabled);
    ui->comboBox_timeUnit->setEnabled(enabled);
}

void FrostbiteBanListWidget::addBanListItem(const BanIdTypeEnum &banIdType, const QString &banId, const BanTypeEnum &banType, int seconds, int rounds, const QString &reason)
{
    int row = ui->tableWidget_bl_banList->rowCount();
    ui->tableWidget_bl_banList->insertRow(row);

    QTableWidgetItem *banIdTypeItem = new QTableWidgetItem();
    banIdTypeItem->setData(Qt::UserRole, QVariant::fromValue(banIdType));
    banIdTypeItem->setText(BanIdType::toString(banIdType));

    ui->tableWidget_bl_banList->setItem(row, 0, banIdTypeItem);
    ui->tableWidget_bl_banList->setItem(row, 1, new QTableWidgetItem(banId));

    QString remaining;

    switch (banType) {
    case BanTypeEnum::Perm:
        remaining = tr("Permanent");
        break;

    case BanTypeEnum::Rounds:
        remaining = rounds > 1 ? tr("%1 Rounds").arg(rounds) : tr("%1 Round").arg(rounds);
        break;

    case BanTypeEnum::Seconds:
        remaining = Time::fromSeconds(seconds--).toString();
        break;
    }

    QTableWidgetItem *banTypeItem = new QTableWidgetItem();
    banTypeItem->setData(Qt::UserRole, QVariant::fromValue(banType));

    if (banType == BanTypeEnum::Seconds) {
        banTypeItem->setData(Qt::UserRole + 1, QVariant::fromValue(seconds));
    }

    banTypeItem->setText(remaining);

    ui->tableWidget_bl_banList->setItem(row, 2, banTypeItem);
    ui->tableWidget_bl_banList->setItem(row, 3, new QTableWidgetItem(reason));
}

/* Client */
void FrostbiteBanListWidget::onAuthenticated()
{
    getClient()->getCommandHandler()->sendBanListListCommand();
}

/* Commands */
void FrostbiteBanListWidget::onBanListListCommand(const QList<BanListEntry> &banList)
{
    ui->pushButton_clear->setEnabled(!banList.isEmpty());

    setBanlist(banList);
}

/* User Interface */
void FrostbiteBanListWidget::validate()
{
    bool enabled = !ui->lineEdit_value->text().isEmpty();

    ui->radioButton_permanent->setEnabled(enabled);
    ui->radioButton_temporary->setEnabled(enabled);
    ui->pushButton_ban->setEnabled(enabled);
}

void FrostbiteBanListWidget::update()
{
    // Loop thru all rows and update current duration.
    for (int row = 0; row < ui->tableWidget_bl_banList->rowCount(); row++) {
        QTableWidgetItem *tableWidgetItem = ui->tableWidget_bl_banList->item(row, 2);
        BanTypeEnum banType = tableWidgetItem->data(Qt::UserRole).value<BanTypeEnum>();

        if (banType == BanTypeEnum::Seconds) {
            int seconds = tableWidgetItem->data(Qt::UserRole + 1).value<int>();

            if (seconds > 0) {
                tableWidgetItem->setText(Time::fromSeconds(seconds--).toString());
            } else {
                ui->tableWidget_bl_banList->removeRow(row);
            }

            tableWidgetItem->setData(Qt::UserRole + 1, seconds);
        }
    }
}



void FrostbiteBanListWidget::tableWidget_bl_banList_customContextMenuRequested(const QPoint &pos)
{
    if (ui->tableWidget_bl_banList->itemAt(pos)) {
        menu_bl_banList->exec(QCursor::pos());
    }
}

void FrostbiteBanListWidget::action_bl_banList_remove_triggered()
{
    int row = ui->tableWidget_bl_banList->currentRow();
    BanIdTypeEnum banIdType = ui->tableWidget_bl_banList->itemAt(row, 0)->data(Qt::UserRole).value<BanIdTypeEnum>();
    QString player = ui->tableWidget_bl_banList->item(row, 1)->text();

    if (!player.isEmpty()) {
        getClient()->getCommandHandler()->sendBanListRemoveCommand(banIdType, player);

        ui->tableWidget_bl_banList->removeRow(row);
    }
}

void FrostbiteBanListWidget::pushButton_clear_clicked()
{
    ui->tableWidget_bl_banList->clearContents();
    ui->tableWidget_bl_banList->setRowCount(0);
    ui->pushButton_clear->setEnabled(ui->tableWidget_bl_banList->rowCount() < 0);
    getClient()->getCommandHandler()->sendBanListClearCommand();
}

void FrostbiteBanListWidget::radioButton_permanent_clicked()
{
    setTemporaryEnabled(false);
}

void FrostbiteBanListWidget::radioButton_temporary_clicked()
{
    setTemporaryEnabled(true);
}

void FrostbiteBanListWidget::comboBox_by_currentIndexChanged(int index)
{
    ui->comboBox_timeUnit->setEnabled(index == 0);
}

void FrostbiteBanListWidget::pushButton_ban_clicked()
{
    BanIdTypeEnum banIdType = ui->comboBox_type->itemData(ui->comboBox_type->currentIndex()).value<BanIdTypeEnum>();
    QString value = ui->lineEdit_value->text();
    QString reason = ui->lineEdit_reason->text();

    if (ui->radioButton_permanent->isChecked()) {
        getClient()->getCommandHandler()->sendBanListAddCommand(banIdType, value, BanTypeEnum::Perm, reason);
    } else {
        BanTypeEnum banType = ui->comboBox_by->currentIndex() > 0 ? BanTypeEnum::Rounds : BanTypeEnum::Seconds;
        int timeout = ui->spinBox_timeout->value();

        if (ui->comboBox_timeUnit->isEnabled()) {
            int timeoutValue = timeout;

            switch (ui->comboBox_timeUnit->currentIndex()) {
            case 0:
                timeout = timeoutValue;
                break;

            case 1:
                timeout = timeoutValue * 60;
                break;

            case 2:
                timeout = timeoutValue * 60 * 60;
                break;

            case 3:
                timeout = timeoutValue * 60 * 60 * 24;
                break;

            case 4:
                timeout = timeoutValue * 60 * 60 * 24 * 7;
                break;
            }
        }

        getClient()->getCommandHandler()->sendBanListAddCommand(banIdType, value, banType, reason, timeout);
    }
}
