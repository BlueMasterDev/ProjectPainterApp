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

// -----------------------------------------------------------------------------------------------------------------
// Drag and Drop properties

/**
 * @brief Drag Enter Event
 * @param QDragEnterEvent *event - évènement de QDragEnterEvent
*/
void CustomGraphicsView::dragEnterEvent(QDragEnterEvent *event)
{
/**
 * L'évènement du DragEnter est acceptée et doit être exécutée
*/
    event->accept();
    event->acceptProposedAction();
}

/**
 * @brief Drag Leave Event
 * @param QDragLeaveEvent *event - évènement de la classe QDragLeaveEvent
*/
void CustomGraphicsView::dragLeaveEvent(QDragLeaveEvent *event)
{
/**
 * L'évènement du DragLeave est acceptée et doit être exécutée
*/
    event->accept();
}

/**
 * @brief Drag Move Event
 * @param QDragMoveEvent *event - évènement de la classe QDragMoveEvent
*/
void CustomGraphicsView::dragMoveEvent(QDragMoveEvent *event)
{
/**
 * L'évènement du DragMove est acceptée et doit être exécutée
*/
    event->accept();
    event->acceptProposedAction();
}

/**
 * @brief Drop Event
 * @param QDropEvent *event - évènement de la classe QDropEvent
*/
void CustomGraphicsView::dropEvent(QDropEvent *event)
{
    if (event->source() == this) return;
/**
 * Utilisation de l'item drag et conversion de la position du curseur à la position de la scène
*/
    QListWidget *list = qobject_cast<QListWidget*>(event->source());
    QString text = list->currentItem()->text();
    QPointF position = mapToScene(event->position().toPoint());

/**
 * Ajout des différentes formes ou dessins selon le texte contenu dans l'item
*/
    if (text == "Learn")
    {
        QPixmap pixmap(":/images/images/quick.png");
        if (!pixmap.isNull()) {
            QGraphicsPixmapItem *item = new QGraphicsPixmapItem(pixmap);
            item->setPos(position);
            scene()->addItem(item);
            item->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable);
        }
    }
    else if (text == "Rectangle")
    {
        QGraphicsItem *item = nullptr;
        item = scene()->addRect(position.x(), position.y(), 100, 50, pen, QBrush(Qt::blue));
        item->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable);
        scene()->addItem(item);
    }
    else if (text == "Ellipse")
    {
        QGraphicsItem *item = nullptr;
        item = scene()->addEllipse(position.x(), position.y(), 100, 50, pen, QBrush(Qt::blue));
        item->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable);
        scene()->addItem(item);
    }
    else if (text == "Star")
    {
        QGraphicsItem *item = nullptr;
        QPolygonF star;
        star << QPointF(0, 40) << QPointF(20, 40) << QPointF(30, 0)
             << QPointF(40, 40) << QPointF(60, 40) << QPointF(45, 60)
             << QPointF(50, 100) << QPointF(30, 75) << QPointF(10, 100)
             << QPointF(15, 60) << QPointF(0, 40);
        item = scene()->addPolygon(star, pen, QBrush(Qt::yellow));
        item->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable);
        item->setPos(position);
        scene()->addItem(item);
    }

    event->acceptProposedAction();
}


