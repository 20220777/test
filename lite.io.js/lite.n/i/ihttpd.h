#ifndef __IHTTPD_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__
#define __IHTTPD_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__

#include <stdio.h>
#include <stdint.h>

int32_t ihttpd(uint8_t* task, int32_t fd, int8_t* uri, int32_t (*f)(void*,int32_t,int8_t*,int32_t,void*,void*),void* o);

#endif

