#include "markdowntohtml.h"

MarkdownToHtml::MarkdownToHtml()
{
}
/***************************************************************************//**
@brief generate html from markdown.
@param inMarkdown markdown source string
@param outHtml html generated from markdown source
@returns NOTHING -> empty
@returns SUCCESS -> ok
@returns ERROR -> something wrong
*******************************************************************************/
MarkdownToHtml::MarkdownToHtmlResult
MarkdownToHtml::translateMarkdownToHtml(MarkdownToHtml::MarkdownType type,
                                        const std::string &inMarkdown,
                                        std::string &outHtml)
{
    return translateMarkdownToHtml(type, inMarkdown.c_str(), inMarkdown.length(), outHtml);
}

MarkdownToHtml::MarkdownToHtmlResult
MarkdownToHtml::translateMarkdownToHtml(MarkdownToHtml::MarkdownType type,
                                        const char *data,
                                        const int length, std::string &outHtml)
{
    if(type == MarkdownToHtml::CommonMark) {
        return translateCommonMarkToHtml(type, data, length, outHtml);
    } else {
        return ERROR;
    }
}
