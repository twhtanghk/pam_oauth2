#!/bin/sh

echo TOKENURL=$TOKENURL >>/etc/environment
echo USERURL=$USERURL >>/etc/environment
echo USERLISTURL=$USERLISTURL >>/etc/environment
/usr/sbin/sshd -D
