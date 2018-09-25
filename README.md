# II1304-Experimentmodulen

## Instructions on how to run the programs

# testcases.c

To run the validating tests use the makefile to compile  

&ensp;&ensp;make all  
&ensp;&ensp;make alld  
&ensp;&ensp;&ensp;&ensp;alld compiles into debug mode, which makes the test print out additional information  
Or  
First compile skew heap and linked list to objects with or without debug flag  
&ensp;&ensp;gcc linkedlist.c -c -o linkedlist.o  
&ensp;&ensp;gcc skewheap.c -c -o skewheap.o  
Second compile the test using skew heap and linked list objects with or without debug flag  
&ensp;&ensp;gcc test.c linkedlist.o skewheap.o -o test  
To run in debug mode where additional information are provided during run, add the debug flag to any compilation  
&ensp;&ensp;"compile command" -D DEBUG  
  
Then run the tests  
&ensp;&ensp;./test  
&ensp;&ensp;&ensp;&ensp;The test then notifies if the datastructures failed or succeded the tests  
&ensp;&ensp;&ensp;&ensp;Upon failure the test will also provide which datastructure failed at which part  
			

# experiment.c

To run the experiment use the makefile to compile  
&ensp;&ensp;make all  
&ensp;&ensp;make alld  
&ensp;&ensp;&ensp;&ensp;alld compiles into debug mode, which makes the test print out additional information  
Or  
First compile skew heap and linked list to objects  
&ensp;&ensp;gcc linkedlist.c -c -o linkedlist.o  
&ensp;&ensp;gcc skewheap.c -c -o skewheap.o  
Second compile the experiment using skew heap and linked list objects  
&ensp;&ensp;gcc experiment.c linkedlist.o skewheap.o -o exp  
To run in debug mode where additional information are provided during run, add the debug flag to any compilation  
&ensp;&ensp;"compile command" -D DEBUG  
	
Then either run experiment with or without arguments. However, latter arguments requires former arguments to be assigned  
&ensp;&ensp;./exp max min n  
&ensp;&ensp;&ensp;where  
&ensp;&ensp;&ensp;max&ensp;-> maximum number of elements to run / Default=10000  
&ensp;&ensp;&ensp;min&ensp;-> minumim number of elements, also the increment size for the test / Default=10  
&ensp;&ensp;&ensp;n&ensp;-> specifik test case to run / Default=unassigned -> runs all testcases  
&ensp;&ensp;&ensp;&ensp;1 -> general-case  
&ensp;&ensp;&ensp;&ensp;2 -> worst-case doubly linked list  
&ensp;&ensp;&ensp;&ensp;3 -> worst-case skew heap  
&ensp;&ensp;note the combination max=10000 & min=10 triggers a special run time, where the tests are incremented with *10.  
