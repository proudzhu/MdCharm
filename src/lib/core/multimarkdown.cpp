#include "markdowntohtml.h"
#include "libMultiMarkdown.h"

MarkdownToHtml::MarkdownToHtmlResult
MarkdownToHtml::translateMultiMarkdownToHtml(MarkdownType type, const char *data,
                                             const int length, std::string &outHtml)
{
    char *result = markdown_to_string(data, 0, HTML_FORMAT);
    outHtml.append(result);
    free(result);
    return SUCCESS;
}
