#include "ActionHandler.h"
#include <QIcon>

ActionHandler::ActionHandler(QObject *parent)
    : QObject(parent), currentAction(nullptr) {}

void ActionHandler::configureActions(QList<QAction*> actions) {
    // Définir les chemins des icônes pour chaque action
    for (QAction *action : actions) {
        QString actionName = action->text(); // Utiliser le texte de l'action comme clé pour les chemins

        if (actionName == "Eraser") {
            initialIcons[action] = ":/images/images/eraser.png";
            activeIcons[action] = ":/images/images/eraser_active.png";
        } else if (actionName == "Cursor") {
            initialIcons[action] = ":/images/images/cursor.png";
            activeIcons[action] = ":/images/images/cursor_active.png";
        } else if (actionName == "Pen") {
            initialIcons[action] = ":/images/images/pen.png";
            activeIcons[action] = ":/images/images/pen_active.png";
        } else if (actionName == "Ellipse") {
            initialIcons[action] = ":/images/images/circle.png";
            activeIcons[action] = ":/images/images/circle_active.png";
        } else if (actionName == "Star") {
            initialIcons[action] = ":/images/images/star.png";
            activeIcons[action] = ":/images/images/star_active.png";
        } else if (actionName == "Rectangle") {
            initialIcons[action] = ":/images/images/rectangle1.png";
            activeIcons[action] = ":/images/images/rectangle1_active.png";
        }

        // Définir l'icône initiale
        action->setIcon(QIcon(initialIcons[action]));
        connect(action, &QAction::triggered, this, &ActionHandler::onActionTriggered);
    }
}

void ActionHandler::onActionTriggered() {
    QAction *action = qobject_cast<QAction*>(sender());
    if (action) {
        updateIcon(action);
    }
}

void ActionHandler::updateIcon(QAction *newAction) {
    // Revient à l'icône initiale pour l'action précédente
    if (currentAction && currentAction != newAction) {
        currentAction->setIcon(QIcon(initialIcons[currentAction]));
    }

    // Met à jour l'icône pour la nouvelle action
    if (activeIcons.contains(newAction)) {
        newAction->setIcon(QIcon(activeIcons[newAction]));
        currentAction = newAction;
    }
}
