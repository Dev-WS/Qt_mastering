#include "MainWindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
      mCpuWiget(this)
{
    ui->setupUi(this);
    //SysInfo::instance().init();
    //ui->centralwidget->layout()->addWidget(&mCpuWiget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

