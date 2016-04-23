#ifndef ABOUTMDCHARMDIALOG_H
#define ABOUTMDCHARMDIALOG_H

#include <QDialog>
#include <memory>

class QPlainTextEdit;
class QLabel;

namespace Ui {
    class AboutMdCharmDialog;
}

class AboutMdCharmDialog : public QDialog
{
    Q_OBJECT

public:
    AboutMdCharmDialog(QWidget *parent);
    ~AboutMdCharmDialog();
private:
    std::shared_ptr<Ui::AboutMdCharmDialog> ui;
    QPushButton *closePushButton;
    QLabel *versionLabel;
};

#endif // ABOUTMDCHARMDIALOG_H
