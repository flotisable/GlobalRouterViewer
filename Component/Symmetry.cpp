#include "Symmetry.h"

QTextStream &operator>>( QTextStream &stream, Symmetry &symmetry )
{
  QString word;

  while( !stream.atEnd() )
  {
    word = stream.readLine();

    if( word.contains( "Blocks : " ) )
    {
      int blockNum = word.section( ' ' , 2 , 2 ).toInt();

      for( int i = 0 ; i < blockNum ; ++i )
      {
        Block block;

        stream >> block;
        symmetry.blocks().push_back( block );
      }
      break;
    }
  }
  return stream;
}

Block* Symmetry::getBlock( const QString &name )
{
  for( Block &block : blocks() )
     if( block.name() == name ) return &block;
  return nullptr;
}
