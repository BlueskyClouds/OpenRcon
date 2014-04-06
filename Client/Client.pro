include(locale/Locale.pri)

include(frostbite/Frostbite.pri)
include(bfbase/BFBase.pri)

include(bfbc2/BFBC2.pri)
include(bf3/BF3.pri)
include(bf4/BF4.pri)

include(minecraft/Minecraft.pri)

QT += core \
      gui \
      network \
      webkitwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OpenRcon
TEMPLATE = app

INCLUDEPATH += frostbite \
               bfbase \
               bfbc2 \
               bf3 \
               bf4 \
               minecraft

DEPENDPATH += frostbite \
              bfbase \
              bfbc2 \
              bf3 \
              bf4 \
              minecraft

HEADERS += OpenRcon.h \
    About.h \
    Connection.h \
    ConnectionManager.h \
    ConnectionTabWidget.h \
    Constants.h \
    Directory.h \
    ServerListDialog.h \
    ServerEditDialog.h \
    ServerEntry.h \
    ServerTableModel.h \
    SettingsDialog.h \
    DragDropListWidget.h \
    DragDropTreeWidget.h \
    SettingsManager.h \
    Game.h \
    GameEntry.h

SOURCES += OpenRcon.cpp \
    About.cpp \
    Connection.cpp \
    ConnectionManager.cpp \
    Directory.cpp \
    Main.cpp \
    ServerListDialog.cpp \
    ServerEditDialog.cpp \
    ServerTableModel.cpp \
    SettingsDialog.cpp \
    DragDropListWidget.cpp \
    DragDropTreeWidget.cpp \
    SettingsManager.cpp \
    Game.cpp

FORMS += About.ui \
    OpenRcon.ui \
    ServerListDialog.ui \
    ServerEditDialog.ui \
    SettingsDialog.ui

RESOURCES += OpenRcon.qrc

win32:RC_FILE = openrcon.rc

macx {
    TARGET = OpenRcon
    ICON = openrcon.icns
    QMAKE_INFO_PLIST = Info.plist
}
