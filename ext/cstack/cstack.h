#include <ruby.h>

typedef struct stack_node_s {
	VALUE object;
	struct stack_node_s *next;
} stack_node;

typedef struct {
	size_t size;
	stack_node *top;
} stack;


static VALUE cStack;
static VALUE mContainers;

static void stack_free(void *ptr);
static VALUE stack_alloc(VALUE klass);
static VALUE stack_init(int argc, VALUE *argv, VALUE self);

static inline stack_node* create_node(VALUE object);
static inline void delete_node(stack_node *node);

static VALUE stack_push(VALUE self, VALUE object);
static VALUE stack_pop(VALUE self);
static VALUE stack_top(VALUE self);
static VALUE stack_clear(VALUE self);
static VALUE stack_size(VALUE self);
static VALUE stack_is_empty(VALUE self);







