FROM python:2

ENV VER=${VER:-master} \
    REPO=https://github.com/twhtanghk/pam_oauth2 \
    APP=/usr/src/app

WORKDIR $APP

RUN echo PYTHONHOME=/usr/local >>/etc/environment && \
    echo PYTHONPATH=/usr/src/app/python >>/etc/environment && \
    apt-get update && \
    apt-get install -y git ssh sudo libpam0g-dev && \
    apt-get clean && \
    mkdir /var/run/sshd && \
    git clone -b $VER $REPO $APP && \
    ln -s /usr/lib/python2.7/plat-x86_64-linux-gnu/_sysconfigdata_nd.py /usr/lib/python2.7/ && \
    pip install -r python/requirements.txt && \
    make install && \
    sed 's/^\(passwd:.*\)$/\1 oauth2/g' </etc/nsswitch.conf >/tmp/nsswitch.conf && \
    mv /tmp/nsswitch.conf /etc && \
    cp -a pam/pam.d/* /etc/pam.d

EXPOSE 22

CMD ./entrypoint.sh
