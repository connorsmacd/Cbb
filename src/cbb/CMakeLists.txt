find_package(Ieme REQUIRED)

add_library(${PROJECT_NAME}
  note_value.cpp
  note_value_constants.cpp
  power_of_2.cpp
  power_of_2_constants.cpp)
target_include_directories(${PROJECT_NAME}
  PUBLIC
    $<BUILD_INTERFACE:${${PROJECT_NAME}_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
target_link_libraries(${PROJECT_NAME} PUBLIC Ieme::Ieme)

if (${CBB_BUILD_TESTS})

  find_package(Catch2 REQUIRED)

  add_executable(note_value_test note_value.test.cpp)
  target_link_libraries(note_value_test PUBLIC ${PROJECT_NAME} Catch2::Catch2)
  add_test(NAME note_value_test COMMAND note_value_test)

  add_executable(power_of_2_test power_of_2.test.cpp)
  target_link_libraries(power_of_2_test PUBLIC ${PROJECT_NAME} Catch2::Catch2)
  add_test(NAME power_of_2_test COMMAND power_of_2_test)

endif()
