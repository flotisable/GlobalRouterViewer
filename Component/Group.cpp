#include "Group.h"

#include <algorithm>
using namespace std;

#include "Pin.h"

QTextStream &operator>>( QTextStream &stream, Group &group )
{
  QString word;

  while( !stream.atEnd() )
  {
    word = stream.readLine();

    if( word.contains( "Horizontal Split : " ) )
    {
      int splitNum = word.section( ' ' , 3 , 3 ).toInt();

      for( int i = 0 ; i < splitNum ; ++i )
      {
        word = stream.readLine();
        group.hsplit().push_back( word.toDouble() );
      }
      group.setLeft  ( group.hsplit().front () );
      group.setRight ( group.hsplit().back  () );
      break;
    }
  }

  while( !stream.atEnd() )
  {
    word = stream.readLine();

    if( word.contains( "Vertical Split : " ) )
    {
      int splitNum = word.section( ' ' , 3 , 3 ).toInt();

      for( int i = 0 ; i < splitNum ; ++i )
      {
        word = stream.readLine();
        group.vsplit().push_back( word.toDouble() );
      }
      group.setTop   ( group.vsplit().front () );
      group.setBottom( group.vsplit().back  () );
      break;
    }
  }

  while( !stream.atEnd() )
  {
    word = stream.readLine();

    if( word.contains( "Symmetrys : " ) )
    {
      int SymmetryNum = word.section( ' ' , 2 , 2 ).toInt();

      for( int i = 0 ; !stream.atEnd() && i < SymmetryNum ; )
      {
        word = stream.readLine();

        if( word.contains( "[ Symmetry : " )  )
        {
          Symmetry symmetry;

          symmetry.setName( word.section( ' ' , 3 , 3 ) );

          stream >> symmetry;

          group.symmetrys().push_back( symmetry );
          ++i;
        }
      }
      break;
    }
  }

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
        group.blocks().push_back( block );
      }
      break;
    }
  }

  return stream;
}


Block* Group::getBlock( const QString &name )
{
  for( Symmetry &symmetry : symmetrys() )
  {
     Block *block = symmetry.getBlock( name );

     if( block ) return block;
  }
  return RoutingRegion::getBlock( name );
}

const Block* Group::getBlock( const QString &name ) const
{
  for( const Symmetry &symmetry : symmetrys() )
  {
     const Block *block = symmetry.getBlock( name );

     if( block ) return block;
  }
  return RoutingRegion::getBlock( name );
}
