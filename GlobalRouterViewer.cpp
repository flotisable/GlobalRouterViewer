#include "GlobalRouterViewer.h"

#include <QtWidgets>

#include "Router.h"

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

void GlobalRouterViewer::updateScene( Router *routingGraph )
{
  constexpr double unit = 10;

  QPen pen;

  pen.setWidth( 1 );

  for( double x : routingGraph->hsplit() )
     scene->addLine(  x * unit , routingGraph->vsplit().front() * -unit ,
                      x * unit , routingGraph->vsplit().back () * -unit , pen );

  for( double y : routingGraph->vsplit() )
     scene->addLine(  routingGraph->hsplit().front() * unit , y * -unit ,
                      routingGraph->hsplit().back () * unit , y * -unit , pen );

  for( Group &group : routingGraph->groups() )
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
  }

  pen.setColor( Qt::blue );
  for( Block &block : routingGraph->blocks() )
  {
     scene->addRect(  block.left() * unit , block.bottom() * -unit ,
                      block.width() * unit , block.height() * unit , pen );
  }
  pen.setColor( Qt::black );

  for( Net &net : routingGraph->nets() )
  {
     for( int i = 0 ; i < net.path().size() - 1 ; ++i )
     {

     }
  }
  fitInView( scene->sceneRect() );
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
