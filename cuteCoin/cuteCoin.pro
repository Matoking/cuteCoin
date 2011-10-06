# Add more folders to ship with the application, here
folder_01.source = qml/cuteCoin
folder_01.target = qml
DEPLOYMENTFOLDERS = folder_01

# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH =

symbian:TARGET.UID3 = 0xE6CC492F

# Smart Installer package's UID
# This UID is from the protected range and therefore the package will
# fail to install if self-signed. By default qmake uses the unprotected
# range value if unprotected UID is defined for the application and
# 0x2002CCCF value if protected UID is given to the application
symbian:DEPLOYMENT.installer_header = 0xA000D7CE

# Allow network access on Symbian
symbian:TARGET.CAPABILITY += NetworkServices
QT += network


ICON = cuteCoin.svg
TARGET = cuteCoin
VERSION = 0.5.0

# If your application uses the Qt Mobility libraries, uncomment the following
# lines and add the respective components to the MOBILITY variable.
# CONFIG += mobility
# MOBILITY +=

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += main.cpp \
    Base.cpp \
    Networking.cpp \
    json.cpp \
    MinerParse.cpp

# Please do not modify the following two lines. Required for deployment.
include(qmlapplicationviewer/qmlapplicationviewer.pri)
qtcAddDeployment()

OTHER_FILES +=

HEADERS += \
    Base.h \
    Networking.h \
    json.h \
    MinerParse.h

RESOURCES +=
