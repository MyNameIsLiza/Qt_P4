#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "homelibrary.h"
#include <QList>
#include <QMessageBox>
#include <QTableWidget>
#include <algorithm>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(720, 400);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
    QList<QString> headers;
    headers << "id" << "Назва" << "Автор" << "Дата публікації" << "Жанр";
    ui->tableWidget->fillHeaders(headers);
    ui->tableWidget_2->fillHeaders(headers);
}

MainWindow::~MainWindow()
{
    delete ui;
}
QList<HomeLibrary> list;
void MainWindow::on_pushButton_2_clicked()
{
    QString s = ui->lineEdit_5->text();
    int index = ui->comboBox->currentIndex();
    QList<HomeLibrary> search;
    ui->tableWidget_2->setRowCount(0);
    switch (index) {
    case 0: search = HomeLibrary::search_by_author(list, s);
        break;
    case 1: if(!(s.toInt()<2022 && s.toInt()>=1457)){
            QMessageBox msgbox;
            msgbox.setWindowTitle("Помилка");
            msgbox.setText("Некоректно введений рік\nПерша книга була видана у 1457 році!");
            msgbox.exec();
            ui->lineEdit_5->setText("");
            return;
        }
        search = HomeLibrary::search_by_publish_year(list, s);
        break;
    case 2: search = HomeLibrary::search_by_genre(list, s);
         break;
    }

    if(search.length()!=0) ui->tableWidget_2->fillByList(search);
    else{
        QMessageBox msgbox;
        msgbox.setWindowTitle("Помилка");
        msgbox.setText("Потрібних книг не знайдено");
        msgbox.exec();
    }
    //ui->tableWidget->setItem(0, 0,  new QTableWidgetItem(HomeLibrary::add_book.get_title()));
    //ui->tableWidget->setItem(0, 1,  new QTableWidgetItem(HomeLibrary::add_book.get_author()));
    //ui->tableWidget->setItem(0, 2,  new QTableWidgetItem(HomeLibrary::add_book.get_publish_year()));
    //ui->tableWidget->setItem(0, 3,  new QTableWidgetItem(HomeLibrary::add_book.get_genre()));
}

void QTableWidget::fillByList(QList<HomeLibrary> list){
    this->setRowCount(0);
    foreach(HomeLibrary book, list){
        this->setRowCount(this->rowCount()+1);
        this->setItem(this->rowCount()-1, 0, new QTableWidgetItem(QString::number(book.get_id())));
        this->setItem(this->rowCount()-1, 1, new QTableWidgetItem(book.get_title()));
        this->setItem(this->rowCount()-1, 2, new QTableWidgetItem(book.get_author()));
        this->setItem(this->rowCount()-1, 3, new QTableWidgetItem(book.get_publish_year()));
        this->setItem(this->rowCount()-1, 4, new QTableWidgetItem(book.get_genre()));
    }
}

void QTableWidget::fillHeaders(QList<QString> list){
    if(list.length()>=1){
    this->setColumnCount(list.length());
    for(int i = 0; i < list.length(); i++){
        this->setHorizontalHeaderItem(i, new QTableWidgetItem(list.at(i)));
    }
    }
}

void QTableWidget::fillByObject(HomeLibrary book){
    this->setRowCount(this->rowCount()+1);
    this->setItem(this->rowCount()-1, 0, new QTableWidgetItem(QString::number(book.get_id())));
    this->setItem(this->rowCount()-1, 1, new QTableWidgetItem(book.get_title()));
    this->setItem(this->rowCount()-1, 2, new QTableWidgetItem(book.get_author()));
    this->setItem(this->rowCount()-1, 3, new QTableWidgetItem(book.get_publish_year()));
    this->setItem(this->rowCount()-1, 4, new QTableWidgetItem(book.get_genre()));

}


void MainWindow::on_pushButton_clicked()
{
    HomeLibrary book;
    QString title = ui->lineEdit->text();
    QString author = ui->lineEdit_2->text();
    QString publish_year = ui->lineEdit_3->text();
    QString genre = ui->lineEdit_4->text();
    if(title!="" && author!="" && publish_year!="" && genre!=""){
        if(!(publish_year.toInt()<2022 && publish_year.toInt()>=1457)){
            QMessageBox msgbox;
            msgbox.setWindowTitle("Помилка");
            msgbox.setText("Некоректно введений рік\nПерша книга була видана у 1457 році!");
            msgbox.exec();
            ui->lineEdit_3->setText("");
            return;
        }
            book.set_id(list.length()+1);
            book.set_title(title);
            book.set_author(author);
            book.set_publish_year(publish_year);
            book.set_genre(genre);
            list.append(book);
            ui->lineEdit->setText("");
            ui->lineEdit_2->setText("");
            ui->lineEdit_3->setText("");
            ui->lineEdit_4->setText("");
            ui->tableWidget->fillByObject(book);
            QMessageBox msgbox;
            msgbox.setWindowTitle("Важливо");
            msgbox.setText("Нова книга була додана");
            msgbox.exec();
    }else{
        QMessageBox msgbox;
        msgbox.setWindowTitle("Помилка");
        msgbox.setText("Заповніть всі поля");
        msgbox.exec();
    }
}

void MainWindow::on_lineEdit_3_textChanged(const QString &arg1)
{
    foreach(QChar c, arg1)
        {
            if(!c.isNumber())
            {
                QMessageBox msgbox;
                msgbox.setWindowTitle("Помилка");
                msgbox.setText("Ви повинні ввести число");
                msgbox.exec();
                ui->lineEdit_3->setText("");
                return;
            }
    }
    if(!(arg1.toInt()<2022 && arg1.toInt()>=1457) && arg1.length()>=4){
        QMessageBox msgbox;
        msgbox.setWindowTitle("Помилка");
        msgbox.setText("Некоректно введений рік\nПерша книга була видана у 1457 році!");
        msgbox.exec();
        ui->lineEdit_3->setText("");
        return;
    }
}

void MainWindow::on_lineEdit_5_textChanged(const QString &arg1)
{
    if(ui->comboBox->currentIndex()==1){
    foreach(QChar c, arg1)
        {
            if(!c.isNumber())
            {
                QMessageBox msgbox;
                msgbox.setWindowTitle("Помилка");
                msgbox.setText("Ви повинні ввести число");
                msgbox.exec();
                ui->lineEdit_5->setText("");
                return;
            }
    }
    if(!(arg1.toInt()<2022 && arg1.toInt()>=1457) && arg1.length()>=4){
        QMessageBox msgbox;
        msgbox.setWindowTitle("Помилка");
        msgbox.setText("Некоректно введений рік\nПерша книга була видана у 1457 році!");
        msgbox.exec();
        ui->lineEdit_5->setText("");
        return;
    }
    }
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    ui->lineEdit_5->setText("");
}

void MainWindow::on_comboBox_2_currentIndexChanged(int index)
{
    switch (index) {
    case 0: std::sort(list.begin(), list.end(), HomeLibrary::compare_by_id);
        break;
    case 1: std::sort(list.begin(), list.end(), HomeLibrary::compare_by_author);
        break;
    case 2: std::sort(list.begin(), list.end(), HomeLibrary::compare_by_publish_year);
            break;
    case 3: std::sort(list.begin(), list.end(), HomeLibrary::compare_by_genre);
            break;
    }
    ui->tableWidget->fillByList(list);
  }

void MainWindow::on_lineEdit_6_textChanged(const QString &arg1)
{
    foreach(QChar c, arg1)
        {
            if(!c.isNumber())
            {
                QMessageBox msgbox;
                msgbox.setWindowTitle("Помилка");
                msgbox.setText("Ви повинні ввести число");
                msgbox.exec();
                ui->lineEdit_6->setText("");
                return;
            }
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    QString id = ui->lineEdit_6->text();
    for(int i = 0; i <list.length(); i++){
    if(ui->tableWidget->item(i, 0)->text() == id){
        ui->tableWidget->removeRow(i);
        list.remove(i);
        ui->lineEdit_6->setText("");
        return;
    }
    }
    QMessageBox msgbox;
    msgbox.setWindowTitle("Важливо");
    msgbox.setText("Книга з id = " + id + " відсутня у списку");
    msgbox.exec();
    ui->lineEdit_6->setText("");
}
