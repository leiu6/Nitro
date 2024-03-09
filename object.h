#ifndef _NITRO_OBJECT_H
#define _NITRO_OBJECT_H

#include "value.h"

/**
 * Nitro objects (Nitro_Object) is the format for variables in Nitro that have
 * heap, rather than stack semantics. For types such as string and array,
 * Nitro_Value can hold a reference to a Nitro_Object. These objects vary in
 * size and are garbage collected using a mark-and-sweep garbage collection
 * system.
 */

typedef struct Nitro_Object Nitro_Object;
struct Nitro_Object {
	Nitro_Type    type;  // The type of the object
	Nitro_Object *next;  // The next object in the list
	Nitro_Object *prev;  // The previous object in the list
	bool          marked;// If the object is reachable or not
};

/**
 * Internal function for allocating Nitro_Objects. Adds the object to the
 * control of the garbage collector. The object is guaranteed to be of the size
 * in bytes, and this function will never return NULL. It is intended to be
 * cast to the derived type that the object actually is.
 */
Nitro_Object *allocate_object(Nitro_Type type, usize size);


/* Types of objects */
typedef struct {
	Nitro_Object obj;

	usize length;
	char  data[];
} Nitro_StringObject;

typedef struct {
	Nitro_Object obj;

	usize reserved;
	usize length;
	Nitro_Type values_type;
	Nitro_Value values[];
} Nitro_ArrayObject;

#endif // _NITRO_OBJECT_H
