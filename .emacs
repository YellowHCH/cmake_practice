(require 'package)
(add-to-list 'package-archives '("melpa" . "http://melpa.org/packages/") t)
(when (< emacs-major-version 24)
  (add-to-list 'package-archives '("gnu" . "http://elpa.gnu.org/packages/")))
(package-initialize)
(custom-set-variables
 ;; custom-set-variables was added by Custom.
 ;; If you edit it by hand, you could mess it up, so be careful.
 ;; Your init file should contain only one such instance.
 ;; If there is more than one, they won't work right.
 '(package-selected-packages
   (quote
    (org-mime smart-tabs-mode highlight-symbol highlight-parentheses dired-sidebar helm-gtags ggtags company-native-complete company-irony-c-headers company-c-headers company auto-scroll-mode auto-highlight-symbol auto-complete-clang auto-complete-c-headers auto-complete))))
(custom-set-faces
 ;; custom-set-faces was added by Custom.
 ;; If you edit it by hand, you could mess it up, so be careful.
 ;; Your init file should contain only one such instance.
 ;; If there is more than one, they won't work right.
 )

(add-to-list 'load-path "/home/zjuerhuang/.emacs.d/elpa/auto-complete-20170125.245")
(require 'auto-complete-config)
(add-to-list 'ac-dictionary-directories "/home/zjuerhuang/.emacs.d/elpa/auto-complete-20170125.245/dict")
(ac-config-default) 

(require 'highlight-symbol)
(global-set-key [(control f3)] 'highlight-symbol)
(global-set-key [f3] 'highlight-symbol-next)
(global-set-key [(shift f3)] 'highlight-symbol-prev)
(global-set-key [(meta f3)] 'highlight-symbol-query-replace)

(setq-default indent-tabs-mode nil)
(setq-default tab-width 8)
(setq indent-line-function 'insert-tab)
(setq c-default-style "linux")

;;(define-globalized-minor-mode real-global-auto-complete-mode
;;  auto-complete-mode (lambda ()
;;                       (if (not (minibufferp (current-buffer)))
;;                           (auto-complete-mode 1))
;;                       ))
;;(real-global-auto-complete-mode t)

(global-auto-revert-mode) 
(setq c-basic-offset 8)
;; code block
(add-hook 'c-mode-hook 'hs-minor-mode)
(add-hook 'c++-mode-hook 'hs-minor-mode)
(add-hook 'c-mode-hook
           (lambda ()
             (local-set-key (kbd "C-c  [") 'hs-hide-block)
             (local-set-key (kbd "C-c  ]") 'hs-hide-block)))
(add-hook 'c++-mode-hook
          (lambda ()
            (local-set-key (kbd "C-c  [") 'hs-hide-block)
            (local-set-key (kbd "C-c  ]") 'hs-show-block)))

;;
(add-hook 'emacs-lisp-mode-hook 'show-paren-mode)


;;
(add-to-list 'load-path "/home/zjuerhuang/.emacs.d/elpa/myKiss")
(require 'idle-highlight-mode)
(autoload 'idle-highlight-mode "idle-highlight" "highlight the word the point is on" t)
(add-hook 'find-file-hook 'idle-highlight-mode)
