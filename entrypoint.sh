#!/bin/sh

echo TOKENURL=$TOKENURL >>/etc/environment
echo USERURL=$USERURL >>/etc/environment
echo USERLISTURL=$USERLISTURL >>/etc/environment
echo CLIENT_ID=$CLIENT_ID >>/etc/environment
echo CLIENT_SECRET=$CLIENT_SECRET >>/etc/environment
echo SCOPE=$SCOPE >>/etc/environment
/usr/sbin/sshd -D
