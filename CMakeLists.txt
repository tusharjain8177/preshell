# Preshell - Interactive C/C++ preprocessor shell
# Copyright (C) 2013, Abel Sinkovics (abel@sinkovics.hu)
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

cmake_minimum_required(VERSION 2.6)

project(preshell)
set(CMAKE_PROJECT_NAME preshell)
set(MAJOR_VERSION 1)
set(MINOR_VERSION 0)
set(PATCH_VERSION 0)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

# Version macros
add_definitions(-DPRESHELL_MAJOR=${MAJOR_VERSION})
add_definitions(-DPRESHELL_MINOR=${MINOR_VERSION})
add_definitions(-DPRESHELL_PATCH=${PATCH_VERSION})

# Boost
# Turn this on to link statically against Boost
# set(Boost_USE_STATIC_LIBS ON)
find_package(Boost COMPONENTS
  system # used by Wave
  thread # used by Wave
  filesystem # used by Wave
  wave
  program_options
)
find_package(Threads) # used by Boost.Thread

include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIRS})

set(
  BOOST_VER
  "${Boost_MAJOR_VERSION}.${Boost_MINOR_VERSION}.${Boost_SUBMINOR_VERSION}"
)


include_directories("include")

# Readline
find_package(Readline)

# Unit testing
enable_testing()

# Recursing
subdirs(lib test app)

# Debian package
if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  set(CMAKE_INSTALL_PREFIX "/usr")
endif()

if(EXISTS "${CMAKE_ROOT}/Modules/CPack.cmake")
  include(InstallRequiredSystemLibraries)
   
  set(CPACK_SET_DESTDIR "on")
  set(CPACK_PACKAGING_INSTALL_PREFIX "/tmp")
  set(CPACK_GENERATOR "DEB")
   
  set(CPACK_PACKAGE_DESCRIPTION "Preshell")
  set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "It is an interactive C preprocessor shell")
  set(CPACK_PACKAGE_VENDOR "Abel Sinkovics")
  set(CPACK_PACKAGE_CONTACT "abel@sinkovics.hu")
  set(CPACK_PACKAGE_VERSION_MAJOR "${MAJOR_VERSION}")
  set(CPACK_PACKAGE_VERSION_MINOR "${MINOR_VERSION}")
  set(CPACK_PACKAGE_VERSION_PATCH "${PATCH_VERSION}")
  set(CPACK_PACKAGE_FILE_NAME "${CMAKE_PROJECT_NAME}_${MAJOR_VERSION}.${MINOR_VERSION}.${CPACK_PACKAGE_VERSION_PATCH}_${CMAKE_SYSTEM_PROCESSOR}")
  set(CPACK_SOURCE_PACKAGE_FILE_NAME "${CMAKE_PROJECT_NAME}_${MAJOR_VERSION}.${MINOR_VERSION}.${CPACK_PACKAGE_VERSION_PATCH}")

  set(CPACK_DEBIAN_PACKAGE_DEPENDS "libboost-system${BOOST_VER}, libboost-thread${BOOST_VER}, libboost-filesystem${BOOST_VER}, libboost-wave${BOOST_VER}, libboost-program-options${BOOST_VER}")
  set(CPACK_DEBIAN_PACKAGE_PRIORITY "optional")
  set(CPACK_DEBIAN_PACKAGE_SECTION "devel")
  set(CPACK_DEBIAN_ARCHITECTURE ${CMAKE_SYSTEM_PROCESSOR})
   
  set(CPACK_COMPONENTS_ALL Libraries ApplicationData)
  include(CPack)
   
endif(EXISTS "${CMAKE_ROOT}/Modules/CPack.cmake")


