/* rgp:protos */
#define RGP_SELF_PadKeyCapDump_1837d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
typedef struct P1837D0 { u8 pad000[0x260]; s32 m260; } P1837D0;
extern char D_00459790[];
/*rgp*/
void PadKeyCapDump_1837d0(P1837D0 *p) { FileWriteAll_180060(D_00459790, 0x3000000, p->m260 * 6); }
