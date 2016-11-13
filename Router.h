#ifndef ROUTER_H
#define ROUTER_H

#include <QRectF>
#include <QVector>
#include <QTextStream>

#include "Component/Net.h"
#include "Component/Block.h"
#include "Component/Group.h"

class Router : public QRectF
{
  public:

    inline QVector<double>& hsplit();
    inline QVector<double>& vsplit();
    inline QVector<Net>&    nets  ();
    inline QVector<Group>&  groups();
    inline QVector<Block>&  blocks();

    Block* getBlock( const QString &name );

  private:

    QVector<double>  mHsplit;
    QVector<double>  mVsplit;
    QVector<Net>     mNets;
    QVector<Group>   mGroups;
    QVector<Block>   mBlocks;
};

QTextStream& operator>>( QTextStream &stream , Router &router );

inline QVector<double>& Router::hsplit() { return mHsplit;  }
inline QVector<double>& Router::vsplit() { return mVsplit;  }
inline QVector<Net>&    Router::nets  () { return mNets;    }
inline QVector<Group>&  Router::groups() { return mGroups;  }
inline QVector<Block>&  Router::blocks() { return mBlocks;  }

#endif
