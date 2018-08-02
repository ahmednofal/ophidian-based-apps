file (GLOB Placer_SRC
	"*.cpp"
)

add_library(myPlacer ${Placer_SRC})
target_link_libraries(myPlacer util ophidian::ophidian_interconnection)
target_include_directories (myPlacer PUBLIC ${CMAKE_SOURCE_DIR})
