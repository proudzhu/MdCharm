#ifndef EXPORTDIRECTORYDIALOG_H
#define EXPORTDIRECTORYDIALOG_H

#include <QDialog>
#include <QWebEngineView>
#include <memory>

class QStandardItemModel;
class Configuration;

namespace Ui {
class ExportDirectoryDialog;
}

class ExportDirectoryDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit ExportDirectoryDialog(QWidget *parent = 0, const QString &dirPath=QString());
    ~ExportDirectoryDialog();
    void addFile(const QString &filePath);
private slots:
    void browerSourceDirSlot();
    void exportPathBrowerSlot();
    void fillData();
    void moveUp();
    void moveDown();
    void removeOne();
    void exportBtnSlot();
    void startExport();
    void exportOneByOne(const QString &content = QString());
    void exportOne(const QString &content);
    void loadFinish();
    void exportFinishSlot();
signals:
    void exportNext();
    void exportFinish();
private:
    void clearModel();
    QStringList getFiles() const;
private:
    std::shared_ptr<Ui::ExportDirectoryDialog> ui;
    std::shared_ptr<Configuration> m_conf;
    QStandardItemModel *m_model;
    QWebEngineView *webView;

    QStringList pendingFile;
    QString htmlTemplate;
    QString cssTemplate;

    QString pdfOutputFilPath;

    QTimer *timer;
};

#endif // EXPORTDIRECTORYDIALOG_H
