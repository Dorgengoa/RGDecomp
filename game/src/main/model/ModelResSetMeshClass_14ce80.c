/* rgp:protos */
#define RGP_SELF_ModelResSetMeshClass_14ce80 1
#include "port/game_protos.h"
#line 1
#include "types.h"
typedef struct A14CE80 { u8 pad000[0x68]; s32 m68; } A14CE80;
typedef struct B14CE80 { A14CE80 *m00; } B14CE80;
void ModelResSetMeshClass_14ce80(B14CE80 *p, s32 v)
{
    A14CE80 *q;
    u8       ok;

    q = p->m00;
    ok = q != 0;
    if (ok) {
        q->m68 = v;
    }
}
