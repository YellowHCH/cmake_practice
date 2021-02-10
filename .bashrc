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
alias la='ls -all'
# sometimes, ls command need to add config color
#alias ls='ls --color'
alias s='du -h --max-depth=0'
alias s1='du -h --max-depth=1'
alias grep='grep --color=auto'
alias hch='cd /root/hch/cmake_practice'
alias vi='vim'
alias bb="bazel build -c fastbuild --copt=-m32 --copt=-fdiagnostics-color=always "
alias mkcscope='find `pwd` -name "*.h" -o -name "*.c" -o -name "*.cc" -o -name "*.hpp" -o -name "*.cpp" > /root/dev_tools/cscope/cscope.file \
                        && cd /root/dev_tools/cscope/ && cscope -Rqb -i cscope.file && cd -'
export CSCOPE_DB='/root/dev_tools/cscope/'
LC_CTYPE="zh_CN.utf8"
PS1="\[\033[01;31m\]\u\[\033[00m\]@\[\033[01;32m\]\h\[\033[00m\][\[\033[01;33m\]\t\[\033[00m\]]:\[\033[01;34m\]\w\[\033[00m\] \n$ "

