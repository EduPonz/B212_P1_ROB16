# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "nodes: 4 messages, 0 services")

set(MSG_I_FLAGS "-Inodes:/home/eduponz/B212_P1_ROB16/src/nodes/msg;-Istd_msgs:/opt/ros/kinetic/share/std_msgs/cmake/../msg;-Igeometry_msgs:/opt/ros/kinetic/share/geometry_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(geneus REQUIRED)
find_package(genlisp REQUIRED)
find_package(gennodejs REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(nodes_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/eduponz/B212_P1_ROB16/src/nodes/msg/PointStamped.msg" NAME_WE)
add_custom_target(_nodes_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "nodes" "/home/eduponz/B212_P1_ROB16/src/nodes/msg/PointStamped.msg" "nodes/Point:std_msgs/Header"
)

get_filename_component(_filename "/home/eduponz/B212_P1_ROB16/src/nodes/msg/Point.msg" NAME_WE)
add_custom_target(_nodes_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "nodes" "/home/eduponz/B212_P1_ROB16/src/nodes/msg/Point.msg" ""
)

#
#  langs = gencpp;geneus;genlisp;gennodejs;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(nodes
  "/home/eduponz/B212_P1_ROB16/src/nodes/msg/PointStamped.msg"
  "${MSG_I_FLAGS}"
  "/home/eduponz/B212_P1_ROB16/src/nodes/msg/Point.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/nodes
)
_generate_msg_cpp(nodes
  "/home/eduponz/B212_P1_ROB16/src/nodes/msg/Point.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/nodes
)

### Generating Services

### Generating Module File
_generate_module_cpp(nodes
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/nodes
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(nodes_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(nodes_generate_messages nodes_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/eduponz/B212_P1_ROB16/src/nodes/msg/PointStamped.msg" NAME_WE)
add_dependencies(nodes_generate_messages_cpp _nodes_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/eduponz/B212_P1_ROB16/src/nodes/msg/Point.msg" NAME_WE)
add_dependencies(nodes_generate_messages_cpp _nodes_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(nodes_gencpp)
add_dependencies(nodes_gencpp nodes_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS nodes_generate_messages_cpp)

### Section generating for lang: geneus
### Generating Messages
_generate_msg_eus(nodes
  "/home/eduponz/B212_P1_ROB16/src/nodes/msg/PointStamped.msg"
  "${MSG_I_FLAGS}"
  "/home/eduponz/B212_P1_ROB16/src/nodes/msg/Point.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/nodes
)
_generate_msg_eus(nodes
  "/home/eduponz/B212_P1_ROB16/src/nodes/msg/Point.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/nodes
)

### Generating Services

### Generating Module File
_generate_module_eus(nodes
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/nodes
  "${ALL_GEN_OUTPUT_FILES_eus}"
)

add_custom_target(nodes_generate_messages_eus
  DEPENDS ${ALL_GEN_OUTPUT_FILES_eus}
)
add_dependencies(nodes_generate_messages nodes_generate_messages_eus)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/eduponz/B212_P1_ROB16/src/nodes/msg/PointStamped.msg" NAME_WE)
add_dependencies(nodes_generate_messages_eus _nodes_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/eduponz/B212_P1_ROB16/src/nodes/msg/Point.msg" NAME_WE)
add_dependencies(nodes_generate_messages_eus _nodes_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(nodes_geneus)
add_dependencies(nodes_geneus nodes_generate_messages_eus)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS nodes_generate_messages_eus)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(nodes
  "/home/eduponz/B212_P1_ROB16/src/nodes/msg/PointStamped.msg"
  "${MSG_I_FLAGS}"
  "/home/eduponz/B212_P1_ROB16/src/nodes/msg/Point.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/nodes
)
_generate_msg_lisp(nodes
  "/home/eduponz/B212_P1_ROB16/src/nodes/msg/Point.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/nodes
)

### Generating Services

### Generating Module File
_generate_module_lisp(nodes
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/nodes
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(nodes_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(nodes_generate_messages nodes_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/eduponz/B212_P1_ROB16/src/nodes/msg/PointStamped.msg" NAME_WE)
add_dependencies(nodes_generate_messages_lisp _nodes_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/eduponz/B212_P1_ROB16/src/nodes/msg/Point.msg" NAME_WE)
add_dependencies(nodes_generate_messages_lisp _nodes_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(nodes_genlisp)
add_dependencies(nodes_genlisp nodes_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS nodes_generate_messages_lisp)

### Section generating for lang: gennodejs
### Generating Messages
_generate_msg_nodejs(nodes
  "/home/eduponz/B212_P1_ROB16/src/nodes/msg/PointStamped.msg"
  "${MSG_I_FLAGS}"
  "/home/eduponz/B212_P1_ROB16/src/nodes/msg/Point.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/nodes
)
_generate_msg_nodejs(nodes
  "/home/eduponz/B212_P1_ROB16/src/nodes/msg/Point.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/nodes
)

### Generating Services

### Generating Module File
_generate_module_nodejs(nodes
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/nodes
  "${ALL_GEN_OUTPUT_FILES_nodejs}"
)

add_custom_target(nodes_generate_messages_nodejs
  DEPENDS ${ALL_GEN_OUTPUT_FILES_nodejs}
)
add_dependencies(nodes_generate_messages nodes_generate_messages_nodejs)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/eduponz/B212_P1_ROB16/src/nodes/msg/PointStamped.msg" NAME_WE)
add_dependencies(nodes_generate_messages_nodejs _nodes_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/eduponz/B212_P1_ROB16/src/nodes/msg/Point.msg" NAME_WE)
add_dependencies(nodes_generate_messages_nodejs _nodes_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(nodes_gennodejs)
add_dependencies(nodes_gennodejs nodes_generate_messages_nodejs)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS nodes_generate_messages_nodejs)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(nodes
  "/home/eduponz/B212_P1_ROB16/src/nodes/msg/PointStamped.msg"
  "${MSG_I_FLAGS}"
  "/home/eduponz/B212_P1_ROB16/src/nodes/msg/Point.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/nodes
)
_generate_msg_py(nodes
  "/home/eduponz/B212_P1_ROB16/src/nodes/msg/Point.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/nodes
)

### Generating Services

### Generating Module File
_generate_module_py(nodes
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/nodes
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(nodes_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(nodes_generate_messages nodes_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/eduponz/B212_P1_ROB16/src/nodes/msg/PointStamped.msg" NAME_WE)
add_dependencies(nodes_generate_messages_py _nodes_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/eduponz/B212_P1_ROB16/src/nodes/msg/Point.msg" NAME_WE)
add_dependencies(nodes_generate_messages_py _nodes_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(nodes_genpy)
add_dependencies(nodes_genpy nodes_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS nodes_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/nodes)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/nodes
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(nodes_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()
if(TARGET geometry_msgs_generate_messages_cpp)
  add_dependencies(nodes_generate_messages_cpp geometry_msgs_generate_messages_cpp)
endif()

if(geneus_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/nodes)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/nodes
    DESTINATION ${geneus_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_eus)
  add_dependencies(nodes_generate_messages_eus std_msgs_generate_messages_eus)
endif()
if(TARGET geometry_msgs_generate_messages_eus)
  add_dependencies(nodes_generate_messages_eus geometry_msgs_generate_messages_eus)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/nodes)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/nodes
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(nodes_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()
if(TARGET geometry_msgs_generate_messages_lisp)
  add_dependencies(nodes_generate_messages_lisp geometry_msgs_generate_messages_lisp)
endif()

if(gennodejs_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/nodes)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/nodes
    DESTINATION ${gennodejs_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_nodejs)
  add_dependencies(nodes_generate_messages_nodejs std_msgs_generate_messages_nodejs)
endif()
if(TARGET geometry_msgs_generate_messages_nodejs)
  add_dependencies(nodes_generate_messages_nodejs geometry_msgs_generate_messages_nodejs)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/nodes)
  install(CODE "execute_process(COMMAND \"/usr/bin/python\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/nodes\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/nodes
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(nodes_generate_messages_py std_msgs_generate_messages_py)
endif()
if(TARGET geometry_msgs_generate_messages_py)
  add_dependencies(nodes_generate_messages_py geometry_msgs_generate_messages_py)
endif()
