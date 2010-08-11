win32:LIBS += -L../lib/SDL-1.2.14/lib \
    -L../lib/SDL_ttf-2.0.10/lib \
    -L../lib/SDL_mixer-1.2.11/lib \
    -L../lib/SDL_image-1.2.10/lib \
    -L/usr/local/lib \
    -llibSDL \
    -lSDL_image \
    -lSDL_ttf \
    -l \
    SDL_mixer \
    -lws2_32
INCLUDEPATH = ../lib/SDL-1.2.14/include/SDL;../lib/SDL_ttf-2.0.10/include;../lib/SDL_mixer-1.2.11/include;../lib/SDL_image-1.2.10/include
OTHER_FILES += GPL.txt \
    config.cfg
HEADERS += Window.h \
    Widget.h \
    VersionNotMatchScene.h \
    Timer.h \
    Threading.h \
    TextEdit.h \
    Surface.h \
    SpriteID.h \
    SpriteBank.h \
    Sprite.h \
    SoundBank.h \
    Socket.h \
    SignupScene.h \
    SelectServerScene.h \
    SelectCharScene.h \
    Scene.h \
    NetSock.h \
    NetMessages.h \
    Mouse.h \
    MessageDialog.h \
    MenuScene.h \
    LoginScene.h \
    LoadingScene.h \
    Label.h \
    GlobalDef.h \
    Game.h \
    Font.h \
    ExitScene.h \
    Event.h \
    CreateNewCharScene.h \
    ConnectingWidget.h \
    Config.h \
    Character.h \
    Buffers.h \
    PlayGroundScene.h \
    Player.h \
    Map.h \
    Logger.h
SOURCES += Window.cpp \
    Widget.cpp \
    VersionNotMatchScene.cpp \
    Timer.cpp \
    Threading.cpp \
    TextEdit.cpp \
    Surface.cpp \
    SpriteBank.cpp \
    Sprite.cpp \
    SoundBank.cpp \
    Socket.cpp \
    SignupScene.cpp \
    SelectServerScene.cpp \
    SelectCharScene.cpp \
    Scene.cpp \
    NetSock.cpp \
    Mouse.cpp \
    MessageDialog.cpp \
    MenuScene.cpp \
    main.cpp \
    LoginScene.cpp \
    LoadingScene.cpp \
    Label.cpp \
    Game.cpp \
    Font.cpp \
    ExitScene.cpp \
    Event.cpp \
    CreateNewCharScene.cpp \
    ConnectingWidget.cpp \
    Config.cpp \
    PlayGroundScene.cpp \
    Player.cpp \
    Map.cpp \
    Logger.cpp
