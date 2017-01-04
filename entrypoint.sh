#!/bin/bash

for i in PYTHONHOME PYTHONPATH TOKENURL USERURL USERLISTURL CLIENT_ID CLIENT_SECRET SCOPE; do
  echo $i=${!i} >>/etc/environment
done

/usr/sbin/sshd -D
