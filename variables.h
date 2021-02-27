// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //

// // // // // // // // //
//  VARIABLES LIBRARY:  //
// // // // // // // // //

#ifndef PROJECT_VARIABLES_H
#define PROJECT_VARIABLES_H

#include "command.h"
//#include "parser.h"
#include "structs.h"

extern void set(history *hist, linked_jobs *jobs, int *pid, char **tokens);

extern void get(char **tokens);

extern void unset(char **tokens);

#endif //PROJECT_VARIABLES_H

// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //