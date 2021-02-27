// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //

// // // // // // //
//  MAIN LIBRARY: //
// // // // // // //

#include "command.h"
#include <readline/readline.h>
#include <readline/history.h>

int ctrlC = 1;
int pid = -1;
int pid_shell = -1;

void shell()
{
    printf("\n");
    printf("                    \e[100m            \e[0m\n");
    printf("                 \e[100m  \e[41m              \e[100m  \e[0m\n");
    printf("              \e[100m \e[41m                      \e[100m \e[0m\n");
    sleep(1);
    printf("            \e[100m \e[41m         \e[103m  \e[41m    \e[103m  \e[41m         \e[100m \e[0m\n");
    printf("          \e[100m \e[41m        \e[103m      \e[41m  \e[103m      \e[41m        \e[100m \e[0m\n");
    printf("        \e[100m \e[41m     \e[103m   \e[41m  \e[103m      \e[41m  \e[103m      \e[41m  \e[103m   \e[41m     \e[100m \e[0m\n");
    sleep(1);
    printf("      \e[100m \e[41m      \e[103m     \e[41m  \e[103m     \e[41m  \e[103m     \e[41m  \e[103m     \e[41m      \e[100m \e[0m\n");
    printf("     \e[100m \e[41m      \e[103m      \e[41m  \e[103m     \e[41m  \e[103m     \e[41m  \e[103m      \e[41m      \e[100m \e[0m\n");
    printf("    \e[100m \e[41m     \e[103m \e[41m  \e[103m     \e[41m  \e[103m     \e[41m  \e[103m     \e[41m  \e[103m     \e[41m  \e[103m \e[41m     \e[100m \e[0m\n");
    sleep(1);
    printf("  \e[100m \e[41m    \e[103m    \e[41m  \e[103m     \e[41m   \e[103m    \e[41m  \e[103m    \e[41m   \e[103m     \e[41m  \e[103m    \e[41m    \e[100m \e[0m\n");
    printf("  \e[100m \e[41m    \e[103m     \e[41m  \e[103m     \e[41m  \e[103m    \e[41m  \e[103m    \e[41m  \e[103m     \e[41m  \e[103m     \e[41m    \e[100m \e[0m\n");
    printf(" \e[100m \e[41m      \e[103m     \e[41m  \e[103m    \e[41m  \e[103m    \e[41m  \e[103m    \e[41m  \e[103m    \e[41m  \e[103m     \e[41m      \e[100m \e[0m\n");
    sleep(1);
    printf(" \e[100m \e[41m    \e[103m \e[41m  \e[103m     \e[41m  \e[103m    \e[41m \e[103m    \e[41m  \e[103m    \e[41m \e[103m    \e[41m  \e[103m     \e[41m  \e[103m \e[41m    \e[100m \e[0m\n");
    printf(" \e[100m \e[41m    \e[103m  \e[41m  \e[103m     \e[41m  \e[103m   \e[41m \e[103m    \e[41m  \e[103m    \e[41m \e[103m   \e[41m  \e[103m     \e[41m  \e[103m  \e[41m    \e[100m \e[0m\n");
    printf(" \e[100m \e[41m    \e[103m   \e[41m  \e[103m     \e[41m \e[103m   \e[41m \e[103m    \e[41m  \e[103m    \e[41m \e[103m   \e[41m \e[103m     \e[41m  \e[103m   \e[41m    \e[100m \e[0m\n");
    sleep(1);
    printf(" \e[100m \e[41m   \e[103m     \e[41m  \e[103m    \e[41m \e[103m   \e[41m \e[103m    \e[41m  \e[103m    \e[41m \e[103m   \e[41m \e[103m    \e[41m  \e[103m     \e[41m   \e[100m \e[0m\n");
    printf(" \e[100m \e[41m    \e[103m     \e[41m  \e[103m   \e[41m \e[103m   \e[41m \e[103m    \e[41m  \e[103m    \e[41m \e[103m   \e[41m \e[103m   \e[41m  \e[103m     \e[41m    \e[100m \e[0m\n");
    printf(" \e[100m \e[41m      \e[103m    \e[41m  \e[103m  \e[41m \e[103m   \e[41m \e[103m    \e[41m  \e[103m    \e[41m \e[103m   \e[41m \e[103m  \e[41m  \e[103m    \e[41m      \e[100m \e[0m\n");
    sleep(1);
    printf("   \e[100m \e[41m       \e[103m  \e[41m \e[103m  \e[41m \e[103m   \e[41m \e[103m    \e[41m  \e[103m    \e[41m \e[103m   \e[41m \e[103m  \e[41m \e[103m  \e[41m       \e[100m \e[0m\n");
    printf("     \e[100m \e[41m     \e[103m  \e[41m \e[103m  \e[41m \e[103m   \e[41m \e[103m    \e[41m  \e[103m    \e[41m \e[103m   \e[41m \e[103m  \e[41m \e[103m  \e[41m     \e[100m \e[0m\n");
    printf("       \e[100m \e[41m   \e[103m  \e[41m \e[103m  \e[41m \e[103m   \e[41m \e[103m    \e[41m  \e[103m    \e[41m \e[103m   \e[41m \e[103m  \e[41m \e[103m  \e[41m   \e[100m \e[0m\n");
    sleep(1);
    printf("         \e[100m \e[41m \e[103m  \e[41m \e[103m  \e[41m \e[103m   \e[41m \e[103m    \e[41m  \e[103m    \e[41m \e[103m   \e[41m \e[103m  \e[41m \e[103m  \e[41m \e[100m \e[0m\n");
    printf("         \e[100m \e[41m \e[103m  \e[41m \e[103m  \e[41m \e[103m   \e[41m \e[103m    \e[41m  \e[103m    \e[41m \e[103m   \e[41m \e[103m  \e[41m \e[103m  \e[41m \e[100m \e[0m\n");
    printf("         \e[100m \e[41m \e[103m  \e[41m \e[103m  \e[41m \e[103m   \e[41m \e[103m    \e[41m  \e[103m    \e[41m \e[103m   \e[41m \e[103m  \e[41m \e[103m  \e[41m \e[100m \e[0m\n");
    sleep(1);
    printf("         \e[100m \e[41m                                \e[100m \e[0m\n");
    printf("         \e[100m                                  \e[0m\n");
    sleep(3);
}

void start()
{
    printf("\033[H\033[J");
    printf("%s\n\n", "     \e[95mWELCOME TO SHELL-AS\e[0m");
    printf("%s\n", "\e[92mBY: \e[94mARNEL SANCHEZ RODRIGUEZ");
    printf("%s\n", "                \e[0m&");
    printf("%s\n", "    \e[94mSAMUEL EFRAIN PUPO WONG\e[0m");
    sleep(3);
    printf("\033[H\033[J");
}

char *prompt()
{
    char *dir = getcwd(NULL, 0);
    if (dir == NULL)
        exit(1);
    char *home = getenv("HOME");
    char *new_dir = (char *)calloc(strlen(dir) - strlen(home) + 1, sizeof(char));
    if(!strncasecmp(dir, home, strlen(home)))
    {
        new_dir[0] = '~';
        int i = 1;
        for (int j = strlen(home); j < strlen(dir); i++, j++)
            new_dir[i] = dir[j];
        new_dir[i] = 0;
    }
    else
        new_dir = dir;
    char* user = (char *)calloc(SIZE, sizeof(char));
    strcpy(user, "\e[1m(shell-AS) \e[92m");
    strcat(user, getenv("USER"));
    strcat(user,"\e[0m\e[1m:\e[94m\e[1m");
    strcat(user, new_dir);
    strcat(user,"\e[1m\e[0m");
    strcat(user,"$ ");
    return user;
}

void print(int signal)
{
    if(pid_shell != pid)
    {
        if (ctrlC == 2)
        {
            kill(pid, 9);
        }
        else
        {
            kill(pid, 2);
        }
        ctrlC++;
        printf("\n");
    }
    else
    {
        printf("\n%s", prompt());
    }
}

void end()
{
    printf("\033[H\033[J");
    printf("%s\n", "     \e[95mPLEASE, COME BACK AGAIN\e[0m");
    sleep(2);
    printf("\033[H\033[J");
}

int main()
{
    char *location = getcwd(NULL, 0), *line;
    if (location == NULL)
        return 1;
    signal(2, print);
    pid_shell = getpid();
    int bg, status;
    history hist = load_history();
    int temp = hist.first;
    while (hist.last!=temp)
    {
        add_history(hist.args[temp++]);
    }
    command *commands;
    counters count;
    linked_jobs *jobs = create_linked_jobs();
    //shell();
    //start();
    do
    {
        if (temp < hist.last)
        {
            add_history(hist.args[temp % HISTORY_SIZE]);
            temp = hist.last;
        }
        pid=pid_shell;
        line = readline(prompt());
        count = create_counter();
        bg = 0;
        commands = tokenize(&hist, 1, line, &count, &bg);
        status = 0;
        ctrlC = 1;
    }
    while(control(&hist, commands, count, bg, jobs, &pid, &status));
    if (temp < hist.last - 1)
    {
        add_history(hist.args[temp % HISTORY_SIZE]);
    }
    save_history(location, hist);
    //free(location);
    free(line);
    free(commands);
    return 0;
}

// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //