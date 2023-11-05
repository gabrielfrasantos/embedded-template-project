add_library(reference_project.application.gui ${HAL_TI_EXCLUDE_FROM_ALL} STATIC)

target_include_directories(reference_project.application.gui PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/../../>"
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)

target_link_libraries(reference_project.application.gui PUBLIC
    infra.util
    embedded_lvgl.interfaces
    embedded_lvgl.core
    embedded_lvgl.widgets
)

target_sources(reference_project.application.gui PRIVATE
    MainScreen.cpp
    MainScreen.hpp
)
