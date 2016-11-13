#ifndef BLOCK_H
#define BLOCK_H

#include <QString>
#include <QRectF>
#include <QTextStream>

class Block : public QRectF
{
  public:
  
    inline Block( const QString &name = QString() );
    inline Block( const QString &name , qreal lbX , qreal lbY , qreal w , qreal h );
    inline Block( const QString &name , const QPointF &lb     , qreal w , qreal h );
    
    inline const QString& name() const;
    
    inline void setName( const QString &name );
    
  private:
  
    QString mName;
};

QTextStream& operator>>( QTextStream &stream , Block &block );

inline Block::Block( const QString &name ) : mName( name ) {}
inline Block::Block( const QString &name , qreal lbX , qreal lbY , qreal w , qreal h )
  : QRectF( lbX , lbY + h , w , h ) , mName( name ) {}
inline Block::Block( const QString &name , const QPointF &lb     , qreal w , qreal h )
  : QRectF( lb.x() , lb.y() + h , w , h ) , mName( name ) {}

inline const QString& Block::name() const { return mName; }

inline void Block::setName( const QString &name ) { mName = name; }

#endif
