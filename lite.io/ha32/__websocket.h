/*****************************************************************************/
/*                                                                           */
/*            NCLab (Networked Control Lab) CORE version 1.0                 */
/*                                                                           */
/*****************************************************************************/
/*****************************************************************************/
/*                                                                           */
/*  File Name         : __socket.h                                           */
/*                                                                           */
/*  Description       : This file contains all the necessary constants ,     */
/*                      type definitions according to CAST specifications,	 */
/*                      common system headers.                               */
/*                                                                           */
/*                                                                           */
/*  Issues / Problems : None                                                 */
/*                                                                           */
/*  Revision History  :                                                      */
/*                                                                           */
/*        DD MM YYYY   Author(s)        Changes (Describe the changes made)  */
/*        18 03 2021   Shin Seunghyeok  Draft                                */
/*                                                                           */
/*****************************************************************************/
#ifndef ____WEBSOCKET_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__
#define ____WEBSOCKET_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__
#include <stdint.h>
#include <__common.h>
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//////                                                                   //////
//////                                                                   //////
//////                          User Variable                            //////
//////                                                                   //////
//////                                                                   //////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************/
/*****************************************************************************/
/*********************************        ************************************/
/*********************************        ************************************/
/*********************************        ************************************/
/*****************************                ********************************/
/*******************************            **********************************/
/*********************************        ************************************/
/************************************   **************************************/
/************************************* ***************************************/
/*****************************************************************************/






///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//////                                                                   //////
//////                                                                   //////
//////                           WebSocket                               //////
//////                                                                   //////
//////                                                                   //////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************/
/*****************************************************************************/
/*********************************        ************************************/
/*********************************        ************************************/
/*********************************        ************************************/
/*****************************                ********************************/
/*******************************            **********************************/
/*********************************        ************************************/
/************************************   **************************************/
/************************************* ***************************************/
/*****************************************************************************/
#if __WEBSOCKET__
#if __STATIC__
#if defined __cplusplus
extern "C"
#endif
int32_t __websocket_fdset(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o);

#if defined __cplusplus
extern "C"
#endif
int32_t __websocket_fd(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o);

#if defined __cplusplus
extern "C"
#endif
int32_t __websocket_read(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o);

#if defined __cplusplus
extern "C"
#endif
int32_t __websocket_write(void* h, int32_t fd,int8_t* b,int32_t sz, void* extra, void* o);

#if defined __cplusplus
extern "C"
#endif
int32_t __websocket_set_reader(void* h, uint8_t* mode, int32_t (*f[])(void*,int32_t,int8_t*,int32_t,void*,void*), void* o);

#if defined __cplusplus
extern "C"
#endif
int32_t __websocket_connect(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o);

#if defined __cplusplus
extern "C"
#endif
int32_t __websocket_open(void** h, int8_t* argv, int8_t* b, int32_t sz, int32_t (*f[])(void*,int32_t,int8_t*,int32_t,void*,void*), void* o);

#if defined __cplusplus
extern "C"
#endif
int32_t __websocket_close(void** h);

#if defined __cplusplus
extern "C"
#endif
int32_t __websocket_close_fd(void* h, int32_t fd);


#if defined __cplusplus
extern "C"
#endif
void __websocket_display_clientinfo(void* h);


#endif
#endif


#endif




