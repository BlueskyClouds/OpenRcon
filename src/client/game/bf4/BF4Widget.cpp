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

#include "BF4Widget.h"

BF4Widget::BF4Widget(BF4Client *client, QWidget *parent) :
    Frostbite2Widget(client, parent)
{
    commandList += {
        "admin.shutdown",
        "fairFight.activate",
        "fairFight.deactivate",
        "fairFight.isActive",
        "spectatorList.add",
        "spectatorList.clear",
        "spectatorList.list",
        "spectatorList.remove",
        "spectatorList.save",
        "vars.alwaysAllowSpectators",
        "vars.skillBasedBalance",
        "vars.commander",
        "vars.forceReloadWholeMags",
        "vars.hitIndicatorsEnabled",
        "vars.maxSpectators",
        "vars.mpExperience",
        "vars.preset",
        "vars.roundTimeLimit",
        "vars.roundWarmupTimeout",
        "vars.serverType",
        "vars.teamFactionOverride",
        "vars.ticketBleedRate",
        "vars.roundPlayersReadyBypassTimer",
        "vars.roundPlayersReadyMinCount",
        "vars.roundPlayersReadyPercent",
        "vars.isNoobOnlyJoin"
    };
}

BF4Widget::~BF4Widget()
{

}
