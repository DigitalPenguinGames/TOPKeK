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
		DungeonScene.cpp \
        LightedDungeonScene.cpp \
		Map.cpp \
		Background.cpp \
		Tile.cpp \
		SceneChanger.cpp \
		Player.cpp \
        Enemy.cpp \
        Octorok.cpp \
        Weapon.cpp \
        RockProjectile.cpp \
		Projectile.cpp \
		Collisionable.cpp \
        Prop.cpp \
    	Fairy.cpp \
    	Effect.cpp \
        Light.cpp \
        LightSprite.cpp \
        DungeonDoor.cpp \
    GUI/Button.cpp \
    GUI/Container.cpp \
    GUI/Frame.cpp \
    GUI/ImgButton.cpp \
    GUI/ImgTextButton.cpp \
    GUI/Label.cpp \
    GUI/Layout.cpp \
    GUI/TextButton.cpp \
    GUI/VLayout.cpp \
    GUI/HLayout.cpp \
    GUI/Widget.cpp \
    TextBox.cpp \
    SoundManager.cpp \
    DataManager.cpp \
    StatsBar.cpp \
    FairyShoot.cpp \
    TextBoxManager.cpp

HEADERS += utils.hpp \
		Resources.cpp \
		Game.cpp \
		Scene.hpp \
		ScenePlayable.hpp \
		DungeonScene.hpp \
        LightedDungeonScene.hpp \
		Map.hpp \
		Background.hpp \
		Tile.hpp \
		SceneChanger.hpp \
		Player.hpp \
        Enemy.hpp \
        Octorok.hpp \
        Weapon.hpp \
        RockProjectile.hpp \
		Projectile.hpp \
		Collisionable.hpp \
        Prop.hpp \
    	Fairy.hpp \
    	Effect.hpp \
        Light.hpp \
        LightSprite.hpp \
        DungeonDoor.hpp \   
    GUI/Button.hpp \
    GUI/Container.hpp \
    GUI/ImgButton.hpp \
    GUI/ImgTextButton.hpp \
    GUI/Label.hpp \
    GUI/Layout.hpp \
    GUI/TextButton.hpp \
    GUI/VLayout.hpp \
    GUI/HLayout.hpp \
    GUI/Widget.hpp \
    GUI/Frame.hpp \
    TextBox.hpp \
    SoundManager.hpp \
    DataManager.hpp \
    StatsBar.hpp \
    FairyShoot.hpp \
    TextBoxManager.hpp
