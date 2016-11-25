#include "Path.h"

#include "../RoutingGraph/Router.h"

QTextStream& operator>>( QTextStream &stream  , Path &path )
{
  RoutingRegion *region = new Router;
  QString       name;
  int           pathNum;

  stream >> name >> pathNum;

  region->setName( name );

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
