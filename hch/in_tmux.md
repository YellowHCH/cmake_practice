> *Ref* <https://www.ruanyifeng.com/blog/2019/10/tmux.html>

### 新建session:
tmux new -s <session_name>
### 进入session:
tmux attach -t <session_name>
### 离开session:
ctrl+b+d or cmd 'exit'
### 列出所有session
tmux ls
ctrl+b s
### 拆分tmux窗口:
ctrl+b+% or or cmd 'tmux split-window -h' #左右
ctrl+b+" or cmd 'tmux split-window' #上下
### 关闭窗口:
ctrl+b+x
### 切换窗口
ctrl+b+<arrow key>
### 调整窗口大小
ctrl+b ctrl+<arrow key>
