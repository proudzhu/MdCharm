#ifndef CODESYNTAXHIGHLIGHTER_H
#define CODESYNTAXHIGHLIGHTER_H

#include <map>
#include <string>
#include <stack>
#include <memory>

#include "languagedefinationxmlparser.h"

#ifdef MARKDOWN_LIB
    #include "../../dllglobal.h"
#else
    #define AS_DYNAMIC_LIB
#endif

class Language;
class Contain;
class Keywords;
struct StackItem;

class AS_DYNAMIC_LIB LanguageManager
{
public:
    ~LanguageManager();
    void addLanguage(const std::string &name, char *content);
    std::shared_ptr<Language> getLanguage(const std::string &name);
    static std::shared_ptr<LanguageManager> getInstance();
    LanguageManager();
private:
    std::map<std::string, std::shared_ptr<Language>> languages;
    static std::shared_ptr<LanguageManager> instance;
};

class CodeSyntaxHighlighter
{
public:
    CodeSyntaxHighlighter();
    const std::string& highlight(const char *name, int len, const char *code, int codeLen);
    const std::string& highlight(std::shared_ptr<Language> lan, const char *code, int len);
private:
    int processLexem(const std::string &subCode, const std::string *matchCode=nullptr);
    std::string processBuffer();
    std::string processKeywords();
    std::string processKeywords(std::shared_ptr<Contain> contain);
    std::string processSubLanguage(std::shared_ptr<Contain> top);

    void processMatch(std::shared_ptr<Contain> contain, const std::string& match);
    Keywords::KeywordsType keywordMatch(const std::string &match, std::shared_ptr<Contain> contain=nullptr);
    std::string escape(const char *src, int len);
    std::shared_ptr<Contain> findEndContain(std::shared_ptr<Contain> contain, const std::string& match);
private:
    std::string result;
    std::string modeBuffer;
    std::shared_ptr<Language> lan;
    std::shared_ptr<Contain> top;
    int relevance;
    std::stack<std::shared_ptr<Contain>> parentStack;
};

#endif // CODESYNTAXHIGHLIGHTER_H
