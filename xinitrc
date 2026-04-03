#!/bin/bash

#xrandr --output DP-0 --mode 1920x1080 --rate 180.00 --output DVI-D-0 --mode 1680x1050 --rate 60 --right-of DP-0

status.sh & #sudo cp ~/dotfiles/vxwm/status.sh /bin/status.sh
xclip &
xset r rate 250 40 &
xinput --set-prop 10 "libinput Accel Speed" -1 &
#hsetroot -cover ~/.cache/wal/wallpaper.jpg 
wal -R 
hsetroot -solid "$(sed -n '6p' ~/.cache/wal/colors)" &
dunst &
setxkbmap -layout us,ru -option 'grp:alt_shift_toggle'
picom &

vxwm 
