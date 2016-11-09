#include <QApplication>

#include "GlobalRouterViewer.h"

int main( int argc , char *argv[] )
{
    QApplication        app( argc , argv );
    GlobalRouterViewer  viewer;

    viewer.show();

    return app.exec();
}
