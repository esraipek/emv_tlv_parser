
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "emvtaglist.h"
#include <QList>
#include <QRegularExpression>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{   //QMap duplicate değer almıyormuş oyzden list
    QList<QPair<QString, QString>> TVList;
    QString TLV = ui->lineEdit->text();
    EmvTagList tagList;
    QList<Tag> tags = tagList.getTags();//taglisttekilere ulaşmak için
    if(TLV.isEmpty()){
        ui->textEdit->setText("veri girin");
        qDebug()<<"boş girilmiş";
        return;

    }
    for(int i=0;  i<TLV.length(); i++){
        QChar ch=TLV[i];
        if (!((ch >= '0' && ch <= '9') || (ch >= 'A' && ch <= 'F') || (ch >= 'a' && ch <= 'f'))){
            ui->textEdit->setText("Hexadecimal karakter gir");
            qDebug() << "Hexadecimal karakter gir";
            return;
        }

    }
    if(TLV.length()<=5){
        ui->textEdit->setText("Yetersiz data");
        qDebug()<<"Yetersiz data";
        return;
    }

    if(TLV.length()%2==1){
        ui->textEdit->setText("Çift sayıda karakter girmeniz gerekli");
        qDebug()<<"Çift sayıda karakter girmeniz gerekli";
        return;
    }

    int i=0;
    while (TLV.length() >= 5) {
        i++;
        qDebug()<<"--while döngüsü--"<<i;
        QString tag_part;
        QString length_part;
        QString value_part;
        int length = 0;
        bool found = false;
        bool found2 = false;
        qDebug()<<"TLV eski:"<<TLV;//input:6F1A840E315041592E5359532E4444463031A5088801025F2D02656E
        //input:A50A5F2D02656E5F2D02656E
        tag_part=TLV.mid(0,4);//ilk 4 karakteri al.
        foreach (const Tag &t, tags) {//4karakteri kontrol et.
            if (t.getTag() == tag_part) {
                found = true;
                break;
            }
        }
        //4 karakter için found
        if (found) {
            qDebug()<<"tag_part:"<<tag_part;
            length_part = TLV.mid(4, 2);
            qDebug()<<"length_part:"<<length_part;
            length = length_part.toInt(nullptr, 16);
            value_part = TLV.mid(6, length * 2);
            qDebug()<<"value_part:"<<value_part;
            if (TLV.length() < 6 + length * 2) {
                ui->textEdit->setText( "Yeterli data yok4");
                qDebug() << "Yeterli data yok4";
                return;
            }
            TVList.append(qMakePair(tag_part, value_part));
            if(tag_part=="BF0C"){
                TLV=TLV.mid(6,TLV.length());
            }
            else{
                TLV = TLV.mid(6 + length * 2);
            }

            qDebug() << "TLV yeni4:" << TLV;
        }
        if (!found) {
            tag_part=TLV.mid(0,2);
            foreach (const Tag &t, tags) {
                if (t.getTag() == tag_part) {
                    found2 = true;
                    break;
                }
            }
        }
        //2 karakter için found
        if(found2){
            tag_part = TLV.left(2);
            qDebug()<<"tag_part:"<<tag_part;
            length_part = TLV.mid(2, 2);
            qDebug()<<"length_part:"<<length_part;
            length = length_part.toInt(nullptr, 16);
            value_part = TLV.mid(4, length * 2);
            qDebug()<<"value_part:"<<value_part;

            if (TLV.length() < 4 + length * 2) {
                ui->textEdit->setText( "Yeterli data yok2");
                qDebug() << "Yeterli data yok2";
                return;
            }

            TVList.append(qMakePair(tag_part, value_part));


            //  eğer tag bir template ise value yu silme. değilse sil.

            if(tag_part=="A5"||tag_part=="61"||tag_part=="6F"||tag_part=="70"||tag_part=="73"||tag_part=="77"||tag_part=="80"){

                TLV=TLV.mid(4,TLV.length());

            }
            else{
                TLV = TLV.mid(4 + length * 2);
            }

            qDebug()<<"TLV yeni2:"<<TLV;
        }

        if(!found2 && !found){
            ui->textEdit->setText("Tag bulunamadı");
            qDebug()<<"tag bulunamadı";
            break;
        }

    }

    QStringList output;
    for (const QPair<QString, QString> &pair : TVList) {
        QString tagName;
        foreach (const Tag &t, tags) {
            if (t.getTag() == pair.first) {
                tagName = t.getName();
                break;
            }
        }
        if (!tagName.isEmpty()) {
            output.append(QString("Tag: %1, Name: %2, Value: %3").arg(pair.first).arg(tagName).arg(pair.second));
        } else {
            output.append(QString("Tag: %1, Name: Unknown, Value: %2").arg(pair.first).arg(pair.second));
        }
    }

    QString result = output.join("\n");
    ui->textEdit->setText(result);
    qDebug() << "Parsed tags with names and values:\n" << result;

}

