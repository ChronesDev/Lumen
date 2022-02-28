add_subdirectory(Ext)

target_link_libraries(Lumen PUBLIC minhook)
target_include_directories(Lumen PUBLIC "Ext/include/")
