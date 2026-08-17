#!/bin/sh
while true; do
    xsetroot -name " ""$(date '+%d/%m | %H:%M:%S ')"
    sleep 1
done &
