#include "MainWindow.h"

#include <QtWidgets>

#include "GlobalRouterViewer.h"
#include "RoutingGraphInfo.h"
#include "Router.h"

MainWindow::MainWindow()
{
  viewer      = new GlobalRouterViewer( this );
  info        = new RoutingGraphInfo  ( this );
  fileDialog  = new QFileDialog       ( this , tr( "Open File" ) );

  fileDialog->setFileMode( QFileDialog::ExistingFile );

  setupMenuBar  ();
  setupLeftDock ();

  connect(  fileDialog  , SIGNAL( fileSelected( QString ) ) ,
            this        , SLOT  ( read( QString ) ) );
  connect(  this        , SIGNAL( fileRead( Router* ) ) ,
            info        , SLOT  ( setRoutingGraph( Router* ) ) );
  connect(  this        , SIGNAL( fileRead( const QString& ) ) ,
            info        , SLOT  ( setSourceFile( const QString& ) ) );

  setCentralWidget( viewer );
  setWindowTitle  ( tr( "Global Routing Viewer" ) );
}

bool MainWindow::read( const QString &fileName )
{
  constexpr auto openMode = QIODevice::ReadOnly | QIODevice::Text;

  QFile file( fileName );

  if( file.open( openMode ) )
  {
    QTextStream inFile( &file );
    QString     word;

    while( !inFile.atEnd() )
    {
      inFile >> word;

      if( word != "[Graph]" ) inFile >> *routingGraph;
    }
    emit fileRead( routingGraph );
    emit fileRead( fileName );

    return true;
  }
  return false;
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
