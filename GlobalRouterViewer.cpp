#include "GlobalRouterViewer.h"

GlobalRouterViewer::GlobalRouterViewer(QWidget *parent) : QGraphicsView( parent )
{

}

GlobalRouterViewer::GlobalRouterViewer(QGraphicsScene *scene, QWidget *parent)
    :QGraphicsView( scene , parent )
{

}
