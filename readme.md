# My vxwm dotfiles 

![Screenshot](rice.jpg)

## Installation

```bash
git clone https://github.com/talantvacheslav/dotfiles.git
cd dotfiles/
cp -rf config/* ~/.config/
cp -rf cache/* ~/.cache/
cp -rf xinitrc ~/.xinitrc
cd vxwm/
make 
sudo make install
sudo cp -rf status.sh /bin/status.sh
cd ..
cd zixclip
gcc zixclip.c -o zixclip -lX11 -lXfixes -lsqlite3 -lcrypto
sudo cp -rf zixclip /bin/zixclip #add it to autostart later any method you want
sudo cp -rf zixclip-rofi.sh /bin/zixclip-rofi.sh
```

## Usage

```bash
startx
```

## Dependencies(?)
kitty fish pywal picom rofi nemo flameshot zen-browser dunst btop AyuGram discord 

## Applications binds

`super+e` nemo
`super+t` kitty
`super+w` zen-browser
`super+s` ayugram
`super+d` discord
`super+a` spotify


#### see another binds in config.def.h

