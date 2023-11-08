#ifndef __PROTOCOL_SHOF_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__
#define __PROTOCOL_SHOF_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__

#include <cCommon.h>

#define EQUIP_IDS_COUNT        17
static unsigned char equip_ids[EQUIP_IDS_COUNT] = {1, 16, 0,};
static unsigned char shof_protocol[32] = {0x02, 0x03, 0x14,};


int on_shof_protocol_proc(char* b, int sz, int* pos, char* out);
int on_shof_protocol_request(char* b);

//int on_shof_protocol_proc(int* SR, char* b, int sz, int* pos, char* out);


#endif