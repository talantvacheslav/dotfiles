#!/bin/sh
# cp to ~/.local/bin/ and bind

ZIXCLIP="${ZIXCLIP:-zixclip}"

id=$($ZIXCLIP list | rofi -dmenu -i -p clipboard | cut -f1)

[ -n "$id" ] && $ZIXCLIP select "$id"
