add_executable(application.test)
emil_add_test(application.test)

target_link_libraries(application.test PUBLIC
    gmock_main
    infra.timer
    infra.timer_test_helper
)

target_sources(application.test PRIVATE
    TestStub.cpp
)
