#include "value.h"

#include <stdio.h>

int main() {
	Nitro_Value msg = nitro_value_string("Hello, worlds!");
	Nitro_Value other_msg;
	other_msg = nitro_value_array(NITRO_FLOAT, 100);

	(void)other_msg;
	
	printf("%s\n", nitro_value_as_string(msg));
	return 0;
}
