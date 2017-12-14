DIR=~/diffdmtcp/dmtcp
#DIR=~/dmtcp

default:
	gcc -g -O0 -c main.c
	$(DIR)/bin/dmtcp_ld $(DIR) main.o

run:
	$(DIR)/bin/dmtcp_launch --no-gzip -p 7779 ./a.out

restart:
	$(DIR)/bin/dmtcp_restart -p 7779 ckpt*.dmtcp

tidy:
	rm -f ckpt*.dmtcp ckpt*.temp

gdb:
	gdb --args $(DIR)/bin/dmtcp_launch -p 7779 ./a.out


clean:
	rm -f *.o a.out *.nz core.* *.dmtcp
	rm -rf ./addrs
