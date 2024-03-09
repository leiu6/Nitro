#include "value.h"

#include "object.h"

#include <string.h>

Nitro_Value nitro_value_array(Nitro_Type type, usize reserve) {
	Nitro_ArrayObject *array = (Nitro_ArrayObject *)allocate_object(
                NITRO_ARRAY,
		sizeof(Nitro_ArrayObject) + sizeof(Nitro_Value) * reserve
        );

	array->reserved = reserve;
	array->length = 0;
	array->values_type = type;
	
	return (Nitro_Value){
		.type = NITRO_ARRAY,
		.value.r = (void *)array
	};
}

Nitro_Value nitro_value_string(const char *str) {
	usize len = strlen(str);

	Nitro_StringObject *obj = (Nitro_StringObject *)allocate_object(
	        NITRO_STRING,
		sizeof(Nitro_StringObject) + len + 1
        );

	obj->length = len;

	memcpy(obj->data, str, len);
	obj->data[len] = '\0';
	
	return (Nitro_Value){
		.type = NITRO_STRING,
		.value.r = (void *)obj
	};
}

const char *nitro_value_as_string(Nitro_Value value) {
	assert(nitro_value_is_string(value));
	return ((Nitro_StringObject *)value.value.r)->data;
}

usize nitro_value_string_length(Nitro_Value value) {
	assert(nitro_value_is_string(value));
	return ((Nitro_StringObject *)value.value.r)->length;
}
