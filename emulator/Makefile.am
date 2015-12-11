DECODER_GEN := ../decgen/decgen32
DECODER_HDR := mips_dec.h
DECODER_DEF := mips_inst.def

$(DECODER_HDR): $(DECODER_DEF)
	$(DECODER_GEN) -i -g 0.25 -o $@ $<

# the binary programs to build
bin_PROGRAMS = emips

# source code of the binary program, place all cpp files here
emips_SOURCES = main.cpp
emips_LDADD = libemips.a

lib_LIBRARIES = libemips.a

libemips_a_SOURCES = $(DECODER_HDR) mips_iss.cpp mips_emul.cpp \
	emumem.cpp loader.cpp syscall.cpp read_elf.cpp \
	util.cpp debug_disasm.cpp debug.cpp  gdbserver.cpp auto_impl.h \
	read_elf.h

# header files for the library, all hpp files here
include_HEADERS = mips_iss.hpp mips_emul.hpp misc.hpp \
	debug_disasm.hpp arch.hpp emumem.h \
	$(top_builddir)/config.h bittypes.hpp

EXTRA_DIST = $(DECODER_DEF) inst_num.def
