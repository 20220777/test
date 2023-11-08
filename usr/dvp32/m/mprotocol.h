#ifndef __MPROTOCOL_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__
#define __MPROTOCOL_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__



#define STX                0x02
#define ETX                0x03
#define PROTOCOL_SZ        15

int on_protcol_check(unsigned char* se, char* b, int sz, int* pos, char* o, int* osz, void* cbf(char*, int));
int on_protcol_check_HEX(unsigned char* se, int maxsz, unsigned int* SR, char* b, int sz, int* pos, char* o, int* osz);


#endif
