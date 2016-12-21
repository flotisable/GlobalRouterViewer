#include "RoutingRegion.h"

#include <algorithm>
#include <cassert>
using namespace std;

#include "Component/Pin.h"

QVector<QPoint> RoutingRegion::connectedPin( Net &net )
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

bool RoutingRegion::netConnected( Net &net )
{
  for( const Pin &pin : net.pins() )
     if(  ( mHsplit.front() <= pin.x() && pin.x() <= mHsplit.back() ) &&
          ( mVsplit.front() <= pin.y() && pin.y() <= mVsplit.back() ) )
       return true;
  return false;
}

Block* RoutingRegion::getBlock( const QString &name )
{
  auto it = find_if(  mBlocks.begin() , mBlocks.end() ,
                      [&]( const Block &block ) { return block.name() == name; } );

  return ( it != mBlocks.end() ) ? &( *it ) : nullptr;
}

const Block* RoutingRegion::getBlock( const QString &name ) const
{
  for( const Block &block : blocks() )
     if( block.name() == name ) return &block;

  return nullptr;
}
