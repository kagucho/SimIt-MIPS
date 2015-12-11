DECODER_GEN := ../decgen/decgen32
DECODER_HDR := mips_dec.h
DECODER_DEF := mips_inst.def

$(DECODER_HDR): $(DECODER_DEF)
	$(DECODER_GEN) -i -g 0.25 -o $@ $<

# the binary programs to build
bin_PROGRAMS = emips emips_lite

# source code of the binary program, place all cpp files here
emips_lite_SOURCES = main.cpp
emips_lite_CPPFLAGS = -DSIM_LITE
emips_lite_LDADD = libemips_lite.a

emips_SOURCES = main.cpp $(DECODER_HDR) mips_iss.cpp mips_emul.cpp \
	emumem.cpp loader.cpp syscall.cpp read_elf.cpp util.cpp \
	debug_disasm.cpp debug.cpp gdbserver.cpp \
	auto_impl.h read_elf.h

# source code needed for decompiler

lib_LIBRARIES = libemips_lite.a

libemips_lite_a_SOURCES = $(DECODER_HDR) mips_iss.cpp mips_emul.cpp \
	emumem.cpp loader.cpp syscall.cpp read_elf.cpp \
	util.cpp debug_disasm.cpp debug.cpp \
	mips_gen.hpp mips_gen.cpp 

libemips_lite_a_CPPFLAGS = -DSIM_LITE

# header files for the library, all hpp files here
include_HEADERS = mips_iss.hpp mips_emul.hpp misc.hpp \
	debug_disasm.hpp arch.hpp emumem.h \
	../config.h bittypes.hpp dyn_mips_emul.hpp

EXTRA_DIST = $(DECODER_DEF) inst_num.def elf.h
