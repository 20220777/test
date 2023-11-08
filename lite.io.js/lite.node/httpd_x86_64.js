///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
////////////////////////////////              /////////////////////////////////
////////////////////////////////              /////////////////////////////////
////////////////////////////////              /////////////////////////////////
////////////////////////////////              /////////////////////////////////
///////////////////////////                         ///////////////////////////
////////////////////////////                      /////////////////////////////
//////////////////////////////                  ///////////////////////////////
////////////////////////////////              /////////////////////////////////
//////////////////////////////////          ///////////////////////////////////
////////////////////////////////////     //////////////////////////////////////
////////////////////////////////////// ////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

let req_method = "";
var _serial_timer_proc;
var _socket_timer_proc;
var _httpd_timer_proc;

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
var common = require("./__common.js");
var tcp = require("./__socket.js");
var srl = require("./__serial.js");
var httpd = require("./__httpd.js");

console.log("################################################################################");
console.log("#                                                                              #");
console.log("#                                                                              #");
console.log("#                             STARTED                                          #");
console.log("#                                                                              #");
console.log("#                                                                              #");
console.log("################################################################################");


// httpd_fd = httpd.open("./out/liteio_httpd_x86_64", "8090", "D:\\waas\\htdocs\\", httpd_callback);
// common.sleep(2000);
tcp_fd = tcp.open("./out/liteio_socket_x86_64", "192.168.0.106", "502", tcp_callback);
common.sleep(2000);
srl_fd = srl.open("./out/liteio_serial_x86_64", "COM4", "115200", serial_callback);
common.sleep(2000);
// console.log("tcp " + tcp_fd);
// console.log("serial " + srl_fd);
// console.log("httpd " + httpd_fd);


function httpd_callback(fd, buf, sz)
{
  if (sz < 0 )
  {
    console.log(sz);
    return ;
  }

  console.log('httpd_callback -> ', sz ,':', buf);

  html  = "HTTP/1.1 200 OK\r\n";
  html += "\r\n";

  httpd.write(fd, html, html.length);
  //httpd.close(fd);
  return;
}




function tcp_callback(fd, buf, sz)
{
  if (sz < 0 )
  {
    console.log(sz);
    return ;
  }

  var str = "";
  buf.forEach(function(byte) {                
                str += ('0' + (byte & 0xFF).toString(16)).slice(-2) + " ";
            });

  //for ( i=0 ; i<sz ; i++ ) str += String.fromCharCode(buf[i]);
  console.log('tcp_callback -> ', sz ,':', str);


}



function serial_callback(fd, buf, sz)
{
  if (sz < 0 )
  {
    console.log(sz);
    return ;
  }

  var str = "";
  buf.forEach(function(byte) {                
                str += ('0' + (byte & 0xFF).toString(16)).slice(-2) + " ";
            });

  //for ( i=0 ; i<sz ; i++ ) str += String.fromCharCode(buf[i]);
  console.log('serial_callback -> ', sz ,':', str);

}



function serial_timer_proc(obj)
{
  console.log('serial_timer_proc');

  srl.write(srl_fd, "abcdefgh", 8);

  clearTimeout(_serial_timer_proc)
  _serial_timer_proc = setTimeout(serial_timer_proc, 1500, obj);
}
function socket_timer_proc(obj)
{
  console.log('socket_timer_proc');
  const  mbuf = new Uint8Array(32);
  var sz = 0;
  mbuf[sz++] = 0x00;
  mbuf[sz++] = 0x01;
  mbuf[sz++] = 0x00;
  mbuf[sz++] = 0x00;
  mbuf[sz++] = 0x00;
  mbuf[sz++] = 0x06;
  mbuf[sz++] = 0x00;
  mbuf[sz++] = 0x03;
  mbuf[sz++] = 0x00;
  mbuf[sz++] = 0x00;
  mbuf[sz++] = 0x00;
  mbuf[sz++] = 0x08;
  console.log(mbuf, sz);

  tcp.write(tcp_fd, mbuf, sz);

  clearTimeout(_socket_timer_proc)
  _socket_timer_proc = setTimeout(socket_timer_proc, 1500, obj);
}


_serial_timer_proc = setTimeout(serial_timer_proc, 1000, 0);
_socket_timer_proc = setTimeout(socket_timer_proc, 2000, 0);
