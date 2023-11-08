/*****************************************************************************/
/*                                                                           */
/*                           ASE CORE version 1.0                            */
/*                                                                           */
/*****************************************************************************/
/*****************************************************************************/
/*                                                                           */
/*  File Name         : xjpeg.c                                              */
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
#include "xjpeg.h"
//#include "../jpeg-8b/wrbmp.h"

//#pragma comment(lib, "jpeg-8b/lib/libjpeg.lib")


LOCAL(djpeg_dest_ptr)
select_type (j_decompress_ptr dinfo, int32_t fmt)
{
  switch (fmt) {
#ifdef BMP_SUPPORTED
  case FMT_BMP:
    return jinit_write_bmp(dinfo, FALSE);
  case FMT_OS2:
    return jinit_write_bmp(dinfo, TRUE);
#endif
#ifdef GIF_SUPPORTED
  case FMT_GIF:
    return jinit_write_gif(dinfo);
#endif
#ifdef PPM_SUPPORTED
  case FMT_PPM:
    return jinit_write_ppm(dinfo);
#endif
#ifdef RLE_SUPPORTED
  case FMT_RLE:
    return jinit_write_rle(dinfo);
#endif
#ifdef TARGA_SUPPORTED
  case FMT_TARGA:
    return jinit_write_targa(dinfo);
#endif
  default:
    ERREXIT(dinfo, JERR_UNSUPPORTED_FORMAT);
    break;
  }
  return 0;
}

LOCAL(cjpeg_source_ptr)
select_input_type (j_compress_ptr cinfo, int32_t input)
{
  switch (input) {
#ifdef BMP_SUPPORTED
  case 'B':
    return jinit_read_bmp(cinfo);
#endif
#ifdef GIF_SUPPORTED
  case 'G':
    return jinit_read_gif(cinfo);
#endif
#ifdef PPM_SUPPORTED
  case 'P':
    return jinit_read_ppm(cinfo);
#endif
#ifdef RLE_SUPPORTED
  case 'R':
    return jinit_read_rle(cinfo);
#endif
#ifdef TARGA_SUPPORTED
  case 0x00:
    return jinit_read_targa(cinfo);
#endif
  default:
    ERREXIT(cinfo, JERR_UNKNOWN_FORMAT);
    break;
  }

  return NULL;			/* suppress compiler warnings*/
}




static void put_scanline(uint8_t* jpegline, int32_t jpeg_row, int32_t jpeg_width, uint8_t* DIBits, int32_t x0, int32_t y0, int32_t w)
{
   int32_t i_DIBits, i_buffer;
   i_DIBits = ((y0 + jpeg_row)* w + x0)* 4;
   for (i_buffer = 0; i_buffer < jpeg_width* 3; i_buffer += 3) {
      DIBits[i_DIBits++] =*(jpegline + i_buffer + 2);
      DIBits[i_DIBits++] =*(jpegline + i_buffer + 1);
      DIBits[i_DIBits++] =*(jpegline + i_buffer);
      DIBits[i_DIBits++] = 0;
   }
}

static void put_scanline_someplace (JSAMPLE* ba, int32_t row_stride)
{
  static int32_t height;
  int32_t i;

  for (i=0; i < row_stride; i++)
    printf("%d\n", ba[i]);


  printf ("width: %3d height: %3d\n", row_stride, height++);
}

int32_t xjpeg_file_to_buf(xjpeg* _this, int8_t* fname, int8_t* outbuf, int32_t* len)
{
  FILE* fp;
  JDIMENSION lines;
  int32_t input;
  _this->cinfo.err = jpeg_std_error(&_this->cerr);
  jpeg_create_compress(&_this->cinfo);

  _this->cinfo.in_color_space = JCS_RGB; /* arbitrary guess*/
  jpeg_set_defaults(&_this->cinfo);


  fp = fopen(fname, READ_BINARY);

  input = getc(fp);
  ungetc(input, fp);
  _this->src_mgr = select_input_type(&_this->cinfo,input);
  _this->src_mgr->input_file = fp;


  /* Read the input file header to obtain file size & colorspace.*/
  (*_this->src_mgr->start_input) (&_this->cinfo, _this->src_mgr);

  /* Now that we know input colorspace, fix colorspace-dependent defaults*/
  jpeg_default_colorspace(&_this->cinfo);

  /* Specify data destination for compression*/
  jpeg_mem_dest(&_this->cinfo, (uint8_t**)&outbuf, (unsigned long*)len);

  //_this->cinfo.image_width      = xinfo.width;
  //_this->cinfo.image_height     = xinfo.height;
  //_this->cinfo.input_components = 3;
  //_this->cinfo.in_color_space   = JCS_RGB;

  jpeg_set_defaults(&_this->cinfo);
  jpeg_set_quality (&_this->cinfo, 75, 1);


  /* Start compressor*/
  jpeg_start_compress(&_this->cinfo, 1);

  /* Process data*/
  while (_this->cinfo.next_scanline < _this->cinfo.image_height)
  {
    lines = (*_this->src_mgr->get_pixel_rows)(&_this->cinfo, _this->src_mgr);
    (void) jpeg_write_scanlines(&_this->cinfo, _this->src_mgr->buffer, lines);
  }

  /* Finish compression and release memory*/
  (*_this->src_mgr->finish_input) (&_this->cinfo, _this->src_mgr);

  jpeg_finish_compress(&_this->cinfo);

  fclose(fp);


  jpeg_destroy_compress(&_this->cinfo);


  return 0;
}


//// JPEG buf ---> BMP file
int32_t xjpeg_buf_to_file(xjpeg* _this, int8_t* fname, int8_t* input, int32_t len, int32_t fmt)
{
  FILE* fp;
  JDIMENSION lines;

  /* Initialize the JPEG decompression object with default error handling.*/
  _this->dinfo.err = jpeg_std_error(&_this->derr);
  jpeg_create_decompress(&_this->dinfo);

  /* Open the output file.*/
  fp = fopen(fname, WRITE_BINARY);

  /* Specify data source for decompression*/
  jpeg_mem_src(&_this->dinfo, (uint8_t*)input, (unsigned long)len);

  /* Read file header, set default decompression parameters*/
  (void) jpeg_read_header(&_this->dinfo, 1);

  /* Initialize the output module now to let it override any crucial
  * option settings (for instance, GIF wants to force color quantization).
  */
  _this->dest_mgr = select_type(&_this->dinfo, fmt);

  _this->dest_mgr->output_file = fp;

  /* Start decompressor*/
  (void) jpeg_start_decompress(&_this->dinfo);

  /* Write output file header*/
  (*_this->dest_mgr->start_output) (&_this->dinfo, _this->dest_mgr);

  /* Process data*/
  while (_this->dinfo.output_scanline < _this->dinfo.output_height) {
    lines = jpeg_read_scanlines(&_this->dinfo, _this->dest_mgr->buffer,
					_this->dest_mgr->buffer_height);
    (*_this->dest_mgr->put_pixel_rows) (&_this->dinfo, _this->dest_mgr, lines);
  }

  /* Finish decompression and release memory.
  * I must do it in this order because output module has allocated memory
  * of lifespan JPOOL_IMAGE; it needs to finish before releasing memory.
  */
  (*_this->dest_mgr->finish_output) (&_this->dinfo, _this->dest_mgr);
  (void) jpeg_finish_decompress(&_this->dinfo);
  jpeg_destroy_decompress(&_this->dinfo);

  fclose(fp);
  return 0;
}



//
//typedef struct {
//  struct djpeg_dest_struct pub;	/* public fields*/
//
//  boolean is_os2;		/* saves the OS2 format request flag*/
//
//  jvirt_sarray_ptr whole_image;	/* needed to reverse row order*/
//  JDIMENSION data_width;	/* JSAMPLEs per row*/
//  JDIMENSION row_width;		/* physical width of one row in the BMP file*/
//  int32_t pad_bytes;		/* number of padding bytes needed per row*/
//  JDIMENSION cur_output_row;	/* next row# to write to virtual array*/
//} bmp_dest_struct;
//
//typedef bmp_dest_struct* bmp_dest_ptr;
//
//METHODDEF(void)
//put_pixel_rows (j_decompress_ptr cinfo, djpeg_dest_ptr dinfo,
//		JDIMENSION rows_supplied)
///* This version is for writing 24-bit pixels*/
//{
//  bmp_dest_ptr dest = (bmp_dest_ptr) dinfo;
//  JSAMPARRAY image_ptr;
//  register JSAMPROW inptr, outptr;
//  register JDIMENSION col;
//  int32_t pad;
//
//  /* Access next row in virtual array*/
//  image_ptr = (*cinfo->mem->access_virt_sarray)
//    ((j_common_ptr) cinfo, dest->whole_image,
//     dest->cur_output_row, (JDIMENSION) 1, TRUE);
//  dest->cur_output_row++;
//
//  /* Transfer data.  Note destination values must be in BGR order
//  * (even though Microsoft's own documents say the opposite).
//  */
//  inptr = dest->pub.buffer[0];
//  outptr = image_ptr[0];    
//    outptr[2] =*inptr++;	/* can omit GETJSAMPLE() safely*/
//    outptr[1] =*inptr++;
//    outptr[0] =*inptr++;
//    outptr += 3;
//  }
//
//  /* Zero out the pad bytes.*/
//  pad = dest->pad_bytes;
//  while (--pad >= 0)
//   *outptr++ = 0; 
//}

/// JPEG buf ---> BMP buf
int32_t xjpeg_buf_to_buf( xjpeg* _this, int8_t* input, int32_t isize, uint8_t* output, int32_t* osize,int32_t fmt)
{
  JDIMENSION lines;
  int32_t        row_stride;
  JSAMPARRAY buffer;		/* Output row buffer*/
  int32_t i;
  uint32_t  pix;
  //bmp_dest_ptr  dest;


  _this->dinfo.err = jpeg_std_error(&_this->derr);
  jpeg_create_decompress(&_this->dinfo);


  jpeg_mem_src(&_this->dinfo, (uint8_t*)input, (unsigned long)isize);
  (void) jpeg_read_header(&_this->dinfo, 1);
  _this->dest_mgr = select_type(&_this->dinfo, fmt);
  _this->dest_mgr->output_file = 0;
  _this->dest_mgr->output_buf = (output);

  //dest = (bmp_dest_ptr) _this->dest_mgr;
  //dest->bmp = output;
  (*_this->dest_mgr->start_output) (&_this->dinfo, (djpeg_dest_ptr)_this->dest_mgr);

  (void) jpeg_start_decompress(&_this->dinfo);

  //*: = _this->dinfo.output_height*_this->dinfo.output_width*4;
  /* Process data*/
  while (_this->dinfo.output_scanline < _this->dinfo.output_height)
  {
    lines = jpeg_read_scanlines(&_this->dinfo, _this->dest_mgr->buffer,
					_this->dest_mgr->buffer_height);
    (*_this->dest_mgr->put_pixel_rows) (&_this->dinfo, (djpeg_dest_ptr)_this->dest_mgr, lines);
  }

  (*_this->dest_mgr->finish_output) (&_this->dinfo, (djpeg_dest_ptr)_this->dest_mgr);

  (void) jpeg_finish_decompress(&_this->dinfo);
  jpeg_destroy_decompress(&_this->dinfo);

  return 0;
}


int32_t new_xjpeg(xjpeg** pp_xjpeg)
{
  *pp_xjpeg = (xjpeg*)calloc(1, sizeof(xjpeg));
  //(*pp_xjpeg)->vtbl = (xjpegvtbl*)calloc(1, sizeof(xjpegvtbl));

  //(*pp_xjpeg)->vtbl->file_to_buf     = xjpeg_file_to_buf;
  //(*pp_xjpeg)->vtbl->buf_to_file     = xjpeg_buf_to_file;
  //(*pp_xjpeg)->vtbl->buf_to_buf      = xjpeg_buf_to_buf;

  return 0;
}

int32_t delete_xjpeg(xjpeg** pp_xjpeg)
{
  //free((*pp_xjpeg)->vtbl);
  free(*pp_xjpeg);
  return 0;
}

