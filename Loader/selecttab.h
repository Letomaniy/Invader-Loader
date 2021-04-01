#ifndef SELECTTAB_H
#define SELECTTAB_H

#include <QDialog>
#include <QDir>

namespace Ui {
class selecttab;
}

class selecttab : public QDialog
{
    Q_OBJECT
bool m_pressed=false;
public:
    explicit selecttab(QWidget *parent = nullptr);
    ~selecttab();
protected:

    void mouseReleaseEvent(QMouseEvent *event)override;
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
private slots:
    void on_vk_clicked();

    void on_exit_clicked();

    void on_minimize_clicked();

    void on_inject_clicked();

private:
    QString ssssss = QDir::homePath() + "\\AppData\\Roaming\\" ;
            QString appdata = ssssss.replace("/","\\");
            QString tmp = QDir::homePath() + "\\AppData\\Local\\Temp" ;
            QString temp = tmp.replace("/","\\");
    QPoint m_dragPosition;
    Ui::selecttab *ui;
};

#endif // SELECTTAB_H
