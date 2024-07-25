#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QColorDialog>
#include <QPen>
#include <QIcon>
#include <QMessageBox>
#include <QClipboard>
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
    , actionHandler(new ActionHandler(this))
    , selectedColor(Qt::black)
    // , selectedColor_2(Qt::yellow)
{
    ui->setupUi(this);

    customView = new CustomGraphicsView(selectedColor,ui->penWidthSpinBox->value(), ui->penStyleComboBox->currentIndex(), this);
    scene = new QGraphicsScene(this);

    customView->setScene(scene);

    ui->mainLayout->replaceWidget(ui->graphicsView, customView);
    delete ui->graphicsView;
    ui->graphicsView = nullptr;

    graphics_Save_Load = new Graphics_Save_Load(customView);

    connect(ui->penColorButton, &QPushButton::clicked, this, &MainWindow::onColorButtonClicked);


    //les actions et les icônes
    setupActions();

    //maj curseur lié aux actions
    connect(actionHandler, &ActionHandler::cursorChanged, this, &MainWindow::updateCursor);


    // connect(ui->toolButton_2, &QPushButton::clicked, this, &MainWindow::onColorButton_2Clicked);

}

MainWindow::~MainWindow()
{
    delete ui;
    delete graphics_Save_Load;
}

// -----------------------------------------------------------------------------------------------------------------
// Pen Properties

void MainWindow::onColorButtonClicked()
{
    QColor color = QColorDialog::getColor(selectedColor, this, "Choose Color");

    if (color.isValid()) {
        selectedColor = color;
        ui->penColorButton->setStyleSheet(QString("background-color: %1").arg(color.name()));
        customView->setPenColor(color);
    }
}


void MainWindow::on_penWidthSpinBox_valueChanged(int arg1)
{
    customView->setPenWidth(arg1);
}

void MainWindow::on_penWidthSpinBox_textChanged(const QString &arg1)
{
    customView->setPenWidth(arg1.toInt());
}

void MainWindow::on_colorButton_1_clicked()
{
    customView->setPenColor(QColor(85, 0, 127));
}

void MainWindow::on_colorButton_2_clicked()
{
    customView->setPenColor(QColor(50, 14, 127));
}

void MainWindow::on_colorButton_3_clicked()
{
    customView->setPenColor(QColor(0, 0, 255));
}

void MainWindow::on_colorButton_4_clicked()
{
    customView->setPenColor(QColor(0, 255, 0));
}

void MainWindow::on_colorButton_5_clicked()
{
    customView->setPenColor(QColor(255, 255, 0));
}

void MainWindow::on_colorButton_6_clicked()
{
    customView->setPenColor(QColor(255, 85, 0));
}

void MainWindow::on_colorButton_7_clicked()
{
    customView->setPenColor(QColor(255, 0, 0));
}

void MainWindow::on_penStyleComboBox_currentIndexChanged(int index)
{
    customView->setPenStyle(index);
}

// -----------------------------------------------------------------------------------------------------------------
// File Properties - About

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

void MainWindow::on_actionAbout_this_app_triggered()
{
    QMessageBox::about(this, "Message", "Membre du projet : \n\nMUKHTAR Masooma\nRENOU Noemie\nKITIHOUN Bryan\nJIN Laurent");
}

void MainWindow::on_actionQuit_triggered()
{
    QApplication::quit();
}

// -----------------------------------------------------------------------------------------------------------------

void MainWindow::setupActions() {
    // Liste des actions
    QList<QAction*> actions = { ui->actionEraser, ui->actionCursor, ui->actionPen, ui->actionEllipse, ui->actionStar, ui->actionRectangle };
    actionHandler->configureActions(actions);
}

void MainWindow::onActionTriggered() {
    QAction *action = qobject_cast<QAction*>(sender());
    if (action) {
        // Met à jour l'icône et le curseur dans ActionHandler
        actionHandler->onActionTriggered();
    }
}

void MainWindow::updateCursor(const QCursor& cursor) {
    // Mettre à jour le curseur de la vue graphique
    ui->graphicsView->setCursor(cursor);
}

// -----------------------------------------------------------------------
// void MainWindow::onColorButton_2Clicked()
// {
//     QColor color = QColorDialog::getColor(selectedColor_2, this, "Choose Color");
