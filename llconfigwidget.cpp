#include "llconfigwidget.h"

LLConfigWidget::LLConfigWidget() {
    setupUi(this);

#ifndef ENABLE_ADVANCED_SETTINGS
    advancedOptionsButton->hide();
#endif
}

LLConfigWidget::~LLConfigWidget() {}

void LLConfigWidget::saveSettings() {}