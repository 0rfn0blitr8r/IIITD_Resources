Q2

dependencies: makefile date.c dir.c Q2.c

use **make* to run the makefile, it compiles all the dependencies and runs the *main* executable file
after every input, the current working directory is printed, providing a terminal emulator look to it.

you can use the following commands:
(A) word: 
	$ word [filename] : returns the number of words in the textfile, including '\n'
	$ word -n [filename] : returns the number of words in the textfile, excluding '\n'
	$ word -d [filename] [filename] : returns the difference between number of words in the textfile, including '\n'

(B) date:
	$ date [filename] : returns last modified date and time of the provided file
	$ date -d [filename] : returns last modified date and time of the provided file,
						displaying time described by STRING
	$ date -R [filename] : returns last modified date and time of the provided file, 
						with date and time in RFC 5322 format

(C) dir:
	$ dir [dirname] : if the directory with the given name is present, returns with an error, 
					else makes a new directory and changes path to it
	$ dir -r [dirname] : if the directory with the given name is present, deletes it and makes a new one with changing the path to it, 
					else makes a new directory and changes path to it; 
	$ dir -v [dirname] : if the directory with the given name is present, returns with an error, 
					else makes a new directory and changes path to it; 
					alongwith the necessary print statements

(D) exit: to exit from our terminal