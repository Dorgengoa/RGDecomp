#pragma opt_propagation off
#include "types.h"
typedef rg_u128 u128;


struct GObj {
    u8 pad000[0x1B0];
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void v15(f32 a0) { VCM(void, (void *, f32), 0x44, a0); }
    
    
    
    
    
    
};

struct Key {
    s16 a;
    s16 b;
};

extern "C" GObj *D_004832F8;
extern "C" u8 *D_004832AC;
extern "C" s32 D_004832D8;
extern "C" s32 D_00483308;
extern "C" s32 D_0048330C;
extern "C" s16 D_00483360;
extern "C" u8 D_004E94C0[];
extern "C" u8 D_004E9510[];
extern "C" u8 D_004E9530[];

extern "C" {
s32 GetDrawCtx_15de80(void);
s32 DrawEnvGetVsyncInterval_144130(s32);
void BitArray16Ctor_3842e0(Key *);
s32 BitArrayTest_384320(Key *, s32);
u8 *GetCurrentScene_1f5be0(void);
u8 *MemStackHeapAllocFront_14dd10(s32, s32);
u8 *InsectCageGetCollTris_389d70(s32 *);
void memcpy(void *, void *, s32);
s32 MenuObjBuildAvoidTrisMaybe_3878c0(u8 *, u8 *, s32, u128 *);
void MenuObjWalkUpdateMaybe_387390(u8 *, u8 *, s32);
void MemStackHeapFree_14dcb0(s32, u8 *);
void MenuObjUpdate_386f70(u8 *, f32);
void MenuObjSetUpdate_3850c0(s32);
void MenuCursorObjBobUpdate_386150(void *);
void InsectCageItemIconTick_385f50(void *);
void UiUpdateWidgets_2913a0(s32);
void InsectCageMenuUpdate_38a230(void);
}

void InsectCageMenuUpdate_38a230(void)
{
    u128 q;
    Key key __attribute__((aligned(16)));
    s32 count;
    s32 total;
    f32 scale;
    s32 heap;
    u8 *buf;
    s32 pos;
    u8 *src;
    s32 i;
    s32 j;
    s32 left;
    s32 off;
    s32 n;
    s32 k;
    s32 r;




    r = DrawEnvGetVsyncInterval_144130(GetDrawCtx_15de80());
    scale = 1.0f;
    if (r == 1) {
        scale = 0.5f;
    }
    BitArray16Ctor_3842e0(&key);
    key.a = D_00483360;
    if (BitArrayTest_384320(&key, 1) == 0) {
        heap = *(s32 *)(GetCurrentScene_1f5be0() + 0x180C);
        count = 0;
        buf = MemStackHeapAllocFront_14dd10(heap, 0x300);
        if (buf != 0) {
            src = InsectCageGetCollTris_389d70(&count);
            for (i = 0; i < count; i++) {
                memcpy(buf + i * 0x60, src + i * 0x60, 0x60);
            }
            total = count;
            j = 0;
            do {
                {
                u8 *bs = D_004832AC;
                off = j * 0x9D0;
                if (*(s8 *)(bs + off + 0x985) != 0) {
                    q = *(u128 *)(D_004832AC + off + 0x180);
                    pos = total;
                    left = 0x80;
                    k = 0;
                    do {
                        if (j != k) {
                            n = MenuObjBuildAvoidTrisMaybe_3878c0(D_004832AC + k * 0x9D0, buf + pos * 0x60, left, &q);
                            pos += n;
                            left -= n;
                        }
                    } while (++k < 5);
                    MenuObjWalkUpdateMaybe_387390(D_004832AC + off, buf, pos);
                }
                }
            } while (++j < 5);
            MemStackHeapFree_14dcb0(heap, buf);
        }
    }
    i = 0;
    do {
        MenuObjUpdate_386f70(D_004832AC + i * 0x9D0, scale);
    } while (++i < 5);
    MenuObjSetUpdate_3850c0(D_004832D8);
    if (BitArrayTest_384320(&key, 3) == 0) {
        MenuCursorObjBobUpdate_386150(D_004E94C0);
    }
    InsectCageItemIconTick_385f50(D_004E9510);
    InsectCageItemIconTick_385f50(D_004E9530);
    if (D_00483308 != 0) {
        UiUpdateWidgets_2913a0(D_00483308);
    }
    if (D_0048330C != 0) {
        UiUpdateWidgets_2913a0(D_0048330C);
    }
    if (D_00483308 != 0 && D_004832F8 != 0) {
        D_004832F8->v15(scale);
    }
}
