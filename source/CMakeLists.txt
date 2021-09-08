set(TARGET_NAME search)
add_library(${TARGET_NAME} search/search.cpp search/search.h)
target_include_directories(${TARGET_NAME} INTERFACE ./)
install(TARGETS ${TARGET_NAME} ARCHIVE DESTINATION lib/)