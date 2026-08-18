#!/bin/bash

#script and rofi config is fork from https://github.com/NyxOkkotsu/vxwmdotfiles

# Target directory containing your wallpapers
WALL_DIR="$HOME/Pictures/Wallpapers"

# Ensure the wallpaper directory exists, create it if it doesn't
mkdir -p "$WALL_DIR"

# Generate the input list for Rofi with explicit icon paths (\0icon\x1f)
ROFI_INPUT=""
while read -r file; do
    if [ -n "$file" ]; then
        # Format: "Filename to display[NULL]icon[US]/absolute/path/to/image"
        ROFI_INPUT+="${file}\0icon\x1f${WALL_DIR}/${file}\n"
    fi
done <<< "$(ls -1 "$WALL_DIR" | grep -E "\.(jpg|jpeg|png)$")"

# Launch Rofi with icon support and pipe the formatted input
SELECTION=$(echo -e "$ROFI_INPUT" | rofi -show-icons -dmenu -i -p "󰸉 Wallpaper" -theme ~/.config/rofi/wall-changer.rasi)

# If the user does not select anything (e.g., presses ESC), exit the script safely
if [ -z "$SELECTION" ]; then
    exit 1
fi

# Construct the absolute full path to the selected wallpaper file
WALLPAPER="$WALL_DIR/$SELECTION"

# 1. Set the desktop background using xwallpaper with the stretch option
xwallpaper --stretch "$WALLPAPER"

# 2. Run pywal to generate a new color palette based on the wallpaper
# The -n flag prevents pywal from setting the wallpaper itself
wal -i "$WALLPAPER" -n

#comment if dont want 
hsetroot -solid "$(sed -n 's/^dwm\.selbgcolor:[[:space:]]*//p' ~/.cache/wal/dwm.Xresources)"

# Reload the Xresources db so xrdb patch inside vxwm can see the new colors
xrdb -merge "$HOME/.cache/wal/colors.Xresources"

# Send an X key event to simulate pressing Mod+F5 to live-reload vxwm colors
xdotool key Super+F5

# 3. Trigger the Dunst color synchronizer script to apply the new theme
if [ -f "$HOME/wal-dunst.sh" ]; then
    "$HOME/wal-dunst.sh"
fi

