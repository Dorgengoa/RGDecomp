"""Admission helpers. Candidate generation alone never enables these hooks."""
import hashlib
import json
import re
import struct
from pathlib import Path
from data2c_elf import ELF

ROOT = Path(__file__).resolve().parent.parent


def enabled():
    cfg = ROOT / 'config/data2c.json'
    return cfg.exists() and json.loads(cfg.read_text()).get('admitted', False)


def objects():
    return json.loads((ROOT / 'handoff/data2c-manifest.json').read_text())['objects']


def addresses():
    result = {}
    # Interior assembler aliases can name a pointer target without having a
    # function-sized row in main.symbols.txt. Derive them from annotated
    # addresses, including historical listings after retirement.
    import data2c
    cfg = json.loads((ROOT / 'config/data2c.json').read_text())
    # The release ships these label addresses precomputed
    # (handoff/data2c-listing-labels.json): the listings they come from are
    # only in the project's git history.
    frozen = ROOT / 'handoff/data2c-listing-labels.json'
    if frozen.exists():
        result.update(json.loads(frozen.read_text()))
    for path in (() if frozen.exists() else ('asm/main.s', 'asm/data/main_data.data.s')):
        pending = []
        for line in data2c.listing(path, cfg, cfg.get('historical_inputs', False)).splitlines():
            label = data2c.LABEL.match(line)
            if label:
                pending.append(label[1])
            row = data2c.ROW.match(line)
            if row:
                for name in pending:
                    result[name] = int(row[2], 16)
                pending = []
    for obj in objects():
        result[obj['name']] = obj['address']
        for name in obj.get('labels', []):
            result[name] = obj['address']
    for path in ('config/main.symbols.txt', 'SCUS_974.90.lcf'):
        for line in (ROOT / path).read_text().splitlines():
            m = re.match(r'^\s*(\w+)\s*=\s*(0x[0-9A-Fa-f]+)\s*;', line)
            if m:
                result[m[1]] = int(m[2], 16)
    import data2c_symbols
    current = {}
    for line in (ROOT / 'config/main.symbols.txt').read_text().splitlines():
        m = data2c.SYMBOL.match(line)
        if m:
            current[int(m[2], 16)] = m[1]
    result.update(data2c_symbols.verify_entries(cfg, current, ROOT))
    result.update(data2c_symbols.external_addresses(cfg, ROOT))
    return result


def prepare(out, arming_address=None):
    """Check actual compiled bytes/relocations, then set measured placement.

    The compiler owns values; postprocessing only changes section placement,
    materializes C zero initializers, and lowers alignment for the retail slot.
    A mismatch is never repaired using reference bytes.
    """
    directory = ROOT / 'build/data2c-obj'
    stamp = directory / '.built-by'
    if not stamp.exists() or stamp.read_text() != 'host':
        raise ValueError('data candidates need a successful remote build')
    symbols = addresses()
    hashes = json.loads((directory / 'source-hashes.json').read_text())
    retail = (__import__('rgd').RETAIL_DIR / 'SCUS_974.90').read_bytes()
    checked = materialized = lowered = 0
    for obj in objects():
        source = ROOT / obj['source']
        if hashes.get(obj['source']) != hashlib.sha256(source.read_bytes()).hexdigest():
            raise ValueError('stale data object: ' + obj['source'])
        path = directory / obj['object']
        elf = ELF(path)
        names = [s for s in elf.symbols if s['name'] == obj['name'] and s['bind'] == 1]
        if len(names) != 1:
            raise ValueError('expected one global definition: ' + obj['name'])
        sym = names[0]
        d = bytearray(elf.data)
        shoff = struct.unpack_from('<I', d, 32)[0]
        es, count, sx = struct.unpack_from('<HHH', d, 46)
        headers = [list(struct.unpack_from('<10I', d, shoff+i*es)) for i in range(count)]
        section = sym['section']
        if section == 0xfff2:  # a genuine C COMMON zero definition
            if (obj['section'] != '.bss' and not obj.get('reservation')) or sym['size'] != obj['size']:
                raise ValueError('unexpected COMMON initialized object')
            section = len(headers)
            headers.append([0, 8, 3, 0, 0, obj['size'], 0, 0, 1, 0])
            sec = next(s for s in elf.sections if s['type'] == 2)
            index = elf.symbols.index(sym)
            struct.pack_into('<I', d, sec['offset'] + index*16 + 4, 0)
            struct.pack_into('<H', d, sec['offset'] + index*16 + 14, section)
            actual = b'\0' * obj['size']
        else:
            if sym['value'] != 0 or not 0 < section < len(headers):
                raise ValueError('data symbol is not a whole input section: ' + obj['name'])
            if headers[section][5] != obj['size']:
                raise ValueError('wrong data section size: ' + obj['name'])
            actual = elf.relocated(section, obj['address'], symbols)
        if obj['section'] == '.bss' or obj.get('reservation'):
            if any(actual):
                raise ValueError('nonzero bss data')
        else:
            offset = obj['address'] - 0xffe80
            expected = retail[offset:offset+obj['size']]
            if actual != expected and not (arming_address is not None and obj['address'] <= arming_address < obj['address']+obj['size']):
                raise ValueError('compiled data differs from retail: ' + obj['name'])
        # Every allocated data section must be accounted for.
        for i, header in enumerate(headers):
            if header[2] & 2 and header[5] and i != section:
                raise ValueError('unexpected extra allocated data section: ' + obj['name'])
        want = headers[section]
        if obj['section'] == '.bss' or obj.get('reservation'):
            want[1], want[2] = 8, 3
        else:
            if want[1] == 8:
                while len(d) % 4:
                    d.append(0)
                want[4] = len(d)
                d += b'\0' * want[5]  # materialize only compiler-proven zeros
                materialized += 1
            want[1], want[2] = 1, 2 if obj['section'] == '.rodata' else 3
        alignment = 16
        while obj['address'] % alignment:
            alignment //= 2
        if want[8] > alignment:
            lowered += 1
        want[8] = min(want[8] or 1, alignment)
        original_strings = elf.section_bytes(sx)
        new_strings = original_strings + obj['section'].encode() + b'\0'
        want[0] = len(original_strings)
        headers[sx][4], headers[sx][5] = len(d), len(new_strings)
        d += new_strings
        # Empty default sections are not admitted by mwld.
        for i, header in enumerate(headers):
            if i and i != section and header[2] & 2 and not header[5]:
                headers[i] = [0] * 10
        while len(d) % 4:
            d.append(0)
        struct.pack_into('<I', d, 32, len(d))
        struct.pack_into('<H', d, 48, len(headers))
        d += b''.join(struct.pack('<10I', *h) for h in headers)
        (out / obj['object']).write_bytes(d)
        checked += 1
    print('Compiled-byte preflight: %d objects; %d compiler-zero sections materialized; %d alignments lowered.' %
          (checked, materialized, lowered))


def text_slots():
    return [(o['object'][:-2], o['address'], o['size'], o['last_address']) for o in objects()
            if o['address'] < 0x46f9c0]


def placements():
    return {o['object'][:-2]: o['section'] for o in objects()}


def external_assignments(body):
    """MAIN imports overlay addresses; their code lives in separate images."""
    import data2c_symbols
    cfg = json.loads((ROOT / 'config/data2c.json').read_text())
    values = data2c_symbols.external_addresses(cfg, ROOT)
    existing = set(re.findall(r'^\s*(\w+)\s*=', body, re.M))
    lines = ['        %s = 0x%08X;' % (name, address)
             for name, address in sorted(values.items())
             if cfg['external_symbols'][name]['domain'] != 'main_assembly' and name not in existing]
    if lines:
        anchor = '        D_0044B778 = 0x0044B778;'
        if body.count(anchor) != 1:
            raise ValueError('external pointer assignment anchor missing')
        body = body.replace(anchor, '        // MAIN imports from separately loaded overlays and their shared arena.\n' + '\n'.join(lines) + '\n' + anchor)
    return body


def tail():
    return [(o['object'], o['section']) for o in objects() if o['address'] >= 0x46f9c0 and not o.get('reservation')]


def reservations():
    return [(o['object'], o['section']) for o in objects() if o.get('reservation')]
