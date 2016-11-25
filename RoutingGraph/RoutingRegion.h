#ifndef ROUTINGREGION_H
#define ROUTINGREGION_H

#include <QVector>

#include "Component/Block.h"
#include "Component/Net.h"

class RoutingRegion : public Block
{
  public:

    virtual ~RoutingRegion() = default;

    inline QVector<double>&  hsplit();
    inline QVector<double>&  vsplit();
    inline QVector<Block>&   blocks();

    QVector<QPoint> connectedPin( Net &net );

    bool            netConnected( Net &net );
    virtual Block*  getBlock    ( const QString &name );

  protected:

    QVector<double> mHsplit;
    QVector<double> mVsplit;
    QVector<Block>  mBlocks;
};

inline QVector<double>& RoutingRegion::hsplit() { return mHsplit; }
inline QVector<double>& RoutingRegion::vsplit() { return mVsplit; }
inline QVector<Block>&  RoutingRegion::blocks() { return mBlocks; }

#endif // ROUTINGREGION_H
