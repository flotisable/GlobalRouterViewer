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
  
    inline QVector<Symmetry>&       symmetrys();
    inline const QVector<Symmetry>& symmetrys() const;

    virtual Block*        getBlock( const QString &name ) override;
    virtual const Block*  getBlock( const QString &name ) const override;
  
  private:

    QVector<Symmetry> mSymmetrys;
};

QTextStream& operator>>( QTextStream &stream , Group &group );

inline QVector<Symmetry>&       Group::symmetrys()        { return mSymmetrys; }
inline const QVector<Symmetry>& Group::symmetrys() const  { return mSymmetrys; }

#endif
