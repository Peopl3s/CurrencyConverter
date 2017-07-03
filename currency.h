#pragma once
#include <QtWidgets>
#include <QtCore>
#include <QtNetwork>
class CurrencyConverter:public QWidget{
    Q_OBJECT
private:
    double dollar;
    double euro;
    QComboBox *input1,*input2;
    QLineEdit *line1,*line2;
    QLabel *rateCB;
    QTimer *timer;
    QNetworkAccessManager *manager;
public:
    explicit CurrencyConverter(QWidget *p=0);
    CurrencyConverter(const CurrencyConverter &c)=delete;
    CurrencyConverter& operator=(const CurrencyConverter &c)=delete;
    virtual ~CurrencyConverter(){}
public slots:
    virtual  void loadRate()const;
    virtual  void parse(QNetworkReply *reply);
    virtual void Convert() const;
    virtual void SqSS();

};
