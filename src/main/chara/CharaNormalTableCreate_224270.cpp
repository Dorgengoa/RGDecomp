#include "types.h"
#pragma opt_lifetimes off
#undef NULL
#define NULL 0
extern "C" {
s32 CharaTableCreate_223ff0(...);

/* Paired clone of CharaTableCreate_223ff0 (identical opcode shape, different callees
   and register numbers) -- see that file for the derivation and the
   STATUS note; this file ports the same shape with CharaNormalTableCreate_224270's own
   constants (a `0x40`-byte pool instead of `0x48`, vtable at +0x88/sub-
   object at +0x7C instead of +0x98/+0x8C) and callees (CharaNormalTableObjCtor_224410,
   CharaNormalTableObjInit_2243b0, CharaNormalTableObjGetBody_2243a0, CharaNormalTableClone_225830).

   STATUS: PARKED, same as CharaTableCreate_223ff0 -- right shape, 4 bytes (1 word)
   short on the shared-tail merge (see that file's STATUS note; the same
   pragma/spelling sweep was measured null here too). */

extern void *MemStackHeapAlloc_14db10(void *heap, s32 kind, s32 n, s32 sz);
extern void *MemStackNew_14e130(s32 sz, void *heap);
extern void MemStackReturnToOwnerMaybe_14dad0(void *self);
extern void MemStackHeapFree_14dcb0(void *self, void *p);
extern void *CharaNormalTableObjCtor_224410(void *obj);
extern void CharaNormalTableObjInit_2243b0(void *obj);
extern void *CharaNormalTableObjGetBody_2243a0(void *obj);
extern s32 CharaNormalTableClone_225830(void *a, void *buf, void *c, s32 m, void *e);

typedef struct VtblFUN_00224270 {
    u8 pad0[0x8];
    s32 (*unk8)(void *, void *);
} VtblFUN_00224270;

typedef struct ObjFUN_00224270 {
    u8 pad00[0x1C];
    u8 sub1C[1];                      /* +0x1C */
    u8 pad1D[0x7C - 0x1D];
    u8 sub7C[1];                      /* +0x7C */
    u8 pad7D[0x88 - 0x7D];
    VtblFUN_00224270 *unk88;          /* +0x88 */
} ObjFUN_00224270;

class VC_0 {
public:
    u8 pad[0xC];
    virtual s32 f(void * x0);
};
s32 CharaNormalTableCreate_224270(u8 *p, void *c, s32 m)
{
    ObjFUN_00224270 *o = (ObjFUN_00224270 *)p;
    s32 var17;
    void *buf;

    if (c == 0 || m == 0) {
        var17 = 0;
        goto done;
    }
    buf = MemStackHeapAlloc_14db10((void *)m, 2, 0, 0x40);
    if (buf != 0) {
        var17 = (s32)MemStackNew_14e130(0x40, (void *)m);
        if (var17 != 0) {
            var17 = (s32)CharaNormalTableObjCtor_224410((void *)var17);
        }
        if (var17 != 0) {
            CharaNormalTableObjInit_2243b0((void *)var17);
            if (CharaNormalTableClone_225830(CharaNormalTableObjGetBody_2243a0((void *)var17), buf, c, m, o->sub1C) != 0) {
                MemStackReturnToOwnerMaybe_14dad0((void *)m);
                if (((VC_0 *)(o->sub7C))->f((void *)var17) != 0) {
                    return var17;
                }
            }
        }
    }
    MemStackReturnToOwnerMaybe_14dad0((void *)m);
    MemStackHeapFree_14dcb0((void *)m, buf);
    var17 = 0;
done:
    return var17;
}

}
