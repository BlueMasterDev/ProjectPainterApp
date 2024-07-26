/**
 * @file customgraphicsview.h
 * @brief Fichier pour la classe CustomGraphicsView
 */

#ifndef CUSTOMGRAPHICSVIEW_H
#define CUSTOMGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QStack>
#include <QMouseEvent>
#include <QGraphicsRectItem>
#include <QListWidget>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsPolygonItem>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QMouseEvent>



/**
 * @class CustomGraphicsView
 * @brief Classe pour la zone de dessin qui est dérivée de la classe QGraphicsView
 */
class CustomGraphicsView : public QGraphicsView
{
    Q_OBJECT

public:
    explicit CustomGraphicsView(QWidget *parent = nullptr);
    CustomGraphicsView(QColor defaultPenColor, int defaultPenWidth, int defaultPenStyleIndex, QWidget *parent = nullptr);

    void setPenColor(const QColor &color);
    void setPenWidth(int width);
    void setPenStyle(int styleIndex);
    //undo
    void undo();
    void redo();

    enum DrawShape { None, Pen, Rectangle, Ellipse };
    void setDrawShape(DrawShape shape);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragLeaveEvent(QDragLeaveEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dropEvent(QDropEvent *event) override;


signals:
    void itemDrop(QString);

private:
    bool drawing;
    QPointF lastPoint;
    QPen pen;

    //undo action
    QStack<QGraphicsItem*> itemStack;
    QStack<QGraphicsItem*> redoStack;
    DrawShape currentShape;
    QGraphicsItem *currentItem;

};

#endif // CUSTOMGRAPHICSVIEW_H
