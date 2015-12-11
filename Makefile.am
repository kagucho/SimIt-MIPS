
if ENABLE_JIT
JIT = jit
else
JIT =
endif

SUBDIRS = decgen emulator issgen $(JIT)

include_HEADERS = config.h

EXTRA_DIST = document/guide.html  document/index.html \
	document/mipsimweb.css  \
	test/8q.c test/array.c test/cmp.c test/cq.c test/dag.c \
	test/decl.c test/eight.c test/fact2.c test/fib.c test/fib_mem.c \
	test/fields.c test/funcptr_test.c test/grep.c test/hyper.c test/ifthen.c \
	test/incr.c test/init.c test/limits.c test/mm_int.c test/mod.c \
	test/nested.c test/paranoia.c test/sort.c test/struct.c \
	test/switch.c test/wc.c test/wf1.c test/Makefile \
	issgen/mips.isa test/wc test/grep

dist-hook:
	$(top_srcdir)/prepend_license $(top_srcdir)/license_notice $(distdir) $(top_srcdir)/filelist
	touch $(distdir)/issgen/parse_isa.cpp $(distdir)/issgen/scan_isa.cpp


