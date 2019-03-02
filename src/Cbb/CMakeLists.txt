add_library(Cbb Fraction.cpp NoteValue.cpp)
target_include_directories(Cbb PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../../include)
target_compile_features(Cbb PUBLIC cxx_std_17)
add_library(Cbb::Cbb ALIAS Cbb)

add_executable(FractionTest Fraction.test.cpp)
target_link_libraries(FractionTest PUBLIC Cbb Catch2::Catch2)

add_executable(NoteValueTest NoteValue.test.cpp)
target_link_libraries(NoteValueTest PUBLIC Cbb Catch2::Catch2)

add_test(NAME FractionTest COMMAND FractionTest)
add_test(NAME NoteValueTest COMMAND NoteValueTest)
