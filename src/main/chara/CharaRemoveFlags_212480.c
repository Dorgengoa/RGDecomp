#include "types.h"
/* `ld` / `nor` / `and` / `sd`: a 64-bit bit-clear in place. */
typedef struct P212480 { u8 pad000[0x568]; u64 m568; } P212480;
void CharaRemoveFlags_212480(P212480 *p, u64 mask) { p->m568 = p->m568 & ~mask; }
