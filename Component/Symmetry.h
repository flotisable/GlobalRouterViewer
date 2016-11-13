#ifndef SYMMETRY_H
#define SYMMETRY_H

#include <QString>
#include <QVector>
#include <QTextStream>

#include "Block.h"

class Symmetry
{
  public:
  
    inline Symmetry( const QString &name = QString() );
  
    inline const QString&   name  () const;
    inline QVector<Block>&  blocks();
    
    inline void setName( const QString &name );

    Block* getBlock( const QString &name );
  
  private:
  
    QString         mName;
    QVector<Block>  mBlocks;
};

QTextStream& operator>>( QTextStream &stream , Symmetry &symmetry );

inline Symmetry::Symmetry( const QString &name ) : mName( name ) {}

inline const QString&  Symmetry::name   () const  { return mName;    }
inline QVector<Block>& Symmetry::blocks ()        { return mBlocks;  }

inline void Symmetry::setName( const QString &name ) { mName = name; }

#endif
