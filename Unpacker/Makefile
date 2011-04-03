#Wojciech :Krzemien 13.02.2006
#Makefile for DriftChamber simulation
# 
# make run, make clean, make tar
#===============================================================================
DIR=unpacker
###################
ARCH         := $(shell root-config --arch)
PLATFORM      = $(ARCH)
###################
NAME1 = unpacker_wk
NAME2 = hldevent_wk
NAME3 = hldsubevent_wk
NAME4 = event_wk
NAME5 = eventhdr_wk
NAME6 = mydict
NAME7 = hit_wk
###################
LINKDEF = wkLinkDef.h
###################
EXEC1 = myroot.x
###################
OBJS1 = $(NAME1).o
OBJS2 = $(NAME2).o
OBJS3 = $(NAME3).o
OBJS4 = $(NAME4).o
OBJS5 = $(NAME5).o
OBJS6 = $(NAME6).o
OBJS7 = $(NAME7).o
###################
HEADS1 = $(NAME1).h 
HEADS2 = $(NAME2).h 
HEADS3 = $(NAME3).h 
HEADS4 = $(NAME4).h 
HEADS5 = $(NAME5).h 
HEADS6 = $(NAME6).h 
HEADS7 = $(NAME7).h 
###################
LIB_SHARED = lib$(NAME1).so
###################
ROOTCFLAGS   := $(shell root-config --cflags)
ROOTLIBS     := $(shell root-config --libs)
ROOTGLIBS    := $(shell root-config --glibs)
###################
CFLAGS = -O -Wall -g -fPIC
LDFLAGS=-O
###################
CFLAGS     += $(ROOTCFLAGS)
LIBS          = $(ROOTLIBS) $(SYSLIBS)
GLIBS         = $(ROOTGLIBS) $(SYSLIBS)
###################
CO = g++
LD = $(CO)
###################
%.o: %.cc %.h
	$(CO) $(CFLAGS) -c $<
%.o: %.cc
	$(CO) $(CFLAGS) -c $<
###################
$(LIB_SHARED): $(OBJS1) $(OBJS2) $(OBJS3) $(OBJS4) $(OBJS5) $(OBJS6) $(OBJS7) $(OBJS8)
	$(LD) -shared $(LDFLAGS) $^ $(LIBS) $(GLIBS) -o $@
###################
run: $(EXEC1)
	./$(EXEC1)
###################
clean:
	rm -f *.o *.x core core* a.out *.so mydict.*
###################
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz $(DIR) )
###################
$(NAME6).cc:$(HEADS1) $(HEADS2) $(HEADS3) $(HEADS4) $(HEADS5) $(HEADS7) $(LINKDEF)
	@echo "Generation dictrionary..."
	@rootcint -f $(NAME6).cc -c -p $(HEADS1) $(HEADS2) $(HEADS3) $(HEADS4) $(HEADS5) $(HEADS7) $(LINKDEF)
###################
