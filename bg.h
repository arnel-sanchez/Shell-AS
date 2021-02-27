// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //

// // // // // //
// BG LIBRARY: //
// // // // // //

#ifndef PROJECT_BG_H
#define PROJECT_BG_H

#include <stdio.h>
#include <wait.h>

#include "structs.h"

extern void jobs_update(linked_jobs *jobs, int *status);

extern void jobs_list(linked_jobs *jobs, int *status);

extern void fg(linked_jobs *jobs, char *id, int *status);

#endif //PROJECT_BG_H

// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //
