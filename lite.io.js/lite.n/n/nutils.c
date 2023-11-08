#include <nutils.h>

int32_t get_pid(int8_t* pname, int32_t* pid)
{
  FILE* fp = 0;
  int8_t list[2048] = {0};
  int8_t dname[1024] = {0};
  int8_t fname[1024] = {0};
  int8_t line[1024] = {0};
  int8_t oname[1024] = {0};
  int32_t lcnt = 0;
  int32_t i = 0;
  int32_t e = 0;
  
  *pid = 0;

  e = __get_files("/proc/", "DIR", list, &lcnt);
  for ( i=0 ; i<lcnt ; i++ )
  {
    if( __get_dlmtr_str(list, ':', i, dname) > 0 )
    {
      if ( __str_to_decimal(dname) >= 0 )
      {
        sprintf(fname, "/proc/%s/status", dname);
        fp = fopen(fname, "r");
        if ( fgets(line, 1024, fp) > 0 )
        {
          if ( __get_trimstr(line, 0x09, 0x0A, oname) > 0 )
          {
            if( strncmp(pname, oname, strlen(pname)) == 0 )
            {
              *pid = atoi(dname);
              fclose(fp);
              break;
            }
          }
        }
        fclose(fp);
      }
    }
  }

  return *pid;
}

