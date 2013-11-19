#!/usr/bin/env bash

function restart_service {
        service httpd restart
        service postfix restart
}

function clean_cache {
        sync; echo 3 > /proc/sys/vm/drop_caches
}

# MB
used=$(free -m | awk '/^Mem:/{print $3}')

# greater than 1900MB

if [[ $used -gt 1900 ]]; then
        clean_cache
        restart_httpd
        echo "restared service"
else
        echo "nothing"
fi
