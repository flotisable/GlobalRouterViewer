#ifndef SYMMETRY_H
#define SYMMETRY_H

#include <QString>
#include <QVector>

#include "Block.h"

class Symmetry
{
  public:
  
    inline Symmetry( const QString &name = QString() );
  
    inline const QString&   name  ();
    inline QVector<Block>&  blocks();
    
    inline void setName( const QString &name );
  
  private:
  
    QString         mName;
    QVector<Block>  mBlocks;
};

inline Symmetry::Symmetry( const QString &name ) : mName( name ) {}

inline const QString&  Symmetry::name   () { return mName;    }
inline QVector<Block>& Symmetry::blocks () { return mBlocks;  }

inline void Symmetry::setName( const QString &name ) { mName = name; }

#endif
