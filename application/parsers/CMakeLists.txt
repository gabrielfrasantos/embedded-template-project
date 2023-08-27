add_library(reference_project.application.parsers ${HAL_TI_EXCLUDE_FROM_ALL} STATIC)

target_include_directories(reference_project.application.parsers PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/../../>"
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)

target_link_libraries(reference_project.application.parsers PUBLIC
    hal.interfaces
    infra.util
    services.util
)

target_sources(reference_project.application.parsers PRIVATE
    Display.cpp
    Display.hpp
)
