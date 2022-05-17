" Setting some decent VIM settings for programming

set ai                          " set auto-indenting on for programming
set showmatch                   " automatically show matching brackets. works like it does in bbedit.
set vb                          " turn on the "visual bell" - which is much quieter than the "audio blink"
set ruler                       " show the cursor position all the time
set laststatus=2                " make the last line where the status is two lines deep so you can see status always
set backspace=indent,eol,start  " make that backspace key work the way it should
set nocompatible                " vi compatible is LAME
set background=dark             " Use colours that work well on a dark background (Console is usually black)
set showmode                    " show the current mode
set clipboard=unnamed           " set clipboard to unnamed to access the system clipboard under windows
syntax on                       " turn syntax highlighting on by default
colorscheme slate "desert "
"colorscheme elflord
set number
set hlsearch                    " highlight search
set completeopt=preview,menu    " auto complete
set clipboard+=unnamed          " share cut table
set autowrite
"set cursorline              " 突出显示当前行
"highlight CursorLine   cterm=NONE ctermbg=darkgray ctermfg=NONE
"set guifont=Courier\New:h16:b:cDEFAULT" 设置字体
" 不同的机器背景色相差太大了，这里每次都要调整
hi Search term=standout ctermfg=0 ctermbg=3 guifg=orangered guibg=yellow2 

"autocmd InsertLeave * se nocul " 用浅色高亮当前行
"autocmd InsertEnter * se cul " 用浅色高亮当前行
set ruler " 显示标尺 
set scrolloff=3 " 光标移动到buffer的顶部和底部时保持3行距离
set fdm=marker  " 代码折叠
" disable flash screen
set noerrorbells visualbell t_vb=

"set mouse=a

""" special tmux
if &term =~ '^screen'
  " tmux will send xterm-style keys when its xterm-keys option is on
  execute "set <xUp>=\e[1;*A"
  execute "set <xDown>=\e[1;*B"
  execute "set <xRight>=\e[1;*C"
  execute "set <xLeft>=\e[1;*D"
endif
"""

set ts=2
set softtabstop=2
set shiftwidth=2
set encoding=utf-8                                                                                                                                                                                      
set fileencodings=utf-8,ucs-bom,gb18030,gbk,gb2312,cp936
set fenc=cp936
set expandtab
set autoindent
map <C-t> :NERDTreeToggle<CR>
"autocmd vimenter * NERDTree
let g:NERDTreeShowLineNumbers=1
let g:NERDTreeHidden=0
let g:NERDTreeSize=10

"" ctags
set tags+=/data/chenhui.huang/workspace/MTensorRT/tags
set tags+=/data/chenhui.huang/workspace/torch-mlir/tags

"" config tagbar
map <S-t> :TagbarToggle<CR>

        " Show EOL type and last modified timestamp, right after the filename
set statusline=%<%F%h%m%r\ [%{&ff}]\ (%{strftime(\"%H:%M\ %d/%m/%Y\",getftime(expand(\"%:p\")))})%=%l,%c%V\ %P

"""""""""""""""""""""
nmap <C-\>s :cs find s <C-R>=expand("<cword>")<CR><CR>                                                                                                                                              
nmap <C-[>g :cs find g <C-R>=expand("<cword>")<CR><CR>  
nmap <C-\>c :cs find c <C-R>=expand("<cword>")<CR><CR>  
nmap <C-\>t :cs find t <C-R>=expand("<cword>")<CR><CR>  
nmap <C-\>e :cs find e <C-R>=expand("<cword>")<CR><CR>  
nmap <C-\>f :cs find f <C-R>=expand("<cfile>")<CR><CR>  
nmap <C-\>i :cs find i ^<C-R>=expand("<cfile>")<CR>$<CR>
nmap <C-\>d :cs find d <C-R>=expand("<cword>")<CR><CR>
"""""""""""""""""""""
" 你在此设置运行时路径
set rtp+=~/.vim/bundle/Vundle.vim

call vundle#begin()

" 在这里面输入安装的插件
" Vundle 本身就是一个插件
Plugin 'VundleVim/Vundle.vim'
"Plugin 'scrooloose/nerdtree'
Plugin 'majutsushi/tagbar'
"Plugin 'taghighlight'
"Plugin 'justinmk/vim-syntax-extra'
Plugin 'octol/vim-cpp-enhanced-highlight'
Bundle 'The-NERD-tree'
Bundle 'The-NERD-Commenter'
"Bundle 'ycm-core/YouCompleteMe'
"Bundle 'cscope_maps.vim'
"所有插件都应该在这一行之前
call vundle#end()

" https://github.com/octol/vim-cpp-enhanced-highlight
let g:cpp_class_scope_highlight = 1
let g:cpp_member_variable_highlight = 1
let g:cpp_class_decl_highlight = 1
let g:cpp_posix_standard = 1
let g:cpp_concepts_highlight = 1
let g:cpp_function_highlight = 1
let g:cpp_attributes_highlight = 1
let g:cpp_member_highlight = 1

"let cpp_simple_highlight = 0
" 这个配置很危险，非常难看
"let g:cpp_experimental_template_highlight = 1
"

if !has('gui_running')
  set t_Co=256
endif

"""" hilight specific file type
autocmd BufNewFile,BufRead *.patch,*.diff,*.mlir,*.toml,*.td set syntax=cpp
" Put all standard C and C++ keywords under Vim's highlight group 'Statement'
" (affects both C and C++ files)
" let g:cpp_simple_highlight = 1

" filetype off
filetype plugin indent on

"------------------------------------------------------------------------------
" Only do this part when compiled with support for autocommands.
if has("autocmd")
    "Set UTF-8 as the default encoding for commit messages
    autocmd BufReadPre COMMIT_EDITMSG,git-rebase-todo setlocal fileencodings=utf-8

    "Remember the positions in files with some git-specific exceptions"
    autocmd BufReadPost *
      \ if line("'\"") > 0 && line("'\"") <= line("$")
      \           && expand("%") !~ "COMMIT_EDITMSG"
      \           && expand("%") !~ "ADD_EDIT.patch"
      \           && expand("%") !~ "addp-hunk-edit.diff"
      \           && expand("%") !~ "git-rebase-todo" |
      \   exe "normal g`\"" |
      \ endif

      autocmd BufNewFile,BufRead *.patch set filetype=diff
      autocmd BufNewFile,BufRead *.diff set filetype=diff

      autocmd Syntax diff
      \ highlight WhiteSpaceEOL ctermbg=red |
      \ match WhiteSpaceEOL /\(^+.*\)\@<=\s\+$/

      autocmd Syntax gitcommit setlocal textwidth=74
endif " has("autocmd")
