add_library(Cbb Fraction.cpp MIDI.cpp NoteValue.cpp Pitch.cpp)
target_include_directories(Cbb PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../../include)
target_compile_features(Cbb PUBLIC cxx_std_17)    
