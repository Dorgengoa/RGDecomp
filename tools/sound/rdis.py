"""Small MIPS R3000 disassembler for IRX modules (own code, CC0).

usage: python rdis.py FILE.IRX [start_hex end_hex]
Prints imports/exports, then a linear disassembly of .text with import
names, jal targets, and lui/addiu|ori pair constants resolved.
"""
import struct, sys
sys.path.insert(0, "tools/census/platform")
import irx  # read-only use

R = ["zero", "at", "v0", "v1", "a0", "a1", "a2", "a3", "t0", "t1", "t2", "t3", "t4", "t5", "t6", "t7",
     "s0", "s1", "s2", "s3", "s4", "s5", "s6", "s7", "t8", "t9", "k0", "k1", "gp", "sp", "fp", "ra"]

NAMES = {
    "sifcmd": {14: "sceSifInitRpc", 15: "sceSifBindRpc", 16: "sceSifCallRpc", 17: "sceSifRegisterRpc",
               18: "sceSifCheckStatRpc", 19: "sceSifSetRpcQueue", 20: "sceSifGetNextRequest",
               21: "sceSifExecRequest", 22: "sceSifRpcLoop", 23: "sceSifGetOtherData",
               24: "sceSifRemoveRpc", 25: "sceSifRemoveRpcQueue", 12: "sceSifSendCmd", 13: "isceSifSendCmd"},
    "thbase": {4: "CreateThread", 5: "DeleteThread", 6: "StartThread", 7: "StartThreadArgs", 8: "ExitThread",
               9: "ExitDeleteThread", 10: "TerminateThread", 14: "ChangeThreadPriority", 20: "GetThreadId",
               22: "ReferThreadStatus", 24: "SleepThread", 25: "WakeupThread", 26: "iWakeupThread",
               28: "iCancelWakeupThread", 33: "DelayThread", 34: "GetSystemTime", 35: "SetAlarm",
               36: "iSetAlarm", 37: "CancelAlarm", 39: "USec2SysClock", 40: "SysClock2USec"},
    "thsemap": {4: "CreateSema", 5: "DeleteSema", 6: "SignalSema", 7: "iSignalSema", 8: "WaitSema", 9: "PollSema"},
    "thevent": {4: "CreateEventFlag", 5: "DeleteEventFlag", 6: "SetEventFlag", 7: "iSetEventFlag",
                8: "ClearEventFlag", 9: "iClearEventFlag", 10: "WaitEventFlag"},
    "intrman": {4: "RegisterIntrHandler", 5: "ReleaseIntrHandler", 6: "EnableIntr", 7: "DisableIntr",
                17: "CpuSuspendIntr", 18: "CpuResumeIntr", 23: "QueryIntrContext"},
    "sysmem": {4: "AllocSysMemory", 5: "FreeSysMemory", 14: "Kprintf"},
    "loadcore": {5: "FlushDcache", 6: "RegisterLibraryEntries", 7: "ReleaseLibraryEntries"},
    "sysclib": {8: "look_ctype_table", 11: "memcmp", 12: "memcpy", 14: "memset", 17: "bzero", 22: "strcmp",
                27: "strlen", 29: "strncmp", 36: "strtol"},
    "stdio": {4: "printf"},
    "sifman": {7: "sceSifSetDma", 8: "sceSifDmaStat"},
    "timrman": {4: "AllocHardTimer", 6: "FreeHardTimer", 20: "SetTimerHandler", 22: "SetupHardTimer",
                23: "StartHardTimer", 24: "StopHardTimer"},
    "libsd": {4: "sceSdInit", 5: "sceSdSetParam", 6: "sceSdGetParam", 7: "sceSdSetSwitch", 8: "sceSdGetSwitch",
              9: "sceSdSetAddr", 10: "sceSdGetAddr", 11: "sceSdSetCoreAttr", 12: "sceSdGetCoreAttr",
              13: "sceSdNote2Pitch", 14: "sceSdPitch2Note", 15: "sceSdProcBatch", 16: "sceSdProcBatchEx",
              17: "sceSdVoiceTrans", 18: "sceSdBlockTrans", 19: "sceSdVoiceTransStatus",
              20: "sceSdBlockTransStatus", 21: "sceSdSetTransCallback", 22: "sceSdSetIRQCallback",
              23: "sceSdSetEffectAttr", 24: "sceSdGetEffectAttr", 25: "sceSdClearEffectWorkArea",
              26: "sceSdSetTransIntrHandler", 27: "sceSdSetSpu2IntrHandler",
              28: "sceSdGetTransIntrHandlerArgument", 29: "sceSdGetSpu2IntrHandlerArgument",
              30: "sceSdStopTrans", 31: "sceSdCleanEffectWorkArea", 32: "sceSdSetEffectMode",
              33: "sceSdSetEffectModeParams"},
}


def sx(v):
    return v - 0x10000 if v & 0x8000 else v


def exports(ws, vb):
    out = {}
    for i, w in enumerate(ws):
        if w == 0x41C00000 and i + 4 < len(ws):
            name = struct.pack("<2I", ws[i + 3], ws[i + 4]).split(b"\0")[0].decode("latin-1")
            j, n = i + 5, 0
            while j < len(ws) and ws[j] != 0:
                out[ws[j]] = f"{name}#{n}"
                j += 1
                n += 1
    return out


def dis(w, pc):
    op = w >> 26
    rs, rt, rd, sa, fn = (w >> 21) & 31, (w >> 16) & 31, (w >> 11) & 31, (w >> 6) & 31, w & 63
    imm = w & 0xFFFF
    if w == 0:
        return "nop", None
    if op == 0:
        t = {0: "sll", 2: "srl", 3: "sra"}
        if fn in t:
            return f"{t[fn]} {R[rd]},{R[rt]},{sa}", None
        t = {4: "sllv", 6: "srlv", 7: "srav"}
        if fn in t:
            return f"{t[fn]} {R[rd]},{R[rt]},{R[rs]}", None
        if fn == 8:
            return f"jr {R[rs]}", None
        if fn == 9:
            return f"jalr {R[rd]},{R[rs]}", None
        if fn == 12:
            return "syscall", None
        if fn == 13:
            return "break", None
        t = {16: "mfhi", 18: "mflo"}
        if fn in t:
            return f"{t[fn]} {R[rd]}", None
        t = {17: "mthi", 19: "mtlo"}
        if fn in t:
            return f"{t[fn]} {R[rs]}", None
        t = {24: "mult", 25: "multu", 26: "div", 27: "divu"}
        if fn in t:
            return f"{t[fn]} {R[rs]},{R[rt]}", None
        t = {32: "add", 33: "addu", 34: "sub", 35: "subu", 36: "and", 37: "or", 38: "xor", 39: "nor",
             42: "slt", 43: "sltu"}
        if fn in t:
            return f"{t[fn]} {R[rd]},{R[rs]},{R[rt]}", None
        return f".word {w:08x}", None
    if op == 1:
        t = {0: "bltz", 1: "bgez", 16: "bltzal", 17: "bgezal"}
        tg = (pc + 4 + (sx(imm) << 2)) & 0xFFFFFFFF
        return f"{t.get(rt, '?regimm')} {R[rs]},{tg:x}", tg
    if op in (2, 3):
        tg = ((pc + 4) & 0xF0000000) | ((w & 0x3FFFFFF) << 2)
        return f"{'j' if op == 2 else 'jal'} {tg:x}", tg
    if op in (4, 5, 6, 7):
        tg = (pc + 4 + (sx(imm) << 2)) & 0xFFFFFFFF
        n = {4: "beq", 5: "bne", 6: "blez", 7: "bgtz"}[op]
        if op in (4, 5):
            return f"{n} {R[rs]},{R[rt]},{tg:x}", tg
        return f"{n} {R[rs]},{tg:x}", tg
    t = {8: "addi", 9: "addiu", 10: "slti", 11: "sltiu"}
    if op in t:
        return f"{t[op]} {R[rt]},{R[rs]},{sx(imm)}", None
    t = {12: "andi", 13: "ori", 14: "xori"}
    if op in t:
        return f"{t[op]} {R[rt]},{R[rs]},0x{imm:x}", None
    if op == 15:
        return f"lui {R[rt]},0x{imm:x}", None
    if op == 16:
        return f"cop0 {w:08x} (rs={rs} rt={R[rt]} rd={rd})", None
    t = {32: "lb", 33: "lh", 34: "lwl", 35: "lw", 36: "lbu", 37: "lhu", 38: "lwr", 40: "sb", 41: "sh",
         42: "swl", 43: "sw", 46: "swr"}
    if op in t:
        return f"{t[op]} {R[rt]},{sx(imm)}({R[rs]})", None
    return f".word {w:08x}", None


def main():
    path = sys.argv[1]
    blob = open(path, "rb").read()
    info = irx.parse(blob)
    ws, vb = info["words"], info["vbase"]
    imp = {a: f"{l}#{n}:{NAMES.get(l, {}).get(n, '?')}" for a, (l, n) in info["imports"].items()}
    exp = exports(ws, vb)
    lo = int(sys.argv[2], 16) if len(sys.argv) > 2 else 0
    hi = int(sys.argv[3], 16) if len(sys.argv) > 3 else len(ws) * 4
    print(f"; {info['name']} {info['version']} text={len(ws)*4:#x}")
    for a, n in sorted(exp.items()):
        print(f"; export {n} -> {a:x}")
    jt = set()
    for i, w in enumerate(ws):
        if w >> 26 == 3:
            jt.add((w & 0x3FFFFFF) << 2)
    regs = {}
    for i in range(lo // 4, min(hi // 4, len(ws))):
        pc = vb + 4 * i
        w = ws[i]
        if pc in exp:
            print(f"\n;=== export {exp[pc]}")
        if pc in jt and pc not in imp:
            print(f"\n;--- sub_{pc:x}")
            regs = {}
        if pc in imp and (w == 0x03E00008):
            print(f"{pc:6x}: stub {imp[pc]}")
            continue
        s, tg = dis(w, pc)
        note = ""
        op, rs, rt = w >> 26, (w >> 21) & 31, (w >> 16) & 31
        if op == 15:
            regs[rt] = (w & 0xFFFF) << 16
        elif op in (9, 13) and rs in regs:
            v = (regs[rs] + sx(w & 0xFFFF)) & 0xFFFFFFFF if op == 9 else regs[rs] | (w & 0xFFFF)
            note = f" ; ={v:#x}"
            s2 = blob_str(info, v)
            if s2:
                note += f' "{s2}"'
            regs[rt] = v
        elif op in (35, 43, 32, 36, 33, 37, 40, 41) and rs in regs:
            note = f" ; [{(regs[rs] + sx(w & 0xFFFF)) & 0xFFFFFFFF:#x}]"
            if op in (35, 32, 36, 33, 37):
                regs.pop(rt, None)
        elif op == 0 and (w & 63) in (0x21, 0x25):
            regs.pop((w >> 11) & 31, None)
        if tg is not None and op == 3:
            nm = imp.get(tg) or exp.get(tg) or f"sub_{tg:x}"
            note += f" ; -> {nm}"
        print(f"{pc:6x}: {w:08x}  {s}{note}")


def blob_str(info, v):
    t = info["text"]
    if 0 <= v < len(t):
        e = t.find(b"\0", v)
        s = t[v:e]
        if 4 <= len(s) < 80 and all(32 <= c < 127 or c in (9, 10) for c in s):
            return s.decode().replace("\n", "\\n")
    return None


if __name__ == "__main__":
    main()
