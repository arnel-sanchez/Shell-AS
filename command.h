// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //

// // // // // // // //
//  COMMAND LIBRARY: //
// // // // // // // //

#ifndef PROJECT_EXECUTE_H
#define PROJECT_EXECUTE_H

#include "bg.h"
#include "help.h"
#include "history.h"
#include "variables.h"

extern char *pwd();

extern int control(history *hist, command *commands, counters count, int bg, linked_jobs *jobs, int *pid, int *status);

#endif //PROJECT_EXECUTE_H

// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //