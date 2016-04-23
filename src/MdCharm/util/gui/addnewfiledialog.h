#ifndef ADDNEWFILEDIALOG_H
#define ADDNEWFILEDIALOG_H

#include <QDialog>
#include <memory>

class QLabel;
class QLineEdit;
class QDialogButtonBox;

namespace Ui {
class AddNewFileDialog;
}

class AddNewFileDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit AddNewFileDialog(QWidget *parent = 0);
    void setParentDir(const QString &dirPath);
    QString getFileName();
    ~AddNewFileDialog();
    
private:
    std::shared_ptr<Ui::AddNewFileDialog> ui;
    QLabel *parentDirLabel;
    QLineEdit *fileNameLineEdit;
    QDialogButtonBox *buttonBox;
};

#endif // ADDNEWFILEDIALOG_H
