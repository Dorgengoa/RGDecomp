#include "types.h"

/* factory.bin overlay, 0x004EC5E0 -- bring the factory scene's widget cache
 * up.  452 bytes, 116 instructions, 4 conditional branches, 25 calls
 * (br/ins 0.034): the branch-light band, straight transcription.
 *
 * ★★ `n->f74` IS WRITTEN THREE TIMES IN A ROW with three different addresses
 * and mwcc deletes the first two as dead stores in every non-volatile
 * spelling.  `volatile` on the DECLARATION keeps them -- the anti-dead-store
 * shape of the volatile lever ([[overlay-c-pipeline]], title `004EAF70`).
 *
 * ★ D_004B2570, D_0047CD50, D_0047CD30 and D_004792E0 are outside the gp
 * window (_gp 0x00485170 +/- 0x8000), so all four are `const` incomplete
 * arrays and take %hi/%lo.  Every D_00484xxx and D_004807xx/D_0048080x is
 * inside the window and stays plain.
 */

typedef struct Node {
    u8                pad00[0x50];
    u8                f50;
    u8                pad51[0x23];
    const void *volatile f74;
    u8                pad78[0x20];
    u8                f98;
    u8                pad99[0x3];
    u8                f9C;
} Node;

extern void *D_00484A28;                        /* _gp - 0x748  */
extern void *D_00484A2C;                        /* _gp - 0x744  */
extern void *D_00484A30;                        /* _gp - 0x740  */
extern void *D_00484A44;                        /* _gp - 0x72C  */
extern void *D_00484A48;                        /* _gp - 0x728  */
extern void *D_00484A4C;                        /* _gp - 0x724  */
extern void *D_00484A50;                        /* _gp - 0x720  */
extern void *D_00484A54;                        /* _gp - 0x71C  */
extern void *D_00484A58;                        /* _gp - 0x718  */
extern void *D_00484A5C;                        /* _gp - 0x714  */
extern void *D_00484A60;                        /* _gp - 0x710  */
extern u8    D_00484A64;                        /* _gp - 0x70C  */
extern u8    D_00484A6C;                        /* _gp - 0x704  */
extern void *D_00484A70;                        /* _gp - 0x700  */
extern u8    D_00484A84;                        /* _gp - 0x6EC  */
extern u8    D_004807FC;                        /* _gp - 0x4974 */
extern u8    D_00480800;                        /* _gp - 0x4970 */

extern const u8 D_004B2570[];
extern const u8 D_0047CD50[];
extern const u8 D_0047CD30[];
extern const u8 D_004792E0[];

extern void  factory_FactoryMenuResRequest_4ec2f0(void);
extern void *func_207DF0(void);
extern void *func_15DE40(void);
extern void  func_158AC0(void *s, s32 id);
extern void *func_206AC0(void);
extern void *func_206A90(void);
extern void  func_14D830(void *p);
extern void  func_183960(const u8 *p);
extern void  func_183D50(const u8 *p, u32 a, s32 b, s32 c);
extern void  func_183940(const u8 *p);
extern Node *func_14E230(s32 id, void *heap);
extern void  func_28DB70(void *p);

void factory_FactoryMenuOpen_4ec5e0(void)
{
    void *s;
    Node *n;

    D_00484A28 = func_207DF0();
    s = func_15DE40();
    func_158AC0(s, 0x32D);
    func_158AC0(s, 0x32F);
    func_158AC0(s, 0x32E);
    D_00484A2C = func_206AC0();
    func_14D830(D_00484A2C);
    D_00484A30 = func_206A90();
    func_14D830(D_00484A30);
    D_00484A64 = 0;
    D_004807FC = 1;
    factory_FactoryMenuResRequest_4ec2f0();
    func_183960(D_004B2570);
    func_183D50(D_004B2570, 0xF00C, 0xA, 4);
    func_183940(D_004B2570);
    D_00484A6C = 1;
    D_00484A44 = func_14E230(0x7C, D_00484A2C);
    n = func_14E230(0xC0, D_00484A2C);
    if (n != 0) {
        func_28DB70(&n->f98);
    }
    D_00484A48 = n;
    n = func_14E230(0xC4, D_00484A2C);
    if (n != 0) {
        n->f74 = D_0047CD50;
        n->f74 = D_0047CD30;
        n->f74 = D_004792E0;
        func_28DB70(&n->f9C);
    }
    D_00484A4C = n;
    D_00484A50 = func_14E230(0x74, D_00484A2C);
    D_00484A54 = func_14E230(0x78, D_00484A2C);
    n = func_14E230(0x7C, D_00484A2C);
    if (n != 0) {
        func_28DB70(&n->f50);
    }
    D_00484A58 = n;
    n = func_14E230(0xC0, D_00484A2C);
    if (n != 0) {
        func_28DB70(&n->f98);
    }
    D_00484A5C = n;
    D_00484A60 = func_14E230(0x94, D_00484A2C);
    D_00480800 = 1;
    D_00484A70 = 0;
    D_00484A84 = 0;
}
