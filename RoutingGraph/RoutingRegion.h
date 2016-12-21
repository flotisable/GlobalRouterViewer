#ifndef ROUTINGREGION_H
#define ROUTINGREGION_H

#include <QVector>

#include "Component/Block.h"
#include "Component/Net.h"

class RoutingRegion : public Block
{
  public:

    virtual ~RoutingRegion() = default;

    inline QVector<double>&       hsplit();
    inline const QVector<double>& hsplit() const;
    inline QVector<double>&       vsplit();
    inline const QVector<double>& vsplit() const;
    inline QVector<Block>&        blocks();
    inline const QVector<Block>   blocks() const;

    QVector<QPoint> connectedPin( Net &net );

    bool                  netConnected( Net &net );
    virtual Block*        getBlock    ( const QString &name );
    virtual const Block*  getBlock    ( const QString &name ) const;

  protected:

    QVector<double> mHsplit;
    QVector<double> mVsplit;
    QVector<Block>  mBlocks;
};

inline QVector<double>&       RoutingRegion::hsplit()       { return mHsplit; }
inline const QVector<double>& RoutingRegion::hsplit() const { return mHsplit; }
inline QVector<double>&       RoutingRegion::vsplit()       { return mVsplit; }
inline const QVector<double>& RoutingRegion::vsplit() const { return mVsplit; }
inline QVector<Block>&        RoutingRegion::blocks()       { return mBlocks; }
inline const QVector<Block>   RoutingRegion::blocks() const { return mBlocks; }

#endif // ROUTINGREGION_H
