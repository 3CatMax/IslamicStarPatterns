#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "SystemParams.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->treeWidget, SIGNAL(itemClicked(QTreeWidgetItem*, int )),    this, SLOT(ItemClicked(QTreeWidgetItem*, int)));
    connect(ui->angleSpinBox, SIGNAL(valueChanged(int)),    this, SLOT(ParamsChanged()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ParamsChanged()
{
    float degAngle = ui->angleSpinBox->value();
    float radAngle = degAngle * M_PI / 180.0;
    //std::cout << degAngle << " " << radAngle << "\n";

    SystemParams::rad_angle = radAngle;

    std::string tilingName;
    if(ui->treeWidget->selectedItems().size() > 0)
    {
        QTreeWidgetItem* item = ui->treeWidget->selectedItems()[0];
        tilingName = item->text(0).toStdString();
    }
    else
    {
        tilingName = "3.4.12 RD";
    }

    ui->widget->GetGLWidget()->GeneratePattern(tilingName);
    ui->widget->GetGLWidget()->repaint();
}

void MainWindow::ItemClicked(QTreeWidgetItem* item, int column)
{
    if(item)
    {
        std::string tilingName = item->text(column).toStdString();

        if(item->childCount() == 0)
        {
            ui->widget->GetGLWidget()->GeneratePattern(tilingName);
            ui->widget->GetGLWidget()->repaint();
            //std::cout << item->text(column).toStdString() << "\n";
        }
    }
}
