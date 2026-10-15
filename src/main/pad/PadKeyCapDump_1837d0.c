#include "types.h"
typedef struct P1837D0 { u8 pad000[0x260]; s32 m260; } P1837D0;
extern const char D_00459790[];
extern void FileWriteAll_180060(const char *s, s32 b, s32 c);
void PadKeyCapDump_1837d0(P1837D0 *p) { FileWriteAll_180060(D_00459790, 0x3000000, p->m260 * 6); }
