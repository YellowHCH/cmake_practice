# .bashrc

# User specific aliases and functions

#alias rm='rm -i'
#alias cp='cp -i'
#alias mv='mv -i'

# Source global definitions
if [ -f /etc/bashrc ]; then
	. /etc/bashrc
fi
export PATH="$PATH:$HOME/.ft"
source ~/.git-completion.bash
#source ~/.git-completion.bash
alias python='/usr/bin/python3.6'
alias l='ls'
alias ll='ls -l'
LC_CTYPE="zh_CN.utf8"
PS1="\[\033[01;31m\]\u\[\033[00m\]@\[\033[01;32m\]\h\[\033[00m\][\[\033[01;33m\]\t\[\033[00m\]]:\[\033[01;34m\]\w\[\033[00m\] $ "

