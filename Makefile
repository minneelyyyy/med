
OUT=med

OBJS=src/med.o src/rope.o src/rc.o src/buffer.o

all: $(OUT)

.PHONY: all clean
.SUFFIXES: .c .o

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<

$(OUT): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS) -lncurses

clean:
	rm -f $(OUT) $(OBJS)
