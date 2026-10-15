#include "types.h"
typedef struct P26F5B0 { u8 pad000[0x5]; u8 m5; } P26F5B0;
void TextStyleAddSpaceWidth_26f5b0(P26F5B0 *p, s32 v) { p->m5 += (u8)v; }
