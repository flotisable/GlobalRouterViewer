#include "Router.h"

QTextStream& operator>>( QTextStream &stream , Router &router )
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
        router.nets().push_back( net );
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
  for( Block &block : blocks() )
     if( block.name() == name ) return &block;
  return nullptr;
}
