#ifndef ACTIONHANDLER_H
#define ACTIONHANDLER_H

#include <QObject>
#include <QAction>
#include <QMap>

class ActionHandler : public QObject {
    Q_OBJECT

public:
    explicit ActionHandler(QObject *parent = nullptr);

    // Configure les chemins des icônes pour les actions
    void configureActions(QList<QAction*> actions);

private slots:
    void onActionTriggered();

private:
    void updateIcon(QAction *newAction);
    QMap<QAction*, QString> initialIcons; // Stocke les icônes initiales
    QMap<QAction*, QString> activeIcons; // Stocke les icônes après clic
    QAction *currentAction; // Action actuellement sélectionnée
};

#endif // ACTIONHANDLER_H
