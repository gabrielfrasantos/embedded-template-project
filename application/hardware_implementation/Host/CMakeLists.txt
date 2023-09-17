add_library(reference_project.application.hardware_implementation STATIC)
install(TARGETS reference_project.application.hardware_implementation EXPORT halTivaTargets)

target_include_directories(reference_project.application.hardware_implementation PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/../../../>"
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)

target_link_libraries(reference_project.application.hardware_implementation PUBLIC
    drivers.display.tft
    drivers.stepper_motor
    reference_project.application.hardware_abstraction
)

target_compile_definitions(reference_project.application.hardware_implementation PUBLIC
    BOARD_HEADER="application/hardware_implementation/Host/Board.hpp"
)

target_sources(reference_project.application.hardware_implementation PRIVATE
    Board.cpp
    Board.hpp
)
