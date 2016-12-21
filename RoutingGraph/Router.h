#ifndef ROUTER_H
#define ROUTER_H

#include <QVector>
#include <QTextStream>

#include "RoutingRegion.h"
#include "Component/Net.h"
#include "Component/Group.h"

class Router : public RoutingRegion
{
  public:

    inline QVector<Net>&          nets  ();
    inline const QVector<Net>&    nets  () const;
    inline QVector<Group>&        groups();
    inline const QVector<Group>&  groups() const;

    virtual Block*        getBlock  ( const QString &name ) override;
    virtual const Block*  getBlock  ( const QString &name ) const override;
    RoutingRegion*        getRegion ( const QString &name );
    const RoutingRegion*  getRegion ( const QString &name ) const;
    Net*                  getNet    ( const QString &name );
    const Net*            getNet    ( const QString &name ) const;

  private:

    QVector<Net>    mNets;
    QVector<Group>  mGroups;
};

QTextStream& operator>>( QTextStream &stream , Router &router );

inline QVector<Net>&          Router::nets  ()        { return mNets;   }
inline const QVector<Net>&    Router::nets  () const  { return mNets;   }
inline QVector<Group>&        Router::groups()        { return mGroups; }
inline const QVector<Group>&  Router::groups() const  { return mGroups; }

#endif
