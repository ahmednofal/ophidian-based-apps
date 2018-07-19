file (GLOB util_SRC
	"*.cpp"
)

add_library(util ${util_SRC})
target_include_directories (util PUBLIC ${CMAKE_SOURCE_DIR})
