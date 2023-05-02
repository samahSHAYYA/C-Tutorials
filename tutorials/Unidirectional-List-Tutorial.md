# Unidirectional / Singly Linked Lists Tutorial

The target of this exercise is to gain working knowledge with unidirectional
(aka singly linked) lists and the corresponding basic **CRUD** operations
(**C**reate, **R**ead, **U**pdate, and **D**lete).

## Tasks

In all tasks below, do not use recursion unless explicitly asked to do so.

### Task 1: Data Structure Declaration and Textual Description

Write the code for a unidirectional list node, name the type **UniNode**,
composed of integer field called **value**. Name the next-element pointer as
**next**.

Write **displayUniList** function to display the list, and also the
**uniListToString** funtion that returns a string description of the
unidirectional list items as below:
    - Empty list: < >
    - Single-element list: < v1 >
    - Several elements list: < v1 | v2 | ... | vn >

### Task 2: Creation Operation

Write function **addUniNode** to add an element to the end of a unidirectional
list or create it if it does not exist. The function should take the **root**
node of the list and the **value** to add as arguments. Be careful about the
argument types. The function should return a **bool** as output indicating
success or failure.

Recall that in C, an **int** can be treated as bool taking **0** as false and
any other **non-zero** value as true. Nevertheless, it is recommended to use
bool from **stdbool.h** to assure clarity.

Write the recursive version of the aforementioned function and name it
**addUniNodeRecursively**.

### Task 3: Read / Find Operations

Write **findUniNode** function that takes **root** node and **value** as
arguments and returns a valid node pointer if exists, otherwise a **NULL**
pointer value. Note the search stops at first occurrence.

Write a recursive version and call it **findUniNodeRecursively**.


### Task 4: Update Operation

Write **updateUniNode** function that takes **root** node, **originalValue**,
and **newValue** as arguments and returns a **bool** telling if an update was
made or not. Note that it only updates first occurrence.

Write a recursive version, call it **updateUniNodeRecursively**.

### Task 5: Delete Operation

Write **deleteUniNode** function that takes **root** and **value** as arguments
and returns a **bool** telling if the item was deleted or not. Note that the
function only deletes first occurrence.

Write a recursive version and call it **deleteUniNodeRecursively**.

### Task 6: Delete Entire List

Write **deleteEntireUniList** function that takes **root** as arguments and
deletes all the list items. The function does not return any value.

Write a recursive version as well and call it
**deleteEntireUniListRecursively**.

### Task 7: Getting List Length / UniNodes Count

Write **getUniNodesCount** that takes **root** as argument and returns
**size_t**, the items' counts, as an output. Write the recursive version as
well and name it **getUniNodesCountRecursively**.

### Task 8: Ordered Unidirectional List

In this task, we are interested in creating an ordered unidirectional list in
which the next node is greater than or equal to the previous one.

For this, we need to write the following functions:
    - **addOrderedUniNode**
    - **addOrderedUniNodeRecursively**
    - **findOrderedUniNode**
    - **findOrderedUniNodeRecusrively**
    - **deleteOrderedUniNode**
    - **deleteOrderedUniNodeRecursively**

Note that in case of ordered unidirectional list, the search and deletion can
be further optimized as they can stop when current node value is greater than
the queried value. Also, the update function previously presented in previous
task makes no more sense. It is actually replaceable by deleting the original
value and adding orderly the new value.
