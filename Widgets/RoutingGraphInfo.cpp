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
  this->routingGraph = routingGraph;

  setupWidgets();

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

  groupCombo->clear();
  symmetryCombo->clear();
  blockCombo->clear();
  netCombo->clear();

  // set nets
  layout = qobject_cast<QVBoxLayout*>( netGroupBox->layout() );

  for( const Net &net : routingGraph->nets() )
     layout->addWidget( new QCheckBox( net.name() ) );
  // end set nets
  // set blocks
  layout = qobject_cast<QVBoxLayout*>( blockGroupBox->layout() );

  for( Group &group : routingGraph->groups() )
  {
     for( Symmetry &symmetry : group.symmetrys() )
        for( const Block &block : symmetry.blocks() )
           layout->addWidget( new QCheckBox( block.name() ) );

     for( const Block &block : group.blocks() )
        layout->addWidget( new QCheckBox( block.name() ) );
  }
  for( const Block &block : routingGraph->blocks() )
     layout->addWidget( new QCheckBox( block.name() ) );
  // end set blocks

  groupCombo->addItem( "All" );

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

  if( groupName != "All" )
  {
    Group &group = *find_if(  routingGraph->groups().begin() ,
                              routingGraph->groups().end() ,
                              [&]( const Group &group )
                              { return ( group.name() == groupName ); } );

    symmetryCombo->addItem( "All" );

    for( const Symmetry &symmetry : group.symmetrys() )
       symmetryCombo->addItem( symmetry.name() );

    symmetryCombo->setCurrentIndex( 0 );
  }
}

void RoutingGraphInfo::updateBlockCombo( const QString &containerName )
{
  blockCombo->clear();
  blockCombo->addItem( "All" );

  if( containerName.isEmpty() ) return;

  if( containerName != "All" )
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
    if( groupCombo->currentText() != "All" )
    {
      Group &group =
        *find_if( routingGraph->groups().begin() , routingGraph->groups().end() ,
                  [&]( const Group &group )
                  { return ( group.name() == groupCombo->currentText() ); } );

      for( const Block &block : group.blocks() )
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

  if( groupName == "All" )
  {
    for( int i = 0 ; i < layout->count() ; ++i )
       layout->itemAt( i )->widget()->show();
  }
  else
  {
    Group &group = *find_if(  routingGraph->groups().begin() ,
                              routingGraph->groups().end() ,
                              [&]( const Group &group )
                              { return ( group.name() == groupName ); } );

    for( Net &net :routingGraph->nets() )
    {
       if( group.netConnected( net ) )
       {
         for( int i = 0 ; i < layout->count() ; ++i )
         {
            QCheckBox *checkBox =
              qobject_cast<QCheckBox*>( layout->itemAt( i )->widget() );

            if( checkBox->text() == net.name() )
            {
              checkBox->show();
              break;
            }
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

  modeSelector->setCurrentIndex( 1 );
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

  netGroupBox->setLayout( new QVBoxLayout );

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

  blockGroupBox->setLayout( new QVBoxLayout );

  layout->addWidget( netCombo       );
  layout->addWidget( blockGroupBox  );

  group->setLayout( layout );

  return group;
}
