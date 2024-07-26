#ifndef ACTIONHANDLER_H
#define ACTIONHANDLER_H

#include <QObject>
#include <QAction>
#include <QMap>
#include <QCursor>

/**
 * @class ActionHandler
 * @brief Classe pour gérer les actions de la menuBar
 */
class ActionHandler : public QObject {
    Q_OBJECT

public:
    explicit ActionHandler(QObject *parent = nullptr);

    void configureActions(const QList<QAction*>& actions);

    QAction* getCurrentAction() const;

signals:
    void cursorChanged(const QCursor& cursor);

public slots:
    void onActionTriggered();

private:
    void updateIcon(QAction *newAction);
    void updateCursor(QAction *newAction);

    QMap<QAction*, QString> initialIcons;
    QMap<QAction*, QString> activeIcons;
    QMap<QAction*, QCursor> cursors;
    QAction *currentAction;
};

#endif // ACTIONHANDLER_H
