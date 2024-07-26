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
    : QGraphicsView(parent), drawing(false), currentShape(None), currentItem(nullptr)
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
    : QGraphicsView(parent), drawing(false), currentShape(None), currentItem(nullptr)
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

void CustomGraphicsView::setDrawShape(DrawShape shape)
{
    currentShape = shape;
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

        switch (currentShape) {
        case Rectangle:
            currentItem = scene()->addRect(QRectF(lastPoint, lastPoint), pen);
            itemStack.push(currentItem);
            break;
        case Ellipse:
            currentItem = scene()->addEllipse(QRectF(lastPoint, lastPoint), pen);
            itemStack.push(currentItem);
            break;
        default:
            break;
        }
    }
}

/**
 * @brief Gestion du mouvement de la souris pour le dessin
 * @param event : evenement de la souris
 */
void CustomGraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    QPointF currentPoint = mapToScene(event->pos());
    QGraphicsLineItem* line = nullptr;
        switch (currentShape) {
        case Pen:
            currentPoint = mapToScene(event->pos());
            line = new QGraphicsLineItem(lastPoint.x(), lastPoint.y(), currentPoint.x(), currentPoint.y());
            line->setPen(pen);
            itemStack.push(line);
            scene()->addItem(line);
            lastPoint = currentPoint;
            break;
        case Rectangle:
            if (QGraphicsRectItem *rect = qgraphicsitem_cast<QGraphicsRectItem*>(currentItem)) {
                rect->setRect(QRectF(lastPoint, currentPoint).normalized());
            }
            break;
        case Ellipse:
            if (QGraphicsEllipseItem *ellipse = qgraphicsitem_cast<QGraphicsEllipseItem*>(currentItem)) {
                ellipse->setRect(QRectF(lastPoint, currentPoint).normalized());
            }
            break;
        default:
            break;
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
        currentItem = nullptr;
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
