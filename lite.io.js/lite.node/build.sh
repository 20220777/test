#! /bin/bash

OUTPUT_DIR=out
################################################################################
################################################################################
################################################################################
rm -rf build
mkdir $OUTPUT_DIR

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
\cp -rfp build/Release/obj.target/*serial*.node $OUTPUT_DIR

echo "################################################################################"
echo "# build shm"
echo "################################################################################"
./bindings $1 shm
node-gyp clean configure build;
\cp -rfp build/Release/obj.target/*shm*.node $OUTPUT_DIR

echo "################################################################################"
echo "# build httpd"
echo "################################################################################"
./bindings $1 httpd
node-gyp clean configure build;
\cp -rfp build/Release/obj.target/*httpd*.node $OUTPUT_DIR

echo "################################################################################"
echo "# build http"
echo "################################################################################"
./bindings $1 http
node-gyp clean configure build;
\cp -rfp build/Release/obj.target/*http*.node $OUTPUT_DIR

echo "################################################################################"
echo "# build wsd"
echo "################################################################################"
./bindings $1 wsd
node-gyp clean configure build;
\cp -rfp build/Release/obj.target/*wsd*.node $OUTPUT_DIR

echo "################################################################################"
echo "# build wsc"
echo "################################################################################"
./bindings $1 wsc
node-gyp clean configure build;
\cp -rfp build/Release/obj.target/*wsc*.node $OUTPUT_DIR

echo "################################################################################"
echo "# build tcpd"
echo "################################################################################"
./bindings $1 tcpd
node-gyp clean configure build;
\cp -rfp build/Release/obj.target/*tcpd*.node $OUTPUT_DIR

echo "################################################################################"
echo "# build tcp"
echo "################################################################################"
./bindings $1 tcp
node-gyp clean configure build;
\cp -rfp build/Release/obj.target/*tcp*.node $OUTPUT_DIR

else
echo "################################################################################"
echo "# build " $2
echo "################################################################################"
./bindings $1 $2
node-gyp clean configure build;
\cp -rfp build/Release/obj.target/*$2*.node $OUTPUT_DIR
fi
