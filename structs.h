// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //

// // // // // // // //
//  STRUCTS LIBRARY: //
// // // // // // // //

#ifndef PROJECT_STRUCTS_H
#define PROJECT_STRUCTS_H

#include <stdlib.h>
#include <stdbool.h>

#define SIZE 1024
#define HISTORY_SIZE 101

typedef struct history
{
    bool updated;
    int first;
    int last;
    char **args;
} history;

typedef enum token_type
{
    standard_token,
    commented_token
} token_type;

typedef struct token
{
    token_type type;
    char *value;
    struct token *previous;
    struct token *next;
} token;

typedef struct token_node
{
    token value;
    struct token_node *previous;
    struct token_node *next;
} token_node;

typedef struct linked_tokens
{
    token *first;
    token *last;
} linked_tokens;

typedef enum character
{
    none,                // no character
    normal,              // normal character
    simple_quotes,       // '
    double_quotes,       // "
    stdout_char,         // >
    concatenated_stdout, // >>
    forced_stdout,       // >|
    stdin_char,          // <
    stdin_stdout,        // <>
    label_stdin,         // <<
    chain_stdin,         // <<<
    pipe_char,           // |
    or,                  // ||
    bg,                  // &
    and,                 // &&
    semicolon,           // ;
} character;

typedef struct command
{
    char **args;
    char **redir;
} command;

typedef struct counters
{
    int length;
    int pipes;
    int redirect;
    int concat_or;
    int concat_and;
    int concat_all;
    int conditionals;
} counters;

typedef enum conditional_moment
{
    none_m,
    then_m,
    else_m
} conditional_moment;

typedef struct job
{
    char *args;
    int *pid;
    int count;
} job;

typedef struct job_node
{
    int index;
    job *data;
    struct job_node *previous;
    struct job_node *next;
} job_node;

typedef struct linked_jobs
{
    int index;
    job_node *first;
    job_node *last;
    int count;
} linked_jobs;

typedef struct variables
{
    char **var;
    char **value;
} variables;

extern history create_history(int last, char **args);

extern token *create_token(int size);

extern linked_tokens create_linked_tokens();

extern command create_command();

extern counters create_counter();

extern job *create_job(history *hist);

extern linked_jobs *create_linked_jobs();

extern void insert_job(linked_jobs *jobs, job *new_job);

#endif //PROJECT_STRUCTS_H

// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //