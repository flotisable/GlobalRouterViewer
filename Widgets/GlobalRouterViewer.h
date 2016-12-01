#ifndef GLOBALROUTERVIEWER_H
#define GLOBALROUTERVIEWER_H

#include <QGraphicsView>
#include <QMap>

class Router;
class RoutingRegion;

class GlobalRouterViewer : public QGraphicsView
{
  Q_OBJECT

  public:

    GlobalRouterViewer( QWidget *parent = nullptr );
    GlobalRouterViewer( QGraphicsScene *scene , QWidget *parent = nullptr );

  public slots:

    void setRoutingGraph( Router *routingGraph );
    void selectRegion   ( const QString &regionName );
    void selectBlock    ( const QString &blockName );
    void updateNet      ( const QString &netName );
    void selectNet      ( const QString &netName );
    void updateBlock    ( const QString &blockName );
    void fitToAll       ();
    void fitToRegion    ();

  protected:

    void keyPressEvent( QKeyEvent *event ) Q_DECL_OVERRIDE;

  private:

    static constexpr double unit = 10;

    QGraphicsScene *scene;

    Router *routingGraph = nullptr;

    RoutingRegion             *selectedRegion = nullptr;
    QList<QGraphicsLineItem*> splits;
    QList<QGraphicsRectItem*> regionBlocks;
    QList<QGraphicsRectItem*> symmetryBlocks;

    QMap<QString,QList<QGraphicsLineItem*>> nets;
    QMap<QString,QGraphicsRectItem*>        blocks;

};

#endif // GLOBALROUTERVIEWER_H
