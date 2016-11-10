#ifndef GROUP_H
#define GROUP_H

#include <QVector>
#include <QPoint>

#include "Block.h"
#include "Net.h"
#include "Symmetry.h"

class Group : public Block
{
  public:
  
    inline const QVector<double>&  hsplit    ();
    inline const QVector<double>&  vsplit    ();
    inline QVector<Symmetry>&      symmetrys ();
    inline QVector<Block>&         blocks    ();

    QVector<QPoint> connectedPin( Net &net );

    void buildSplit();
    bool netConnected( Net &net );
  
  private:

    QVector<double>    mHsplit;
    QVector<double>    mVsplit;
    QVector<Symmetry>  mSymmetrys;
    QVector<Block>     mBlocks;
};

inline const QVector<double>&  Group::hsplit   () { return mHsplit;    }
inline const QVector<double>&  Group::vsplit   () { return mVsplit;    }
inline QVector<Symmetry>&      Group::symmetrys() { return mSymmetrys; }
inline QVector<Block>&         Group::blocks   () { return mBlocks;    }

#endif
