#define _CRT_SECURE_NO_WARNINGS
#include "selecttab.h"
#include "ui_selecttab.h"
#include "core.h"
#include <QDesktopServices>
#include <QDesktopWidget>
#include <QKeyEvent>
#include <QProcess>
#include <QSettings>
#include <QThread>
#include <QUrl>
#include <QMessageBox>

selecttab::selecttab(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::selecttab)
{
    setWindowIcon(QIcon(":/img/icon.ico"));
    setWindowFlags(Qt::Dialog);
    setFixedSize(189, 300);
    move(QApplication::desktop() -> screen() -> rect().center() - this -> rect().center());
    setWindowFlags( Qt::FramelessWindowHint);
    ui->setupUi(this);
    ui->inject->setEnabled(false);
}

selecttab::~selecttab()
{
    delete ui;

}

void selecttab::on_vk_clicked()
{
    QDesktopServices::openUrl(QUrl("https://vk.com/anapxict"));
}

void selecttab::on_exit_clicked()
{
QApplication::quit();
}

void selecttab::on_minimize_clicked()
{
QWidget::showMinimized();
} 



#include <wchar.h>
#include <iostream>
#include <ctime>
#include <fileapi.h>
#include <chrono>
#include <thread>
#include <fstream>
#include <string>
void selecttab::on_inject_clicked()
{
     //Your Injection method
}

void selecttab::mouseMoveEvent(QMouseEvent *event)
{
    QDialog::mouseMoveEvent(event);

    if(m_pressed)
    {
        if (event->buttons() & Qt::LeftButton )
        {
            window()->move(event->globalPos() - m_dragPosition);
            event->accept();

        }
    }
}

void selecttab::mousePressEvent(QMouseEvent *event)
{
    QDialog::mousePressEvent(event);
    m_pressed=true;

    if (event->button() == Qt::LeftButton)
    {
        m_dragPosition = event->globalPos() - frameGeometry().topLeft();
        event->accept();

    }
}

void selecttab::mouseReleaseEvent(QMouseEvent* event)
{
    QDialog::mouseReleaseEvent(event);
    m_pressed=false;
}
