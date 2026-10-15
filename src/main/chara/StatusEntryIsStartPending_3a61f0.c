#include "types.h"
typedef struct P3A61F0 { u8 m0; u8 pad001[0x1]; u8 m2; } P3A61F0;
s32 StatusEntryIsStartPending_3a61f0(P3A61F0 *p) { return p->m0 != 0 && (p->m2 & 1) != 0; }
