# vxwm - Versatile X Window Manager for x11 forked from dwm

# About
vxwm represents a significantly enhanced version of dwm that maintains its lightweight nature while offering modular flexibility. Instead of manually applying patches, you can toggle pre-installed features directly in the configuration by switching values between 0 and 1, it is all manageable via modules.def.h.

The defining feature of vxwm is its implementation of infinite tags. While traditional tiling managers act like a slide projector, swapping one static view for another, vxwm treats the screen as a viewport over a vast, continuous canvas. Windows aren't hidden or layered; they exist on an infinite surface, and you simply move your perspective across it. You can slide your view to find more space, snap focus to a specific window, or return to the origin using the homecanvas bind. Even though this sounds complex, this isn't resource hungry and isn't hard to use.

vxwm has repositories on:   
[codeberg](https://codeberg.org/wh1tepearl/vxwm)   
[github](https://github.com/wh1tepearll/vxwm) (readonly mirror)

# Requirements

In order to build vxwm you need the Xlib, Xft and Xinerama header files.

## Deps Installation

Arch Linux:

    sudo pacman -Sy libx11 libxft libxinerama

Void Linux:

    sudo xbps-install -S libX11 libX11-devel libXft libXft-devel libXinerama libXinerama-devel

Gentoo Linux:
    
    sudo emerge -av x11-libs/libX11 x11-libs/libXft x11-libs/libXinerama

# Getting Started:

## Installation

Clone this repository and cd into it.

    git clone https://codeberg.org/wh1tepearl/vxwm.git
    cd vxwm

Edit config.mk to match your local setup (vxwm is installed into
the /usr/local namespace by default).

Afterwards enter the following commands to build and install vxwm:
    
    make
    sudo make clean install

(yes, run make first and only then sudo make clean install)

## Running vxwm

You will need startx utility installed.

Add the following line to your .xinitrc to start vxwm using startx:

    exec vxwm

If you want to restart vxwm without losing your session 
or for hot configuration reload, add something like this to your .xinitrc:

    vxwm &
    exec sleep infinity

And then for restarting vxwm use the rvx utility.

In order to connect vxwm to a specific display, make sure that
the DISPLAY environment variable is set correctly, e.g.:

    DISPLAY=:1 exec vxwm

(This will start vxwm on display :1)

In order to display status info in the bar, you can do something
like this in your .xinitrc:

    while xsetroot -name "`date` `uptime | sed 's/.*,//'`"
    do
    	sleep 1
    done &
    exec vxwm


# Configuration

The configuration of vxwm is done by editing config.h and modules.h to
match your preferences and (re)compiling the source code.

## Adding custom keybinds

Add this to config.h and replace yoursillyprogram with the actual cmd that will be executed in hte keybind (recommended adding it right before keys array):

    static const char *yoursillyprogramcmd[]  = { "yoursillyprogram", NULL };

If your cmd uses multiple arguments, you should write them like this:

    static const char *yoursillyprogramcmd[]  = { "yoursillyprogram", "arg1", "arg2", NULL };

etc.

And then add this to keys massive:

    { MODKEY|ShiftMask,             XK_u, spawn,          {.v = yoursillyprogramcmd } }, 

## Modules

Enable/disable (0/1) modules you need/don't need, thats it.

> [!NOTE]
> After any change in config/modules recompile vxwm and restart using rvx.

# Acknowledgements

vxwm was made by wh1tepearl, many thanks to suckless.org and the [dwm] developers for making dwm in first place.
Thanks 5element developer and hevel wayland compositor developers for the inspiration of infinite tags.

Also try:

hevel wayland compositor: https://git.sr.ht/~dlm/hevel

5element: https://hg.sr.ht/~umix11/5element



> [!NOTE]
> If you encounter any bugs - **please make an issue!**<br>
> If you want something added - **please make an issue!**<br>
> If you want to change something - **please make an issue!**
