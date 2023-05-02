# Challenge: Cirular Lists

A circular list (aka a circular linked list), is a type of data structure where 
each element, called a node, has a pointer or reference to the next node in the 
list. However, unlike a regular linked list where the last node's next pointer
is set to null, in a circular list, the last node's next pointer points back to
the first node, forming a loop or a circle.

This means that we can traverse the list starting from any node and continue 
until we reach the same node again, without encountering a null pointer, which 
is the end of a regular linked list.

In this **challenge / assignment**, you are expected to follow the same lead as
in previous **unidirectional** and **bidirectional** tutorials and write the
same function as those requested there. 

In this assignmnet, no new structure deifinition is required, and you are 
expected directly to work with **UniNode** and **BiNode** data  types, creating
**unicircular** and **** lists. Each of these two circular lists will
have their own header ans source files (i.e., **unicircular.h**, 
**unicircular.c**, **bicircular.h**, and **bicircular.c**).

After having them done, you should add the source files to
**list_lib/CMakeLists.txt** file (see how **unidirectional** and 
**bidirectional** source files are added).