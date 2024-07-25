#ifndef ACTIONHANDLER_H
#define ACTIONHANDLER_H

#include <QObject>
#include <QAction>
#include <QMap>
#include <QCursor>

class ActionHandler : public QObject {
    Q_OBJECT

public:
    explicit ActionHandler(QObject *parent = nullptr);

    // Configure les actions avec leurs icônes et les curseurs associés
    void configureActions(const QList<QAction*>& actions);

    QAction* getCurrentAction() const;

signals:
    void cursorChanged(const QCursor& cursor); // Signal émis lorsque le curseur doit être changé

public slots:
    void onActionTriggered();

private:
    void updateIcon(QAction *newAction);
    void updateCursor(QAction *newAction);

    QMap<QAction*, QString> initialIcons;
    QMap<QAction*, QString> activeIcons;
    QMap<QAction*, QCursor> cursors;      // Map des actions aux curseurs

    QAction *currentAction;
};

#endif // ACTIONHANDLER_H
