SOURCES += main.cpp twitter.cpp
HEADERS += twitter.h

include (oauth/oauth.pri)

CONFIG -= app_bundle

QT += network