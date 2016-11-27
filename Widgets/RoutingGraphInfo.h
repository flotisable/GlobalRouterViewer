#ifndef ROUTINGGRAPHINFO_H
#define ROUTINGGRAPHINFO_H

#include <QWidget>
#include <QList>
#include <QCheckBox>
#include <QSignalMapper>

class QComboBox;
class QGroupBox;
class QLabel;
class Router;

class RoutingGraphInfo : public QWidget
{
  Q_OBJECT

  public:

    explicit RoutingGraphInfo( QWidget *parent = nullptr );
    RoutingGraphInfo( Router *routingGraph , QWidget *parent = nullptr );

  signals:

    void routingGraphChanged( Router *routingGraph );
    void regionSelected     ( const QString &regionName );
    void netCheckToggled    ( const QString &netName );
    void blockSelected      ( const QString &blockName );
    void blockCheckToggled  ( const QString &blockName );
    void netSelected        ( const QString &netName );

  public slots:

    void setRoutingGraph    ( Router *routingGraph );
    void setSourceFile      ( const QString &fileName );
    void updateInfo         ();
    void changeMode         ( const QString &mode );
    void updateSymmetryCombo( const QString &groupName      );
    void updateBlockCombo   ( const QString &containerName  );
    void updateNets         ( const QString &groupName      );
    void updateBlocks       ( const QString &netName        );

  private:

    void        setupWidgets          ();
    void        setupConnect          ();
    QGroupBox*  setupGroupModeWidgets ();
    QGroupBox*  setupNetModeWidgets   ();

    Router *routingGraph;

    QLabel    *sourceFileLabel;
    QComboBox *modeSelector;

    QGroupBox *groupModeGroupBox;
    QGroupBox *netModeGroupBox;

    QSignalMapper *netMapper;
    QComboBox     *groupCombo;
    QComboBox     *symmetryCombo;
    QComboBox     *blockCombo;
    QGroupBox     *netGroupBox;

    QSignalMapper *blockMapper;
    QComboBox     *netCombo;
    QGroupBox     *blockGroupBox;
};

#endif // ROUTINGGRAPHINFO_H
