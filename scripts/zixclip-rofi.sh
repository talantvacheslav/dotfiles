#!/bin/sh

PATH="$HOME/vxwmdots/scripts:$PATH"
export PATH

ZIXCLIP="${ZIXCLIP:-zixclip}"

id=$("$ZIXCLIP" list | rofi -dmenu -i -p clipboard | cut -f1)

[ -n "$id" ] && "$ZIXCLIP" select "$id"
