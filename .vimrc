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
colorscheme desert "elflord
set number
set hlsearch                    " highlight search
set completeopt=preview,menu    " auto complete
set clipboard+=unnamed          " share cut table
set autowrite
set cursorline              " 突出显示当前行
"highlight CursorLine   cterm=NONE ctermbg=darkgray ctermfg=NONE
set guifont=Courier\New:h16:b:cDEFAULT" 设置字体
hi Search term=standout ctermfg=0 ctermbg=11 guifg=orangered guibg=yellow2 

autocmd InsertLeave * se nocul " 用浅色高亮当前行
autocmd InsertEnter * se cul " 用浅色高亮当前行
set ruler " 显示标尺 
set scrolloff=3 " 光标移动到buffer的顶部和底部时保持3行距离
set fdm=marker  " 代码折叠

set ts=4
set softtabstop=4
set shiftwidth=4
set expandtab
set autoindent
map <C-t> :NERDTreeToggle<CR>
"autocmd vimenter * NERDTree
let g:NERDTreeShowLineNumbers=1
let g:NERDTreeHidden=0
let g:NERDTreeSize=10

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
Plugin 'justinmk/vim-syntax-extra'
Plugin 'octol/vim-cpp-enhanced-highlight'
Bundle 'The-NERD-tree'
Bundle 'The-NERD-Commenter'
"Bundle 'ycm-core/YouCompleteMe'
Bundle 'cscope_maps.vim'
"所有插件都应该在这一行之前
call vundle#end()

"""
"cpp-enhanced-highlight
"高亮类，成员函数，标准库和模板
let g:cpp_class_scope_highlight = 1
let g:cpp_member_variable_highlight = 1
let g:cpp_concepts_highlight = 1
"let g:cpp_experimental_simple_template_highlight = 1
"文件较大时使用下面的设置高亮模板速度较快，但会有一些小错误
let g:cpp_experimental_template_highlight = 1
"""

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
