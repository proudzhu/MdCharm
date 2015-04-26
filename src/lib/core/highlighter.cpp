#include <string>
#include <stdio.h>

#include "codesyntaxhighlighter.h"
#include "highlighter.h"
#include "hoedown/buffer.h"

using namespace std;

void highlighter(hoedown_buffer *ob, const char *name, int len, const char *code, int codeLen)
{
    CodeSyntaxHighlighter highlighter;
    const string& result = highlighter.highlight(name, len, code, codeLen);
    hoedown_buffer_put(ob, (const uint8_t*)result.c_str(), result.length());
}
