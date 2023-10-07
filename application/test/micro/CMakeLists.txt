add_executable(application.test)
emil_add_test(application.test)

target_link_libraries(application.test PUBLIC
    gmock_main
)

target_sources(application.test PRIVATE
    TestStub.cpp
)
