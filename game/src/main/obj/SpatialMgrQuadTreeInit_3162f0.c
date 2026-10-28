/* rgp:protos */
#define RGP_SELF_SpatialMgrQuadTreeInit_3162f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* MEASURED (q12 sweep, 3 arms): the 16-byte copies are `lq`/`sq`, which needs
   a u128-worded member.  Four f32 members give four lwc1/swc1 pairs and four
   s32 members give the same -- 12 words too many; two s64 members give
   ld/sd pairs, 4 words too many.  A bare `u128` typedef and a struct wrapping
   one are ONE object (sha1 7b786779).
   MemStackNew_14e230 takes (size, self+4) -- the `addiu $5,$16,4` before the jal is
   its second argument, not scheduling noise.  0x42C80000 is 100.0f built with
   lui and stored as an integer word. */
typedef rg_u128 u128;
typedef struct QT { u128 v; } QT;
typedef struct Sub003162f0 { QT m00; f32 m10; u8 pad14[0x10]; s32 m24; } Sub003162f0;
extern char D_00462350[];
extern u32 strlen(const char *s);
extern char *strcpy(char *d, const char *s);
/*rgp*/
/*rgp*/
/*rgp*/
void SpatialMgrQuadTreeInit_3162f0(void *self, void *a, void *b, QT *q, f32 t)
{
    u8 *p;
    Sub003162f0 *r;
    s32 i;
    p = (u8 *)self;
    MemStackClear_14dff0(p + 4);
    MemStackInit_14d810(p + 4, a, b);
    if (strlen(D_00462350) < 0x10) {
        strcpy((char *)(p + 4), D_00462350);
    }
    *(s32 *)(p + 0x94) = 0;
    *(s32 *)(p + 0x9C) = 0x42C80000;
    *(f32 *)(p + 0xA0) = t;
    *(QT *)(p + 0xB0) = *q;
    r = ((Sub003162f0 *)MemStackNew_14e230(0x30, p + 4));
    if (r != 0) {
        r->m24 = 0;
        for (i = 0; i < 4; i++) {
            *(s32 *)((u8 *)r + i * 4 + 0x14) = 0;
        }
    }
    *(Sub003162f0 **)(p + 0x98) = r;
    if (r != 0) {
        r->m00 = *(QT *)(p + 0xB0);
        *(f32 *)((u8 *)(*(Sub003162f0 **)(p + 0x98)) + 0x10) = *(f32 *)(p + 0xA0);
    }
}
