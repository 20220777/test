module.exports = {
  _module : 0,
  open : function(path,port,home,callback)
  {
    _common = require('./__common.js');
    if (path == null ) _module = require('liteio_websocket_x86_64.node');
    else _module = require(path);

    _port = port;
    _url = home;
    _index = "index.html";
    if ( port == null ) _port = "8091";
    if ( home == null ) _home = "/";


    param  = "--httpd_port " + _port;
    param += " --httpd_home " + _home;
    param += " --httpd_index " + _index;
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
