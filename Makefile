#########################
CFILES := 
HFILES := 
#CFILES := $(wildcard *.c)
#HFILES := $(wildcard *.h)
PROGRAMS := $(patsubst %.c,%,$(CFILES))
CFLAGS := -g -Wall
LDFLAGS :=
########################

# -MMD generates dependencies while compiling
CFLAGS += -MMD
CC := gcc

OBJFILES := $(CFILES:.c=.o)
DEPFILES := $(CFILES:.c=.d)

all : $(PROGRAMS)
	$(LINK.o) $(LDFLAGS) -o $@ $^

clean :
	rm -f $(PROGRAMS) $(OBJFILES) $(DEPFILES)

tags: 
	/usr/bin/ctags -e $(HFILES) $(CFILES)

-include $(DEPFILES)
