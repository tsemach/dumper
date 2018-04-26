

#progs += parser
stcss += parser

parser_dir = parser
parser_src = dump_parser.cpp matcher.cpp

#include makefiles/llvm_defaults.mk

#parser_ccflags := -std=c++11 -fno-rtti -O0 -g -I./build/include
#parser_llvm_cxxflags := `$(LLVM_BIN_PATH)/llvm-config --cxxflags`
#parser_cland_include := -I$(LLVM_SRC_PATH)/tools/clang/include -I$(LLVM_BUILD_PATH)/tools/clang/include

parser_cfl = $(LLVM_CXXFLAGS) $(CLANG_INCLUDES)
parser_ldf = $(CLANG_LIBS) $(LLVM_LDFLAGS)

parser_stc = AST
