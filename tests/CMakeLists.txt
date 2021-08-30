add_executable(
    tests
    main.cxx
    tests_constrained_integral_constant.cxx
    tests_integral_constant_literals.cxx
)

target_link_libraries(
    tests
    PRIVATE
    random-cpp-stuff
)