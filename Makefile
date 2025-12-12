CC = gcc
CFLAGS = -Wall -Wextra -O2 -g -std=c11
SRCDIR = src
OBJDIR = build/obj
BINDIR = build
TARGET = $(BINDIR)/eau_analyse

SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SOURCES))

.PHONY: all clean

all: $(TARGET)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJS) | $(BINDIR)
	$(CC) $(CFLAGS) $(OBJS) -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(BINDIR):
	mkdir -p $(BINDIR)

clean:
	rm -rf $(OBJDIR) $(BINDIR) vol_*.dat vol_*.png plot_*.plt leaks_history.dat
