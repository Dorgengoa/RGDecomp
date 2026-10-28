/* rg-override: replaces game/src/main/sys/RegisterGlobalObject_100dc0.c sha256 e8a23999c4e60789593876f4b431e351eacd44656e657f6a02ddabc70a14e72a
 * why: stores the chain head by absolute address `*(N **)0x004853D0` (MAIN .bss, not a
 * hardware register, so the hwaccess stage leaves it); spelled with the data symbol */
/* rgp:protos */
#define RGP_SELF_RegisterGlobalObject_100dc0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
typedef struct N00100dc0 {
    struct N00100dc0 *next;   /* +0x0 */
    s32 b;                    /* +0x4 */
    s32 a;                    /* +0x8 */
} N00100dc0;

/* MSL __register_global_object: push {next, dtor, object} on the global
   destructor chain whose head is D_004853D0 (DestroyGlobalChain_100d60,
   src/crt/crt_msl.c, pops it at exit). */
extern struct { N00100dc0 *v; s32 pad[3]; } D_004853D0;

s32 RegisterGlobalObject_100dc0(s32 a, s32 b, N00100dc0 *n)
{
    n->next = D_004853D0.v;
    n->b = b;
    n->a = a;
    D_004853D0.v = n; /* retail: *(N00100dc0 **)0x004853D0 = n */
    return a;
}
