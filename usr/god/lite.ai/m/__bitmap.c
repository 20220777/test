#include "__bitmap.h"
#include <common.h>

int32_t get_pixel_single(int8_t* fn, int8_t* pif, uint8_t* p, uint8_t* o)
{
  int32_t e = 0;
  int32_t x=0, y=0;
  int32_t ofst; //10(4)
  int32_t wdth, hght, bcnt;   //18(4), 22(4), 28(2)
  int32_t dpth, padd;
  int32_t r, c;
  int32_t i=0;
  int8_t xy[2][8];
  FILE* fp;

  fp = fopen(fn, "rb");  
  fseek(fp, 0, 0);
  e = fread(p, 1, 14, fp);
  ofst = TO_INTEGER((p+10), 4);

  e = fread(&p[14], 1, ofst-14, fp);
  wdth = TO_INTEGER((p+18), 4);
  hght = TO_INTEGER((p+22), 4);
  dpth = TO_INTEGER((p+28), 2)/(sizeof(int8_t)*8);
  padd = wdth%(sizeof(int32_t));

  TO_COORD(pif, xy[0], xy[1]);
  x = atoi(xy[0]);
  y = atoi(xy[1]);

  fseek(fp, ((hght-x)*(wdth*dpth+padd) + (y-1)*dpth + ofst), 0);
  e = fread(o, 1, sizeof(uint8_t)*3, fp);

  fclose(fp);

  return e>0?(((*(o+0)<<16)|(*(o+1)<<8)|(*(o+2)))&0x00FFFFFF):e;
}


int32_t get_bmp_hdr(void* fp, uint8_t* p, uint32_t* h)
{
  int32_t e = 0;
  int32_t ofst; //10(4)
  int32_t wdth, hght, bcnt;   //18(4), 22(4), 28(2)
  
  fseek((FILE*)fp, 0, 0);
  e = fread(p, 1, 14, (FILE*)fp);
  ofst = TO_INTEGER((p+10), 4);

  e = fread(&p[14], 1, ofst-14, (FILE*)fp);
  wdth = TO_INTEGER((p+18), 4);
  hght = TO_INTEGER((p+22), 4);
  bcnt = TO_INTEGER((p+28), 2);

  *(h+0) = ofst;
  *(h+1) = wdth;
  *(h+2) = hght;
  *(h+3) = bcnt;

  return 0;
}


int32_t get_pixel(void* fp, int8_t* pif, uint32_t* h, uint8_t* o)
{
  int32_t e = 0;
  int32_t x=0, y=0;
  int32_t ofst; //10(4)
  int32_t wdth, hght, bcnt;   //18(4), 22(4), 28(2)
  int32_t dpth, padd;
  int32_t r, c;
  int32_t i=0;
  int8_t xy[2][8];
  
  fseek((FILE*)fp, 0, 0);

  ofst = *(h+0);
  wdth = *(h+1);
  hght = *(h+2);
  bcnt = *(h+3);
  dpth = bcnt/(sizeof(int8_t)*8);
  padd = wdth%(sizeof(int32_t));

  TO_COORD(pif, xy[0], xy[1]);
  x = atoi(xy[0]);
  y = atoi(xy[1]);
  fseek((FILE*)fp, ((hght-x)*(wdth*dpth+padd) + (y-1)*dpth + ofst), 0);

  e = fread(o, 1, sizeof(uint8_t)*dpth, (FILE*)fp);

  return  e==1?( *(o+0)&0x000000FF ):
          e==2?( ((*(o+0)<<8)|(*(o+1)))&0x0000FFFF ):
          e==3?( ((*(o+0)<<16)|(*(o+1)<<8 )|(*(o+2)))&0x00FFFFFF ):
          e==4?( ((*(o+0)<<24)|(*(o+1)<<16)|(*(o+2)<<8)|(*(o+3)))&0xFFFFFFFF ):e;
}



int32_t get_bmp_pixel(int8_t* fn, int8_t* pif, void* (*f)(int32_t, int32_t, int32_t), uint8_t* o)
{
  FILE* fp;
  uint8_t b[64];
  int32_t e = 0;
  int32_t i = 0;
  int32_t ii= 0;
  uint32_t owhb[4] = {0, };
  int32_t dpth, padd;
  int32_t rcnt = 0;

  fp = fopen(fn, "rb");

  e = get_bmp_hdr((void*)fp, b, owhb);


  if ( *f )
  {
    fseek((FILE*)fp, 0, 0);

    dpth = owhb[3]/(sizeof(int8_t)*8);
    padd = owhb[1]%(sizeof(int32_t));

    rcnt = ((owhb[1]*dpth)+padd);

    for ( i=1 ; i<=owhb[2] ; i++ )
    {
      for ( ii=1 ; ii<=owhb[1] ; ii++ )
      {
        fseek((FILE*)fp, ((owhb[2]-i)*(owhb[1]*dpth+padd) + (ii-1)*dpth + owhb[0]), 0);
        e = fread(b, 1, sizeof(uint8_t)*dpth, (FILE*)fp);
        e = ( e==1?(   *(b+0)&0x000000FF ):
              e==2?( ((*(b+0)<<8 )|(*(b+1)))&0x0000FFFF ):
              e==3?( ((*(b+0)<<16)|(*(b+1)<<8 )|(*(b+2)))&0x00FFFFFF ):
              e==4?( ((*(b+0)<<24)|(*(b+1)<<16)|(*(b+2)<<8)|(*(b+3)))&0xFFFFFFFF ):e);
        if ( (*f)(i, ii, e) < 0 ) break;
      }
    }
  }
  else
  {
    e = get_pixel((void*)fp, pif, owhb, o);
  }

  fclose(fp);
  return e;
}




int32_t get_bitmap(int8_t* img, int8_t* bmphdr, int8_t* dibhdr, int8_t** raw)
{
  int32_t e=0;
  int32_t i=0;
  int32_t offset = 0;
  //// dib hdr seq
  int32_t hdrsz = 0;
  int32_t wdth = 0;
  int32_t hght = 0;
  int16_t bpln = 0;
  int16_t bcnt = 0;

  int32_t w = 0;

  memcpy(bmphdr,  img+0, 14*sizeof(int8_t));
  memcpy(&offset, img+10, 4*sizeof(int8_t)); /// entire header length

  memcpy(&hdrsz,  img+14, 4*sizeof(int8_t));
  memcpy(dibhdr,  img+14, hdrsz*sizeof(int8_t));

  memcpy(&wdth,   dibhdr+4, 4*sizeof(int8_t));
  memcpy(&hght,   dibhdr+8, 4*sizeof(int8_t));
  memcpy(&bpln,   dibhdr+12, 2*sizeof(int8_t));
  memcpy(&bcnt,   dibhdr+14, 2*sizeof(int8_t));

  *raw = img+offset;  
  e = wdth*hght*(bcnt/8);

  return e;
}


int32_t set_bitmap(int8_t* img, int8_t* bmphdr, int8_t* dibhdr, int8_t* raw)
{
  int32_t s = 0;
  int32_t i = 0;
  int32_t offset = 0;
  //// dib hdr seq
  int32_t hdrsz = 0;
  int32_t wdth = 0;
  int32_t hght = 0;
  int16_t bpln = 0;
  int16_t bcnt = 0;

  int32_t w = 0;

  memcpy(img + 0, bmphdr, 14 * sizeof(int8_t));
  memcpy(&offset, bmphdr+10, 4 * sizeof(int8_t)); /// entire header length

  memcpy(&hdrsz, dibhdr, 4 * sizeof(int8_t));
  memcpy(img + 14, dibhdr, hdrsz * sizeof(int8_t));

  memcpy(&wdth, dibhdr + 4, 4 * sizeof(int8_t));
  memcpy(&hght, dibhdr + 8, 4 * sizeof(int8_t));
  memcpy(&bpln, dibhdr + 12,2 * sizeof(int8_t));
  memcpy(&bcnt, dibhdr + 14,2 * sizeof(int8_t));

  s = (wdth*(bcnt/(sizeof(uint8_t)*8))+BMP_PADDING(wdth))*hght;
  memcpy(img+offset, raw, s );

  return s;
}


int32_t write_bitmap(int8_t* fn, int8_t* wh, int8_t bcnt, int8_t* raw)
{
  int32_t e = 0;
  int8_t _wh[2][32] = {0};
  int32_t w = 0, h = 0;
  uint8_t bmphdr[14] = {0};
  uint8_t dibhdr[40] = {0};
  int32_t sz = 0;
  int32_t tsz = 0;
  int32_t offset = 54;
  uint8_t* img = 0;
  int32_t hdrsz = 40;
  FILE* fp = 0;
  
  TO_COORD(wh, _wh[0], _wh[1])

  w = atoll(_wh[0]);
  h = atoll(_wh[1]);

  sz = (w*(bcnt/(sizeof(uint8_t)*8))+BMP_PADDING(w))*h;
  tsz = sz + offset;

  bmphdr[0] = 'B';
  bmphdr[1] = 'M';

  memcpy(&bmphdr[2],  &tsz, sizeof(uint32_t));
  memcpy(&bmphdr[10], &offset, sizeof(uint32_t));
  memcpy(&dibhdr[0],  &hdrsz, sizeof(uint32_t));
  memcpy(&dibhdr[4],  &w, sizeof(uint32_t));
  memcpy(&dibhdr[8],  &h, sizeof(uint32_t));

  dibhdr[12] = 1;
  dibhdr[13] = 0;

  memcpy(&dibhdr[14], &bcnt, sizeof(uint16_t));
  memcpy(&dibhdr[20], &sz, sizeof(uint32_t));


  fp = fopen(fn, "wb");
  img = (uint8_t*)calloc(tsz, sizeof(uint8_t));
  set_bitmap(img, bmphdr, dibhdr, raw);

  fwrite(img, 1, tsz, fp);
  fflush(fp);
  fclose(fp);
  free(img);
  
  return e;
}




int32_t mosaic(int8_t* img, int8_t* hdr, int32_t x, int32_t y, int32_t w, int32_t h, int8_t** raw)
{
  int32_t e=0;
  int32_t i=0;
  int32_t offset = 0;
  //// dib hdr seq
  int32_t hdrsz = 0;
  int32_t wdth = 0;
  int32_t hght = 0;
  int16_t bpln = 0;
  int16_t bcnt = 0;
  int32_t _h=0;
  int32_t dpth=0;

  memcpy(hdr,  img+0, 14*sizeof(int8_t));
  memcpy(&offset, img+10, 4*sizeof(int8_t)); /// entire header length

  memcpy(&hdrsz,  img+14, 4*sizeof(int8_t));
  memcpy(hdr+14,  img+14, hdrsz*sizeof(int8_t));

  memcpy(&wdth,   hdr+18, 4*sizeof(int8_t));
  memcpy(&hght,   hdr+22, 4*sizeof(int8_t));
  memcpy(&bpln,   hdr+26, 2*sizeof(int8_t));
  memcpy(&bcnt,   hdr+28, 2*sizeof(int8_t));

  dpth = (bcnt/(sizeof(uint8_t)*8));

  if ( (x+w) > wdth ) return -1;
  if ( (y+h) > hght ) return -1;

  for ( i=0, _h=0 ; _h<h ; i++, _h++ )
  {
    memcpy((*raw+(w*dpth*i)), img+offset+((BMP_PADDING(wdth)+wdth*dpth)*(hght-(h-_h)-y))+(x*dpth), sizeof(uint8_t)*w*dpth);
  }
  e = _h*i*dpth;

  return e;
}


int32_t pick_mosaic_bitmap(int8_t* src, int32_t x, int32_t y, int32_t w, int32_t h, int8_t** dst)
{
  int32_t sz = 0;
  int8_t  bmphdr[54];
  int32_t _sz = 0;
  int32_t rsz = 0;
  int8_t* p = *dst+54;

  int16_t bcnt = 0;

  sz = mosaic(src, bmphdr, x, y, w, h, &p);
  if ( sz < 0 ) return sz;

  memcpy(&bcnt, &bmphdr[28], 2*sizeof(int8_t));

  _sz = sz+54;
  rsz = w*h*(bcnt/(sizeof(uint8_t)*8));

  memcpy(*dst, src, 54*sizeof(int8_t));

  memcpy(*dst+2, &_sz, sizeof(int32_t));
  memcpy(*dst+18, &w, sizeof(int32_t));
  memcpy(*dst+22, &h, sizeof(int32_t));
  memcpy(*dst+34, &rsz, sizeof(int32_t));

  return _sz;
}







int32_t write_raw_bitmap(int8_t* raw, int32_t* wh, int32_t bcnt, int8_t* tgt)
{
  int32_t ofst = 54;
  int32_t hdsz = 40;
  int32_t tsz = 0;
  int32_t sz = 0;
  int32_t _h = 0;
  int32_t dpth = 0;

  sz = ((*(wh+0))*(bcnt/(sizeof(uint8_t)*8))+BMP_PADDING(*(wh+0)))*(*(wh+1));
  tsz = sz + ofst;
  dpth = (bcnt/(sizeof(uint8_t)*8));

  *(tgt+0) = 'B';
  *(tgt+1) = 'M';
  memcpy(tgt+2,  &tsz, 4*sizeof(int8_t));
  memcpy(tgt+10, &ofst, 4*sizeof(int8_t));
  memcpy(tgt+14, &hdsz, 4*sizeof(int8_t));
  memcpy(tgt+18,  wh+0, 4*sizeof(int8_t));
  memcpy(tgt+22,  wh+1, 4*sizeof(int8_t));
  *(tgt+26) = 1;
  *(tgt+27) = 0;
  memcpy(tgt+28, &bcnt, 2*sizeof(int8_t));
  memcpy(tgt+34, &sz, 2*sizeof(int8_t));

  for ( _h=0 ; _h<*(wh+1) ;_h++ )
  {
    memcpy(tgt+ofst+((BMP_PADDING(*(wh+0))+(*(wh+0))*dpth)*((*(wh+1))-_h-1)), raw+((*(wh+0))*dpth)*((*(wh+1))-_h-1), sizeof(uint8_t)*dpth*(*(wh+0)));
  }

  return tsz;
}




int32_t rwrite_raw_bitmap(int8_t* raw, int32_t* wh, int32_t bcnt, int8_t* tgt)
{
  int32_t ofst = 54;
  int32_t hdsz = 40;
  int32_t tsz = 0;
  int32_t sz = 0;
  int32_t _h = 0;
  int32_t dpth = 0;

  sz = ((*(wh+0))*(bcnt/(sizeof(uint8_t)*8))+BMP_PADDING(*(wh+0)))*(*(wh+1));
  tsz = sz + ofst;
  dpth = (bcnt/(sizeof(uint8_t)*8));

  *(tgt+0) = 'B';
  *(tgt+1) = 'M';
  memcpy(tgt+2,  &tsz, 4*sizeof(int8_t));
  memcpy(tgt+10, &ofst, 4*sizeof(int8_t));
  memcpy(tgt+14, &hdsz, 4*sizeof(int8_t));
  memcpy(tgt+18,  wh+0, 4*sizeof(int8_t));
  memcpy(tgt+22,  wh+1, 4*sizeof(int8_t));
  *(tgt+26) = 1;
  *(tgt+27) = 0;
  memcpy(tgt+28, &bcnt, 2*sizeof(int8_t));
  memcpy(tgt+34, &sz, 2*sizeof(int8_t));

  for ( _h=0 ; _h<*(wh+1) ;_h++ )
  {
    memcpy(tgt+ofst+((BMP_PADDING(*(wh+0))+(*(wh+0))*dpth)*((*(wh+1))-_h-1)), raw+((*(wh+0))*dpth)*_h, sizeof(uint8_t)*dpth*(*(wh+0)));
  }

  return tsz;
}


int32_t write_raw(int8_t* raw, int32_t* wh, int32_t bcnt, int8_t* bmp)
{
  int32_t e=0;
  int32_t i=0;
  int32_t ofst = 54;
  int32_t hdsz = 40;
  int32_t tsz = 0;
  int32_t sz = 0;

  sz = ((*(wh+0))*(bcnt/(sizeof(uint8_t)*8))+BMP_PADDING(*(wh+0)))*(*(wh+1));
  tsz = sz + ofst;

  *(bmp+0) = 'B';
  *(bmp+1) = 'M';
  memcpy(bmp+2,  &tsz, 4*sizeof(int8_t));
  memcpy(bmp+10, &ofst, 4*sizeof(int8_t));
  memcpy(bmp+14, &hdsz, 4*sizeof(int8_t));
  memcpy(bmp+18,  wh+0, 4*sizeof(int8_t));
  memcpy(bmp+22,  wh+1, 4*sizeof(int8_t));
  *(bmp+26) = 1;
  *(bmp+27) = 0;
  memcpy(bmp+28, &bcnt, 2*sizeof(int8_t));
  memcpy(bmp+34, &sz, 2*sizeof(int8_t));

  memcpy(bmp+ofst, raw, sz );

  return tsz;
}



int32_t read_raw(int8_t* bmp, int32_t* xy, int32_t* wh, int8_t** raw)
{
  int32_t ofst = 0;
  int32_t hdsz = 0;
  int32_t wdth = 0;
  int32_t hght = 0;
  int16_t bpln = 0;
  int16_t bcnt = 0;
  int32_t dpth=0;
  int32_t _h=0;

  memcpy(&ofst, bmp+10, 4*sizeof(int8_t));
  memcpy(&hdsz,  bmp+14, 4*sizeof(int8_t));
  memcpy(&wdth,   bmp+14+4, 4*sizeof(int8_t));
  memcpy(&hght,   bmp+14+8, 4*sizeof(int8_t));
  memcpy(&bpln,   bmp+14+12, 2*sizeof(int8_t));
  memcpy(&bcnt,   bmp+14+14, 2*sizeof(int8_t));

  dpth = (bcnt/(sizeof(uint8_t)*8));

  if ( (*(xy+0)+*(wh+0) ) > wdth ) return -1;
  if ( (*(xy+1)+*(wh+1) ) > hght ) return -1;

  //if ( r == 'r' || r == 'R' )
  //{
  //  for ( _h=*(wh+1)-1 ; _h>=0 ; _h-- )
  //  {
  //    memcpy((*raw+((*(wh+0))*dpth*(*(wh+1)-1-_h))), bmp+ofst+((BMP_PADDING(wdth)+wdth*dpth)*(hght-((*(wh+1))-_h)-(*(xy+1))))+((*(xy+0))*dpth), sizeof(uint8_t)*(*(wh+0))*dpth);
  //  }
  //}
  //else
  {
    for (_h=0 ; _h<*(wh+1) ; _h++ )
    {
      memcpy((*raw+((*(wh+0))*dpth*_h)), bmp+ofst+((BMP_PADDING(wdth)+wdth*dpth)*(hght-((*(wh+1))-_h)-(*(xy+1))))+((*(xy+0))*dpth), sizeof(uint8_t)*(*(wh+0))*dpth);
    }
  }
  return (*(wh+0))*(*(wh+1))*dpth;
}



int32_t rread_raw(int8_t* bmp, int32_t* xy, int32_t* wh, int8_t** raw)
{
  int32_t ofst = 0;
  int32_t hdsz = 0;
  int32_t wdth = 0;
  int32_t hght = 0;
  int16_t bpln = 0;
  int16_t bcnt = 0;
  int32_t dpth=0;
  int32_t _h=0;

  memcpy(&ofst, bmp+10, 4*sizeof(int8_t));
  memcpy(&hdsz,  bmp+14, 4*sizeof(int8_t));
  memcpy(&wdth,   bmp+14+4, 4*sizeof(int8_t));
  memcpy(&hght,   bmp+14+8, 4*sizeof(int8_t));
  memcpy(&bpln,   bmp+14+12, 2*sizeof(int8_t));
  memcpy(&bcnt,   bmp+14+14, 2*sizeof(int8_t));

  dpth = (bcnt/(sizeof(uint8_t)*8));

  if ( (*(xy+0)+*(wh+0) ) > wdth ) return -1;
  if ( (*(xy+1)+*(wh+1) ) > hght ) return -1;

  for (  _h=*(wh+1)-1 ; _h>=0 ; _h-- )
  {
    memcpy((*raw+((*(wh+0))*dpth*(*(wh+1)-1-_h))), bmp+ofst+((BMP_PADDING(wdth)+wdth*dpth)*(hght-((*(wh+1))-_h)-(*(xy+1))))+((*(xy+0))*dpth), sizeof(uint8_t)*(*(wh+0))*dpth);
  }
  return (*(wh+0))*(*(wh+1))*dpth;
}


int32_t pick_pixel(int8_t* bmp, int32_t* xy, int8_t** raw)
{
  int32_t ofst = 0;
  int32_t hdsz = 0;
  int32_t wdth = 0;
  int32_t hght = 0;
  int16_t bpln = 0;
  int16_t bcnt = 0;
  int32_t dpth = 0;

  memcpy(&ofst, bmp+10, 4*sizeof(int8_t));
  memcpy(&hdsz,  bmp+14, 4*sizeof(int8_t));
  memcpy(&wdth,   bmp+14+4, 4*sizeof(int8_t));
  memcpy(&hght,   bmp+14+8, 4*sizeof(int8_t));
  memcpy(&bpln,   bmp+14+12, 2*sizeof(int8_t));
  memcpy(&bcnt,   bmp+14+14, 2*sizeof(int8_t));

  dpth = (bcnt/(sizeof(uint8_t)*8));

  if ( (*(xy+0) ) > wdth ) return -1;
  if ( (*(xy+1) ) > hght ) return -1;

  memcpy(*raw, bmp+ofst+((BMP_PADDING(wdth)+wdth*dpth)*(hght-(*(xy+1))-1)+((*(xy+0))*dpth)), sizeof(uint8_t)*dpth);

  return sizeof(uint8_t)*dpth;
}


int32_t __serialize_bitmap(int8_t* bmp, int32_t *wh, int32_t bcnt, int32_t padding, uint8_t* seq, int8_t* raw)
{
  int32_t i=0;
  int32_t dpth = bcnt/8;
  int32_t pwdth = 0;
  int32_t bmppadding = (*(seq+1)=='b'||*(seq+1)=='B')?(*(wh+0)%sizeof(uint32_t)):0;

  pwdth += (padding? ((*(wh+0)) + padding*2)*dpth:0);
  if ( *(seq+0)=='r' || *(seq+0)=='R' )
  {
    for ( i=0 ; i<*(wh+1) ; i++ )
    {
      pwdth+=padding*dpth;
      memcpy(raw+((*(wh+0))*dpth*i)+pwdth, bmp+((bmppadding+*(wh+0)*dpth)*(*(wh+1)-i-1)), sizeof(uint8_t)**(wh+0)*dpth);
      pwdth+=padding*dpth;
    }
  }
  else if ( *(seq+0)=='f' || *(seq+0)=='F' )
  {
    for ( i=0 ; i<*(wh+1) ; i++ )
    {
      pwdth+=padding*dpth;
      memcpy(raw+((*(wh+0))*dpth*i)+pwdth, bmp+((bmppadding+*(wh+0)*dpth)*i), sizeof(uint8_t)**(wh+0)*dpth);
      pwdth+=padding*dpth;
    }

  }
  pwdth += (padding? ((*(wh+0)) + padding*2)*dpth:0);

  return ((*(wh+0))*dpth*i)+pwdth;
}



int32_t __padding_size(int32_t* wh, int32_t bcnt, int32_t padding)
{
  return ((*(wh+0))+padding*2)*(bcnt/8)*((*(wh+1))+padding*2);
}
