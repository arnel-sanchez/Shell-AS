// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //

// // // // // // // //
//  BUFFER LIBRARY:  //
// // // // // // // //

#include "buffer.h"

char *read_line()
{
    int i = 0, line_size = SIZE;
    bool simple_quotes = false, double_quotes = false;
    char c, *line = (char *)calloc(line_size, sizeof(char));
    while(scanf("%c", &c))
    {
        if (c == '\'' && !double_quotes)
            simple_quotes = !simple_quotes;
        if (c == '"' && !simple_quotes)
            double_quotes = !double_quotes;
        else if (c == '\n')
        {
            if (!simple_quotes && !double_quotes && (i < 1 || line[i - 1] != '\\'))
                break;
            printf("> ");
        }
        line[i++] = c;
        if (i == line_size)
        {
            line_size += line_size;
            line = (char *)realloc(line, line_size * sizeof(char));
        }
    }
    line[i] = 0;
    return line;
}

// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //