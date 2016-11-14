#include "Group.h"

#include <algorithm>
using namespace std;

#include "Pin.h"

QVector<QPoint> Group::connectedPin( Net &net )
{
  QVector<QPoint> pins;

  for( const Pin &pin : net.pins() )
  {
     if(  ( mHsplit.front() <= pin.x() && pin.x() <= mHsplit.back() ) &&
          ( mVsplit.front() <= pin.y() && pin.y() <= mVsplit.back() ) )
     {
       int x;
       int y;

       for( x = 0 ; x < mHsplit.size() ; ++x )
          if( mHsplit[x] >= pin.x() )
          {
            --x;
            break;
          }
       for( y = 0 ; y < mVsplit.size() ; ++y )
          if( mVsplit[y] >= pin.y() )
          {
            --y;
            break;
          }

       pins.push_back( QPoint( x , y ) );
     }
  }
  return pins;
}

Block* Group::getBlock( const QString &name )
{
  for( Symmetry &symmetry : symmetrys() )
  {
     Block *block = symmetry.getBlock( name );

     if( block ) return block;
  }
  for( Block &block : blocks() )
     if( block.name() == name ) return &block;
  return nullptr;
}

bool Group::netConnected( Net &net )
{
  for( const Pin &pin : net.pins() )
     if(  ( mHsplit.front() <= pin.x() && pin.x() <= mHsplit.back() ) &&
          ( mVsplit.front() <= pin.y() && pin.y() <= mVsplit.back() ) )
       return true;
  return false;
}

QTextStream &operator>>(QTextStream &stream, Group &group)
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
      group.setBottom( group.vsplit().front () );
      group.setTop   ( group.vsplit().back  () );
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
