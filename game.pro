TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-window -lsfml-system

QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp \
		utils.cpp \
		Resources.cpp \
		Game.cpp \
		Scene.cpp \
		OutsideScene.cpp \
		Map.cpp

HEADERS += utils.hpp \
		Resources.cpp \
		Game.cpp \
		Scene.hpp \
		OutsideScene.hpp \
		Map.hpp
