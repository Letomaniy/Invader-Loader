#include "logintab.h"
#include "selecttab.h"
#include "ui_logintab.h"
#include <QDesktopWidget>
#include <QMessageBox>
#include "core.h"
#include <QMessageAuthenticationCode>
#include <QClipboard>
#include <QKeyEvent>
#include <QMainWindow>

logintab::logintab(QWidget * parent):
  QDialog(parent),
  ui(new Ui::logintab) {
    config * conf;
    conf = new config();
    setWindowIcon(QIcon(":/img/icon.ico"));//:/img/icon.ico
    setWindowFlags(Qt::Dialog);
    setFixedSize(267, 474);//380, 300
    move(QApplication::desktop() -> screen() -> rect().center() - this -> rect().center());
    setWindowFlags(Qt::X11BypassWindowManagerHint | Qt::FramelessWindowHint);
    ui -> setupUi(this);

    if (!conf -> UsingKeySystem) {
      ui -> _keylabel -> hide();
      ui -> key -> hide();
      ui->_keylabel->setEnabled(false);
      ui->key->setEnabled(false);
      setFixedSize(267, 474);//380, 260
    }
    if(QFile(temp + "\\settings.ini").exists())//\\settings.ini
        {
            loadSettings();
        }
    if(conf->HideKeyField && conf -> UsingKeySystem && ui->key->text().count() >0)
    {
        ui -> _keylabel -> hide();
        ui -> key -> hide();
        ui->_keylabel->setEnabled(false);
        ui->key->setEnabled(false);
        setFixedSize(380, 260);
    }
    delete conf;


  }

logintab::~logintab() {
  delete ui;
}

void logintab::saveSettings()
{
    QSettings settings(temp + "\\settings.ini", QSettings::IniFormat );//\\settings.ini
    settings.beginGroup( "AllSettings" );//AllSettings
    settings.setValue("rememberme", ui->rememberme->isChecked());//rememberme
    settings.setValue("login", ui->login->text());//login
    settings.setValue("password", ui->password->text());//password
    settings.setValue("key", ui->key->text());//key
    settings.endGroup();
}

void logintab::loadSettings()
{
    QSettings settings(temp + "\\settings.ini", QSettings::IniFormat );//\\settings.ini
    settings.beginGroup( "AllSettings" );//AllSettings
    ui->rememberme->setChecked(settings.value("rememberme").toBool());//rememberme
    ui->login->setText(settings.value("login").toString());//login
    ui->password->setText(settings.value("password").toString());//password
    ui->key->setText(settings.value("key").toString());//key
    settings.endGroup();
}

void logintab::on_LogIn_clicked() {
    if(ui->rememberme->isChecked())
        {
            saveSettings();
        }else
        {
            if(QFile(temp + "\\settings.ini").exists())//\\settings.ini
            {
                 QFile(temp + "\\settings.ini").remove();//\\settings.ini
            }
        }
  config * conf;
  conf = new config();
  QString login = ui -> login -> text();
  QString password = ui -> password -> text();
  QString key;
  if (conf -> UsingKeySystem) {
    key = ui -> key -> text();
  } else {
    key = "NOACTIVEKEYSYSTEM";//NOACTIVEKEYSYSTEM
  }
  if (conf -> UsingKeySystem && ui -> key -> text().length() == 0) {
    core::ShowMessageBox(NULL, "Enter the key.", "Error", MB_OK | MB_ICONINFORMATION);//Enter the key.,Error
    return;

  } else if (ui -> login -> text().length() == 0) {
    core::ShowMessageBox(NULL, "Enter login.", "Error", MB_OK | MB_ICONINFORMATION);//Enter login.,Error
    return;
  } else if (ui -> password -> text().length() == 0) {
    core::ShowMessageBox(NULL, "Enter password.", "Error", MB_OK | MB_ICONINFORMATION);//Enter password.,Error
    return;
  }
  if ((conf -> UsingKeySystem && ui -> key -> text().count() <= 5)) {
    core::ShowMessageBox(NULL, "The key is invalid or less than 5 characters long.", "Error", MB_OK | MB_ICONINFORMATION);//The key is invalid or less than 5 characters long.,Error
    return;

  } else if (ui -> login -> text().count() <= 5) {
    core::ShowMessageBox(NULL, "Login length is less than 5 characters.", "Error", MB_OK | MB_ICONINFORMATION);//Login length is less than 5 characters.,Error
    return;
  } else if (ui -> password -> text().count() <= 5) {
    core::ShowMessageBox(NULL, "Password length is less than 5 characters.", "Error", MB_OK | MB_ICONINFORMATION);//Password length is less than 5 characters.,Error
    return;
  }
  Sosi:
  QString rands, check;
  QString HWID = core::stringEncrypt("(" + QSysInfo::machineHostName() + ")" + "(" + QSysInfo::productType() + " " + QSysInfo::kernelVersion() + ")" + "(" + QSysInfo::machineUniqueId() + ")", "6cdc8fd72d0e8d4648327492a95f2e18");
  QString result = (rands = core::GetRandomString()) + "|" + login + "|" + password + "|" + key + "|" + HWID;
  result = "c11ce8c670b55204d00e4a61ff9c79" + core::stringEncrypt(result, "c526fce0e4e706322424de071b0e0d"); //c526fce0e4e706322424de071b0e0d
  check = QString(QCryptographicHash::hash((rands.toLocal8Bit()), QCryptographicHash::Md5).toHex());
  QString resultRequest = base64_decode( core::Request(core::RequestMethod::GET, conf -> UrlToCheckLisencePHP, {
    result
  }).replace("izwhHrDONzDKDSNo5Iac8qUPbcniD1u4nSVvZn0fwaRu9", ""));
  if (resultRequest.length() != NULL) {
    if (resultRequest.contains(check)) {
      if (resultRequest.contains("UijeSR"))
      {
          core::ShowMessageBox(NULL, "Cheat not purchased or license has expired!", "Information!", MB_OK | MB_ICONINFORMATION);//Cheat not purchased or license has expired!,Information!
                          return;
      }
      if (resultRequest.contains("nBIM"))
      {
          core::ShowMessageBox(NULL, "PC ID incorrect!", "Information!", MB_OK | MB_ICONINFORMATION);//PC ID incorrect!,Information!
                          return;
      } else if (resultRequest.contains("siAa"))
      {
          core::ShowMessageBox(NULL, "Set user information!", "Information!", MB_OK | MB_ICONINFORMATION);//Set user information!,Information!
                       goto Sosi;
      }
      if (resultRequest.contains("Tvvh")) {
          core::ShowMessageBox(NULL, "Username incorrect!", "Information!", MB_OK | MB_ICONINFORMATION);//Username incorrect!,Information!

                          return;
      }
      if (resultRequest.contains("Eb9k")) {
          core::ShowMessageBox(NULL, "Password incorrect!", "Information!", MB_OK | MB_ICONINFORMATION);//Password incorrect!,Information!

                          return;
      }
        if(conf->UsingKeySystem && resultRequest.contains("gpXShU"))
        {
            core::ShowMessageBox(NULL, "Key entered incorrectly!", "Error!", MB_OK | MB_ICONERROR);//Key entered incorrectly!,Error!
            return;
        }
        if(resultRequest.contains("3DOm") && resultRequest.contains("6MDp") && resultRequest.contains("6MDM")&& resultRequest.contains("2zihdc") && (resultRequest.contains("AXqEK7") || !conf->UsingKeySystem))
        {
           selecttab* seltab;
           seltab = new selecttab();
           hide();
           seltab->show();
           delete this;
      }
  } else {
    core::ShowMessageBox(NULL, "Error in the request certificate!", "Error!", MB_OK | MB_ICONERROR);//Error in the request certificate!,Error!
    return;
  }
} else {
  core::ShowMessageBox(NULL, "Invalid username.\r\nUnknown error!", "Error!", MB_OK | MB_ICONERROR);//Invalid username.\r\nUnknown error!,Error!
  return;
}

// Spargalka
//AXqEK7-key correct
//gpXShU-key incorrect
//NOACTIVEKEYSYSTEM-key system off
//siAa - set hwid
//3DOm - correct username
//6MDp - correct hwid
//6MDM - correct password
//UijeSR- Days is gone
//2zihdc- Good game!
//Tvvh - incorrect username
//nBIM - incorrect hwid
//Eb9k - incorrect password

delete conf;
}

void logintab::on_minimize_clicked() {
  QWidget::showMinimized();
}

void logintab::on_exit_clicked() {
  QApplication::quit();
}


void logintab::mouseMoveEvent(QMouseEvent *event)
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

void logintab::mousePressEvent(QMouseEvent *event)
{
    QDialog::mousePressEvent(event);
    m_pressed=true;

    if (event->button() == Qt::LeftButton)
    {
        m_dragPosition = event->globalPos() - frameGeometry().topLeft();
        event->accept();

    }
}

void logintab::mouseReleaseEvent(QMouseEvent* event)
{
    QDialog::mouseReleaseEvent(event);
    m_pressed=false;
}
