all:
	g++ -std=c++11 src/visualizer.cpp -o bin/visualizer.out

example:
	g++ -std=c++11 src/visualizer.cpp -o bin/visualizer.out
	bin/visualizer.out examples/ir.ll examples/ir.dot
	dot examples/ir.dot -Tpng -o images/ir.png
