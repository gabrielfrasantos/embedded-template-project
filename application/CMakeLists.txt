if (CMAKE_CROSSCOMPILING)
    add_executable(reference_project.application Main.cpp)

    emil_build_for(reference_project.application TARGET_MCU_VENDOR ${TARGET_MCU_VENDOR})

    target_link_libraries(reference_project.application PRIVATE
        services.util
        hal_tiva.instantiations
        hal_tiva.tiva
        reference_project.application.hardware_abstraction
        reference_project.application.hardware_implementation
        reference_project.application.parsers
    )

    add_subdirectory(hardware_abstraction)
    add_subdirectory(hardware_implementation)
    add_subdirectory(parsers)
    add_subdirectory(gui)

    if (TARGET_MCU_VENDOR STREQUAL "ti")
        hal_ti_target_default_linker_scripts(reference_project.application)
        hal_ti_target_default_init(reference_project.application)
    endif()

    emil_generate_artifacts(TARGET reference_project.application LST MAP BIN HEX)
else()
    if (TEMPLATE_PROJECT_ENABLE_TESTS)
        add_subdirectory(test)
    endif()
endif()