#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QFileDialog;
class Router;
class GlobalRouterViewer;
class RoutingGraphInfo;

class MainWindow : public QMainWindow
{
  Q_OBJECT

  public:

    MainWindow();
    ~MainWindow();

  signals:

    void fileRead( Router *routingGraph );
    void fileRead( const QString &fileName );

  public slots:

    bool read( const QString &fileName );

  private:

    void setupMenuBar ();
    void setupLeftDock();
    void setupConnect ();

    GlobalRouterViewer  *viewer;
    RoutingGraphInfo    *info;
    Router              *routingGraph;

    QFileDialog *fileDialog;

    QMenu *fileMenu;
    QMenu *windowMenu;

    QAction *openAct;
    QAction *quitAct;

    QAction *toggleLeftDockAct;
};

#endif // MAINWINDOW_H
