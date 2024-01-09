#ifndef APR_STACK_H
#define APR_STACK_H

#include <stdio.h>

#include <apr_general.h>
#include <apr_pools.h>

/** The fundamental node type */
typedef struct node {
    int value;
    struct node* next;
} apr_stack_node_t;

/**
 * Create a new stack.
 * @param mp The pool to allocate out of.
 * @param value The integer value representing the node's payload.
 * @return The reference to the new stack.
 * @remark The future implementation will permit the use of other types, too.
 */
APR_DECLARE(apr_stack_node_t*) apr_stack_create(apr_pool_t *mp, const int value);

/**
 * Creates and pushes new node with value to the given stack.
 * @param mp The pool to allocate out of.
 * @param stack The stack to push to.
 * @param value The integer value representing the node's payload.
 * @return The reference to the new stack node.
 */
APR_DECLARE(apr_stack_node_t*) apr_stack_push(apr_pool_t *mp, apr_stack_node_t *stack, const int value);

/**
 * Pops the top element out of the stack.
 * @param stack The stack to pop out from.
 * @return The integer value from the popped node.
 */
APR_DECLARE(int) apr_stack_pop(apr_stack_node_t *stack);

/**
 * Prints out the given stack.
 * @param stack The stack to print out.
 * @example { 101 -> 102 -> NULL }
 */
APR_DECLARE(void) apr_stack_print(apr_stack_node_t *stack);

#endif //APR_STACK_H
