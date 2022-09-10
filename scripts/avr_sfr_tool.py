#
#  Author: sascha_lammers@gmx.de
#

import argparse
import sys
import libs.avr_mapping

parser = argparse.ArgumentParser(description='Firmware Configuration Tool', formatter_class=argparse.RawTextHelpFormatter)
parser.add_argument('-m', '--mcu', help='MCU name', default='atmega328p')
parser.add_argument('--output', help='output file', type=str, default='-')
parser.add_argument('--pins', help='output pins', type=int, default=[], nargs='+', required=True)
parser.add_argument('--zc-pin', help='zero crossing pin', type=int, required=True)

args = parser.parse_args()
mcu = libs.avr_mapping.AvrPinMapping(args.mcu)

if args.output=='-':
    file = sys.stdout
else:
    file = open(args.output, 'w')

def fprint(msg = ''):
    file.write(str(msg) + '\n')

all = []
mask = {}
channels = args.pins

for pin in channels:
    bit = mcu.get_bit(pin)
    bit_value = mcu.get_bv(pin)
    port = mcu.get_port(pin)
    all.append((port, {'bv': bit_value, 'pins': [(pin, bit, 'pin=%u mask=b%s/0x%02x' % (bit, format(bit_value, '08b'), bit_value))]}))
    if port not in mask:
        mask[port] = 0
    mask[port] |= bit_value


num = len(all)
set_bit = []
clr_bit = []
enable = []
disable = []
write = []
n = 0
comment = [
    'zero crossing pin=%s mask=0x%02x/b%s' % (mcu.get_pin(args.zc_pin), mcu.get_bv(args.zc_pin), format(mcu.get_bv(args.zc_pin), '08b'))
]
channel_data = []
for port, val in all:
    for (pin, bit, pin_val) in val['pins']:
        comment.append('port=%s mask=0x%02x %s' % (port, val['bv'], pin_val))
        channel_data.append({'port': port, 'pin': pin, 'bv': val['bv'], 'bit': bit})
    enable.append("(%s | 0x%02x)" % (port, mask[port]))
    disable.append("(%s & ~0x%02x)" % (port, mask[port]))
    set_bit.append("(%s | mask[%u])" % (port, n))
    clr_bit.append("(%s & ~mask[%u])" % (port, n))
    write.append("%s = tmp[%u]" % (port, n))
    n += 1

fprint('// AUTO GENERATED FILE - DO NOT MODIFY')
fprint('// MCU: %s' % mcu.get_mcu_name())
fprint('// %s' % '\n// '.join(comment))
fprint()
fprint('#pragma once')
fprint('#include <avr/io.h>')
fprint()
fprint('#define DIMMER_SFR_ZC_STATE (%s & 0x%02x)' % (mcu.get_pin(args.zc_pin), mcu.get_bv(args.zc_pin)))
fprint('#define DIMMER_SFR_ZC_IS_SET asm volatile ("sbis %%0, %%1" :: "I" ( _SFR_IO_ADDR(%s)), "I" (%u));' % (mcu.get_pin(args.zc_pin), mcu.get_bit(args.zc_pin)))
fprint('#define DIMMER_SFR_ZC_IS_CLR asm volatile ("sbic %%0, %%1" :: "I" ( _SFR_IO_ADDR(%s)), "I" (%u));' % (mcu.get_pin(args.zc_pin), mcu.get_bit(args.zc_pin)))
fprint('#define DIMMER_SFR_ZC_JMP_IF_SET(label) DIMMER_SFR_ZC_IS_CLR asm volatile("rjmp " # label);');
fprint('#define DIMMER_SFR_ZC_JMP_IF_CLR(label) DIMMER_SFR_ZC_IS_SET asm volatile("rjmp " # label);');
fprint()
fprint('// all ports are read first, modified and written back to minimize the delay between toggling different ports (3 cycles, 187.5ns per port @16MHz)')
fprint()
if num==1:
    fprint("#define DIMMER_SFR_ENABLE_ALL_CHANNELS() { %s; }" % (''.join(enable).replace('|', '|=').strip('()')))
    fprint("#define DIMMER_SFR_DISABLE_ALL_CHANNELS() { %s; }" % (''.join(disable).replace('&', '&=').strip('()')))
    fprint("#define DIMMER_SFR_CHANNELS_SET_BITS(mask) { %s; }" % (''.join(set_bit).replace('|', '|=').replace('[0]', '').strip('()')))
    fprint("#define DIMMER_SFR_CHANNELS_CLR_BITS(mask) { %s; }" % (''.join(clr_bit).replace('&', '&=').replace('[0]', '').strip('()')))
else:
    fprint("#define DIMMER_SFR_ENABLE_ALL_CHANNELS() { uint8_t tmp[%u] = { (uint8_t)%s }; %s; }" % (num, ', (uint8_t)'.join(enable), '; '.join(write)))
    fprint("#define DIMMER_SFR_DISABLE_ALL_CHANNELS() { uint8_t tmp[%u] = { (uint8_t)%s }; %s; }" % (num, ', (uint8_t)'.join(disable), '; '.join(write)))
    fprint("#define DIMMER_SFR_CHANNELS_SET_BITS(mask) { uint8_t tmp[%u] = { (uint8_t)%s }; %s; }" % (num, ', (uint8_t)'.join(set_bit), '; '.join(write)))
    fprint("#define DIMMER_SFR_CHANNELS_CLR_BITS(mask) { uint8_t tmp[%u] = { (uint8_t)%s }; %s; }" % (num, ', (uint8_t)'.join(clr_bit), '; '.join(write)))


fprint()

def create_switch(name, opcode, list):
    n = 0
    cases = []
    for val in list:
        case = n and ('case %u' % n) or 'default'
        cases.append('%s: asm volatile ("%s %%0, %%1" :: "I" ( _SFR_IO_ADDR(%s)), "I" (%u))' % (case, opcode, val['port'], val['bit']))
        n += 1

    if len(list)>1:
        fprint('#define DIMMER_SFR_CHANNELS_%s(channel) switch(channel) { %s; }' % (name, '; break; '.join(cases)))
    else:
        fprint('#define DIMMER_SFR_CHANNELS_%s(channel) %s' % (name, '; '.join(cases).replace('default: ', '')))


create_switch('ENABLE', 'sbi', channel_data)
create_switch('DISABLE', 'cbi', channel_data)

signature = mcu.get_signature()
full_signature = list(signature)
full_signature += channels
full_signature = map(lambda n: ('0x%02x' % n), full_signature)

fprint()
fprint("// verify signature during compilation")
fprint("static constexpr uint8_t kInlineAssemblerSignature[] = { %s }; // MCU %s (%02x-%02x-%02x)" % (', '.join(full_signature), mcu.get_mcu_name(), signature[0], signature[1], signature[2]))
fprint()


if file != sys.stdout:
    file.close()
    print("Created %s..." % args.output)
