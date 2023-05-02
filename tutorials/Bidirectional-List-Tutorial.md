# Bidirectional / Doubly Linked Lists Tutorial

The target of this exercise is to gain working knowledge with bidirectional
(aka doubly linked) lists and the corresponding basic **CRUD** operations
(**C**reate, **R**ead, **U**pdate, and **D**lete).

## Tasks

In all tasks below, do not use recursion unless explicitly asked to do so.

### Task 1: Data Structure Declaration and Textual Description

Write the code for a bidirectional list node, name the type **BiNode**,
composed of integer field called **value**. Name the previous-element pointer
as **prev** and the next-element pointer as **next**.

Write **displayBiList** function to display the list, and also the
**biListToString** funtion that returns a string description of the
bidirectional list items as below:
    - Empty list: < >
    - Single-element list: < v1 >
    - Several elements list: < v1 | v2 | ... | vn >

### Task 2: Creation Operation

Write function **addBiNode** to add an element to the end of a bidirectional
list or create it if it does not exist. The function should take the **root**
node of the list and the **value** to add as arguments. Be careful about the
argument types. The function should return a **bool** as output indicating
success or failure.

Recall that in C, an **int** can be treated as bool taking **0** as false and
any other **non-zero** value as true. Nevertheless, it is recommended to use
bool from **stdbool.h** to assure clarity.

Write the recursive version of the aforementioned function and name it
**addBiNodeRecursively**.

### Task 3: Read / Find Operations

Write **findBiNode** function that takes **root** node and **value** as
arguments and returns a valid node pointer if exists, otherwise a **NULL**
pointer value. Note the search stops at first occurrence.

Write a recursive version and call it **findBiNodeRecursively**.


### Task 4: Update Operation

Write **updateBiNode** function that takes **root** node, **originalValue**,
and **newValue** as arguments and returns a **bool** telling if an update was
made or not. Note that it only updates first occurrence.

Write a recursive version, call it **updateBiNodeRecursively**.

### Task 5: Delete Operation

Write **deleteBiNode** function that takes **root** and **value** as arguments
and returns a **bool** telling if the item was deleted or not. Note that the
function only deletes first occurrence.

Write a recursive version and call it **deleteBiNodeRecursively**.

### Task 6: Delete Entire List

Write **deleteEntireBiList** function that takes **root** as arguments and
deletes all the list items. The function does not return any value.

Write a recursive version as well and call it
**deleteEntireBiListRecursively**.

### Task 7: Getting List Length / Items Count

Write **getBiNodesCount** that takes **root** as argument and returns
**size_t**, the items' counts, as an output. Write the recursive version as
well and name it **getBiNodesCountRecursively**.

### Task 8: Ordered Bidirectional List

In this task, we are interested in creating an ordered bidirectional list in
which the next node is greater than or equal to the previous one.

For this, we need to write the following functions:
    - **addOrderedBiNode**
    - **addOrderedBiNodeRecursively**
    - **findOrderedBiNode**
    - **findOrderedBiNodeRecusrively**
    - **deleteOrderedBiNode**
    - **deleteOrderedBiNodeRecursively**

Note that in case of ordered bidirectional list, the search and deletion can
be further optimized as they can stop when current node value is greater than
the queried value. Also, the update function previously presented in previous
task makes no more sense. It is actually replaceable by deleting the original
value and adding orderly the new value.
