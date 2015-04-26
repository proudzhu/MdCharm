#ifndef MARKDOWNTOHTML_H
#define MARKDOWNTOHTML_H

#include <cerrno>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include "hoedown/document.h"
#include "hoedown/html.h"

#ifdef MARKDOWN_LIB
    #define DECLSPEC __declspec(dllexport)
#else
    #define DECLSPEC
#endif

#define DEF_MAX_NESTING 16

class DECLSPEC MarkdownToHtml
{
public:
    const static int OUTPUT_UNIT = 512;
    enum MarkdownToHtmlResult {
        ERROR = -1,
        NOTHING,
        SUCCESS
    };

    enum MarkdownType {
        Markdown,
        PHPMarkdownExtra,
        MultiMarkdown,
        CommonMark
    };

public:
    MarkdownToHtml();
    static MarkdownToHtmlResult translateMarkdownToHtml(MarkdownType type,
                                        const std::string &inMarkdown,
                                        std::string &outHtml);
    static MarkdownToHtmlResult translateMarkdownToHtml(MarkdownType type,
                                        const char* data,
                                        const int length, std::string &outHtml);
    static MarkdownToHtmlResult translateMarkdownExtraToHtml(MarkdownType type,
                                        const char* data,
                                        const int length, std::string &outHtml);
    static MarkdownToHtmlResult translateMultiMarkdownToHtml(MarkdownType type,
                                        const char* data,
                                        const int length, std::string &outHtml);
    static MarkdownToHtmlResult translateCommonMarkToHtml(MarkdownType type,
                                        const char* data,
                                        const int length, std::string &outHtml);
    static MarkdownToHtmlResult renderMarkdownExtarToc(MarkdownType type,
                                                       const char* data,
                                                       const int length, std::string &toc);

    static MarkdownToHtmlResult renderToHtml(MarkdownType type,
                                             const char *data,
                                             const int length,
                                             std::string &outHtml,
                                             hoedown_renderer* (*renderFunc)(hoedown_html_flags render_flags, int nesting_level));
};

#endif // MARKDOWNTOHTML_H
