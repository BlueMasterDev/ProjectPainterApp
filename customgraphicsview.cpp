/**
 * @file customgraphicsview.cpp
 * @brief Fichier pour la classe CustomGraphicsView
 */

#include "customgraphicsview.h"

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

/**
 * @brief Permet de définir le type de forme selectionner
 * @param shape : correspondant à une valeur de l'enumération shape qui contient les formes possibles ( rien , crayon, rectangle, ellipse)
 */
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
            break;
        case Ellipse:
            currentItem = scene()->addEllipse(lastPoint.x(), lastPoint.y(), 0, 0, pen);
            // currentItem = scene()->addEllipse(100 ,100 , 100, 100, pen);
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
    if ((event->buttons() & Qt::LeftButton) && drawing) {
        QPointF currentPoint = mapToScene(event->pos());

        switch (currentShape) {
        case Pen:
            scene()->addLine(lastPoint.x(), lastPoint.y(), currentPoint.x(), currentPoint.y(), pen);
            lastPoint = currentPoint;
            break;
        case Rectangle:
            if (QGraphicsRectItem *rect = qgraphicsitem_cast<QGraphicsRectItem*>(currentItem)) {
                rect->setRect(QRectF(lastPoint, currentPoint).normalized());
            }
            break;
        case Ellipse:
            if (QGraphicsEllipseItem *ellipse = qgraphicsitem_cast<QGraphicsEllipseItem*>(currentItem)) {
                qreal x = std::min(lastPoint.x(), currentPoint.x());
                qreal y = std::min(lastPoint.y(), currentPoint.y());
                qreal w = std::abs(lastPoint.x() - currentPoint.x());
                qreal h = std::abs(lastPoint.y() - currentPoint.y());
                ellipse->setRect(x, y, w, h);
            }
            break;
        default:
            break;
        }
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
