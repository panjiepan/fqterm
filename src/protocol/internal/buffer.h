#ifndef BUFFER_H
#define BUFFER_H

#include <stdlib.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif /* } */

typedef struct
{
	uint8_t *p;
	size_t alloc;
	size_t offs;
	size_t sz;
} buffer;

/* if success, return 1, otherwise return 0 */
int buffer_init(buffer *);
static inline void buffer_deinit(buffer *b)
{
	free(b->p);
}
static inline uint8_t *buffer_data(buffer *b)
{
	return b->p + b->offs;
}
static inline size_t buffer_len(buffer *b)
{
	return b->sz;
}
static inline void buffer_consume(buffer *b, size_t L)
{
	b->offs += L;
	b->sz -= L;
}
int buffer_append(buffer *b, const uint8_t *s, size_t len);
int buffer_append_byte(buffer *b, uint8_t);
int buffer_append_be32(buffer *b, uint32_t);

#ifdef __cplusplus
}
#endif

#endif
