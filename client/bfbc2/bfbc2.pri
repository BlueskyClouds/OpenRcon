INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

HEADERS += bfbc2/BFBC2.h \
    bfbc2/BFBC2CommandHandler.h \
    bfbc2/BFBC2Widget.h \
    bfbc2/BFBC2Mod.h \
    bfbc2/BFBC2LevelEntry.h \
    bfbc2/BFBC2LevelDictionary.h \
    bfbc2/BFBC2ServerInfo.h

SOURCES += bfbc2/BFBC2.cpp \
    bfbc2/BFBC2CommandHandler.cpp \
    bfbc2/BFBC2Widget.cpp \
    bfbc2/BFBC2LevelDictionary.cpp

FORMS += bfbc2/BFBC2Widget.ui

RESOURCES += bfbc2/BFBC2.qrc