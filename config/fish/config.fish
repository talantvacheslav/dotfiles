# function fish_prompt
#     echo $PWD (set_color cyan) '> '
# end

function fish_prompt
    string join '' -- (set_color normal) (prompt_pwd) (set_color cyan) ' < '
end
set fish_greeting ""
if status is-interactive

fish_add_path ~/.spicetify
fish_add_path ~/.local/bin
fish_add_path ~/bin

alias vv='cd ~/vxwm/vxwm'
alias cal='cal -m'
alias lv='lavat -c cyan -k red'
alias ff='fastfetch -l netbsd'
alias f='fastfetch'
alias sk='~/.local/bin/suckless_fetch.bak.sh'
alias wf='~/bin/scripts/wfetch.sh'
alias nn='nvim .'
alias q="printf '\033[2J\033[3J\033[1;1H'"
alias tray='stalonetray --geometry 5x1+1720+0 --background "#000000" --icon-size 20'
alias nf='neofetch --ascii_distro netbsd'
alias n='neofetch'
alias x='startx'
alias w-real='bash -c w'
alias cma='cmatrix -rmu 6'
alias pf='pfetch'
alias qf='qfetch'
alias ls='eza --icons'
end
