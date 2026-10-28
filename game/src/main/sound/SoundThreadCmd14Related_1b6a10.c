/* rgp:protos */
#define RGP_SELF_SoundThreadCmd14Related_1b6a10 1
#include "port/game_protos.h"
#line 1
#include "types.h"
typedef struct P1B6A10 { s32 m00; s32 m04; s32 m08; } P1B6A10;
/*rgp*/
void SoundThreadCmd14Related_1b6a10(P1B6A10 *p) { SoundIopSendCmdG3S3_166020(p->m00, p->m04, p->m08); }
