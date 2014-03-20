/*
Copyright (C) 2010 The OpenRcon Project.

This file is part of OpenRcon.

OpenRcon is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

OpenRcon is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with OpenRcon.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef ORPLUGIN_GLOBAL_H
#define ORPLUGIN_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(ORPLUGIN_LIBRARY)
#  define ORPLUGINSHARED_EXPORT Q_DECL_EXPORT
#else
#  define ORPLUGINSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // ORPLUGIN_GLOBAL_H
