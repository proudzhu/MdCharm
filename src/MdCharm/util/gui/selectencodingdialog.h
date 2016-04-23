#ifndef SELECTENCODINGDIALOG_H
#define SELECTENCODINGDIALOG_H

#include <QDialog>
#include <memory>

class Configuration;

namespace Ui {
class SelectEncodingDialog;
}

class QComboBox;
class QDialogButtonBox;
class QCheckBox;

class SelectEncodingDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit SelectEncodingDialog(bool modified, QString currentEncoding, QWidget *parent = 0);
    ~SelectEncodingDialog();
    QString getSelectedEncoding();
    bool isReloadFile();

private slots:
    void reloadFileWarning();
    
private:
    std::shared_ptr<Ui::SelectEncodingDialog> ui;
    QComboBox *encodingComboBox;
    QDialogButtonBox *buttonBox;
    QCheckBox *reloadFileCheckBox;
    std::shared_ptr<Configuration> conf;
    bool modified;
};

#endif // SELECTENCODINGDIALOG_H
