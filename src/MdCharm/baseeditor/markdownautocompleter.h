#ifndef MARKDOWNAUTOCOMPLETER_H
#define MARKDOWNAUTOCOMPLETER_H

#include <memory>
#include "baseautocompleter.h"

class QRegExp;
class Configuration;

class MarkdownAutoCompleter : public BaseAutoCompleter
{
public:
    MarkdownAutoCompleter(QObject *parent=0);
    ~MarkdownAutoCompleter();

    virtual int paragraphSeparatorAboutToBeInserted(QTextCursor &cursor);
private:
    int isOrderList(QString &text, int start);
    bool isUnorderList(QChar c1, QChar c2);
private:
    QRegExp *orderRe;
    std::shared_ptr<Configuration> conf;
};

#endif // MARKDOWNAUTOCOMPLETER_H
