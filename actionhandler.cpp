#include "ActionHandler.h"
#include <QIcon>
#include <QPixmap>

ActionHandler::ActionHandler(QObject *parent)
    : QObject(parent), currentAction(nullptr) {}

void ActionHandler::configureActions(const QList<QAction*>& actions) {
    for (QAction *action : actions) {
        QString actionName = action->text(); // Utiliser le texte de l'action comme clé pour les chemins

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

        //icône initiale
        action->setIcon(QIcon(initialIcons[action]));
        connect(action, &QAction::triggered, this, &ActionHandler::onActionTriggered);
    }
}

void ActionHandler::onActionTriggered() {
    QAction *action = qobject_cast<QAction*>(sender());
    if (action) {
        updateIcon(action);
        updateCursor(action);
    }
}

void ActionHandler::updateIcon(QAction *newAction) {
    // Revenir à l'icône initiale pour l'action précédente
    if (currentAction && currentAction != newAction) {
        currentAction->setIcon(QIcon(initialIcons[currentAction]));
    }

    // Mettre à jour l'icône pour la nouvelle action
    if (activeIcons.contains(newAction)) {
        newAction->setIcon(QIcon(activeIcons[newAction]));
        currentAction = newAction;
    }
}

void ActionHandler::updateCursor(QAction *newAction) {
    if (cursors.contains(newAction)) {
        //signal pour changer le curseur
        emit cursorChanged(cursors[newAction]);
    }
}

QAction* ActionHandler::getCurrentAction() const {
    return currentAction;
}
