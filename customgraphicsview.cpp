/**
 * @file customgraphicsview.cpp
 * @brief Fichier pour la classe CustomGraphicsView
 */

#include "customgraphicsview.h"
#include <QGraphicsLineItem>
#include <QMouseEvent>

/**
 * @brief Constructeur de base de CustomGraphicsView
 * @param parent : widget parent
 */
CustomGraphicsView::CustomGraphicsView(QWidget *parent)
    : QGraphicsView(parent), drawing(false)
{
    pen.setColor(Qt::black);
    pen.setWidth(5);
}

/**
 * @brief Constructeur de CustomGraphicsView permettant d'indiquer les paramètres du crayon
 * @param defaultPenColor : couleur par défaut du crayon
 * @param defaultPenWidth : taille par défaut du crayon
 * @param defaultPenStyleIndex : entier correspondant au style par défaut du crayon
 * @param parent : widget parent
 */
CustomGraphicsView::CustomGraphicsView(QColor defaultPenColor, int defaultPenWidth, int defaultPenStyleIndex, QWidget *parent)
    : QGraphicsView(parent), drawing(false)
{
    pen.setColor(defaultPenColor);
    pen.setWidth(defaultPenWidth);
    pen.setStyle(static_cast<Qt::PenStyle>(defaultPenStyleIndex + 1)); // in Qt::PenStyle 0 is no pen so we don't use it
    pen.setDashOffset(qreal(defaultPenWidth));
}

/**
 * @brief Permet de changer la couleur de l'objet crayon
 * @param color : nouvelle couleur du crayon
 */
void CustomGraphicsView::setPenColor(const QColor &color)
{
    pen.setColor(color);
}

/**
 * @brief Permet de changer la taille de l'objet crayon
 * @param width : nouvelle taille du crayon
 */
void CustomGraphicsView::setPenWidth(int width)
{
    pen.setWidth(width);
    pen.setDashOffset(qreal(width));
}

/**
 * @brief Permet de changer le style de l'objet crayon
 * @param styleIndex : entier correspondant à une valeur de l'enumération PenStyle qui contient les styles possibles
 */
void CustomGraphicsView::setPenStyle(int styleIndex)
{
    pen.setStyle(static_cast<Qt::PenStyle>(styleIndex + 1)); // in Qt::PenStyle 0 is no pen so we don't use it
}

/**
 * @brief Gestion du clic gauche de la souris (pression) pour le dessin
 * @param event : evenement de la souris
 */
void CustomGraphicsView::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        drawing = true;
        lastPoint = mapToScene(event->pos());
    }
}

/**
 * @brief Gestion du mouvement de la souris pour le dessin
 * @param event : evenement de la souris
 */
void CustomGraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    // if ((event->buttons() & Qt::LeftButton) && drawing) {
    //     QPointF currentPoint = mapToScene(event->pos());
    //     scene()->addLine(lastPoint.x(), lastPoint.y(), currentPoint.x(), currentPoint.y(), pen);
    //     lastPoint = currentPoint;
    // }
    if ((event->buttons() & Qt::LeftButton) && drawing) {
        QPointF currentPoint = mapToScene(event->pos());
        QGraphicsLineItem* line = new QGraphicsLineItem(lastPoint.x(), lastPoint.y(), currentPoint.x(), currentPoint.y());
        line->setPen(pen);

        scene()->addItem(line);
        itemStack.push(line);

        lastPoint = currentPoint;
    }
}

/**
 * @brief Gestion du clic gauche de la souris (relachement) pour le dessin
 * @param event : evenement de la souris
 */
void CustomGraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && drawing) {
        drawing = false;
    }
}

/**
 * @brief Gestion de l'action undo dans la menuBar
 * @param event : evenement d'action
 */
void CustomGraphicsView::undo()
{
    if (!itemStack.isEmpty()) {
        QGraphicsItem* item = itemStack.pop();
        redoStack.push(item);
        scene()->removeItem(item);
    }
}

/**
 * @brief Gestion de l'action undo dans la menuBar
 * @param event : evenement d'action
 */
void CustomGraphicsView::redo()
{
    if (!redoStack.isEmpty()) {
        QGraphicsItem* item = redoStack.pop();
        scene()->addItem(item);
        itemStack.push(item);
    }
}
