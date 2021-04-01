#include "core.h"
#include "invl.h"
#include "ui_invl.h"
#include "logintab.h"
#include <Windows.h>

InvL::InvL(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::InvL)
{

    setWindowIcon(QIcon(":/img/icon.ico"));//:/img/icon.ico
    setWindowFlags(Qt::Dialog);
    setFixedSize(281, 56);
    move(QApplication::desktop()->screen()->rect().center() - this->rect().center());
    setWindowFlags(Qt::X11BypassWindowManagerHint | Qt::FramelessWindowHint);
    ui->setupUi(this);
    tmr = new QTimer(this);
    tmr->setInterval(2);
    connect(tmr, SIGNAL(timeout()), this, SLOT(Update()));
    tmr->start();
}
void InvL::Update()
{
    config* conf;
    conf = new config();
    if (!conf->AutoUpdateDisable) {
        if (!conf->ShowUpdateWindow) {
            hide();
        }

        QNetworkAccessManager managerver;
        QNetworkReply* responsever = managerver.get(QNetworkRequest(QUrl(conf->UrlToVersionFile)));
        ui->label->setText("Проверка");
        QEventLoop eventver;
        connect(responsever, SIGNAL(finished()), &eventver, SLOT(quit()));
        eventver.exec();
        QString content = responsever->readAll().trimmed();
        if (content.length() == 0) {
            QApplication::quit();
            return;
        }
        else if (content != conf->version) {
            ui->label->setText("Скачивание");
            QNetworkAccessManager managerver;
            QNetworkReply* responsever = managerver.get(QNetworkRequest(QUrl(conf->UrlToUpdatedFile)));

            QEventLoop eventver;
            connect(responsever, SIGNAL(finished()), &eventver, SLOT(quit()));
            eventver.exec();

            QByteArray data = responsever->readAll();

            QFile file(QFileInfo(QApplication::applicationFilePath()).fileName().replace(".exe", "") + content.trimmed() + ".exe");
            if (file.open(QIODevice::ReadWrite)) {
                file.write(data);
                file.close();
            }

            ui->label->setText("Запускаем");
            QProcess vvv;
            vvv.startDetached(QFileInfo(QApplication::applicationFilePath()).fileName().replace(".exe", "") + content.trimmed() + ".exe");
            QApplication::quit();
        }
        else if (content == conf->version) {
            ui->label->setText("Готово");

        }
    }
    delete conf;
    logintab* login = new logintab();
    hide();
    login->show();
    tmr->stop();
}

InvL::~InvL()
{
    delete ui;
}
