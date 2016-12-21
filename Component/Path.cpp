#include "Path.h"

#include "../RoutingGraph/Router.h"

QTextStream& operator>>( QTextStream &stream  , Path &path )
{
  RoutingRegion *region = new Router;
  QString       name;
  int           pathLayer;
  int           pathNum;

  stream >> name >> pathLayer >> pathNum;

  region->setName( name );

  path.setLayer( pathLayer );
  path.setBelongRegion( region );

  for( int i = 0 ; i < pathNum ; ++i )
  {
     QString buffer;
     double x;
     double y;

     stream >> buffer >> x >> buffer >> y >> buffer;

     path.path().push_back( QPoint( x , y ) );
  }
  return stream;
}
