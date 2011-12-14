#include "llconfigwidget.h"
#include "paths.h"
#include <QMessageBox>
#include <QProcess>
#include <QSettings>

LLConfigWidget::LLConfigWidget() {
    setupUi(this);

#ifndef ENABLE_ADVANCED_SETTINGS
    advancedOptionsButton->hide();
#endif
    
    QSettings s(getConfigDir()+"video.cfg", QSettings::IniFormat);
    QString cur_mode = s.value("resolution").toString();

    QStringList modes;
    int cur_idx = 0;

#ifdef _WIN32
#else
    QProcess p;
    p.start("xrandr", QStringList() << "-q");
    if(!p.waitForStarted()) {
        QMessageBox::critical(this, tr("Critical Error"), tr("Could not read available resolutions. Make sure you have the xrandr program available."));
        QApplication::quit();
    }

    p.waitForFinished();

    QByteArray data = p.readAll();

    QString data_str(data);
    QStringList lines = data_str.split('\n');
    lines.removeFirst();
    lines.removeFirst();
    lines.removeLast();

    foreach(QString str, lines) {
        str.remove(0, 3);
        QString mode = str.split(' ')[0];
        if(mode == cur_mode)
            cur_idx = modes.length();
        modes.push_back(mode);
        
    }
#endif
    resolutionCombo->addItems(modes);
    resolutionCombo->setCurrentIndex(cur_idx);

    fullscreenCheck->setCheckState(s.value("fullscreen", true).toBool() ? Qt::Checked : Qt::Unchecked);
    vsyncCheck->setCheckState(s.value("vsync", true).toBool() ? Qt::Checked : Qt::Unchecked);
}

LLConfigWidget::~LLConfigWidget() {}

void LLConfigWidget::saveSettings() {
    QSettings s(getConfigDir()+"video.cfg", QSettings::IniFormat);
    s.setValue("resolution", resolutionCombo->currentText());
    s.setValue("fullscreen", fullscreenCheck->checkState() == Qt::Checked);
    s.setValue("vsync", vsyncCheck->checkState() == Qt::Checked);
}