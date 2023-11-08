/*****************************************************************************/
/*                                                                           */
/*            NCLab (Networked Control Lab) CORE version 1.0                 */
/*                                                                           */
/*****************************************************************************/
/*****************************************************************************/
/*                                                                           */
/*  File Name         : icommon.h                                            */
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
#ifndef __ICOMMON_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__
#define __ICOMMON_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__
#include <stdint.h>


#define DEBUG                      0




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

#if 1//__STATIC__==1
extern int32_t __setMessage(void* h, void* m, void* w, void* l);
extern int32_t __putMessage(void* h, void* m, void* w, void* l);

#endif


#endif



#if 0
@sc create WAAS_NODE binpath= "[EXEC] --m service --d WAAS_NODE --s WAAS_NODE --X [code.X.x86.dll] --l [LOG PATH] -- e d2" start= auto
@sc start WAAS_NODE

@sc stop WAAS_NODE
@sc delete WAAS_NODE
#endif



#if 0
#!/bin/bash

# cd /lib/systemd/system
# ln -s /usr/local/node/x32/node.c.service .
# systemctl status node.c.service
# systemctl daemon-reload
# systemctl enable node.c.service
# systemctl start node.c.service


# node.c.service
HOME=`pwd`
$HOME/pkg/node.c.$1.out --m console --d WAAS_NODE --s WAAS_NODE --X $HOME/pkg/code.X.$1.so --p $HOME/pkg/$1 --l /usr/local/node/log --e d7

#endif
