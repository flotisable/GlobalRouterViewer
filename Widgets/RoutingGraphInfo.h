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

    QComboBox         *groupCombo;
    QComboBox         *symmetryCombo;
    QComboBox         *blockCombo;
    QGroupBox         *netGroupBox;

    QList<QSharedPointer<QCheckBox>>  nets;

    QComboBox *netCombo;
    QGroupBox *blockGroupBox;

    QList<QSharedPointer<QCheckBox>>  blocks;
};

#endif // ROUTINGGRAPHINFO_H
