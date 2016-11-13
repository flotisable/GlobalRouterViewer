#include "Symmetry.h"

QTextStream &operator>>( QTextStream &stream, Symmetry &symmetry )
{
  QString word;

  while( !stream.atEnd() )
  {
    if( word == "Blocks :" )
    {
      while( !stream.atEnd() )
      {
        word = stream.readLine();

        if( word.isEmpty() ) break;

        Block block;

        stream >> block;
        symmetry.blocks().push_back( block );
      }
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
