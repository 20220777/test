#ifndef __MDBC_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__
#define __MDBC_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__

#include <stdlib.h>
#include <string.h>

#include <mysql/6.x/include/mysql.h>

#pragma comment(lib, "mysql/6.x/lib/libmysql.lib")

#define DB_HOST    "1.246.219.218"
#define DB_USER    "MANANDTEL"
#define DB_PASS    "aosdpsxpf"
#define DB_NAME    "smart_factory_upper"
#define DB_PORT    "3306"



int mdbcOpen(void** hdl, char* host, char* port, char* user, char* pass, char* name, void* (*f)(int));
int mdbcClose(void** hdl);

int mdbcRead(void* hdl, int fd, char* b, int sz);
int mdbcWrite(void* hdl, int fd, char* b, int sz);
int mdbcQuery(void* hdl, int fd, char* query, int sz);

#endif