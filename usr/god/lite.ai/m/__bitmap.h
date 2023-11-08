#ifndef __BITMAP_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__
#define __BITMAP_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>


int32_t get_pixel_single(int8_t* fn, int8_t* pif, uint8_t* p, uint8_t* o);
int32_t get_bmp_hdr(void* fp, uint8_t* p, uint32_t* h);
int32_t get_pixel(void* fp, int8_t* pif, uint32_t* h, uint8_t* o);
int32_t get_bmp_pixel(int8_t* fn, int8_t* pif, void* (*f)(int32_t, int32_t, int32_t), uint8_t* o);
int32_t get_bitmap(int8_t* img, int8_t* bmphdr, int8_t* dibhdr, int8_t** raw);
int32_t set_bitmap(int8_t* img, int8_t* bmphdr, int8_t* dibhdr, int8_t* raw);
int32_t write_bitmap(int8_t* fn, int8_t* wh, int8_t bcnt, int8_t* raw);
int32_t mosaic(int8_t* img, int8_t* hdr, int32_t x, int32_t y, int32_t w, int32_t h, int8_t** raw);
int32_t pick_mosaic_bitmap(int8_t* src, int32_t x, int32_t y, int32_t w, int32_t h, int8_t** dst);


#if defined __cplusplus
extern "C"
#endif
int32_t read_raw(int8_t* bmp, int32_t* xy, int32_t* wh, int8_t** raw);


#if defined __cplusplus
extern "C"
#endif
int32_t write_raw(int8_t* raw, int32_t* wh, int32_t bcnt, int8_t* bmp);


#if defined __cplusplus
extern "C"
#endif
int32_t rread_raw(int8_t* bmp, int32_t* xy, int32_t* wh, int8_t** raw);


#if defined __cplusplus
extern "C"
#endif
int32_t pick_pixel(int8_t* bmp, int32_t* xy, int8_t** raw);



#if defined __cplusplus
extern "C"
#endif
int32_t write_raw(int8_t* raw, int32_t* wh, int32_t bcnt, int8_t* bmp);


#if defined __cplusplus
extern "C"
#endif
int32_t write_raw_bitmap(int8_t* raw, int32_t* wh, int32_t bcnt, int8_t* bmp);


#if defined __cplusplus
extern "C"
#endif
int32_t rwrite_raw_bitmap(int8_t* raw, int32_t* wh, int32_t bcnt, int8_t* bmp);


#if defined __cplusplus
extern "C"
#endif
int32_t __serialize_bitmap(int8_t* bmp, int32_t *wh, int32_t bcnt, int32_t padding, uint8_t* seq, int8_t* raw);


#if defined __cplusplus
extern "C"
#endif
int32_t __padding_size(int32_t* wh, int32_t bcnt, int32_t padding);

#endif