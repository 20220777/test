#include <stdio.h>
#include <stdint.h>
//#include <network.h>
#include <common.h>
#include <nm.h>

#if __LINUX__
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <linux/wireless.h>
#endif

#if __NODE__
#define IFF_LOOPBACK     0x08
#endif

#define WIFI_NETWORK               "/etc/wpa_supplicant/wpa_supplicant.conf"
#define CUSTOM_NETWORK             "/etc/dhcpcd.conf"
#define DNS_INFO                   "/etc/resolv.conf"
#define GW_INFO                    "/proc/net/route"
#define EEPROM                     "/opt/iiot/rom"
#define WPA_CONF                   "wpa_supplicant.conf"

#define GUIDE_WIDTH                480
#define GUIDE_HEIGHT               280
#define GUIDE_TOP                  32
#define GUIDE_BOTTOM               (GUIDE_HEIGHT-GUIDE_TOP)
#define WIDTH                      "40px"
#define HEIGHT                     "14px"
#define TWIDTH_00                  "25%"
#define TWIDTH_01                  "75%"
#define THEIGHT                    "24px"
#define __DEVICES__                "eth0\nwlan0\n"
#define SECRET_KEY                 "OOOOOOOO"


int32_t _writeto(uint8_t* fn, int32_t offset, uint8_t* o, int32_t sz)
{
  int32_t e = 0;
  FILE* fp = 0;

  fp = fopen(fn, "w");
  fseek(fp, offset, SEEK_SET);
  e = fwrite(o, sizeof(uint8_t), sz,  fp);  
  fclose(fp);
  return e;
}

int32_t _readfrom(uint8_t* fn, int32_t offset, uint8_t* o, int32_t* sz)
{
  int32_t e = 0;
  FILE* fp = 0;

  fp = fopen(fn, "r");
  if ( fp == 0 )
  {
    return 0xEFFFFFFF;
  }
  fseek(fp, offset, SEEK_SET);
  e = fread(o, sizeof(uint8_t), *sz, fp);
  if ( e >=0 )  *(o+e) = 0;

  fclose(fp);
  return e;
}


int32_t _appendto(uint8_t* fn, int32_t offset, uint8_t* o, int32_t sz)
{
  int32_t e = 0;
  FILE* fp = 0;
  int32_t s = 0;

  fp = fopen(fn, "a+");
  fseek(fp, offset, SEEK_SET);
  s = ftell(fp);
  fseek(fp, s, SEEK_SET);
  e = fwrite(o, sizeof(uint8_t), sz, fp);  
  fclose(fp);
  return e;
}


int32_t xget_dlmtr(uint8_t* in, int8_t dlmtr, int32_t idx, int8_t* out)
{
  int32_t e=-1;
  int32_t i=0;
  int32_t ii=0;
  int32_t _idx = -1;

  if ( dlmtr == 0 ) return e;

  for ( i=0,ii=0 ;i<(int32_t)strlen(in) ; i++,ii++ )
  {
    *(out+ii) = *(in+i);

    //printf("[%02X] [%c] \r\n", *(in+i), *(in+i));

    if ( *(in+i)==dlmtr )
    {
      _idx++;
      e = idx-_idx;
    }

    if ( e >= 1 )
    {
      ii=-1;
      e=-1;
    }

    if ( e == 0 )
    {
      *(out+ii) = 0;
      e = ii;
      break;
    }
  }


  if ( i==(int32_t)strlen(in) )
  {
    if ( (idx-_idx)<=1 )
    {
      *(out+ii) = 0;
      e = ii?ii:-1;
    }
    else
    {
      *out = 0;
    }
  }

  return e;
}



int32_t _getEEPROM(uint8_t* dn, uint8_t* token, uint8_t* o, int32_t* sz)
{
  int32_t e = 0;
  int32_t i = 0;
  int8_t fname[256] = {0};
  int8_t fcontents[4096] = {0};
  int8_t v[32][64] = {0};
  int8_t* pv;
  int32_t s = 4096;
  int32_t pos = 0;

  sprintf(fname, "%s/.%s", EEPROM, dn);
  e = _readfrom(fname, 0, fcontents, &s);
  if ( e < 0 ) return -1;

  for ( i=0; ; i++)
  {
    e = get_dlmtr(fcontents, '\n', i, v[0]);
    if ( e > 0 )
    {
      e = get_dlmtr(v[0], '=', 0, v[1]);
      e = get_dlmtr(v[1], ' ', 1, v[2]);
      if ( strncmp(token, v[2], strlen(v[2])) == 0 )
      {
        *sz = get_dlmtr(v[0], '=', 1, o);
        break;
      }
    }
    else
    {
      e = i;
      break;
    }
  }

  return e;
}


int32_t _checkDHCP(int8_t* dn)
{
  int32_t e = 0;
  int8_t fname[256] = {0};
  int8_t fcontents[4096] = {0};
  int8_t* pf = fcontents;
  int32_t s = 4096;

  sprintf(fname, "%s/.%s", EEPROM, dn);
  e = _readfrom(fname, 0, fcontents, &s);
  if ( e < 0 ) return 0xEFFFFFFF;

  for ( ; (*pf)==' ' ; pf++);

  if ( *pf == '#' ) return 1;
  return 0;
}

int32_t _get_keyvalue(uint8_t* in, uint8_t* key, uint8_t* out)
{
  uint8_t* p = in;
  int32_t i = 0;
  int32_t l = 0;
  int32_t e = -1;
  for ( ; *in; in++)
  {
    p = in;
    for ( i=0 ; *in && (*in!='&') ; in++, i++ ) if (*in == '=') l=i;
    if ( (strlen(key)==l) && (strncmp(p,key,l)==0) )
    {
      *in = 0;
      memcpy(out, p+l+1, (i-l)*sizeof(uint8_t));
      e = i-l-1;
      break;
    }
  }
  return e;
}

int32_t get_token(uint8_t* in, uint8_t* dist, int32_t idx, uint8_t* out, int32_t* sz)
{
  int32_t e = 0;
  int32_t i = 0;
  int32_t k = 0;

  for ( ; *in ; in++ )
  {
    if ( *in == dist )
    {
      *sz = k;
      k = 0;
      if ( i-1 == idx )
      {
        *(out+*sz) = 0;
        break;
      }
    }
    else
    {
      if ( k==0 ) i++;
      *(out+k) = *in;
      k++;
    }
  }
  return *sz;
}
int32_t _nRead(uint8_t* f, uint8_t* b, int32_t* sz)
{
  FILE* fp = fopen(f, "r");
  int32_t e = 0;

  for ( ; ; )
  {
    e = fread(b+(*sz), 1, 1024, fp);
    if ( e > 0 )
    {
      *sz+=e;
    }
    else
    {
      break;
    }
  }
  fclose(fp);
  return *sz;
}

int32_t netmask_prefix(uint8_t* nm)
{
  int32_t pfx = 0;

  for ( ; *nm ; nm++)
  {
    if ( *nm & 0x80 ) pfx++;  else break;
    if ( *nm & 0x40 ) pfx++;  else break;
    if ( *nm & 0x20 ) pfx++;  else break;
    if ( *nm & 0x10 ) pfx++;  else break;
    if ( *nm & 0x08 ) pfx++;  else break;
    if ( *nm & 0x04 ) pfx++;  else break;
    if ( *nm & 0x02 ) pfx++;  else break;
    if ( *nm & 0x01 ) pfx++;  else break;
  }
  return pfx;
}

int32_t netmask_convert(int8_t pfx, uint8_t* nm)
{
  int8_t i = 0;
  int8_t j = pfx;
  int8_t k = 0;
  for ( k=0 ; j>0 ; k++ )
  {
    for ( i=7 ; i>=0 ; i--, j-- )
    {
      *(nm+k) |= (0x01 << i);
      //printf("[%d,%d] %02X %02X %02X %02X\r\n", i,k, *(nm), *(nm+1), *(nm+2), *(nm+3));
    }
  }
  return *nm;
}



int32_t stoh(uint8_t* in, uint8_t* t, uint8_t* out)
{
  volatile uint8_t _dgt[4] = {0};
  uint8_t i = 0;
 
  for ( ; *in ; in++ )
  {
    memset(_dgt, 0, sizeof(uint8_t)*4);
    for ( i=0 ; (*in!=*t) && *in ; in++, i++ )
    {
      _dgt[i] = *in;
    }
    *out = atoi(_dgt);
    out++;
  }
  return 0;
}

int32_t ip_to_hex(uint8_t* in, uint8_t* out)
{
  uint8_t _dgt[4] = {0};
  uint8_t i = 0;
 
  for ( ; *in ; in++ )
  {
    memset(_dgt, 0, sizeof(uint8_t)*4);
    for ( i=0 ; (*in!='.') && *in ; in++, i++ )
    {
      _dgt[i] = *in;
    }
    *out = atoi(_dgt);
    out++;
  }
  return 0;
}

int32_t _getIFNames(uint8_t* o)
{
  int32_t e=0;
  #if __LINUX__
  int32_t i = 0;
  int32_t n = 0;
  int32_t fd = 0;
  uint8_t data[4096] = {0};
  struct ifconf ifc = {0};
  struct ifreq* ifr = 0;
  #if __DEBUG__
  printf(" %-16s:%6d | \r\n", __FUNCTION__,__LINE__);
  #endif

  fd = socket(AF_INET,SOCK_DGRAM, 0);

  ifc.ifc_len = sizeof(data);
  ifc.ifc_buf = (caddr_t)data;

  ioctl(fd, SIOCGIFCONF, &ifc);

  ifr = (struct ifreq*)data;
  n = ifc.ifc_len/sizeof(struct ifreq);

  for ( i=0 ; i<n ; i++ )
  {
    sprintf(o, "%s\n", ((ifr+i)->ifr_name));
    o+=strlen(o);
  }
  e = i;
  close(fd);
  #endif

  return e;
}



int32_t _getIP(uint8_t* dname, uint8_t* o)
{
  int32_t e = 0;
  int32_t fd = 0;

  #if __LINUX__
  struct ifreq ifr = {0};

  #if __DEBUG__
  printf(" %-16s:%6d | %s\r\n", __FUNCTION__,__LINE__,dname);
  #endif

  fd = socket(AF_INET,SOCK_DGRAM, 0);
  ifr.ifr_addr.sa_family = AF_INET;
  memcpy(ifr.ifr_name, dname, IFNAMSIZ-1);

  ioctl(fd, SIOCGIFADDR, &ifr);
  close(fd);

  sprintf(o, "%s", inet_ntoa(((struct sockaddr_in*)&ifr.ifr_addr)->sin_addr));
  #endif

  return e;
}

int32_t _getNetmask(uint8_t* dname, uint8_t* o)
{
  int32_t e = 0;
  int32_t fd = 0;
  #if __DEBUG__
  printf(" %-16s:%6d | \r\n", __FUNCTION__,__LINE__);
  #endif

  #if __LINUX__
  struct ifreq ifr = {0};

  fd = socket(AF_INET,SOCK_DGRAM, 0);

  ifr.ifr_addr.sa_family = AF_INET;

  memcpy(ifr.ifr_name, dname, IFNAMSIZ-1);

  ioctl(fd, SIOCGIFNETMASK, &ifr);
  close(fd);

  sprintf(o, "%s", inet_ntoa(((struct sockaddr_in*)&ifr.ifr_netmask)->sin_addr));
  #endif

  return e;
}

int32_t _getGateway(uint8_t* dname, uint8_t* o)
{
  int32_t i = 0;
  int32_t k = 0;
  int32_t e = 0;
  int32_t sz = 0;
  uint8_t gw[1024] = {0};
  uint8_t _gw[32] = {0};
  uint8_t __gw[4] = {0};
  uint8_t _info[1024] = {0};
  #if __DEBUG__
  printf(" %-16s:%6d | \r\n", __FUNCTION__,__LINE__);
  #endif

  #if __LINUX__
  e = _nRead(GW_INFO, gw, &sz);

  for ( i=0 ; ; i++ )
  {
    e = get_dlmtr(gw, '\n', i, _info);
    if ( e < 0 ) break;

    if ( strncmp(_info, dname, strlen(dname))==0 )
    {
      for ( k=0 ; *(_info+k) ; k++)
      {
        if ( *(_info+k)=='\r' )
        {
          *(_info+k)=0;
          break;
        }
      }

      e = get_token(_info, 0x09, 2, _gw, &sz);
      __gw[0] = HSTR_TO_HEX(&_gw[6]);
      _gw[6]=0;
      __gw[1] = HSTR_TO_HEX(&_gw[4]);
      _gw[4]=0;
      __gw[2] = HSTR_TO_HEX(&_gw[2]);
      _gw[2]=0;
      __gw[3] = HSTR_TO_HEX(&_gw[0]);

      sprintf(o, "%d.%d.%d.%d", __gw[0], __gw[1], __gw[2], __gw[3]);
      break;
    }
  }
  #endif
  return e;
}

int32_t _getMAC(uint8_t* dname, uint8_t* o)
{
  int32_t e = 0;
  int32_t fd = 0;
  #if __DEBUG__
  printf(" %-16s:%6d | \r\n", __FUNCTION__,__LINE__);
  #endif

  #if __LINUX__
  struct ifreq ifr = {0};

  fd = socket(AF_INET,SOCK_DGRAM, 0);

  ifr.ifr_addr.sa_family = AF_INET;

  memcpy(ifr.ifr_name, dname, IFNAMSIZ-1);

  ioctl(fd, SIOCGIFHWADDR, &ifr);
  close(fd);

  memcpy(o, ifr.ifr_hwaddr.sa_data, 6);
  #endif

  return e;
}

int32_t _getDNS(uint8_t* o, int32_t* count)
{
  int32_t i = 0;
  int32_t k = 0;
  int32_t e = 0;
  int32_t sz = 0;
  uint8_t dns[1024] = {0};
  uint8_t _info[1024] = {0};
  uint8_t _dns[1024] = {0};

  #if __DEBUG__
  printf(" %-16s:%6d | \r\n", __FUNCTION__,__LINE__);
  #endif

  #if __LINUX__
  e = _nRead(DNS_INFO, dns, &sz);

  for ( i=0 ; ; i++ )
  {
    e = get_dlmtr(dns, '\n', i, _info);
    if ( e < 0 ) break;

    if ( strncmp(_info, "nameserver", strlen("nameserver"))==0 )
    {
      for ( k=0 ; *(_info+k) ; k++)
      {
        if ( *(_info+k)=='\r' )
        {
          *(_info+k)=0;
          break;
        }
      }
      get_dlmtr(_info, ' ', 1, _dns);
      (*count) ++;

      sprintf(o, "%s ", _dns);
      o += strlen(o);
    }
  }
  #endif
  return *count;
}


int32_t _setIP(uint8_t* dname, uint8_t* o)
{
  int32_t e = 0;
  FILE* fp = 0;
  uint8_t ipv4[4] = {0};
  uint32_t _ipv4 = 0;
  uint32_t offset_base = 0;
  #if __DEBUG__
  printf(" %-16s:%6d | \r\n", __FUNCTION__,__LINE__);
  #endif

  ip_to_hex(o, ipv4);
  _ipv4 = ((ipv4[3]<<24)|(ipv4[2]<<16)|(ipv4[1]<<8)|ipv4[0]);

  if ( strncmp("wlan0", dname, strlen(dname)) == 0 )
  {
    offset_base = 32;
  }
  _writeto(EEPROM, offset_base+0, &_ipv4, sizeof(uint32_t));


  #if 0
  int32_t fd = 0;
  uint8_t ipv4[4] = {0};
  uint32_t _ipv4 = 0;
  uint32_t* p = 0;
  uint32_t k = 0;

  #if __LINUX__
  struct ifreq ifr = {0};
  struct sockaddr_in* addr = 0;

  fd = socket(AF_INET,SOCK_DGRAM, 0);
  ifr.ifr_addr.sa_family = AF_INET;
  memcpy(ifr.ifr_name, dname, IFNAMSIZ-1);

  addr = (struct sockaddr_in*)&ifr.ifr_addr;

  ip_to_hex(o, ipv4);

  _ipv4 = ((ipv4[3]<<24)|(ipv4[2]<<16)|(ipv4[1]<<8)|ipv4[0]);
  //addr->sin_addr = ((ipv4[3]<<24)|(ipv4[2]<<16)|(ipv4[1]<<8)|ipv4[0]);

  memcpy(&addr->sin_addr, &_ipv4, sizeof(uint32_t));

  ioctl(fd, SIOCSIFADDR, &ifr);
  close(fd);
  #endif
  #endif

  return e;
}

int32_t _setNetmask(uint8_t* dname, uint8_t* o)
{
  int32_t e = 0;
  FILE* fp = 0;
  uint8_t ipv4[4] = {0};
  uint32_t _ipv4 = 0;
  uint32_t offset_base = 0;
  #if __DEBUG__
  printf(" %-16s:%6d | \r\n", __FUNCTION__,__LINE__);
  #endif

  ip_to_hex(o, ipv4);
  _ipv4 = ((ipv4[3]<<24)|(ipv4[2]<<16)|(ipv4[1]<<8)|ipv4[0]);

  if ( strncmp("wlan0", dname, strlen(dname)) == 0 )
  {
    offset_base = 32;
  }
  _writeto(EEPROM, offset_base+4, &_ipv4, sizeof(uint32_t));

  return 0;
}

int32_t _setGateway(uint8_t* dname, uint8_t* o)
{
  int32_t e = 0;
  FILE* fp = 0;
  uint8_t ipv4[4] = {0};
  uint32_t _ipv4 = 0;
  uint32_t offset_base = 0;
  #if __DEBUG__
  printf(" %-16s:%6d | \r\n", __FUNCTION__,__LINE__);
  #endif

  ip_to_hex(o, ipv4);
  _ipv4 = ((ipv4[3]<<24)|(ipv4[2]<<16)|(ipv4[1]<<8)|ipv4[0]);

  if ( strncmp("wlan0", dname, strlen(dname)) == 0 )
  {
    offset_base = 32;
  }
  _writeto(EEPROM, offset_base+8, &_ipv4, sizeof(uint32_t));
  return 0;
}
int32_t _setMAC(uint8_t* dname, uint8_t* o)
{
  int32_t e = 0;
  FILE* fp = 0;
  uint8_t mac[6] = {0};
  uint32_t offset_base = 0;
  #if __DEBUG__
  printf(" %-16s:%6d | \r\n", __FUNCTION__,__LINE__);
  #endif

  stoh(o, ":", mac); 

  if ( strncmp("wlan0", dname, strlen(dname)) == 0 )
  {
    offset_base = 32;
  }
  _writeto(EEPROM, offset_base+12, mac, sizeof(uint8_t)*6);
  return 0;
}




int32_t _setDNS(uint8_t* o, int32_t* cnt)
{
  int32_t e = 0;
  FILE* fp = 0;
  uint8_t ipv4[4] = {0};
  uint32_t _ipv4 = 0;

  //ip_to_hex(o, ipv4);
  //_ipv4 = ((ipv4[3]<<24)|(ipv4[2]<<16)|(ipv4[1]<<8)|ipv4[0]);

  //_writeto(EEPROM, 0, &_ipv4, sizeof(uint32_t));
  return 0;
}


int32_t _getStatus(uint8_t* dn)
{
  int32_t e = 0;
  int32_t fd = 0;

  #if __LINUX__
  struct ifreq ifr = {0};
  #if __DEBUG__
  printf(" %-16s:%6d | \r\n", __FUNCTION__,__LINE__);
  #endif

  fd = socket(AF_INET,SOCK_DGRAM, 0);
  ifr.ifr_addr.sa_family = AF_INET;
  memcpy(ifr.ifr_name, dn, IFNAMSIZ-1);

  ioctl(fd, SIOCGIFFLAGS, &ifr);
  close(fd);

  e = ifr.ifr_flags&IFF_UP;

  #endif
  return e;
}

int32_t _setStatus(uint8_t* dn, uint8_t sts)
{
  int32_t e = 0;
  int32_t fd = 0;

  #if __LINUX__
  struct ifreq ifr = {0};
  #if __DEBUG__
  printf(" %-16s:%6d | \r\n", __FUNCTION__,__LINE__);
  #endif

  fd = socket(AF_INET,SOCK_DGRAM, 0);
  ifr.ifr_addr.sa_family = AF_INET;
  memcpy(ifr.ifr_name, dn, IFNAMSIZ-1);
  if ( sts ) ifr.ifr_flags |= IFF_UP;
  else ifr.ifr_flags &= ~IFF_UP;

  ioctl(fd, SIOCSIFFLAGS, &ifr);
  close(fd);

  #endif
  return e;
}

int32_t _getType(uint8_t* dn, uint8_t flags)
{
  int32_t e = 0;
  int32_t fd = 0;

  #if __LINUX__
  struct ifreq ifr = {0};
  #if __DEBUG__
  printf(" %-16s:%6d | \r\n", __FUNCTION__,__LINE__);
  #endif

  fd = socket(AF_INET,SOCK_DGRAM, 0);
  ifr.ifr_addr.sa_family = AF_INET;
  memcpy(ifr.ifr_name, dn, IFNAMSIZ-1);

  ioctl(fd, SIOCGIFFLAGS, &ifr);
  close(fd);

  e = ifr.ifr_flags&flags;

  #endif
  return e;
}


int32_t _scanAP(uint8_t* dn)
{
  int32_t e = 0;
  int32_t fd = 0;

  #if __LINUX__
  struct iwreq iwr = {0};
  #if __DEBUG__
  printf(" %-16s:%6d | \r\n", __FUNCTION__,__LINE__);
  #endif

  fd = socket(AF_INET,SOCK_DGRAM, 0);
  memcpy(iwr.ifr_name, dn, IFNAMSIZ-1);

  iwr.u.data.pointer = 0;
  iwr.u.data.flags = 0;
  iwr.u.data.length = 0;

  ioctl(fd, SIOCSIWSCAN, &iwr);

  // creat thread and callback

  close(fd);

  #endif
  return e;
}

int32_t _getSSID(uint8_t* dn, uint8_t* ssid)
{
  int32_t e = 0;
  int32_t fd = 0;

  #if __LINUX__
  struct iwreq iwr = {0};
  #if __DEBUG__
  printf(" %-16s:%6d | \r\n", __FUNCTION__,__LINE__);
  #endif

  fd = socket(AF_INET,SOCK_DGRAM, 0);
  memcpy(iwr.ifr_name, dn, IFNAMSIZ-1);

  //id = (int8_t*)calloc(sizeof(int8_t), IW_ESSID_MAX_SIZE);
  iwr.u.essid.pointer = ssid;
  iwr.u.essid.length = IW_ESSID_MAX_SIZE+1;

  ioctl(fd, SIOCGIWESSID, &iwr);
  close(fd);

  //free(id);

  #endif
  return e;
}

int32_t _getPassPhrase(uint8_t* dn, uint8_t* o)
{
  int32_t e = 0;
  int32_t i = 0;
  int32_t s = 4096;
  int32_t wstr[4096] = {0};
  uint8_t v[32][256]={0};
  uint8_t* p = 0;
  uint8_t* po = 0;
  #if __DEBUG__
  printf(" %-16s:%6d | \r\n", __FUNCTION__,__LINE__);
  #endif

  e = _readfrom(WIFI_NETWORK, 0, wstr, &s);
  if ( e < 0 ) return -1;

  for ( i=0; ; i++)
  {
    e = get_dlmtr(wstr, '\n', i, v[0]);
    if ( e > 0 )
    {
      p = v[0];
      for( ; *p==' ' || *p=='\t' ; p++); //FF

      e = get_dlmtr(p, '=', 0, v[1]);
      if ( strcompare("psk", v[1]) == 0 )
      {
        e = get_dlmtr(p, '=', 1, v[2]);
        po = v[2];
        for( ;*po=='\"';po++);
        for( ;*po!='\"';po++,o++) *o=*po;
        *o = 0;
        break;
      }
      else if ( strcompare("wep_key0", v[1]) == 0 )
      {
        e = get_dlmtr(p, '=', 1, v[2]);
        po = v[2];
        for( ;*po=='\"';po++);
        for( ;*po!='\"';po++,o++) *o=*po;
        *o = 0;
        break;
      }
    }
    else if ( e < 0 )
    {
      e = i;
      break;
    }
  }
  return e;
}



int32_t writeNetworkInfo(uint8_t* dname, uint8_t* ip, uint8_t* netmask, uint8_t* routers, uint8_t* dns)
{
  //FILE* fp = fopen(CUSTOM_NETWORK, "w");
  //uint8_t buf[8192] = {0};
  //int32_t sz = 0;
  //int32_t s = 0;
  //int32_t e = 0;
  //uint8_t nm[4] = {0};

  //ip_to_hex(netmask, nm);

  //s = _nRead(BASIC_NETWORK, buf,&sz);
  //if ( s > 0 )
  //{
  //  for ( ; ; )
  //  {
  //    e = fwrite(buf, 1, s, fp);
  //    e -= s;
  //    if ( e<= 0 ) break;
  //    s -= e;
  //  }
  //}
  //sprintf(buf,
  //        "\r\n"
  //        "interface %s\r\n"
  //        "static ip_address=%s/%d\r\n"
  //        "static routers=%s\r\n"
  //        "static domain_name_servers=%s\r\n",
  //        dname,
  //        ip,
  //        netmask_prefix(nm),
  //        routers,
  //        dns
  //);
  //fwrite(buf, 1, strlen(buf), fp);

  //fclose(fp);

  return 0;
}


int32_t _readNetworkInfo(int8_t* dn, int32_t fd, int8_t* uri, int32_t (*f)(void*,int32_t,int8_t*,int32_t,void*,void*),void* o)
{
  int32_t e = 0;
  int32_t i = 0;
  uint8_t _dhcp = 0;
  uint8_t ip[32] = {0};
  uint8_t gw[32] = {0};
  uint8_t nm[32] = {0};
  uint8_t dns[4][32] = {0};
  int32_t dcount = 0;
  uint8_t _ip[5] = {0};
  uint8_t _gw[5] = {0};
  uint8_t _nm[5] = {0};
  uint8_t _dns[4][5] = {0};
  uint8_t _mac[7] = {0};
  uint8_t buf[4096] = {0};
  uint8_t v[128][32] = {0};
  int32_t sz = 0;
  uint8_t _sts = 0;
  uint8_t _ssid[1024] = {0};
  uint8_t _auth[1024] = {0};
  uint8_t _pass[1024] = {0};

  #if __DEBUG__
  printf(" %-16s:%6d | \r\n", __FUNCTION__,__LINE__);
  #endif

  _dhcp = _checkDHCP(dn);
  _sts = _getStatus(dn);


  if ( _dhcp == 0)
  {
    e = _getEEPROM(dn, "ip_address", v[0], &sz);
    //printf("%12s:%8d -> %s\r\n", __FUNCTION__,__LINE__, v[0]);
    get_dlmtr(v[0], '/', 0, ip);
    get_dlmtr(v[0], '/', 1, v[1]);
    //printf("%12s:%8d -> %s\r\n", __FUNCTION__,__LINE__, v[1]);
    stoh(ip, ".", _ip);
    netmask_convert(atoi(v[1]), _nm);

    e = _getEEPROM(dn, "routers", gw, &sz);
    //printf("%12s:%8d -> %s\r\n", __FUNCTION__,__LINE__,gw);
    //print_buffer("gw", gw, strlen(gw));
    stoh(gw, ".", _gw);
    //printf("%12s:%8d -> %s\r\n", __FUNCTION__,__LINE__, gw);

    e = _getEEPROM(dn, "domain_name_servers", v[2], &sz);
    //printf("%12s:%8d -> %s\r\n", __FUNCTION__,__LINE__, v[2]);
    get_dlmtr(v[2], ' ', 0, dns[0]);
    get_dlmtr(v[2], ' ', 1, dns[1]);
    stoh(dns[0], ".", _dns[0]);
    stoh(dns[1], ".", _dns[1]);
    //printf("%12s:%8d -> %s %s\r\n", __FUNCTION__,__LINE__, dns[0], dns[1]);
  }
  else
  {
    _getIP(dn, ip);
    stoh(ip, ".", _ip);
    _getNetmask(dn, nm);
    stoh(nm, ".", _nm);
    _getGateway(dn, gw);
    stoh(gw, ".", _gw);
    _getDNS(v[0], &dcount);
    get_dlmtr(v[0], ' ', 0, dns[0]);
    get_dlmtr(v[0], ' ', 1, dns[1]);
    stoh(dns[0], ".", _dns[0]);
    stoh(dns[1], ".", _dns[1]);
  }



  sprintf(buf,
                "<div class='guide' style='width:100%%;height:%dpx;'>"
                  "<div class='guide text bold' style='width:100%%;height:22px;'>"
                    "<div class='guide VBLANK' style='width:80px;'>&nbsp</div>"
                    "<div class='guide' style='float:right;width:90px;height:%s;'>"
                      "<select name='device_enabled' class='guide text inputtext' style='width:100%%;height:100%%;'>"
                        "<option value='0' %s>DISABLED</option>"
                        "<option value='1' %s>ENABLED</option>"
                      "</select>"
                    "</div>"
                    "<div class='guide VBLANK' style='float:right;width:20px;'>&nbsp</div>"
                    "<div class='guide' style='float:right;width:80px;height:%s;'>"
                      "<select name='dhcp_enabled' class='guide text inputtext' style='width:100%%;height:100%%;'>"
                        "<option value='0' %s>STATIC</option>"
                        "<option value='1' %s>DHCP</option>"
                      "</select>"
                    "</div>"
                    "<div class='guide VBLANK' style='float:right;width:80px;'>&nbsp</div>"
                  "</div>"
                  "<div class='guide HLINE'></div>"
                  ,GUIDE_BOTTOM
                  ,"16px",_sts==0?"selected":"",_sts==1?"selected":""
                  ,"16px",_dhcp==0?"selected":"",_dhcp==1?"selected":""
  );
  if ( *f ) f(o, fd, buf, strlen(buf), 0, o);

  if ( strcompare(dn, "wlan0") == 0 )
  {
    _getSSID("wlan0", _ssid);

    sprintf(buf,
                    "<div class='guide text bold' style='width:%s;height:%s;'>"
                      "SSID"
                    "</div>"
                    "<div class='guide' style='width:%s;height:%s;'>"
                      "<input type=text name=ssid class='guide text inputtext' id=ssid style='width:%s;height:%s;' value=%s></input>"
                    "</div>"
                    "<div class='guide HLINE'></div>"
            ,TWIDTH_00,THEIGHT,TWIDTH_01,THEIGHT
            ,"200px",HEIGHT,_ssid
    );
    if ( *f ) f(o, fd, buf, strlen(buf), 0, o);

    sprintf(buf,
                    "<div class='guide text bold' style='width:%s;height:%s;'>"
                      "authentication"
                    "</div>"
                    "<div class='guide' style='width:%s;height:%s;'>"
                      "<div class='guide' style='width:%s;height:%s;'>"
                        "<select name='auth' class='guide text inputtext' style='width:100%%;height:100%%;'>"
                          "<option value='0' %s>WPA2PSK + AES</option>"
                          "<option value='1' %s>WPAPSK/WPA2PSK + AES</option>"
                          "<option value='2' %s>WPAPSK + AES</option>"
                          "<option value='3' %s>WPA2PSK + TKIP/AES</option>"
                          "<option value='4' %s>WPAPSK/WPA2PSK + TKIP/AES</option>"
                          "<option value='5' %s>WPAPSK + TKIP/AES</option>"
                          "<option value='6' %s>WPAPSK + TKIP</option>"
                          "<option value='7' %s>WPA2PSK + TKIP</option>"
                          "<option value='8' %s>WPAPSK/WPA2PSK + TKIP</option>"
                          "<option value='9' %s>AUTO + WEP</option>"
                          "<option value='A' %s>OPEN + WEP</option>"
                          "<option value='B' %s>SHARE + WEP</option>"
                        "</select>"
                      "</div>"
                    "</div>"
                    "<div class='guide HLINE'></div>"
            ,TWIDTH_00,THEIGHT,TWIDTH_01,THEIGHT
            ,"200px",HEIGHT
            ,_auth=='0'?"selected":""
            ,_auth=='1'?"selected":""
            ,_auth=='2'?"selected":""
            ,_auth=='3'?"selected":""
            ,_auth=='4'?"selected":""
            ,_auth=='5'?"selected":""
            ,_auth=='6'?"selected":""
            ,_auth=='7'?"selected":""
            ,_auth=='8'?"selected":""
            ,_auth=='9'?"selected":""
            ,_auth=='A'?"selected":""
            ,_auth=='B'?"selected":""
    );
    if ( *f ) f(o, fd, buf, strlen(buf), 0, o);

    _getPassPhrase(dn, _pass);
    sprintf(buf,
                    "<div class='guide text bold' style='width:%s;height:%s;'>"
                      "passphrase"
                    "</div>"
                    "<div class='guide' style='width:%s;height:%s;'>"
                      "<input type=text name=passphrase class='guide text inputtext' id=passphrase style='width:%s;height:%s;' value='%s'></input>"
                    "</div>"
                    "<div class='guide HLINE'></div>"
            ,TWIDTH_00,THEIGHT,TWIDTH_01,THEIGHT
            ,"200px",HEIGHT
            ,_pass
    );
    if ( *f ) f(o, fd, buf, strlen(buf), 0, o);
  }

  sprintf(buf,
                  "<div class='guide text bold' style='width:%s;height:%s;'>"
                    "IP"
                  "</div>"
                  "<div class='guide' style='width:%s;height:%s;'>"
                    "<input type=text name=ip0 class='guide text inputtext' id=ip0 style='width:%s;height:%s;' value=%d></input>"
                    "<div class='guide text'>.</div>"
                    "<input type=text name=ip1 class='guide text inputtext' id=ip1 style='width:%s;height:%s;' value=%d></input>"
                    "<div class='guide text'>.</div>"
                    "<input type=text name=ip2 class='guide text inputtext' id=ip2 style='width:%s;height:%s;' value=%d></input>"
                    "<div class='guide text'>.</div>"
                    "<input type=text name=ip3 class='guide text inputtext' id=ip3 style='width:%s;height:%s;' value=%d></input>"
                  "</div>"
                  "<div class='guide HLINE'></div>"
          ,TWIDTH_00,THEIGHT,TWIDTH_01,THEIGHT
          ,WIDTH,HEIGHT,_ip[0],WIDTH,HEIGHT,_ip[1],WIDTH,HEIGHT,_ip[2],WIDTH,HEIGHT,_ip[3]
  );
  if ( *f ) f(o, fd, buf, strlen(buf), 0, o);

  sprintf(buf,
                  "<div class='guide text bold' style='width:%s;height:%s;'>"
                    "Netmask"
                  "</div>"
                  "<div class='guide' style='width:%s;height:%s;'>"
                    "<input type=text name=nm0 class='guide text inputtext' id=nm0 style='width:%s;height:%s;' value=%d></input>"
                    "<div class='guide text'>.</div>"
                    "<input type=text name=nm1 class='guide text inputtext' id=nm1 style='width:%s;height:%s;' value=%d></input>"
                    "<div class='guide text'>.</div>"
                    "<input type=text name=nm2 class='guide text inputtext' id=nm2 style='width:%s;height:%s;' value=%d></input>"
                    "<div class='guide text'>.</div>"
                    "<input type=text name=nm3 class='guide text inputtext' id=nm3 style='width:%s;height:%s;' value=%d></input>"
                  "</div>"
                  "<div class='guide HLINE'></div>"
          ,TWIDTH_00,THEIGHT,TWIDTH_01,THEIGHT
          ,WIDTH,HEIGHT,_nm[0],WIDTH,HEIGHT,_nm[1],WIDTH,HEIGHT,_nm[2],WIDTH,HEIGHT,_nm[3]
  );
  if ( *f ) f(o, fd, buf, strlen(buf), 0, o);

  sprintf(buf,
                  "<div class='guide text bold' style='width:%s;height:%s;'>"
                    "Gateway"
                  "</div>"
                  "<div class='guide' style='width:%s;height:%s;'>"
                    "<input type=text name=gw0 class='guide text inputtext' id=gw0 style='width:%s;height:%s;' value=%d></input>"
                    "<div class='guide text'>.</div>"
                    "<input type=text name=gw1 class='guide text inputtext' id=gw1 style='width:%s;height:%s;' value=%d></input>"
                    "<div class='guide text'>.</div>"
                    "<input type=text name=gw2 class='guide text inputtext' id=gw2 style='width:%s;height:%s;' value=%d></input>"
                    "<div class='guide text'>.</div>"
                    "<input type=text name=gw3 class='guide text inputtext' id=gw3 style='width:%s;height:%s;' value=%d></input>"
                  "</div>"
                  "<div class='guide HLINE'></div>"
          ,TWIDTH_00,THEIGHT,TWIDTH_01,THEIGHT
          ,WIDTH,HEIGHT,_gw[0],WIDTH,HEIGHT,_gw[1],WIDTH,HEIGHT,_gw[2],WIDTH,HEIGHT,_gw[3]
  );
  if ( *f ) f(o, fd, buf, strlen(buf), 0, o);


  #if 0
  sprintf(buf,
                  "<div class='guide text bold' style='width:%s;height:20px;'>"
                    "MAC"
                  "</div>"
                  "<div class='guide' style='width:%s;height:20px;'>"
                    "<input type=text name=mac0 class='guide text inputtext' id=mac0 style='width:%s;height:%s;' value=%02X></input>"
                    "<div class='guide text'>:</div>"
                    "<input type=text name=mac1 class='guide text inputtext' id=mac1 style='width:%s;height:%s;' value=%02X></input>"
                    "<div class='guide text'>:</div>"
                    "<input type=text name=mac2 class='guide text inputtext' id=mac2 style='width:%s;height:%s;' value=%02X></input>"
                    "<div class='guide text'>:</div>"
                    "<input type=text name=mac3 class='guide text inputtext' id=mac3 style='width:%s;height:%s;' value=%02X></input>"
                    "<div class='guide text'>:</div>"
                    "<input type=text name=mac4 class='guide text inputtext' id=mac4 style='width:%s;height:%s;' value=%02X></input>"
                    "<div class='guide text'>:</div>"
                    "<input type=text name=mac5 class='guide text inputtext' id=mac5 style='width:%s;height:%s;' value=%02X></input>"
                  "</div>"
                  "<div class='guide HLINE'></div>"
          ,TWIDTH_00,TWIDTH_01
          ,WIDTH,HEIGHT,mac[0]
          ,WIDTH,HEIGHT,mac[1]
          ,WIDTH,HEIGHT,mac[2]
          ,WIDTH,HEIGHT,mac[3]
          ,WIDTH,HEIGHT,mac[4]
          ,WIDTH,HEIGHT,mac[5]
  );
  if ( *f ) f(o, fd, buf, strlen(buf), 0, o);
  #endif


  sprintf(buf,
                  "<div class='guide text bold' style='width:%s;height:60px;'>"
                    "DNS"
                  "</div>"
                  "<div class='guide' style='width:%s;height:60px;'>"
          ,TWIDTH_00,TWIDTH_01
  );
  if ( *f ) f(o, fd, buf, strlen(buf), 0, o);



  for ( i=0 ; i<2 ; i++ )
  {
    //get_dlmtr(dns, ':', i, _dns);
    //ip_to_hex(_dns, _ip);

    sprintf(buf,
                    "<div class='guide' style='width:100%%;height:%s;'>"
                      "<input type=text name=dns%d0 class='guide text inputtext' id=dns%d0 style='width:%s;height:%s;' value=%d></input>"
                      "<div class='guide text'>.</div>"
                      "<input type=text name=dns%d1 class='guide text inputtext' id=dns%d1 style='width:%s;height:%s;' value=%d></input>"
                      "<div class='guide text'>.</div>"
                      "<input type=text name=dns%d2 class='guide text inputtext' id=dns%d2 style='width:%s;height:%s;' value=%d></input>"
                      "<div class='guide text'>.</div>"
                      "<input type=text name=dns%d3 class='guide text inputtext' id=dns%d3 style='width:%s;height:%s;' value=%d></input>"
                    "</div>"
                    "<div class='guide HLINE'></div>"
          ,THEIGHT
          ,i,i,WIDTH,HEIGHT,_dns[i][0],i,i,WIDTH,HEIGHT,_dns[i][1],i,i,WIDTH,HEIGHT,_dns[i][2],i,i,WIDTH,HEIGHT,_dns[i][3]
    );
    if ( *f ) f(o, fd, buf, strlen(buf), 0, o);
  }

  sprintf(buf,
                  "</div>"
                "</div>"
  );
  if ( *f ) f(o, fd, buf, strlen(buf), 0, o);

  return 200;
}

int32_t _updateWiFiInfo(int8_t* dn, int8_t*uri)
{
  int32_t e = 0;
  uint8_t ssid[256] = {0};
  uint8_t auth = 0;
  uint8_t pass[256] = {0};
  uint8_t wstr[4096] = {0};
  uint8_t _pass[1024] = {0};

  #if __DEBUG__
  printf(" %-16s:%6d | \r\n", __FUNCTION__,__LINE__);
  #endif

  //printf("uri ---> %s\r\n", uri);


  if ( strcompare(dn, "wlan0") == 0 )
  {

    e = _get_keyvalue(uri, "auth", &auth);
    e = _get_keyvalue(uri, "passphrase", pass);
    e = _get_keyvalue(uri, "ssid", ssid);

    //printf("%s %c %s\r\n", ssid, auth, pass);


    if ( auth=='0' )
    {
      sprintf(_pass, "psk=\"%s\"", pass);
    }
    else if ( auth=='9' || auth=='A' || auth=='B' )
    {
      sprintf(_pass, "wep_key0=\"%s\"", pass);
    }
    else
    {
      sprintf(_pass, "psk=\"%s\"", pass);
    }

    sprintf(wstr,
            "ctrl_interface=DIR=/var/run/wpa_supplicant GROUP=netdev\n"
            "update_config=1\n"
            "country=KR\n\n"
            "network={\n"
            "\tssid=\"%s\"\n"
            "\t%s\n"
            "}"
            ,ssid
            ,_pass
    );
    _writeto(WIFI_NETWORK, 0, wstr, strlen(wstr));
  }
  return e;
}

int32_t _updateNetworkInfo(int8_t* dnames)
{
  int32_t e = 0;
  int32_t i = 0;
  uint8_t wstr[4096] = {0};
  int32_t sz = 4096;
  uint8_t fname[256] = {0};
  uint8_t tmp[1024] = {0};
  #if __DEBUG__
  printf(" %-16s:%6d | \r\n", __FUNCTION__,__LINE__);
  #endif

  sprintf(fname, "%s/.%s", EEPROM, "dhcpcd.conf");
  e = _readfrom(fname, 0, wstr, &sz);

  _writeto(CUSTOM_NETWORK, 0, wstr, strlen(wstr));

  for ( i=0 ; ; i++ )
  {
    e = get_dlmtr(dnames, '\n', i, tmp);
    if ( e < 0 ) break;

    #if __LINUX__
    if ( _getType(tmp, IFF_LOOPBACK) == 0 )
    {
      sprintf(fname, "%s/.%s", EEPROM, tmp);
      e = _readfrom(fname, 0, wstr, &sz);
  
      e = _appendto(CUSTOM_NETWORK, 0, wstr, strlen(wstr));
    }
    #endif
  }

  return e;
}

int32_t _writeNetworkInfo(int8_t* dn, int32_t fd, int8_t* uri, int32_t (*f)(void*,int32_t,int8_t*,int32_t,void*,void*),void* o)
{
  int32_t e = 0;
  int32_t i = 0;
  uint8_t tmp[64] = {0};
  uint8_t v[32][64] = {0};
  uint8_t ip[4] = {0};
  uint8_t nm[4] = {0};
  uint8_t gw[4] = {0};
  uint8_t mac[6] = {0};
  uint8_t dns[4][4] = {0};
  int32_t dcount = 0;
  uint8_t dhcp = 0;
  uint8_t sts = 0;
  uint8_t str[64] = {0};
  uint8_t wstr[4096] = {0};
  int32_t wstrp = 0;
  uint8_t fname[256] = {0};

  #if __LINUX__
  struct stat st = {0};
  if (stat(EEPROM, &st) == -1) mkdir(EEPROM, 0755);
  #endif
  #if __DEBUG__
  printf(" %-16s:%6d | \r\n", __FUNCTION__,__LINE__);
  #endif

  e = _get_keyvalue(uri, "dhcp_enabled", &dhcp);
  if ( dhcp == '1' )
  {
    sprintf(&wstr[wstrp], "#");
    wstrp = strlen(wstr);
  }
  sprintf(&wstr[wstrp], "interface %s\n", dn);
  wstrp = strlen(wstr);


  e = _get_keyvalue(uri, "ip0", v[0]);
  e = _get_keyvalue(uri, "ip1", v[1]);
  e = _get_keyvalue(uri, "ip2", v[2]);
  e = _get_keyvalue(uri, "ip3", v[3]);
  e = _get_keyvalue(uri, "nm0", v[4]);
  e = _get_keyvalue(uri, "nm1", v[5]);
  e = _get_keyvalue(uri, "nm2", v[6]);
  e = _get_keyvalue(uri, "nm3", v[7]);
  nm[0] = atoi(v[4]);
  nm[1] = atoi(v[5]);
  nm[2] = atoi(v[6]);
  nm[3] = atoi(v[7]);
  sprintf(str, "%s.%s.%s.%s/%d", v[0], v[1], v[2], v[3], netmask_prefix(nm));
  if ( dhcp == '1' )
  {
    sprintf(&wstr[wstrp], "#");
    wstrp = strlen(wstr);
  }
  sprintf(&wstr[wstrp], "static ip_address=%s\n", str);
  wstrp = strlen(wstr);

  e = _get_keyvalue(uri, "gw0", v[0]);
  e = _get_keyvalue(uri, "gw1", v[1]);
  e = _get_keyvalue(uri, "gw2", v[2]);
  e = _get_keyvalue(uri, "gw3", v[3]);
  sprintf(str, "%s.%s.%s.%s", v[0], v[1], v[2], v[3]);
  if ( dhcp == '1' )
  {
    sprintf(&wstr[wstrp], "#");
    wstrp = strlen(wstr);
  }
  sprintf(&wstr[wstrp], "static routers=%s\n", str);
  wstrp = strlen(wstr);

  e = _get_keyvalue(uri, "mac0", v[0]);
  e = _get_keyvalue(uri, "mac1", v[1]);
  e = _get_keyvalue(uri, "mac2", v[2]);
  e = _get_keyvalue(uri, "mac3", v[3]);
  e = _get_keyvalue(uri, "mac4", v[4]);
  e = _get_keyvalue(uri, "mac5", v[5]);
  sprintf(str, "%s:%s:%s:%s:%s:%s", v[0], v[1], v[2], v[3], v[4], v[5]);

  for ( i=0 ; i<4 ; i++ )
  {
    sprintf(tmp, "dns%d0", i);
    e = _get_keyvalue(uri, tmp, v[0]); if ( e < 0 ) break;
    sprintf(tmp, "dns%d1", i);  
    e = _get_keyvalue(uri, tmp, v[1]);
    sprintf(tmp, "dns%d2", i);  
    e = _get_keyvalue(uri, tmp, v[2]);
    sprintf(tmp, "dns%d3", i);  
    e = _get_keyvalue(uri, tmp, v[3]);

    //printf("\r\n\r\n\r\n\r\n%s.%s.%s.%s\r\n\r\n", v[0], v[1], v[2], v[3]);

    dns[i][0] = atoi(v[0]);
    dns[i][1] = atoi(v[1]);
    dns[i][2] = atoi(v[2]);
    dns[i][3] = atoi(v[3]);
  }
  dcount = i;
  if ( dhcp == '1' )
  {
    sprintf(&wstr[wstrp], "#");
    wstrp = strlen(wstr);
  }
  sprintf(&wstr[wstrp], "static domain_name_servers=");
  wstrp = strlen(wstr);

  for ( i=0 ; i<dcount ; i++ )
  {
    sprintf(&wstr[wstrp], "%d.%d.%d.%d ", dns[i][0],dns[i][1],dns[i][2],dns[i][3]);
    wstrp = strlen(wstr);
  }
  sprintf(&wstr[wstrp], "\n");


  //printf("\r\n================================================================================\r\n%s\r\n", wstr);

  #if __DEBUG__
  printf(" %-16s:%6d | %s %s\r\n", __FUNCTION__,__LINE__, EEPROM, dn);
  #endif
  sprintf(fname, "%s/.%s", EEPROM, dn);
  #if __DEBUG__
  printf(" %-16s:%6d | %s\r\n", __FUNCTION__,__LINE__, fname);
  #endif
  _writeto(fname, 0, wstr, strlen(wstr));
  #if __DEBUG__
  printf(" %-16s:%6d | \r\n", __FUNCTION__,__LINE__);
  #endif

  if ( strcompare(dn, "eth0") != 0 )
  {
    e = _get_keyvalue(uri, "device_enabled", &sts);
    _setStatus(dn, sts-0x30);
  }
  #if __DEBUG__
  printf(" %-16s:%6d | \r\n", __FUNCTION__,__LINE__);
  #endif

  return 200;
}

int32_t _writeHTMLHeader(int32_t fd, int32_t (*f)(void*,int32_t,int8_t*,int32_t,void*,void*),void* o)
{
  int32_t e = 0;
  uint8_t buf[4096] = {0};

  sprintf(buf,
          "<!DOCTYPE HTML>"
          "<HTML>"
            "<HEAD>"
              "<meta http-equiv='Content-Type' content='text/html; charset=UTF-8' />"
              "<TITLE>Network Setup</TITLE>"
//              "<link type='text/css' href='index.css' rel='stylesheet' media='screen' />"
              "<script>"
                "function doSubmit(v) {"
                  "document.ninfo.mode.value = v;"
                  "document.ninfo.submit();"
                "}"
              "</script>"
            "</HEAD>"
            "<style>"
            ".guide {float:left;position:relative;}"
            ".HBLANK{background-color:transparent;width:100%%;height:1px;}"
            ".VBLANK{background-color:transparent;width:1px;height:100%%;}"
            ".HLINE{background-color:#999999;width:100%%;height:1px;}"
            ".VLINE{background-color:#999999;width:1px;height:100%%;}"
            ".text{font-family:courier new;font-size:0.7em;}"
            ".bold{font-weight:700;}"
            ".inputtext{text-align:center;display:inline-block;font-size:0.7em;background-color:#EFEFEF;}"
            ".inputbutton{text-align:center;display:inline-block;background-color:#EFEFEF;width:100px;height:100%%;border-radius:8px;}"
            ".mitem{cursor:pointer;}"
            "</style>"
            );
  if ( *f ) f(o, fd, buf, strlen(buf), 'H', o);


  return e;
}

struct stNetworkKeyValue
{
  uint8_t ip[4];
  uint8_t nm[4];
  uint8_t gw[4];
  uint8_t mac[6];
  uint8_t dns[4][4];
  uint8_t dhcp;
  uint8_t ssid[256];
  uint8_t pass[256];
  uint8_t auth;
};

int32_t _getNetworkKeyValue(int8_t* uri, struct stNetworkKeyValue* p)
{
  int32_t e = 0;
  int32_t i = 0;
  uint8_t tmp[32] = {0};
  uint8_t v[16][32] = {0};
  #if __DEBUG__
  printf(" %-16s:%6d | \r\n", __FUNCTION__,__LINE__);
  #endif


  _get_keyvalue(uri, "ssid", p->ssid);
  _get_keyvalue(uri, "passphrase", p->pass);
  _get_keyvalue(uri, "auth", &p->auth);

  e = _get_keyvalue(uri, "dhcp_enabled", &p->dhcp);
  if ( e < 0 ) return 0xEFFFFFFF;
  e = _get_keyvalue(uri, "ip0", v[0]);
  e = _get_keyvalue(uri, "ip1", v[1]);
  e = _get_keyvalue(uri, "ip2", v[2]);
  e = _get_keyvalue(uri, "ip3", v[3]);
  p->ip[0] = atoi(v[0]);
  p->ip[1] = atoi(v[1]);
  p->ip[2] = atoi(v[2]);
  p->ip[3] = atoi(v[3]);
  e = _get_keyvalue(uri, "nm0", v[4]);
  e = _get_keyvalue(uri, "nm1", v[5]);
  e = _get_keyvalue(uri, "nm2", v[6]);
  e = _get_keyvalue(uri, "nm3", v[7]);
  p->nm[0] = atoi(v[4]);
  p->nm[1] = atoi(v[5]);
  p->nm[2] = atoi(v[6]);
  p->nm[3] = atoi(v[7]);
  e = _get_keyvalue(uri, "gw0", v[0]);
  e = _get_keyvalue(uri, "gw1", v[1]);
  e = _get_keyvalue(uri, "gw2", v[2]);
  e = _get_keyvalue(uri, "gw3", v[3]);
  p->gw[0] = atoi(v[0]);
  p->gw[1] = atoi(v[1]);
  p->gw[2] = atoi(v[2]);
  p->gw[3] = atoi(v[3]);
  e = _get_keyvalue(uri, "mac0", v[0]);
  e = _get_keyvalue(uri, "mac1", v[1]);
  e = _get_keyvalue(uri, "mac2", v[2]);
  e = _get_keyvalue(uri, "mac3", v[3]);
  e = _get_keyvalue(uri, "mac4", v[4]);
  e = _get_keyvalue(uri, "mac5", v[5]);
  p->mac[0] = HSTR_TO_HEX(v[0]);
  p->mac[1] = HSTR_TO_HEX(v[1]);
  p->mac[2] = HSTR_TO_HEX(v[2]);
  p->mac[3] = HSTR_TO_HEX(v[3]);
  p->mac[4] = HSTR_TO_HEX(v[4]);
  p->mac[5] = HSTR_TO_HEX(v[5]);

  for ( i=0 ; i<4 ; i++ )
  {
    sprintf(tmp, "dns%d0", i);
    e = _get_keyvalue(uri, tmp, v[0]); if ( e < 0 ) break;
    sprintf(tmp, "dns%d1", i);  
    e = _get_keyvalue(uri, tmp, v[1]);
    sprintf(tmp, "dns%d2", i);  
    e = _get_keyvalue(uri, tmp, v[2]);
    sprintf(tmp, "dns%d3", i);  
    e = _get_keyvalue(uri, tmp, v[3]);

    p->dns[i][0] = atoi(v[0]);
    p->dns[i][1] = atoi(v[1]);
    p->dns[i][2] = atoi(v[2]);
    p->dns[i][3] = atoi(v[3]);
  }

  return 0;
}



int32_t _writeHTMLBody(int32_t fd, int8_t* uri0, int8_t* uri1, int32_t (*f)(void*,int32_t,int8_t*,int32_t,void*,void*),void* o)
{
  struct stNetworkKeyValue nkv = {0};
  int32_t e = 0;
  uint8_t buf[4096] = {0};
  uint8_t tmp[64] = {0};
  uint8_t dn[32] = {0};
  uint8_t mode[32] = {0};
  int32_t dcount = 0;
  uint8_t str[64] = {0};
  uint8_t wstr[4096] = {0};
  int32_t wstrp = 0;
  uint8_t devices[256] = {__DEVICES__};
  uint8_t dnames[1024] = {0};
  uint8_t secret[1024] = {0};
  int32_t dnamesp = 0;
  int32_t ssid[1024] = {0};
  int32_t i = 0;
  #if __DEBUG__
  printf(" %-16s:%6d | \r\n", __FUNCTION__,__LINE__);
  #endif

  e = _get_keyvalue(uri1, "secret", secret);
  if ( secret[0] == 0 ) return -1;
  if ( strcompare(SECRET_KEY, secret) ) return -1;

  e = _get_keyvalue(uri1, "dn", dn);
  e = _get_keyvalue(uri1, "mode", mode);
  e = _get_keyvalue(uri1, "secret", secret);

  if ( dn[0] == 0 ) sprintf(dn, "eth0");

  #if __DEBUG__
  print_buffer("device name", dn, strlen(dn));
  #endif

  #ifndef __DEVICES__
  _getIFNames(devices);
  #endif
  //printf("%s\r\n", fname);

  for ( i=0 ; ; i++ )
  {
    e = get_dlmtr(devices, '\n', i, tmp);
    if ( e < 0 ) break;
    //printf("%s  ->  %d\r\n", tmp, _getType(tmp, IFF_LOOPBACK));
    #if __LINUX__
    if ( _getType(tmp, IFF_LOOPBACK) == 0 )
    {
      sprintf(&dnames[dnamesp], "<option value='%s' %s>%s</option>", tmp, dn[0]==0?"selected":strcmp(dn,tmp)==0?"selected":"", tmp);
      dnamesp += strlen(dnames);
    }
    #endif
  }

  sprintf(buf,
            "<BODY>"
              "<form name=ninfo method=post action=%s>"
              "<div class='guide' style='width:%dpx;height:%dpx;background-color:#EFEFEF;'>"
                "<div class='guide' style='width:100%%;height:%dpx;'>"
                  "<div class='guide text bold' style='width:100%%;height:%s;'>"
                    "<div class='guide' style='width:20%%;height:100%%;'>"
                      "<select name='dn' class='guide text inputtext' style='width:100%%;height:100%%;' onchange='doSubmit(\"r\");'>"
                        "%s"
                      "</select>"
                    "</div>"
                    "<div class='guide' style='width:80%%;height:100%%;'>"
                      "<input type=button value='save' class='guide bold' style='float:right;font-size:0.9em;width:64px;height:20px;background-color:#EEEEEE' onclick='doSubmit(\"w\");'></input>"
                      "<input type=hidden name='mode' value='w'></input>"
                      "<input type=hidden name='secret' value='%s'></input>"
                    "</div>"
                  "</div>"
                "</div>"
                ,uri0,GUIDE_WIDTH, GUIDE_HEIGHT, GUIDE_TOP, HEIGHT, dnames, secret
  );
  if ( *f ) f(o, fd, buf, strlen(buf), 0, o);

  if ( strncmp(mode, "w", strlen(mode)) == 0 )
  {
    if ( _getNetworkKeyValue(uri1, &nkv) >= 0 )
    {
      _writeNetworkInfo(dn, fd, uri1, f, o);
      _updateNetworkInfo(devices);
      _updateWiFiInfo(dn,uri1);
    }
  }
  _readNetworkInfo(dn, fd, uri1, f, o);
  sprintf(buf,
              "</div>"
              "</form>"
            "</BODY>"
          "</HTML>"
  );
  if ( *f ) f(o, fd, buf, strlen(buf), 0, o);


  return 200;
}


int32_t nNetworkInfo(int32_t fd, int8_t* uri0, int8_t* uri1, int32_t (*f)(void*,int32_t,int8_t*,int32_t,void*,void*),void* o)
{
  int32_t e = 0;

  _writeHTMLHeader(fd, f, o);

  e = _writeHTMLBody(fd, uri0, uri1, f, o);
  return e;
}
