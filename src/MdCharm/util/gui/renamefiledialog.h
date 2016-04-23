#ifndef RENAMEFILEDIALOG_H
#define RENAMEFILEDIALOG_H

#include <QDialog>
#include <memory>

namespace Ui {
class RenameFileDialog;
}

class RenameFileDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit RenameFileDialog(const QString &fileFullPath, QWidget *parent = 0);
    QString getNewFilePath();
    ~RenameFileDialog();

private slots:
    void acceptSlot();
    
private:
    std::shared_ptr<Ui::RenameFileDialog> ui;
    QString oldFilePath;
    QString newFP;
};

#endif // RENAMEFILEDIALOG_H
