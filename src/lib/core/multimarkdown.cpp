#include "markdowntohtml.h"
#include "libMultiMarkdown.h"

using namespace std;

MarkdownToHtml::MarkdownToHtmlResult
MarkdownToHtml::translateMultiMarkdownToHtml(MarkdownType type, const char *data,
                                             const int length, string &outHtml)
{
    char *result = markdown_to_string(data, 0, HTML_FORMAT);
    outHtml.append(result);
    free(result);
    return SUCCESS;
}
