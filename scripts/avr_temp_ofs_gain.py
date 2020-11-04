
# add calibation points (temperature, ADC reading) to the list calibration_points

def getT(LSB, g, o):
    return (((LSB - (273 + 100 - o)) * 128) / g) + 25

# typical values
# Atmega328P
# calibration_points = [(-40, 0x010D), (25, 0x0160), (125, 0x01E0)]
# Atmega328PB
#calibration_points = [(-40, 205), (25, 270), (105, 350)]

# two point calibration
calibration_points = [(-40, 269), (125, 480)]

sdl = []
for o in range(0, 255):
    for g in range(1, 255):
        sd = 0
        ll = []
        llstr = []
        diff = 0
        for (T, LSB) in calibration_points:
            t = getT(LSB, g, o)
            diff += abs(T - t)
            ll.append(t)
            llstr.append('%d=%.2f' % (T, t))
        sdl.append((diff, 'gain=%u ofs=%u (%s)' % (g, o, ' '.join(llstr))))

sdl.sort()

for s in sdl[0:10]:
    print('%s diff=%.2f' % (s[1], s[0]))
