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
    Language* getLanguage(const std::string &name);
    static std::shared_ptr<LanguageManager> getInstance();
    LanguageManager();
private:
    std::map<std::string, Language *> languages;
    static std::shared_ptr<LanguageManager> instance;
};

class CodeSyntaxHighlighter
{
public:
    CodeSyntaxHighlighter();
    const std::string& highlight(const char *name, int len, const char *code, int codeLen);
    const std::string& highlight(Language* lan, const char *code, int len);
private:
    int processLexem(const std::string &subCode, const std::string *matchCode=nullptr);
    std::string processBuffer();
    std::string processKeywords();
    std::string processKeywords(Contain *contain);
    std::string processSubLanguage(Contain *top);

    void processMatch(Contain* contain, const std::string& match);
    Keywords::KeywordsType keywordMatch(const std::string &match, Contain *contain=nullptr);
    std::string escape(const char *src, int len);
    Contain* findEndContain(Contain *contain, const std::string& match);
private:
    std::string result;
    std::string modeBuffer;
    Language *lan;
    Contain* top;
    int relevance;
    std::stack<Contain *> parentStack;
};

#endif // CODESYNTAXHIGHLIGHTER_H
