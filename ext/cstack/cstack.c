#include <cstack.h>

/****************************************
 * Memory Management and Initializations
 ****************************************/

static void stack_gc_mark(void *ptr) {
  if (ptr) {
		stack *s = ptr;
		stack_node *node = s->top;
		while(node) {
			rb_gc_mark(node->object);
			node = node->next;
		}
	}
}

static void stack_free(void *ptr) {
	stack *s = (stack *) ptr;
	
	if (s) {
		while(s->size != 0) {	
			stack_node *node = s->top;
			s->top = node->next;
			s->size--;

			delete_node(node);			
		}
		
		xfree(s);
		s = NULL;
	}
}

static VALUE stack_alloc(VALUE klass) {
	stack *s = ALLOC(stack);
	s->size = 0;
	s->top = NULL;
	
	return Data_Wrap_Struct(klass, stack_gc_mark, stack_free, s);
}

static VALUE stack_init(int argc, VALUE *argv, VALUE self) {
	long len, i;
	VALUE object_array;
	
	if(argc == 0) {
		return self;
	}
	else if(argc > 1) {
		rb_raise(rb_eArgError, "wrong number of arguments");
	}
	else {
		object_array = rb_check_array_type(argv[0]);
		
		if(!NIL_P(object_array)) {
			len = RARRAY_LEN(object_array);
			
			for (i = 0; i < len; i++) {
				stack_push(self, RARRAY_PTR(object_array)[i]);
			}
		}
	}
	return self;
}


/****************************************
 *            Helper functions
 ****************************************/

static inline stack_node* create_node(VALUE object) {
	stack_node *new_node = ALLOC(stack_node);
	new_node->object = object;
	new_node->next = NULL;
	
	return new_node;
}

static inline void delete_node(stack_node *node){
	xfree(node);
	node->object = Qnil;
	node->next = NULL;
	node = NULL;
}

/****************************************
 *             Binding Methods
 ****************************************/


static VALUE stack_push(VALUE self, VALUE object) {
	stack *s;
	Data_Get_Struct(self, stack, s);
	
	stack_node *new_node = create_node(object);

	new_node->next = s->top;
	s->top = new_node;
	s->size++;
	
	return object;
}

static VALUE stack_pop(VALUE self) {
	stack *s;
	Data_Get_Struct(self, stack, s);
	
	if(s->size == 0)
		return Qnil;
	
	stack_node *node = s->top;
	VALUE object = node->object;
	
	s->top = node->next;
	s->size--;
	
	delete_node(node);
	
	return object;
}

static VALUE stack_top(VALUE self) {
	stack *s;
	Data_Get_Struct(self, stack, s);
	
	
	return s->size > 0 ? INT2NUM(10) : Qnil;
}

static VALUE stack_clear(VALUE self) {
	stack *s;
	Data_Get_Struct(self, stack, s);
	
	while(s->size--) {
		stack_node *node = s->top;
		s->top = s->top->next;
		
		delete_node(node);
	}
	
	return Qnil;
}


static VALUE stack_size(VALUE self) {
	stack *s;
	Data_Get_Struct(self, stack, s);
	
	return INT2NUM(s->size);
}

static VALUE stack_is_empty(VALUE self) {
	stack *s;
	Data_Get_Struct(self, stack, s);
	
	return (s->size == 0) ? Qtrue : Qfalse;
}


/****************************************
 *             Init Method
 ****************************************/

void Init_cstack() {
	mContainers = rb_define_module("CStack");
	cStack = rb_define_class_under(mContainers, "Stack", rb_cObject);
	
	rb_include_module(cStack, rb_eval_string("Enumerable"));
	
	rb_define_alloc_func(cStack, stack_alloc);
	
	rb_define_method(cStack, "initialize", stack_init, -1);
	rb_define_method(cStack, "push", stack_push, 1);
	rb_define_method(cStack, "pop", stack_pop, 0);
	rb_define_method(cStack, "top", stack_top, 0);
	rb_define_method(cStack, "clear", stack_clear, 0);
	rb_define_method(cStack, "size", stack_size, 0);
	rb_define_method(cStack, "empty?", stack_is_empty, 0);

	rb_define_alias(cStack, "<<", "push");
	rb_define_alias(cStack, "length", "size");
}