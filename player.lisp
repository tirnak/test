 (load "quicklisp.lisp")
 (quicklisp-quickstart:install)
 (ql:quickload "cl-cffi-gtk")

(defpackage :player-package
  (:use :gtk :gdk :gdk-pixbuf :gobject
   :glib :gio :pango :cairo :common-lisp))

(in-package :player-package)

(defun player ()
  (within-main-loop
    (let ((window (make-instance 'gtk-window
               :type :toplevel
               :title "The Lisp Player"
               :border-width 12
               :default-width 300))
           (grid (make-instance 'gtk-grid
               :column-homogeneous t
               :row-homogeneous t))
           (fileChooser (make-instance 'gtk-file-chooser-widget
               :label "choose file to play"))
           (pause (make-instance 'gtk-switch
               :active t
               :label "pause")))
           (g-signal-connect window "destroy"
             (lambda (widget) 
               (declare (ignore widget))
               (progn 
                  (sb-ext:run-program "killall" (list "mpg321") :output t :search t)
                  (leave-gtk-main))))
           (g-signal-connect pause "notify::active"
             (lambda (widget param)
               (declare (ignore param))
               (if (gtk-switch-active widget)
                 (sb-ext:run-program "pkill" (list "-SIGCONT" "mpg321") :output t :search t)
                 (sb-ext:run-program "pkill" (list "-SIGSTOP" "mpg321") :output t :search t))))
                 ;(gtk-button-set-label pause "continue")
                 ;(gtk-button-set-label pause "pause"))))
           (g-signal-connect fileChooser "file-activated"
            (lambda (widget)
              (declare (ignore widget))
                (progn 
                  (sb-ext:run-program "/usr/bin/killall" (list "mpg321")
                    :output t)
                  (format t "File set: ~A~%"
                    (gtk-file-chooser-get-filename fileChooser))
                  (sb-ext:run-program "mpg321" (list (gtk-file-chooser-get-filename fileChooser))
                    :output t :wait nil :search t))))
      (gtk-grid-attach grid fileChooser 0 0 2 2)
      (gtk-grid-attach grid pause    0 2 2 1)
      (gtk-container-add window grid)
      (gtk-widget-show-all window))))


(player)
