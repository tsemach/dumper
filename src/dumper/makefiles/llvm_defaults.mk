
LLVM_SRC_PATH := /home/tsemach/install/llvm
LLVM_BUILD_PATH := /home/tsemach/install/llvm/build
LLVM_BIN_PATH := $(LLVM_BUILD_PATH)/bin

LLVM_LDFLAGS_NOLIBS := `$(LLVM_BIN_PATH)/llvm-config --ldflags`
CLANG_INCLUDES := -I$(LLVM_SRC_PATH)/tools/clang/include -I$(LLVM_BUILD_PATH)/tools/clang/include
 
LLVM_CXXFLAGS := `$(LLVM_BIN_PATH)/llvm-config --cxxflags`
LLVM_LDFLAGS := `$(LLVM_BIN_PATH)/llvm-config --ldflags --libs --system-libs`
LLVM_STFLAGS := `$(LLVM_BIN_PATH)/llvm-config --ldflags --system-libs`

CLANG_LIBS_LIST := \
	clangAST \
	clangASTMatchers \
	clangAnalysis \
	clangBasic \
	clangDriver \
	clangEdit \
	clangFrontend \
	clangFrontendTool \
	clangLex \
	clangParse \
	clangSema \
	clangEdit \
	clangRewrite \
	clangRewriteFrontend \
	clangStaticAnalyzerFrontend \
	clangStaticAnalyzerCheckers \
	clangStaticAnalyzerCore \
	clangSerialization \
	clangToolingCore \
	clangTooling \
	clangFormat

CLANG_LIBS = -Wl,--start-group $(addprefix -l, $(CLANG_LIBS_LIST)) -Wl,--end-group


