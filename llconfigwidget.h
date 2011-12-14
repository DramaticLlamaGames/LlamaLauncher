#include <QWidget>
#include "ui_configwidget.h"

class LLConfigWidget : public QWidget, public Ui_ConfigWidget {
    Q_OBJECT
public:
    LLConfigWidget();
    ~LLConfigWidget();

public slots:
    void saveSettings();
};