#-------------------------------------------------
#
# Project created by QtCreator 2014-10-01T00:11:49
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BinPuzzle
TEMPLATE = app


SOURCES += main.cpp\
    PuzzleGame.cpp \
    PuzzlePiece.cpp \
    PuzzleSceneItem.cpp \
    PuzzleMainView.cpp \
    PuzzleScene.cpp

HEADERS  += \
    PuzzleSceneItem.h \
    PuzzlePiece.h \
    PuzzleGame.h \
    PuzzleMainView.h \
    PuzzleScene.h

FORMS    += \
    PuzzleMainView.ui
