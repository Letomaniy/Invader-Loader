#ifndef INVL_H
#define INVL_H

#include "core.h"
#include <QMainWindow>
#include <QMessageBox>
#include <QDesktopWidget>
#include <QApplication>
#include <QTextStream>
#include <QSettings>
#include <QDir>
#include <QPoint>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QIODevice>
#include <QKeyEvent>
#include <QGraphicsOpacityEffect>
#include <Qt>
#include <QObject>
#include <QSharedMemory>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class InvL; }
QT_END_NAMESPACE

class InvL : public QMainWindow
{
    Q_OBJECT

public:
    InvL(QWidget *parent = nullptr);
    ~InvL();
public slots:
    void Update();

private:
    QTimer *tmr;
    Ui::InvL *ui;

};
#endif // INVL_H
