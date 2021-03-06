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

#include "BF3CommandHandler.h"
#include "FrostbiteConnection.h"
#include "FrostbiteRconPacket.h"
#include "FrostbiteUtils.h"

BF3CommandHandler::BF3CommandHandler(QObject *parent) :
    Frostbite2CommandHandler(parent)
{

}

BF3CommandHandler::~BF3CommandHandler()
{

}

bool BF3CommandHandler::parse(const QString &request, const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    typedef void (BF3CommandHandler::*ResponseFunction)(const FrostbiteRconPacket&, const FrostbiteRconPacket&);

    static QHash<QString, ResponseFunction> responseList = {
        /* Commands */
        // Admin
        { "admin.effectiveMaxPlayers",     &BF3CommandHandler::parseAdminEffectiveMaxPlayersCommand },

        // Vars
        { "vars.ranked",                   &BF3CommandHandler::parseVarsRankedCommand },
        { "vars.crossHair",                &BF3CommandHandler::parseVarsCrossHairCommand },
        { "vars.playerManDownTime",        &BF3CommandHandler::parseVarsPlayerManDownTimeCommand },
        { "vars.premiumStatus",            &BF3CommandHandler::parseVarsPremiumStatusCommand },
        { "vars.bannerUrl",                &BF3CommandHandler::parseVarsBannerUrlCommand },
        { "vars.roundsPerMap",             &BF3CommandHandler::parseVarsRoundsPerMapCommand }

    };

    if (responseList.contains(request)) {
        ResponseFunction response = responseList[request];

        if (response) {
            (this->*response)(packet, lastSentPacket);
        }

        return true;
    }

    return Frostbite2CommandHandler::parse(request, packet, lastSentPacket);
}

/* Send commands */
// Admin
void BF3CommandHandler::sendAdminEffectiveMaxPlayersCommand()
{
    connection->sendCommand("admin.effectiveMaxPlayers");
}

// Variables
void BF3CommandHandler::sendVarsRankedCommand()
{
    connection->sendCommand("vars.ranked");
}

void BF3CommandHandler::sendVarsRankedCommand(bool ranked)
{
    connection->sendCommand(QString("\"vars.ranked\" \"%1\"").arg(FrostbiteUtils::toString(ranked)));
}

void BF3CommandHandler::sendVarsCrossHairCommand()
{
    connection->sendCommand("vars.crossHair");
}

void BF3CommandHandler::sendVarsCrossHairCommand(bool enabled)
{
    connection->sendCommand(QString("\"vars.crossHair\" \"%1\"").arg(FrostbiteUtils::toString(enabled)));
}

void BF3CommandHandler::sendVarsPlayerManDownTimeCommand(int percent)
{
    QString command;

    if (percent < 0) {
        command = "vars.playerManDownTime";
    } else {
        command = QString("\"vars.playerManDownTime\" \"%1\"").arg(percent);
    }

    connection->sendCommand(command);
}

void BF3CommandHandler::sendVarsPremiumStatusCommand()
{
     connection->sendCommand("vars.premiumStatus");
}

void BF3CommandHandler::sendVarsPremiumStatusCommand(bool enabled)
{
     connection->sendCommand(QString("\"vars.premiumStatus\" \"%1\"").arg(FrostbiteUtils::toString(enabled)));
}

void BF3CommandHandler::sendVarsBannerUrlCommand(const QString &bannerUrl)
{
    QString command;

    if (bannerUrl.isEmpty()) {
        command = "vars.bannerUrl";
    } else {
        command = QString("\"vars.bannerUrl\" \"%1\"").arg(bannerUrl);
    }

    connection->sendCommand(command);
}

void BF3CommandHandler::sendVarsRoundsPerMapCommand(int rounds)
{
    QString command;

    if (rounds < 0) {
        command = "vars.roundsPerMap";
    } else {
        command = QString("\"vars.roundsPerMap\" \"%1\"").arg(rounds);
    }

    connection->sendCommand(command);
}

/* Parse commands */
// Admin
void BF3CommandHandler::parseAdminEffectiveMaxPlayersCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() >= 1) {
        int effectiveMaxPlayers = FrostbiteUtils::toInt(packet.getWord(1).getContent());

        emit (onAdminEffectiveMaxPlayersCommand(effectiveMaxPlayers));
    }
}

// Variables
void BF3CommandHandler::parseVarsRankedCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() >= 1 && lastSentPacket.getWordCount() == 1) {
        bool ranked = FrostbiteUtils::toBool(packet.getWord(1).getContent());

        emit (onVarsRankedCommand(ranked));
    }
}

void BF3CommandHandler::parseVarsCrossHairCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() >= 1 && lastSentPacket.getWordCount() == 1) {
        bool enabled = FrostbiteUtils::toInt(packet.getWord(1).getContent());

        emit (onVarsCrossHairCommand(enabled));
    }
}

void BF3CommandHandler::parseVarsPlayerManDownTimeCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() >= 1 && lastSentPacket.getWordCount() == 1) {
        int percent = FrostbiteUtils::toInt(packet.getWord(1).getContent());

        emit (onVarsPlayerManDownTimeCommand(percent));
    }
}

void BF3CommandHandler::parseVarsPremiumStatusCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() >= 1 && lastSentPacket.getWordCount() == 1) {
        bool enabled = FrostbiteUtils::toBool(packet.getWord(1).getContent());

        emit (onVarsPremiumStatusCommand(enabled));
    }
}

void BF3CommandHandler::parseVarsBannerUrlCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() >= 1 && lastSentPacket.getWordCount() == 1) {
        QString bannerUrl = packet.getWord(1).getContent();

        emit (onVarsBannerUrlCommand(bannerUrl));
    }
}

void BF3CommandHandler::parseVarsRoundsPerMapCommand(const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(lastSentPacket);

    QString response = packet.getWord(0).getContent();

    if (response == "OK" && packet.getWordCount() >= 1 && lastSentPacket.getWordCount() == 1) {
        int rounds = FrostbiteUtils::toInt(packet.getWord(1).getContent());

        emit (onVarsRoundsPerMapCommand(rounds));
    }
}
