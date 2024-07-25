#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QColor>
#include "graphics_save_load.h"

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
    void on_actionQuit_triggered();
    void on_actionSave_triggered();
    void on_actionLoad_triggered();
    void on_actionAdd_image_triggered();
    void on_actionAbout_this_app_triggered();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QColor selectedColor;
    Graphics_Save_Load *graphics_Save_Load;

};

#endif // MAINWINDOW_H
