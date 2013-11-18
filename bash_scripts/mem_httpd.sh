#!/usr/bin/env bash

function restart_httpd {
	/etc/init.d/httpd restart
}

free=$(cat /proc/meminfo | grep "MemFree" | awk '{print $2}')

# less than 20MB 

if [[ $free -lt 20480 ]]; then
	sync
	restart_httpd
fi
