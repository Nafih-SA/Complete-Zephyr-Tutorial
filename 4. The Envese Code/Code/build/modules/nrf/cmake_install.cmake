# Install script for directory: C:/Users/Vinayan/ncs/v1.3.0/nrf

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/Zephyr-Kernel")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "TRUE")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("C:/Users/Vinayan/Desktop/SA/Enverse/code/enverse/i2c_fujitsu_fram/build/modules/nrf/ext/cmake_install.cmake")
  include("C:/Users/Vinayan/Desktop/SA/Enverse/code/enverse/i2c_fujitsu_fram/build/modules/nrf/lib/cmake_install.cmake")
  include("C:/Users/Vinayan/Desktop/SA/Enverse/code/enverse/i2c_fujitsu_fram/build/modules/nrf/samples/cmake_install.cmake")
  include("C:/Users/Vinayan/Desktop/SA/Enverse/code/enverse/i2c_fujitsu_fram/build/modules/nrf/subsys/cmake_install.cmake")
  include("C:/Users/Vinayan/Desktop/SA/Enverse/code/enverse/i2c_fujitsu_fram/build/modules/nrf/drivers/cmake_install.cmake")
  include("C:/Users/Vinayan/Desktop/SA/Enverse/code/enverse/i2c_fujitsu_fram/build/modules/nrf/tests/cmake_install.cmake")

endif()
