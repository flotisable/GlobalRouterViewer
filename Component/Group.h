#ifndef GROUP_H
#define GROUP_H

#include <QVector>
#include <QPoint>
#include <QTextStream>

#include "Block.h"
#include "Net.h"
#include "Symmetry.h"

class Group : public Block
{
  public:
  
    inline QVector<double>&   hsplit    ();
    inline QVector<double>&   vsplit    ();
    inline QVector<Symmetry>& symmetrys ();
    inline QVector<Block>&    blocks    ();

    QVector<QPoint> connectedPin( Net &net );
    Block*          getBlock    ( const QString &name );

    bool netConnected( Net &net );
  
  private:

    QVector<double>   mHsplit;
    QVector<double>   mVsplit;
    QVector<Symmetry> mSymmetrys;
    QVector<Block>    mBlocks;
};

QTextStream& operator>>( QTextStream &stream , Group &group );

inline QVector<double>&   Group::hsplit   () { return mHsplit;    }
inline QVector<double>&   Group::vsplit   () { return mVsplit;    }
inline QVector<Symmetry>& Group::symmetrys() { return mSymmetrys; }
inline QVector<Block>&    Group::blocks   () { return mBlocks;    }

#endif
