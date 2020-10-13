
import re
import sys
import os


filename = './src/dimmer_protocol.h'
outfile = './src/dimmer_protocol_constexpr.h'
# outfile = './scripts/def.h'

with open(outfile, 'w', newline='\n') as ofh:
    ofh.write('// translates defines into constexpr to read the values with intellisense\n');
    ofh.write('#include <stddef.h>\n');
    ofh.write('#include <stdint.h>\n');
    ofh.write('#include "dimmer_def.h"\n');
    ofh.write('#include "dimmer_protocol.h"\n');
    ofh.write('#include "dimmer_reg_mem.h"\n');
    with open(filename, 'r') as ifh:
        for line in ifh.read().split('\n'):
            line = line.strip()
            m = re.match('^#define\s+([^\s]*)', line)
            if m:
                # ofh.write('Serial.print(F("#define %-40.40s ")); Serial.printf("0x%%02x\\n", %s);\n' % (m[1],  m[1]))
                ofh.write('static constexpr size_t __%s = %s;\n' % (m[1],  m[1]))


