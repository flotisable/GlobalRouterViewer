#ifndef PATH_H
#define PATH_H

#include <QVector>
#include <QTextStream>
#include <QPoint>

class RoutingRegion;

class Path
{
  public:

    inline RoutingRegion*         belongRegion() const;
    inline QVector<QPoint>&       path        ();
    inline const QVector<QPoint>& path        () const;
    inline int                    layer       () const;

    inline void setBelongRegion ( RoutingRegion *region );
    inline void setLayer        ( int           layer   );

  private:

    RoutingRegion   *mBelongRegion = nullptr;
    QVector<QPoint> mPath;
    int             mLayer;
};

QTextStream& operator>>( QTextStream &stream , Path &path );

inline RoutingRegion*         Path::belongRegion() const  { return mBelongRegion; }
inline QVector<QPoint>&       Path::path        ()        { return mPath; }
inline const QVector<QPoint>& Path::path        () const  { return mPath; }
inline int                    Path::layer       () const  { return mLayer; }

inline void Path::setBelongRegion ( RoutingRegion *region ) { mBelongRegion = region; }
inline void Path::setLayer        ( int           layer   ) { mLayer        = layer;  }

#endif // PATH_H
