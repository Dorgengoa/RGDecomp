/* rgp:protos */
#define RGP_SELF_CharaFindCurLevelRow_3afdb0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* $4 is reloaded AFTER $5 is read out of it: the halfword argument is read
   from the object before the object pointer is replaced. */
typedef struct P3AFDB0 { u8 pad000[0x10]; u16 m10; u8 pad012[0x21E]; void *m230; } P3AFDB0;
/*rgp*/
void CharaFindCurLevelRow_3afdb0(P3AFDB0 *p, int rgp_a1, int rgp_a2, int rgp_a3) { CharaRecFindLevelRow_401880(p->m230, p->m10, 1, (int)rgp_a3); }
