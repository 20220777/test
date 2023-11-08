/*****************************************************************************/
/*                                                                           */
/*            NCLab (Networked Control Lab) CORE version 1.0                 */
/*                                                                           */
/*****************************************************************************/
/*****************************************************************************/
/*                                                                           */
/*  File Name         : xcommon.h                                            */
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
#ifndef __XCOMMON_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__
#define __XCOMMON_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__

#include <common.h>
#if __uCHIP__
#endif
#if __LINUX__
#endif
#if __WIN32__
#include <tchar.h>
#endif



#if defined __cplusplus
extern "C"
#endif
int32_t __check_key(int8_t* key);



#if defined __cplusplus
extern "C"
#endif
uint8_t __check_sys_arch(uint32_t a);



#if defined __cplusplus
extern "C"
#endif
int32_t __base64_decode(int8_t* text, int32_t sz, int8_t* out);



#if defined __cplusplus
extern "C"
#endif
int32_t __base64_encode(int8_t* text, int32_t sz, int8_t* out);



#if defined __cplusplus
extern "C"
#endif
int32_t __urldecode(uint8_t *source, uint8_t *dest);



#if defined __cplusplus
extern "C"
#endif
int32_t __urlencode(uint8_t *source, uint8_t *dest);



#if defined __cplusplus
extern "C"
#endif
int32_t __get_trimstr(int8_t* str, int8_t pfx, int8_t sfx, int8_t* output);



#if defined __cplusplus
extern "C"
#endif
int32_t __get_dlmtr_str(int8_t* str, int8_t dlmtr, int32_t idx, int8_t* out);



#if defined __cplusplus
extern "C"
#endif
int32_t __compare_str(int8_t* src, int8_t* dst, int32_t sz);



#if defined __cplusplus
extern "C"
#endif
int32_t __replace_str(int8_t* str, int8_t from, int8_t to);



#if defined __cplusplus
extern "C"
#endif
int32_t __remove_token(int8_t* str, int8_t tkn, int8_t* out);



#if defined __cplusplus
extern "C"
#endif
int32_t __change_seq(int8_t* str, int32_t pos, int32_t sz, int8_t* out);



#if defined __cplusplus
extern "C"
#endif
int32_t __change_token(int8_t* str, int8_t o, int8_t n, int8_t* out);



#if defined __cplusplus
extern "C"
#endif
int32_t __get_url(int8_t* url, int8_t* host, int8_t* sub);



#if defined __cplusplus
extern "C"
#endif
int32_t __get_lastindex(int8_t* str, int8_t tok);



#if defined __cplusplus
extern "C"
#endif
int32_t __get_firstindex(int8_t* str, int8_t tok);



#if defined __cplusplus
extern "C"
#endif
int32_t __get_token_count(int8_t* str, int8_t dlmtr);



#if defined __cplusplus
extern "C"
#endif
int32_t __str_to_uppercase(int8_t* str);



#if defined __cplusplus
extern "C"
#endif
int32_t __str_to_lowercase(int8_t* str);



#if defined __cplusplus
extern "C"
#endif
int32_t __truncate_str(int8_t* str, int32_t index);



#if defined __cplusplus
extern "C"
#endif
int32_t __get_str_pos(int8_t* msg, int32_t size, int8_t* pfx, int32_t sz, int32_t* pos);



#if defined __cplusplus
extern "C"
#endif
long double ____factorial(long double x);



#if defined __cplusplus
extern "C"
#endif
long double ____pow(long double x, long double n);



#if defined __cplusplus
extern "C"
#endif
long double ____round(long double p, int32_t n);



#if defined __cplusplus
extern "C"
#endif
int8_t* __format_change(int8_t* src, int8_t* format, int8_t* out);



#if defined __cplusplus
extern "C"
#endif
int32_t __get_ini_value(int8_t*, int8_t*, int8_t*, int8_t*);



#if defined __cplusplus
extern "C"
#endif
int32_t __get_filename(int8_t* fname, int8_t* output);



#if defined __cplusplus
extern "C"
#endif
void __get_fileext(int8_t* fname, int8_t* output);



#if defined __cplusplus
extern "C"
#endif
void __get_filename_only(int8_t* fname, int8_t* output);



#if defined __cplusplus
extern "C"
#endif
int32_t __get_prefix(int8_t* path);



#if defined __cplusplus
extern "C"
#endif
int32_t __get_file_size(int8_t* fname);



#if defined __cplusplus
extern "C"
#endif
int32_t __get_file_buffer(int8_t* fname, int32_t offset, int32_t size, int8_t* out);



#if defined __cplusplus
extern "C"
#endif
int32_t __remove_file(int8_t* fname);



#if defined __cplusplus
extern "C"
#endif
int32_t __set_file_contents(int8_t* fname, int32_t offset, int8_t* str, int32_t sz);



#if defined __cplusplus
extern "C"
#endif
int32_t __open_file_dialog(void* hwnd, int8_t* fname, int8_t* ext);



#if defined __cplusplus
extern "C"
#endif
int32_t __save_file_dialog(void* hwnd, int8_t* fname, int8_t* ext);



#if defined __cplusplus
extern "C"
#endif
int32_t __getpid(int8_t* pname, int32_t* pid);



#if defined __cplusplus
extern "C"
#endif
int32_t __create_dir(int8_t* dname);



#if defined __cplusplus
extern "C"
#endif
int32_t __remove_dir(int8_t* dname);



#if defined __cplusplus
extern "C"
#endif
int32_t __get_files(int8_t* dname, uint8_t* mode, uint8_t* list, int32_t* count);



#if defined __cplusplus
extern "C"
#endif
int32_t __get_bit_semaphore(uint32_t* id, int32_t idx, uint8_t v, int32_t msec);



#if defined __cplusplus
extern "C"
#endif
int32_t __set_bit_semaphore(uint32_t* id, int32_t idx, uint8_t v);



#if defined __cplusplus
extern "C"
#endif
int32_t __get_hex_semaphore(uint32_t* id, uint32_t h, uint32_t v, int32_t msec);



#if defined __cplusplus
extern "C"
#endif
int32_t __set_hex_semaphore(uint32_t* id, uint32_t h, uint32_t v);



#if defined __cplusplus
extern "C"
#endif
int32_t __check_hex_semaphore(uint32_t* id, uint32_t h, uint32_t v);



#if defined __cplusplus
extern "C"
#endif
int32_t __get_semaphore(int32_t msec, uint8_t* id);



#if defined __cplusplus
extern "C"
#endif
int32_t __set_semaphore(uint8_t* id);



#if defined __cplusplus
extern "C"
#endif
int32_t __signal_post(int32_t pid, int32_t sid, void* arg);



#if defined __cplusplus
extern "C"
#endif
int32_t __signal_peek(int32_t msec, int32_t sid, void** output);



#if defined __cplusplus
extern "C"
#endif
void* __get_thread_id();



#if defined __cplusplus
extern "C"
#endif
int32_t __get_thread_status(int32_t msec, int32_t sid, void** arg);



#if defined __cplusplus
extern "C"
#endif
void* __thread_detach(void* id);



#if defined __cplusplus
extern "C"
#endif
void* __thread_create(void* (*f)(void*),void* arg, void* id);



#if defined __cplusplus
extern "C"
#endif
int32_t __set_thread_priority(void* hdl, int32_t priority);



#if defined __cplusplus
extern "C"
#endif
int32_t __get_thread_priority(void* hdl);



#if defined __cplusplus
extern "C"
#endif
int32_t __thread_destroy(int32_t sid, void* id, void* arg);



#if defined __cplusplus
extern "C"
#endif
int32_t __thread_terminate(void* hdl);



#if defined __cplusplus
extern "C"
#endif
void __thread_exit(int32_t sid, void* id);



#if defined __cplusplus
extern "C"
#endif
int32_t __set_event(void** hdl);



#if defined __cplusplus
extern "C"
#endif
int32_t __wait_event(void** hdl, int32_t msec);



#if defined __cplusplus
extern "C"
#endif
int32_t __create_event(void** hdl);



#if defined __cplusplus
extern "C"
#endif
int32_t __destroy_event(void** hdl);



#if defined __cplusplus
extern "C"
#endif
int32_t __lock_init(void* crit);



#if defined __cplusplus
extern "C"
#endif
int32_t __lock_final(void* crit);



#if defined __cplusplus
extern "C"
#endif
int32_t __lock(void* crit);



#if defined __cplusplus
extern "C"
#endif
int32_t __unlock(void* crit);



#if defined __cplusplus
extern "C"
#endif
time_t __system_time(time_t*inTT);



#if defined __cplusplus
extern "C"
#endif
int32_t __noiz();



#if defined __cplusplus
extern "C"
#endif
int32_t __mcsleep(uint64_t msec);



#if defined __cplusplus
extern "C"
#endif
#if __LINUX__
int32_t __set_timer(void* hwnd, int32_t id, int32_t msec, void (*f)(int32_t));
#endif
#if __WIN32__
int32_t __set_timer(void* hwnd, int32_t id, int32_t msec, void* (*f)(void*, int32_t, int32_t, int32_t));
#endif



#if defined __cplusplus
extern "C"
#endif
int32_t __kill_timer(void* hwnd, int32_t id);



#if defined __cplusplus
extern "C"
#endif
int64_t __get_digit_count(int64_t n);



#if defined __cplusplus
extern "C"
#endif
double __get_freq_counter(void*);



#if defined __cplusplus
extern "C"
#endif
double __get_freq(void*);



#if defined __cplusplus
extern "C"
#endif
long double __check_freq(void*, void*);



#if defined __cplusplus
extern "C"
#endif
void __usleep(long double us);



#if defined __cplusplus
extern "C"
#endif
int8_t* __get_curr_time(int8_t*p, int8_t* arg0, int8_t* arg1, int8_t* arg2, int8_t* arg3, int32_t* YY, int32_t* MM, int32_t* DD, int32_t* hh, int32_t* mm, int32_t* ss, int32_t* us);


#if defined __cplusplus
extern "C"
#endif
int8_t* __get_gmtime(void* tm, int8_t* s);



#if defined __cplusplus
extern "C"
#endif
int32_t __get_log_name(int8_t* pattern, int8_t* fname);



#if defined __cplusplus
extern "C"
#endif
uint32_t __get_compile_date();



#if defined __cplusplus
extern "C"
#endif
int32_t __log_write(uint32_t mode, FILE* fp, const int8_t* fmt, ...);



#if defined __cplusplus
extern "C"
#endif
int32_t __log_printf(FILE*, const int8_t* fmt, ...);



#if defined __cplusplus
extern "C"
#endif
void __display_buffer(int8_t* pre, int8_t* buffer, int32_t sz);



#if defined __cplusplus
extern "C"
#endif
int32_t __fprint_buffer(int8_t* pre, int8_t* buffer, int32_t sz, int8_t* output, int32_t dcnt);



#if defined __cplusplus
extern "C"
#endif
int32_t __fprint_raw_buffer(int8_t* pfx, int8_t* buffer, int32_t sz, int8_t* out);



#if defined __cplusplus
extern "C"
#endif
void __dump_buffer(int8_t* pre, int8_t* buffer, int32_t sz, int8_t* output);



#if defined __cplusplus
extern "C"
#endif
void __fprintf_buffer(int8_t* buffer, int32_t sz, int8_t* output, int32_t dcnt,const int8_t* fmt,...);



#if defined __cplusplus
extern "C"
#endif
void __xfprintf(int8_t* msg,const int8_t* fmt,...);



#if defined __cplusplus
extern "C"
#endif
int32_t __check_path(int8_t* path);



#if defined __cplusplus
extern "C"
#endif
int32_t __make_log(int8_t* path, int8_t* log, uint8_t chk);



#if defined __cplusplus
extern "C"
#endif
int32_t __get_last_days(int32_t YY, int32_t* marr);



#if defined __cplusplus
extern "C"
#endif
int32_t __remove_path(int8_t* path, uint32_t mode, int8_t* out, int32_t* YY, int32_t* MM, int32_t* DD, int32_t* hh, int32_t* mm, int32_t* ss, int32_t* us);



#if defined __cplusplus
extern "C"
#endif
void* __log_write_ex(int8_t* ppath, int8_t* fname, int8_t* pfname, void** pfp, int8_t* pfx, uint32_t mode, const int8_t* fmt, ...);



#if defined __cplusplus
extern "C"
#endif
uint8_t __get_shift_count(uint32_t v);



#if defined __cplusplus
extern "C"
#endif
int32_t __get_padd(int32_t n, int32_t m);



#if defined __cplusplus
extern "C"
#endif
void __to_binary(int32_t n, int8_t* r);



#if defined __cplusplus
extern "C"
#endif
int32_t __digit_to_bin(int32_t val, int8_t* out, int32_t* sz);



#if defined __cplusplus
extern "C"
#endif
int32_t __digit_to_bin_buffer(int32_t val, int8_t* out);



#if defined __cplusplus
extern "C"
#endif
int32_t __to_bit(int8_t* str, int32_t sz, int8_t* mode, void* (*f)(int32_t, uint8_t));



#if defined __cplusplus
extern "C"
#endif
int32_t __str_to_bin(int8_t* val, int32_t sz,  int8_t* out);



#if defined __cplusplus
extern "C"
#endif
int32_t __str_to_bin_buffer(int8_t* val, int8_t* out);



#if defined __cplusplus
extern "C"
#endif
int32_t __hex_to_decimal(int8_t* h, int32_t sz);



#if defined __cplusplus
extern "C"
#endif
int32_t __hex_to_digit(int8_t* h);



#if defined __cplusplus
extern "C"
#endif
float __hex_to_float(uint32_t);



#if defined __cplusplus
extern "C"
#endif
int32_t __str_to_hex(int8_t*, int32_t, int8_t, int8_t*);



#if defined __cplusplus
extern "C"
#endif
int32_t __string_to_hex(uint8_t* src, uint8_t* dst);



#if defined __cplusplus
extern "C"
#endif
uint8_t __asc_to_hex(uint8_t* asc);



#if defined __cplusplus
extern "C"
#endif
float __format_convert(float i, int32_t dgt, uint8_t rnd);



#if defined __cplusplus
extern "C"
#endif
int32_t __get_float_digit(float i);



#if defined __cplusplus
extern "C"
#endif
int32_t __ascii_to_hex(uint8_t asc);



#if defined __cplusplus
extern "C"
#endif
int32_t __ascii_to_decimal(uint8_t asc);



#if defined __cplusplus
extern "C"
#endif
int32_t __str_to_decimal(uint8_t* s);



#if defined __cplusplus
extern "C"
#endif
int32_t __ascii_to_unicode(int8_t*, int32_t, int8_t*);



#if defined __cplusplus
extern "C"
#endif
int32_t __unicode_to_ascii(int8_t*, int32_t, int8_t*);



#if defined __cplusplus
extern "C"
#endif
int32_t version(int8_t** version);



#if defined __cplusplus
extern "C"
#endif
int32_t __check_expire_date(int32_t date,int32_t creation,int32_t expire);



#if defined __cplusplus
extern "C"
#endif
int32_t __get_os_version(int8_t** version);


#if defined __cplusplus
extern "C"
#endif
#if __WIN32__
HKEY __reg_open(HKEY key, int8_t* subkey);
#endif


#if defined __cplusplus
extern "C"
#endif
#if __WIN32__
void __reg_close(HKEY key);
#endif


#if defined __cplusplus
extern "C"
#endif
#if __WIN32__
int32_t __reg_write(HKEY key, int8_t* subkey, int8_t* name, int8_t* value, int32_t type, int32_t size);
#endif


#if defined __cplusplus
extern "C"
#endif
#if __WIN32__
int32_t __reg_read(HKEY key, int8_t* subkey, int8_t* name, int8_t* value, int32_t* type, int32_t* size);
#endif



#if defined __cplusplus
extern "C"
#endif
#if __WIN32__
int32_t __reg_delete(HKEY key, int8_t* subkey, int8_t* name);
#endif



#if defined __cplusplus
extern "C"
#endif




#if defined __cplusplus
extern "C"
#endif
int8_t* __get_version(int8_t* file_name, int8_t* query);



#if defined __cplusplus
extern "C"
#endif
void __on_sys_center(void* hwnd);



#if defined __cplusplus
extern "C"
#endif
void __on_wnd_center(void* prnt, void* chld);



#if defined __cplusplus
extern "C"
#endif
void __on_center(void* prnt, void* chld);



#if defined __cplusplus
extern "C"
#endif
void __on_full_screen(void* hwnd);



#if defined __cplusplus
extern "C"
#endif
int32_t __get_hostip(int8_t* host, int8_t* ip);



#if defined __cplusplus
extern "C"
#endif
int32_t __get_devip(int8_t* dev, int8_t* ip, uint8_t* mac);



#if defined __cplusplus
extern "C"
#endif
int32_t __get_pause(int8_t* str);



#if defined __cplusplus
extern "C"
#endif
int32_t __get_protocol(int8_t* hdr, int8_t*desc);



#if defined __cplusplus
extern "C"
#endif
int32_t __get_port(int8_t* hdr, int32_t* src, int32_t* dst);



#if defined __cplusplus
extern "C"
#endif
int32_t __get_ip(int8_t* hdr, int32_t* src, int32_t* dst);



#if defined __cplusplus
extern "C"
#endif
int32_t __ip_to_str(int32_t ip, int8_t* str);



#if defined __cplusplus
extern "C"
#endif
int32_t __str_to_ip(int8_t* str, int32_t* ip);



#if defined __cplusplus
extern "C"
#endif
int32_t __get_adapter_info(int8_t* dev, int8_t* out, uint32_t f);



#if defined __cplusplus
extern "C"
#endif
uint16_t __check_sum(uint16_t*header, int32_t sz);



#if defined __cplusplus
extern "C"
#endif
int32_t __set_ipv4_hdr(int8_t* hdr, int32_t sz, int32_t id, int32_t protocol, int32_t src, int32_t dst);



#if defined __cplusplus
extern "C"
#endif
int32_t __display_ipv4_hdr(int8_t* hdr);



#if defined __cplusplus
extern "C"
#endif
int32_t __display_tcp_hdr(int8_t* hdr);



#if defined __cplusplus
extern "C"
#endif
int32_t __display_udp_hdr(int8_t* hdr);



#if defined __cplusplus
extern "C"
#endif
int32_t __get_pixel_single(int8_t* fn, int8_t* pif, uint8_t* p, uint8_t* o);


// h ->   ofst, wdth, hght, bcnt
#if defined __cplusplus
extern "C"
#endif
int32_t __get_bmp_hdr(void* fp, uint8_t* p, uint32_t* h);


// h ->   ofst, wdth, hght, bcnt
#if defined __cplusplus
extern "C"
#endif
int32_t __get_pixel(void* fp, int8_t* pif, uint32_t* h, uint8_t* o);



#if defined __cplusplus
extern "C"
#endif
int32_t __get_bmp_pixel(int8_t* fn, int8_t* pif, void* (*f)(int32_t,int32_t,int32_t), uint8_t* o);



#if defined __cplusplus
extern "C"
#endif
int32_t __get_bitmap(int8_t* img, int8_t* bmphdr, int8_t* dibhdr, int8_t** raw);



#if defined __cplusplus
extern "C"
#endif
int32_t __set_bitmap(int8_t* img, int8_t* bmphdr, int8_t* dibhdr, int8_t* raw);



#if defined __cplusplus
extern "C"
#endif
int32_t __write_bitmap(int8_t* fn, int8_t* wh, int8_t bcnt, int8_t* raw);



#if defined __cplusplus
extern "C"
#endif
int32_t __get_mosaic(int8_t* img, int8_t* hdr, int32_t x, int32_t y, int32_t w, int32_t h, int8_t** raw);



#if defined __cplusplus
extern "C"
#endif
int32_t __get_mosaic_image(int8_t* src, int32_t x, int32_t y, int32_t w, int32_t h, int8_t** dst);



#if defined __cplusplus
extern "C"
#endif
int32_t __lookup_filepath(int8_t* fname, int8_t* path);






/***
mode
+-+-+-+-+ +-+-+-+-+
+-+-+-+-+ +-+-+-+-+
 ^ ^ ^ ^   ^
 | | | |   |
 | | | |   +----------- TITLE
 | | | +--------------- TIME
 | | +----------------- DAY
 | +------------------- MONTH
 +--------------------- YEAR
***/

#if __LINUX__
#define	LOG_TIME(x,title,buf)              \
if ( x&0xF8 )                              \
{                                          \
	if ( buf )                               \
    if ( title )                           \
		  sprintf(buf,"|%s|%.8s|",             \
						  __get_curr_time(buf,           \
												  x&0x80?"/":0,    \
												  x&0x40?"/":0,    \
												  x&0x20?" ":0,    \
												  x&0x10?":":0,    \
											    0,0,0,0,0,0,0),  \
												  title);          \
    else                                   \
		  sprintf(buf,"|%s|",                  \
						  __get_curr_time(buf,           \
												  x&0x80?"/":0,    \
												  x&0x40?"/":0,    \
												  x&0x20?" ":0,    \
												  x&0x10?":":0,    \
											    0,0,0,0,0,0,0)); \
	else                                     \
  {                                        \
    int8_t tm[32];                         \
    if ( title )                           \
		  fprintf(stderr,"|%s|%.8s|",          \
						  __get_curr_time(tm,            \
												  x&0x80?"/":0,    \
												  x&0x40?"/":0,    \
												  x&0x20?" ":0,    \
												  x&0x10?":":0,    \
											    0,0,0,0,0,0,0),  \
												  title);          \
    else                                   \
		  fprintf(stderr,"|%s|",               \
						  __get_curr_time(tm,            \
												  x&0x80?"/":0,    \
												  x&0x40?"/":0,    \
												  x&0x20?" ":0,    \
												  x&0x10?":":0,    \
											    0,0,0,0,0,0,0)); \
  }                                        \
}
#endif

#if __WIN32__
#define	LOG_TIME(x,title,buf)
#endif

#if __WIN32__
#define bprintf(a,b,c,...)     __fprintf_buffer(a,b,0,16,c,__VA_ARGS__)
#endif

#if __LINUX__
#define bprintf(a,b,c,d...)     __fprintf_buffer(a,b,0,16,c,##d)
#endif
#define tohex(a,b)           __string_to_hex(a,b)

#define TO_BIN(a,b)          (((uint8_t)a)&&(1<<b))




#define ctod(x)   ((x==0)?0:(x-0x30))
#define dtoc(x)   (x+0x30)


#if defined __cplusplus
extern "C"
#endif
long double __sinus(long double arg, int32_t quad);


#if defined __cplusplus
extern "C"
#endif
long double __cosx(long double x);


#if defined __cplusplus
extern "C"
#endif
long double __sinx(long double x);


#if defined __cplusplus
extern "C"
#endif
long double __tanx(long double x);



/****
@param n: input numbers.
@param sz: number of n
@return: number of result
****/
#if defined __cplusplus
extern "C"
#endif
int64_t __sort_numbers_gt(int64_t* n, int64_t sz);

/****
@param n: input numbers.
@param sz: number of n
@return: number of result
****/
#if defined __cplusplus
extern "C"
#endif
int64_t __sort_numbers_lt(int64_t* n, int64_t sz);

/****
@param p: input number
@return: 0:composite number,  1:prime number
****/
#if defined __cplusplus
extern "C"
#endif
int64_t __is_prime(int64_t p);

/****
@param p: input numbers.   p[0],   p[1]
@param ps: output prime number set
@param count: input request count
@return: number of result
****/
#if defined __cplusplus
extern "C"
#endif
int64_t __get_prime_set(int64_t* p, int64_t* ps, int64_t count);

/****
@param p: input number.   p
@param ps: output prime number set less than p
@param count: input request count
@return: number of result
****/
#if defined __cplusplus
extern "C"
#endif
int64_t __get_prime_lt(int64_t p, int64_t* ps, int64_t count);

/****
@param p: input number.   p
@param ps: output prime number set greater than p
@param count: input request count
@return: number of result
****/
#if defined __cplusplus
extern "C"
#endif
int64_t __get_prime_gt(int64_t p, int64_t* ps, int64_t count);

/****
@param p: input number.   p
@param ps: input prime number set
@param sz: input request count
@param rs: output result set
@return: number of result
****/
#if defined __cplusplus
extern "C"
#endif
int64_t __get_prime_factor_set(int64_t p, int64_t* ps, int64_t sz, int64_t* rs);


/****
@param n: input, number set
@param p: output, prime factors
@return: number of ps
****/
#if defined __cplusplus
extern "C"
#endif
int64_t __prime_factoring(int64_t* n, int64_t* p);

/****
@param n: input, number set
@param ps: output, prime set ->  (basenumber, expvalue), (basenumber, expvalue), 
@param p: input temporary
@return: number of ps
****/
#if defined __cplusplus
extern "C"
#endif
int64_t __prime_factoring_ex(int64_t* n, int64_t* ps, int64_t* p);


/****
@param p: input, number
@param rs: output, prime set
@return: number of rs
****/
#if defined __cplusplus
extern "C"
#endif
int64_t __get_prime_factors(int64_t p, int64_t* rs);


/****
@param p: input, number
@param rs: output, prime set
@return: number of rs
****/
#if defined __cplusplus
extern "C"
#endif
int64_t __get_prime_factoring(int64_t p, int64_t* rs);


/****
@param p: input, number  p[0]
@return: next prime number
****/
#if defined __cplusplus
extern "C"
#endif
int64_t __get_next_prime(int64_t* p);


/****
@param p: input, number  p[0]
@return: previous prime number
****/
#if defined __cplusplus
extern "C"
#endif
int64_t __get_prev_prime(int64_t* p);


//#if defined __cplusplus
//extern "C"
//#endif
//#if __WIN32__
//#if __IO_EXPORT__
//__declspec(dllexport)
//#endif
//#endif
//int64_t get_gcd_lcm(int64_t* ns, int64_t* rs, int64_t* rc, uint8_t mode);
//
//
//#if defined __cplusplus
//extern "C"
//#endif
//#if __WIN32__
//#if __IO_EXPORT__
//__declspec(dllexport)
//#endif
//#endif
//int64_t __get_common_divisor(int64_t n, int64_t* cd);

/****
@param n: input, number
@param p: output, factor set
@return: number of factor set
****/
#if defined __cplusplus
extern "C"
#endif
int64_t __get_divisor(int64_t n, int64_t* p);

/****
@param n: input, number set
@param p: output, common factor set
@param gl: output, gl[0]:GCM, gl[1]:LCD
@return: number of common factor set
****/
#if defined __cplusplus
extern "C"
#endif
int64_t __get_common_divisor(int64_t* n, int64_t* p, int64_t* gl);


/****
@param ps: input, number set
@param rs: output, result set
@return: 0:FALSE, 1:TRUE
****/
#if defined __cplusplus
extern "C"
#endif
int64_t __is_coprime(int64_t* ps, int64_t* rs);

#if defined __cplusplus
extern "C"
#endif
int64_t __get_coprimes(int64_t* ps, int64_t* t, int64_t count, int64_t* q);

#if defined __cplusplus
extern "C"
#endif
int64_t __get_coprimes_gt(int64_t* ps, int64_t* t, int64_t count, int64_t* q);

#if defined __cplusplus
extern "C"
#endif
int64_t __get_coprimes_lt(int64_t* ps, int64_t* t, int64_t count, int64_t* q);

#if defined __cplusplus
extern "C"
#endif
int64_t __euclid(int64_t* n, int64_t* q);

/****
@param n: input numbers.
@param euc: __euclid factors ---> [][2]
@return: number of euc
****/
#if defined __cplusplus
extern "C"
#endif
int64_t __euclidex(int64_t* q, int64_t* euc);


#if defined __cplusplus
extern "C"
#endif
uint64_t __get_exp(int64_t b, int64_t exp, int64_t m);


#if defined __cplusplus
extern "C"
#endif
int64_t __str_to_long(int8_t* str, int32_t sz);


#if defined __cplusplus
extern "C"
#endif
int64_t __check_perfect_number(int64_t n, int64_t* pn);


#if defined __cplusplus
extern "C"
#endif
int64_t __euler(int64_t* n, int64_t* pv, int64_t* pf);


#if defined __cplusplus
extern "C"
#endif
int64_t __is_mersenne_prime(int64_t p);


#if defined __cplusplus
extern "C"
#endif
int64_t __get_max_size(int8_t** n);


#if defined __cplusplus
extern "C"
#endif
int32_t __get_array_count(int8_t** n);


#if defined __cplusplus
extern "C"
#endif
int32_t __dalign(int8_t** n, int32_t c, int8_t** r, int32_t sz);


#if defined __cplusplus
extern "C"
#endif
int32_t __dcmpswitch(int8_t** p, int32_t* idx);


#if defined __cplusplus
extern "C"
#endif
int64_t __rsa_encode(int8_t m, int64_t key, int64_t mod);


#if defined __cplusplus
extern "C"
#endif
int64_t __rsa_decode(int64_t cipher, int64_t key, int64_t mod);


#if defined __cplusplus
extern "C"
#endif
int64_t __rsa_encode_stream(int8_t* m, int64_t sz, int64_t key, int64_t mod, void*(*f)(int8_t*, int64_t, int64_t, uint64_t*), int8_t* o);


#if defined __cplusplus
extern "C"
#endif
int64_t __rsa_decode_stream(int8_t* m, int64_t sz, int64_t key, int64_t mod, void*(*f)(int8_t*, int64_t, int64_t, uint64_t*), int8_t* o);


#if defined __cplusplus
extern "C"
#endif
int8_t* __xplus(int8_t** n, int8_t* out, int8_t** p);


#if defined __cplusplus
extern "C"
#endif
int8_t* __xminus(int8_t** n, int8_t* out, int8_t** p);


#if defined __cplusplus
extern "C"
#endif
int8_t* __xmultiple(int8_t** n, int8_t* out, int8_t** p);


#if defined __cplusplus
extern "C"
#endif
int8_t* __xdevide(int8_t** n, int8_t* out, int8_t* q, int8_t* r, int8_t** p, int8_t** pp);


#if defined __cplusplus
extern "C"
#endif
void __init_rand();


#if defined __cplusplus
extern "C"
#endif
long double __get_rand(long double* range);


#if defined __cplusplus
extern "C"
#endif
long double __get_decimal_point(long double a, long double* r);


#if defined __cplusplus
extern "C"
#endif
long double __split_decimal_point(long double o, long double* m, long double* r);


#if defined __cplusplus
extern "C"
#endif
long double __get_square(long double a, long double b);


#if defined __cplusplus
extern "C"
#endif
void __print_matrix(long double* matrix, int64_t* rc, long double mod, int8_t* o, const int8_t* fmt, ...);


#if defined __cplusplus
extern "C"
#endif
void printMatrix(long double* mtrx,int8_t* rc,long double mod,int8_t* o,const int8_t* fmt,...);



/****
super increasing sequence
@param: mod is input, *(mod+0) is seed, *(mod+1) is mod
@param: c is input, c is columns
@param: s is output, result set
@return: sum of s
****/
#if defined __cplusplus
extern "C"
#endif
long double __get_super_inc_seq(long double* mod, int64_t c, long double* s);

#if defined __cplusplus
extern "C"
#endif
long double __get_matrix(long double* mtrx, int64_t* rc,  long double* rng);

#if defined __cplusplus
extern "C"
#endif
long double getMatrix(long double* mtrx, int8_t* rc,  int8_t* rng);

#if defined __cplusplus
extern "C"
#endif
long double __remake_matrix(long double* a, int64_t* arc, long double* s, long double* rng, long double* rmat, long double mod);

/****
super increasing sequence
@param: a is input, matrix K
@param: arc is input, rows and columns of matrix K
@param: s is output, result matrix
@param: rng is input, range of result matrix
@param: mod is input, modulus
@param: o is output, string of result set
@return: sum of s
****/
#if defined __cplusplus
extern "C"
#endif
int64_t __matrix_XO(long double* a, int64_t* arc, long double* s, long double* rng, long double mod, int8_t* o);

/****
super increasing sequence
@param: a is input, matrix K
@param: arc is input, rows and columns of matrix K
@param: s is output, result matrix
@param: rng is input, range of result matrix
@param: mod is input, modulus
@param: o is output, string of result set
@return: sum of s
****/
#if defined __cplusplus
extern "C"
#endif
int64_t MatrixXO(long double* a, int8_t* arc, long double* s, int8_t* rng, long double mod, int8_t* o);

/****
super increasing sequence
@param: a is input, matrix K
@param: arc is input, rows and columns of matrix K
@param: s is output, result matrix
@param: rng is input, range of result matrix
@param: rmat is input, result matrix
@param: mod is input, modulus
@param: o is output, string of result set
@return: sum of s
****/
#if defined __cplusplus
extern "C"
#endif
int64_t __matrix_X(long double* a, int64_t* arc, long double* s, int64_t* src, long double* rng, long double* rmat, long double mod);

/****
super increasing sequence
@param: a is input, matrix K
@param: arc is input, rows and columns of matrix K
@param: s is output, result matrix
@param: rng is input, range of result matrix
@param: rmat is input, result matrix
@param: mod is input, modulus
@param: o is output, string of result set
@return: sum of s
****/
#if defined __cplusplus
extern "C"
#endif
int64_t MatrixX(long double* a, int8_t* arc, long double* s, int8_t* src, int8_t* rng, long double* rmat, long double mod);


#if defined __cplusplus
extern "C"
#endif
int64_t __set_matrix_Xc1(long double* a, int64_t* arc, long double* s, int64_t* src, long double* rng, long double* rmat, long double mod);


#if defined __cplusplus
extern "C"
#endif
int64_t __set_matrix_XcN(long double* a, int64_t* arc);


#if defined __cplusplus
extern "C"
#endif
int64_t __matrix_add(long double* a, long double* b, int64_t* abrc, long double* s);


#if defined __cplusplus
extern "C"
#endif
int64_t __matrix_mul(long double* a, int64_t* arc, long double* b, int64_t* brc, long double* s, int64_t* src);


#if defined __cplusplus
extern "C"
#endif
long double __get_matrix_element(long double* a, int64_t* arc, int64_t* rc);


#if defined __cplusplus
extern "C"
#endif
long double getMatrixElement(long double* a, int8_t* arc, int8_t* rc);


#if defined __cplusplus
extern "C"
#endif
long double __set_matrix_element(long double* a, int64_t* arc, int64_t* rc, long double o);


#if defined __cplusplus
extern "C"
#endif
long double setMatrixElement(long double* a, int8_t* arc, int8_t* rc, long double o);


#if defined __cplusplus
extern "C"
#endif
int64_t __matrix_T(long double* a, int64_t* arc, long double* s, int64_t* src);


#if defined __cplusplus
extern "C"
#endif
int64_t MatrixT(long double* a, int8_t* arc, long double* s, int8_t* src);


#if defined __cplusplus
extern "C"
#endif
int64_t __matrix_adj(long double* a, int64_t* arc, int64_t* rc, long double* s);


#if defined __cplusplus
extern "C"
#endif
int64_t MatrixADJ(long double* a, int8_t* arc, int8_t* rc, long double* s);


#if defined __cplusplus
extern "C"
#endif
long double __matrix_det_e(long double* a, int64_t* arc);


#if defined __cplusplus
extern "C"
#endif
long double __matrix_det(long double* a, int64_t* arc, long double* s);


#if defined __cplusplus
extern "C"
#endif
int64_t __matrix_inv_e(long double* a, int64_t* arc, long double* s, int64_t* src, long double* t);


#if defined __cplusplus
extern "C"
#endif
int64_t __matrix_inv(long double det, long double* a, int64_t* arc, long double* s);


#if defined __cplusplus
extern "C"
#endif
int64_t __matrix_INV(long double* a, int64_t* arc, long double* s, int64_t* src, long double* t, long double* inv);


#if defined __cplusplus
extern "C"
#endif
int64_t MatrixINV(int64_t* a, int8_t* arc, long double* s, int8_t* src, long double* t, long double* inv);


#if defined __cplusplus
extern "C"
#endif
int64_t __matrix_decode(long double a, long double* b, int64_t* brc, long double* d, int64_t* drc);


#if defined __cplusplus
extern "C"
#endif
int64_t MatrixDecode(long double a, long double* b, int8_t* brc, long double* d, int8_t* drc);


#if defined __cplusplus
extern "C"
#endif
long double radian_to_degree(int64_t r);




#define __SIZE_OF_NOISE__    128

/***
MAX Entropy 128
***/
#if defined __cplusplus
extern "C"
#endif
uint8_t __get_noiz(uint32_t who);

#if defined __cplusplus
extern "C"
#endif
int32_t __get_noise(int32_t who, uint8_t* o, int32_t sz_bit);

#if defined __cplusplus
extern "C"
#endif
int32_t __RCT(uint8_t* b, int32_t sz, uint32_t cutoff);

#if defined __cplusplus
extern "C"
#endif
int32_t __APT(uint8_t* b, int32_t sz, uint32_t cutoff);



#endif



