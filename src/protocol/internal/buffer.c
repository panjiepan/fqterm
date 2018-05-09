#include "buffer.h"
#include <string.h>
#include <endian.h>

#define INITSIZE 2048

int buffer_init(buffer *b)
{
	b->p = (uint8_t*)malloc(INITSIZE);
	if (b->p) {
		b->alloc = INITSIZE;
		b->offs = 0;
		b->sz = 0;
		return 1;
	} else {
		return 0;
	}
}

static int ensure(buffer *b, size_t len)
{
	if (b->offs + b->sz + len <= b->alloc)
		return 1;

	uint8_t *r = (uint8_t*)realloc(b->p, (b->alloc + len) * 2);
	if (r == NULL)
		return 0;
	b->alloc = (b->alloc + len) * 2;
	b->p = r;
	return 1;
}

int buffer_append(buffer *b, const uint8_t *s, size_t len)
{
	if (ensure(b, len)) {
		memcpy(b->p + b->offs + b->sz, s, len);
		b->sz += len;
		return 1;
	} else {
		return 0;
	}
}

int buffer_append_byte(buffer *b, uint8_t x)
{
	if (ensure(b, 1)) {
		b->p[b->offs + b->sz] = x;
		b->sz += 1;
	} else {
		return 0;
	}
}

int buffer_append_be32(buffer *b, uint32_t x)
{
	uint32_t beint = htobe32(x);
	if (ensure(b, 4)) {
		*(uint32_t*)(b->p + b->offs + b->sz) = beint;
		b->sz += 4;
	} else {
		return 0;
	}
}
