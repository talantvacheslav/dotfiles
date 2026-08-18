#!/bin/bash

#xrandr --output DP-0 --mode 1920x1080 --rate 180.00 --output DVI-D-0 --mode 1680x1050 --rate 60 --right-of DP-0

~/vxwmdots/scripts/status.sh & 
xclip &
xset r rate 250 40 &
xinput --set-prop 10 "libinput Accel Speed" -1 &
wal -R 
hsetroot -solid "$(sed -n 's/^dwm\.selbgcolor:[[:space:]]*//p' ~/.cache/wal/dwm.Xresources)" &
dunst &
setxkbmap -layout us,ru -option 'grp:alt_shift_toggle'
picom &

vxwm 
