#ifndef __PROTOCOL_JMT_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__
#define __PROTOCOL_JMT_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__

#include <stdint.h>


void* on_jmt_protocol_check(void* o, int8_t* b, int32_t sz, int32_t code);
uint8_t jmt_hex_strm(int8_t* in, int32_t sz, int8_t* out);

static uint8_t jmt_protocol_info[2] = {0x06, 0x0D};




#endif