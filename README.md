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

# Example
The following C code 

```C++
void foo() {
  int X = 21;
  int Y = 22;
  {
    int Z = 23;
    Z = X;
  }
  X = Y;
}
```
when compiled to LLVM IR will look like

```llvm
; ModuleID = 'a.cpp'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

%"class.std::ios_base::Init" = type { i8 }

@_ZStL8__ioinit = internal global %"class.std::ios_base::Init" zeroinitializer, align 1
@__dso_handle = external global i8
@llvm.global_ctors = appending global [1 x { i32, void ()*, i8* }] [{ i32, void ()*, i8* } { i32 65535, void ()* @_GLOBAL__sub_I_a.cpp, i8* null }]
                                                                                                                                                                              ; Function Attrs: uwtable                                                                                                                                                     define internal void @__cxx_global_var_init() #0 section ".text.startup" !dbg !37 {
  call void @_ZNSt8ios_base4InitC1Ev(%"class.std::ios_base::Init"* @_ZStL8__ioinit), !dbg !410                                                                                  %1 = call i32 @__cxa_atexit(void (i8*)* bitcast (void (%"class.std::ios_base::Init"*)* @_ZNSt8ios_base4InitD1Ev to void (i8*)*), i8* getelementptr inbounds (%"class.std::ios_base::Init", %"class.std::ios_base::Init"* @_ZStL8__ioinit, i32 0, i32 0), i8* @__dso_handle) #2, !dbg !411
  ret void, !dbg !410                                                                                                                                                         }                                                                                                                                                                             
declare void @_ZNSt8ios_base4InitC1Ev(%"class.std::ios_base::Init"*) #1

declare void @_ZNSt8ios_base4InitD1Ev(%"class.std::ios_base::Init"*) #1
...
!0 = distinct !DICompileUnit(language: DW_LANG_C_plus_plus, file: !1, producer: "clang version 3.8.0-2ubuntu4 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !3, subprograms: !36, globals: !46, imports: !48)
!1 = !DIFile(filename: "a.cpp", directory: "/home/madhura/visualizer")
!2 = !{}
!3 = !{!4, !6, !8, !16, !17, !19, !23}
!4 = !DICompositeType(tag: DW_TAG_structure_type, file: !5, line: 82, size: 64, align: 32, flags: DIFlagFwdDecl, identifier: "_ZTS11__mbstate_t")
!5 = !DIFile(filename: "/usr/include/wchar.h", directory: "/home/madhura/visualizer")
!6 = !DICompositeType(tag: DW_TAG_structure_type, name: "_IO_FILE", file: !7, line: 44, flags: DIFlagFwdDecl, identifier: "_ZTS8_IO_FILE")
!7 = !DIFile(filename: "/usr/include/stdio.h", directory: "/home/madhura/visualizer")
!8 = !DICompositeType(tag: DW_TAG_structure_type, name: "__va_list_tag", file: !1, size: 192, align: 64, elements: !9, identifier: "_ZTS13__va_list_tag")
!9 = !{!10, !12, !13, !15}
!10 = !DIDerivedType(tag: DW_TAG_member, name: "gp_offset", scope: !"_ZTS13__va_list_tag", file: !1, baseType: !11, size: 32, align: 32)

```
(The IR is truncated for demonstration purpose)
