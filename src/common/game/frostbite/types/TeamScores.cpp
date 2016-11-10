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

#include "TeamScores.h"

TeamScores::TeamScores(const QList<int> &scores, int targetScore) :
    scores(scores),
    targetScore(targetScore)
{

}

TeamScores::~TeamScores()
{

}

QList<int> TeamScores::getScores() const
{
    return scores;
}

int TeamScores::getTargetScore() const
{
    return targetScore;
}