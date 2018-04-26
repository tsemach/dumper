

progs += generator

generator_dir = generator
generator_src = dump_generator.cpp

#include makefiles/llvm_defaults.mk

#generator_ccflags := -std=c++11 -fno-rtti -O0 -g -I./build/include
#generator_llvm_cxxflags := `$(LLVM_BIN_PATH)/llvm-config --cxxflags`
#generator_cland_include := -I$(LLVM_SRC_PATH)/tools/clang/include -I$(LLVM_BUILD_PATH)/tools/clang/include

generator_cfl = $(LLVM_CXXFLAGS) $(CLANG_INCLUDES)
#generator_ldf = $(CLANG_LIBS) $(LLVM_LDFLAGS)
generator_ldf =
generator_stc = AST parser


