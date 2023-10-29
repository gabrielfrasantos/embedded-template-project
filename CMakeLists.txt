cmake_minimum_required(VERSION 3.24)

project(embedded-template-project LANGUAGES C CXX VERSION 1.0.0) # x-release-please-version

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED On)

option(TEMPLATE_PROJECT_ENABLE_TESTS "Enable unit tests" Off)
option(TEMPLATE_PROJECT_ENABLE_COVERAGE "Enable coverage" Off)
option(TEMPLATE_PROJECT_ENABLE_FILESYSTEM "Enable embedded immplementation of a filesystem" Off)
option(TEMPLATE_PROJECT_ENABLE_SEGGER_RTT "Enable embedded immplementation of Segger RTT" Off)
option(TEMPLATE_PROJECT_ENABLE_STM32_USB "Enable embedded immplementation of USB stack (STM32 USB)" Off)
option(TEMPLATE_PROJECT_ENABLE_LVGL "Enable embedded immplementation of lvgl (Light and Versatile Graphics Library)" Off)

set_directory_properties(PROPERTY USE_FOLDERS ON)

if (TEMPLATE_PROJECT_ENABLE_TESTS)
    include(CTest)
    enable_testing()
endif()

add_subdirectory(embedded-infra)
add_subdirectory(drivers)

if (NOT TEMPLATE_PROJECT_ENABLE_TESTS)
    if (TARGET_MCU_VENDOR)
        add_subdirectory(arch/hal/${TARGET_MCU_VENDOR})
    endif()

    if (TEMPLATE_PROJECT_ENABLE_FILESYSTEM)
        add_subdirectory(implementations/filesystem)
    endif()

    if (TEMPLATE_PROJECT_ENABLE_SEGGER_RTT)
        add_subdirectory(implementations/segger_rtt)
    endif()

    if (TEMPLATE_PROJECT_ENABLE_STM32_USB)
        add_subdirectory(implementations/stm32_usb)
    endif()

    if (TEMPLATE_PROJECT_ENABLE_LVGL)
        add_subdirectory(implementations/lvgl)
    endif()
endif()

add_subdirectory(application)

emil_exclude_directory_from_clang_format(drivers)
emil_exclude_directory_from_clang_format(embedded-infra)
emil_clangformat_directories(application DIRECTORIES .)
emil_folderize_all_targets()
