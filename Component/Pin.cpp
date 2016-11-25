#include "Pin.h"

#include "Block.h"

QTextStream& operator>>( QTextStream &stream , Pin &pin )
{
  Block   *block = new Block;
  QString name;
  QString buffer;
  double  x;
  double  y;

  stream >> name >> buffer >> x >> buffer >> y >> buffer;

  block->setName( name );

  pin.setConnect( block );
  pin.setX( x );
  pin.setY( y );

  return stream;
}
