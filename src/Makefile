CC = gcc
CFLAGS = -g -Wall

CLIENT_TARGET = punch
REZVENDOUS_TARGET = rezvendous

SRCDIR = src
OBJDIR = obj
BINDIR = bin

CLIENT_SRCS = $(wildcard $(SRCDIR)/client/*.c)
REZVENDOUS_SRCS = $(wildcard $(SRCDIR)/rezvendous/*.c)

#SRCS = $(wildcard $(SRCDIR)/*.c)
CLIENT_OBJS = $(patsubst $(SRCDIR)/client/%.c, $(OBJDIR)/client/%.o, $(CLIENT_SRCS)
REZVENDOUS_OBJS = $(patsubst $(SRCDIR)/rezvendous/%.c, $(OBJDIR)/rezvendous/%.o, $(REZVENDOUS_SRCS))

all: $(BINDIR)/$(CLIENT_TARGET) $(BINDIR)/$(REZVENDOUS_TARGET)

# Object files
$(OBJDIR)/client/%.o: $(SRCDIR)/client/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/rezvendous/%.o: $(SRCDIR)/rezvendous/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Binaries
$(BINDIR)/client: $(OBJS)/$(CLIENT_TARGET)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -o $@ $^

$(BINDIR)/rezvendous: $(OBJS)/$(REZVENDOUS_TARGET)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -o $@ $^

clean:	
	rm -f $(OBJDIR)/client/*.o $(OBJDIR)/rezvendous/*.o $(BINDIR)/client/$(CLIENT_TARGET) $(BINDIR)/rezvendous/$(REZVENDOUS_TARGET)

.PHONY: all clean
