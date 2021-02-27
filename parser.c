// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //

// // // // // // // //
//  PARSER LIBRARY:  //
// // // // // // // //

#include "parser.h"

linked_tokens tokens(char *line)
{
    character current = none;
    bool comment = false, back_slash, change = false;
    int size = SIZE, i = 0;
    linked_tokens l_tokens = create_linked_tokens();
    token *tok = create_token(size);
    l_tokens.first = tok;
    for (int j = 0; j < strlen(line); j++)
    {
        back_slash = false;
        switch (line[j])
        {
            case '\'':
                if (current != double_quotes)
                {
                    current = current == simple_quotes ? normal : simple_quotes;
                    continue;
                }
                break;
            case '\"':
                if (current != simple_quotes)
                {
                    current = current == double_quotes ? normal : double_quotes;
                    continue;
                }
                break;
            default:
                if (current != simple_quotes && current != double_quotes)
                {
                    switch (line[j])
                    {
                        case ' ':
                            if (current == none)
                                continue;
                            current = none;
                            change = true;
                            break;
                        case '#':
                            if (i == 0)
                                comment = true;
                            break;
                        case '\\':
                            j++;
                            if (j >= strlen(line))
                                continue;
                            current = normal;
                            back_slash = true;
                            break;
                        case '&':
                            if (current == bg)
                                current = and;
                            else
                            {
                                change = current != none;
                                current = bg;
                            }
                            break;
                        case '|':
                            switch (current)
                            {
                                case pipe_char:
                                    current = or;
                                    break;
                                case stdout_char:
                                    current = forced_stdout;
                                    break;
                                default:
                                    change = current != none;
                                    current = pipe_char;
                                    break;
                            }
                            break;
                        case ';':
                            change = current != none;
                            current = semicolon;
                            break;
                        case '>':
                            switch (current)
                            {
                                case stdout_char:
                                    current = concatenated_stdout;
                                    break;
                                case stdin_char:
                                    current = stdin_stdout;
                                    break;
                                default:
                                    change = current != none;
                                    current = stdout_char;
                                    break;
                            }
                            break;
                        case '<':
                            switch (current)
                            {
                                case stdin_char:
                                    current = label_stdin;
                                    break;
                                case label_stdin:
                                    current = chain_stdin;
                                    break;
                                default:
                                    change = current != none;
                                    current = stdin_char;
                                    break;
                            }
                            break;
                        case '~':
                            if (i == 0 && (j + 1 >= strlen(line) || line[j + 1] == ' ' || line[j + 1] == '/'))
                            {
                                char *home = getenv("HOME");
                                for (int l = 0; l < strlen(home); l++)
                                {
                                    tok->value[i++] = home[l];
                                    if (i == size)
                                    {
                                        size += size;
                                        tok->value = (char *)realloc(tok->value, size * sizeof(char));
                                    }
                                }
                                current = normal;
                                continue;
                            }
                        default:
                            change = current != none && current != normal;
                            current = normal;
                            break;
                    }
                }
                if (change)
                {
                    tok->value[i] = 0;
                    tok->next = create_token(size);
                    tok->next->previous = tok;
                    tok = tok->next;
                    i = 0;
                    change = false;
                }
                break;
        }
        if (comment)
            break;
        if (current == simple_quotes || current == double_quotes || line[j] != ' ')
        {
            if (current == simple_quotes || current == double_quotes || back_slash)
                tok->type = commented_token;
            tok->value[i++] = line[j];
        }
        if (i == size)
        {
            size += size;
            tok->value = (char *)realloc(tok->value, size * sizeof(char));
        }
    }
    if (strlen(tok->value) < 1)
    {
        if (tok->previous != NULL)
        {
            tok = tok->previous;
            tok->next = NULL;
        }
        else
            l_tokens.first = NULL;
    }
    l_tokens.last = tok;
    return l_tokens;
}

linked_tokens alias(history *hist, linked_tokens l_tokens)
{
    bool tokenize_again = false;
    token *current = l_tokens.first;
    int i = 0, size = SIZE;
    char *line = (char *)calloc(size, sizeof(char));
    while (current != NULL)
    {
        if (strlen(current->value) > 0 && !strcmp(current->value, "again"))
        {
            token *temp = current->previous;
            char *h_line = again(hist, &current);
            for (int j = 0; j < strlen(h_line); j++)
            {
                line[i++] = h_line[j];
                if (i == size)
                {
                    size += size;
                    line = (char *)calloc(size, sizeof(char));
                }
            }
            line[i++] = ' ';
            linked_tokens new_tokens = tokens(h_line);
            /*if (current == NULL)
                return create_linked_tokens();*/
            if (temp != NULL)
            {
                new_tokens.first->previous = temp;
                temp->next = new_tokens.first;
            }
            else
                l_tokens.first = new_tokens.first;
            if (current != NULL && (temp == NULL || temp->next != current)
            && h_line[strlen(h_line) - 1] == new_tokens.last->value[strlen(new_tokens.last->value) - 1])
            {
                new_tokens.last->next = current;
                current->previous = new_tokens.last;
            }
            else
                l_tokens.last = new_tokens.last;
            tokenize_again = true;
        }
        else
        {
            if (current->type == commented_token)
                line[i++] = '"';
            for (int j = 0; j < strlen(current->value); j++)
            {
                line[i++] = current->value[j];
                if (i == size)
                {
                    size += size;
                    line = (char *)calloc(size, sizeof(char));
                }
            }
            if (current->type == commented_token)
                line[i++] = '"';
            current = current->next;
            if (current != NULL)
            {
                line[i++] = ' ';
                if (i == size)
                {
                    size += size;
                    line = (char *)calloc(size, sizeof(char));
                }
            }
        }
    }
    if (tokenize_again)
    {
        line[i] = 0;
        update_history(hist, line);
    }
    current = l_tokens.first;
    while (current != NULL)
    {
        if (strlen(current->value) > 0)
        {
            if (current->type != commented_token && current->value[0] == '#')
                current->previous->next = NULL;
            if (current->value[0] == '$')
                ;// sustituir la variable
        }
        current = current->next;
    }
    return l_tokens;
}

command *analyze_line(history  *hist, char *line, counters *count, int *bg)
{
    int size = SIZE, args_size = SIZE, redir_size = SIZE, i = 0, j = 0, k = 0;
    linked_tokens tokenizer = alias(hist, tokens(line));
    token *current = tokenizer.first;
    command *to_return = (command *)calloc(size, sizeof(command));
    to_return[0] = create_command();
    while (current != NULL)
    {
        if(current->type == standard_token && (!strcmp(current->value, "|") || !strcmp(current->value, "&") || !strcmp(current->value, "||")
        || !strcmp(current->value, "&&") || !strcmp(current->value, ";") || !strcmp(current->value, "if") || !strcmp(current->value, "then")
        || !strcmp(current->value, "else") || !strcmp(current->value, "end")))
        {
            if(to_return[i].args[0] != NULL || to_return[i].redir[0] != NULL)
            {
                i++;
                if (i == size)
                {
                    size += size;
                    to_return = (command*)calloc(size, sizeof(command));
                }
                to_return[i] = create_command();
            }
            if(!strcmp(current->value, "|"))
                count->pipes++;
            else if(!strcmp(current->value, "||"))
                count->concat_or++;
            else if(!strcmp(current->value, "&&"))
                count->concat_and++;
            else if(!strcmp(current->value, ";"))
                count->concat_all++;
            else if(!strcmp(current->value, "if"))
                count->conditionals++;
            to_return[i++].args[0] = current->value;
            to_return[i] = create_command();
            j = 0;
            k = 0;
        }
        else if (current->type == standard_token && (!strcmp(current->value, "<") || !strcmp(current->value, "<>") || !strcmp(current->value, "<<")
        || !strcmp(current->value, "<<<") || !strcmp(current->value, ">") || !strcmp(current->value, ">>") || !strcmp(current->value, ">|")))
        {
            count->redirect++;
            to_return[i].redir[k++] = current->value;
            if (k == redir_size)
            {
                redir_size += redir_size;
                to_return[i].args = (char **)calloc(redir_size, sizeof(char*));
            }
            current = current->next;
            if (current != NULL)
            {
                to_return[i].redir[k++] = current->value;
                if (k == redir_size)
                {
                    redir_size += redir_size;
                    to_return[i].args = (char **)calloc(redir_size, sizeof(char*));
                }
            }
        }
        else
        {
            to_return[i].args[j++] = current->value;
            if (j == args_size)
            {
                args_size += args_size;
                to_return[i].args = (char**)calloc(args_size, sizeof(char*));
            }
        }
        if (current != NULL)
            current = current->next;
    }
    if (to_return[i].args[0] != NULL || to_return[i].redir[0] != NULL)
        i++;
    if (to_return[i - 1].args != NULL && to_return[i - 1].args[0] != NULL && !strcmp(to_return[i - 1].args[0], "&") && tokenizer.last->type == standard_token)
    {
        i--;
        to_return[i].args = NULL;
        to_return[i].redir = NULL;
        *bg = 1;
    }
    count->length = i;
    /*for (int k = 0; k < count->length; ++k) {
        if (to_return[k]->args[0] != NULL && !strcmp(to_return[k]->args[0], "ls")) {
            if((to_return[k]->redir[0] == NULL) || (to_return[k]->redir[0] != NULL && strcmp(to_return[k]->redir[0], ">") && strcmp(to_return[k]->redir[0], ">>"))) {
                i = 0;
                while (to_return[k]->args[i] != NULL) {
                    i++;
                }
                to_return[k]->args[i] = "--color=always";
                if (i == size) {
                    size *= size;
                    to_return[k]->args = (char **) malloc(sizeof(char *) * size);;
                }
                tokenizer[++i] = NULL;
            }
        }
    }*/
    return to_return;
}

extern command *tokenize(history *hist, int update_hist, char *line, counters *count, int *bg)
{
    if(update_hist)
        update_history(hist, line);
    return analyze_line(hist, line, count, bg);
}
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //