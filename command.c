// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //

// // // // // // // //
//  COMMAND LIBRARY: //
// // // // // // // //

#include "command.h"
#include "kilo.h"

void cd(char** tokens, int *status)
{
    if(tokens[1] == NULL)
        tokens[1] = getenv("HOME");
    *status = chdir(tokens[1]);
    if (*status)
        printf("cd: %s: No such file or directory\n", tokens[1]);
}

int execute(history *hist,  command *commands, counters count, int bg, linked_jobs *jobs, int *pid, int *status)
{
    int p = 0;
    if (commands == NULL)
        return 1;
    int pipes[2 * count.pipes][2], PIDS[count.length];
    for(int i = 0; i < 2 * count.pipes; i++)
        pipe(pipes[i]);
    int k = 0;
    while (k < count.length)
    {
        if(commands[k].args[0] == NULL)
        {
            if(commands[k].redir[0] != NULL && (!strcmp(commands[k].redir[0], ">") || !strcmp(commands[k].redir[0], ">>")))
                open(commands[k].redir[1], O_CREAT | O_TRUNC, 00700);
        }
        else if(strcmp(commands[k].args[0], "|") != 0)
        {
            if (count.pipes == 0 && count.redirect == 0)
            {
                if (!strcmp(commands[k].args[0], "exit"))
                {
                    *status = 0;
                    return bg;
                }
                else if (!strcmp(commands[k].args[0], "cd"))
                {
                    if (!bg)
                        cd(commands[k].args, status);
                }
                else if (!strcmp(commands[k].args[0], "editext"))
                {
                    p = fork();
                    if (p)
                        *pid = p;
                    else
                        *pid = getppid();
                    if(!p)
                        kilo(2,commands[k].args[1]);
                    waitpid(*pid, status, bg);
                    printf("\e[1;1H\e[2J");
                    return 1;
                }
                else if (!strcmp(commands[k].args[0], "jobs"))
                {
                    if (!bg)
                    {
                        jobs_list(jobs, status);
                    }
                }
                else if (!strcmp(commands[k].args[0], "history"))
                {
                    my_history_list(*hist, commands[k].args[1]);
                }
                else if(!strcmp(commands[k].args[0], "help"))
                {
                    select_help(commands[k].args, status);
                }
                else if (!strcmp(commands[k].args[0], "fg"))
                {
                    fg(jobs, commands[k].args[1], status);
                }
                else if (!strcmp(commands[k].args[0], "true"))
                {
                    *status = 0;
                }
                else if (!strcmp(commands[k].args[0], "false"))
                {
                    *status = 1;
                }
                else if(!strcmp(commands[k].args[0], "get"))
                {
                    *status = 0;
                    get(commands[k].args);
                }
                else if(!strcmp(commands[k].args[0], "set"))
                {
                    *status = 0;
                    set(hist, jobs, pid, commands[k].args);
                }
                else if(!strcmp(commands[k].args[0], "unset"))
                {
                    *status = 0;
                    unset(commands[k].args);
                }
                else
                {
                    p = fork();
                    PIDS[k] = p;
                    if (p)
                        *pid = p;
                    else
                        *pid = getppid();

                    if (!p && execvp(commands[k].args[0], commands[k].args))
                    {
                        *status = 1;
                        printf("%s: command not found\n", commands[k].args[0]);
                        exit(1);
                    }
                    if (bg)
                    {
                        jobs->last->data->pid[jobs->last->data->count] = p;
                        jobs->last->data->count +=1;
                    }
                    waitpid(p, status, bg);
                }
            }
            else
            {
                p = fork();
                PIDS[k] = p;
                if (p)
                    *pid = p;
                else
                    *pid = getppid();

                bool in = false, out = false;
                int fd_in = 0, fd_out = 0;
                int j = 0;
                if (!p)
                {
                    if (count.length > 1)
                    {
                        if(!k)
                            dup2(pipes[k][1], STDOUT_FILENO);
                        else if (k == count.length - 1)
                            dup2(pipes[k - 2][0], STDIN_FILENO);
                        else
                        {
                            dup2(pipes[k - 2][0], STDIN_FILENO);
                            dup2(pipes[k][1], STDOUT_FILENO);
                        }
                    }
                    while (commands[k].redir[j] != NULL)
                    {
                        if (!strcmp(commands[k].redir[j], "<"))
                        {
                            fd_in = open(commands[k].redir[j + 1], O_RDONLY, 00700);
                            if (!in)
                            {
                                in = true;
                                if (fd_in == -1)
                                {
                                    perror(NULL);
                                    exit(1);
                                }
                                dup2(fd_in, STDIN_FILENO);
                            }
                            close(fd_in);
                        }
                        else if (!strcmp(commands[k].redir[j], ">"))
                        {
                            fd_out = open(commands[k].redir[j + 1], O_WRONLY | O_CREAT | O_TRUNC, 00700);
                            if (!out)
                            {
                                out = true;
                                if (fd_out == -1)
                                {
                                    perror(NULL);
                                    exit(1);
                                }
                                dup2(fd_out, STDOUT_FILENO);
                            }
                            close(fd_out);
                        }
                        else if (!strcmp(commands[k].redir[j], ">>"))
                        {
                            fd_out = open(commands[k].redir[j + 1], O_WRONLY | O_CREAT | O_APPEND, 00700);
                            if (!out)
                            {
                                out = true;
                                if (fd_out == -1)
                                {
                                    perror(NULL);
                                    exit(1);
                                }
                                dup2(fd_out, STDOUT_FILENO);
                            }
                            close(fd_out);
                        }
                        j += 2;
                    }
                    if (!strcmp(commands[k].args[0], "exit"))
                    {
                        *status = 0;
                        return bg;
                    }
                    else if (!strcmp(commands[k].args[0], "cd"))
                    {
                        if (!bg)
                        {
                            cd(commands[k].args, status);
                            exit(1);
                        }
                    }
                    else if (!strcmp(commands[k].args[0], "jobs"))
                    {
                        if (!bg)
                        {
                            jobs_list(jobs, status);
                            exit(1);
                        }
                    }
                    else if (!strcmp(commands[k].args[0], "history"))
                    {
                        my_history_list(*hist, commands[k].args[1]);
                        exit(1);
                    }
                    else if(!strcmp(commands[k].args[0], "help"))
                    {
                        select_help(commands[k].args, status);
                        exit(1);
                    }
                    else if (!strcmp(commands[k].args[0], "fg"))
                    {
                        fg(jobs, commands[k].args[1], status);
                        exit(1);
                    }
                    else if (!strcmp(commands[k].args[0], "true"))
                    {
                        *status = 0;
                        exit(1);
                    }
                    else if (!strcmp(commands[k].args[0], "false"))
                    {
                        *status = 1;
                        exit(1);
                    }
                    else if(!strcmp(commands[k].args[0], "get"))
                    {
                        *status = 0;
                        get(commands[k].args);
                        exit(1);
                    }
                    else if(!strcmp(commands[k].args[0], "set"))
                    {
                        *status = 0;
                        set(hist, jobs, pid, commands[k].args);
                        exit(1);
                    }
                    else if(!strcmp(commands[k].args[0], "unset"))
                    {
                        *status = 0;
                        unset(commands[k].args);
                        exit(1);
                    }
                    else if (execvp(commands[k].args[0], commands[k].args))
                    {
                        *status = 1;
                        char *t = commands[k].args[0];
                        strcat(t, ": command not found\n");
                        write(2, t, strlen(t));
                        exit(1);
                    }
                }
                else
                {
                    if(!k && count.length > 1)
                        close(pipes[k][1]);
                    else if(k == count.length-1 && count.length > 1)
                        close(pipes[k - 2][0]);
                    else if(count.length > 1)
                    {
                        close(pipes[k - 2][0]);
                        close(pipes[k][1]);
                    }
                    if(count.length == 1)
                        waitpid(p, status, bg);
                    else
                    {
                        int q;
                        for(q = 0; q < k; q++)
                            waitpid(PIDS[k], status, bg);
                    }
                }
            }
        }
        k++;
    }
    return 1;
}

int control(history *hist, command *commands, counters count, int bg, linked_jobs *jobs, int *pid, int *status)
{
    if (bg)
    {
        job *new_job = create_job(hist);
        insert_job(jobs, new_job);
        printf("[%i] %s\n", jobs->index - 1, new_job->args);
        //jobs_update(jobs);
    }
    bool change = false, pc = false;
    int if_count = 0, if_status = 0;
    conditional_moment cm = none_m;
    if(count.concat_all > 0 || count.concat_and > 0 || count.concat_or > 0 || count.conditionals > 0)
    {
        command *new_commands = (command *)calloc((count.length + 1), sizeof(command));
        counters c = create_counter();
        for (int i = 0, j = 0; i < count.length; i++)
        {
            if (commands[i].args[0] != NULL)
            {
                if (!strcmp(commands[i].args[0], ";"))
                {
                    if(!pc)
                        execute(hist, new_commands, c, bg, jobs, pid, status);
                    count.concat_all--;
                    change = true;
                    pc = false;
                }
                else if (!strcmp(commands[i].args[0], "if"))
                {
                    if_count++;
                    if (if_count == 1)
                        continue;
                    c.conditionals++;
                }
                if (if_count == 1 && (!strcmp(commands[i].args[0], "then") || !strcmp(commands[i].args[0], "else")))
                {
                    if (!strcmp(commands[i].args[0], "then"))
                    {
                        cm = then_m;
                        control(hist, new_commands, c, bg, jobs, pid, status);
                        if_status = *status;
                    }
                    else if (!strcmp(commands[i].args[0], "else"))
                    {
                        cm = else_m;
                        if (!if_status)
                            control(hist, new_commands, c, bg, jobs, pid, status);
                    }
                    change = true;
                    pc = false;
                }
                else if (!strcmp(commands[i].args[0], "end"))
                {
                    if (if_count > 0)
                    {
                        if (if_count == 1)
                        {
                            if ((cm == then_m && !if_status) || (cm == else_m && if_status))
                                control(hist, new_commands, c, bg, jobs, pid, status);
                            cm = none_m;
                            change = true;
                            pc = false;
                        }
                        else
                            if_count--;
                    }
                    else
                        printf("end: unexpected\n");
                }
                else if(!strcmp(commands[i].args[0], "||"))
                {
                    if (if_count > 0)
                        c.concat_or++;
                    else if (!pc)
                    {
                        execute(hist, new_commands, c, bg, jobs, pid, status);
                        if (!*status)
                        {
                            if (count.concat_all > 0)
                                pc = true;
                            else
                                return 1;
                        }
                        change = true;
                    }
                }
                else if(!strcmp(commands[i].args[0], "&&"))
                {
                    if (if_count > 0)
                        c.concat_and++;
                    else if (!pc)
                    {
                        execute(hist, new_commands, c, bg, jobs, pid, status);
                        if (*status)
                        {
                            if (count.concat_all > 0)
                                pc = true;
                            else
                                return 1;
                        }
                        change = true;
                    }
                }
                else if (!strcmp(commands[i].args[0], "|"))
                    c.pipes++;
            }
            if (change)
            {
                new_commands = (command *)calloc((count.length + 1), sizeof(command));
                c = create_counter();
                j = 0;
                change = false;
            }
            else
            {
                if (if_count < 1 && (!strcmp(commands[i].args[0], "then") || !strcmp(commands[i].args[0], "else")))
                    printf("%s: unexpected\n", commands[i].args[0]);
                else
                {
                    int k = 0;
                    while (commands[i].redir[k] != NULL && (!strcmp(commands[i].redir[k], "<") || !strcmp(commands[i].redir[k], ">") || !strcmp(commands[i].redir[k], ">>")))
                    {
                        c.redirect++;
                        k += 2;
                    }
                    new_commands[j++] = commands[i];
                    new_commands[j] = create_command();
                    c.length++;
                }
            }
        }
        return execute(hist, new_commands, c, bg, jobs, pid, status);
    }
    else
        return execute(hist, commands, count, bg, jobs, pid, status);
}

// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //