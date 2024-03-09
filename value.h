#ifndef _NITRO_VALUE_H
#define _NITRO_VALUE_H

#include "common.h"

typedef enum {
	NITRO_NIL,
	NITRO_CHAR,
	NITRO_BOOL,
	NITRO_INT,
	NITRO_FLOAT,
	NITRO_ARRAY,
	NITRO_STRING,
	NITRO_FUNCTION
} Nitro_Type;

typedef struct {
	Nitro_Type type;

	union {
		char c;
		bool b;
		i64 i;
		f64 f;
		void *r;
	} value;
} Nitro_Value;

#define nitro_value_nil() (Nitro_Value){ .type = NITRO_NIL, .value.r = NULL }

#define nitro_value_char(ch) (Nitro_Value){ .type = NITRO_CHAR, .value.c = ch }

#define nitro_value_bool(bl) (Nitro_Value){ .type = NITRO_BOOL, .value.b = bl }

#define nitro_value_int(in) (Nitro_Value){ .type = NITRO_INT, .value.i = in }

#define nitro_value_float(fl) (Nitro_Value){ .type = NITRO_FLOAT, .value.f = fl }

Nitro_Value nitro_value_array(Nitro_Type type, usize reserve);

Nitro_Value nitro_value_string(const char *str);

// TODO: implement function to make Nitro_Value function


#define nitro_value_is_nil(v) (v.type == NITRO_NIL)

#define nitro_value_is_char(v) (v.type == NITRO_CHAR)

#define nitro_value_is_bool(v) (v.type == NITRO_BOOL)

#define nitro_value_is_int(v) (v.type == NITRO_INT)

#define nitro_value_is_float(v) (v.type == NITRO_FLOAT)

#define nitro_value_is_array(v) (v.type == NITRO_ARRAY)

#define nitro_value_is_string(v) (v.type == NITRO_STRING)

#define nitro_value_is_function(v) (v.type == NITRO_FUNCTION)


#define nitro_value_as_char(v) (v.value.c)

#define nitro_value_as_bool(v) (v.value.b)

#define nitro_value_as_int(v) (v.value.i)

#define nitro_value_as_float(v) (v.value.f)

// TODO: implement array accessor and string stuff

const char *nitro_value_as_string(Nitro_Value value);

usize nitro_value_string_length(Nitro_Value value);

#endif // _NITRO_VALUE_H
