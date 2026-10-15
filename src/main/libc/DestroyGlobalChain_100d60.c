#include "types.h"

/* MW C++ runtime __destroy_global_chain (NMWException.cp): run and unlink
 * every registered global destructor.  Built -O4,p (config/toolchain.txt). */

typedef struct DestructorChain {
    struct DestructorChain *next; /* +0x0 */
    void *destructor;             /* +0x4 */
    void *object;                 /* +0x8 */
} DestructorChain;

/* __global_destructor_chain; same declaration as RegisterGlobalObject_100dc0 (__register_global_object) */
extern struct { DestructorChain *v; s32 pad[3]; } D_004853D0;

void DestroyGlobalChain_100d60(void)
{
    DestructorChain *gdc;

    while ((gdc = D_004853D0.v) != 0) {
        D_004853D0.v = gdc->next;
        ((void (*)(void *, short))gdc->destructor)(gdc->object, -1);
    }
}
