# generated from catkin/cmake/template/pkgConfig.cmake.in

# append elements to a list and remove existing duplicates from the list
# copied from catkin/cmake/list_append_deduplicate.cmake to keep pkgConfig
# self contained
macro(_list_append_deduplicate listname)
  if(NOT "${ARGN}" STREQUAL "")
    if(${listname})
      list(REMOVE_ITEM ${listname} ${ARGN})
    endif()
    list(APPEND ${listname} ${ARGN})
  endif()
endmacro()

# append elements to a list if they are not already in the list
# copied from catkin/cmake/list_append_unique.cmake to keep pkgConfig
# self contained
macro(_list_append_unique listname)
  foreach(_item ${ARGN})
    list(FIND ${listname} ${_item} _index)
    if(_index EQUAL -1)
      list(APPEND ${listname} ${_item})
    endif()
  endforeach()
endmacro()

# pack a list of libraries with optional build configuration keywords
# copied from catkin/cmake/catkin_libraries.cmake to keep pkgConfig
# self contained
macro(_pack_libraries_with_build_configuration VAR)
  set(${VAR} "")
  set(_argn ${ARGN})
  list(LENGTH _argn _count)
  set(_index 0)
  while(${_index} LESS ${_count})
    list(GET _argn ${_index} lib)
    if("${lib}" MATCHES "^(debug|optimized|general)$")
      math(EXPR _index "${_index} + 1")
      if(${_index} EQUAL ${_count})
        message(FATAL_ERROR "_pack_libraries_with_build_configuration() the list of libraries '${ARGN}' ends with '${lib}' which is a build configuration keyword and must be followed by a library")
      endif()
      list(GET _argn ${_index} library)
      list(APPEND ${VAR} "${lib}${CATKIN_BUILD_CONFIGURATION_KEYWORD_SEPARATOR}${library}")
    else()
      list(APPEND ${VAR} "${lib}")
    endif()
    math(EXPR _index "${_index} + 1")
  endwhile()
endmacro()

# unpack a list of libraries with optional build configuration keyword prefixes
# copied from catkin/cmake/catkin_libraries.cmake to keep pkgConfig
# self contained
macro(_unpack_libraries_with_build_configuration VAR)
  set(${VAR} "")
  foreach(lib ${ARGN})
    string(REGEX REPLACE "^(debug|optimized|general)${CATKIN_BUILD_CONFIGURATION_KEYWORD_SEPARATOR}(.+)$" "\\1;\\2" lib "${lib}")
    list(APPEND ${VAR} "${lib}")
  endforeach()
endmacro()


if(ugv_control_CONFIG_INCLUDED)
  return()
endif()
set(ugv_control_CONFIG_INCLUDED TRUE)

# set variables for source/devel/install prefixes
if("FALSE" STREQUAL "TRUE")
  set(ugv_control_SOURCE_PREFIX /home/michel/UGVControl/src/ugv_control)
  set(ugv_control_DEVEL_PREFIX /home/michel/UGVControl/devel)
  set(ugv_control_INSTALL_PREFIX "")
  set(ugv_control_PREFIX ${ugv_control_DEVEL_PREFIX})
else()
  set(ugv_control_SOURCE_PREFIX "")
  set(ugv_control_DEVEL_PREFIX "")
  set(ugv_control_INSTALL_PREFIX /home/michel/UGVControl/install)
  set(ugv_control_PREFIX ${ugv_control_INSTALL_PREFIX})
endif()

# warn when using a deprecated package
if(NOT "" STREQUAL "")
  set(_msg "WARNING: package 'ugv_control' is deprecated")
  # append custom deprecation text if available
  if(NOT "" STREQUAL "TRUE")
    set(_msg "${_msg} ()")
  endif()
  message("${_msg}")
endif()

# flag project as catkin-based to distinguish if a find_package()-ed project is a catkin project
set(ugv_control_FOUND_CATKIN_PROJECT TRUE)

if(NOT " " STREQUAL " ")
  set(ugv_control_INCLUDE_DIRS "")
  set(_include_dirs "")
  foreach(idir ${_include_dirs})
    if(IS_ABSOLUTE ${idir} AND IS_DIRECTORY ${idir})
      set(include ${idir})
    elseif("${idir} " STREQUAL "include ")
      get_filename_component(include "${ugv_control_DIR}/../../../include" ABSOLUTE)
      if(NOT IS_DIRECTORY ${include})
        message(FATAL_ERROR "Project 'ugv_control' specifies '${idir}' as an include dir, which is not found.  It does not exist in '${include}'.  Ask the maintainer 'mike <mike@todo.todo>' to fix it.")
      endif()
    else()
      message(FATAL_ERROR "Project 'ugv_control' specifies '${idir}' as an include dir, which is not found.  It does neither exist as an absolute directory nor in '/home/michel/UGVControl/install/${idir}'.  Ask the maintainer 'mike <mike@todo.todo>' to fix it.")
    endif()
    _list_append_unique(ugv_control_INCLUDE_DIRS ${include})
  endforeach()
endif()

set(libraries "")
foreach(library ${libraries})
  # keep build configuration keywords, target names and absolute libraries as-is
  if("${library}" MATCHES "^(debug|optimized|general)$")
    list(APPEND ugv_control_LIBRARIES ${library})
  elseif(TARGET ${library})
    list(APPEND ugv_control_LIBRARIES ${library})
  elseif(IS_ABSOLUTE ${library})
    list(APPEND ugv_control_LIBRARIES ${library})
  else()
    set(lib_path "")
    set(lib "${library}-NOTFOUND")
    # since the path where the library is found is returned we have to iterate over the paths manually
    foreach(path /home/michel/UGVControl/install/lib;/home/michel/husky_ws/devel/lib;/home/michel/catkin_ws/devel/lib;/home/michel/Documents/husky_kinetic/devel/lib;/opt/ros/kinetic/lib)
      find_library(lib ${library}
        PATHS ${path}
        NO_DEFAULT_PATH NO_CMAKE_FIND_ROOT_PATH)
      if(lib)
        set(lib_path ${path})
        break()
      endif()
    endforeach()
    if(lib)
      _list_append_unique(ugv_control_LIBRARY_DIRS ${lib_path})
      list(APPEND ugv_control_LIBRARIES ${lib})
    else()
      # as a fall back for non-catkin libraries try to search globally
      find_library(lib ${library})
      if(NOT lib)
        message(FATAL_ERROR "Project '${PROJECT_NAME}' tried to find library '${library}'.  The library is neither a target nor built/installed properly.  Did you compile project 'ugv_control'?  Did you find_package() it before the subdirectory containing its code is included?")
      endif()
      list(APPEND ugv_control_LIBRARIES ${lib})
    endif()
  endif()
endforeach()

set(ugv_control_EXPORTED_TARGETS "ugv_control_generate_messages_cpp;ugv_control_generate_messages_eus;ugv_control_generate_messages_lisp;ugv_control_generate_messages_nodejs;ugv_control_generate_messages_py")
# create dummy targets for exported code generation targets to make life of users easier
foreach(t ${ugv_control_EXPORTED_TARGETS})
  if(NOT TARGET ${t})
    add_custom_target(${t})
  endif()
endforeach()

set(depends "")
foreach(depend ${depends})
  string(REPLACE " " ";" depend_list ${depend})
  # the package name of the dependency must be kept in a unique variable so that it is not overwritten in recursive calls
  list(GET depend_list 0 ugv_control_dep)
  list(LENGTH depend_list count)
  if(${count} EQUAL 1)
    # simple dependencies must only be find_package()-ed once
    if(NOT ${ugv_control_dep}_FOUND)
      find_package(${ugv_control_dep} REQUIRED NO_MODULE)
    endif()
  else()
    # dependencies with components must be find_package()-ed again
    list(REMOVE_AT depend_list 0)
    find_package(${ugv_control_dep} REQUIRED NO_MODULE ${depend_list})
  endif()
  _list_append_unique(ugv_control_INCLUDE_DIRS ${${ugv_control_dep}_INCLUDE_DIRS})

  # merge build configuration keywords with library names to correctly deduplicate
  _pack_libraries_with_build_configuration(ugv_control_LIBRARIES ${ugv_control_LIBRARIES})
  _pack_libraries_with_build_configuration(_libraries ${${ugv_control_dep}_LIBRARIES})
  _list_append_deduplicate(ugv_control_LIBRARIES ${_libraries})
  # undo build configuration keyword merging after deduplication
  _unpack_libraries_with_build_configuration(ugv_control_LIBRARIES ${ugv_control_LIBRARIES})

  _list_append_unique(ugv_control_LIBRARY_DIRS ${${ugv_control_dep}_LIBRARY_DIRS})
  list(APPEND ugv_control_EXPORTED_TARGETS ${${ugv_control_dep}_EXPORTED_TARGETS})
endforeach()

set(pkg_cfg_extras "ugv_control-msg-extras.cmake")
foreach(extra ${pkg_cfg_extras})
  if(NOT IS_ABSOLUTE ${extra})
    set(extra ${ugv_control_DIR}/${extra})
  endif()
  include(${extra})
endforeach()
