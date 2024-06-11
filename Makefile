CC = gcc
CFLAGS = -g -Wall

CLIENT_TARGET = punch
RENDEZVOUS_TARGET = rendezvous

SRCDIR = src
OBJDIR = obj
BINDIR = bin

CLIENT_SRCS = $(wildcard $(SRCDIR)/client/*.c)
RENDEZVOUS_SRCS = $(wildcard $(SRCDIR)/rendezvous/*.c)

#SRCS = $(wildcard $(SRCDIR)/*.c)
CLIENT_OBJS = $(patsubst $(SRCDIR)/client/%.c, $(OBJDIR)/client/%.o, $(CLIENT_SRCS))
RENDEZVOUS_OBJS = $(patsubst $(SRCDIR)/rendezvous/%.c, $(OBJDIR)/rendezvous/%.o, $(RENDEZVOUS_SRCS))

all: $(BINDIR)/$(CLIENT_TARGET) $(BINDIR)/$(RENDEZVOUS_TARGET)

# Object files
$(OBJDIR)/client/%.o: $(SRCDIR)/client/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/rendezvous/%.o: $(SRCDIR)/rendezvous/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Binaries
$(BINDIR)/$(CLIENT_TARGET): $(CLIENT_OBJS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -o $@ $^

$(BINDIR)/$(RENDEZVOUS_TARGET): $(RENDEZVOUS_OBJS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -o $@ $^

clean:	
	rm -f $(OBJDIR)/client/*.o $(OBJDIR)/rendezvous/*.o $(BINDIR)/$(CLIENT_TARGET) $(BINDIR)/$(RENDEZVOUS_TARGET)

.PHONY: all clean
