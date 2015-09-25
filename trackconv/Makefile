SCADESRCDIR = Scade/Simulation
SCADEFILES = $(wildcard $(SCADESRCDIR)/*.c)
SCADEOBJS = $(subst .c,.o,$(SCADEFILES))
ENVSIMDIR = ../EnvSim/libenvsim
JIMDIR = ../EnvSim/libenvsim/jimtcl
CFLAGS = -I. -I include -I $(SCADESRCDIR) -I $(ENVSIMDIR)/src -I $(JIMDIR) -O3 -m64
LDFLAGS = -L $(ENVSIMDIR)/build/Debug -lenvsim

trackconv: main.o libtrackconv.a
	$(CC) $^ -o $@ $(LDFLAGS)

libtrackconv.a: $(SCADEOBJS)
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
