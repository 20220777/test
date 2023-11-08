#ifndef ____UTILS_H_3E768634_8484_4626_B86C_40859CBBA626____
#define ____UTILS_H_3E768634_8484_4626_B86C_40859CBBA626____

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define TOP_TITLE  "\r\n****************************************\r\n" "*    [Start Task]                      *" "\r\n****************************************\r\n"
#define PREFIX     printf("|        |");
#define CRLF       printf("\r\n");


#define BOX(a)       printf("+------------------------------------------------------------------------------+\r\n" \
                            "|                                                                              |\r\n"\
                            "| %-76s |\r\n" \
                            "|                                                                              |\r\n"\
                            "+------------------------------------------------------------------------------+\r\n", a)

#define __DELAY(a,b)     ((a/b)+(a%b?1:0))



#endif
