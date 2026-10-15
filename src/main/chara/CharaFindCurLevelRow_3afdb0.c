#include "types.h"
/* $4 is reloaded AFTER $5 is read out of it: the halfword argument is read
   from the object before the object pointer is replaced. */
typedef struct P3AFDB0 { u8 pad000[0x10]; u16 m10; u8 pad012[0x21E]; void *m230; } P3AFDB0;
extern void CharaRecFindLevelRow_401880(void *a, s32 b, s32 c);
void CharaFindCurLevelRow_3afdb0(P3AFDB0 *p) { CharaRecFindLevelRow_401880(p->m230, p->m10, 1); }
