#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

      m=new QMenu;
      m->addAction("empty");

    setMinimumWidth(500);
    setMinimumHeight(200);
    setWindowTitle("CurrencyConverter");
    setWindowFlags(Qt::Window);
    setWindowIcon(QIcon("money.png"));
    currency=new CurrencyConverter;
    setStyleSheet("MainWindow { background-image: url(d.png); background-color:black;}");
    setCentralWidget(currency);
    resize(500,200);
}

MainWindow::~MainWindow()
{
    delete ui;
}
