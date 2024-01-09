# apr_stack
A minimalistic implementation of a stack, written in
[C](https://en.wikipedia.org/wiki/C_(programming_language)), 
using [APR](https://apr.apache.org/).

[!WARNING]
Currently, this implementation handles **ONLY** integer numbers as payload.

### Architecture
This implementation is based on a [linked list](https://en.wikipedia.org/wiki/Linked_list) 
data structure, where the first node (head) represents the bottom of the stack and the
last node (tail), the top of it.

<img src="https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcT8kaju9g3_wS8WH0QW-zB0Fo82sJV3RJ-y7-Y1sI2gFqfsLfMYmxr2onINMJrUOpfIdg&usqp=CAU" />

### How to build
Having a [GNU make](https://www.gnu.org/software/make/), to build apr_stack, is easy.
Simply, run the command **make** and you will get two new folders. The bin, with a
simple demonstration of apr_stack, and a lib, containing the shared library of it.

### Operations
- **push** - adds an element to the top of the stack
- **pop** - takes the top element out of the stack
- **print** - generates a simple representation of the stack, starting from the given node

### Code snippets

The core concept for this implementation is the node:
```c
typedef struct node {
    int value;
    struct node* next;
} apr_stack_node_t;
```
where the **value** member is the actual payload of this node, the **next** member whereas
the link (pointer) to the following node.

To start using the stack, first you need to create it:
```c
apr_stack_node_t* stack = apr_stack_create(mp, 101);
```
Here, the **mp** is the memory pool used to allocate the space for the stack and the
**101** is the actual payload.

Once you have a stack, to create and push a new node you simply use this method:
```c
apr_stack_push(mp, stack, 102);
apr_stack_push(mp, stack, 103);
```
Here, the **mp** is the memory pool used to allocate the space for the new node, 
**stack** is the existing stack and **102** is the payload of this new node.

If you need to pop the top element out of the stack, use this command
```c
apr_stack_pop(mp, stack);
```
what will remove the value **103** from the stack.

To print the resulting stack to the console, simply use the command
```c
apr_stack_print(stack);
```
and the result will be
```c
{ 101 -> 102 -> NULL }
```
## Erata - APR memory pool and garbage collection

To prepare the conditions for the use of this stack implementation, first you need
to initialize the [APR](https://apr.apache.org/docs/apr/1.7/)'s internal structure ([apr_general.h](https://apr.apache.org/docs/apr/1.7/apr__general_8h.html)):
```c
apr_status_t rv;
...
rv = apr_initialize();
```
After this, you need to create the main memory pool ([apr_pools.h](https://apr.apache.org/docs/apr/1.7/apr__pools_8h.html)),
used by many **apr_stack** operations:
```c
apr_pool_t *mp;
...
apr_pool_create(&mp, NULL);
```

[!TIP]
Because APR allows you to define (thread-safely) sub-pools, is indicated to organize your logic
in functions (methods) what will get and use a dedicated memory pool. See [here](https://apr.apache.org/docs/apr/1.7/group__apr__pools.html#ga918adf3026c894efeae254a0446aed3b).


At the end of your perambulation in the world of **apr_stack**, you **MUST** free
the allocated memory and tear down any APR internal data structure:

```c
apr_pool_destroy(mp);
apr_terminate();
```

Enjoy it!
