/**
 * @file mainwindow.h
 * @brief Fichier pour la classe MainWindow
 */


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QColor>
#include <QAction>
#include <actionhandler.h>
#include "graphics_save_load.h"
#include "customgraphicsview.h"
#include <QListWidget>
#include <QGraphicsEllipseItem>
#include <QGraphicsRectItem>
#include <QGraphicsPolygonItem>
#include <QMimeData>
#include <QDrag>
#include <QDropEvent>
#include <QPolygonF>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/**
 * @class MainWindow
 * @brief Classe pour la fenêtre de l'application qui est dérivée de la classe QMainWindow
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setListWidgetItems();

private slots:
    // Pen Properties
    void onColorButtonClicked();

    // void onColorButton_2Clicked();
    void on_penWidthSpinBox_valueChanged(int arg1);
    void on_penWidthSpinBox_textChanged(const QString &arg1);
    void on_colorButton_1_clicked();
    void on_colorButton_2_clicked();
    void on_colorButton_3_clicked();
    void on_colorButton_4_clicked();
    void on_colorButton_5_clicked();
    void on_colorButton_6_clicked();
    void on_colorButton_7_clicked();
    void on_penStyleComboBox_currentIndexChanged(int index);

    // Files Properties
    void on_actionQuit_triggered();
    void on_actionSave_triggered();
    void on_actionLoad_triggered();
    void on_actionAdd_image_triggered();
    void on_actionAbout_this_app_triggered();

    //Cursor and actions update
    void onActionTriggered();
    void updateCursor(const QCursor& cursor); // Slot pour mettre à jour le curseur

private:
    Ui::MainWindow *ui;
    CustomGraphicsView *customView;
    QGraphicsScene *scene;
    QColor selectedColor;
    ActionHandler *actionHandler;
    // QColor selectedColor_2;
    void setupActions();

    Graphics_Save_Load *graphics_Save_Load;
    QListWidget *listWidget;

    QPointF mapToScene(QPoint);
};

#endif // MAINWINDOW_H
