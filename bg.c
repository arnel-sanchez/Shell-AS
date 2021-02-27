// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //

// // // // // //
// BG LIBRARY: //
// // // // // //

#include "bg.h"

void jobs_update(linked_jobs *jobs, int *status)
{
    *status = 0;
    /*if (jobs->count < 1)
        return;
    job_node *node = jobs->first, *next, *previous;
    job *job_data;
    while (node != NULL && node != jobs->last)
    {
        job_data = node->data;
        next = node->next;
        if (waitpid(job_data->pid, 0, WNOHANG))
        {
            printf("[%i]    %i    ", node->index, job_data->pid);
            previous = node->previous;
            if (previous != NULL)
                previous->next = next;
            else
                jobs->first = next;
            if (next != NULL)
                next->previous = previous;
            else
                jobs->last = previous;
            jobs->count -= 1;
            printf("Done    ");
            for (int j = 0; job_data->args[j] != NULL; j++)
                printf("%s ", job_data->args[j]);
            printf(" %s", job_data->pwd);
            printf("\n");
            free(node);
        }
        node = next;
    }*/
}

void jobs_list(linked_jobs *jobs, int *status)
{
    *status = 0;
    if (jobs->count < 1)
        return;
    int ended = 0;
    job_node *node = jobs->first, *next, *previous;
    job *job_data;
    while (node != NULL)
    {
        job_data = node->data;
        printf("[%i]+  ", node->index);
        next = node->next;
        bool done = true;
        for (int i = 0; i < job_data->count; i++)
            if (!waitpid(job_data->pid[i], 0, WNOHANG))
                done = false;
        if (done)
        {
            previous = node->previous;
            if (previous != NULL)
                previous->next = next;
            else
                jobs->first = next;
            if (next != NULL)
                next->previous = previous;
            else
                jobs->last = previous;
            printf("Done                    ");
            ended = 1;
        }
        else
            printf("Running                 ");
        printf("%s\n", job_data->args);
        if (ended)
        {
            free(node);
            ended = 0;
            jobs->count -= 1;
        }
        node = next;
    }
}

void fg(linked_jobs *jobs, char *id, int *status)
{
    *status = 0;
    if (jobs->count < 1)
    {
        printf("fg: current: no such job\n");
        *status = 0;
    }
    else if (id == NULL)
    {
        job_node *node = jobs->last;
        for (int i = 0; i < node->data->count; i++)
            waitpid(node->data->pid[i], 0, 0);
        jobs->count -= 1;
    }
    else
    {
        int pid = atoi(id);
        if (pid > 0)
        {
            job_node *node = jobs->first;
            while (node != NULL)
            {
                job_node *next = node->next;
                if (pid == node->index)
                {
                    job_node *previous = node->previous;
                    if (previous != NULL)
                        previous->next = next;
                    else
                        jobs->first = next;
                    if (next != NULL)
                        next->previous = previous;
                    else
                        jobs->last = previous;
                    jobs->count -= 1;
                    for (int i = 0; i < node->data->count; i++)
                        if (!waitpid(node->data->pid[i], 0, 0))
                    free(node);
                    return;
                }
                node = next;
            }
        }
        printf("fg: %s: no such job\n", id);
    }
}

// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //