#include "apr_stack.h"
/**
 * A small application for demonstration
 * To run it after build:
 *      LD_LIBRARY_PATH=lib bin/main
 */
int main(int argc, const char *argv[]) {
    apr_pool_t *mp;

    /* create a memory pool. */
    apr_pool_create(&mp, NULL);

    /* create a new stack with an initial payload */
    apr_stack_node_t* stack = apr_stack_create(mp, 101);

    /* create and push a new node with payload 102 */
    apr_stack_push(mp, stack, 102);

    /* print out the stack */
    apr_stack_print(stack);

    apr_stack_push(mp, stack, 103);
    apr_stack_print(stack);

    /* pop the top element out of the stack */
    apr_stack_pop(stack);
    apr_stack_print(stack);

    /* destroy the memory pool. These chunks above are freed by this */
    apr_pool_destroy(mp);
    return 0;
}
