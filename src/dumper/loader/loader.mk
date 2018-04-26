stcss += loader

loader_dir = loader

loader_src = \
	dump_loader.cpp \
	dump_loader_factory.cpp \
	dump_loader_json.cpp \
	dump_loader_test.cpp \

loader_hxx = dump_loader_common.h dump_loader_factory.h dump_loader.h dump_loader_json.h dump_loader_test.h
loader_lbx = jsoncpp
loader_inc = /usr/include/jsoncpp

