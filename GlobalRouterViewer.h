#ifndef GLOBALROUTERVIEWER_H
#define GLOBALROUTERVIEWER_H

#include <QGraphicsView>

class GlobalRouterViewer : public QGraphicsView
{
    Q_OBJECT

    public:

        GlobalRouterViewer( QWidget *parent = nullptr );
        GlobalRouterViewer( QGraphicsScene *scene , QWidget *parent = nullptr );

    private:

        QGraphicsScene *scene;
};

#endif // GLOBALROUTERVIEWER_H
