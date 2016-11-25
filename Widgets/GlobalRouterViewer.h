#ifndef GLOBALROUTERVIEWER_H
#define GLOBALROUTERVIEWER_H

#include <QGraphicsView>

class Router;

class GlobalRouterViewer : public QGraphicsView
{
  Q_OBJECT

  public:

    GlobalRouterViewer( QWidget *parent = nullptr );
    GlobalRouterViewer( QGraphicsScene *scene , QWidget *parent = nullptr );

  public slots:

    void updateScene( Router *routingGraph );

  protected:

    void keyPressEvent( QKeyEvent *event ) Q_DECL_OVERRIDE;

  private:

    QGraphicsScene  *scene;
};

#endif // GLOBALROUTERVIEWER_H
