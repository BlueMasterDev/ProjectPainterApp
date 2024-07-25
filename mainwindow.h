#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QColor>
#include <QAction>
#include <actionhandler.h>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class CustomGraphicsView : public QGraphicsView
{
    Q_OBJECT

public:
    explicit CustomGraphicsView(QWidget *parent = nullptr);

    void setPenColor(const QColor &color);
    void setPenWidth(int width);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    bool drawing;
    QPointF lastPoint;
    QColor penColor;
    int penWidth;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onColorButtonClicked();
    //void changeIcon();
    void onActionTriggered();
    void updateCursor(const QCursor& cursor); // Slot pour mettre à jour le curseur

    // void onColorButton_2Clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QColor selectedColor;
    ActionHandler *actionHandler;
    // QColor selectedColor_2;

    void setupActions();
};

#endif // MAINWINDOW_H
