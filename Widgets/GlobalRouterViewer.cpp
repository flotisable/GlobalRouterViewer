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

  for( double x : routingGraph->hsplit() )
     scene->addLine(  x * unit , routingGraph->vsplit().front() * -unit ,
                      x * unit , routingGraph->vsplit().back () * -unit );

  for( double y : routingGraph->vsplit() )
     scene->addLine(  routingGraph->hsplit().front() * unit , y * -unit ,
                      routingGraph->hsplit().back () * unit , y * -unit );

  fitInView( scene->sceneRect() );
}

void GlobalRouterViewer::selectRegion( const QString &regionName )
{
  selectedRegion = routingGraph->getRegion( regionName );
  Q_ASSERT( selectedRegion );

  // clear previous blocks and splits
  for( QGraphicsRectItem *item : regionBlocks )
     scene->removeItem( item );

  regionBlocks.clear();

  for( QGraphicsLineItem *item : splits )
     scene->removeItem( item );

  splits.clear();
  // end clear previous blocks and splits

  if( regionName == "ALL" )
  {
    for( const Group &group : static_cast<Router*>( selectedRegion )->groups() )
       regionBlocks.push_back(
         scene->addRect(  group.left() * unit , group.bottom() * -unit ,
                          group.width() * unit , group.height() * unit ,
                          QPen( Qt::darkRed ) ,
                          QBrush( Qt::darkRed , Qt::Dense6Pattern ) ) );
  }
  else
  {
    regionBlocks.push_back(
      scene->addRect( selectedRegion->left() * unit , selectedRegion->bottom() * -unit ,
                      selectedRegion->width() * unit , selectedRegion->height() * unit ,
                      QPen( scene->palette().color( QPalette::Base ) ) ,
                      QBrush( scene->palette().color( QPalette::Base ) ) ) );

    // setup splits
    for( double x : selectedRegion->hsplit() )
       splits.push_back(
         scene->addLine( x * unit , selectedRegion->vsplit().front() * -unit ,
                         x * unit , selectedRegion->vsplit().back() * -unit ) );

    for( double y : selectedRegion->vsplit() )
       splits.push_back(
         scene->addLine( selectedRegion->hsplit().front() * unit , y * -unit ,
                         selectedRegion->hsplit().back() * unit , y * -unit ) );
    // end setup splits

    for( Symmetry &symmetry : static_cast<Group*>( selectedRegion )->symmetrys() )
       for( const Block &block : symmetry.blocks() )
          regionBlocks.push_back(
            scene->addRect( block.left() * unit , block.bottom() * -unit ,
                            block.width() * unit , block.height() * unit ,
                            QPen( Qt::blue ) , QBrush( Qt::blue , Qt::Dense6Pattern ) ) );
  }

  // setup blocks
  for( const Block &block : selectedRegion->blocks() )
     regionBlocks.push_back(
       scene->addRect(  block.left() * unit , block.bottom() * -unit ,
                        block.width() * unit , block.height() * unit ,
                        QPen( Qt::blue ) , QBrush( Qt::blue , Qt::Dense6Pattern ) ) );

  regionBlocks.push_back(
    scene->addRect( selectedRegion->left() * unit , selectedRegion->bottom() * -unit ,
                    selectedRegion->width() * unit , selectedRegion->height() * unit ,
                    QPen( Qt::red ) ) );
  // end setup blocks
}

void GlobalRouterViewer::selectBlock( const QString &blockName )
{
  if( !routingGraph ) return;
  if( selectedBlock ) scene->removeItem( selectedBlock );

  Block *block = routingGraph->getBlock( blockName );

  if( !block ) return;

  selectedBlock = scene->addRect( block->left() * unit , block->bottom() * -unit ,
                                  block->width() * unit , block->height() * unit ,
                                  QPen( Qt::red ) ,
                                  QBrush( Qt::red , Qt::Dense6Pattern ) );
}

void GlobalRouterViewer::updateNet( const QString &netName )
{
  if( !selectedRegion ) return;

  if( nets.find( netName ) == nets.end() )
  {
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

         QPen pen( ( pathT.layer() == 0 ) ? Qt::darkGreen : Qt::darkYellow );

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
                                                  pen ) );
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
  if( !routingGraph ) return;

  QVector<Net> &nets = routingGraph->nets();

  if( !selectedNet.empty() )
  {
    for( auto item : selectedNet )
       scene->removeItem( item );
    selectedNet.clear();
  }

  auto it = std::find_if( nets.begin() , nets.end() ,
                          [&]( const Net &net ) { return ( net.name() == netName ); } );

  if( it == nets.end() ) return;

  for( const Path &pathT : it->paths() )
  {
     const QVector<QPoint>  &path   = pathT.path();
     QVector<double>        &hsplit = pathT.belongRegion()->hsplit();
     QVector<double>        &vsplit = pathT.belongRegion()->vsplit();

     for( int i = 0 ; i < path.size() - 1 ; ++i )
     {
        const QPoint &p1 = path[i];
        const QPoint &p2 = path[i+1];

        double x1 = ( hsplit[p1.x()] + hsplit[p1.x()+1] ) / 2;
        double y1 = ( vsplit[p1.y()] + vsplit[p1.y()+1] ) / 2;
        double x2 = ( hsplit[p2.x()] + hsplit[p2.x()+1] ) / 2;
        double y2 = ( vsplit[p2.y()] + vsplit[p2.y()+1] ) / 2;

        selectedNet.push_back( scene->addLine(  x1 * unit , y1 * -unit ,
                                                x2 * unit , y2 * -unit ,
                                                QPen( Qt::darkGreen ) ) );
     }
  }
}

void GlobalRouterViewer::updateBlock( const QString &blockName )
{
  if( !routingGraph ) return;

  if( blocks.find( blockName ) == blocks.end() )
  {
    Block *block = routingGraph->getBlock( blockName );

    blocks.insert(  blockName ,
                    scene->addRect( block->left() * unit , block->bottom() * -unit ,
                                    block->width() * unit , block->height() * unit ,
                                    QPen( Qt::blue ) ,
                                    QBrush( Qt::blue , Qt::Dense6Pattern ) ) );
  }
  else
  {
    scene->removeItem( blocks[blockName] );
    blocks.remove( blockName );
  }
}

void GlobalRouterViewer::fitToAll()
{
  QRectF rect = scene->sceneRect();

  fitInView( rect );
}

void GlobalRouterViewer::fitToRegion()
{
  QRectF rect(  selectedRegion->left() * unit , selectedRegion->bottom() * -unit ,
                selectedRegion->width() * unit , selectedRegion->height() * unit );

  fitInView( rect );
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
