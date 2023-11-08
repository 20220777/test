/*****************************************************************************/
/*                                                                           */
/*                           ASE CORE version 1.0                            */
/*                                                                           */
/*****************************************************************************/
/*****************************************************************************/
/*                                                                           */
/*  File Name         : xjpeg.h                                              */
/*                                                                           */
/*  Description       :                                                      */
/*                                                                           */
/*                                                                           */
/*  Issues / Problems : None                                                 */
/*                                                                           */
/*  Revision History  :                                                      */
/*                                                                           */
/*        DD MM YYYY   Author(s)        Changes (Describe the changes made)  */
/*        01 01 2007   Shin Seunghyeok  Draft                                */
/*                                                                           */
/*****************************************************************************/
#ifndef __XJPEG_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__
#define __XJPEG_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__

#include <stdint.h>

//#include <stdio.h>
//#include <stdlib.h>

#include "cdjpeg.h"		/* Common decls for cjpeg/djpeg applications*/


typedef enum {
	FMT_BMP,		/* BMP format (Windows flavor)*/
	FMT_GIF,		/* GIF format*/
	FMT_OS2,		/* BMP format (OS/2 flavor)*/
	FMT_PPM,		/* PPM/PGM (PBMPLUS formats)*/
	FMT_RLE,		/* RLE format*/
	FMT_TARGA,		/* Targa format*/
	FMT_TIFF		/* TIFF format*/
} IMAGE_FORMATS;


//#if __WIN32__
//#pragma pack(1)
//#endif
//typedef struct
//#if __PACKED__
//__attribute__((packed))
//#endif
//{
//  int32_t (*file_to_buf)(xjpeg*, int8_t*, int8_t*, int32_t*);
//  int32_t (*buf_to_file)(xjpeg*, int8_t*, int8_t*, int32_t, int32_t);
//  int32_t (*buf_to_buf)(xjpeg*, int8_t*, int32_t, uint8_t*, int32_t*, int32_t);
//}
//xjpegvtbl;
//#if __WIN32__
//#pragma pack()
//#endif

#if __WIN32__
#pragma pack(1)
#endif
typedef struct
#if __PACKED__
__attribute__((packed))
#endif
{
  int32_t                   _id;
  //xjpegvtbl*          vtbl;


  /* for ijg*/
  struct jpeg_decompress_struct   dinfo;
  struct jpeg_compress_struct     cinfo;

  struct jpeg_error_mgr           derr;
  struct jpeg_error_mgr           cerr;

  struct cdjpeg_progress_mgr      progress;

  cjpeg_source_ptr                src_mgr;
  djpeg_dest_ptr                  dest_mgr;
  /* end of ijg*/
} xjpeg;
#if __WIN32__
#pragma pack()
#endif




#if defined __cplusplus
extern "C"
#endif
int32_t xjpeg_file_to_buf(xjpeg* _this, int8_t* fname, int8_t* outbuf, int32_t* len);

#if defined __cplusplus
extern "C"
#endif
int32_t xjpeg_buf_to_file(xjpeg* _this, int8_t* fname, int8_t* input, int32_t len, int32_t fmt);

#if defined __cplusplus
extern "C"
#endif
int32_t xjpeg_buf_to_buf( xjpeg* _this, int8_t* input, int32_t isize, uint8_t* output, int32_t* osize,int32_t fmt);


#if defined __cplusplus
extern "C"
#endif
int32_t new_xjpeg(xjpeg**);

#if defined __cplusplus
extern "C"
#endif
int32_t delete_xjpeg(xjpeg**);

#endif
