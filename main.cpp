#include <QApplication>
#include "llmainwindow.h"
#include "paths.h"

int main(int argc, char** argv) {
    QApplication app(argc, argv);
    app.setApplicationName(APPNAME);
    app.setOrganizationName(PUBLISHER);

    switchToAppDir();

    LLMainWindow window;
    window.show();

    return app.exec();
}