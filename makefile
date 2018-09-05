all: ll sh test exp

alld: lld shd testd expd

renew: clean all

td: ll sh testd

ed: ll sh expd

lld:
	gcc linkedlist.c -c -o linkedlist.o -D DEBUG
shd:
	gcc skewheap.c -c -o skewheap.o -D DEBUG
testd:
	gcc testcases.c linkedlist.o skewheap.o -o test -D DEBUG
expd:
	gcc experiment.c linkedlist.o skewheap.o -o exp -D DEBUG
	
ll:
	gcc linkedlist.c -c -o linkedlist.o 
sh:
	gcc skewheap.c -c -o skewheap.o 
test:
	gcc testcases.c linkedlist.o skewheap.o -o test 
exp:
	gcc experiment.c linkedlist.o skewheap.o -o exp 

clean:
	rm linkedlist.o skewheap.o test.exe exp.exe