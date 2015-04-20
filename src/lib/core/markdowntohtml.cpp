#include "markdowntohtml.h"
#include "markdown_lib.h"
#include "markdown.h"
#include "html.h"
#include "buffer.h"
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
    return renderToHtml(type, data, length, outHtml, sdhtml_renderer);
}

MarkdownToHtml::MarkdownToHtmlResult
MarkdownToHtml::renderToHtml(MarkdownToHtml::MarkdownType type, const char *data, const int length, string &outHtml,
                             void (*renderFunc)(struct sd_callbacks *callbacks, struct html_renderopt *options, unsigned int render_flags))
{
    if (length == 0) //length is 0, just return
        return NOTHING;

    buf *ib, *ob;
    sd_callbacks callbacks;
    html_renderopt options;
    sd_markdown *markdown;
    unsigned int extension=0;

    ib = bufnew(length);
    if (ib == NULL)
    {
        return ERROR;
    }
    bufgrow(ib, length);
    ib->size = length;
    memcpy(ib->data, data, length);

    ob = bufnew(OUTPUT_UNIT);
    if (ob == NULL)
    {
        bufrelease(ib);
        return ERROR;
    }

    renderFunc(&callbacks, &options, HTML_TOC);
    if(type == MarkdownToHtml::Markdown)
        extension = 0;
    else if(type == MarkdownToHtml::PHPMarkdownExtra)
        extension = MKDEXT_NO_INTRA_EMPHASIS
            |MKDEXT_TABLES
            |MKDEXT_FENCED_CODE
            |MKDEXT_AUTOLINK
            |MKDEXT_STRIKETHROUGH
            |MKDEXT_SUPERSCRIPT
            |MKDEXT_LAX_SPACING
            ;
    markdown = sd_markdown_new( extension, 16, &callbacks, &options);
    if (markdown == NULL)
    {
        bufrelease(ib);
        bufrelease(ob);
        return ERROR;
    }

    sd_markdown_render(ob, ib->data, ib->size, markdown);
    sd_markdown_free(markdown);

    outHtml.assign((const char*)ob->data, ob->size);

    bufrelease(ib);
    bufrelease(ob);
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
void sdhtml_toc_renderer_with_flag(struct sd_callbacks *callbacks, struct html_renderopt *options_ptr, unsigned int render_flags)
{
    sdhtml_toc_renderer(callbacks, options_ptr);
}

MarkdownToHtml::MarkdownToHtmlResult
MarkdownToHtml::renderMarkdownExtarToc(MarkdownType type, const char *data,
                                       const int length, string &toc)
{
    return renderToHtml(type, data, length, toc, sdhtml_toc_renderer_with_flag);
}
