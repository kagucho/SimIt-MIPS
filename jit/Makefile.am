
if ENABLE_JIT
JIT_PROGS = emips_jit emips_jit_server
else
JIT_PROGS =
endif

# the binary programs to build
bin_PROGRAMS = emips_decomp $(JIT_PROGS)

# source code needed for decompiler
emips_decomp_SOURCES = decomp.cpp decomp.hpp decomp_main.cpp auto_emitc.h
emips_decomp_LDADD = $(top_builddir)/emulator/libemips.a libdcom.a
#emips_decomp_CPPFLAGS = -DDYNAMIC

# source code needed for decompiler
emips_jit_server_SOURCES = decomp_server_main.cpp \
	decomp_server.cpp decomp_server.hpp
emips_jit_server_LDADD = $(top_builddir)/emulator/libemips.a libdcom.a
emips_jit_server_CPPFLAGS = -DDYNAMIC

emips_jit_SOURCES = dyn_main.cpp dyn_mips_emul.cpp dyn_decomp.cpp util.hpp
emips_jit_LDADD = $(top_builddir)/emulator/libemips.a libdcom.a
emips_jit_LDFLAGS = -export-dynamic -ldl -lpthread
emips_jit_CPPFLAGS = -DDYNAMIC

noinst_LIBRARIES = libdcom.a
libdcom_a_SOURCES = decomp_common.cpp decomp_common.hpp \
	mips_gen.hpp mips_gen.cpp

# header files for the library, all hpp files here
INCLUDES = -I$(top_srcdir)/emulator
include_HEADERS = dyn_mips_emul.hpp build_dll.hpp

bin_SCRIPTS = build_scs


EXTRA_DIST = build_dll.hpp.in \
	decomp_src/compiled_main.cpp  decomp_src/compiled_run.cpp  \
	decomp_src/compiled_run.hpp  decomp_src/Makefile.in

pkgdata_DATA = \
	decomp_src/compiled_main.cpp  decomp_src/compiled_run.cpp  \
	decomp_src/compiled_run.hpp  decomp_src/Makefile
