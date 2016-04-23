#ifndef INSERTCODEDIALOG_H
#define INSERTCODEDIALOG_H

#include <QDialog>
#include <memory>

namespace Ui {
class InsertCodeDialog;
}

class InsertCodeDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit InsertCodeDialog(QWidget *parent = 0);
    QString getCodeType();
    ~InsertCodeDialog();
    
private:
    std::shared_ptr<Ui::InsertCodeDialog> ui;
};

#endif // INSERTCODEDIALOG_H
