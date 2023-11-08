var httpd = require('./liteio_httpd_x64');
var shm = require('./liteio_shm_x64');
var srl = require('./liteio_serial_x64');
var wsd = require('./liteio_wsd_x64');


let req_method = "";

var httpd_fd = httpd.open("--httpd_port 8083 --httpd_home /opt/www/htdocs --httpd_index index.html", httpd_callback);
//var shm_fd = shm.open("--shm_key 7810 --shm_size 8192", shm_callback);
//var srl_fd = srl.open("--serial_port /dev/ttyAMA1 --serial_baudrate 115200 --serial_size_of_buffer 64", serial_callback);
//var wsd_fd = wsd.open("--wsd_port 7810", wsd_callback);


var wsd_cfds;


class cClientSet
{
  constructor()
  {
    this.fd = new Array();
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
let wsdClientSet = new cClientSet();

function serial_write()
{
  //console.log('serial_write to ', srl_fd);
  srl.write(srl_fd, "ABCD", 4);
}


function arr2str(b)
{
  return String.fromCharCode.apply(null, new Uint16Array(b));
}


function wsd_callback(fd, buf, sz, type)
{
  //console.log('wsd_callback ', fd);
  //console.log("+##############################################################################+");

  //wsdClientSet.add(fd);
  wsd_cfds = fd;
}


function wsd_write()
{
  var i = 0;
  var msg = 0;

  msg = "WebSocket " + i;
  //console.log('wsd_write ', wsd_cfds);
  wsd.write(wsd_cfds, "1234", 4);


  /***
  for ( i=0 ; i<wsdClientSet.fd.length ; i++ )
  {
    msg = "WebSocket " + i;
    wsd.write(wsdClientSet.fd[i], msg, msg.length);
  }
  ***/
}


//setInterval(wsd_write, 500);






function serial_callback(fd, buf, sz, type)
{
  //console.log('serial_callback');
  //console.log("+##############################################################################+");
  //console.log( arr2str(buf), ", ", sz );
  //console.log("+^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^+");
}

function shm_callback(fd, buf, sz, type)
{
  //console.log('shm_callback');
  //console.log("+##############################################################################+");
  //console.log( arr2str(buf) );
  //console.log("+^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^+");
}


function httpd_raw_callback(fd, uri, sz, type)
{
  console.log("httpd_raw_callback");

}

function httpd_event_callback(fd, uri, sz, type)
{
  var html = 0;
  console.log("httpd_event_callback");
  //console.log("+------------------------------------------------------------------------------+");
  //console.log( arr2str(uri) );
  var _uri = arr2str(uri).split('?');
  // console.log("-------------------------------");

  switch(type)
  {
    case  0xE0001010:
      if ( _uri[0] == '/network' )
      {
        html  = "HTTP/1.1 200 OK\r\n";
        html += "Content-Type: text/html\r\n";
        html += "\r\n";
        html += "<form method=post action='/network2?test=sample'>";
        //html += "<input type=text name='id'>";
        html += "{'key0':'kv0'}";
        html += "<input type=submit>";
        html += "</form>";
      }
      else if ( _uri[0] == '/network2' )
      {
        html  = "HTTP/1.1 200 OK\r\n";
        html += "\r\n";
        html += "network2\r\n";
      }
      else if ( _uri[0] == '/__debug' )
      {
        html  = "HTTP/1.1 200 OK\r\n";
        html += "\r\n";

        if ( _uri[1] == 'on')
        {
          shm.debug(1);
          srl.debug(1);
          httpd.debug(1);
          html += "enabled debug mode\r\n";
        }
        else
        {
          shm.debug(0);
          srl.debug(0);
          httpd.debug(0);
          html += "disabled debug mode\r\n";
        }
      }
      else if ( _uri[0] == '/req' ){
        html = createmessage(200, fs.readFileSync("../www/req.html"))
      }
      else if (_uri[0] == '/res'){
        
        html = createmessage(200, `Method : ${req_method}\r\nData : ${getData(_uri[1])}`)
      }
      else if(_uri[0] == '/upload') {
        //if(req_method==="GET") html = createmessage(200, fs.readFileSync("../www/upload.html"))
        //else {
        //  html = createmessage(200, 'OK')
        //}

        //console.log(_uri[1]);
      }
      else
      {
        html  = "HTTP/1.1 404 Not Found\r\n";
        html += "\r\n";
        html += "Not Found\r\n";
      }

      
      //console.log("+******************************************************************************+");
      //console.log(arr2str(uri));
      //console.log(arr2str(uri).length);
      //console.log("+//////////////////////////////////////////////////////////////////////////////+");
      //shm.write(0, arr2str(uri), arr2str(uri).length, "ksbridge.x32");
      //httpd.write(fd, html, html.length);
      //console.log("+------------------------------------------------------------------------------+");
      //httpd.close(fd);
      //console.log("+//////////////////////////////////////////////////////////////////////////////+");
      break;

    case 0xE000FDC0:
      //console.log(fd + ' :  connected');
      break;

    case 0xE000FDCF:
      //console.log(fd + ' :  disconnected');
      break;
    default:

      console.log(_uri[0]);
      //console.log(_uri[1]);
      html  = "HTTP/1.1 200 OK\r\n";
      html += "\r\n";
      httpd.write(fd, html, html.length);


      ////req_method = getMethod(_uri[0]);
      break
  }
  //console.log("+______________________________________________________________________________+");
}

function httpd_callback(fd, uri, sz, type)
{

  console.log('httpd_callback');


  if ( type & 0x80000000 )
  {
    httpd_event_callback(fd, uri, sz, type);
  }
  else
  {
    httpd_raw_callback(fd, uri, sz, type);
  }


}
