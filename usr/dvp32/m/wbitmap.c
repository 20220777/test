#include "wbitmap.h"
#include "resource.h"

static wBitmap* gp;


void setFont()
{
  HFONT  font;
  font = CreateFont(10, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "Courier New");

  SetFont(gp->hitem[EDIT_BITMAP_BMPHDR], &font);
  SetFont(gp->hitem[EDIT_BITMAP_DIBHDR], &font);
  SetFont(gp->hitem[EDIT_BITMAP_HEX], &font);
  
}


int bitmap_info(char* bmphdr, char* dibhdr, char* raw)
{
  char sample[256];
  int sz = 0;

  char _c[32];
  int  _s;

  int wdth, hght, bcnt;
  int  i, h, w;

  // bmphdr
  // type       : 2
  // size       : 4
  // reserved 1 : 2
  // reserved 2 : 2 
  // offset     : 4
  sprintf(&sample[sz], "type : %c%c \r\n", *(bmphdr+0), *(bmphdr+1));
  sz += strlen(&sample[sz]);

  memcpy(&_s, bmphdr+2, sizeof(int));
  sprintf(&sample[sz], "size : %d \r\n", _s);
  sz += strlen(&sample[sz]);

  memcpy(&_s, bmphdr+10, sizeof(int));
  sprintf(&sample[sz], "offset: %d \r\n", _s);
  sz += strlen(&sample[sz]);

  SetText(gp->hitem[EDIT_BITMAP_BMPHDR], sample, sz);
  sz = 0;
  // dibhdr
  // hdr size         : 4
  // width            : 4
  // height           : 4
  // plane            : 2  ,  current value is 1
  // bit count        : 2
  // compression type : 4
  // size of image    : 4
  // x pixel / M      : 4
  // x pixel / M      : 4
  // color map        : 4
  // color used       : 4
  memcpy(&_s, dibhdr, sizeof(int));
  sprintf(&sample[sz], "hdr size : %d \r\n", _s);
  sz += strlen(&sample[sz]);

  memcpy(&_s, dibhdr+4, sizeof(int));
  sprintf(&sample[sz], "width : %d \r\n", _s);
  sz += strlen(&sample[sz]);
  wdth = _s;

  memcpy(&_s, dibhdr+8, sizeof(int));
  sprintf(&sample[sz], "height : %d \r\n", _s);
  sz += strlen(&sample[sz]);
  hght = _s;

  memcpy(&_s, dibhdr+12, sizeof(short));
  sprintf(&sample[sz], "bit plane : %d \r\n", _s);
  sz += strlen(&sample[sz]);

  memcpy(&_s, dibhdr+14, sizeof(short));
  sprintf(&sample[sz], "bit count : %d \r\n", _s);
  sz += strlen(&sample[sz]);
  bcnt = _s;

  memcpy(&_s, dibhdr+16, sizeof(int));
  sprintf(&sample[sz], "compression : %d \r\n", _s);
  sz += strlen(&sample[sz]);

  memcpy(&_s, dibhdr+20, sizeof(int));
  sprintf(&sample[sz], "entire image size : %d \r\n", _s);
  sz += strlen(&sample[sz]);

  memcpy(&_s, dibhdr+24, sizeof(int));
  sprintf(&sample[sz], "x pixel : %d \r\n", _s);
  sz += strlen(&sample[sz]);

  memcpy(&_s, dibhdr+28, sizeof(int));
  sprintf(&sample[sz], "y pixel : %d \r\n", _s);
  sz += strlen(&sample[sz]);

  memcpy(&_s, dibhdr+32, sizeof(int));
  sprintf(&sample[sz], "color map entry count : %d \r\n", _s);
  sz += strlen(&sample[sz]);

  memcpy(&_s, dibhdr+36, sizeof(int));
  sprintf(&sample[sz], "number of color : %d \r\n", _s);
  sz += strlen(&sample[sz]);

  SetText(gp->hitem[EDIT_BITMAP_DIBHDR], sample, sz);



  ///// RAW PIXEL
  sz = 0;
  bcnt = bcnt/8;
  for ( h=hght-1 ; h>=0 ; h-- )
  {
    sz = 0;
    for ( w=0 ; w<(wdth*bcnt) ; w+=bcnt )
    {
      for ( i=0 ; i<bcnt ; i++ )
      {
        //sprintf(&sample[sz], "%d", ((unsigned char)*(raw+i+w + h*(wdth*bcnt)))=0?1:0);
        sprintf(sample, "%02X ", (unsigned char)*(raw+i+w + h*(wdth*bcnt)));
        AppendText(gp->hitem[EDIT_BITMAP_HEX], sample, strlen(sample));
      }
    }
    sprintf(&sample[sz], "\r\n");    
    AppendText(gp->hitem[EDIT_BITMAP_HEX], sample, strlen(sample));
  }

  return 0;
}

static int load_bitmap(char* fname, int(*f)(char*, char*, char*))
{
  FILE* fp = 0;
  char* f_buf;
  int   fsz;
  char  bmphdr[14];
  char  dibhdr[40];
  char* raw;

  fp = fopen(fname, "rb");

  fsz = get_file_size(fname);

  f_buf = (char*)calloc(fsz, sizeof(char));
  fread(f_buf, 1, fsz, fp);

  get_bitmap(f_buf, bmphdr, dibhdr, &raw);

  if ( f ) f(bmphdr, dibhdr, raw);

  free(f_buf);
  fclose(fp);
  return 0;
}


void draw_bitmap(char* fname)
{
  HBITMAP hbmp, oldbmp;
  BITMAP  bitmap;
  HDC     hmemdc;
  HDC     hdc;
  PAINTSTRUCT ps;

  hdc = BeginPaint(gp->hitem[STATIC_BITMAP_VIEW], &ps);
  hmemdc = CreateCompatibleDC(hdc);

  hbmp = (HBITMAP)LoadImage(0, fname, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION|LR_LOADFROMFILE);

  GetObject(hbmp, sizeof(bitmap), &bitmap);
  oldbmp = (HBITMAP)SelectObject(hmemdc, hbmp);
  BitBlt(hdc, 10, 10, bitmap.bmWidth, bitmap.bmHeight, hmemdc, 0, 0, SRCCOPY);
  SelectObject(hmemdc, oldbmp);
  DeleteObject(hbmp);

  DeleteDC(hmemdc);
  //DeleteDC(hdc);
  EndPaint(gp->hitem[STATIC_BITMAP_VIEW], &ps);
}






void wbitmap_command(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  char temp[32];

  switch(LOWORD(wparam))
  {
    case IDC_BUTTON_BITMAP_FILEOPEN:
      if (open_file_dialog(0, gp->fname, "Bitmap\0*.bmp\0") == MB_OK)
      {
        SetText(gp->hitem[EDIT_BITMAP_FILE], gp->fname, strlen(gp->fname));

        load_bitmap(gp->fname, bitmap_info);

        //draw_bitmap(gp->fname);

        //x_draw_ctrl(gp->pimg, gp->hitem[STATIC_BITMAP_VIEW]);
      }
      break;

    case IDC_EDIT_BITMAP_FILE:
      break;

    case IDC_STATIC_BITMAP_VIEW:
      break;

    case IDC_BUTTON_BITMAP_CONVERT:
      break;

    case IDC_EDIT_BITMAP_HEX:
      break;
  }    
}

void* wbitmap_dlgproc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  switch(msg)
  {
    case WM_COMMAND:
      wbitmap_command(hwnd, msg, wparam, lparam);
      break;

    case WM_PAINT:
      draw_bitmap("D:\\temp\\a.bmp");
      break;
    default:
      break;    
  }

  return 0;
}


void* wbitmap_init(HWND hwnd, wBitmap* p)
{
  int e;
  void* hmod;

  gp = p;
  //memset(&mbitmap, 0, sizeof(tagBitmap));

  gp->hitem[BUTTON_BITMAP_FILEOPEN] = GetDlgItem(hwnd, IDC_BUTTON_BITMAP_FILEOPEN);
  gp->hitem[EDIT_BITMAP_FILE] = GetDlgItem(hwnd, IDC_EDIT_BITMAP_FILE);
  gp->hitem[STATIC_BITMAP_VIEW] = GetDlgItem(hwnd, IDC_STATIC_BITMAP_VIEW);
  gp->hitem[BUTTON_BITMAP_CONVERT] = GetDlgItem(hwnd, IDC_BUTTON_BITMAP_CONVERT);
  gp->hitem[EDIT_BITMAP_BMPHDR] = GetDlgItem(hwnd, IDC_EDIT_BITMAP_BMPHDR);
  gp->hitem[EDIT_BITMAP_DIBHDR] = GetDlgItem(hwnd, IDC_EDIT_BITMAP_DIBHDR);
  gp->hitem[EDIT_BITMAP_HEX] = GetDlgItem(hwnd, IDC_EDIT_BITMAP_HEX);


  SetText(gp->hitem[BUTTON_BITMAP_FILEOPEN], "OPEN", 4);
  SetText(gp->hitem[BUTTON_BITMAP_CONVERT], "CONVERT", 7);

  setFont();

  //new_ximage(&gp->pimg);

  return 0;
}
