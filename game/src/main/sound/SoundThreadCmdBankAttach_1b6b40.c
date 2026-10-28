/* rgp:protos */
#define RGP_SELF_SoundThreadCmdBankAttach_1b6b40 1
#include "port/game_protos.h"
#line 1
#include "types.h"
typedef struct P1B6B40 { s32 m00; s32 m04; s32 m08; } P1B6B40;
/*rgp*/
void SoundThreadCmdBankAttach_1b6b40(P1B6B40 *p) { SoundIopSendCmdG1S0_165828(5, p->m00, p->m04, p->m08); }
