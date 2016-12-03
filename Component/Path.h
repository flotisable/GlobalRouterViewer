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

    inline void setBelongRegion( RoutingRegion *region );

  private:

    RoutingRegion   *mBelongRegion = nullptr;
    QVector<QPoint> mPath;
};

QTextStream& operator>>( QTextStream &stream , Path &path );

inline RoutingRegion*         Path::belongRegion() const  { return mBelongRegion; }
inline QVector<QPoint>&       Path::path        ()        { return mPath; }
inline const QVector<QPoint>& Path::path        () const  { return mPath; }

inline void Path::setBelongRegion( RoutingRegion *region ) { mBelongRegion = region; }

#endif // PATH_H
