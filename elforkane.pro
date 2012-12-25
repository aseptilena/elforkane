#****************************************************************************
#   elforkane Copyright (C) 2012 yahia nouah <yahiaui@gmail.com>
#
#      This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.
#      This is free software, and you are welcome to redistribute it
#      under certain conditions; type `show c' for details.
#
#  The hypothetical commands `show w' and `show c' should show the appropriate
#  parts of the General Public License.  Of course, your program's commands
#  might be different; for a GUI interface, you would use an "about box".
#
#    You should also get your employer (if you work as a programmer) or school,
#  if any, to sign a "copyright disclaimer" for the program, if necessary.
#  For more information on this, and how to apply and follow the GNU GPL, see
#  <http://www.gnu.org/licenses/>.
#
#    The GNU General Public License does not permit incorporating your program
#  into proprietary programs.  If your program is a subroutine library, you
#  may consider it more useful to permit linking proprietary applications with
#  the library.  If this is what you want to do, use the GNU Lesser General
#  Public License instead of this License.  But first, please read
#  <http://www.gnu.org/philosophy/why-not-lgpl.html>.
# ----------------------------------------------------------
# If you have questions regarding the use of this file, please contact
# yahia nouah (yahiaui@gmail.com)
# $elforkane_END_LICENSE$
#
#**************************************************************************
#-------------------------------------------------
#
# Project created by QtCreator 2011-12-23T17:36:01
#
#-------------------------------------------------

QT       += core gui phonon  sql  network



OBJECTS_DIR = usr
MOC_DIR = usr
UI_DIR = usr
INCLUDEPATH += usr
TARGET =elforkane

win32 {

    debug:DESTDIR = usr/bin
    release:DESTDIR = usr/bin
    RC_FILE = myapp.rc
}else{
DESTDIR = usr/bin
}
SOURCES += main.cpp\
        mainwindow.cpp \
    database.cpp \
    dialogaddreciter.cpp \
    dialogoption.cpp \
    dialogabout.cpp\
    sceenbase.cpp \
    network.cpp


HEADERS  += mainwindow.h \
    database.h \
    dialogaddreciter.h \
    dialogoption.h \
    dialogabout.h\
    fullinterface.h \
    sceenbase.h \
    network.h

FORMS    += mainwindow.ui \
    dialogaddreciter.ui \
    dialogoption.ui \
    dialogabout.ui

RESOURCES += \
    img.qrc


TRANSLATIONS    =usr/share/elforkane/language/elforkane_ar.ts\
usr/share/elforkane/language/elforkane_fr.ts\
usr/share/elforkane/language/elforkane_en.ts
CODECFORTR = UTF-8






# install

MKDIR = mkdir -p /usr/share/elforkane

 data.files =usr/share/elforkane*
 data.path=/usr/share/

 desktopfile.files = elforkane.desktop
 desktopfile.path = /usr/share/applications

 icon.files = usr/share/icons/hicolor/22x22/apps/elforkane.png
 icon.path = /usr/share/icons/hicolor/22x22/apps
 icon1.files = usr/share/icons/hicolor/24x24/apps/elforkane.png
 icon1.path = /usr/share/icons/hicolor/24x24/apps
 icon2.files = usr/share/icons/hicolor/32x32/apps/elforkane.png
 icon2.path = /usr/share/icons/hicolor/32x32/apps
 icon3.files = usr/share/icons/hicolor/48x48/apps/elforkane.png
 icon3.path = /usr/share/icons/hicolor/48x48/apps
 icon4.files = usr/share/icons/hicolor/64x64/apps/elforkane.png
 icon4.path = /usr/share/icons/hicolor/64x64/apps
 icon5.files = usr/share/icons/hicolor/scalable/apps/elforkane.svg
 icon5.path = /usr/share/icons/hicolor/scalable/apps

 target.path = /usr/bin

 INSTALLS +=    data \
                target \
                desktopfile\
                icon\
                icon1\
                icon2\
                icon3\
                icon4\
                icon5











