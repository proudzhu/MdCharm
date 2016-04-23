#ifndef SPELLCHECKSELECTORDIALOG_H
#define SPELLCHECKSELECTORDIALOG_H

#include <QDialog>
#include <memory>

namespace Ui {
class SpellCheckSelectorDialog;
}

class SpellCheckSelectorDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit SpellCheckSelectorDialog(QWidget *parent = 0, Qt::WindowFlags f = Qt::WindowTitleHint|Qt::WindowSystemMenuHint);
    ~SpellCheckSelectorDialog();
    QString getSpellCheckLanguageName();

public slots:
    void acceptSlot();
    
private:
    std::shared_ptr<Ui::SpellCheckSelectorDialog> ui;
    QString language;
};

#endif // SPELLCHECKSELECTORDIALOG_H
