/*****************************************************************************/
/*                                                                           */
/*            NCLab (Networked Control Lab) CORE version 1.0                 */
/*                                                                           */
/*****************************************************************************/
/*****************************************************************************/
/*                                                                           */
/*  File Name         : __error.h      	                                     */
/*                                                                           */
/*  Description       : This file contains all the necessary constants ,     */
/*                      type definitions according to CAST specifications,   */
/*                      common system headers.                               */
/*                                                                           */
/*                                                                           */
/*  Issues / Problems : None                                                 */
/*                                                                           */
/*  Revision History  :                                                      */
/*                                                                           */
/*        DD MM YYYY   Author(s)        Changes (Describe the changes made)  */
/*        01 01 2007   Shin Seunghyeok  Draft                                */
/*        01 12 2009   Shin Seunghyeok  Draft                                */
/*                                                                           */
/*****************************************************************************/
#ifndef __ERROR_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__
#define __ERROR_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__



#define E_NORMAL                                   0
#define E_UNKNOWN_FAIL                             0xEFFFFFF1
#define E_HANDLE_NULL                              0xEFFFFFFF
#define E_NULL                                     0xFFFFFFFF
#define E_ABNORMAL                                 0xE0000000
#define E_ABNORMAL_STATUS                          0xE0000001
#define E_CRITICAL_ERROR                           0xE0000002


#define E_ALLOC_FAIL                               0xE000000F
#define E_IO_ERROR                                 0xE0000010
#define E_READING                                  0xE000101B
#define E_READ_COMPLETE                            0xE000101A
#define E_READ_FAIL                                0xE000101F
#define E_WRITEING                                 0xE000100B
#define E_WRITE_COMPLETE                           0xE000100A
#define E_WRITE_FAIL                               0xE000100F
#define E_IO_INPUT_OK                              0xE0001010
#define E_IO_CLOSEING                              0xE000FDFB
#define E_IO_CLOSE_COMPLETE                        0xE000FDFA
#define E_IO_CLOSE_FAIL                            0xE000FDFF
#define E_IO_OPENING                               0xE000FD0B
#define E_IO_OPEN_COMPLETE                         0xE000FD0A
#define E_IO_OPEN_FAIL                             0xE000FD0F
#define E_IO_REMOTE_CONNECTING                     0xE000FDAB
#define E_IO_REMOTE_CONNECT_COMPLETE               0xE000FDAA
#define E_IO_REMOTE_CONNECT_FAIL                   0xE000FDAF
#define E_CLIENT_CONNECTING                        0xE000FDCB
#define E_CLIENT_CONNECT_COMPLETE                  0xE000FDCA
#define E_CLIENT_CONNECT_FAIL                      0xE000FDCF
#define E_CLIENT_BUFFER_PTR                        0xE000BF0B

#define E_INPUT_NULL                               0xEFFF101B
#define E_OUTPUT_NULL                              0xEFFF100B
#define E_SIZE                                     0xEFFF105B


#define E_SIFR_NORMAL_SUCCESS                      E_NORMAL
#define E_SIFR_SELFCHECK_FAIL                      E_CRITICAL_ERROR
#define E_SIFR_ENCODEING                           0xE500ECDB
#define E_SIFR_ENCODE_COMPLETE                     0xE500ECDA
#define E_SIFR_DECODEING                           0xE500DCDB
#define E_SIFR_DECODE_COMPLETE                     0xE500DCDA
#define E_SIFR_ARIA_KEY_NULL                       0xE5A10001
#define E_SIFR_ARIA_KEY_SIZE                       0xE5A10002
#define E_SIFR_ARIA_VECTOR_NULL                    0xE5A10003
#define E_SIFR_ARIA_VECTOR_SIZE                    0xE5A10004
#define E_SIFR_ARIA_CTR_NULL                       0xE5A10005
#define E_SIFR_ARIA_CTR_SIZE                       0xE5A10006
#define E_SIFR_LEA_KEY_NULL                        0xE5A20001
#define E_SIFR_LEA_KEY_SIZE                        0xE5A20002
#define E_SIFR_LEA_VECTOR_NULL                     0xE5A20003
#define E_SIFR_LEA_VECTOR_SIZE                     0xE5A20004
#define E_SIFR_LEA_CTR_NULL                        0xE5A20005
#define E_SIFR_LEA_CTR_SIZE                        0xE5A20006
#define E_SIFR_SEED_KEY_NULL                       0xE5A30001
#define E_SIFR_SEED_KEY_SIZE                       0xE5A30002
#define E_SIFR_SEED_VECTOR_NULL                    0xE5A30003
#define E_SIFR_SEED_VECTOR_SIZE                    0xE5A30004
#define E_SIFR_SEED_CTR_NULL                       0xE5A30005
#define E_SIFR_SEED_CTR_SIZE                       0xE5A30006
#define E_SIFR_HIGHT_KEY_NULL                      0xE5A40001
#define E_SIFR_HIGHT_KEY_SIZE                      0xE5A40002
#define E_SIFR_HIGHT_VECTOR_NULL                   0xE5A40003
#define E_SIFR_HIGHT_VECTOR_SIZE                   0xE5A40004
#define E_SIFR_HIGHT_CTR_NULL                      0xE5A40005
#define E_SIFR_HIGHT_CTR_SIZE                      0xE5A40006




#endif