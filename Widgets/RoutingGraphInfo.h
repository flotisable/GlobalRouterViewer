#ifndef ROUTINGGRAPHINFO_H
#define ROUTINGGRAPHINFO_H

#include <QWidget>
#include <QList>
#include <QCheckBox>

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
    void netCheckToggled    ( const QString &netName );
    void blockCheckToggled  ( const QString &blockName );

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
    QGroupBox*  setupGroupModeWidgets ();
    QGroupBox*  setupNetModeWidgets   ();

    Router *routingGraph;

    QLabel    *sourceFileLabel;
    QComboBox *modeSelector;

    QGroupBox *groupModeGroupBox;
    QGroupBox *netModeGroupBox;

    QComboBox *groupCombo;
    QComboBox *symmetryCombo;
    QComboBox *blockCombo;
    QGroupBox *netGroupBox;

    QComboBox *netCombo;
    QGroupBox *blockGroupBox;
};

#endif // ROUTINGGRAPHINFO_H
