#include "markdowntohtml.h"
#include "cmark.h"

using namespace std;

MarkdownToHtml::MarkdownToHtmlResult
MarkdownToHtml::translateCommonMarkToHtml(MarkdownType type, const char *data,
                                             const int length, string &outHtml)
{
    char *result = cmark_markdown_to_html(data, length, CMARK_OPT_DEFAULT);
    outHtml.append(result);
    free(result);
    return SUCCESS;
}
