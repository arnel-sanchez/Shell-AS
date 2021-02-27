// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //

// // // // // // // //
//  STRUCTS LIBRARY: //
// // // // // // // //

#include "structs.h"

history create_history(int last, char **args)
{
    history *hist = (history *)calloc(1, sizeof(history));
    hist->updated = false;
    hist->first = 1;
    hist->last = last;
    hist->args = args;
    return *hist;
}

token *create_token(int size)
{
    token *tok = (token *)calloc(1, sizeof(token));
    tok->type = standard_token;
    tok->value = (char *)calloc(size, sizeof(char));
    tok->previous = NULL;
    tok->next = NULL;
    return tok;
}

linked_tokens create_linked_tokens()
{
    linked_tokens *tokens = (linked_tokens *)calloc(1, sizeof(linked_tokens));
    tokens->first = NULL;
    tokens->last = NULL;
    return *tokens;
}

command create_command()
{
    command *comm = (command *)calloc(1, sizeof(command));
    comm->args = (char **)calloc(SIZE, sizeof(char *));
    comm->redir = (char **)calloc(SIZE, sizeof(char *));
    return *comm;
}

counters create_counter()
{
    counters *count = (counters *)calloc(1, sizeof(counters));
    count->length = 0;
    count->pipes = 0;
    count->redirect = 0;
    count->concat_or = 0;
    count->concat_and = 0;
    count->concat_all = 0;
    count->conditionals = 0;
    return *count;
}

job *create_job(history *hist)
{
    job *current = (job *)calloc(1, sizeof(job));
    int last = hist->last - 1;
    if (last == HISTORY_SIZE)
        last -= 1;
    else if (last > HISTORY_SIZE)
    {
        last %= HISTORY_SIZE;
        if (last < 1)
            last = 1;
    }
    current->args = hist->args[last];
    current->pid = (int *)calloc(SIZE, sizeof(int));
    current->count = 0;
    return current;
}

linked_jobs *create_linked_jobs()
{
    linked_jobs *jobs = (linked_jobs *)calloc(1, sizeof(linked_jobs));
    jobs->index = 1;
    jobs->first = NULL;
    jobs->last = NULL;
    jobs->count = 0;
    return jobs;
}

void insert_job(linked_jobs *jobs, job *new_job)
{
    job_node *new_node = (job_node *)calloc(1, sizeof(job_node));
    new_node->index = jobs->index;
    new_node->data = new_job;
    new_node->previous = NULL;
    new_node->next = NULL;
    jobs->index += 1;
    if (jobs->count < 1)
    {
        jobs->first = new_node;
        jobs->last = new_node;
    }
    else
    {
        new_node->previous = jobs->last;
        new_node->previous->next = new_node;
        jobs->last = new_node;
    }
    jobs->count += 1;
}

// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //