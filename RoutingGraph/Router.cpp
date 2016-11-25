#include "Router.h"

QTextStream& operator>>( QTextStream &stream , Router &router )
{
  QString word;

  router.setName( "ALL" );

  while( !stream.atEnd() )
  {
    word = stream.readLine();

    if( word.contains( "Horizontal Split : " ) )
    {
      int splitNum = word.section( ' ' , 3 , 3 ).toInt();

      for( int i = 0 ; i < splitNum ; ++i )
      {
        word = stream.readLine();
        router.hsplit().push_back( word.toDouble() );
      }
      router.setLeft  ( router.hsplit().front () );
      router.setRight ( router.hsplit().back  () );
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
        router.vsplit().push_back( word.toDouble() );
      }
      router.setBottom( router.vsplit().front () );
      router.setTop   ( router.vsplit().back  () );
      break;
    }
  }

  while( !stream.atEnd() )
  {
    word = stream.readLine();

    if( word.contains( "Groups : " ) )
    {
      int groupNum = word.section( ' ' , 2 , 2 ).toInt();

      for( int i = 0 ; !stream.atEnd() && i < groupNum ; )
      {
        word = stream.readLine();

        if( word.contains( "[ Group : " )  )
        {
          Group group;

          group.setName( word.section( ' ' , 3 , 3 ) );

          stream >> group;

          router.groups().push_back( group );
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
        router.blocks().push_back( block );
      }
      break;
    }
  }

  while( !stream.atEnd() )
  {
    word = stream.readLine();

    if( word.contains( "Nets : " ) )
    {
      int netNum = word.section( ' ' , 2 , 2 ).toInt();

      for( int i = 0 ; i < netNum ; ++i )
      {
        Net net;

        stream >> net;

        for( Pin &pin : net.pins() )
        {
           Block *block = pin.connect();

           pin.setConnect( router.getBlock( block->name() ) );
           delete block;
        }
        for( Path &path : net.paths() )
        {
           RoutingRegion *region = path.belongRegion();

           path.setBelongRegion( router.getRegion( region->name() ) );
           delete region;
        }
        router.nets().push_back( net );

        stream.readLine();
      }
    }
  }

  return stream;
}

Block* Router::getBlock( const QString & name )
{
  for( Group &group : groups() )
  {
    Block *block = group.getBlock( name );

    if( block ) return block;
  }
  return RoutingRegion::getBlock( name );
}

RoutingRegion* Router::getRegion( const QString &name )
{
  if( this->name() == name ) return this;

  for( Group &group : groups() )
     if( group.name() == name ) return &group;

  return nullptr;
}
