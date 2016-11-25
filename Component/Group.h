#ifndef GROUP_H
#define GROUP_H

#include <QVector>
#include <QPoint>
#include <QTextStream>

#include "../RoutingGraph/RoutingRegion.h"
#include "Symmetry.h"

class Group : public RoutingRegion
{
  public:
  
    inline QVector<Symmetry>& symmetrys ();

    virtual Block* getBlock( const QString &name ) override;
  
  private:

    QVector<Symmetry> mSymmetrys;
};

QTextStream& operator>>( QTextStream &stream , Group &group );

inline QVector<Symmetry>& Group::symmetrys() { return mSymmetrys; }

#endif
