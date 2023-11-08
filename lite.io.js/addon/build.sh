#! /bin/bash

################################################################################
################################################################################
################################################################################
rm -rf build


if [ -z $1 ]
then
echo $0 "[system arch] [nmodule]";
exit;
fi

if [ -z $2 ]
then
echo $0 "[system arch] [nmodule]";
exit;
fi

if [ $2 == 'all' ]
then
echo "################################################################################"
echo "# build serial"
echo "################################################################################"
./bindings $1 serial
node-gyp clean configure build;
\cp -rfp build/Release/obj.target/*serial*.node bin

echo "################################################################################"
echo "# build shm"
echo "################################################################################"
./bindings $1 shm
node-gyp clean configure build;
\cp -rfp build/Release/obj.target/*shm*.node bin

echo "################################################################################"
echo "# build httpd"
echo "################################################################################"
./bindings $1 httpd
node-gyp clean configure build;
\cp -rfp build/Release/obj.target/*httpd*.node bin

echo "################################################################################"
echo "# build http"
echo "################################################################################"
./bindings $1 http
node-gyp clean configure build;
\cp -rfp build/Release/obj.target/*http*.node bin

echo "################################################################################"
echo "# build wsd"
echo "################################################################################"
./bindings $1 wsd
node-gyp clean configure build;
\cp -rfp build/Release/obj.target/*wsd*.node bin

echo "################################################################################"
echo "# build wsc"
echo "################################################################################"
./bindings $1 wsc
node-gyp clean configure build;
\cp -rfp build/Release/obj.target/*wsc*.node bin

echo "################################################################################"
echo "# build tcpd"
echo "################################################################################"
./bindings $1 tcpd
node-gyp clean configure build;
\cp -rfp build/Release/obj.target/*tcpd*.node bin

echo "################################################################################"
echo "# build tcp"
echo "################################################################################"
./bindings $1 tcp
node-gyp clean configure build;
\cp -rfp build/Release/obj.target/*tcp*.node bin

else
echo "################################################################################"
echo "# build " $2
echo "################################################################################"
./bindings $1 $2
node-gyp clean configure build;
\cp -rfp build/Release/obj.target/*$2*.node bin
fi
