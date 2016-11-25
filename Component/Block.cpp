#include "Block.h"

QTextStream &operator>>( QTextStream &stream, Block &block )
{
  QString name;
  QString buffer;
  double  lbX;
  double  lbY;
  double  width;
  double  height;

  stream >> name >> buffer >> lbX >> buffer >> lbY >> buffer >> width >> height;

  block.setName   ( name );
  block.setWidth  ( width );
  block.setHeight ( height );
  block.moveTopLeft( QPointF( lbX , lbY ) );

  return stream;
}
