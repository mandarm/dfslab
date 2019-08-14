#########################
# Customise these
CFILES := $(wildcard *.c)
HFILES := $(wildcard *.h)
PROG := driver 
CFLAGS := -g -Wall -DDEBUG
LDFLAGS :=
########################

# -MMD generates dependencies while compiling
CFLAGS += -MMD
CC := gcc

OBJFILES := $(CFILES:.c=.o)
DEPFILES := $(CFILES:.c=.d)

$(PROG) : $(OBJFILES)
	$(LINK.o) $(CFLAGS) -o $@ $^

clean :
	rm -f $(PROG) $(OBJFILES) $(DEPFILES)

tags: 
	/usr/bin/ctags -e $(HFILES) $(CFILES)

-include $(DEPFILES)
