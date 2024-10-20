#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H



//emv tag leri için bir class oluştur
//pushbutton a basıldığında burdaki tagleri kontrol etsin.
//ikili ve 4lü olarak kontrol ettiğini düşünelim
//ilk başta 4lü olarak kontrol etsin.
//bulursa yandaki iki karakteri length olarak kalanı da value olarak alsın.
//bulamazsa 2li arasın. bulursa yan ikiyi length kalanı value olarak alsın.
//bulamazsa yanlış veri girildi desin şimdilik.


//substring olarak ayıralım şimdilik sonradan farklı bir şey buluruz.
