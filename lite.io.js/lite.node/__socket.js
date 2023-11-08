///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//////                                                                   //////
//////                                                                   //////
//////                            Socket                                 //////
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
/***
class __socket
{
  this.module = null;
  this.fd = 0;
  constructor()
  {
    //this.fd = new Array();
  }

  load(pth = null)
  {
    if (pth == null ) this.module = require('liteio_socket_x86_64');
    else this.module = require(pth);
  }
  open(pth,ip,port)
  {
    load(pth);
    _ip = ip;
    _port = port;
    if ( ip == null ) _ip = "192.168.0.106";
    if ( port == null ) _port = "501";

    this.fd = this.module.open("--socket_ip " + _ip + " --socket_port " + _port + + " --socket_cstype CLIENT --socket_protocol TCP --socket_casttype UNICAST --socket_size_of_buffer 1024", this.callback);
    return this.fd;
  }

  callback(fd, buf, sz)
  {
    if ( sz <= 0 )
    {
      console.log(sz);
      return;
    }


    var str = "";
    buf.forEach(function(byte) {                
                  str += ('0' + (byte & 0xFF).toString(16)).slice(-2) + " ";
              });

    //for ( i=0 ; i<sz ; i++ ) str += String.fromCharCode(buf[i]);
    console.log('serial_callback -> ', sz ,':', str);


    //console.log("+##############################################################################+");
    //console.log("-->", arr2str(buf), ", ", sz );
    //console.log("+^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^+");
  }



  add(fd)
  {
    chk = 0;
    idx = 0;
    for ( idx=0 ; idx<fd.length ; idx++ )
    {
      if ( fd[idx] == 0 )
      {
        chk = 1;
        break;
      }
    }
    if ( chk == 0 ) fd[idx] = fd;
    return chk;
  }

  del(fd)
  {
    idx = 0;
    for ( idx=0 ; idx<fd.length ; idx++ )
    {
      if ( fd[idx] == fd )
      {
        fd[idx] = 0;
        break;
      }
    }
  }
}
***/

module.exports = {
  _module : 0,
  open : function(path,ip,port,callback)
  {
    _common = require('./__common.js');

    if (path == null ) _module = require('liteio_socket_x86_64');
    else _module = require(path);
    _ip = ip;
    _port = port;
    if ( ip == null ) _ip = "192.168.0.106";
    if ( port == null ) _port = "501";

    param  = "--socket_ip " + _ip;
    param += " --socket_port " + _port;
    param += " --socket_cstype CLIENT";
    param += " --socket_protocol TCP";
    param += " --socket_casttype UNICAST";
    param += " --socket_size_of_buffer 1024";

    console.log(param);
    //_common.sleep(1000);
    fd = _module.open(param, callback);
    return fd;
  },
  write : function(fd,buf,sz)
  {
    return _module.write(fd,buf,sz);
  }
};