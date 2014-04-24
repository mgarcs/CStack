#include <ruby.h>

#define FALSE 0
#define TRUE 1

typedef struct struct_deque_node {
	VALUE obj;
	struct struct_deque_node *left;
	struct struct_deque_node *right;
} deque_node;

typedef struct {
	unsigned int size;
	deque_node *front;
	deque_node *back;
} deque;
