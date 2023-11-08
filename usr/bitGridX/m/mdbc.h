#ifndef __MDBC_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__
#define __MDBC_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <mysql/6.x/include/mysql.h>

#pragma comment(lib, "mysql/6.x/lib/libmysql.lib")

#define DB_HOST    "1.246.219.218"
#define DB_USER    "MANANDTEL"
#define DB_PASS    "aosdpsxpf"
#define DB_NAME    "smart_factory_upper"
#define DB_PORT    "3306"



int32_t mdbcOpen(void** hdl, int8_t* host, int8_t* port, int8_t* user, int8_t* pass, int8_t* name, void* (*f)(int32_t));
int32_t mdbcClose(void** hdl);

int32_t mdbcRead(void* hdl, int32_t fd, int8_t* b, int32_t sz);
int32_t mdbcWrite(void* hdl, int32_t fd, int8_t* b, int32_t sz);
int32_t mdbcQuery(void* hdl, int32_t fd, int8_t* query, int32_t sz);

#endif