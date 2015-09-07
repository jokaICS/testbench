SCADESRCDIR = Simulation
SCADEFILES = $(wildcard $(SCADESRCDIR)/*.c)
SCADEOBJS = $(subst .c,.o,$(SCADEFILES))
CFLAGS = -I. -I include -O3

libtestbench.a: $(SCADEOBJS)
	ar ru $@ $^
	ranlib $@

run: main.o
	$(CC) $< -o $@

.PHONY: clean

clean:
	rm -f $(SCADESRCDIR)/*.o
	rm -f libtestbench.a
