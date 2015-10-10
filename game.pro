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
        LightedDungeonScene.cpp \
		Map.cpp \
		Background.cpp \
		Tile.cpp \
		SceneChanger.cpp \
		Player.cpp \
		Projectile.cpp \
		Collisionable.cpp \
    	Fairy.cpp \
    	Effect.cpp \
        Light.cpp \
        LightSprite.cpp \
    GUI/Button.cpp \
    GUI/Container.cpp \
    GUI/Frame.cpp \
    GUI/ImgButton.cpp \
    GUI/ImgTextButton.cpp \
    GUI/Label.cpp \
    GUI/Layout.cpp \
    GUI/TextButton.cpp \
    GUI/VLayout.cpp \
    GUI/Widget.cpp \
    TextBox.cpp

HEADERS += utils.hpp \
		Resources.cpp \
		Game.cpp \
		Scene.hpp \
		ScenePlayable.hpp \
		OutsideScene.hpp \
		DungeonScene.hpp \
        LightedDungeonScene.hpp \
		Map.hpp \
		Background.hpp \
		Tile.hpp \
		SceneChanger.hpp \
		Player.hpp \
		Projectile.hpp \
		Collisionable.hpp \
    	Fairy.hpp \
    	Effect.hpp \
        Light.hpp \
        LightSprite.hpp \
    GUI/Button.hpp \
    GUI/Container.hpp \
    GUI/ImgButton.hpp \
    GUI/ImgTextButton.hpp \
    GUI/Label.hpp \
    GUI/Layout.hpp \
    GUI/TextButton.hpp \
    GUI/VLayout.hpp \
    GUI/Widget.hpp \
    GUI/Frame.hpp \
    TextBox.hpp
