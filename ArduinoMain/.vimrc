call plug#begin()
Plug 'jacoborus/tender.vim'
Plug 'vim-airline/vim-airline'
Plug 'vim-airline/vim-airline-themes'
Plug 'preservim/nerdtree'
Plug 'Valloric/YouCompleteMe'
call plug#end() 

syntax enable

set number
set relativenumber
set tabstop=2
set softtabstop=2
set shiftwidth=2
set smarttab
set expandtab
set smartindent

colorscheme tender


function! BuildFunc()
  execute "wall"
  execute "!arduino-cli"
endfunction

command Build call BuildFunc()

