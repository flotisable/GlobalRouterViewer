#include "Net.h"

QTextStream &operator>>( QTextStream &stream, Net &net )
{
  QString             word;
  QString             name;
  double              currentDensity;
  int                 pinNum;
  int                 pathNum;

  stream >> name >> currentDensity >> pinNum >> pathNum;

  net.setName           ( name );
  net.setCurrentDensity ( currentDensity );

  for( int i = 0 ; i < pinNum ; ++i )
  {
    Pin pin;

    stream >> pin;

    net.pins().push_back( pin );
  }
  stream.readLine();

  for( int i = 0 ; i < pathNum ; ++i )
  {
    Path path;

    stream >> path;

    net.paths().push_back( path );
    stream.readLine();
  }
  return stream;
}
