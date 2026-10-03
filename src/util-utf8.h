#ifndef UTIL_UTF8_H
#define UTIL_UTF8_H
#include <stddef.h>

unsigned utf8_seqlen(unsigned char lead);

unsigned utf8_encode_len(unsigned codepoint);

size_t utf8_encode(unsigned codepoint, unsigned char *out);

#endif
