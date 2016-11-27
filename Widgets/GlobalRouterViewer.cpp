#include "GlobalRouterViewer.h"

#include <QtWidgets>
#include <algorithm>

#include "../RoutingGraph/Router.h"

GlobalRouterViewer::GlobalRouterViewer( QWidget *parent ) : QGraphicsView( parent )
{
  scene = new QGraphicsScene( this );

  setScene( scene );
}

GlobalRouterViewer::GlobalRouterViewer( QGraphicsScene *scene, QWidget *parent )
    :QGraphicsView( scene , parent )
{
  this->scene = scene;

  setScene( scene );
}

void GlobalRouterViewer::setRoutingGraph( Router *routingGraph )
{
  this->routingGraph = routingGraph;
}

void GlobalRouterViewer::updateScene( Router *routingGraph )
{
  QPen pen;

  pen.setWidth( 1 );

  for( double x : routingGraph->hsplit() )
     scene->addLine(  x * unit , routingGraph->vsplit().front() * -unit ,
                      x * unit , routingGraph->vsplit().back () * -unit , pen );

  for( double y : routingGraph->vsplit() )
     scene->addLine(  routingGraph->hsplit().front() * unit , y * -unit ,
                      routingGraph->hsplit().back () * unit , y * -unit , pen );

  /*for( Group &group : routingGraph->groups() )
  {
     pen.setColor( Qt::black );
     for( double x : group.hsplit() )
        scene->addLine( x * unit , group.vsplit().front() * -unit ,
                        x * unit , group.vsplit().back () * -unit , pen );

     for( double y : group.vsplit() )
        scene->addLine( group.hsplit().front() * unit , y * -unit ,
                        group.hsplit().back () * unit , y * -unit , pen );

     pen.setColor( Qt::blue );
     for( Symmetry & symmetry : group.symmetrys() )
     {

        for( Block &block : symmetry.blocks() )
        {
           scene->addRect(  block.left() * unit , block.bottom() * -unit ,
                            block.width() * unit , block.height() * unit , pen );
        }
     }
     for( Block &block : group.blocks() )
     {
        scene->addRect( block.left() * unit , block.bottom() * -unit ,
                        block.width() * unit , block.height() * unit , pen );
     }
     pen.setColor( Qt::red );
     scene->addRect(  group.left() * unit , group.bottom() * -unit ,
                      group.width() * unit , group.height() * unit , pen );
  }*/

  /*pen.setColor( Qt::blue );
  for( Block &block : routingGraph->blocks() )
  {
     scene->addRect(  block.left() * unit , block.bottom() * -unit ,
                      block.width() * unit , block.height() * unit , pen );
  }
  pen.setColor( Qt::black );*/

  fitInView( scene->sceneRect() );
}

void GlobalRouterViewer::selectRegion( const QString &regionName )
{
  if( !routingGraph ) return;
  selectedRegion = routingGraph->getRegion( regionName );
  Q_ASSERT( selectedRegion );
}

void GlobalRouterViewer::selectBlock( const QString &blockName )
{
  Q_UNUSED( blockName )
}

void GlobalRouterViewer::updateNet( const QString &netName )
{
  if( !selectedRegion ) return;

  if( nets.find( netName ) == nets.end() )
  {
    Q_ASSERT( routingGraph );
    QVector<Net> &nets = routingGraph->nets();

    auto it = std::find_if( nets.begin() , nets.end() ,
                            [&]( const Net &net ) { return ( net.name() == netName ); } );

    if( it == nets.end() ) return;

    QList<QGraphicsLineItem*> pathItems;
    Net                       &net = *it;

    for( Path &pathT : net.paths() )
       if( pathT.belongRegion()->name() == selectedRegion->name() )
       {
         QVector<QPoint> &path    = pathT.path();
         QVector<double> &hsplit  = selectedRegion->hsplit();
         QVector<double> &vsplit  = selectedRegion->vsplit();

         for( int i = 0 ; i < path.size() - 1 ; ++i )
         {
            QPoint &p1 = path[i];
            QPoint &p2 = path[i+1];

            qreal x1 = ( hsplit[p1.x()] + hsplit[p1.x()+1] ) / 2;
            qreal x2 = ( hsplit[p2.x()] + hsplit[p2.x()+1] ) / 2;
            qreal y1 = ( vsplit[p1.y()] + vsplit[p1.y()+1] ) / 2;
            qreal y2 = ( vsplit[p2.y()] + vsplit[p2.y()+1] ) / 2;

            pathItems.push_back( scene->addLine(  x1 * unit , -y1 * unit ,
                                                  x2 * unit , -y2 * unit ,
                                                  QPen( Qt::darkGreen ) ) );
         }
         this->nets.insert( netName , pathItems );
       }
  }
  else
  {
    for( QGraphicsLineItem *item : nets[netName] )
       scene->removeItem( item );
    nets.remove( netName );
  }
}

void GlobalRouterViewer::selectNet( const QString &netName )
{
  Q_UNUSED( netName )
}

void GlobalRouterViewer::updateBlock( const QString &blockName )
{
  Q_UNUSED( blockName )
}

void GlobalRouterViewer::keyPressEvent( QKeyEvent *event )
{
  constexpr double unit = 10;

  switch( event->key() )
  {
    case Qt::Key_Z:

      switch( event->modifiers() )
      {
        case Qt::ShiftModifier:   scale( 2 , 2 );     break;
        case Qt::ControlModifier: scale( 0.5 , 0.5 ); break;
      }
      break;

    case Qt::Key_Up:    translate( 0 , -unit  ); break;
    case Qt::Key_Down:  translate( 0 , unit   ); break;
    case Qt::Key_Left:  translate( -unit  , 0 ); break;
    case Qt::Key_Right: translate( unit   , 0 ); break;

    default: break;
  }
  QGraphicsView::keyPressEvent( event );
}
