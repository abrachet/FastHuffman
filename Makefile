TARGET = encoder
WARNING = -Wall -Wshadow --pedantic
ERROR = -Wvla -Werror
OPTIMIZATIONS = -O2 -march=native 
#-mllvm -force-vector-width=8 -avx -march=core-avx2
GCC = gcc -std=c99 $(WARNING) $(ERROR) $(OPTIMIZATIONS) 

TESTFLAGS = -DNDEBUG

SRCS =  main.c count_worker.c create_tree.c

OBJS = $(SRCS:%.c=%.o)

VALGRIND = valgrind --tool=memcheck --verbose --log-file=memcheck.txt  --leak-check=full

$(TARGET): $(OBJS)
	$(GCC) $(TESTFLAGS) $(OBJS) -o $(TARGET)

.c.o:
	$(GCC) $(CFLAGS) $(TESTFLAGS) -c $*.c

clean:
	rm -f $(OBJS) $(TARGET)

testmemory: $(TARGET)
	$(VALGRIND) ./$(TARGET) global_index.js 5

debug: $(TARGET)
	lldb ./$(TARGET) text.txt 5

test1: $(TARGET)
	./encoder text.txt 1

test2: $(TARGET)
	./encoder text.txt 2

test3: $(TARGET)
	./encoder text.txt 5

testbig: $(TARGET)
	./encoder index.js 10

timebig: $(TARGET)
	time ./encoder global_index.js 5