/* SPDX-License-Identifier: CC0-1.0 */
/* EE libpad (v1 API) reimplemented over the padman HLE (src/ps2/padmc).
 * docs/PADMC.md. The game links the asm-bodied retail libpad out (PLAN transform
 * 6); these functions take its place with the retail semantics read off the asm in
 * game/src/main/sdk/scePad*.c. */
#ifndef SCE_LIBPAD_H
#define SCE_LIBPAD_H
#ifdef __cplusplus
extern "C" {
#endif

#define scePadStateDiscon  0
#define scePadStateFindPad 1
#define scePadStateFindCTP1 2
#define scePadStateExecCmd 5
#define scePadStateStable  6
#define scePadStateError   7
#define scePadStateClosed  99 /* retail scePadGetState on a port that is not open */

#define scePadReqStateComplete 0
#define scePadReqStateFaild    1
#define scePadReqStateBusy     2

#define InfoModeCurID    1
#define InfoModeCurExID  2
#define InfoModeCurExOffs 3
#define InfoModeIdTable  4

#define InfoActFunc    1
#define InfoActSub     2
#define InfoActSize    3
#define InfoActCurr    4

int scePadInit(int mode);
int scePadEnd(void);
int scePadPortOpen(int port, int slot, void *addr);
int scePadPortClose(int port, int slot);
int scePadRead(int port, int slot, unsigned char *rdata); /* bytes copied (int, not u8: the game declares s32) */
/* Port-side (not Sony API): read observer for the timing record
 * (docs/TIMING-LOCKSTEP.md), called after every scePadRead of an open port
 * with the bytes copied.  NULL removes it.  One observer. */
typedef void (*scePadHleReadHook)(void *user, int port, int slot, const unsigned char *data, int len);
void scePadHleSetReadHook(scePadHleReadHook fn, void *user);
int scePadGetState(int port, int slot);
int scePadGetReqState(int port, int slot);
int scePadSetReqState(int port, int slot, int state);
int scePadInfoMode(int port, int slot, int term, int offs);
int scePadSetMainMode(int port, int slot, int offs, int lock);
int scePadInfoAct(int port, int slot, int actno, int term);
int scePadSetActAlign(int port, int slot, const unsigned char *data);
int scePadSetActDirect(int port, int slot, const unsigned char *data);
int scePadSetButtonInfo(int port, int slot, int info);
int scePadEnterPressMode(int port, int slot);
int scePadExitPressMode(int port, int slot);
int scePadInfoPressMode(int port, int slot);
int scePadGetPortMax(void);
int scePadGetSlotMax(int port);
int scePadGetModVersion(void);
/* Newer half of the port's DMA buffer; copies its 0x80 bytes to `copy` if non-NULL. */
unsigned char *scePadGetDmaStr(int port, int slot, void *copy);

/* game-tree name (census/platform_sdk_surface.tsv) */
int scePadEnd_12b208(void);

#ifdef __cplusplus
}
#endif
#endif
