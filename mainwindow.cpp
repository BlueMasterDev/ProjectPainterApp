/**
 * @file mainwindow.cpp
 * @brief Fichier pour la classe MainWindow
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QColorDialog>
#include <QPen>
#include <QIcon>
#include <QMessageBox>
#include <QClipboard>
#include <QFileDialog>
#include <QGraphicsLineItem>
#include <QGraphicsView>
#include <QGraphicsScene>


/**
 * @brief Constructeur de base de MainWindow
 * @param parent : widget parent
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , actionHandler(new ActionHandler(this))
    , selectedColor(Qt::black)
    , backgroundColor(Qt::white)
{
    ui->setupUi(this);

    customView = new CustomGraphicsView(selectedColor,ui->penWidthSpinBox->value(), ui->penStyleComboBox->currentIndex(), this);

    /**
     * Création de la scene et définition de sa taille à partir d'un rectangle
     */
    scene = new QGraphicsScene(this);
    const int sceneMaxSize = 1000;
    scene->setSceneRect(0, 0, sceneMaxSize, sceneMaxSize);

    /**
    * Ajout de la scene à la graphicsview et centrage par défaut sur le centre de la scene
    */
    customView->setScene(scene);
    customView->centerOn(QPointF(sceneMaxSize/2, sceneMaxSize/2));

    /**
    * Création de la grille
    */
    setDefaultScene();
    ui->mainLayout->replaceWidget(ui->graphicsView, customView);
    delete ui->graphicsView;
    ui->graphicsView = nullptr;

    graphics_Save_Load = new Graphics_Save_Load(customView);

    connect(ui->penColorButton, &QPushButton::clicked, this, &MainWindow::onColorButtonClicked);
    setupActions();
    connect(actionHandler, &ActionHandler::cursorChanged, this, &MainWindow::updateCursor);
    connect(ui->actionUndo, &QAction::triggered, customView, &CustomGraphicsView::undo);
    connect(ui->actionRedo, &QAction::triggered, customView, &CustomGraphicsView::redo);

    /**
    * Initialisation de la ListWidget avec tous les items
    */

    setListWidgetItems();
    customView->setAcceptDrops(true);
}

/**
 * @brief Destructeur de base de MainWindow
 */
MainWindow::~MainWindow()
{
    delete ui;
    delete graphics_Save_Load;
}

void MainWindow::setListWidgetItems()
{
    listWidget = ui->listWidgetShapeItems;
    /**
    * Mise en place des icônes pour les items
    */
    QPixmap pixLearn(":/images/images/quick.png");
    QPixmap pixEllipse(":/images/images/circle.png");
    QPixmap pixRect(":/images/images/rectangle.png");
    QPixmap pixStar(":/images/images/star.png");

    /**
    * Création des items pour la listwidget
    */
    QListWidgetItem *itemLearn = new QListWidgetItem;
    QListWidgetItem *itemEllipse = new QListWidgetItem;
    QListWidgetItem *itemRect = new QListWidgetItem;
    QListWidgetItem *itemStar = new QListWidgetItem;

    /**
    * Application des icônes pour tous les items
    */
    itemLearn->setIcon(pixLearn);
    itemEllipse->setIcon(pixEllipse);
    itemRect->setIcon(pixRect);
    itemStar->setIcon(pixStar);

    /**
    * Application du texte pour tous les items
    */
    itemLearn->setText("Learn");
    itemEllipse->setText("Ellipse");
    itemRect->setText("Rectangle");
    itemStar->setText("Star");

    /**
    * Ajout de tous les items dans la listwidget
    */
    listWidget->addItem(itemLearn);
    listWidget->addItem(itemEllipse);
    listWidget->addItem(itemRect);
    listWidget->addItem(itemStar);

    /**
    * Activation du drag and drop
    */
    listWidget->setDragEnabled(true);
}

// -----------------------------------------------------------------------------------------------------------------
// Pen Properties

/**
 * @brief Action qui se déclenche lorsque l'on clique sur la zone de couleur du crayon, permet à l'utilisateur de choisir une couleur.
 */
void MainWindow::onColorButtonClicked()
{
    QColor color = QColorDialog::getColor(selectedColor, this, "Choose Color");

    if (color.isValid()) {
        selectedColor = color;
        ui->penColorButton->setStyleSheet(QString("background-color: %1").arg(color.name()));
        customView->setPenColor(color);
    }
}

/**
 * @brief Action qui se déclenche lorsque l'on incrémente ou décrémente le champs contenant la largeur du crayon.
 */
void MainWindow::on_penWidthSpinBox_valueChanged(int arg1)
{
    customView->setPenWidth(arg1);
}

/**
 * @brief Action qui se déclenche lorsque l'on change numériquement au clavier le champs contenant la largeur du crayon.
 */
void MainWindow::on_penWidthSpinBox_textChanged(const QString &arg1)
{
    customView->setPenWidth(arg1.toInt());
}

/**
 * @brief Action qui se déclenche lorque l'on clique sur la première couleur par défaut (violet)
 */
void MainWindow::on_colorButton_1_clicked()
{
    customView->setPenColor(QColor(85, 0, 127));
    ui->penColorButton->setStyleSheet(QString("background-color: rgb(%1, %2, %3);").arg(85).arg(0).arg(127));
}

/**
 * @brief Action qui se déclenche lorque l'on clique sur la deuxième couleur par défaut (violet-bleu)
 */
void MainWindow::on_colorButton_2_clicked()
{
    customView->setPenColor(QColor(50, 14, 127));
    ui->penColorButton->setStyleSheet(QString("background-color: rgb(%1, %2, %3);").arg(50).arg(14).arg(127));
}

/**
 * @brief Action qui se déclenche lorque l'on clique sur la troisuème couleur par défaut (bleu)
 */
void MainWindow::on_colorButton_3_clicked()
{
    customView->setPenColor(QColor(0, 0, 255));
    ui->penColorButton->setStyleSheet(QString("background-color: rgb(%1, %2, %3);").arg(0).arg(0).arg(255));
}

/**
 * @brief Action qui se déclenche lorque l'on clique sur la quatrième couleur par défaut (vert)
 */
void MainWindow::on_colorButton_4_clicked()
{
    customView->setPenColor(QColor(0, 255, 0));
    ui->penColorButton->setStyleSheet(QString("background-color: rgb(%1, %2, %3);").arg(0).arg(255).arg(0));
}

/**
 * @brief Action qui se déclenche lorque l'on clique sur la cinquième couleur par défaut (jaune)
 */
void MainWindow::on_colorButton_5_clicked()
{
    customView->setPenColor(QColor(255, 255, 0));
    ui->penColorButton->setStyleSheet(QString("background-color: rgb(%1, %2, %3);").arg(255).arg(255).arg(0));
}

/**
 * @brief Action qui se déclenche lorque l'on clique sur la sixième couleur par défaut (orange)
 */
void MainWindow::on_colorButton_6_clicked()
{
    customView->setPenColor(QColor(255, 85, 0));
    ui->penColorButton->setStyleSheet(QString("background-color: rgb(%1, %2, %3);").arg(255).arg(85).arg(0));
}

/**
 * @brief Action qui se déclenche lorque l'on clique sur la septième couleur par défaut (rouge)
 */
void MainWindow::on_colorButton_7_clicked()
{
    customView->setPenColor(QColor(255, 0, 0));
    ui->penColorButton->setStyleSheet(QString("background-color: rgb(%1, %2, %3);").arg(255).arg(0).arg(0));
}

/**
 * @brief Action qui se déclenche lorque l'on change la combo box contenant le style du crayon [Solid, Dashed, Dotted, Dot Dashed]
 */
void MainWindow::on_penStyleComboBox_currentIndexChanged(int index)
{
    customView->setPenStyle(index);
}

// -----------------------------------------------------------------------------------------------------------------
// Canvas Properties

/**
 * @brief Action qui se déclenche lorque l'on coche ou décoche la case d'affichage de la grille
 */
void MainWindow::on_showGridCheckBox_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked)
    {
        lineGrid->show();
    }
    else // Qt::Unchecked
    {
        lineGrid->hide();
    }
}

/**
 * @brief Action qui se déclenche lorque l'on clique sur le bouton pour centrer la scene
 */
void MainWindow::on_centerSceneButton_clicked()
{
    customView->centerOn(scene->sceneRect().center());
}

/**
 * @brief Action qui se déclenche lorque l'on clique sur la zone de couleur du canvas, permet à l'utilisateur de choisir une couleur.
 */
void MainWindow::on_sceneBackgroundButton_clicked()
{
    QColor color = QColorDialog::getColor(backgroundColor, this, "Choose Color");

    if (color.isValid()) {
        backgroundColor = color;
        ui->sceneBackgroundButton->setStyleSheet(QString("background-color: %1").arg(color.name()));
        customView->setBackgroundBrush(QBrush(color));
    }
}

/**
 * @brief Action qui se déclenche lorque l'on clique sur le bouton pour réinitialiser le dessin, une popup permet de valider ou annuler l'action.
 */
void MainWindow::on_eraseDrawingButton_clicked()
{
    auto reply = QMessageBox::warning(this, "Warning", "Do you really want to erase the entire drawing?", QMessageBox::Yes, QMessageBox::Cancel);
    if (reply == QMessageBox::Yes)
    {
        scene->clear();
        setDefaultScene();
        if(!ui->showGridCheckBox->isChecked())
        {
            lineGrid->hide();
        }
    }
}

// -----------------------------------------------------------------------------------------------------------------
// File Properties - About

/**
 * @brief Action qui se déclenche lorque l'on clique sur le bouton sauvegarder
 */
void MainWindow::on_actionSave_triggered()
{
    QString filePath = QFileDialog::getSaveFileName(this, "Save File", "NomImage", "Images (*.png *.jpg)");
    if (!filePath.isEmpty()) {
        graphics_Save_Load->saveScene(filePath);
    }
}

/**
 * @brief Action qui se déclenche lorque l'on clique sur le bouton charger
 */
void MainWindow::on_actionLoad_triggered()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Load File", "", "Images (*.png *.jpg)");
    if (!filePath.isEmpty()) {
        graphics_Save_Load->loadScene(filePath);
    }
}

/**
 * @brief Action qui se déclenche lorque l'on clique sur le bouton d'ajout d'image
 */
void MainWindow::on_actionAdd_image_triggered()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Add File", "", "Images (*.png *.jpg)");
    if (!filePath.isEmpty()) {
        graphics_Save_Load->addImage(filePath);
    }
}

/**
 * @brief Action qui se déclenche lorque l'on clique sur le bouton à propos
 */
void MainWindow::on_actionAbout_this_app_triggered()
{
    QMessageBox::about(this, "Message", "Projet Dessin dans le cadre de la formation POEI module QT C++ \n\nMembre du projet : \n\nMUKHTAR Masooma\nRENOU Noemie\nKITIHOUN Bryan\nJIN Laurent");
}

/**
 * @brief Action qui se déclenche lorque l'on clique sur le bouton quitter
 */
void MainWindow::on_actionQuit_triggered()
{
    QApplication::quit();
}

// -----------------------------------------------------------------------------------------------------------------
// Actions on menuBar

/**
 * @brief Configure les actions de la menuBar
 */
void MainWindow::setupActions() {
    QList<QAction*> actions = { ui->actionEraser, ui->actionCursor, ui->actionPen, ui->actionEllipse, ui->actionStar, ui->actionRectangle};
    actionHandler->configureActions(actions);
    // Connecter les actions dans l'UI
    connect(ui->actionPen, &QAction::triggered, this, [this]() { customView->setDrawShape(CustomGraphicsView::Pen); });
    connect(ui->actionRectangle, &QAction::triggered, this, [this]() { customView->setDrawShape(CustomGraphicsView::Rectangle); });
    connect(ui->actionEllipse, &QAction::triggered, this, [this]() { customView->setDrawShape(CustomGraphicsView::Ellipse); });
}

/**
 * @brief Met à jour l'icône dans ActionHandler
 */
void MainWindow::onActionTriggered() {
    QAction *action = qobject_cast<QAction*>(sender());
    if (action) {
        actionHandler->onActionTriggered();
    }
}

/**
 * @brief Met à jour le curseur dans ActionHandler
 */
void MainWindow::updateCursor(const QCursor& cursor) {
    customView->setCursor(cursor);
}

/**
 * @brief Réglages de la scene : configuration de la grille et des axes.
 */
void MainWindow::setDefaultScene()
{
    const int sceneWidth = scene->sceneRect().width();
    const int sceneHeight = scene->sceneRect().height();

    QPen gridPen(QColor(235,235, 235));
    gridPen.setWidth(2);
    QList<QGraphicsItem *> gridList;

    for (int x = 0; x <= sceneWidth; x += 50)
    {
        QGraphicsLineItem* line = new QGraphicsLineItem(x, 0, x, sceneWidth);
        line->setPen(gridPen);
        gridList.push_back(line);
    }

    for (int y = 0; y <= sceneHeight; y += 50)
    {
        QGraphicsLineItem* line = new QGraphicsLineItem(0, y, sceneHeight, y);
        line->setPen(gridPen);
        gridList.push_back(line);
    }

    lineGrid = scene->createItemGroup(gridList);

    QPen axisPen(QColor(255, 0, 0));
    axisPen.setWidth(2);

    const int axisSize = 300;

    QGraphicsLineItem* xAxis = new QGraphicsLineItem(sceneWidth/2 - axisSize, sceneHeight/2, sceneWidth/2 + axisSize, sceneHeight/2);
    xAxis->setPen(axisPen);
    scene->addItem(xAxis);
    QGraphicsLineItem* yAxis = new QGraphicsLineItem(sceneWidth/2, sceneHeight/2 - axisSize, sceneWidth/2, sceneHeight/2 + axisSize);
    yAxis->setPen(axisPen);
    scene->addItem(yAxis);
}
