
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; MODULE      : kbd-general.scm
;; DESCRIPTION : general keyboard shortcuts for all modes
;; COPYRIGHT   : (C) 1999  Joris van der Hoeven
;;
;; This software falls under the GNU general public license and comes WITHOUT
;; ANY WARRANTY WHATSOEVER. See the file $TEXMACS_PATH/LICENSE for details.
;; If you don't have this file, write to the Free Software Foundation, Inc.,
;; 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(texmacs-module (keyboard kbd-general)
  (:use
    (texmacs texmacs tm-files) (texmacs texmacs tm-help)
    (texmacs texmacs tm-print)
    (texmacs edit edit-hybrid) (texmacs edit edit-fold)
    (texmacs edit edit-misc)
    (texmacs tools tm-cursor) (texmacs tools tm-circulate)
    (texmacs tools tm-bracket)))

(kbd-map
  ("cmd" "" "Execute a TeXmacs command")
  ("noop" (set-message "" ""))
  ("symbol" "" "Insert a TeXmacs symbol")

  ("space" (insert-string " "))
  ("return" (make-return))
  ("backspace" (general-remove #f))
  ("delete" (general-remove #t))
  ("tab" (general-tab))
  ("S-space" (insert-string " "))
  ("S-return" (make-shift-return))
  ("S-backspace" (general-remove #f))
  ("S-delete" (general-remove #t))
  ("C-backspace" (remove-structure-upwards))
  ("C-delete" (remove-structure-upwards))
  ("C-tab" (variant-circulate #t))
  ("C-S-tab" (variant-circulate #f))
  ("A-space" (make-space "0.2spc"))
  ("A-S-space" (make-space "-0.2spc"))
  ("A-backspace" (structured-remove #f))
  ("A-delete" (structured-remove #t))
  ("A-tab" (make-htab "5mm"))
  ("M-space" (make-space "0.2spc"))
  ("M-S-space" (make-space "-0.2spc"))
  ("M-backspace" (position-default))
  ("M-delete" (position-default))
  ("M-tab" (make-htab "5mm"))
  ("escape tab" (noop) (make-htab "5mm"))

  ("left" (cursor-left))
  ("right" (cursor-right))
  ("up" (cursor-up))
  ("down" (cursor-down))
  ("home" (cursor-start-line))
  ("end" (cursor-end-line))
  ("pageup" (cursor-page-up))
  ("pagedown" (cursor-page-down))
  ("S-left" (cursor-select cursor-left))
  ("S-right" (cursor-select cursor-right))
  ("S-up" (cursor-select cursor-up))
  ("S-down" (cursor-select cursor-down))
  ("S-home" (cursor-select cursor-start-line))
  ("S-end" (cursor-select cursor-end-line))
  ("S-pageup" (cursor-select cursor-page-up))
  ("S-pagedown" (cursor-select cursor-page-down))
  ("C-left" (structured-left))
  ("C-right" (structured-right))
  ("C-up" (structured-up))
  ("C-down" (structured-down))
  ("C-home" (structured-start))
  ("C-end" (structured-end))
  ("C-pageup" (structured-top))
  ("C-pagedown" (structured-bottom))
  ("A-left" (structured-insert-left))
  ("A-right" (structured-insert-right))
  ("A-up" (structured-insert-up))
  ("A-down" (structured-insert-down))
  ("A-home" (structured-insert-start))
  ("A-end" (structured-insert-end))
  ("A-pageup" (structured-insert-top))
  ("A-pagedown" (structured-insert-bottom))
  ("M-left" (position-left))
  ("M-right" (position-right))
  ("M-up" (position-up))
  ("M-down" (position-down))
  ("M-home" (position-start))
  ("M-end" (position-end))
  ("M-pageup" (position-top))
  ("M-pagedown" (position-bottom))
  ("M-A-left" (switch-to "previous"))
  ("M-A-right" (switch-to "next"))
  ("M-A-up" (switch-to "first"))
  ("M-A-down" (switch-to "last"))
  ("M-A-home" (selection-set-start) (select-from-keyboard #t))
  ("M-A-end" (selection-set-end) (select-from-keyboard #f))
  ("M-A-pageup" (fold))
  ("M-A-pagedown" (unfold))

  ("F1" (interactive '("Search words in the documentation:") 'docgrep-in-doc))
  ("S-F1" (load-help-buffer "about/welcome/welcome"))
  ("F2" (choose-file "Load file" "" 'load-buffer))
  ("S-F2" (choose-file "Load file" "" 'load-in-new-window))
  ("C-F2" (revert-buffer))
  ("M-F2" (new-buffer))
  ("M-S-F2" (open-window))
  ("M-C-F2" (clone-window))
  ("F3" (save-buffer))
  ("S-F3" (choose-file "Save TeXmacs file" "texmacs" 'save-buffer))
  ("F4" (print))
  ("S-F4" (interactive '("File name:") 'print-to-file))
  ("C-F4" (preview-with-ghostview))
  ("M-F4" (interactive '("First page:" "Last page:") 'print-pages))
  ("M-S-F4" (interactive
	     '("File name:" "First page:" "Last page:")
	     'print-pages-to-file))

  ("undo" (noop) (undo))
  ("redo" (noop) (redo))
  ("cancel" (noop) (clipboard-clear "primary"))
  ("cut" (noop) (clipboard-cut "primary"))
  ("paste" (noop) (clipboard-paste "primary"))
  ("copy" (noop) (clipboard-copy "primary"))
  ("find" (noop) (search-start #t))

  ("<" "<less>")
  (">" "<gtr>")
  ("(" (make-bracket-open "(" ")"))
  (")" (make-bracket-close ")" "("))
  ("[" (make-bracket-open "[" "]"))
  ("]" (make-bracket-close "]" "["))
  ("{" (make-bracket-open "{" "}"))
  ("}" (make-bracket-close "}" "{"))
  ("\\" (if (or (inside? "hybrid") (in-prog?))
	    (insert-string "\\")
	    (make-inactive-hybrid)))
  ("M-\\" (make-inactive-hybrid))
  ("accent:hat" "^")
  ("accent:deadhat" "^")
  ("accent:tilde" "~")
  ("accent:acute" "'")
  ("accent:grave" "`")
  ("symbol \\" "\\")
  ("symbol $" "$")
  ("symbol &" "&")
  ("symbol #" "#")
  ("symbol �" "�")
  ("symbol %" "%")
  ("symbol _" "_")
  ("symbol ^" "^"))

(kbd-map ;; inserting tables
  ("table" "" "Table command")
  ("table N" "" "New table (t: tabular, b: block)")
  ("table N t" (make-compound-arg "tabular"))
  ("table N T" (make-compound-arg "tabular*"))
  ("table N b" (make-compound-arg "block"))
  ("table N B" (make-compound-arg "block*")))

(kbd-map like-old?
  ("tab" (if (or (is-deactivated?) (in-preamble-mode?) (inside? "tuple"))
	     (insert-argument #t)
	     (make-htab "5mm")))
  ("A-backspace" (make-space "-0.2spc"))
  ("A-delete" (cell-del-format ""))
  ("M-backspace" (remove-structure-upwards))
  ("M-delete" (remove-structure-upwards))

  ("C-home" (selection-set-start) (select-from-keyboard #t))
  ("C-end" (selection-set-end) (select-from-keyboard #f))
  ("A-left" (position-left))
  ("A-right" (position-right))
  ("A-up" (position-up))
  ("A-down" (position-down))
  ("A-pageup" (switch-to "previous"))
  ("A-pagedown" (switch-to "next"))
  ("A-home" (switch-to "first"))
  ("A-end" (switch-to "last"))
  ("M-left" (structured-insert-left))
  ("M-right" (structured-insert-right))
  ("M-up" (structured-insert-up))
  ("M-down" (structured-insert-down)))
