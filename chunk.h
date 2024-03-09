#ifndef _NITRO_CHUNK_H
#define _NITRO_CHUNK_H

#include "value.h"

typedef struct {
	u8 *code;
	usize code_reserved;
	usize code_length;

	Nitro_Value *constants;
	usize constants_reserved;
	usize constants_length;
} Chunk;

void chunk_init(Chunk *c);

void chunk_free(Chunk *c);

void chunk_write_byte(Chunk *c, u8 byte);

void chunk_write_word(Chunk *c, u16 word);

u16 chunk_write_constant(Chunk *c, Nitro_Value cons);

#endif // _NITRO_CHUNK_H
