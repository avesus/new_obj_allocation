# Install script for directory: /home/noah/programs/branch_2/new_obj_allocation/folly-master

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
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

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/build/libfolly.a")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/build/libfolly_test_util.a")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/AtomicHashArray-inl.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/AtomicHashArray.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/AtomicHashMap-inl.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/AtomicHashMap.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/AtomicIntrusiveLinkedList.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/AtomicLinkedList.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/AtomicUnorderedMap.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/Benchmark.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/Bits.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/CPortability.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/CancellationToken-inl.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/CancellationToken.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/Chrono.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/ClockGettimeWrappers.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/ConcurrentBitSet.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/ConcurrentSkipList-inl.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/ConcurrentSkipList.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/ConstexprMath.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/Conv.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/CppAttributes.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/CpuId.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/DefaultKeepAliveExecutor.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/Demangle.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/DiscriminatedPtr.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/DynamicConverter.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/Exception.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/ExceptionString.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/ExceptionWrapper-inl.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/ExceptionWrapper.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/Executor.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/Expected.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/FBString.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/FBVector.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/File.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/FileUtil.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/Fingerprint.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/FixedString.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/Format-inl.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/Format.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/FormatArg.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/FormatTraits.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/Function.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/GLog.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/GroupVarint.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/Hash.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/IPAddress.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/IPAddressException.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/IPAddressV4.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/IPAddressV6.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/Indestructible.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/IndexedMemPool.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/IntrusiveList.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/Lazy.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/Likely.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/LockTraits.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/MPMCPipeline.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/MPMCQueue.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/MacAddress.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/MapUtil.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/Math.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/Memory.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/MicroLock.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/MicroSpinLock.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/MoveWrapper.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/Optional.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/Overload.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/PackedSyncPtr.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/Padded.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/Poly-inl.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/Poly.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/PolyException.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/Portability.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/Preprocessor.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/ProducerConsumerQueue.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/RWSpinLock.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/Random-inl.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/Random.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/Range.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/Replaceable.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/ScopeGuard.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/SharedMutex.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/Singleton-inl.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/Singleton.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/SingletonThreadLocal.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/SocketAddress.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/SpinLock.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/String-inl.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/String.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/Subprocess.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/Synchronized.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/SynchronizedPtr.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/ThreadCachedInt.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/ThreadLocal.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/TimeoutQueue.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/TokenBucket.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/Traits.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/Try-inl.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/Try.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/UTF8String.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/Unicode.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/Unit.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/Uri-inl.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/Uri.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/Utility.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/Varint.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/VirtualExecutor.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/dynamic-inl.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/dynamic.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/json.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/json_patch.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/json_pointer.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/small_vector.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/sorted_vector_types.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/stop_watch.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/chrono" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/chrono/Conv.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/chrono" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/chrono/Hardware.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/compression" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/compression/Compression.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/compression" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/compression/CompressionContextPool.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/compression" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/compression/CompressionContextPoolSingletons.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/compression" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/compression/CompressionCoreLocalContextPool.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/compression" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/compression/Utils.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/compression" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/compression/Zlib.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/compression" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/compression/Zstd.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/concurrency" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/concurrency/AtomicSharedPtr.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/concurrency" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/concurrency/CacheLocality.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/concurrency" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/concurrency/ConcurrentHashMap.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/concurrency" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/concurrency/CoreCachedSharedPtr.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/concurrency" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/concurrency/DynamicBoundedQueue.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/concurrency" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/concurrency/PriorityUnboundedQueueSet.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/concurrency" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/concurrency/QueueObserver.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/concurrency" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/concurrency/UnboundedQueue.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/concurrency/detail" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/concurrency/detail/AtomicSharedPtr-detail.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/concurrency/detail" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/concurrency/detail/ConcurrentHashMap-detail.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/container" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/container/Access.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/container" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/container/Array.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/container" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/container/BitIterator.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/container" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/container/Enumerate.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/container" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/container/EvictingCacheMap.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/container" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/container/F14Map-fwd.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/container" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/container/F14Map.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/container" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/container/F14Set-fwd.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/container" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/container/F14Set.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/container" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/container/Foreach-inl.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/container" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/container/Foreach.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/container" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/container/HeterogeneousAccess-fwd.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/container" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/container/HeterogeneousAccess.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/container" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/container/Iterator.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/container" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/container/Merge.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/container" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/container/SparseByteSet.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/container/detail" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/container/detail/BitIteratorDetail.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/container/detail" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/container/detail/F14Defaults.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/container/detail" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/container/detail/F14IntrinsicsAvailability.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/container/detail" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/container/detail/F14MapFallback.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/container/detail" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/container/detail/F14Mask.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/container/detail" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/container/detail/F14Policy.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/container/detail" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/container/detail/F14SetFallback.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/container/detail" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/container/detail/F14Table.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/container/detail" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/container/detail/Util.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/detail" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/detail/AsyncTrace.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/detail" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/detail/AtFork.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/detail" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/detail/AtomicHashUtils.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/detail" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/detail/AtomicUnorderedMapUtils.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/detail" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/detail/Demangle.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/detail" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/detail/DiscriminatedPtrDetail.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/detail" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/detail/FileUtilDetail.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/detail" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/detail/FingerprintPolynomial.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/detail" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/detail/Futex-inl.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/detail" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/detail/Futex.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/detail" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/detail/GroupVarintDetail.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/detail" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/detail/IPAddress.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/detail" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/detail/IPAddressSource.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/detail" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/detail/Iterators.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/detail" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/detail/MPMCPipelineDetail.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/detail" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/detail/MemoryIdler.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/detail" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/detail/PolyDetail.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/detail" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/detail/RangeCommon.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/detail" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/detail/RangeSse42.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/detail" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/detail/Singleton.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/detail" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/detail/SingletonStackTrace.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/detail" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/detail/SlowFingerprint.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/detail" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/detail/SocketFastOpen.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/detail" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/detail/Sse.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/detail" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/detail/StaticSingletonManager.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/detail" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/detail/ThreadLocalDetail.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/detail" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/detail/TurnSequencer.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/detail" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/detail/TypeList.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/detail" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/detail/UniqueInstance.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/executors" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/executors/Async.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/executors" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/executors/CPUThreadPoolExecutor.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/executors" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/executors/Codel.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/executors" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/executors/DrivableExecutor.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/executors" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/executors/EDFThreadPoolExecutor.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/executors" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/executors/ExecutorWithPriority-inl.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/executors" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/executors/ExecutorWithPriority.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/executors" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/executors/FiberIOExecutor.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/executors" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/executors/FutureExecutor.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/executors" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/executors/GlobalExecutor.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/executors" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/executors/GlobalThreadPoolList.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/executors" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/executors/IOExecutor.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/executors" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/executors/IOObjectCache.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/executors" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/executors/IOThreadPoolExecutor.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/executors" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/executors/InlineExecutor.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/executors" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/executors/ManualExecutor.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/executors" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/executors/QueuedImmediateExecutor.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/executors" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/executors/ScheduledExecutor.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/executors" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/executors/SequencedExecutor.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/executors" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/executors/SerialExecutor.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/executors" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/executors/SoftRealTimeExecutor.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/executors" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/executors/StrandExecutor.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/executors" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/executors/ThreadPoolExecutor.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/executors" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/executors/ThreadedExecutor.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/executors" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/executors/TimedDrivableExecutor.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/executors" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/executors/TimekeeperScheduledExecutor.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/executors/task_queue" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/executors/task_queue/BlockingQueue.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/executors/task_queue" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/executors/task_queue/LifoSemMPMCQueue.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/executors/task_queue" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/executors/task_queue/PriorityLifoSemMPMCQueue.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/executors/task_queue" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/executors/task_queue/PriorityUnboundedBlockingQueue.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/executors/task_queue" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/executors/task_queue/UnboundedBlockingQueue.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/executors/thread_factory" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/executors/thread_factory/InitThreadFactory.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/executors/thread_factory" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/executors/thread_factory/NamedThreadFactory.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/executors/thread_factory" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/executors/thread_factory/PriorityThreadFactory.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/executors/thread_factory" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/executors/thread_factory/ThreadFactory.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/AtomicReadMostlyMainPtr.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/AutoTimer.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/BitVectorCoding.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/Bits.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/Cleanup.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/CodingDetail.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/DynamicParser-inl.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/DynamicParser.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/EliasFanoCoding.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/EnvUtil.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/EventCount.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/ExecutionObserver.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/FlatCombiningPriorityQueue.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/FunctionScheduler.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/FutureDAG.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/Instructions.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/JSONSchema.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/JemallocHugePageAllocator.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/JemallocNodumpAllocator.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/LockFreeRingBuffer.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/NestedCommandLineApp.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/PrimaryPtr.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/ProgramOptions.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/QuotientMultiSet-inl.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/QuotientMultiSet.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/ReadMostlySharedPtr.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/RelaxedConcurrentPriorityQueue.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/STTimerFDTimeoutManager.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/Select64.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/SingleWriterFixedHashMap.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/SingletonRelaxedCounter.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/StampedPtr.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/StringKeyedCommon.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/StringKeyedMap.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/StringKeyedSet.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/StringKeyedUnorderedMap.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/StringKeyedUnorderedSet.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/TLRefCount.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/TestUtil.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/ThreadWheelTimekeeperHighRes.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/ThreadedRepeatingFunctionRunner.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/TimerFD.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/TimerFDTimeoutManager.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/TupleOps.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental/bser" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/bser/Bser.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental/coro" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/coro/Accumulate-inl.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental/coro" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/coro/Accumulate.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental/coro" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/coro/AsyncGenerator.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental/coro" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/coro/AsyncPipe.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental/coro" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/coro/AsyncScope.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental/coro" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/coro/Baton.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental/coro" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/coro/BlockingWait.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental/coro" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/coro/Collect-inl.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental/coro" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/coro/Collect.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental/coro" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/coro/Concat-inl.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental/coro" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/coro/Concat.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental/coro" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/coro/CurrentExecutor.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental/coro" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/coro/Dematerialize-inl.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental/coro" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/coro/Dematerialize.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental/coro" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/coro/DetachOnCancel.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental/coro" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/coro/Error.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental/coro" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/coro/Filter-inl.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental/coro" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/coro/Filter.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental/coro" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/coro/FutureUtil.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental/coro" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/coro/Generator.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental/coro" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/coro/GmockHelpers.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental/coro" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/coro/Invoke.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental/coro" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/coro/Materialize-inl.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental/coro" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/coro/Materialize.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental/coro" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/coro/Merge-inl.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental/coro" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/coro/Merge.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental/coro" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/coro/Multiplex-inl.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental/coro" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/coro/Multiplex.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental/coro" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/coro/Mutex.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental/coro" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/coro/Retry.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental/coro" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/coro/SharedLock.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental/coro" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/coro/SharedMutex.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental/coro" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/coro/Sleep-inl.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental/coro" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/coro/Sleep.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental/coro" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/coro/Task.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental/coro" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/coro/TimedWait.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental/coro" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/coro/Timeout-inl.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental/coro" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/coro/Timeout.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental/coro" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/coro/Traits.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental/coro" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/coro/Transform-inl.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental/coro" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/coro/Transform.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental/coro" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/coro/UnboundedQueue.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental/coro" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/coro/Utils.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental/coro" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/coro/ViaIfAsync.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental/coro" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/coro/Wait.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental/coro" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/coro/WithCancellation.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental/coro/detail" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/coro/detail/Barrier.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental/coro/detail" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/coro/detail/BarrierTask.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental/coro/detail" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/coro/detail/Helpers.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental/coro/detail" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/coro/detail/InlineTask.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental/coro/detail" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/coro/detail/Malloc.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental/coro/detail" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/coro/detail/ManualLifetime.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental/coro/detail" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/coro/detail/Traits.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental/flat_combining" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/flat_combining/FlatCombining.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental/io" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/io/FsUtil.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental/io" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/io/HugePages.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental/observer" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/observer/Observable-inl.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental/observer" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/observer/Observable.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental/observer" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/observer/Observer-inl.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental/observer" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/observer/Observer-pre.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental/observer" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/observer/Observer.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental/observer" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/observer/SimpleObservable-inl.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental/observer" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/observer/SimpleObservable.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental/observer/detail" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/observer/detail/Core.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental/observer/detail" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/observer/detail/GraphCycleDetector.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental/observer/detail" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/observer/detail/ObserverManager.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental/settings" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/settings/Settings.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental/settings" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/settings/SettingsMetadata.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental/settings/detail" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/settings/detail/SettingsImpl.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental/symbolizer" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/symbolizer/Dwarf.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental/symbolizer" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/symbolizer/Elf-inl.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental/symbolizer" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/symbolizer/Elf.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental/symbolizer" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/symbolizer/ElfCache.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental/symbolizer" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/symbolizer/LineReader.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental/symbolizer" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/symbolizer/SignalHandler.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental/symbolizer" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/symbolizer/StackTrace.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental/symbolizer" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/symbolizer/SymbolizePrinter.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental/symbolizer" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/symbolizer/SymbolizedFrame.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/experimental/symbolizer" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/experimental/symbolizer/Symbolizer.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/external/farmhash" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/external/farmhash/farmhash.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/fibers" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/fibers/AddTasks-inl.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/fibers" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/fibers/AddTasks.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/fibers" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/fibers/AtomicBatchDispatcher-inl.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/fibers" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/fibers/AtomicBatchDispatcher.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/fibers" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/fibers/BatchDispatcher.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/fibers" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/fibers/BatchSemaphore.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/fibers" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/fibers/Baton-inl.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/fibers" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/fibers/Baton.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/fibers" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/fibers/BoostContextCompatibility.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/fibers" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/fibers/CallOnce.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/fibers" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/fibers/EventBaseLoopController-inl.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/fibers" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/fibers/EventBaseLoopController.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/fibers" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/fibers/ExecutorBasedLoopController.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/fibers" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/fibers/ExecutorLoopController-inl.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/fibers" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/fibers/ExecutorLoopController.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/fibers" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/fibers/Fiber-inl.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/fibers" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/fibers/Fiber.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/fibers" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/fibers/FiberManager-inl.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/fibers" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/fibers/FiberManager.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/fibers" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/fibers/FiberManagerInternal-inl.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/fibers" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/fibers/FiberManagerInternal.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/fibers" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/fibers/FiberManagerMap-inl.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/fibers" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/fibers/FiberManagerMap.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/fibers" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/fibers/ForEach-inl.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/fibers" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/fibers/ForEach.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/fibers" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/fibers/GenericBaton.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/fibers" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/fibers/GuardPageAllocator.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/fibers" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/fibers/LoopController.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/fibers" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/fibers/Promise-inl.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/fibers" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/fibers/Promise.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/fibers" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/fibers/Semaphore.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/fibers" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/fibers/SemaphoreBase.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/fibers" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/fibers/SimpleLoopController.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/fibers" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/fibers/TimedMutex-inl.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/fibers" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/fibers/TimedMutex.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/fibers" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/fibers/WhenN-inl.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/fibers" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/fibers/WhenN.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/fibers/async" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/fibers/async/Async.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/fibers/async" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/fibers/async/Baton.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/fibers/async" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/fibers/async/Collect-inl.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/fibers/async" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/fibers/async/Collect.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/fibers/async" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/fibers/async/FiberManager.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/fibers/async" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/fibers/async/Future.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/fibers/async" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/fibers/async/Promise.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/fibers/async" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/fibers/async/Task.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/fibers/async" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/fibers/async/WaitUtils.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/fibers/detail" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/fibers/detail/AtomicBatchDispatcher.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/fibers" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/fibers/traits.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/functional" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/functional/ApplyTuple.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/functional" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/functional/Invoke.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/functional" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/functional/Partial.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/futures" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/futures/Barrier.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/futures" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/futures/Future-inl.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/futures" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/futures/Future-pre.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/futures" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/futures/Future.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/futures" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/futures/FutureSplitter.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/futures" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/futures/ManualTimekeeper.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/futures" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/futures/Portability.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/futures" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/futures/Promise-inl.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/futures" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/futures/Promise.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/futures" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/futures/Retrying.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/futures" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/futures/SharedPromise-inl.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/futures" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/futures/SharedPromise.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/futures" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/futures/ThreadWheelTimekeeper.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/futures" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/futures/WTCallback.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/futures/detail" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/futures/detail/Core.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/futures/detail" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/futures/detail/Types.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/gen" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/gen/Base-inl.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/gen" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/gen/Base.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/gen" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/gen/Combine-inl.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/gen" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/gen/Combine.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/gen" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/gen/Core-inl.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/gen" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/gen/Core.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/gen" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/gen/File-inl.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/gen" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/gen/File.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/gen" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/gen/IStream.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/gen" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/gen/Parallel-inl.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/gen" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/gen/Parallel.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/gen" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/gen/ParallelMap-inl.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/gen" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/gen/ParallelMap.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/gen" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/gen/String-inl.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/gen" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/gen/String.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/hash" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/hash/Checksum.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/hash" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/hash/FarmHash.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/hash" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/hash/Hash.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/hash" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/hash/SpookyHashV1.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/hash" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/hash/SpookyHashV2.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/hash/detail" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/hash/detail/ChecksumDetail.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/init" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/init/Init.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/init" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/init/Phase.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/io" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/io/Cursor-inl.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/io" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/io/Cursor.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/io" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/io/GlobalShutdownSocketSet.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/io" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/io/IOBuf.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/io" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/io/IOBufQueue.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/io" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/io/RecordIO-inl.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/io" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/io/RecordIO.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/io" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/io/ShutdownSocketSet.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/io" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/io/SocketOptionMap.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/io" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/io/TypedIOBuf.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/io/async" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/io/async/AsyncPipe.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/io/async" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/io/async/AsyncSSLSocket.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/io/async" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/io/async/AsyncServerSocket.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/io/async" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/io/async/AsyncSignalHandler.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/io/async" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/io/async/AsyncSocket.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/io/async" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/io/async/AsyncSocketBase.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/io/async" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/io/async/AsyncSocketException.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/io/async" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/io/async/AsyncTimeout.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/io/async" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/io/async/AsyncTransport.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/io/async" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/io/async/AsyncTransportCertificate.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/io/async" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/io/async/AsyncUDPServerSocket.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/io/async" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/io/async/AsyncUDPSocket.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/io/async" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/io/async/DecoratedAsyncTransportWrapper.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/io/async" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/io/async/DelayedDestruction.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/io/async" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/io/async/DelayedDestructionBase.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/io/async" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/io/async/DestructorCheck.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/io/async" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/io/async/EventBase.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/io/async" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/io/async/EventBaseBackendBase.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/io/async" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/io/async/EventBaseLocal.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/io/async" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/io/async/EventBaseManager.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/io/async" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/io/async/EventBaseThread.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/io/async" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/io/async/EventFDWrapper.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/io/async" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/io/async/EventHandler.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/io/async" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/io/async/EventUtil.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/io/async" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/io/async/HHWheelTimer-fwd.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/io/async" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/io/async/HHWheelTimer.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/io/async" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/io/async/NotificationQueue.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/io/async" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/io/async/PasswordInFile.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/io/async" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/io/async/Request.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/io/async" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/io/async/SSLContext.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/io/async" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/io/async/SSLOptions.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/io/async" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/io/async/ScopedEventBaseThread.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/io/async" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/io/async/TimeoutManager.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/io/async" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/io/async/VirtualEventBase.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/io/async" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/io/async/WriteChainAsyncTransportWrapper.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/io/async/ssl" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/io/async/ssl/BasicTransportCertificate.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/io/async/ssl" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/io/async/ssl/OpenSSLUtils.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/io/async/ssl" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/io/async/ssl/SSLErrors.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/io/async/ssl" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/io/async/ssl/TLSDefinitions.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/lang" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/lang/Align.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/lang" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/lang/Aligned.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/lang" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/lang/Assume-inl.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/lang" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/lang/Assume.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/lang" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/lang/Bits.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/lang" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/lang/CArray.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/lang" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/lang/CString.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/lang" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/lang/Cast.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/lang" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/lang/CheckedMath.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/lang" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/lang/CustomizationPoint.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/lang" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/lang/Exception.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/lang" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/lang/Keep.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/lang" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/lang/Launder.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/lang" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/lang/Ordering.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/lang" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/lang/Pretty.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/lang" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/lang/PropagateConst.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/lang" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/lang/RValueReferenceWrapper.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/lang" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/lang/SafeAssert.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/lang" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/lang/StaticConst.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/lang" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/lang/TypeInfo.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/lang" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/lang/UncaughtExceptions.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/logging" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/logging/AsyncFileWriter.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/logging" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/logging/AsyncLogWriter.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/logging" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/logging/BridgeFromGoogleLogging.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/logging" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/logging/CustomLogFormatter.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/logging" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/logging/FileHandlerFactory.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/logging" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/logging/FileWriterFactory.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/logging" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/logging/GlogStyleFormatter.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/logging" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/logging/ImmediateFileWriter.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/logging" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/logging/Init.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/logging" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/logging/LogCategory.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/logging" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/logging/LogCategoryConfig.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/logging" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/logging/LogConfig.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/logging" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/logging/LogConfigParser.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/logging" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/logging/LogFormatter.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/logging" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/logging/LogHandler.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/logging" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/logging/LogHandlerConfig.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/logging" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/logging/LogHandlerFactory.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/logging" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/logging/LogLevel.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/logging" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/logging/LogMessage.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/logging" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/logging/LogName.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/logging" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/logging/LogStream.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/logging" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/logging/LogStreamProcessor.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/logging" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/logging/LogWriter.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/logging" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/logging/Logger.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/logging" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/logging/LoggerDB.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/logging" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/logging/ObjectToString.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/logging" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/logging/RateLimiter.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/logging" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/logging/StandardLogHandler.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/logging" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/logging/StandardLogHandlerFactory.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/logging" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/logging/StreamHandlerFactory.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/logging" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/logging/xlog.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/memory" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/memory/Arena-inl.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/memory" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/memory/Arena.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/memory" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/memory/EnableSharedFromThis.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/memory" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/memory/MallctlHelper.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/memory" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/memory/Malloc.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/memory" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/memory/MemoryResource.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/memory" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/memory/ReentrantAllocator.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/memory" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/memory/SanitizeLeak.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/memory" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/memory/ThreadCachedArena.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/memory" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/memory/UninitializedMemoryHacks.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/memory/detail" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/memory/detail/MallocImpl.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/net" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/net/NetOps.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/net" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/net/NetworkSocket.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/net/detail" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/net/detail/SocketFileDescriptorMap.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/poly" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/poly/Nullable.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/poly" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/poly/Regular.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/portability" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/portability/Asm.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/portability" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/portability/Atomic.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/portability" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/portability/Builtins.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/portability" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/portability/Config.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/portability" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/portability/Constexpr.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/portability" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/portability/Dirent.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/portability" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/portability/Event.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/portability" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/portability/Fcntl.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/portability" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/portability/GFlags.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/portability" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/portability/GMock.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/portability" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/portability/GTest.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/portability" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/portability/IOVec.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/portability" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/portability/Libgen.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/portability" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/portability/Malloc.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/portability" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/portability/Math.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/portability" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/portability/Memory.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/portability" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/portability/OpenSSL.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/portability" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/portability/PThread.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/portability" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/portability/Sched.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/portability" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/portability/Semaphore.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/portability" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/portability/Sockets.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/portability" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/portability/Stdio.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/portability" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/portability/Stdlib.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/portability" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/portability/String.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/portability" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/portability/SysFile.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/portability" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/portability/SysMembarrier.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/portability" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/portability/SysMman.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/portability" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/portability/SysResource.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/portability" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/portability/SysStat.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/portability" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/portability/SysSyscall.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/portability" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/portability/SysTime.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/portability" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/portability/SysTypes.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/portability" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/portability/SysUio.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/portability" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/portability/Syslog.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/portability" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/portability/Time.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/portability" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/portability/Unistd.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/portability" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/portability/Windows.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/python" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/python/AsyncioExecutor.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/python" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/python/async_generator.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/python" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/python/coro.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/python" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/python/executor.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/python" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/python/futures.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/python" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/python/iobuf.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/ssl" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/ssl/Init.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/ssl" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/ssl/OpenSSLCertUtils.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/ssl" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/ssl/OpenSSLHash.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/ssl" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/ssl/OpenSSLLockTypes.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/ssl" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/ssl/OpenSSLPtrTypes.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/ssl" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/ssl/OpenSSLVersionFinder.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/ssl" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/ssl/SSLSession.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/ssl" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/ssl/SSLSessionManager.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/ssl/detail" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/ssl/detail/OpenSSLSession.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/ssl/detail" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/ssl/detail/OpenSSLThreading.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/stats" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/stats/BucketedTimeSeries-inl.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/stats" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/stats/BucketedTimeSeries.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/stats" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/stats/Histogram-inl.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/stats" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/stats/Histogram.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/stats" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/stats/MultiLevelTimeSeries-inl.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/stats" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/stats/MultiLevelTimeSeries.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/stats" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/stats/QuantileEstimator-inl.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/stats" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/stats/QuantileEstimator.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/stats" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/stats/TDigest.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/stats" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/stats/TimeseriesHistogram-inl.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/stats" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/stats/TimeseriesHistogram.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/stats/detail" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/stats/detail/Bucket.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/stats/detail" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/stats/detail/BufferedStat-inl.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/stats/detail" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/stats/detail/BufferedStat.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/stats/detail" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/stats/detail/DigestBuilder-inl.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/stats/detail" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/stats/detail/DigestBuilder.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/stats/detail" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/stats/detail/DoubleRadixSort.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/stats/detail" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/stats/detail/SlidingWindow-inl.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/stats/detail" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/stats/detail/SlidingWindow.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/synchronization" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/synchronization/AsymmetricMemoryBarrier.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/synchronization" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/synchronization/AtomicNotification-inl.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/synchronization" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/synchronization/AtomicNotification.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/synchronization" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/synchronization/AtomicRef.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/synchronization" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/synchronization/AtomicStruct.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/synchronization" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/synchronization/AtomicUtil-inl.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/synchronization" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/synchronization/AtomicUtil.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/synchronization" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/synchronization/Baton.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/synchronization" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/synchronization/CallOnce.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/synchronization" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/synchronization/DistributedMutex-inl.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/synchronization" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/synchronization/DistributedMutex.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/synchronization" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/synchronization/DistributedMutexSpecializations.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/synchronization" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/synchronization/Hazptr-fwd.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/synchronization" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/synchronization/Hazptr.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/synchronization" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/synchronization/HazptrDomain.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/synchronization" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/synchronization/HazptrHolder.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/synchronization" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/synchronization/HazptrObj.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/synchronization" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/synchronization/HazptrObjLinked.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/synchronization" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/synchronization/HazptrRec.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/synchronization" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/synchronization/HazptrThrLocal.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/synchronization" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/synchronization/HazptrThreadPoolExecutor.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/synchronization" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/synchronization/LifoSem.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/synchronization" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/synchronization/Lock.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/synchronization" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/synchronization/MicroSpinLock.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/synchronization" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/synchronization/ParkingLot.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/synchronization" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/synchronization/PicoSpinLock.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/synchronization" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/synchronization/RWSpinLock.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/synchronization" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/synchronization/Rcu-inl.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/synchronization" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/synchronization/Rcu.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/synchronization" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/synchronization/SanitizeThread.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/synchronization" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/synchronization/SaturatingSemaphore.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/synchronization" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/synchronization/SmallLocks.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/synchronization" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/synchronization/Tearable.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/synchronization" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/synchronization/Utility.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/synchronization" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/synchronization/WaitOptions.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/synchronization/detail" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/synchronization/detail/AtomicUtils.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/synchronization/detail" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/synchronization/detail/Hardware.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/synchronization/detail" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/synchronization/detail/HazptrUtils.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/synchronization/detail" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/synchronization/detail/InlineFunctionRef.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/synchronization/detail" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/synchronization/detail/ProxyLockable-inl.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/synchronization/detail" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/synchronization/detail/ProxyLockable.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/synchronization/detail" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/synchronization/detail/Sleeper.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/synchronization/detail" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/synchronization/detail/Spin.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/synchronization/detail" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/synchronization/detail/ThreadCachedInts.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/synchronization/detail" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/synchronization/detail/ThreadCachedLists.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/synchronization/example" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/synchronization/example/HazptrLockFreeLIFO.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/synchronization/example" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/synchronization/example/HazptrSWMRSet.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/synchronization/example" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/synchronization/example/HazptrWideCAS.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/system" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/system/HardwareConcurrency.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/system" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/system/MemoryMapping.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/system" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/system/Shell.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/system" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/system/ThreadId.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/system" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/system/ThreadName.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/tracing" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/tracing/ScopedTraceSection.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/tracing" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/tracing/StaticTracepoint-ELFx86.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/tracing" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/tracing/StaticTracepoint.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/container/test" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/container/test/F14TestUtil.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/container/test" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/container/test/TrackingTypes.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/io/async/test" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/io/async/test/AsyncSSLSocketTest.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/io/async/test" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/io/async/test/AsyncSocketTest.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/io/async/test" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/io/async/test/AsyncSocketTest2.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/io/async/test" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/io/async/test/BlockingSocket.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/io/async/test" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/io/async/test/MockAsyncSocket.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/io/async/test" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/io/async/test/MockAsyncServerSocket.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/io/async/test" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/io/async/test/MockAsyncSSLSocket.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/io/async/test" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/io/async/test/MockAsyncTransport.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/io/async/test" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/io/async/test/MockAsyncUDPSocket.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/io/async/test" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/io/async/test/MockTimeoutManager.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/io/async/test" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/io/async/test/ScopedBoundPort.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/io/async/test" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/io/async/test/SocketPair.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/io/async/test" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/io/async/test/TestSSLServer.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/io/async/test" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/io/async/test/TimeUtil.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/io/async/test" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/io/async/test/UndelayedDestruction.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/io/async/test" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/io/async/test/Util.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/synchronization/test" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/synchronization/test/Semaphore.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/test" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/test/DeterministicSchedule.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/test" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/test/JsonTestUtil.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly/test" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/folly/test/TestUtils.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/folly" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/build/folly/folly-config.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/folly" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/build/folly-config.cmake")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/folly/folly-targets.cmake")
    file(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/folly/folly-targets.cmake"
         "/home/noah/programs/branch_2/new_obj_allocation/folly-master/build/CMakeFiles/Export/lib/cmake/folly/folly-targets.cmake")
    if(EXPORT_FILE_CHANGED)
      file(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/folly/folly-targets-*.cmake")
      if(OLD_CONFIG_FILES)
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/folly/folly-targets.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        file(REMOVE ${OLD_CONFIG_FILES})
      endif()
    endif()
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/folly" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/build/CMakeFiles/Export/lib/cmake/folly/folly-targets.cmake")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^()$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/folly" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/build/CMakeFiles/Export/lib/cmake/folly/folly-targets-noconfig.cmake")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/home/noah/programs/branch_2/new_obj_allocation/folly-master/build/libfolly.pc")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/noah/programs/branch_2/new_obj_allocation/folly-master/build/folly/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/noah/programs/branch_2/new_obj_allocation/folly-master/build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
