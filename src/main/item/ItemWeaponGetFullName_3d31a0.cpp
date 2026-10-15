#include "types.h"

/* jalr through vtable slot 0xB4: virtual_index = (0xB4 - 8) / 4 = 43.
 * [[jalr-is-cpp-virtual]] */

typedef struct S2_003d31a0 {
    u8 pad0[0xC];
    s8 *unkC;
} S2_003d31a0;

class VE_003d31a0 {
public:
    virtual void v00(); virtual void v01(); virtual void v02();
    virtual void v03(); virtual void v04(); virtual void v05();
    virtual void v06(); virtual void v07(); virtual void v08();
    virtual void v09(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14();
    virtual void v15(); virtual void v16(); virtual void v17();
    virtual void v18(); virtual void v19(); virtual void v20();
    virtual void v21(); virtual void v22(); virtual void v23();
    virtual void v24(); virtual void v25(); virtual void v26();
    virtual void v27(); virtual void v28(); virtual void v29();
    virtual void v30(); virtual void v31(); virtual void v32();
    virtual void v33(); virtual void v34(); virtual void v35();
    virtual void v36(); virtual void v37(); virtual void v38();
    virtual void v39(); virtual void v40(); virtual void v41();
    virtual void v42();
    virtual s32 *v43();          /* slot 0xB4 */

    u8 pad4[0xC];
    S2_003d31a0 *unk10;
};

extern "C" s8 *strcpy(s8 *, s8 *);
extern "C" s8 *strcat(s8 *, s8 *);

extern "C" s8 *ItemWeaponGetFullName_3d31a0(VE_003d31a0 *arg0, s8 *arg1)
{
    S2_003d31a0 *temp;
    s32 *temp2;

    if (arg1 == 0) {
        return 0;
    }
    temp = arg0->unk10;
    if (temp == NULL) {
        return 0;
    }
    strcpy(arg1, temp->unkC);
    temp2 = arg0->v43();
    if (temp2 != NULL) {
        strcat(arg1, (s8 *)*temp2);
    }
    return arg1;
}
