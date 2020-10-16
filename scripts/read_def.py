#
#  Author: sascha_lammers@gmx.de
#

#
# ceate constants of the defines used in dimmer_protocol.h
#

import re
import sys
import os

filename = './src/dimmer_protocol.h'
outfile1 = './src/dimmer_protocol_constexpr.h'
outfile2 = './scripts/print_def.h'

with open(outfile1, 'w', newline='\n') as ofh1:
    with open(outfile2, 'w', newline='\n') as ofh2:
        ofh1.write('// translates defines into constexpr to read the values with intellisense\n');
        ofh1.write('#include <stddef.h>\n');
        ofh1.write('#include <stdint.h>\n');
        ofh1.write('#include "dimmer_def.h"\n');
        ofh1.write('#include "dimmer_protocol.h"\n');
        ofh1.write('#include "dimmer_reg_mem.h"\n');
        with open(filename, 'r') as ifh:
            for line in ifh.read().split('\n'):
                line = line.strip()
                m = re.match('^#define\s+([^\s]*)', line)
                if m:
                    ofh1.write('static constexpr size_t __%s = %s;\n' % (m[1],  m[1]))
                    ofh2.write('Serial.print(F("#define %-40.40s ")); Serial.printf("0x%%02x\\n", (uint8_t)%s);\n' % (m[1],  m[1]))


