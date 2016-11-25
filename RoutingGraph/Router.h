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

    inline QVector<Net>&    nets  ();
    inline QVector<Group>&  groups();

    virtual Block* getBlock ( const QString &name ) override;
    RoutingRegion* getRegion( const QString &name );

  private:

    QVector<Net>    mNets;
    QVector<Group>  mGroups;
};

QTextStream& operator>>( QTextStream &stream , Router &router );

inline QVector<Net>&    Router::nets  () { return mNets;    }
inline QVector<Group>&  Router::groups() { return mGroups;  }

#endif
