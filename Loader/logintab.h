#ifndef LOGINTAB_H
#define LOGINTAB_H
#include <QApplication>
#include <QtCore>
#include <QDialog>


namespace Ui {
class logintab;
}

class logintab : public QDialog
{
    Q_OBJECT
    bool m_pressed=false;

public:

   
    QString base64_encode(QString string){
        QByteArray ba;
        ba.append(string);
        return ba.toBase64();
    }
    QString base64_decode(QString string){
        QByteArray ba;
        ba.append(string);
        return QByteArray::fromBase64(ba);
    }
    std::vector<char> GetVector(QString filemane);
    explicit logintab(QWidget *parent = nullptr);
    ~logintab();

private slots:
    void on_LogIn_clicked();

    void on_minimize_clicked();

    void on_exit_clicked();

protected:

    void mouseReleaseEvent(QMouseEvent *event)override;
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);

private:
    void loadSettings();
    void saveSettings();
    QPoint m_dragPosition;
    QString ssssss = QDir::homePath() + "\\AppData\\Roaming" ;
            QString appdata = ssssss.replace("/","\\");
            QString tmp = QDir::homePath() + "\\AppData\\Local\\Temp" ;
            QString temp = tmp.replace("/","\\");
    Ui::logintab *ui;
};

#endif // LOGINTAB_H
