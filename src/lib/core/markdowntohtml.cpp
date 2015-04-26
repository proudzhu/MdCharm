#include "markdowntohtml.h"
#include "libMultiMarkdown.h"
#include "hoedown/document.h"
#include "hoedown/html.h"
#include "hoedown/buffer.h"
#include "cmark.h"

using namespace std;

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
                                        const string &inMarkdown,
                                        string &outHtml)
{
    return translateMarkdownToHtml(type, inMarkdown.c_str(), inMarkdown.length(), outHtml);
}

MarkdownToHtml::MarkdownToHtmlResult
MarkdownToHtml::translateMarkdownToHtml(MarkdownToHtml::MarkdownType type,
                                        const char *data,
                                        const int length, string &outHtml)
{
    if(type == MarkdownToHtml::Markdown || type == MarkdownToHtml::PHPMarkdownExtra){
        return translateMarkdownExtraToHtml(type, data, length, outHtml);
    } else if(type == MarkdownToHtml::MultiMarkdown) {
        return translateMultiMarkdownToHtml(type, data, length, outHtml);
    } else if(type == MarkdownToHtml::CommonMark) {
        return translateCommonMarkToHtml(type, data, length, outHtml);
    } else {
        return ERROR;
    }
}

MarkdownToHtml::MarkdownToHtmlResult
MarkdownToHtml::translateMarkdownExtraToHtml(MarkdownToHtml::MarkdownType type,
                                        const char *data,
                                        const int length, string &outHtml)
{
    return renderToHtml(type, data, length, outHtml, hoedown_html_renderer_new);
}

MarkdownToHtml::MarkdownToHtmlResult
MarkdownToHtml::renderToHtml(MarkdownToHtml::MarkdownType type, const char *data, const int length, string &outHtml,
                             hoedown_renderer* (*renderFunc)(hoedown_html_flags render_flags, int nesting_level))
{
    if (length == 0) //length is 0, just return
        return NOTHING;

    hoedown_buffer *ib, *ob;
    hoedown_renderer *callbacks;
    hoedown_html_renderer_state options;
    hoedown_document *markdown;
    unsigned int extensions = 0;
    hoedown_html_flags render_flags;

    ib = hoedown_buffer_new(length);
    if (ib == NULL)
    {
        return ERROR;
    }
    hoedown_buffer_grow(ib, length);
    ib->size = length;
    memcpy(ib->data, data, length);

    ob = hoedown_buffer_new(OUTPUT_UNIT);
    if (ob == NULL)
    {
        hoedown_buffer_free(ib);
        return ERROR;
    }

    callbacks = renderFunc(render_flags, 0);
    if(type == MarkdownToHtml::Markdown)
        extensions = 0;
    if(type == MarkdownToHtml::PHPMarkdownExtra)
        extensions = HOEDOWN_EXT_BLOCK
                | HOEDOWN_EXT_SPAN
                | HOEDOWN_EXT_FLAGS
                ;

    markdown = hoedown_document_new(callbacks, (hoedown_extensions)extensions, DEF_MAX_NESTING);
    if (markdown == NULL)
    {
        hoedown_buffer_free(ib);
        hoedown_buffer_free(ob);
        return ERROR;
    }

    hoedown_document_render(markdown, ob, ib->data, ib->size);
    hoedown_document_free(markdown);

    outHtml.assign((const char*)ob->data, ob->size);

    hoedown_buffer_free(ib);
    hoedown_buffer_free(ob);
    return SUCCESS; // success
}

MarkdownToHtml::MarkdownToHtmlResult
MarkdownToHtml::translateMultiMarkdownToHtml(MarkdownType type, const char *data,
                                             const int length, string &outHtml)
{
    char *result = markdown_to_string(data, 0, HTML_FORMAT);
    outHtml.append(result);
    free(result);
    return SUCCESS;
}

MarkdownToHtml::MarkdownToHtmlResult
MarkdownToHtml::translateCommonMarkToHtml(MarkdownType type, const char *data,
                                             const int length, string &outHtml)
{
    char *result = cmark_markdown_to_html(data, length, CMARK_OPT_DEFAULT);
    outHtml.append(result);
    free(result);
    return SUCCESS;
}

/**
 * @brief MarkdownToHtml::renderMarkdownExtarToc Get toc
 * @param type
 * @param data
 * @param length
 * @param toc
 * @return
 */
hoedown_renderer *hoedown_html_toc_renderer_new_with_flags(hoedown_html_flags render_flags, int nesting_level)
{
    return hoedown_html_toc_renderer_new(nesting_level);
}

MarkdownToHtml::MarkdownToHtmlResult
MarkdownToHtml::renderMarkdownExtarToc(MarkdownType type, const char *data,
                                       const int length, string &toc)
{
    return renderToHtml(type, data, length, toc, hoedown_html_toc_renderer_new_with_flags);
}
