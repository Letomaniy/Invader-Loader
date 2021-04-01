#include "invl.h"
#include "core.h"
#include <QApplication>
#include <QLockFile>

int main(int argc, char *argv[])
{
    config *conf;
    conf = new config();

    QApplication a(argc, argv);


    if(conf->ProtectAgainStart)
    {

        QSharedMemory sharedMemory;
        sharedMemory.setKey("d8kr2bPaMxT3OEeA5hbYTmR5qnfTJoTwC7svdNYfLkI6VcFwO");
        Sleep(100);

        if (!sharedMemory.create(1))
        {
            delete conf;
            core::ShowMessageBox(NULL, "An instance of this application is running!","Error!", MB_OK | MB_ICONERROR);
            exit(0);
        }else
        {
            InvL w;
            w.show();
            return a.exec();
        }

    }else {
        InvL w;
        w.show();
        return a.exec();
}

}
