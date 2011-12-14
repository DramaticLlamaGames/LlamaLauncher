#include <QDialog>

class LLConfigWidget;

class LLMainWindow : public QDialog {
    Q_OBJECT
public:
    LLMainWindow();
    ~LLMainWindow();

private slots:
    void launchGame();

private:
    LLConfigWidget* config;
};