#include "RoutingGraphInfo.h"

#include <QtWidgets>
#include <algorithm>
using namespace std;

#include "../RoutingGraph/Router.h"

RoutingGraphInfo::RoutingGraphInfo( QWidget *parent )
  : RoutingGraphInfo( nullptr , parent )
{
}

RoutingGraphInfo::RoutingGraphInfo( Router *routingGraph, QWidget *parent )
  : QWidget( parent )
{
  this->routingGraph  = routingGraph;
  blockMapper         = new QSignalMapper( this );
  netMapper           = new QSignalMapper( this );

  setupWidgets();
  setupConnect();
}

void RoutingGraphInfo::setRoutingGraph( Router *routingGraph )
{
  this->routingGraph = routingGraph;
  emit routingGraphChanged( routingGraph );
}

void RoutingGraphInfo::setSourceFile( const QString &fileName )
{
  sourceFileLabel->setText( fileName );
}

void RoutingGraphInfo::updateInfo()
{
  QVBoxLayout *layout;
  QCheckBox   *checkBox;

  groupCombo->clear();
  symmetryCombo->clear();
  blockCombo->clear();
  netCombo->clear();

  // set nets
  if( netGroupBox->layout() ) delete netGroupBox->layout();

  layout = new QVBoxLayout;
  netGroupBox->setLayout( layout );

  for( const Net &net : routingGraph->nets() )
  {
     checkBox = new QCheckBox( net.name() );
     layout->addWidget( checkBox );
     netMapper->setMapping( checkBox , net.name() );
     connect( checkBox , SIGNAL( stateChanged( int ) ) , netMapper , SLOT( map() ) );
  }
  // end set nets
  // set blocks
  if( blockGroupBox->layout() ) delete blockGroupBox->layout();

  layout = new QVBoxLayout;
  blockGroupBox->setLayout( layout );

  for( Group &group : routingGraph->groups() )
  {
     for( Symmetry &symmetry : group.symmetrys() )
        for( const Block &block : symmetry.blocks() )
        {
           checkBox = new QCheckBox( block.name() );
           layout->addWidget( checkBox );
           blockMapper->setMapping( checkBox , block.name() );
           connect( checkBox    , SIGNAL( stateChanged( int ) ) ,
                    blockMapper , SLOT  ( map() ) );
        }

     for( const Block &block : group.blocks() )
     {
        checkBox = new QCheckBox( block.name() );
        layout->addWidget( checkBox );
        blockMapper->setMapping( checkBox , block.name() );
        connect( checkBox , SIGNAL( stateChanged( int ) ) , blockMapper , SLOT( map() ) );
     }
  }
  for( const Block &block : routingGraph->blocks() )
  {
     checkBox = new QCheckBox( block.name() );
     layout->addWidget( checkBox );
     blockMapper->setMapping( checkBox , block.name() );
     connect( checkBox , SIGNAL( stateChanged( int ) ) , blockMapper , SLOT( map() ) );
  }
  // end set blocks

  groupCombo->addItem( "ALL" );

  for( Group &group : routingGraph->groups() )
     groupCombo->addItem( group.name() );

  groupCombo->setCurrentIndex( 0 );

  netCombo->addItem( "None" );

  for( const Net &net : routingGraph->nets() )
     netCombo->addItem( net.name() );

  netCombo->setCurrentIndex( 0 );
}

void RoutingGraphInfo::changeMode( const QString &mode )
{
  if( mode == "Group Mode" )
  {
    groupModeGroupBox->show();
    netModeGroupBox->hide();
    groupCombo->setCurrentIndex( 0 );
  }
  else
  {
    netModeGroupBox->show();
    groupModeGroupBox->hide();
    netCombo->setCurrentIndex( 0 );
  }
}

void RoutingGraphInfo::updateSymmetryCombo( const QString &groupName )
{
  symmetryCombo->clear();

  if( groupName != "ALL" )
  {
    auto it = find_if( routingGraph->groups().begin() , routingGraph->groups().end() ,
                       [&]( const Group &group )
                       { return ( group.name() == groupName ); } );

    if( it == routingGraph->groups().end() ) return;

    symmetryCombo->addItem( "ALL" );

    for( const Symmetry &symmetry : it->symmetrys() )
       symmetryCombo->addItem( symmetry.name() );

    symmetryCombo->setCurrentIndex( 0 );
  }
}

void RoutingGraphInfo::updateBlockCombo( const QString &containerName )
{
  blockCombo->clear();
  blockCombo->addItem( "ALL" );

  if( containerName.isEmpty() ) return;

  if( containerName != "ALL" )
  {
    if( containerName[0] == 'G' )
    {
      Group &group = *find_if(  routingGraph->groups().begin() ,
                                routingGraph->groups().end() ,
                                [&]( const Group &group )
                                { return ( group.name() == containerName ); } );

      for( const Block &block : group.blocks() )
         blockCombo->addItem( block.name() );
    }
    else
    {
      for( Group &group : routingGraph->groups() )
      {
         auto it = find_if( group.symmetrys().begin() , group.symmetrys().end() ,
                            [&]( const Symmetry &symmetry )
                              { return ( symmetry.name() == containerName ); } );

         if( it == group.symmetrys().end() ) continue;

         for( const Block &block : (*it).blocks() )
            blockCombo->addItem( block.name() );
         break;
      }
    }
  }
  else
  {
    if( groupCombo->currentText() != "ALL" )
    {
      RoutingRegion *group = routingGraph->getRegion( groupCombo->currentText() );

      if( !group ) return;

      for( const Block &block : group->blocks() )
         blockCombo->addItem( block.name() );
    }
    else
    {
      for( const Block &block : routingGraph->blocks() )
         blockCombo->addItem( block.name() );
    }
  }

  blockCombo->setCurrentIndex( 0 );
}

void RoutingGraphInfo::updateNets( const QString &groupName )
{
  QVBoxLayout *layout = qobject_cast<QVBoxLayout*>( netGroupBox->layout() );

  for( int i = 0 ; i < layout->count() ; ++i )
     layout->itemAt( i )->widget()->hide();

  for( Net &net :routingGraph->nets() )
  {
     auto it = find_if( net.paths().begin() , net.paths().end() ,
                        [&]( const Path &path )
                        { return ( path.belongRegion()->name() == groupName ); } );

     if( it != net.paths().end() )
     {
       for( int i = 0 ; i < layout->count() ; ++i )
       {
          QCheckBox *checkBox = qobject_cast<QCheckBox*>( layout->itemAt( i )->widget() );

          if( checkBox->text() == net.name() )
          {
            checkBox->show();
            break;
          }
       }
     }
  }
}

void RoutingGraphInfo::updateBlocks( const QString &netName )
{
  QVBoxLayout *layout = qobject_cast<QVBoxLayout*>( blockGroupBox->layout() );

  for( int i = 0 ; i < layout->count() ; ++i )
     layout->itemAt( i )->widget()->hide();

  auto it = find_if(  routingGraph->nets().begin() , routingGraph->nets().end() ,
                      [&]( const Net &net ) { return ( net.name() == netName ); } );

  if( it == routingGraph->nets().end() )  return;

  Net &net = *it;

  for( const Pin &pin : net.pins() )
     for( int i = 0 ; i < layout->count() ; ++i )
     {
        QCheckBox *checkBox = qobject_cast<QCheckBox*>( layout->itemAt( i )->widget() );

        if( checkBox->text() == pin.connect()->name() )
        {
          checkBox->show();
          break;
        }
     }
}

void RoutingGraphInfo::setupWidgets()
{
  QVBoxLayout *layout = new QVBoxLayout;

  sourceFileLabel = new QLabel;
  modeSelector    = new QComboBox;

  modeSelector->addItem( "Group Mode" );
  modeSelector->addItem( "Net   Mode" );

  groupModeGroupBox = setupGroupModeWidgets ();
  netModeGroupBox   = setupNetModeWidgets   ();

  layout->addWidget( sourceFileLabel  );
  layout->addWidget( modeSelector     );
  layout->addSpacing( 1 );
  layout->addWidget( groupModeGroupBox );
  layout->addWidget( netModeGroupBox );
  layout->addStretch();

  setLayout( layout );

  connect(  modeSelector  , SIGNAL( currentIndexChanged( const QString& ) ) ,
            this          , SLOT  ( changeMode( const QString& ) ) );

  modeSelector->setCurrentIndex( 0 );
  netModeGroupBox->hide();
}

void RoutingGraphInfo::setupConnect()
{
  connect(  this , SIGNAL ( routingGraphChanged( Router* ) ) ,
            this , SLOT   ( updateInfo() ) );

  connect(  groupCombo    , SIGNAL( currentIndexChanged( const QString& ) ) ,
            this          , SLOT  ( updateSymmetryCombo( const QString& ) ) );
  connect(  groupCombo    , SIGNAL( currentIndexChanged( const QString& ) ) ,
            this          , SLOT  ( updateBlockCombo( const QString& ) ) );
  connect(  symmetryCombo , SIGNAL( currentIndexChanged( const QString& ) ) ,
            this          , SLOT  ( updateBlockCombo( const QString& ) ) );
  connect(  groupCombo    , SIGNAL( currentIndexChanged( const QString& ) ) ,
            this          , SLOT  ( updateNets( const QString& ) ) );
  connect(  netCombo      , SIGNAL( currentIndexChanged( const QString& ) ) ,
            this          , SLOT  ( updateBlocks( const QString& ) ) );

  connect(  groupCombo    , SIGNAL( currentIndexChanged( const QString& ) ) ,
            this          , SIGNAL( regionSelected( const QString& ) ) );
  connect(  groupCombo    , SIGNAL( currentIndexChanged( const QString& ) ) ,
            this          , SIGNAL( blockSelected( const QString& ) ) );
  connect(  symmetryCombo , SIGNAL( currentIndexChanged( const QString& ) ) ,
            this          , SIGNAL( blockSelected( const QString& ) ) );
  connect(  blockCombo    , SIGNAL( currentIndexChanged( const QString& ) ) ,
            this          , SIGNAL( blockSelected( const QString& ) ) );
  connect(  netCombo      , SIGNAL( currentIndexChanged( const QString& ) ) ,
            this          , SIGNAL( netSelected( const QString& ) ) );

  connect(  netMapper     , SIGNAL( mapped( const QString& ) ) ,
            this          , SIGNAL( netCheckToggled( const QString& ) ) );
  connect(  blockMapper   , SIGNAL( mapped( const QString& ) ) ,
            this          , SIGNAL( blockCheckToggled( const QString& ) ) );
}

QGroupBox* RoutingGraphInfo::setupGroupModeWidgets()
{
  QVBoxLayout *layout = new QVBoxLayout;
  QGroupBox   *group  = new QGroupBox;

  groupModeGroupBox = new QGroupBox;

  groupCombo    = new QComboBox;
  symmetryCombo = new QComboBox;
  blockCombo    = new QComboBox;
  netGroupBox   = new QGroupBox;

  layout->addWidget( groupCombo     );
  layout->addWidget( symmetryCombo  );
  layout->addWidget( blockCombo     );
  layout->addWidget( netGroupBox    );

  group->setLayout( layout );

  return group;
}

QGroupBox* RoutingGraphInfo::setupNetModeWidgets()
{
  QVBoxLayout *layout = new QVBoxLayout;
  QGroupBox   *group  = new QGroupBox;

  netCombo      = new QComboBox;
  blockGroupBox = new QGroupBox;

  layout->addWidget( netCombo       );
  layout->addWidget( blockGroupBox  );

  group->setLayout( layout );

  return group;
}
