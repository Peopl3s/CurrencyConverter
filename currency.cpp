#include <QtWidgets>
#include <QtCore>
#include <QtNetwork>
#include "currency.h"
CurrencyConverter::CurrencyConverter(QWidget *p):QWidget(p){

    manager=new QNetworkAccessManager;

    timer=new QTimer;
    timer->start(60000);

    connect(timer,SIGNAL(timeout()),this,SLOT(loadRate()));

    loadRate();

    connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(parse(QNetworkReply*)));

    input1=new QComboBox;
    input2=new QComboBox;

    input1->setObjectName("input1");
    input2->setObjectName("input2");


    line1=new QLineEdit;
    line2=new QLineEdit;

    line1->setObjectName("line1");
    line2->setObjectName("line2");

    connect(input1,SIGNAL(currentIndexChanged(int)),SLOT(Convert()));
    connect(input2,SIGNAL(currentIndexChanged(int)),SLOT(Convert()));

    connect(line1,SIGNAL(textEdited(QString)),SLOT(Convert()));
    connect(line2,SIGNAL(textEdited(QString)),SLOT(Convert()));

    rateCB=new QLabel;

    input1->addItem(QIcon("Russia.ico"),"RUB");
    input1->addItem(QIcon("united-states-flag_6409.png"),"USD");
    input1->addItem(QIcon("ev.png"),"EUR");

    input2->addItem(QIcon("Russia.ico"),"RUB");
    input2->addItem(QIcon("united-states-flag_6409.png"),"USD");
    input2->addItem(QIcon("ev.png"),"EUR");

    line1->setValidator(new QDoubleValidator);
    line2->setValidator(new QDoubleValidator);

    QFormLayout *f=new QFormLayout;
    f->setHorizontalSpacing(0);
    f->setVerticalSpacing(10);
    f->addRow(input1,line1);
    f->addRow(input2,line2);
    f->addRow(rateCB);

    SqSS();

    setLayout(f);

}

void CurrencyConverter::loadRate() const
{
    manager->get(QNetworkRequest(QUrl("https://www.yandex.ru")));
}
void CurrencyConverter::parse(QNetworkReply *reply)
{
    QString s;

    if(reply->error()==QNetworkReply::NoError)
    {
        s=QString::fromUtf8(reply->readAll());

        QRegExp e("<span class=\"inline-stocks__value_inner\">(\\d+(,|.)?\\d*)</span>");

        int pos = 0;
        int c=0;

        QList<double> list;

        while ((pos = e.indexIn(s, pos)) != -1 && c<2)
        {
            list<<e.cap(1).replace(',','.').toDouble();

            pos += e.matchedLength();
            ++c;
        }
        dollar=list.at(0);
        euro=list.at(1);

        QDateTime *d = new QDateTime(QDateTime::currentDateTime());
        rateCB->setText("по курсу ЦБ РФ на "+d->toString("dd.MM.yyyy HH:mm"));

    } else (new QErrorMessage(this))->showMessage("ot access the host. The course is not updated.");
}
void CurrencyConverter::Convert() const
{
    if(sender()->objectName()=="input1" ||sender()->objectName()=="input2" ||sender()->objectName()=="line1")
    {
        QString txt=line1->text().replace(',','.');

        if(input1->currentIndex()==0 && input2->currentIndex()==1)
        {
            line2->setText(QString().setNum(txt.toDouble()/dollar));
        } else if (input1->currentIndex()==1 && input2->currentIndex()==0)
        {
            line2->setText(QString().setNum(txt.toDouble()*dollar));            /* рубли - доллароы*/

        } else if(input1->currentIndex()==0 && input2->currentIndex()==2)/* рубли - евро*/
        {
            line2->setText(QString().setNum(txt.toDouble()/euro));
        }else if(input1->currentIndex()==2 && input2->currentIndex()==0)
        {
            line2->setText(QString().setNum(txt.toDouble()*euro));

        } else if(input1->currentIndex()==1 && input2->currentIndex()==2)  /* доллары - евро*/
        {
            line2->setText(QString().setNum((txt.toDouble()*dollar)/euro));    /*  евро - доллары*/
        }
        else if(input1->currentIndex()==2 && input2->currentIndex()==1)
        {
            line2->setText(QString().setNum((txt.toDouble()*euro)/dollar));
        } else if (input1->currentIndex()==input2->currentIndex()) line2->setText(txt);

    } else if (sender()->objectName()=="line2")
    {

        QString txt=line2->text().replace(',','.');

        if(input2->currentIndex()==0 && input1->currentIndex()==1)
        {
            line1->setText(QString().setNum(txt.toDouble()/dollar));
        } else if (input2->currentIndex()==1 && input1->currentIndex()==0)
        {
            line1->setText(QString().setNum(txt.toDouble()*dollar));       /* рубли - доллароы*/
        }
        else if(input2->currentIndex()==0 && input1->currentIndex()==2)/* рубли - евро*/
        {
            line1->setText(QString().setNum(txt.toDouble()/euro));

        }else if(input2->currentIndex()==2 && input1->currentIndex()==0)
        {
            line1->setText(QString().setNum(txt.toDouble()*euro));
        }
        else if(input2->currentIndex()==1 && input1->currentIndex()==2)  /* доллары - евро*/
        {
            line1->setText(QString().setNum((txt.toDouble()*dollar)/euro));
        }
        else if(input2->currentIndex()==2 && input1->currentIndex()==1)   /*  евро - доллары*/
        {
            line1->setText(QString().setNum((txt.toDouble()*euro)/dollar));
        } else if (input1->currentIndex()==input2->currentIndex()) line1->setText(txt);
    }
}

void CurrencyConverter::SqSS()
{
    QFile file("style.qss");

    file.open(QFile::ReadOnly);

    QString strCSS = QLatin1String(file.readAll());

    this->setStyleSheet(strCSS);
}
