#
#  Author: sascha_lammers@gmx.de
#

from libs.avr_mapping_helper import (ra as ra, bv as bv, dc as dc, me as me, pf as pf)

class Mapping(object):

    name = 'ATmega328P'
    signature = (0x1e, 0x95, 0x0f)
    pins = dc(ra(0, 19))
    digital_pins = dc(ra(0, 13))
    analog_pins = dc(ra(14, 19), pf('A%u', ra(0, 5)))
    pin_to_PORT = me(
        dc(ra(0, 7), 'PORTD'),
        dc(ra(8, 13), 'PORTB'),
        dc(ra(14, 19), 'PORTC')
    )
    pin_to_PIN = me(
        dc(ra(0, 7), 'PIND'),
        dc(ra(8, 13), 'PINB'),
        dc(ra(14, 19), 'PINC')
    )
    pin_to_DDR = me(
        dc(ra(0, 7), 'DDRD'),
        dc(ra(8, 13), 'DDRB'),
        dc(ra(14, 19), 'DDRC')
    )
    pin_to_BIT = me(
        dc(ra(0, 7), dc(ra(0, 7), bv(ra(0, 7)))),
        dc(ra(8, 13), dc(ra(0, 5), bv(ra(0, 5)))),
        dc(ra(14, 19), dc(ra(0, 5), bv(ra(0, 5))))
    )
    timers = {
        0: (16, ()),
        1: (16, (('Prescaler',
                  (('TCCR1A', 0),
                   ('TCCR1B', ((0, ('~CS10', '~CS11', '~CS12')), (1, ('CS10')), (8, ('CS11')),
                               (64, ('CS10', 'CS11')), (256, ('CS12')), (1024, ('CS10', 'CS12'))))
                   )
                  ),
                 (('Overflow', (('TIMSK1', 'TOIE1'), ('TIFR1', 'TOV1'), ('TCNT1', ('TCNT1L', 'TCNT1H')), 'TIMER1_OVF_vect')),
                  ('CompareA', (('TIMSK1', 'OCIE1A'), ('TIFR1', 'OCF1A'),
                                ('OCR1A', ('OCR1AL', 'OCR1AH')), 'TIMER1_COMPA_vect')),
                  ('CompareB', (('TIMSK1', 'OCIE1B'), ('TIFR1', 'OCF1B'),
                                ('OCR1B', ('OCR1BL', 'OCR1BH')), 'TIMER1_COMPB_vect')),
                  ('Capture', (('TIMSK1', 'ICIE1'), ('TIFR1', 'ICF1'), ('ICR1', ('ICR1L', 'ICR1H')), 'TIMER1_CAPT_vect', (('Falling', ('TCCR1B', '~ICES1')), ('Rising', ('TCCR1B', 'ICES1'))))))
                 )
            ),
        2: (8, (
            ('Prescaler', (('TCCR2A', 0),
                           ('TCCR2B', ((0, ('~CS20', '~CS21', '~CS22')), (1, ('CS20')), (8, ('CS21')), (32, ('CS20', 'CS21')),
                                       (64, ('CS22')), (128, ('CS20', 'CS22')), (256, ('CS21', 'CS22')), (1024, ('CS20', 'CS21', 'CS22'))))
                           )),
            (
                ('Overflow', (('TIMSK2', 'TOIE2'),
                              ('TIFR2', 'TOV2'), ('TCNT2'), 'TIMER2_OVF_vect')),
                ('CompareA', (('TIMSK2', 'OCIE2A'),
                              ('TIFR2', 'OCF2A'), ('OCR1A'), 'TIMER2_COMPA_vect')),
                ('CompareB', (('TIMSK2', 'OCIE2B'),
                              ('TIFR2', 'OCF2B'), ('OCR1B'), 'TIMER2_COMPB_vect')),
            )
        ))
    }
