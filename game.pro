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
		ScenePlayable.cpp \
		OutsideScene.cpp \
		DungeonScene.cpp \
		Map.cpp \
		Tile.cpp \
		SceneChanger.cpp \
		Player.cpp \
		Projectile.cpp \
		Collisionable.cpp \
    Fairy.cpp \
    Effect.cpp

HEADERS += utils.hpp \
		Resources.cpp \
		Game.cpp \
		Scene.hpp \
		ScenePlayable.hpp \
		OutsideScene.hpp \
		DungeonScene.hpp \
		Map.hpp \
		Tile.hpp \
		SceneChanger.hpp \
		Player.hpp \
		Projectile.hpp \
		Collisionable.hpp \
    Fairy.hpp \
    Effect.hpp
