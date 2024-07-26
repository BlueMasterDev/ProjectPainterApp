#include "ActionHandler.h"
#include <QIcon>
#include <QPixmap>

ActionHandler::ActionHandler(QObject *parent)
    : QObject(parent), currentAction(nullptr) {}

/**
 * @brief Mise à jour des chemins des images à récupérer quand l'icone ou le curseur change
 */
void ActionHandler::configureActions(const QList<QAction*>& actions) {
    for (QAction *action : actions) {
        QString actionName = action->text();

        if (actionName == "Eraser") {
            initialIcons[action] = ":/images/images/eraser.png";
            activeIcons[action] = ":/images/images/eraser_active.png";
            cursors[action] = QCursor(QPixmap(":/images/images/eraser_cursor.png"));
        } else if (actionName == "Cursor") {
            initialIcons[action] = ":/images/images/cursor.png";
            activeIcons[action] = ":/images/images/cursor_active.png";
            cursors[action] = QCursor(QPixmap(":/images/images/cursor_cursor.png"));
        } else if (actionName == "Pen") {
            initialIcons[action] = ":/images/images/pen.png";
            activeIcons[action] = ":/images/images/pen_active.png";
            cursors[action] = QCursor(QPixmap(":/images/images/pen_cursor.png"));
        } else if (actionName == "Ellipse") {
            initialIcons[action] = ":/images/images/circle.png";
            activeIcons[action] = ":/images/images/circle_active.png";
            cursors[action] = QCursor(QPixmap(":/images/images/circle_cursor.png"));
        } else if (actionName == "Star") {
            initialIcons[action] = ":/images/images/star.png";
            activeIcons[action] = ":/images/images/star_active.png";
            cursors[action] = QCursor(QPixmap(":/images/images/star_cursor.png"));
        } else if (actionName == "Rectangle") {
            initialIcons[action] = ":/images/images/rectangle1.png";
            activeIcons[action] = ":/images/images/rectangle1_active.png";
            cursors[action] = QCursor(QPixmap(":/images/images/rectangle_cursor.png"));
        }
        action->setIcon(QIcon(initialIcons[action]));
        connect(action, &QAction::triggered, this, &ActionHandler::onActionTriggered);
    }
}

/**
 * @brief Mise à jour de l'icone et du curseur après un clic sur l'action
 */
void ActionHandler::onActionTriggered() {
    QAction *action = qobject_cast<QAction*>(sender());
    if (action) {
        updateIcon(action);
        updateCursor(action);
    }
}

/**
 * @brief Sélectionne la nouvelle action et déselectionne la précédente
 */
void ActionHandler::updateIcon(QAction *newAction) {
    if (currentAction && currentAction != newAction) {
        currentAction->setIcon(QIcon(initialIcons[currentAction]));
    }
    if (activeIcons.contains(newAction)) {
        newAction->setIcon(QIcon(activeIcons[newAction]));
        currentAction = newAction;
    }
}

/**
 * @brief Signal de changement de curseur
 */
void ActionHandler::updateCursor(QAction *newAction) {
    if (cursors.contains(newAction)) {
        emit cursorChanged(cursors[newAction]);
    }
}

/**
 * @brief Action actuelle
 */
QAction* ActionHandler::getCurrentAction() const {
    return currentAction;
}
