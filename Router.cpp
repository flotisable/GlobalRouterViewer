#include "Router.h"

QTextStream& operator>>( QTextStream &stream , Router &router )
{
  QString word;

  while( !stream.atEnd() )
  {
    word = stream.readLine();

    if( word == "Horizontal Split : " )
    {
      while( true )
      {
        word = stream.readLine();

        if( word.isEmpty() ) break;

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

    if( word == "Vertical Split : " )
    {
      while( true )
      {
        word = stream.readLine();

        if( word.isEmpty() ) break;

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

    if( word == "[ Groups ]" )
    {
      while( !stream.atEnd() )
      {
        word = stream.readLine();

        if( word.contains( "[ Group : " )  )
        {
          Group group;

          group.setName( word.section( ' ' , 3 , 3 ) );

          stream >> group;

          router.groups().push_back( group );
        }
        else if( word == "[ Blocks ]" ) break;
      }
      break;
    }
  }

  if( word == "[ Blocks ]" )
  {
    while( !stream.atEnd() )
    {
      word = stream.readLine();

      if( word.isEmpty() ) break;

      Block block;

      stream >> block;
      router.blocks().push_back( block );
    }
  }

  while( !stream.atEnd() )
  {
    word = stream.readLine();

    if( word == "[ Nets ]" )
    {
      while( !stream.atEnd() )
      {
        Net net;

        stream >> net;

        if( !net.name().isEmpty() )
        {
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
