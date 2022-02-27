file(GLOB_RECURSE LumenImpl CONFIGURE_DEPENDS "*.impl.cc")
target_sources(Lumen PUBLIC ${LumenImpl})

target_include_directories(Lumen PUBLIC "./")