
(cl:in-package :asdf)

(defsystem "nodes-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :std_msgs-msg
)
  :components ((:file "_package")
    (:file "Point" :depends-on ("_package_Point"))
    (:file "_package_Point" :depends-on ("_package"))
    (:file "PointStamped" :depends-on ("_package_PointStamped"))
    (:file "_package_PointStamped" :depends-on ("_package"))
  ))