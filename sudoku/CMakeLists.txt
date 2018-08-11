set( ME sudoku )

add_executable( ${ME}
    "src/lsb_msb.hpp"
    "src/main.cpp"
	"src/parse.cpp"
	"src/solve.cpp"
	"src/sudoku.hpp"
)
