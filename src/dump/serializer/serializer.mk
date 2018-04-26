stcss += serializer

serializer_dir = serializer

stam = afca

serializer_src = \
	dump_serializer.cpp \
	dump_serializer_factory.cpp \
	dump_serializer_json.cpp \
	dump_serializer_test.cpp \

serializer_hxx = dump_serializer_common.h dump_serializer_factory.h dump_serializer.h dump_serializer_json.h dump_serializer_test.h
serializer_lbx = jsoncpp
serializer_inc = /usr/include/jsoncpp

