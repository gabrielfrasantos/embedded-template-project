add_library(reference_project.application.hardware_abstraction ${HAL_TI_EXCLUDE_FROM_ALL} INTERFACE)

emil_build_for(reference_project.application.hardware_abstraction TARGET_MCU_VENDOR ${TARGET_MCU_VENDOR})

target_link_libraries(reference_project.application.hardware_abstraction INTERFACE
    hal.interfaces
    services.util
    services.tracer
    services.network
)

target_sources(reference_project.application.hardware_abstraction INTERFACE
    Hal.hpp
)
