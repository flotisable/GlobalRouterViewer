#ifndef NET_H
#define NET_H

#include <QVector>
#include <QString>
#include <QPoint>
#include <QTextStream>

#include "Pin.h"
#include "Path.h"

class Net
{
  public:

    inline Net( const QString &name = QString() );
    inline Net( const QString &name , int currentDensity );

    inline const QString&       name          () const;
    inline int                  currentDensity() const;
    inline QVector<Pin>&        pins          ();
    inline const QVector<Pin>&  pins          () const;
    inline QVector<Path>&       paths         ();
    inline const QVector<Path>& paths         () const;

    inline void setName          ( const QString  &name           );
    inline void setCurrentDensity( int            currentDensity  );

  private:

    QString mName;
    int     mCurrentDensity;

    QVector<Pin>  mPins;
    QVector<Path> mPaths;
};

QTextStream& operator>>( QTextStream &stream , Net &net );

inline Net::Net( const QString &name ) : mName( name ) {}
inline Net::Net( const QString &name , int currentDensity )
  : mName( name ) , mCurrentDensity( currentDensity ) {}

inline const QString&       Net::name           () const  { return mName;           }
inline int                  Net::currentDensity () const  { return mCurrentDensity; }
inline QVector<Pin>&        Net::pins           ()        { return mPins;           }
inline const QVector<Pin>&  Net::pins           () const  { return mPins;           }
inline QVector<Path>&       Net::paths          ()        { return mPaths;          }
inline const QVector<Path>& Net::paths          () const  { return mPaths;          }

inline void Net::setName          ( const QString &name )
{ mName = name; }
inline void Net::setCurrentDensity( int currentDensity )
{ mCurrentDensity = currentDensity; }

#endif
