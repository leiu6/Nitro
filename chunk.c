#include "chunk.h"

#include <stdlib.h>
#include <stdio.h>

#define CODE_INIT_SIZE 256
#define CONSTANTS_INIT_SIZE 32

void chunk_init(Chunk *c) {
	c->code = c->constants = NULL;

	c->code = malloc(CODE_INIT_SIZE);
	if (!c->code) {
		goto cleanup;
	}

	c->code_reserved = CODE_INIT_SIZE;
	c->code_length = 0;

	c->constants = malloc(CONSTANTS_INIT_SIZE);
	if (!c->constants) {
		goto cleanup;
	}

	c->constants_reserved = CONSTANTS_INIT_SIZE;
	c->constants_length = 0;

	return;
	
cleanup:
	if (c->code) {
		free(c->code);
	}

	if (c->constants) {
		free(c->constants);
	}
	
	fprintf(stderr, "[!] Out of memory. Now exiting.\n");
	exit(-10);
}

void chunk_free(Chunk *c) {
	free(c->code);
	free(c->constants);
}

void chunk_write_byte(Chunk *c, u8 byte) {
	if (c->code_length + 1 > c->code_reserved) {
		u8 *temp = realloc(c->code, c->code_reserved * 2);
		if (!temp) {
			fprintf(stderr, "[!] Out of memory. Now exiting.\n");
			exit(-11);
		}

		c->code = temp;
		c->code_reserved *= 2;
	}

	c->code[c->code_length++] = byte;
}

void chunk_write_word(Chunk *c, u16 word) {
	u8 most, least;

	most = word >> 8;
	least = word & 0xFF;

	chunk_write_byte(c, most);
	chunk_write_byte(c, least);
}

u16 chunk_write_constant(Chunk *c, Nitro_Value cons) {
	if (c->constants_length + 1 > c->constants_reserved) {
		Nitro_Value *temp = realloc(c->constants, 2 * c->constants_reserved);
		if (!temp) {
			fprintf(stderr, "[!] Out of memory. Now exiting.\n");
			exit(-11);
		}

		c->constants = temp;
		c->constants_reserved *= 2;
	}

	c->constants[c->constants_length++] = cons;

	// Prevent integer overflow condition
	// If this happens, we are in big trouble
	assert(c->constants_length <= UINT16_MAX);
	
	return (u16)c->constants_length - 1;
}
