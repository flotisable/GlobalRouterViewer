#ifndef PIN_H
#define PIN_H

#include <QPointF>
#include <QTextStream>

class Block;

class Pin : public QPointF
{
  public:

    inline Pin( Block* const connect = nullptr );
    inline Pin( Block* const connect , const QPoint &p );
    inline Pin( Block* const connect , qreal x , qreal y );

    inline Block* connect() const;

    inline void setConnect( Block* const connect );

  private:

    Block *mConnect;
};

QTextStream& operator>>( QTextStream &stream , Pin &pin );

inline Pin::Pin( Block* const connect ) : mConnect( connect ) {}
inline Pin::Pin( Block* const connect , const QPoint &p )
  : QPointF( p ) , mConnect( connect ) {}
inline Pin::Pin( Block* const connect , qreal x , qreal y )
  : QPointF( x , y ) , mConnect( connect ) {}

inline Block* Pin::connect() const { return mConnect; }

inline void Pin::setConnect( Block* const connect ) { mConnect = connect; }

#endif
