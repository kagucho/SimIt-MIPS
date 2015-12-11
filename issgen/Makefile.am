
noinst_PROGRAMS = issgen
issgen_SOURCES = symbol.cpp symbol.hpp issgen.hpp issgen.cpp parse_isa.cpp scan_isa.cpp parse_isa.hpp

parse_isa.cpp : parse_isa.y
	@YACC@ -d -p isa_ $^ -o $@

scan_isa.cpp : scan_isa.l
	@LEX@ -Pisa_ -o$@ $^

deploy: mips.isa issgen
	./issgen -p mips mips.isa
	cp mips_iss.cpp $(top_srcdir)/emulator
	cp mips_iss.hpp $(top_srcdir)/emulator
	cp mips_inst.def $(top_srcdir)/emulator
	cp mips_gen.cpp $(top_srcdir)/jit
	cp mips_gen.hpp $(top_srcdir)/jit

EXTRA_DIST = parse_isa.y scan_isa.l
