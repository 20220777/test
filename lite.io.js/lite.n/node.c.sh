#!/bin/bash

# cd /lib/systemd/system
# ln -s /usr/local/node/x32/node.c.service .
# systemctl status node.c.service
# systemctl daemon-reload
# systemctl enable node.c.service
# systemctl start node.c.service


HOME=`pwd`

$HOME/pkg/ngine.$1.out --m console --d WAAS_NODE --s WAAS_NODE --X $HOME/pkg/code.X.$1.so  --l /usr/local/node/log --e d7




