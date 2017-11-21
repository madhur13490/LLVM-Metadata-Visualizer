# LLVM-Metadata-Visualizer
This project will help you to visualize LLVM metadata dumped by front-end like Clang. 

Metadata node emitted in IR file usually refers to other metadata nodes and this may make it hard to comprehend the information. This tool will take a LLVM IR file, parse it to find metadata nodes and dump a dot file which will have a graphical representation of whole metadata. Each metadata node present in the file will be a vertex in the graph. An undirected edge connects two nodes if one of them refers to the other. Vertex in the graph tries to depict as detailed information as possible in the form of a table where each row is an attribute present in the metadata node.


# Pre-requisites
* It has just one make file so Linux! (or Windows if you can run makefile with cygwin or so)
* GCC 7.2 (for improved regex support)
* `dot` program (to get a .png file)

# How to use the tool?
* `make all` will give you an executable called `visualizer`
* Invoke it as   
`./visualizer <IR-filename> <DOT-filename>`
* Next, use the standard `dot` program to get a .png file like     
`dot <DOT-filename> -Tpng -o <PNG-filename>`
