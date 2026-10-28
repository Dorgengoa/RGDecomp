/* rgp:protos */
#line 1
#include "types.h"
/* insect 0x00516360 -- C++ virtual dispatch on the SECOND parameter, vptr at
 * offset 0 with 108 slots (0x118..0x1B4).  [[jalr-is-cpp-virtual]]
 * SLOT = 8 + 4*N, so 0x118 is #68 and 0x1B4 is #107; the class needs 108
 * declared-and-never-defined virtuals and NO data member before the first one,
 * which is what puts the vptr at +0.
 */

class S {
public:
    VC_VPTR_MEMBER;  
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
     
    s32 v068(s32 a, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(s32, (void *, s32, int, int), 0x118, a, rgp_fwd2, rgp_fwd3); }   /* slot 0x118 */
      
    s32 v072() { return VCM0(s32, 0x128); }  
      
      
      s32 v083() { return VCM0(s32, 0x154); }
      
    s32 v087() { return VCM0(s32, 0x164); }  
    s32 v090() { return VCM0(s32, 0x170); }  
    s32 v093() { return VCM0(s32, 0x17C); }  
    s32 v096(s32 a) { return VCM(s32, (void *, s32), 0x188, a); }   /* slot 0x188 */
      s32 v099() { return VCM0(s32, 0x194); }
     s32 v101() { return VCM0(s32, 0x19C); } s32 v102() { return VCM0(s32, 0x1A0); }
    s32 v103() { return VCM0(s32, 0x1A4); }  s32 v105() { return VCM0(s32, 0x1AC); }
     s32 v107() { return VCM0(s32, 0x1B4); }
    u8    pad004[0x10 - 0x4];
    void *f010;                     /* +0x10 */
};

struct T {
    u8   pad000[0x10];
    S   *f10;                       /* +0x10 */
    u8   pad014[0x18 - 0x14];
    u8   f18;                       /* +0x18 */
    u8   pad019[0x22 - 0x19];
    s16  f22;                       /* +0x22 */
    s16  f24;                       /* +0x24 */
    u8   f26;                       /* +0x26 */
    u8   pad027;
    u8   f28;                       /* +0x28 */
    u8   pad029;
    u8   f2A[6];                    /* +0x2A */
    u8   pad030[0x36 - 0x30];
    u8   f36;                       /* +0x36 */
    u8   f37;                       /* +0x37 */
    s8   f38;                       /* +0x38 */
    s8   f39;                       /* +0x39 */
    u8   pad03A[0x3C - 0x3A];
    u8   f3C[7];                    /* +0x3C */
    u8   f43[9];                    /* +0x43 */
    u8   f4C;                       /* +0x4C */
    u8   pad04D[0x4F - 0x4D];
    u8   f4F;                       /* +0x4F */
    s16  f50;                       /* +0x50 */
    u8   pad052[0x54 - 0x52];
    s32  f54;                       /* +0x54 */
    u8   pad058[0x5C - 0x58];
    s32  f5C;                       /* +0x5C */
    u8   pad060[0x68 - 0x60];
    s32  f68;                       /* +0x68 */
};

extern "C" void insect_InsectPieceSetMaxHp_512ec0(T *t, s32 a, s32 b);
extern "C" void insect_InsectPieceSetStatus_5132d0(T *t, s32 k);
extern "C" void insect_InsectPieceSetItemDef_516580(T *t, void *p);

extern "C" void insect_InsectPieceLoadFromItem_516360(T *t, S *s, int rgp_a2, int rgp_a3)
{
    s32 i;
    s32 j;

    if (s == 0) {
        return;
    }
    t->f10 = s;
    t->f5C = s->v068(0, (int)(long)(rgp_a2), (int)(long)(rgp_a3));
    t->f18 = s->v103();
    insect_InsectPieceSetMaxHp_512ec0(t, s->v083(), 1);
    t->f22 = s->v107();
    t->f24 = s->v105();
    t->f50 = 0;
    t->f26 = s->v090();
    t->f28 = s->v093();
    for (i = 0; i < 6; i++) {
        t->f2A[i] = s->v096(i);
    }
    t->f36 = s->v099();
    t->f37 = s->v087();
    t->f54 = *(s16 *)s->f010;
    insect_InsectPieceSetItemDef_516580(t, s->f010);
    for (j = 0; j < 7; j++) {
        t->f3C[j] = 0;
    }
    for (j = 0; j < 9; j++) {
        t->f43[j] = 0;
    }
    t->f4C = 0;
    if (t->f38 == 0xC) {
        t->f4C = t->f39 * 5 + 0x32;
    }
    t->f4F = 3;
    t->f68 = s->v072();
    if (s->v101() != 0) {
        insect_InsectPieceSetStatus_5132d0(t, 0x16);
    }
    if (s->v102() != 0) {
        insect_InsectPieceSetStatus_5132d0(t, 0x17);
    }
}
