# LLVM-Metadata-Visualizer
This project will help you to visualize LLVM metadata dumped by front-end line Clang. 

Metadata node emitted in IR file usually refers to other metadata nodes and this may make it hard to comprehend the information. This tool will take LLVM IR file, parse it to find metadata nodes and dump a PNG file which will have a graphical representation of metadata. Each metadata node present in the file will be a vertex in the graph. An undirected edge connects two nodes if one of them refers to the other.
Vertex in the graph tries to depict as detailed information as possible in the form of a table where each row is an attribute present in the metadata node.


