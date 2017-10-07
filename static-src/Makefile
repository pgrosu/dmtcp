CC=gcc
CFLAGS=-g3 -O0



BIN_DIR = bin



RSE_SDIR = src
RSE_ODIR = src
_RSE_OBJS = util.o replace_symbols_elf.o
RSE_OBJS = $(patsubst %,$(RSE_ODIR)/%,$(_RSE_OBJS))
_RSE = replace-symbols-elf
RSE = $(patsubst %,$(BIN_DIR)/%,$(_RSE))



TEST_RSE_SDIR = test
TEST_RSE_ODIR = test
_TEST_RSE_OBJS = dmtcp_plt.o wrapfile1.o wrapfile2.o wrapfile3.o main.o
_TEST_RSE_OBJS_WRAPS = wrapfile1.o wrapfile2.o wrapfile3.o
_TEST_RSE_OBJS_MAIN = main.o
TEST_RSE_OBJS = $(patsubst %,$(TEST_RSE_ODIR)/%,$(_TEST_RSE_OBJS))
TEST_RSE_OBJS_WRAPS = $(patsubst %,$(TEST_RSE_ODIR)/%,$(_TEST_RSE_OBJS_WRAPS))
TEST_RSE_OBJS_MAIN = $(patsubst %,$(TEST_RSE_ODIR)/%,$(_TEST_RSE_OBJS_MAIN))
_TEST_RSE = test_rse
TEST_RSE = $(patsubst %,$(TEST_RSE_ODIR)/%,$(_TEST_RSE))

# ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

default: $(RSE)



$(RSE): $(RSE_OBJS)
	$(CC) -o $@ $^ $(CFLAGS)



test: $(RSE) $(TEST_RSE)
	$(TEST_RSE)
	@echo Test passed!

$(TEST_RSE): $(TEST_RSE_OBJS)
	$(RSE) -o $(TEST_RSE_OBJS_WRAPS) -k foo_wrap --keepnumstr=__dmtcp_   --only_def
	$(RSE) -o $(TEST_RSE_OBJS_MAIN) -s foo      --singlestr=__dmtcp_plt
	$(CC) -o $@ $^ $(CFLAGS)

# ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

$(RSE_ODIR)/%.o: $(RSE_SDIR)/%.c
	$(CC) -c -o $@ $< $(CFLAGS)

$(TEST_RSE_ODIR)/%.o: $(TEST_RSE_SDIR)/%.c
	$(CC) -c -o $@ $< $(CFLAGS)

# ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

clean:
	find . -name "*.o" -type f -delete
	rm -f $(RSE)
