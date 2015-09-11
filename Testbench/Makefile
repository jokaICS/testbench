SCADESRCDIR = Simulation
SCADEFILES = $(wildcard $(SCADESRCDIR)/*.c)
SCADEOBJS = $(subst .c,.o,$(SCADEFILES))
OSSMINCDIR = ~/ics/tmp/ossm/src
OSSMLIB = -L ~/ics/tmp/ossm/build/Debug/ -lossm
CFLAGS = -I. -I include -I $(SCADESRCDIR) -I $(OSSMINCDIR) -O3
LDFLAGS = -ltcl $(OSSMLIB)

testbench: main.o interface.o libtestbench.a
	$(CC) $^ -o $@ $(LDFLAGS)

libtestbench.a: $(SCADEOBJS)
	ar ru $@ $^
	ranlib $@


.PHONY: clean

clean:
	rm -f $(SCADESRCDIR)/*.o
	rm -f *.o
	rm -f libtestbench.a
	rm -f testbench

distclean: clean
	rm -rf $(SCADESRCDIR)
