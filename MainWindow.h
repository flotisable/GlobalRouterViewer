#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QFileDialog;
class Group;
class GlobalRouterViewer;
class RoutingGraphInfo;

class MainWindow : public QMainWindow
{
  public:

    MainWindow();

  private:

    void setupMenuBar ();
    void setupLeftDock();

    GlobalRouterViewer  *viewer;
    RoutingGraphInfo    *info;
    Group               *routingGraph;

    QFileDialog *fileDialog;

    QMenu *fileMenu;
    QMenu *windowMenu;

    QAction *openAct;
    QAction *quitAct;

    QAction *toggleLeftDockAct;
};

#endif // MAINWINDOW_H
