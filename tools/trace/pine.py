# SPDX-License-Identifier: CC0-1.0
"""Minimal PINE IPC client, written from the public protocol description.

PINE ("Protocol for Instrumentation of Emulators") wire format:
  request : u32 total_size (incl. these 4 bytes) | cmd* ; cmd = u8 opcode | args
  reply   : u32 total_size | u8 result (0 = OK, 0xFF = FAIL) | per-command data
All integers are little-endian. On Windows the server is TCP 127.0.0.1:<slot>.
Several commands may be batched into one request; the reply concatenates their
return values in order. The server caps a request at 650000 bytes and a reply at
450000 bytes, so big reads are split into several batches.
"""
import socket
import struct

OP_READ8, OP_READ16, OP_READ32, OP_READ64 = 0, 1, 2, 3
OP_WRITE8, OP_WRITE16, OP_WRITE32, OP_WRITE64 = 4, 5, 6, 7
OP_VERSION, OP_SAVESTATE, OP_LOADSTATE = 8, 9, 10
OP_TITLE, OP_ID, OP_UUID, OP_GAMEVERSION, OP_STATUS = 11, 12, 13, 14, 15

STATUS_NAMES = {0: "running", 1: "paused", 2: "shutdown"}

MAX_REQ = 650000
MAX_REPLY = 450000


class PineError(RuntimeError):
    pass


class Pine:
    def __init__(self, slot=28012, host="127.0.0.1", timeout=10.0):
        self.sock = socket.create_connection((host, slot), timeout=timeout)
        self.sock.setsockopt(socket.IPPROTO_TCP, socket.TCP_NODELAY, 1)

    def close(self):
        try:
            self.sock.close()
        except OSError:
            pass

    def __enter__(self):
        return self

    def __exit__(self, *a):
        self.close()

    # -- transport -------------------------------------------------------
    def _recv_exact(self, n):
        buf = bytearray()
        while len(buf) < n:
            chunk = self.sock.recv(n - len(buf))
            if not chunk:
                raise PineError("connection closed")
            buf += chunk
        return bytes(buf)

    def transact(self, body):
        """Send one batched request body; return the reply payload after the result byte."""
        self.sock.sendall(struct.pack("<I", len(body) + 4) + body)
        size = struct.unpack("<I", self._recv_exact(4))[0]
        rest = self._recv_exact(size - 4)
        if rest[0] != 0:
            raise PineError("PINE command failed (result 0x%02x)" % rest[0])
        return rest[1:]

    # -- simple commands -------------------------------------------------
    def _string(self, op):
        r = self.transact(bytes([op]))
        n = struct.unpack_from("<I", r)[0]
        return r[4:4 + n].rstrip(b"\0").decode("utf-8", "replace")

    def version(self):
        return self._string(OP_VERSION)

    def title(self):
        return self._string(OP_TITLE)

    def game_id(self):
        return self._string(OP_ID)

    def status(self):
        return struct.unpack("<I", self.transact(bytes([OP_STATUS])))[0]

    def save_state(self, slot):
        self.transact(bytes([OP_SAVESTATE, slot]))

    def load_state(self, slot):
        self.transact(bytes([OP_LOADSTATE, slot]))

    def read32(self, addr):
        return struct.unpack("<I", self.transact(struct.pack("<BI", OP_READ32, addr)))[0]

    def read8(self, addr):
        return self.transact(struct.pack("<BI", OP_READ8, addr))[0]

    def write8(self, addr, v):
        self.transact(struct.pack("<BIB", OP_WRITE8, addr, v & 0xFF))

    def write16(self, addr, v):
        self.transact(struct.pack("<BIH", OP_WRITE16, addr, v & 0xFFFF))

    def write32(self, addr, v):
        self.transact(struct.pack("<BII", OP_WRITE32, addr, v & 0xFFFFFFFF))

    def write64(self, addr, v):
        self.transact(struct.pack("<BIQ", OP_WRITE64, addr, v & 0xFFFFFFFFFFFFFFFF))

    def write_block(self, addr, data):
        """Write bytes with batched 64-bit writes (13 bytes per command)."""
        assert addr % 8 == 0 and len(data) % 8 == 0
        per = MAX_REQ // 13 - 16
        for off in range(0, len(data), 8 * per):
            chunk = data[off:off + 8 * per]
            body = b"".join(struct.pack("<BI", OP_WRITE64, addr + off + i) + chunk[i:i + 8]
                            for i in range(0, len(chunk), 8))
            self.transact(body)

    def read_block(self, addr, size):
        """Read [addr, addr+size) with batched 64-bit reads. NOT atomic: the
        emulator keeps running while this executes (see README)."""
        assert addr % 8 == 0 and size % 8 == 0
        per = min(MAX_REQ // 5, MAX_REPLY // 8) - 16
        out = bytearray()
        a, end = addr, addr + size
        while a < end:
            n = min(per, (end - a) // 8)
            body = b"".join(struct.pack("<BI", OP_READ64, a + 8 * i) for i in range(n))
            out += self.transact(body)
            a += 8 * n
        return bytes(out)
