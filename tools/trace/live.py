# SPDX-License-Identifier: CC0-1.0
"""Fast, disk-free snapshots of a running portable PCSX2 (Windows only).

Why: a savestate per sample writes ~42 MB; on a busy HDD that costs seconds
per sample (see README). This module reads EE/IOP RAM straight out of the
PCSX2 process with ReadProcessMemory, but only while PCSX2's CPU thread is
frozen at a vsync boundary, so the snapshot is as consistent as a savestate.

How the vsync boundary is found:
  * With a low NominalScalar the CPU thread (EE+IOP+DMA all run on it) spends
    most of each frame asleep in the frame limiter, which sleeps inside the
    vsync handler. We poll the thread's CPU cycle counter
    (QueryThreadCycleTime); when it stops moving we SuspendThread it and
    confirm it did not move in between.
  * The thread could also be idle mid-frame (e.g. waiting for the ISO reader
    on a slow disk). To reject those, we read the EE cycle counter
    (cpuRegs.cycle) from PCSX2's memory: at a vsync it sits at a fixed phase
    of the 4,920,120-cycle NTSC frame, mid-frame stalls do not.
  * cpuRegs is found by scanning PCSX2's writable image memory for the EE
    COP0 PRId/Config pair (0x2E20, 0x73443) and checking GPR[0] == 0. The
    field offsets (COP0 at +544, cycle at +960) come from the layout of
    PCSX2's savestate 'cpuRegs' block (v2.6.3), observed, not copied.
Nothing here reads PCSX2 source; it treats the process as a black box.
"""
import ctypes
import ctypes.wintypes as wt
import re
import struct
import time

k32 = ctypes.WinDLL("kernel32", use_last_error=True)

PROCESS_VM_READ = 0x0010
PROCESS_QUERY_INFORMATION = 0x0400
THREAD_SUSPEND_RESUME = 0x0002
THREAD_QUERY_INFORMATION = 0x0040
THREAD_QUERY_LIMITED_INFORMATION = 0x0800
TH32CS_SNAPTHREAD = 0x4
MEM_COMMIT = 0x1000
MEM_IMAGE = 0x1000000
PAGE_READWRITE = 0x04
PAGE_WRITECOPY = 0x08

CPUREGS_COP0 = 512 + 16 + 16          # GPR[32] u128, HI, LO
CPUREGS_PC = CPUREGS_COP0 + 128 + 8
CPUREGS_CYCLE = 960
PRID_CONFIG = struct.pack("<II", 0x2E20, 0x73443)


class THREADENTRY32(ctypes.Structure):
    _fields_ = [("dwSize", wt.DWORD), ("cntUsage", wt.DWORD), ("th32ThreadID", wt.DWORD),
                ("th32OwnerProcessID", wt.DWORD), ("tpBasePri", wt.LONG),
                ("tpDeltaPri", wt.LONG), ("dwFlags", wt.DWORD)]


class MEMORY_BASIC_INFORMATION(ctypes.Structure):
    _fields_ = [("BaseAddress", ctypes.c_void_p), ("AllocationBase", ctypes.c_void_p),
                ("AllocationProtect", wt.DWORD), ("PartitionId", wt.WORD),
                ("RegionSize", ctypes.c_size_t), ("State", wt.DWORD),
                ("Protect", wt.DWORD), ("Type", wt.DWORD)]


k32.OpenProcess.restype = wt.HANDLE
k32.OpenThread.restype = wt.HANDLE
k32.CreateToolhelp32Snapshot.restype = wt.HANDLE
k32.ReadProcessMemory.argtypes = [wt.HANDLE, ctypes.c_void_p, ctypes.c_void_p,
                                  ctypes.c_size_t, ctypes.POINTER(ctypes.c_size_t)]
k32.VirtualQueryEx.argtypes = [wt.HANDLE, ctypes.c_void_p,
                               ctypes.POINTER(MEMORY_BASIC_INFORMATION), ctypes.c_size_t]
k32.VirtualQueryEx.restype = ctypes.c_size_t
k32.QueryThreadCycleTime.argtypes = [wt.HANDLE, ctypes.POINTER(ctypes.c_ulonglong)]
k32.SuspendThread.argtypes = [wt.HANDLE]
k32.ResumeThread.argtypes = [wt.HANDLE]
k32.SuspendThread.restype = wt.DWORD
k32.ResumeThread.restype = wt.DWORD
k32.GetThreadDescription.argtypes = [wt.HANDLE, ctypes.POINTER(ctypes.c_wchar_p)]


def _check(ok, what):
    if not ok:
        raise ctypes.WinError(ctypes.get_last_error(), what)


class Proc:
    def __init__(self, pid):
        self.pid = pid
        self.h = k32.OpenProcess(PROCESS_VM_READ | PROCESS_QUERY_INFORMATION, False, pid)
        _check(self.h, "OpenProcess")

    def read(self, addr, size):
        buf = ctypes.create_string_buffer(size)
        n = ctypes.c_size_t()
        _check(k32.ReadProcessMemory(self.h, ctypes.c_void_p(addr), buf, size, ctypes.byref(n)),
               "ReadProcessMemory")
        return buf.raw[:n.value]

    def threads(self):
        snap = k32.CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0)
        te = THREADENTRY32()
        te.dwSize = ctypes.sizeof(te)
        out = []
        ok = k32.Thread32First(snap, ctypes.byref(te))
        while ok:
            if te.th32OwnerProcessID == self.pid:
                out.append(te.th32ThreadID)
            ok = k32.Thread32Next(snap, ctypes.byref(te))
        k32.CloseHandle(snap)
        return out

    def regions(self):
        mbi = MEMORY_BASIC_INFORMATION()
        a = 0
        while k32.VirtualQueryEx(self.h, ctypes.c_void_p(a), ctypes.byref(mbi), ctypes.sizeof(mbi)):
            base = mbi.BaseAddress or 0
            yield base, mbi.RegionSize, mbi.State, mbi.Protect, mbi.Type
            a = base + mbi.RegionSize
            if a >= 0x7FFFFFFFFFFF:
                break


class Thread:
    def __init__(self, tid):
        self.tid = tid
        self.h = k32.OpenThread(THREAD_SUSPEND_RESUME | THREAD_QUERY_INFORMATION |
                                THREAD_QUERY_LIMITED_INFORMATION, False, tid)
        _check(self.h, "OpenThread")

    def name(self):
        p = ctypes.c_wchar_p()
        if k32.GetThreadDescription(self.h, ctypes.byref(p)) >= 0 and p.value:
            return p.value
        return ""

    def cycles(self):
        c = ctypes.c_ulonglong()
        _check(k32.QueryThreadCycleTime(self.h, ctypes.byref(c)), "QueryThreadCycleTime")
        return c.value

    def suspend(self):
        _check(k32.SuspendThread(self.h) != 0xFFFFFFFF, "SuspendThread")

    def resume(self):
        _check(k32.ResumeThread(self.h) != 0xFFFFFFFF, "ResumeThread")


def log_addresses(log_path):
    """EE/IOP RAM host addresses from PCSX2's startup log."""
    text = open(log_path, encoding="utf-8", errors="replace").read()
    out = {}
    for key, name in (("ee", "EE Main Memory"), ("iop", "IOP Main Memory"),
                      ("vu", "VU0/1 On-Chip Memory")):
        m = re.search(re.escape(name) + r"\s+@ 0x([0-9A-Fa-f]+)", text)
        if m:
            out[key] = int(m.group(1), 16)
    return out


class LiveSampler:
    def __init__(self, pid, log_path, idle_ms=15.0):
        self.p = Proc(pid)
        self.addr = {}
        t0 = time.time()
        while not {"ee", "iop"} <= set(self.addr):
            self.addr = log_addresses(log_path)
            if time.time() - t0 > 30:
                raise RuntimeError("RAM addresses not found in %s" % log_path)
            time.sleep(0.1)
        self.idle_s = idle_ms / 1000.0
        self.cpuregs = None
        self.cpu = None
        self._hi = 0
        self._last32 = None

    def find_cpuregs(self, tries=20):
        """Retries: right after VM start COP0 Config may not be set yet, and a
        region read can fail transiently."""
        for _ in range(tries):
            if self._find_cpuregs_once():
                return self.cpuregs
            time.sleep(0.5)
        return None

    def _find_cpuregs_once(self):
        hits = []
        for base, size, state, prot, typ in self.p.regions():
            if state != MEM_COMMIT or typ != MEM_IMAGE or prot not in (PAGE_READWRITE, PAGE_WRITECOPY):
                continue
            try:
                blob = self.p.read(base, size)
            except OSError:
                continue
            for m in re.finditer(re.escape(PRID_CONFIG), blob):
                s = m.start() - (CPUREGS_COP0 + 15 * 4)
                if s >= 0 and blob[s:s + 16] == b"\0" * 16:
                    hits.append(base + s)
        if not hits:
            return None
        # the live one is the one whose cycle counter moves
        first = {h: self.cycle_at(h) for h in hits}
        time.sleep(0.3)
        moving = [h for h in hits if self.cycle_at(h) != first[h]]
        self.cpuregs = (moving or hits)[0]
        return self.cpuregs

    def cycle64(self):
        """cpuRegs.cycle unwrapped to 64 bits. Polled every millisecond by the
        wait loop, so a wrap (every 14.5 s of EE time) is never missed even when
        no snapshot is taken for a long time."""
        c = self.cycle_at(self.cpuregs)
        if self._last32 is not None and c < self._last32:
            if self._last32 - c > 1 << 31:
                self._hi += 1 << 32           # real wrap
            else:
                # PCSX2 sometimes moves cpuRegs.cycle back a little (seen
                # once in a 25,000-frame run). Not a wrap: keep the old value
                # so the unwrapped count stays monotonic.
                return self._hi | self._last32
        self._last32 = c
        return self._hi | c

    def cycle_at(self, base):
        return struct.unpack("<I", self.p.read(base + CPUREGS_CYCLE, 4))[0]

    def find_cpu_thread(self, probe_s=1.0):
        """The CPU thread = the thread that burns the most CPU while the EE
        cycle counter advances (at low speed nearly all of it is EE work)."""
        ts = []
        for tid in self.p.threads():
            try:
                ts.append(Thread(tid))
            except OSError:
                pass
        a = {t.tid: t.cycles() for t in ts}
        time.sleep(probe_s)
        best = max(ts, key=lambda t: t.cycles() - a[t.tid])
        self.cpu = best
        return best

    def wait_vsync_and_read(self, accept, timeout=30.0, read_iop=True, pine=None):
        """Wait for the CPU thread to go idle, freeze it, and if accept(cycle)
        says the EE is at a vsync, return (cycle, ee, iop, spr) bytes (spr is
        read over PINE while frozen, b"" without pine). None on timeout."""
        def read():
            ee = self.p.read(self.addr["ee"], 0x2000000)
            iop = self.p.read(self.addr["iop"], 0x200000) if read_iop else b""
            spr = pine.read_block(0x70000000, 0x4000) if pine else b""
            return ee, iop, spr
        r = self.frozen_call(accept, read, timeout)
        return None if r is None else (r[0],) + r[1]

    def frozen_call(self, accept, fn, timeout=30.0):
        """Run fn() while the CPU thread is frozen at an idle point whose EE
        cycle passes accept(cycle). Returns (cycle, fn()) or None on timeout.
        Also used to apply PINE writes (the input hook) with the EE stopped, so
        the code-page invalidation they cause never races the EE thread."""
        t_end = time.time() + timeout
        last = self.cpu.cycles()
        since = time.perf_counter()
        while time.time() < t_end:
            time.sleep(0.001)
            self.cycle64()
            c = self.cpu.cycles()
            now = time.perf_counter()
            if c != last:
                last, since = c, now
                continue
            if now - since < self.idle_s:
                continue
            self.cpu.suspend()
            try:
                if self.cpu.cycles() != last:      # ran between check and suspend
                    continue
                cyc = self.cycle64()
                if not accept(cyc):
                    # idle, but not at a vsync: wait for it to run again
                    since = float("inf")
                    continue
                result = fn()
                if self.cycle64() != cyc or self.cpu.cycles() != last:
                    continue
                return cyc, result
            finally:
                self.cpu.resume()
        return None


# ------------------------------------------------------------- screenshots
_u32dll = ctypes.WinDLL("user32", use_last_error=True)
_gdi = ctypes.WinDLL("gdi32", use_last_error=True)
_WNDENUMPROC = ctypes.WINFUNCTYPE(wt.BOOL, wt.HWND, wt.LPARAM)


def _windows_of(pid):
    out = []

    def cb(hwnd, _):
        p = wt.DWORD()
        _u32dll.GetWindowThreadProcessId(hwnd, ctypes.byref(p))
        if p.value == pid and _u32dll.IsWindowVisible(hwnd):
            r = wt.RECT()
            _u32dll.GetClientRect(hwnd, ctypes.byref(r))
            out.append((r.right * r.bottom, hwnd, r.right, r.bottom))
        return True
    _u32dll.EnumWindows(_WNDENUMPROC(cb), 0)
    return sorted(out, reverse=True)


def window_shot(pid, path):
    """Save the largest visible window of `pid` as an image (debug aid for
    writing input scripts; uses PrintWindow, so the window may be covered).
    Returns False if there is no window or PIL is missing."""
    try:
        from PIL import Image
    except ImportError:
        return False
    wins = _windows_of(pid)
    if not wins:
        return False
    _, hwnd, w, hgt = wins[0]
    if w <= 0 or hgt <= 0:
        return False
    hdc = _u32dll.GetDC(hwnd)
    mdc = _gdi.CreateCompatibleDC(hdc)
    bmp = _gdi.CreateCompatibleBitmap(hdc, w, hgt)
    _gdi.SelectObject(mdc, bmp)
    _u32dll.PrintWindow(hwnd, mdc, 3)          # PW_CLIENTONLY | PW_RENDERFULLCONTENT

    class BITMAPINFOHEADER(ctypes.Structure):
        _fields_ = [("biSize", wt.DWORD), ("biWidth", wt.LONG), ("biHeight", wt.LONG),
                    ("biPlanes", wt.WORD), ("biBitCount", wt.WORD), ("biCompression", wt.DWORD),
                    ("biSizeImage", wt.DWORD), ("biXPelsPerMeter", wt.LONG),
                    ("biYPelsPerMeter", wt.LONG), ("biClrUsed", wt.DWORD), ("biClrImportant", wt.DWORD)]
    bi = BITMAPINFOHEADER()
    bi.biSize, bi.biWidth, bi.biHeight, bi.biPlanes, bi.biBitCount = ctypes.sizeof(bi), w, -hgt, 1, 32
    buf = ctypes.create_string_buffer(w * hgt * 4)
    _gdi.GetDIBits(mdc, bmp, 0, hgt, buf, ctypes.byref(bi), 0)
    _gdi.DeleteObject(bmp)
    _gdi.DeleteDC(mdc)
    _u32dll.ReleaseDC(hwnd, hdc)
    Image.frombuffer("RGBA", (w, hgt), buf.raw, "raw", "BGRA", 0, 1).convert("RGB").save(path)
    return True
