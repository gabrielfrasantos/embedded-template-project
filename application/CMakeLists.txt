add_executable(reference_project.application Main.cpp)

emil_build_for(reference_project.application TARGET_MCU_VENDOR ${TARGET_MCU_VENDOR})

target_link_libraries(reference_project.application PRIVATE
    services.util
    hal_tiva.instantiations
    hal_tiva.tiva
    drivers.display.tft
    reference_project.application.hardware_abstraction
    reference_project.application.hardware_implementation
)

hal_ti_target_default_linker_scripts(reference_project.application)
hal_ti_target_default_init(reference_project.application)

add_subdirectory(hardware_abstraction)
add_subdirectory(hardware_implementation)

emil_generate_artifacts(TARGET reference_project.application LST MAP BIN HEX)
