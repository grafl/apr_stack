#include "apr_stack.h"

__attribute__((constructor)) void init(void) {
    /* The setup of APR internal data structures */
    apr_status_t rv;
    rv = apr_initialize();
    if (rv != APR_SUCCESS) {
        printf("The setup of APR internal data structures failed.\n");
    }
}

APR_DECLARE(apr_stack_node_t*) apr_stack_create(apr_pool_t *mp, const int value) {
    apr_stack_node_t* node = apr_pcalloc(mp, sizeof(apr_stack_node_t));
    node->value = value;
    return node;
}

APR_DECLARE(apr_stack_node_t*) apr_stack_push(apr_pool_t *mp, apr_stack_node_t *stack, const int value) {
    apr_stack_node_t* current = stack;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = apr_pcalloc(mp, sizeof(apr_stack_node_t));
    current->next->value = value;
    current->next->next = NULL;
    return current->next;
}

APR_DECLARE(int) apr_stack_pop(apr_stack_node_t *stack) {
    int retval = 0;
    if(stack->next == NULL) {
        return stack->value;
    }
    apr_stack_node_t* current = stack;
    while (current->next->next != NULL) {
        current = current->next;
    }
    retval = current->next->value;
    current->next = NULL;
    return retval;
}

APR_DECLARE(void) apr_stack_print(apr_stack_node_t *stack) {
    apr_stack_node_t* temporary = stack;
    printf("{ ");
    while(temporary != NULL) {
        printf("%d -> %s",
           temporary->value,
           (temporary->next != NULL ? "" : "NULL")
        );
        temporary = temporary->next;
    }
    printf(" }\n");
}

__attribute__((destructor))  void fini(void) {
    /* tear down any APR internal data structures */
    apr_terminate();
}
