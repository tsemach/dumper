include common/common.mk
include AST/AST.mk
include formater/formater.mk
include serializer/serializer.mk
include loader/loader.mk
include parser/parser.mk
include generator/generator.mk
include tests/serializer/test_serializer.mk
include tests/loader/test_loader.mk

rootdir = .

#---------------------------------------------------------------------------------------------------------
# from here to the end the code is a generic
# --------------------------------------------------------------------------------------------------------
SHELL := /bin/bash

bindir = build/bin
libdir = build/lib
incdir = build/include 
objdir = .objs

ifeq (1,0)
LLVM_SRC_PATH := /home/tsemach/install/llvm
LLVM_BUILD_PATH := /home/tsemach/install/llvm/build
LLVM_BIN_PATH := $(LLVM_BUILD_PATH)/bin

LLVM_LDFLAGS_NOLIBS := `$(LLVM_BIN_PATH)/llvm-config --ldflags`
CLANG_INCLUDES := -I$(LLVM_SRC_PATH)/tools/clang/include -I$(LLVM_BUILD_PATH)/tools/clang/include
 
LLVM_CXXFLAGS := `$(LLVM_BIN_PATH)/llvm-config --cxxflags`
LLVM_LDFLAGS := `$(LLVM_BIN_PATH)/llvm-config --ldflags --libs --system-libs`
LLVM_STFLAGS := `$(LLVM_BIN_PATH)/llvm-config --ldflags --system-libs`
endif

CC=g++
CCFLAGS=-std=c++11 -fno-rtti -O0 -g -I./build/include
#CPPFLAGS = $(CCFLAGS) $(LLVM_CXXFLAGS) $(CLANG_INCLUDES) 

#cppflags_base = $(CPPFLAGS)
cppflags_base=-std=c++11 -fno-rtti -O0 -g -I./build/include
LLVM_LDFLAGS := `$(LLVM_BIN_PATH)/llvm-config --ldflags --libs --system-libs`

LDFLAGS += $(LLVM_LDFLAGS)
#LDFLAGS_BASE = $(LDFLAGS)

binfiles = $(addprefix $(bindir)/, $(progs))
dynfiles = $(addsuffix .so, $(addprefix $(libdir)/, $(addprefix lib, $(dynss)))) 
stcfiles = $(addsuffix .a, $(addprefix $(libdir)/, $(addprefix lib, $(stcss)))) 

#$(1)_obj = $(patsubst %.cpp,%.o, $(addprefix $($(value 1)_dir)/, $($(value 1)_src)))
define vars_template 
$(1)_cpp = $(addprefix $($(value 1)_dir)/, $($(value 1)_src))
$(1)_hxx = $(if $($(value 1)_hxx), $(addprefix $($(value 1)_dir)/, $($(value 1)_hxx)),)
$(1)_obj = $(patsubst %.cpp,%.o, $(addprefix $($(value 1)_dir)/,   $(addprefix $(objdir)/, $($(value 1)_src))))
$(1)_inc = $(if $($(value 1)_inc), $(addprefix -I, $($(value 1)_inc)),)
$(1)_dyn = $(if $($(value 1)_dyn), $(addsuffix .so, $(addprefix $(libdir)/, $(addprefix  lib, $($(value 1)_dyn)))),)
$(1)_stc = $(if $($(value 1)_stc), $(addsuffix .a, $(addprefix $(libdir)/, $(addprefix lib, $($(value 1)_stc)))),)
$(1)_lbx = $(if $($(value 1)_lbx), $(addprefix -l, $($(value 1)_lbx)),)
$(1)_lib = $(addprefix -l, $($(value 1)_dyn)) $(addprefix -l, $($(value 1)_stc)) $(if $($(value 1)_lbx), $(addprefix -l, $($(value 1)_lbx)),)
endef

$(foreach prog,$(progs) $(dynss) $(stcss), $(eval $(call vars_template,$(prog))))


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

#CLANG_LIBS = -Wl,--start-group $(addprefix -l, $(CLANG_LIBS_LIST)) -Wl,--end-group

.PHONY: all
all: builddir $(stcfiles) $(dynfiles) $(binfiles)

builddir:
	@test -d $(incdir) || mkdir -p $(incdir)
	@test -d $(libdir) || mkdir -p $(libdir)
	@test -d $(bindir) || mkdir -p $(bindir)

%.o: $($(@F):.o=.cpp)  $($(@F):.o=.h) 
	$(CC) -c -std=c++11 $(CPPFLAGS) $< -o $@
	$(CC) -c -MM -MF $($(@F):.o=.d) -std=c++11 $(CPPFLAGS) $(filter %.cpp,$<)

%.h:
	$(info NOT WORKING with PATH -------- memory/mymemory.h)
	cp -f $@ $(incdir)

%.objs/%.o: 
	$(info IN COMP objects_dir - $@)
	$(info in COMP sources_dir = $(sources_dir))

define objs_template =
$(2):  $($(1)_dir)/%.cpp  $($(1)_dir)/%.h
    $(CC) -c -std=c++11 $(CPPFLAGS) $(filter %.cpp,$<) -o $@
    $(CC) -c -MM -MF $*.d -std=c++11 $(CPPFLAGS) $(filter %.cpp,$<)
    @mv -f $*.d $*.d.tmp
    @sed -e 's|.*:|$*.o:|' < $*.d.tmp > $*.d
    @sed -e 's/.*://' -e 's/\\$$//' < $*.d.tmp | fmt -1 | sed -e 's/^ *//' -e 's/$$/:/' >> $*.d
    @rm -f $*.d.tmp
endef

#$(foreach obj,  $($(1)_obj), $(info in for of stcss obj - $($(1)_dir) $(obj) ); $(eval $(call objs_template, $(1) $(obj))))
define stcss_template =
-include $(patsubst %.o,%.d, $($(1)_obj))
CPPFLAGS = $(cppflags_base) $($(1)_inc) $($(1)_cfl) 
$(libdir)/lib$(1).a: $($(1)_obj) $($(1)_hxx)
$(libdir)/lib$(1).a: 
	ar cr $(libdir)/lib$(1).a $($(1)_obj)
	(cd $(1); find . -name \*.h | xargs tar cf - | (cd ../build/include; tar xf -))
endef
$(foreach stc,$(stcss),$(eval $(call stcss_template,$(stc))))

#$(CC) -shared -fPIC $(CPPFLAGS) $($(1)_obj) $(CLANG_LIBS) $(LLVM_LDFLAGS) -o $(libdir)/lib$(1).so 
define dynss_template =
-include $(patsubst %.o,%.d, $($(1)_obj))
CPPFLAGS = $(cppflags_base) $($(1)_inc) $($(1)_lbx) $($(1)_cfl) $($(1)_ldf)
$(libdir)/lib$(1).so: $($(1)_obj)
$(libdir)/lib$(1).so: 
	$(CC) -shared -fPIC $(CPPFLAGS) $($(1)_obj) -o $(libdir)/lib$(1).so 
endef
$(foreach lib,$(dynss),$(eval $(call dynss_template,$(lib))))

define progs_template =
-include $(patsubst %.o,%.d, $($(1)_obj))
CPPFLAGS := $(cppflags_base) $($(1)_inc) $($(1)_lbx) $($(1)_cfl)
$(bindir)/$(1): $($(1)_obj) $($(1)_dyn) $($(1)_stc)
$(bindir)/$(1): 
	$(CC) $(CPPFLAGS) $($(1)_obj) -L./$(libdir) $($(1)_lib) $($(1)_ldf) -o $(bindir)/$(1)
endef
$(foreach prog,$(progs),$(eval $(call progs_template,$(prog))))

printme = $(info $(1))
.PHONY: info
info:
	$(info ----------------------------------------------)
	$(info progs = $(value progs))
	$(info binfiles = $(binfiles))
	$(info dynfiles = $(dynfiles))
	$(info stcfiles = $(stcfiles))
	$(foreach dyns,$(dynss), $(call printme,$(dyns)_cpp = $($(dyns)_cpp)))
	$(foreach dyns,$(dynss), $(call printme,$(dyns)_hxx = $($(dyns)_hxx)))
	$(foreach dyns,$(dynss), $(call printme,$(dyns)_obj = $($(dyns)_obj)))
	$(foreach dyns,$(dynss), $(call printme,$(dyns)_dyn = $($(dyns)_dyn)))
	$(foreach dyns,$(dynss), $(call printme,$(dyns)_cfg = $($(dyns)_cfg)))
	$(foreach dyns,$(dynss), $(call printme,$(dyns)_ldf = $($(dyns)_ldf)))
	$(foreach stcs,$(stcss), $(call printme,$(stcs)_cpp = $($(stcs)_cpp)))
	$(foreach stcs,$(stcss), $(call printme,$(stcs)_hxx = $($(stcs)_hxx)))
	$(foreach stcs,$(stcss), $(call printme,$(stcs)_obj = $($(stcs)_obj)))
	$(foreach stcs,$(stcss), $(call printme,$(stcs)_cfl = $($(stcs)_cfl)))
	$(foreach prog,$(progs), $(call printme,$(prog)_cpp = $($(prog)_cpp)))
	$(foreach prog,$(progs), $(call printme,$(prog)_hxx = $($(prog)_hxx)))
	$(foreach prog,$(progs), $(call printme,$(prog)_obj = $($(prog)_obj)))
	$(foreach prog,$(progs), $(call printme,$(prog)_lib = $($(prog)_lib)))
	$(foreach prog,$(progs), $(call printme,$(prog)_dyn = $($(prog)_dyn)))
	$(foreach prog,$(progs), $(call printme,$(prog)_stc = $($(prog)_stc)))
	$(foreach prog,$(progs), $(call printme,$(prog)_cfl = $($(prog)_cfl)))
	$(foreach prog,$(progs), $(call printme,$(prog)_ldf = $($(prog)_ldf)))
	$(info ----------------------------------------------)

delete = rm -f $(1) 
clean: 
	@$(foreach stcs,$(stcss), $(call delete, $($(stcs)_dir)/*.d))
	@$(foreach stcs,$(stcss), $(call delete, $($(stcs)_dir)/*.o))
	@$(foreach dyns,$(dynss), $(call delete, $($(dyns)_dir)/*.o))
	@$(foreach dyns,$(dynss), $(call delete, $($(dyns)_dir)/*.d))
	@$(foreach prog,$(progs), $(call delete, $($(prog)_dir)/*.o))
	@$(foreach prog,$(progs), $(call delete, $($(prog)_dir)/*.d))
	@rm -rf $(bindir) $(libdir) $(incdir)


