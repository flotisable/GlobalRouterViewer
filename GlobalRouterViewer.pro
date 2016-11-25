QT += widgets

SOURCES += \
    main.cpp \
    Component/Group.cpp \
    Component/Symmetry.cpp \
    Component/Block.cpp \
    Component/Net.cpp \
    Component/Pin.cpp \
    Component/Path.cpp \
    RoutingGraph/Router.cpp \
    RoutingGraph/RoutingRegion.cpp \
    Widgets/GlobalRouterViewer.cpp \
    Widgets/MainWindow.cpp \
    Widgets/RoutingGraphInfo.cpp

HEADERS += \
    Component/Block.h \
    Component/Group.h \
    Component/Net.h \
    Component/Pin.h \
    Component/Symmetry.h \
    Component/Path.h \
    RoutingGraph/Router.h \
    RoutingGraph/RoutingRegion.h \
    Widgets/GlobalRouterViewer.h \
    Widgets/MainWindow.h \
    Widgets/RoutingGraphInfo.h
