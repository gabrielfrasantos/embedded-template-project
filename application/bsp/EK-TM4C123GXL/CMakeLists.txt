add_library(reference_project.application.bsp ${HAL_TI_EXCLUDE_FROM_ALL} STATIC)
install(TARGETS reference_project.application.bsp EXPORT halTivaTargets)

target_include_directories(reference_project.application.bsp PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/../../../>"
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)

target_link_libraries(reference_project.application.bsp PUBLIC
    hal.interfaces

    hal_tiva.instantiations
    hal_tiva.tiva
)

target_sources(reference_project.application.bsp PRIVATE
    Board.cpp
    Board.hpp
)
