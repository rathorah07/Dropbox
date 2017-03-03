#include "dropbox2.h"
#include <QApplication>
#include <iostream>
#include "variables.h"
#include "ssl-client.h"
using namespace std;
dropbox2 * main_object;

int main(int argc, char *argv[])
{
    ServerConnect(argc,argv);
 
    QApplication a(argc, argv);
        dropbox2 w;
        main_object = &w;
        w.show();

        bool flag = a.exec();
        while(!flag)
        {
          flag = a.exec();
        }
}
