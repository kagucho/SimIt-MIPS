
CC = mipsel-linux-gnu-gcc
OD = mipsel-linux-gnu-objdump

BINS = 8q dag fib grep init nested switch \
	array decl fib_mem hyper limits paranoia wc \
	cmp eight fields ifthen mm_int sort wf1 \
	cq fact2 funcptr_test incr mod struct

all : $(BINS)

% : %.c
	$(CC) -O $< -o $@ -static -lm

%.dump : %
	$(OD) -d $< > $@

clean:
	rm -f $(BINS) *.dump
