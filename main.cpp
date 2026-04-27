#include <QApplication>

#include "AdminGUI.h"
#include "FileRepository.h"
#include "GUI.h"
//#include "tests.h"
//#include "ui.h"

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    FileRepository repo(R"(C:\Users\Iulia\Desktop\teste_oop\incercare2\incercare2\text.txt)");
    Repository UserRepo;
    Service service(repo, UserRepo);

    //callAllTests();
    //    Console console{service};
    //    console.Start();

    GUI gui{ service, UserRepo };
    gui.show();

    return a.exec();
}
