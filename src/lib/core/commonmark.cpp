#include "markdowntohtml.h"
#include "cmark.h"

MarkdownToHtml::MarkdownToHtmlResult
MarkdownToHtml::translateCommonMarkToHtml(MarkdownType type, const char *data,
                                             const int length, std::string &outHtml)
{
    char *result = cmark_markdown_to_html(data, length, CMARK_OPT_DEFAULT);
    outHtml.append(result);
    free(result);
    return SUCCESS;
}
