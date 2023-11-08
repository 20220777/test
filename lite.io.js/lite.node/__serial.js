module.exports = {
  _module : 0,
  open : function(path,port,baudrate,callback)
  {
    _common = require('./__common.js');
    if (path == null ) _module = require('liteio_serial_x86_64');
    else _module = require(path);
    _port = port;
    _baudrate = baudrate;
    if ( port == null ) _port = "COM4";
    if ( baudrate == null ) _baudrate = "115200";
    param = "--serial_port " + _port;
    param += " --serial_baudrate " + _baudrate;
    param += " --serial_size_of_buffer 1";
    console.log(param);
    //_common.sleep(10);
    fd = _module.open(param, callback);
    return fd;
  },
  write : function(fd,buf,sz)
  {
    return _module.write(fd,buf,sz);
  }
};


// var srl = require('./out/liteio_serial_x86_64');
// var srl_fd = srl.open("--serial_port COM4 --serial_baudrate 115200 --serial_size_of_buffer 1", serial_callback);
// sleep(2000);

// var sck = require('./out/liteio_socket_x86_64');
// var sck_fd = sck.open("--socket_ip 192.168.0.106 --socket_port 502 --socket_cstype CLIENT --socket_protocol TCP --socket_casttype UNICAST --socket_size_of_buffer 1024", socket_callback);




// function serial_callback(fd, buf, sz)
// {
  // var str = "";
  // for ( i=0 ; i<sz ; i++ ) str += String.fromCharCode(buf[i]);
  // console.log('serial_callback -> ', sz ,':', str);


  // //console.log("+##############################################################################+");
  // //console.log("-->", arr2str(buf), ", ", sz );
  // //console.log("+^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^+");
// }

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//////                                                                   //////
//////                                                                   //////
//////                           Entry Point                             //////
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


// var srl = require('./out/liteio_serial_x86_64');
// var srl_fd = srl.open("--serial_port COM4 --serial_baudrate 115200 --serial_size_of_buffer 1", serial_callback);
// sleep(2000);

// var sck = require('./out/liteio_socket_x86_64');
// var sck_fd = sck.open("--socket_ip 192.168.0.106 --socket_port 502 --socket_cstype CLIENT --socket_protocol TCP --socket_casttype UNICAST --socket_size_of_buffer 1024", socket_callback);




// function serial_callback(fd, buf, sz)
// {
  // var str = "";
  // for ( i=0 ; i<sz ; i++ ) str += String.fromCharCode(buf[i]);
  // console.log('serial_callback -> ', sz ,':', str);


  // //console.log("+##############################################################################+");
  // //console.log("-->", arr2str(buf), ", ", sz );
  // //console.log("+^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^+");
// }


// function socket_callback(fd, buf, sz)
// {
  // if ( sz <= 0 )
  // {
    // console.log( sz );
    // return;
  // }


  // var str = "";
  // buf.forEach(function(byte) {                
                // str += ('0' + (byte & 0xFF).toString(16)).slice(-2) + " ";
            // });

  // //for ( i=0 ; i<sz ; i++ ) str += String.fromCharCode(buf[i]);
  // console.log('serial_callback -> ', sz ,':', str);


  // //console.log("+##############################################################################+");
  // //console.log("-->", arr2str(buf), ", ", sz );
  // //console.log("+^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^+");
// }




// function index_timer_proc(obj)
// {
  // console.log('index_timer_proc');

  // srl.write(srl_fd, "ABCDEFGH", 8);

  // {
    // const  mbuf = new Uint8Array(32);
    // var sz = 0;
    // mbuf[sz++] = 0x00;
    // mbuf[sz++] = 0x01;
    // mbuf[sz++] = 0x00;
    // mbuf[sz++] = 0x00;
    // mbuf[sz++] = 0x00;
    // mbuf[sz++] = 0x06;
    // mbuf[sz++] = 0x00;
    // mbuf[sz++] = 0x03;
    // mbuf[sz++] = 0x00;
    // mbuf[sz++] = 0x00;
    // mbuf[sz++] = 0x00;
    // mbuf[sz++] = 0x08;
    // console.log(mbuf, sz);

    // sck.write(sck_fd, mbuf, sz);
  // }

  // clearTimeout(timer_proc)
  // timer_proc = setTimeout(index_timer_proc, 500, obj);
// }

// timer_proc = setTimeout(index_timer_proc, 1000, 0);

// console.log("################################################################################");
// console.log("#                                                                              #");
// console.log("#                                                                              #");
// console.log("#                             STARTED                                          #");
// console.log("#                                                                              #");
// console.log("#                                                                              #");
// console.log("################################################################################");
