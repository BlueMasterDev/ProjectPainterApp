#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QColorDialog>
#include <QMouseEvent>
#include <QPen>
#include <QMessageBox>
#include <QClipboard>
#include "graphics_save_load.h"
#include <QFileDialog>

CustomGraphicsView::CustomGraphicsView(QWidget *parent)
    : QGraphicsView(parent), drawing(false), penColor(Qt::black), penWidth(5)
{
}

void CustomGraphicsView::setPenColor(const QColor &color)
{
    penColor = color;
}

void CustomGraphicsView::setPenWidth(int width)
{
    penWidth = width;
}

void CustomGraphicsView::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        drawing = true;
        lastPoint = mapToScene(event->pos());
    }
}

void CustomGraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && drawing) {
        QPointF currentPoint = mapToScene(event->pos());
        QPen pen(penColor, penWidth);
        scene()->addLine(lastPoint.x(), lastPoint.y(), currentPoint.x(), currentPoint.y(), pen);
        lastPoint = currentPoint;
    }
}

void CustomGraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && drawing) {
        drawing = false;
    }
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , selectedColor(Qt::yellow)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    auto *customView = new CustomGraphicsView(this);
    customView->setScene(scene);
    ui->mainLayout->replaceWidget(ui->graphicsView, customView);
    delete ui->graphicsView;
    ui->graphicsView = customView;

    graphics_Save_Load = new Graphics_Save_Load(ui->graphicsView);

    connect(ui->penColorButton, &QPushButton::clicked, this, &MainWindow::onColorButtonClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete graphics_Save_Load;
}

void MainWindow::onColorButtonClicked()
{
    QColor color = QColorDialog::getColor(selectedColor, this, "Choose Color");

    if (color.isValid()) {
        selectedColor = color;
        ui->penColorButton->setStyleSheet(QString("background-color: %1").arg(color.name()));
        dynamic_cast<CustomGraphicsView*>(ui->graphicsView)->setPenColor(color);
    }
}

void MainWindow::on_actionQuit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionSave_triggered()
{
    QString filePath = QFileDialog::getSaveFileName(this, "Save File", "NomImage", "Images (*.png *.jpg)");
    if (!filePath.isEmpty()) {
        graphics_Save_Load->saveScene(filePath);
    }
}

void MainWindow::on_actionLoad_triggered()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Load File", "", "Images (*.png *.jpg)");
    if (!filePath.isEmpty()) {
        graphics_Save_Load->loadScene(filePath);
    }
}

void MainWindow::on_actionAdd_image_triggered()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Add File", "", "Images (*.png *.jpg)");
    if (!filePath.isEmpty()) {
        graphics_Save_Load->addImage(filePath);
    }
}
