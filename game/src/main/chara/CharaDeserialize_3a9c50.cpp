/* rgp:protos */
#line 1
#include "types.h"

class Item {
public:
    VC_VPTR_MEMBER;
    
    
    
    void v018(s32 a0, s32 a1) { VCM(void, (void *, s32, s32), 0x18, a0, a1); }
    void v01C() { VCM0(void, 0x1C); }
    u8 pad4[0x24];
};
class Self {
public:
    VC_VPTR_MEMBER;
    
    
    
    void v018() { VCM0(void, 0x18); }
    void v01C() { VCM0(void, 0x1C); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void v508(s32 a0, s32 a1) { VCM(void, (void *, s32, s32), 0x508, a0, a1); }
    u8 pad4[0x304];
    Item items[10];
    s32 m498;
};

extern "C" {
extern s32 UnpackWordTriple_370d70(s32, s32, s32 *, s32 *, s32 *);
extern s32 CharaFindSlotByCompositeId_3ad300(Self *, s32);
extern void CharaLearnAbility_3ad460(Self *, s32, int, int);
extern s16 * CharaFindLearnedAbility_3ad940(Self *, s32, s32, int);
extern s32 D_004658F8[];
}

extern "C" s32 CharaDeserialize_3a9c50(Self *self, s32 p0, s32 n0)
{
    s32 p;
    s32 n;
    s32 t;
    s32 l;
    s32 sz;
    s32 t2;
    s32 l2;
    s32 sz2;
    s32 total;
    s32 r;
    s32 r2;
    s32 q;
    s32 cnt;
    s32 k;
    s16 *e;
    Item *it;

    if (p0 == 0 || n0 <= 0) {
        return 0;
    }
    p = p0;
    n = n0;
    total = 0;
    if (D_004658F8[0] < n0) {
        return 0;
    }
    while (n > 0) {
        t = 0;
        l = 0;
        sz = 0;
        r = UnpackWordTriple_370d70(p, n, &t, &l, &sz);
        if (r <= 0) {
            break;
        }
        total += r;
        p += r;
        n -= r;
        switch (t) {
        case 5:
            self->v508(p, sz);
            for (k = 0; k < 10; k++) {
                self->items[k].v01C();
            }
            self->m498 = 0;
            break;
        case 6:
            q = p;
            cnt = sz;
            k = 0;
            while (cnt > 0) {
                t2 = 0;
                l2 = 0;
                sz2 = 0;
                r2 = UnpackWordTriple_370d70(q, cnt, &t2, &l2, &sz2);
                if (r2 <= 0) {
                    break;
                }
                q += r2;
                cnt -= r2;
                if (t2 == 7 && k < 10) {
                    it = &self->items[k++];
                    it->v018(q, sz2);
                }
                q += sz2;
                cnt -= sz2;
            }
            e = CharaFindLearnedAbility_3ad940(self, 0x86, 0, 0);
            if (e != 0 && CharaFindSlotByCompositeId_3ad300(self, 0x86) == 0) {
                CharaLearnAbility_3ad460(self, *e, 0, 0);
            }
            break;
        }
        total += sz;
        p += sz;
        n -= sz;
    }
    return total;
}
