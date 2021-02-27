// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //

// // // // // // // //
//  HISTORY LIBRARY: //
// // // // // // // //

#ifndef PROJECTS_HISTORY_H
#define PROJECTS_HISTORY_H

#include <fcntl.h>
#include <unistd.h>

#include "parser.h"
#include "structs.h"

#define PERMS 0666

extern history load_history();

extern void my_history_list(history hist, char *count);

extern void update_history(history *hist, char *line);

extern char *again(history *hist, token **tok);

extern void save_history(char *location, history hist);

#endif //PROJECTS_HISTORY_H

// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //