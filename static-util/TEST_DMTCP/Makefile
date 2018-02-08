DIR=~/diffdmtcp/dmtcp
#DIR=~/dmtcp

default:
	gcc -g -O0 -c main.c
	$(DIR)/bin/dmtcp_ld_NORUNTIME --dmtcp $(DIR) --objs main.o --libs libdmtcp_static.a libdmtcp_pid_static.a
	g++ -g -O0 -static -I. main.o ./libdmtcp_static.a.MOD ./libc.a.MOD ./libpthread.a.MOD

run:
	#$(DIR)/bin/dmtcp_launch --no-gzip -p 7779 ./a.out
	$(DIR)/bin/dmtcp_launch -p 7779 ./a.out

restart:
	$(DIR)/bin/dmtcp_restart -p 7779 ckpt*.dmtcp

tidy:
	rm -f ckpt*.dmtcp ckpt*.temp

gdb:
	gdb --args $(DIR)/bin/dmtcp_launch -p 7779 ./a.out


clean:
	rm -f *.o a.out *.nz core.* *.dmtcp *.MOD
	rm -rf ./addrs
