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

#include <QComboBox>
#include <QSpinBox>
#include <QPushButton>
#include <QLineEdit>
#include <QString>
#include <QDateTime>

#include "ChatWidget.h"
#include "ui_ChatWidget.h"
#include "Frostbite2Client.h"
#include "PlayerSubset.h"

ChatWidget::ChatWidget(Frostbite2Client *client, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatWidget),
    client(client)
{
    ui->setupUi(this);

    /* Events */
    connect(client->getCommandHandler(), &Frostbite2CommandHandler::onPlayerChatEvent, this, &ChatWidget::onPlayerChatEvent);

    /* Commands */
    connect(client->getCommandHandler(), static_cast<void (Frostbite2CommandHandler::*)(bool)>(&Frostbite2CommandHandler::onLoginHashedCommand), this, &ChatWidget::onLoginHashedCommand);

    /* User Interface */
    connect(ui->comboBox_mode,    static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &ChatWidget::comboBox_mode_currentIndexChanged);
    connect(ui->spinBox_duration, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),          this, &ChatWidget::spinBox_duration_valueChanged);
    connect(ui->pushButton_send,  &QPushButton::clicked,                                                  this, &ChatWidget::pushButton_send_clicked);
    connect(ui->lineEdit,         &QLineEdit::editingFinished,                                            this, &ChatWidget::pushButton_send_clicked);
}

ChatWidget::~ChatWidget()
{
    delete ui;
}

void ChatWidget::logChat(const QString &sender, const QString &message, const QString &target)
{
    ui->textEdit->append(QString("[%1] <span style=\"color:#0000FF\">[%2] %3</span>: <span style=\"color:#008000\">%4</span>").arg(QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss"), target, sender, message));
}

/* Events */
void ChatWidget::onPlayerChatEvent(const QString &sender, const QString &message, const QString &target)
{
    logChat(sender, message, target);
}

/* Commands */
void ChatWidget::onLoginHashedCommand(bool auth)
{
    if (auth) {
        client->getCommandHandler()->sendAdminEventsEnabledCommand(true);
    }
}

/* User Interface */
void ChatWidget::comboBox_mode_currentIndexChanged(int index)
{
    ui->spinBox_duration->setEnabled(index > 0);
}

void ChatWidget::spinBox_duration_valueChanged(int index)
{
    ui->label_duration->setText(index > 1 ? tr("Seconds") : tr("Second"));
}

void ChatWidget::pushButton_send_clicked()
{
    QString message = ui->lineEdit->text();
    int target = ui->comboBox_target->currentIndex();
    int type = ui->comboBox_mode->currentIndex();
    int duration = ui->spinBox_duration->value();

    if (!message.isEmpty()) {
        PlayerSubsetType playerSubsetType;
        int parameter = 0;

        switch (target) {
        case 0:
            playerSubsetType = PlayerSubsetType::All;
            break;

        case 1:
            playerSubsetType = PlayerSubsetType::Team;
            parameter = 0;
            break;

        case 2:
            playerSubsetType = PlayerSubsetType::Team;
            parameter = 1;
            break;
        }

        switch (type) {
        case 0:
            if (parameter) {
                client->getCommandHandler()->sendAdminSayCommand(message, playerSubsetType, parameter);
            } else {
                client->getCommandHandler()->sendAdminSayCommand(message, playerSubsetType);
            }
            break;

        case 1:
            if (parameter) {
                client->getCommandHandler()->sendAdminYellCommand(message, duration, playerSubsetType, parameter);
            } else {
                client->getCommandHandler()->sendAdminYellCommand(message, duration, playerSubsetType);
            }
            break;
        }

        ui->lineEdit->clear();
    }
}
