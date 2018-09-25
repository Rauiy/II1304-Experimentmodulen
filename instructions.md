##Instructions on how to run the programs

#testcases.c

To run the validating tests use the makefile to compile 
	make all
	make alld
		alld compiles into debug mode, which makes the test print out additional information
Or
First compile skew heap and linked list to objects with or without debug flag
	gcc linkedlist.c -c -o linkedlist.o 
	gcc skewheap.c -c -o skewheap.o 
Second compile the test using skew heap and linked list objects with or without debug flag
	gcc test.c linkedlist.o skewheap.o -o test 
To run in debug mode where additional information are provided during run, add the debug flag to any compilation
	"compile command" -D DEBUG
	
Then run the tests 
	./test
		The test then notifies if the datastructures failed or succeded the tests 
		Upon failure the test will also provide which datastructure failed at which part
			

#experiment.c

To run the experiment use the makefile to compile 
	make all
	make alld
		alld compiles into debug mode, which makes the test print out additional information
Or
First compile skew heap and linked list to objects
	gcc linkedlist.c -c -o linkedlist.o 
	gcc skewheap.c -c -o skewheap.o 
Second compile the experiment using skew heap and linked list objects
	gcc experiment.c linkedlist.o skewheap.o -o exp 
To run in debug mode where additional information are provided during run, add the debug flag to any compilation
	"compile command" -D DEBUG
	
Then either run experiment with or without arguments. However, latter arguments requires former arguments to be assigned
	./exp max min n
	where 
		max -> maximum number of elements to run / Default=10000
		min -> minumim number of elements, also the increment size for the test / Default=10
		n 	-> specifik test case to run / Default=unassigned -> runs all testcases
			1 -> general-case
			2 -> worst-case doubly linked list
			3 -> worst-case skew heap
	note the combination max=10000 & min=10 triggers a special run time, where the tests are incremented with *10.