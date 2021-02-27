// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //

// // // // // // // //
//  PARSER LIBRARY:  //
// // // // // // // //

#ifndef PROJECT_PARSER_H
#define PROJECT_PARSER_H

#include <stdio.h>
#include <string.h>

#include "history.h"
#include "structs.h"

extern command *tokenize(history *hist, int update_hist, char *line, counters *count, int *bg);

#endif //PROJECT_PARSER_H

// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //