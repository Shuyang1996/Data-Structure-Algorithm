This is the first programming assignment of data structure and algorithm class. This assignment is testing the understanding of data structure
like singly list, stack and queue. Also, it tests basic c++ programming skills like input/output functions, libraries, and so forth. 

1) Project1.cpp is the code I submitted to professor. 

2) input.txt is a sample input file

3) output.txt is a sample output file corresponds to input.txt

Below is the assignment instruction:

The program should ask the user for the name of an input text file and an output text file. The input file will contain a list of commands, one per line. Each command will direct the program to create a stack or a queue, to push a value onto a stack or a queue, or to pop a value from a stack or a queue. (Most modern sources use the terms "enqueue" or "dequeue" to indicate insertions into and deletions from queues, but we will use "push" and "pop" for both stacks and queues.)

The input file must contain one command per line. To be valid, a command must follow a very specific format. The command must consist of two or three words, depending on the type of command, separated by single spaces. The line must have no leading or trailing whitespace before the first word or after the last word. For the purposes of this assignment, a "word" is defined to be a sequence of letters and digits, except for words representing values of integers or doubles, which might also contain a single negative sign, and/or, in the case of doubles, a single decimal point. All commands (i.e., lines in the text file) will end with a single Unix-style end-of-line character ('\n').

The first word of each command must either be "create", "push", or "pop" (all lowercase letters). The second word must be a valid name for a stack or a queue. The first character of every name must be either "i", "d", or "s" (all lowercase), standing for integer, double, or string; this represents the data type that is stored in the particular stack or queue. The rest of the name must consist of only letters and digits. Both uppercase and lowercase letters are allowed, and the program should be case sensitive.

If the first word is "create", there must be a third word that will be either "stack" or "queue" (all lowercase letters). This represents the type of list being created. No two lists may have the same name. However, two lists storing different data types (e.g., one list storing integers and another storing strings) may have the same name other than the first characters (in this case, 'i' or 's'). There cannot be a stack and a queue of the same data type that share the same name.

If the first word is "push", there must be a third word representing a value to be pushed onto the stack or queue. This value must match the appropriate type corresponding to the specified stack or queue, and it must fit into a single variable; if the value is a string, it must be a single word, as defined above (containing only letters and digits).

If the first word is "pop", there must not be a third word.

Your program should read and process the commands in the text file. After each command is read, your program should output the string "PROCESSING COMMAND: " followed by the text of the command and then a single Unix-style end-of-line character. There should be exactly one space after the ':' and before the text of the line. All output should be written to the specified output file.

If the command is a "create" command, and the name of the stack or queue that is specified has already been created (whether it was created as a stack or a queue), the program should output the string "ERROR: This name already exists!" using the same casing as is displayed here. If the name is new, the stack or queue should be created, and no additional output should be written.

If the command is a push command, and the specified name does not exist, the program should output the string "ERROR: This name does not exist!" using the same casing as is displayed here. If the stack or queue does exist, the push operation should be applied, and no additional output should be written.

If the command is a pop command, and the specified name does not exist, the program should output the string "ERROR: This name does not exist!" using the same casing as is displayed here. If the stack or queue does exist, but it is empty, the program should output the string "ERROR: This list is empty!" using the same casing as is displayed here. If the stack or queue does exist and is not empty, the pop operation should be applied, and the program should output "Value popped: ", using the same casing as is displayed here, followed by the value that is popped from the stack or queue. There should be exactly one space after the ':' and before the value. For this assignment, a "pop" is assumed to both remove and return a value from the stack or queue.

Typically, if you were to implement a program like this in C++, you would use the provided C++ list class for everything. In other words, you would use it for stacks, queues, and a more general list of stacks and queues. You would probably want to have three separate high level lists for the three different data types that you will be dealing with; e.g., one list would be a list of all stacks and queues holding integers.

While this would be completely reasonable, I am going to require you to create your own data structures for stacks and queues. The purpose of this assignment is not just to make sure that you understand how to use these data structures, but to also make sure that you understand how to implement these data structures, and also to give you experience with several advanced aspects of C++ including templates, inheritance, abstract classes, and polymorphism. In fact, you will need to mix these concepts together to really implement this well, and it can get confusing!
 
I suggest you create an abstract base class called SimpleList that provides some simple aspects of singly linked list functionality. The base class should include protected member functions that provide the ability to insert a node at the start of the list, to insert a node at the end of the list, and to remove a node from the start of the list. You should probably include a private nested class called Node, which contains one field for data and another to point to the next node. See the textbook's implementation of their List class as an example of something similar. The base class should maintain pointers to the start and end of the singly linked list; you can decide if you want to include header nodes (a.k.a. dummy nodes or a sentinel nodes) at the start and/or end of each list. The base class should also include a private data member to store the name of the list and a public member function to retrieve it. The base class should also include two public pure virtual member functions for push and pop; the implementations should be in derived classes, and each can be implemented as a simple, one line member function that calls the appropriate member function of the base class. You should implement two derived classes named Stack and Queue. You should use templates so that you only have to code the base class and the derived classes once. Of course, I am leaving out a lot of details that you will have to figure out; e.g., even the constructors, which in my own implementation accept the name of the stack or queue, can be syntactically confusing.

In terms of the program functionality, other than class member functions, I personally used two functions to open the input and output files, a few functions for syntax checking (not required for your programs, so don't bother with this), one template function to search for a SimpleList with a specified name, and then one large function to parse the input file and process all the commands. Of course, this large function makes many calls to my other functions, including various member functions of my Stack and Queue classes. The large function utilizes three lists; one contains pointers to all stacks and queues of integers, another contains pointers to all stacks and queues of doubles, and the third contains pointers to all stacks and queues of strings. For these lists, you may, as I did, use the provided C++ list class. I'll even show you my declarations:

list<SimpleList<int> *> listSLi; // all integer stacks and queues
list<SimpleList<double> *> listSLd; // all double stacks and queues
list<SimpleList<string> *> listSLs; // all string stacks and queues

A new stack of integers can be created and added to the first list with lines like these:

SimpleList<int> *pSLi;
pSLi = new Stack<int>(listName);
listSLi.push_front(pSLi);



