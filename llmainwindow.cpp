#include "llmainwindow.h"
#include "llconfigwidget.h"
#include "paths.h"
#include <QDialogButtonBox>
#include <QMessageBox>
#include <QProcess>
#include <QVBoxLayout>

LLMainWindow::LLMainWindow() {
    QDialogButtonBox* box = new QDialogButtonBox;
    QPushButton* launchButton = box->addButton(QDialogButtonBox::Yes);
    launchButton->setText(tr("Launch")); // by creating as Yes button then changing the text, we get an icon automagically
    QPushButton* quitButton = box->addButton(QDialogButtonBox::Close);
    QPushButton* saveButton = box->addButton(QDialogButtonBox::Save);

    connect(quitButton, SIGNAL(clicked()), SLOT(close()));
    connect(launchButton, SIGNAL(clicked()), SLOT(launchGame()));

    config = new LLConfigWidget;
    connect(saveButton, SIGNAL(clicked()), config, SLOT(saveSettings()));

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(config);
    layout->addWidget(box);
    setLayout(layout);

    setWindowTitle(tr("%1 Launcher").arg(APPNAME));
}

LLMainWindow::~LLMainWindow() {}

void LLMainWindow::launchGame() {
    config->saveSettings();
    QProcess p;
    p.execute("game");
    if(p.waitForStarted()) {
        close();
    } else {
        QMessageBox::critical(this, tr("Critical Error"), tr("Could not execute the %1 program").arg(APPNAME));
    }
}
