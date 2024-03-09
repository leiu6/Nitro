#include "object.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static Nitro_Object *gc_list_tail = NULL;

/**
 * Inserts an object in the linked list after the other one
 */
static void list_insert_after(Nitro_Object *after, Nitro_Object *insert) {
        insert->next = after->next;
	insert->prev = after;
	if (after->next) {
		after->next->prev = insert;
	}
}

/**
 * Removes an object from the linked list
 */
static void list_remove(Nitro_Object *obj) {
	if (obj->next) {
		obj->next->prev = obj->prev;
	}

	if (obj->prev) {
		obj->prev->next = obj->next;
	}
}

#ifdef NITRO_DEBUG_MEMORY

/**
 * Prints information to stdout about each item in the list
 */
static void list_print_all() {
	Nitro_Object *obj = gc_list_tail;

	puts("Garbage Collector List {");
	
	while (obj != NULL) {
		puts("Nitro_Object:");
		printf("Type: %d\n", obj->type);
		printf("Marked: %s\n", (obj->marked) ? "true" : "false");
		printf("\n");

		obj = obj->prev;
	}

	puts("} Garbage Collector List End");
}

#endif

static void *emalloc(usize size) {
	void *buf = calloc(1, size);
	if (!buf) {
		fprintf(stderr, "[!] Out of memory. Now exiting.\n");
		exit(-10);
	}
	return buf;
}

/*
static void *erealloc(void *ptr, usize old_size, usize size) {
	assert(size > old_size && "Attempt to shrink allocation");
	
	char *temp = realloc(ptr, size);
	if (!temp) {
		fprintf(stderr, "[!] Out of memory. Now exiting.\n");
		exit(-11);
	}

	// Let's zero out the memory
	memset(temp + old_size, 0x00, size - old_size);

	return temp;
}
*/

// TODO: utilize these
static void deallocate_object(Nitro_Object *) __attribute__((unused));
static void gc_flush_all() __attribute__((unused));
static void gc_flush_unmarked() __attribute__((unused));

/**
 * Deallocates the object, removing it from the linked list in the process
 */
static void deallocate_object(Nitro_Object *obj) {
	if (obj == gc_list_tail) {
		gc_list_tail = obj->prev;
	}
	list_remove(obj); // Remove from the garbage collector
	free(obj);

#ifdef NITRO_DEBUG_MEMORY
	puts("Deallocated Object");
	list_print_all();
#endif
}

/**
 * Deallocates all objects under GC control, regardless of their marked status
 */
static void gc_flush_all() {
	Nitro_Object *obj = gc_list_tail;
	while (obj != NULL) {
		deallocate_object(obj);
		obj = obj->prev;
	}
}

/**
 * Deallocates all unmarked (unreachable) objects
 */
static void gc_flush_unmarked() {
	Nitro_Object *obj = gc_list_tail;
	while (obj != NULL) {
		if (!obj->marked) {
			deallocate_object(obj);
		}
		obj = obj->prev;
	}
}

Nitro_Object *allocate_object(Nitro_Type type, usize size) {
	assert(size > sizeof(Nitro_Object) && "Too small object allocation");

	Nitro_Object *obj = emalloc(size);

	obj->type = type;
	obj->next = NULL;
	obj->prev = NULL;
	obj->marked = false;

	if (gc_list_tail) {
		list_insert_after(gc_list_tail, obj);
	}

	gc_list_tail = obj;

#ifdef NITRO_DEBUG_MEMORY
	list_print_all();
#endif
	
	return obj;
}
