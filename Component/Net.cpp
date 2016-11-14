#include "Net.h"

#include <QRegularExpression>

#include "Block.h"

QTextStream &operator>>( QTextStream &stream, Net &net )
{
  QString             word;
  QRegularExpression  sep( R"( +)" );

  word = stream.readLine();

  if( !word.isEmpty() )
  {
    net.setName           ( word.section( ' ' , 0 , 0 ) );
    net.setCurrentDensity ( word.section( ' ' , 1 , 1 ).toDouble() );
  }

  word = stream.readLine();

  while( !word.isEmpty() )
  {
    QString pinWord = word.section( sep , 0 , 5 );
    Pin     pin;

    word = word.section( sep , 6 );

    pin.setConnect( new Block( pinWord.section( sep , 0 , 0 ) ) );
    pin.setX      ( pinWord.section( sep , 2 , 2 ).toDouble() );
    pin.setY      ( pinWord.section( sep , 4 , 4 ).toDouble() );

    net.pins().push_back( pin );
  }

  word = stream.readLine();

  while( !word.isEmpty() )
  {
    QString pointWord = word.section( sep , 0 , 4 );

    word = word.section( sep , 5 );

    net.path().push_back( QPoint( pointWord.section( sep , 1 , 1 ).toInt() ,
                                  pointWord.section( sep , 3 , 3 ).toInt() ) );
  }
  stream.readLine();

  return stream;
}
