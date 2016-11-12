#include "MainWindow.h"

#include <QtWidgets>

#include "GlobalRouterViewer.h"
#include "RoutingGraphInfo.h"

MainWindow::MainWindow()
{
  viewer      = new GlobalRouterViewer( this );
  info        = new RoutingGraphInfo  ( this );
  fileDialog  = new QFileDialog       ( this , tr( "Open File" ) );

  setupMenuBar  ();
  setupLeftDock ();

  setCentralWidget( viewer );
  setWindowTitle  ( tr( "Global Routing Viewer" ) );
}

void MainWindow::setupMenuBar()
{
  fileMenu = menuBar()->addMenu( tr( "File" ) );

  openAct = fileMenu->addAction( tr( "Open" ) );
  quitAct = fileMenu->addAction( tr( "Quit" ) );

  connect( openAct , SIGNAL( triggered( bool ) ) , fileDialog , SLOT( show  () ) );
  connect( quitAct , SIGNAL( triggered( bool ) ) , this       , SLOT( close () ) );

  windowMenu = menuBar()->addMenu( tr( "Windows" ) );
}

void MainWindow::setupLeftDock()
{
  QDockWidget *dockWidget = new QDockWidget( tr( "Routing Graph Info" ) , this );

  dockWidget->setAllowedAreas( Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea );
  dockWidget->setWidget( info );
  addDockWidget( Qt::LeftDockWidgetArea , dockWidget );

  toggleLeftDockAct = dockWidget->toggleViewAction();
  windowMenu->addAction( toggleLeftDockAct );
}
