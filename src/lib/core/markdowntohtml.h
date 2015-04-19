#ifndef MARKDOWNTOHTML_H
#define MARKDOWNTOHTML_H

#include <cerrno>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>

#ifdef MARKDOWN_LIB
    #define DECLSPEC __declspec(dllexport)
#else
    #define DECLSPEC
#endif

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
                                             void (*renderFunc)(struct sd_callbacks *callbacks, struct html_renderopt *options, unsigned int render_flags));
};

#endif // MARKDOWNTOHTML_H
