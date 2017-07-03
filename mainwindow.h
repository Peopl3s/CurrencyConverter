#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "currency.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    virtual void contextMenuEvent(QContextMenuEvent* pe) override
    {
    m->exec(pe->globalPos());
    }
private:
    Ui::MainWindow *ui;
    CurrencyConverter *currency;
    QMenu *m;
};

#endif // MAINWINDOW_H
