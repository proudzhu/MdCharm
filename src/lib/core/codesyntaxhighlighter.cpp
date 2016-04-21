#include "codesyntaxhighlighter.h"
#include "languagedefinationxmlparser.h"

std::shared_ptr<LanguageManager> LanguageManager::instance = nullptr;

LanguageManager::LanguageManager()
{
}

LanguageManager::~LanguageManager()
{
    for (auto lang : languages)
        delete lang.second;
}

void LanguageManager::addLanguage(const std::string &name, char *content)
{
    LanguageDefinationXmlParser ldxp;
    Language *lan = ldxp.startParse(name.c_str(), content);
    lan->compileLanguage();
    languages[name] = lan;
//    lan->printDebugInfo();
}

Language* LanguageManager::getLanguage(const std::string &name)
{
    std::string realLan = name;
    if(name=="c")
        realLan = "cpp";
    else if(name=="html")
        realLan = "xml";
    else if(name=="js")
        realLan = "javascript";
    auto it = languages.find(realLan);
    if(it==languages.end())
        return nullptr;
    return (*it).second;
}

std::shared_ptr<LanguageManager> LanguageManager::getInstance()
{
    if (!instance)
        instance = std::make_shared<LanguageManager>();
    return instance;
}

CodeSyntaxHighlighter::CodeSyntaxHighlighter()
{
    relevance = 0;
    top = nullptr;
}

const std::string& CodeSyntaxHighlighter::highlight(const char *name, int len, const char *code, int codeLen)
{
    std::shared_ptr<LanguageManager> lanManger = LanguageManager::getInstance();
    Language *targetLanguage = lanManger->getLanguage(std::string(name, len));
    if(!targetLanguage){
        result = escape(code, codeLen);
        return result;
    }
    return highlight(targetLanguage, code, codeLen);
}

const std::string& CodeSyntaxHighlighter::highlight(Language *lan, const char *code, int len)
{
    result.clear();
    modeBuffer.clear();
    while(!parentStack.empty())
        parentStack.pop();
    top = nullptr;
    this->lan = lan;
    relevance = 0;
    int index = 0;
    while(true){
        FindResult fr;
        if(top){
            top->getTerminatorsRe().setLastIndex(index);
            fr = top->getTerminatorsRe().exec(code, len);
        } else {
            lan->getTerminatorsRe().setLastIndex(index);
            fr = lan->getTerminatorsRe().exec(code, len);
        }
        if(!fr.isValid())
            break;
        std::string match(code+fr.start, fr.end-fr.start);
        int count = processLexem(std::string(code+index, fr.start-index), &match);
        index = fr.start+count;
    }
    std::string left(code+index, len-index);
    processLexem(left);
    while(!parentStack.empty()){
        result.append("</span>");
        parentStack.pop();
    }
//    printf("%s\n", result.c_str());
    return result;
}

int CodeSyntaxHighlighter::processLexem(const std::string &subCode, const std::string *matchCode)
{
//    printf("subCode: %s\n", subCode.c_str());
//    printf("matchCode: %s\n", matchCode->c_str());
//    return 0;
    modeBuffer += subCode;
    if(matchCode==nullptr){
        result += processBuffer();
        return 0;
    }
    Contain* con = nullptr;
    if(top){
        con = top->findMatchedContain(*matchCode);
        if(!con && top->isRefLanguageContains())
            con = lan->findMatchedContain(*matchCode);
    } else {
        con = lan->findMatchedContain(*matchCode);
    }
    if(con){
        result += processBuffer();
        processMatch(con, *matchCode);
        return con->isReturnBegin() ? 0 : matchCode->length();
    }

    Contain *endContain = findEndContain(top, *matchCode);
    if(endContain){
        if(!(endContain->isReturnEnd()||endContain->isExcludeEnd())){
            modeBuffer += *matchCode;
        }
        result += processBuffer();
        while(top!=endContain->getParent() && top){
            if(top->isShowClassName())
                result += "</span>";
            if(!parentStack.empty()){
                top = parentStack.top();
                parentStack.pop();
            } else {
                top = nullptr;
            }
        }
//        if(parentStack.empty())
//            top = NULL;
        if(endContain->isExcludeEnd()){
            result += escape(matchCode->c_str(), matchCode->length());
        }
        modeBuffer.clear();
        if(endContain->getStarts())
            processMatch(endContain->getStarts(), "");
        return endContain->isReturnEnd() ? 0 : matchCode->length();
    }
    modeBuffer += *matchCode;
    return matchCode->length()>0 ? matchCode->length() : 1;
}

std::string CodeSyntaxHighlighter::processBuffer()
{
    //language no sub language
    if(top)
        return top->isHaveSubLanguage() ? processSubLanguage(top) : processKeywords(top);
    else
        return processKeywords();
}

std::string CodeSyntaxHighlighter::processKeywords()
{
    std::string buffer = escape(modeBuffer.c_str(), modeBuffer.length());
    if(lan->getKeywords().empty())
        return buffer;
    std::string keywordResult;
    int lastIndex = 0;
    lan->getLexemsRe().setLastIndex(0);
    FindResult fr = lan->getLexemsRe().exec(buffer.c_str(), buffer.length());
    while(fr.isValid()){
        keywordResult.append(buffer.substr(lastIndex, fr.start-lastIndex));
        std::string keyword = buffer.substr(fr.start, fr.end-fr.start);
        int km = keywordMatch(keyword);
        if(km!=Keywords::NotFound){
            keywordResult.append("<span class=\"")
                    .append(Keywords::getKeyTypeString(km))
                    .append("\">")
                    .append(keyword)
                    .append("</span>");
        } else {
            keywordResult.append(keyword);
        }
        lastIndex = lan->getLexemsRe().getLastIndex();
        fr = lan->getLexemsRe().exec(buffer.c_str(), buffer.length());
    }
    return keywordResult + buffer.substr(lastIndex);
}

std::string CodeSyntaxHighlighter::processKeywords(Contain *contain)
{
    std::string buffer = escape(modeBuffer.c_str(), modeBuffer.length());
    if(contain->getKeywords().empty()&&!contain->isRefLanguageKeywords())
        return buffer;
    std::string keywordResult;
    int lastIndex = 0;
    contain->getLexemsRe().setLastIndex(0);
    FindResult fr = contain->getLexemsRe().exec(buffer.c_str(), buffer.length());
    while(fr.isValid()){
        keywordResult.append(buffer.substr(lastIndex, fr.start-lastIndex));
        std::string keyword = buffer.substr(fr.start, fr.end-fr.start);
        int km = keywordMatch(keyword, contain);
        if(km!=Keywords::NotFound){
            keywordResult.append("<span class=\"")
                    .append(Keywords::getKeyTypeString(km))
                    .append("\">")
                    .append(keyword)
                    .append("</span>");
        } else {
            keywordResult.append(keyword);
        }
        lastIndex = contain->getLexemsRe().getLastIndex();
        fr = contain->getLexemsRe().exec(buffer.c_str(), buffer.length());
    }
    return keywordResult + buffer.substr(lastIndex);
}

std::string CodeSyntaxHighlighter::processSubLanguage(Contain *top)
{
    CodeSyntaxHighlighter *subHighlighter = new CodeSyntaxHighlighter;
    std::shared_ptr<LanguageManager> languageManager = LanguageManager::getInstance();
    Language* sub = languageManager->getLanguage(top->getSubLanguage());
    if(!sub)
        return escape(modeBuffer.c_str(), modeBuffer.length());
    std::string r = "<span class=\""+top->getSubLanguage()+"\">";
    r += subHighlighter->highlight(sub, modeBuffer.c_str(), modeBuffer.length());
    r += "</span>";
    delete subHighlighter;
    return r;
}

void CodeSyntaxHighlighter::processMatch(Contain *contain, const std::string &match)
{
    std::string markup;
    if(contain->isShowClassName())
        markup.append("<span class=\"").append(contain->getRealName()).append("\">");
    if(contain->isReturnBegin()){
        result += markup;
        modeBuffer.clear();
    } else if (contain->isExcludeBegin()){
        result += escape(match.c_str(), match.length()) + markup;
        modeBuffer.clear();
    } else {
        result += markup;
        modeBuffer = match;
    }
    //TODO: top = Object.create(mode, {parent: {value: top}});
//    parentStack.push(contain);
    if(top){
        contain->setParent(top);
        parentStack.push(top);
    }
    top = contain;
    relevance += contain->getRelevance();
}

int CodeSyntaxHighlighter::keywordMatch(const std::string &match, Contain *contain)
{
    std::string matchStr(match);
    if(!lan->isCaseSensitive()){//to lower case if not case sensitive
        std::transform(matchStr.begin(), matchStr.end(), matchStr.begin(), ::tolower);
    }
    return (contain&&!contain->isRefLanguageKeywords()) ? contain->matchKeyword(matchStr) : lan->matchKeyword(matchStr);
}

Contain* CodeSyntaxHighlighter::findEndContain(Contain *contain, const std::string &match)
{
    if(!contain)
        return nullptr;
    if(!contain->getEnd().empty() && contain->getEndRe().test(match.c_str(), match.length())){
        return contain;
    }
    if(contain->isEndWithParent()){
        return findEndContain(contain->getParent(), match);
    }
    return nullptr;
}

std::string CodeSyntaxHighlighter::escape(const char* src, int len)
{
    std::string result;
    if(len==0)
        return result;
    result.resize(len*2);
    result.resize(0);
    int index=0;
    for(int i=0; i<len; i++){
        if(src[i]=='&'){
            result.append(src+index, i-index);
            result.append("&amp;");
            index = i+1;
        } else if(src[i]=='<'){
            result.append(src+index, i-index);
            result.append("&lt;");
            index = i+1;
        } else if(src[i]=='>'){
            result.append(src+index, i-index);
            result.append("&gt;");
            index = i+1;
        }
    }
    if(len>index)
        result.append(src+index, len-index);
    return result;
}
