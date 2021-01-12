#include <inc/sunshinedesktop.h>
#include <QApplication>
#include <cstdio>

int checkInternetConnection() {
    while(true) {
        std::FILE *p = popen("ping google.com -c 1", "r");

        if (!p) {
            qDebug() << "File not open correctly";
            return -1;
        }

        int status = pclose(p);
        if (status)
        {
            QMessageBox msgBox;
            msgBox.setWindowModality(Qt::NonModal);
            msgBox.setWindowTitle("No internet connection");
            msgBox.setText("Retry?");
            msgBox.setStandardButtons(QMessageBox::Yes);
            msgBox.addButton(QMessageBox::No);
            auto reppy = msgBox.exec();
            if(reppy != QMessageBox::Yes)
            {
              return 1;
            }

        }
        else
        {
            return 0;
        }
    }
}

int main(int argc, char *argv[])
{
    try {
        QApplication a(argc, argv);

        const int result = checkInternetConnection();
        if(result == -1)
        {
            return -1;
        }
        else if(result == 1)
        {
            return 0;
        }

        SunshineDesktop mainWindow;
        mainWindow.setWindowTitle("Weather Station");
        mainWindow.show();

        return a.exec();
    }
    catch (...)
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("No internet connection. Program ended.");
        msgBox.setStandardButtons(QMessageBox::Ok);
        return -1;
    }
}
