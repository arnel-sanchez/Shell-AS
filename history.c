// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //

// // // // // // // //
//  HISTORY LIBRARY: //
// // // // // // // //

#include "history.h"

history load_history()
{
    int line_size = SIZE, fd = open("recent.bin", O_RDONLY), last = 0, i = 0, quotes = 0;
    char buf, **args = (char **)calloc(HISTORY_SIZE, sizeof(char*)), *line = (char *)calloc(line_size, sizeof(char));
    if (fd < 1)
    {
        fd = creat("recent.bin", PERMS);
        write(fd, "HISTORY:\n", 9);
        args[last] = "HISTORY:";
        last += 1;
    }
    else
    {
        fd = open("recent.bin", O_WRONLY);
        write(fd, "HISTORY:\n", 9);
        close(fd);
        fd = open("recent.bin", O_RDONLY);
        while (read(fd, &buf, 1))
        {
            if (buf == '"')
                quotes = !quotes;
            if (!quotes && buf == '\n')
            {
                if (i == 0)
                    break;
                args[last] = line;
                last += 1;
                if (last >= HISTORY_SIZE)
                    break;
                i = 0;
                line = (char *)calloc(line_size, sizeof(char));
                continue;
            }
            line[i++] = buf;
            if (i == line_size)
            {
                line_size += line_size;
                args[last] = (char *)realloc(args[last], line_size * sizeof(char*));
            }
        }
        if (last < HISTORY_SIZE && i > 0)
        {
            args[last] = line;
            last += 1;
        }
    }
    close(fd);
    return create_history(last, args);
}

void my_history_list(history hist, char *count)
{
    int value;
    if (count == NULL)
        value = 10;
    else
    {
        value = atoi(count);
        if (value < 1)
            value = 10;
        else if (value > 100)
        {
            printf("history: %s: correct numeric argument required\n", count);
            return;
        }
    }
    int j = hist.last - value;
    if (hist.last > HISTORY_SIZE && hist.last % HISTORY_SIZE == 1)
        j -= 1;
    if (j < 0)
        j = 1;
    for (int i = 1; j < hist.last; i++, j++)
        if (j % HISTORY_SIZE != 0)
            printf(" %i  %s\n", i, hist.args[j % HISTORY_SIZE]);
}

void update_history(history *hist, char *line)
{
    int previous = hist->last - 1;
    if (previous % HISTORY_SIZE == 0)
        previous -= 1;
    if (strcmp(line, "") != 0 && line[0] != ' ' && (hist->first == hist->last || strcmp(line, hist->args[previous % HISTORY_SIZE]) != 0))
    {
        hist->updated = true;
        hist->args[hist->last % HISTORY_SIZE] = line;
        hist->last += 1;
        if (hist->last % HISTORY_SIZE == 0)
            hist->last += 1;
        if (hist->last > HISTORY_SIZE)
            hist->first += 1;
        if (hist->first % HISTORY_SIZE == 0)
        {
            hist->first = 1;
            hist->last %= HISTORY_SIZE;
        }
    }
    else
        hist->updated = false;
}

char *again(history *hist, token **tok)
{
    if (hist->first == hist->last)
    {
        printf("again: no history\n");
        return "";
    }
    if (hist->updated)
    {
        if (hist->first > 1)
            hist->first -= 1;
        if (hist->last > 1)
            hist->last -= 1;
        if (hist->last % HISTORY_SIZE == 0)
            hist->last -= 1;
        hist->updated = false;
    }
    int value = hist->last - 1, size = 0;
    *tok = (*tok)->next;
    if (*tok != NULL)
    {
        value = atoi((*tok)->value);
        if (value > 0)
        {
            if (value >= hist->last)
            {
                printf("again: %s: correct numeric argument required\n", (*tok)->value);
                return "";
            }
            *tok = (*tok)->next;
            if (*tok != NULL)
            {
                size = atoi((*tok)->value);
                if (size > 0)
                {
                    if (size > 100 || size < value)
                    {
                        printf("again: %s: correct numeric argument required\n", (*tok)->value);
                        return "";
                    }
                    size = hist->last - size - 1;
                    *tok = (*tok)->next;
                }
                else
                {
                    if (value > 10)
                    {
                        printf("again: %s: correct numeric argument required\n", (*tok)->value);
                        return "";
                    }
                    size = hist->last - 11;
                }
            }
            else
            {
                if (value > 10)
                {
                    printf("again: %i: correct numeric argument required\n", value);
                    return "";
                }
                size = hist->last - 11;
            }
            if (size < 0)
                size = 0;
            value += size;
        }
        else
            value = hist->last - 1;
    }
    if (value % HISTORY_SIZE == 0)
        value -= 1;
    return hist->args[value % HISTORY_SIZE];
}

void save_history(char *location, history hist)
{
    strcat(location, "/recent.bin");
    int fd = creat(location, PERMS);
    write(fd, "HISTORY:\n", 9);
    for (int i = hist.first; i < hist.last; i++)
        if (i % HISTORY_SIZE != 0)
        {
            write(fd, hist.args[i % HISTORY_SIZE], strlen(hist.args[i % HISTORY_SIZE]));
            write(fd, "\n", 1);
        }
    close(fd);
}

// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //