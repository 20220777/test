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
var _serial_periodic_proc;
var _tcp_periodic_proc;
var _httpd_periodic_proc;
var _webtcp_periodic_proc;

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
//var tcp = require("./out/liteio_socket_x86_64.node");
// var srl = require("./out/liteio_serial_x86_64.node");
var httpd = require("./__httpd.js");
//var wsd = require("./out/liteio_websocket_x86_64.node");

console.log("################################################################################");
console.log("#                                                                              #");
console.log("#                                                                              #");
console.log("#                             STARTED                                          #");
console.log("#                                                                              #");
console.log("#                                                                              #");
console.log("################################################################################");




httpd_fd = httpd.open("./out/liteio_httpd_x86_64", "--httpd_port 8090 --httpd_home D:\\waas\\htdocs\\ --httpd_index index.html --httpd_size_of_buffer 1024", httpd_callback);
// common.sleep(2000);
// srl_fd = srl.open("--serial_port COM4 --serial_baudrate 115200 --serial_size_of_buffer 1", serial_callback);
// common.sleep(2000);
//tcp_fd = tcp.open("--socket_ip 192.168.0.106 --socket_port 502 --socket_cstype CLIENT --socket_protocol TCP --socket_casttype UNICAST --socket_size_of_buffer 1024", tcp_callback);
// common.sleep(4000);
//wsd_fd = wsd.open("--websocket_url http://127.0.0.1:8091 --websocket_cstype SERVER --websocket_size_of_buffer 1024", wsd_callback);

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


function wsd_callback(fd, buf, sz)
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
  console.log('wsd_callback -> ', sz ,':', str);


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



function serial_periodic_proc(obj)
{
  console.log('serial_periodic_proc');

  srl.write(srl_fd, "abcdefgh", 8);

  clearTimeout(_serial_periodic_proc)
  _serial_periodic_proc = setTimeout(serial_periodic_proc, 500, obj);
}
function tcp_periodic_proc(obj)
{
  console.log('tcp_periodic_proc');
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

  clearTimeout(_tcp_periodic_proc)
  _tcp_periodic_proc = setTimeout(tcp_periodic_proc, 500, obj);
}
function wsd_periodic_proc(obj)
{
  console.log('wsd_periodic_proc');

  clearTimeout(_wsd_periodic_proc)
  _wsd_periodic_proc = setTimeout(wsd_periodic_proc, 500, obj);
}

console.log("################################################################################");
console.log("#                                                                              #");
console.log("#                                                                              #");
console.log("#                             PERIODIC START                                   #");
console.log("#                                                                              #");
console.log("#                                                                              #");
console.log("################################################################################");
//_serial_periodic_proc = setTimeout(serial_periodic_proc, 1000, 0);
//_tcp_periodic_proc = setTimeout(tcp_periodic_proc, 1000, 0);
//_wsd_periodic_proc = setTimeout(wsd_periodic_proc, 1000, 0);
