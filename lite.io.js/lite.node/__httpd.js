module.exports = {
  _module : 0,
  open : function(path,param,callback)
  {
    _common = require('./__common.js');
    if (path == null ) _module = require('liteio_httpd_x86_64');
    else _module = require(path);

    console.log(param);
    //_common.sleep(10);
    fd = _module.open(param, callback);
    return fd;
  },
  close : function(fd)
  {
    console.log('close');
    return _module.close(fd);
  },
  write : function(fd,buf,sz)
  {
    return _module.write(fd,buf,sz);
  },
};
