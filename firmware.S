
.\.pio\build\atomic_sun2.1\firmware.elf:     file format elf32-avr


Disassembly of section .text:

00000000 <__vectors>:
       0:	0c 94 a4 02 	jmp	0x548	; 0x548 <__dtors_end>
       4:	0c 94 45 10 	jmp	0x208a	; 0x208a <__vector_1>
       8:	0c 94 1e 10 	jmp	0x203c	; 0x203c <__vector_2>
       c:	0c 94 cc 02 	jmp	0x598	; 0x598 <__bad_interrupt>
      10:	0c 94 cc 02 	jmp	0x598	; 0x598 <__bad_interrupt>
      14:	0c 94 cc 02 	jmp	0x598	; 0x598 <__bad_interrupt>
      18:	0c 94 cc 02 	jmp	0x598	; 0x598 <__bad_interrupt>
      1c:	0c 94 cc 02 	jmp	0x598	; 0x598 <__bad_interrupt>
      20:	0c 94 cc 02 	jmp	0x598	; 0x598 <__bad_interrupt>
      24:	0c 94 cc 02 	jmp	0x598	; 0x598 <__bad_interrupt>
      28:	0c 94 cc 02 	jmp	0x598	; 0x598 <__bad_interrupt>
      2c:	0c 94 62 08 	jmp	0x10c4	; 0x10c4 <__vector_11>
      30:	0c 94 01 08 	jmp	0x1002	; 0x1002 <__vector_12>
      34:	0c 94 41 09 	jmp	0x1282	; 0x1282 <__vector_13>
      38:	0c 94 cc 02 	jmp	0x598	; 0x598 <__bad_interrupt>
      3c:	0c 94 cc 02 	jmp	0x598	; 0x598 <__bad_interrupt>
      40:	0c 94 a5 0e 	jmp	0x1d4a	; 0x1d4a <__vector_16>
      44:	0c 94 cc 02 	jmp	0x598	; 0x598 <__bad_interrupt>
      48:	0c 94 63 12 	jmp	0x24c6	; 0x24c6 <__vector_18>
      4c:	0c 94 3d 12 	jmp	0x247a	; 0x247a <__vector_19>
      50:	0c 94 cc 02 	jmp	0x598	; 0x598 <__bad_interrupt>
      54:	0c 94 cc 02 	jmp	0x598	; 0x598 <__bad_interrupt>
      58:	0c 94 cc 02 	jmp	0x598	; 0x598 <__bad_interrupt>
      5c:	0c 94 cc 02 	jmp	0x598	; 0x598 <__bad_interrupt>
      60:	0c 94 cc 02 	jmp	0x598	; 0x598 <__bad_interrupt>
      64:	0c 94 cc 02 	jmp	0x598	; 0x598 <__bad_interrupt>
      68:	08 00       	.word	0x0008	; ????
      6a:	00 00       	nop
      6c:	be 92       	st	-X, r11
      6e:	24 49       	sbci	r18, 0x94	; 148
      70:	12 3e       	cpi	r17, 0xE2	; 226
      72:	ab aa       	std	Y+51, r10	; 0x33
      74:	aa 2a       	or	r10, r26
      76:	be cd       	rjmp	.-1156   	; 0xfffffbf4 <__eeprom_end+0xff7efbf4>
      78:	cc cc       	rjmp	.-1640   	; 0xfffffa12 <__eeprom_end+0xff7efa12>
      7a:	4c 3e       	cpi	r20, 0xEC	; 236
      7c:	00 00       	nop
      7e:	00 80       	ld	r0, Z
      80:	be ab       	std	Y+54, r27	; 0x36
      82:	aa aa       	std	Y+50, r10	; 0x32
      84:	aa 3e       	cpi	r26, 0xEA	; 234
      86:	00 00       	nop
      88:	00 00       	nop
      8a:	bf 00       	.word	0x00bf	; ????
      8c:	00 00       	nop
      8e:	80 3f       	cpi	r24, 0xF0	; 240
      90:	00 00       	nop
      92:	00 00       	nop
      94:	00 08       	sbc	r0, r0
      96:	41 78       	andi	r20, 0x81	; 129
      98:	d3 bb       	out	0x13, r29	; 19
      9a:	43 87       	std	Z+11, r20	; 0x0b
      9c:	d1 13       	cpse	r29, r17
      9e:	3d 19       	sub	r19, r13
      a0:	0e 3c       	cpi	r16, 0xCE	; 206
      a2:	c3 bd       	out	0x23, r28	; 35
      a4:	42 82       	std	Z+2, r4	; 0x02
      a6:	ad 2b       	or	r26, r29
      a8:	3e 68       	ori	r19, 0x8E	; 142
      aa:	ec 82       	std	Y+4, r14	; 0x04
      ac:	76 be       	out	0x36, r7	; 54
      ae:	d9 8f       	std	Y+25, r29	; 0x19
      b0:	e1 a9       	ldd	r30, Z+49	; 0x31
      b2:	3e 4c       	sbci	r19, 0xCE	; 206
      b4:	80 ef       	ldi	r24, 0xF0	; 240
      b6:	ff be       	out	0x3f, r15	; 63
      b8:	01 c4       	rjmp	.+2050   	; 0x8bc <_ZL27dimmer_zc_interrupt_handlerv.lto_priv.97+0x2ca>
      ba:	ff 7f       	andi	r31, 0xFF	; 255
      bc:	3f 00       	.word	0x003f	; ????
      be:	00 00       	nop
	...

000000c2 <__trampolines_end>:
      c2:	6e 61       	ori	r22, 0x1E	; 30
      c4:	6e 00       	.word	0x006e	; ????

000000c6 <__c.2332>:
      c6:	69 6e 66 00 00 40 7a 10 f3 5a 00 a0 72 4e 18 09     inf..@z..Z..rN..
      d6:	00 10 a5 d4 e8 00 00 e8 76 48 17 00 00 e4 0b 54     ........vH.....T
      e6:	02 00 00 ca 9a 3b 00 00 00 e1 f5 05 00 00 80 96     .....;..........
      f6:	98 00 00 00 40 42 0f 00 00 00 a0 86 01 00 00 00     ....@B..........
     106:	10 27 00 00 00 00 e8 03 00 00 00 00 64 00 00 00     .'..........d...
     116:	00 00 0a 00 00 00 00 00 01 00 00 00 00 00 2c 76     ..............,v
     126:	d8 88 dc 67 4f 08 23 df c1 df ae 59 e1 b1 b7 96     ...gO.#....Y....
     136:	e5 e3 e4 53 c6 3a e6 51 99 76 96 e8 e6 c2 84 26     ...S.:.Q.v.....&
     146:	eb 89 8c 9b 62 ed 40 7c 6f fc ef bc 9c 9f 40 f2     ....b.@|o.....@.
     156:	ba a5 6f a5 f4 90 05 5a 2a f7 5c 93 6b 6c f9 67     ..o....Z*.\.kl.g
     166:	6d c1 1b fc e0 e4 0d 47 fe f5 20 e6 b5 00 d0 ed     m......G.. .....
     176:	90 2e 03 00 94 35 77 05 00 80 84 1e 08 00 00 20     .....5w........ 
     186:	4e 0a 00 00 00 c8 0c 33 33 33 33 0f 98 6e 12 83     N......3333..n..
     196:	11 41 ef 8d 21 14 89 3b e6 55 16 cf fe e6 db 18     .A..!..;.U......
     1a6:	d1 84 4b 38 1b f7 7c 1d 90 1d a4 bb e4 24 20 32     ..K8..|......$ 2
     1b6:	84 72 5e 22 81 00 c9 f1 24 ec a1 e5 3d 27           .r^"....$...='

000001c4 <_ZZ14count_decimalsdhhE3__c>:
     1c4:	25 25 2e 25 75 66 00                                %%.%uf.

000001cb <_ZZ13print_zcdelayvE3__c>:
     1cb:	2b 52 45 4d 3d 7a 63 64 65 6c 61 79 3d 25 64 0a     +REM=zcdelay=%d.
	...

000001dc <_ZZ22_dimmer_i2c_on_receiveiE3__c_1>:
     1dc:	5b 25 30 32 78 5d 3a 20 30 78 25 30 32 78 20 28     [%02x]: 0x%02x (
     1ec:	25 75 29 0a 00                                      %u)..

000001f1 <_ZZ22_dimmer_i2c_on_receiveiE3__c_0>:
     1f1:	25 30 32 58 00                                      %02X.

000001f6 <_ZZ22_dimmer_i2c_on_receiveiE3__c>:
     1f6:	2b 52 45 4d 3d 2b 49 32 43 54 3d 25 30 32 58 25     +REM=+I2CT=%02X%
     206:	30 32 58 00                                         02X.

0000020a <_ZZ13_write_configbE3__c>:
     20a:	2b 52 45 4d 3d 45 45 50 52 4f 4d 57 2c 63 3d 25     +REM=EEPROMW,c=%
     21a:	6c 75 2c 70 3d 25 75 2c 6e 3d 25 6c 75 2c 77 3d     lu,p=%u,n=%lu,w=
     22a:	25 75 2c 63 72 63 3d 25 30 34 78 0a 00              %u,crc=%04x..

00000237 <_ZZ11read_configvE3__c_0>:
     237:	2b 52 45 4d 3d 45 45 50 52 4f 4d 20 43 52 43 20     +REM=EEPROM CRC 
     247:	65 72 72 6f 72 00                                   error.

0000024d <_ZZ11read_configvE3__c>:
     24d:	2b 52 45 4d 3d 45 45 50 52 4f 4d 52 2c 63 3d 25     +REM=EEPROMR,c=%
     25d:	6c 75 2c 70 3d 25 75 2c 6e 3d 25 6c 75 2c 63 72     lu,p=%u,n=%lu,cr
     26d:	63 3d 25 30 34 78 3d 25 30 34 78 0a 00              c=%04x=%04x..

0000027a <_ZZ5setupE3__c_2>:
     27a:	2b 52 45 4d 3d 74 69 6d 65 6f 75 74 00              +REM=timeout.

00000287 <_ZZ5setupE3__c_1>:
     287:	2b 52 45 4d 3d 4d 65 61 73 75 72 69 6e 67 20 66     +REM=Measuring f
     297:	72 65 71 75 65 6e 63 79 00                          requency.

000002a0 <_ZZ5setupE3__c_0>:
     2a0:	2b 52 45 4d 3d 42 4f 4f 54 00                       +REM=BOOT.

000002aa <_ZZ5setupE3__c>:
     2aa:	1e 95 16 00                                         ....

000002ae <_ZZ4loopE3__c_4>:
     2ae:	6c 76 6c 3d 00                                      lvl=.

000002b3 <_ZZ4loopE3__c_3>:
     2b3:	66 72 71 3d 25 2e 33 66 28 25 75 29 2c 00           frq=%.3f(%u),.

000002c1 <_ZZ4loopE3__c_2>:
     2c1:	56 43 43 3d 25 75 2c 00                             VCC=%u,.

000002c9 <_ZZ4loopE3__c_1>:
     2c9:	69 6e 74 2e 74 65 6d 70 3d 25 2e 33 66 2c 00        int.temp=%.3f,.

000002d8 <_ZZ4loopE3__c_0>:
     2d8:	4e 54 43 3d 25 2e 33 66 2c 00                       NTC=%.3f,.

000002e2 <_ZZ4loopE3__c>:
     2e2:	2b 52 45 4d 3d 00                                   +REM=.

000002e8 <port_to_mode_PGM>:
     2e8:	00 00 00 00 24 00 27 00 2a 00                       ....$.'.*.

000002f2 <_ZZ3remvE3__c>:
     2f2:	2b 52 45 4d 3d 00                                   +REM=.

000002f8 <_ZZ12get_mcu_typeR9MCUInfo_tE3__c_0>:
     2f8:	41 54 6d 65 67 61 33 32 38 50 42 00                 ATmega328PB.

00000304 <_ZZ12get_mcu_typeR9MCUInfo_tE3__c>:
     304:	41 54 6d 65 67 61 33 32 38 50 00                    ATmega328P.

0000030f <_ZZ19display_dimmer_infovE3__c_20>:
     30f:	65 72 72 6f 72 73 3d 5a 43 6d 69 73 66 69 72 65     errors=ZCmisfire
     31f:	3d 25 75 2c 74 65 6d 70 3d 25 75 2c 45 45 50 52     =%u,temp=%u,EEPR
     32f:	4f 4d 43 72 63 3d 25 75 0a 00                       OMCrc=%u..

00000339 <_ZZ19display_dimmer_infovE3__c_19>:
     339:	5a 43 3d 25 64 2f 25 2e 31 66 75 73 0a 00           ZC=%d/%.1fus..

00000347 <_ZZ19display_dimmer_infovE3__c_18>:
     347:	4d 69 6e 2f 4d 61 78 4f 6e 3d 25 75 2f 25 2e 31     Min/MaxOn=%u/%.1
     357:	66 75 73 2c 25 75 2f 25 2e 31 66 75 73 2c 00        fus,%u/%.1fus,.

00000366 <_ZZ19display_dimmer_infovE3__c_17>:
     366:	56 43 43 3d 25 2e 33 66 2c 00                       VCC=%.3f,.

00000370 <_ZZ19display_dimmer_infovE3__c_16>:
     370:	4d 61 78 54 6d 70 3d 25 75 2f 25 75 73 2c 4d 65     MaxTmp=%u/%us,Me
     380:	74 72 69 63 73 3d 25 75 73 2c 00                    trics=%us,.

0000038b <_ZZ19display_dimmer_infovE3__c_15>:
     38b:	49 6e 74 54 65 6d 70 3d 25 2e 32 66 2f 25 2b 2e     IntTemp=%.2f/%+.
     39b:	31 66 43 2c 00                                      1fC,.

000003a0 <_ZZ19display_dimmer_infovE3__c_14>:
     3a0:	4e 54 43 3d 25 2e 32 66 2f 25 2b 2e 31 66 43 2c     NTC=%.2f/%+.1fC,
	...

000003b1 <_ZZ19display_dimmer_infovE3__c_13>:
     3b1:	52 65 73 74 6f 72 65 3d 25 75 2c 46 72 71 3d 25     Restore=%u,Frq=%
     3c1:	2e 33 66 2c 52 65 66 31 31 3d 00                    .3f,Ref11=.

000003cc <_ZZ19display_dimmer_infovE3__c_12>:
     3cc:	76 61 6c 75 65 73 3d 00                             values=.

000003d4 <_ZZ19display_dimmer_infovE3__c_11>:
     3d4:	75 73 2c 4d 61 78 4c 76 6c 73 3d 38 31 39 32 2c     us,MaxLvls=8192,
     3e4:	47 50 49 4f 2f 6c 76 6c 3d 00                       GPIO/lvl=.

000003ee <_ZZ19display_dimmer_infovE3__c_10>:
     3ee:	2c 50 72 65 3d 38 2c 54 69 63 6b 73 3d 00           ,Pre=8,Ticks=.

000003fc <_ZZ19display_dimmer_infovE3__c_9>:
     3fc:	41 64 64 72 3d 25 30 32 78 00                       Addr=%02x.

00000406 <_ZZ19display_dimmer_infovE3__c_8>:
     406:	43 45 3d 31 2c 00                                   CE=1,.

0000040c <_ZZ19display_dimmer_infovE3__c_7>:
     40c:	50 72 3d 55 41 52 54 2c 00                          Pr=UART,.

00000415 <_ZZ19display_dimmer_infovE3__c_6>:
     415:	49 6e 74 54 65 6d 70 2c 56 43 43 2c 00              IntTemp,VCC,.

00000422 <_ZZ19display_dimmer_infovE3__c_5>:
     422:	4e 54 43 3d 41 30 2c 00                             NTC=A0,.

0000042a <_ZZ19display_dimmer_infovE3__c_4>:
     42a:	45 45 50 52 4f 4d 77 72 3d 25 6c 75 2c 00           EEPROMwr=%lu,.

00000438 <_ZZ19display_dimmer_infovE3__c_3>:
     438:	6f 70 74 69 6f 6e 73 3d 00                          options=.

00000441 <_ZZ19display_dimmer_infovE3__c_2>:
     441:	40 25 75 4d 68 7a 0a 00                             @%uMhz..

00000449 <_ZZ19display_dimmer_infovE3__c_1>:
     449:	2c 4d 43 55 3d 25 73 00                             ,MCU=%s.

00000451 <_ZZ19display_dimmer_infovE3__c_0>:
     451:	73 69 67 3d 25 30 32 78 2d 25 30 32 78 2d 25 30     sig=%02x-%02x-%0
     461:	32 78 2c 66 75 73 65 73 3d 6c 3a 25 30 32 78 2c     2x,fuses=l:%02x,
     471:	68 3a 25 30 32 78 2c 65 3a 25 30 32 78 00           h:%02x,e:%02x.

0000047f <_ZZ19display_dimmer_infovE3__c>:
     47f:	4d 4f 53 46 45 54 20 44 69 6d 6d 65 72 20 33 2e     MOSFET Dimmer 3.
     48f:	30 2e 30 20 4a 75 6e 20 31 38 20 32 30 32 30 20     0.0 Jun 18 2020 
     49f:	30 30 3a 32 31 3a 34 35 20 41 75 74 68 6f 72 20     00:21:45 Author 
     4af:	73 61 73 63 68 61 5f 6c 61 6d 6d 65 72 73 40 67     sascha_lammers@g
     4bf:	6d 78 2e 64 65 00                                   mx.de.

000004c5 <_ZL16_i2c_request_cmd>:
     4c5:	2b 49 32 43 52 3d 00                                +I2CR=.

000004cc <_ZL17_i2c_transmit_cmd.lto_priv.103>:
     4cc:	2b 49 32 43 54 3d 00                                +I2CT=.

000004d3 <port_to_input_PGM>:
     4d3:	00 00 00 00 23 00 26 00 29 00                       ....#.&.).

000004dd <digital_pin_to_timer_PGM>:
     4dd:	00 00 00 08 00 02 01 00 00 03 04 07 00 00 00 00     ................
     4ed:	00 00 00 00                                         ....

000004f1 <_ZZN6Dimmer18_calculateChannelsEvE3__c>:
     4f1:	64 69 6d 6d 65 72 5f 63 61 6c 63 75 6c 61 74 65     dimmer_calculate
     501:	5f 63 68 61 6e 6e 65 6c 73 5f 6c 6f 63 6b 65 64     _channels_locked
	...

00000512 <port_to_output_PGM>:
     512:	00 00 00 00 25 00 28 00 2b 00                       ....%.(.+.

0000051c <digital_pin_to_port_PGM>:
     51c:	04 04 04 04 04 04 04 04 02 02 02 02 02 02 03 03     ................
     52c:	03 03 03 03                                         ....

00000530 <digital_pin_to_bit_mask_PGM>:
     530:	01 02 04 08 10 20 40 80 01 02 04 08 10 20 01 02     ..... @...... ..
     540:	04 08 10 20                                         ... 

00000544 <__ctors_start>:
     544:	41 21       	and	r20, r1

00000546 <__ctors_end>:
     546:	21 21       	and	r18, r1

00000548 <__dtors_end>:
     548:	11 24       	eor	r1, r1
     54a:	1f be       	out	0x3f, r1	; 63
     54c:	cf ef       	ldi	r28, 0xFF	; 255
     54e:	d8 e0       	ldi	r29, 0x08	; 8
     550:	de bf       	out	0x3e, r29	; 62
     552:	cd bf       	out	0x3d, r28	; 61

00000554 <__do_clear_bss>:
     554:	24 e0       	ldi	r18, 0x04	; 4
     556:	aa e8       	ldi	r26, 0x8A	; 138
     558:	b2 e0       	ldi	r27, 0x02	; 2
     55a:	01 c0       	rjmp	.+2      	; 0x55e <.do_clear_bss_start>

0000055c <.do_clear_bss_loop>:
     55c:	1d 92       	st	X+, r1

0000055e <.do_clear_bss_start>:
     55e:	a2 3a       	cpi	r26, 0xA2	; 162
     560:	b2 07       	cpc	r27, r18
     562:	e1 f7       	brne	.-8      	; 0x55c <.do_clear_bss_loop>

00000564 <__do_copy_data>:
     564:	12 e0       	ldi	r17, 0x02	; 2
     566:	a0 e0       	ldi	r26, 0x00	; 0
     568:	b1 e0       	ldi	r27, 0x01	; 1
     56a:	ee e5       	ldi	r30, 0x5E	; 94
     56c:	fd e5       	ldi	r31, 0x5D	; 93
     56e:	02 c0       	rjmp	.+4      	; 0x574 <__do_copy_data+0x10>
     570:	05 90       	lpm	r0, Z+
     572:	0d 92       	st	X+, r0
     574:	aa 38       	cpi	r26, 0x8A	; 138
     576:	b1 07       	cpc	r27, r17
     578:	d9 f7       	brne	.-10     	; 0x570 <__do_copy_data+0xc>

0000057a <__do_global_ctors>:
     57a:	12 e0       	ldi	r17, 0x02	; 2
     57c:	c3 ea       	ldi	r28, 0xA3	; 163
     57e:	d2 e0       	ldi	r29, 0x02	; 2
     580:	04 c0       	rjmp	.+8      	; 0x58a <__do_global_ctors+0x10>
     582:	21 97       	sbiw	r28, 0x01	; 1
     584:	fe 01       	movw	r30, r28
     586:	0e 94 88 2a 	call	0x5510	; 0x5510 <__tablejump2__>
     58a:	c2 3a       	cpi	r28, 0xA2	; 162
     58c:	d1 07       	cpc	r29, r17
     58e:	c9 f7       	brne	.-14     	; 0x582 <__do_global_ctors+0x8>
     590:	0e 94 ac 1c 	call	0x3958	; 0x3958 <main>
     594:	0c 94 a2 2e 	jmp	0x5d44	; 0x5d44 <__do_global_dtors>

00000598 <__bad_interrupt>:
     598:	0c 94 00 00 	jmp	0	; 0x0 <__vectors>

0000059c <_Z30i2c_slave_set_register_addressiha>:
     59c:	20 91 1b 04 	lds	r18, 0x041B	; 0x80041b <register_mem+0xa>
     5a0:	42 0f       	add	r20, r18
     5a2:	40 93 1b 04 	sts	0x041B, r20	; 0x80041b <register_mem+0xa>
     5a6:	02 97       	sbiw	r24, 0x02	; 2
     5a8:	0c f0       	brlt	.+2      	; 0x5ac <_Z30i2c_slave_set_register_addressiha+0x10>
     5aa:	6b e7       	ldi	r22, 0x7B	; 123
     5ac:	60 93 8b 04 	sts	0x048B, r22	; 0x80048b <register_mem+0x7a>
     5b0:	08 95       	ret

000005b2 <_Z22_dimmer_i2c_on_requestv>:
     5b2:	cf 93       	push	r28
     5b4:	df 93       	push	r29
     5b6:	c0 91 8b 04 	lds	r28, 0x048B	; 0x80048b <register_mem+0x7a>
     5ba:	d0 e0       	ldi	r29, 0x00	; 0
     5bc:	c0 5f       	subi	r28, 0xF0	; 240
     5be:	db 4f       	sbci	r29, 0xFB	; 251
     5c0:	80 91 1b 04 	lds	r24, 0x041B	; 0x80041b <register_mem+0xa>
     5c4:	9f ef       	ldi	r25, 0xFF	; 255
     5c6:	98 0f       	add	r25, r24
     5c8:	90 93 1b 04 	sts	0x041B, r25	; 0x80041b <register_mem+0xa>
     5cc:	88 23       	and	r24, r24
     5ce:	61 f0       	breq	.+24     	; 0x5e8 <_Z22_dimmer_i2c_on_requestv+0x36>
     5d0:	fe 01       	movw	r30, r28
     5d2:	84 e0       	ldi	r24, 0x04	; 4
     5d4:	cc 38       	cpi	r28, 0x8C	; 140
     5d6:	d8 07       	cpc	r29, r24
     5d8:	38 f4       	brcc	.+14     	; 0x5e8 <_Z22_dimmer_i2c_on_requestv+0x36>
     5da:	21 96       	adiw	r28, 0x01	; 1
     5dc:	60 81       	ld	r22, Z
     5de:	86 e4       	ldi	r24, 0x46	; 70
     5e0:	93 e0       	ldi	r25, 0x03	; 3
     5e2:	0e 94 a5 11 	call	0x234a	; 0x234a <_ZN13SerialTwoWire5writeEh>
     5e6:	ec cf       	rjmp	.-40     	; 0x5c0 <_Z22_dimmer_i2c_on_requestv+0xe>
     5e8:	10 92 1b 04 	sts	0x041B, r1	; 0x80041b <register_mem+0xa>
     5ec:	df 91       	pop	r29
     5ee:	cf 91       	pop	r28
     5f0:	08 95       	ret

000005f2 <_ZL27dimmer_zc_interrupt_handlerv.lto_priv.97>:
     5f2:	8f 92       	push	r8
     5f4:	9f 92       	push	r9
     5f6:	af 92       	push	r10
     5f8:	bf 92       	push	r11
     5fa:	cf 92       	push	r12
     5fc:	df 92       	push	r13
     5fe:	ef 92       	push	r14
     600:	ff 92       	push	r15
     602:	0f 93       	push	r16
     604:	1f 93       	push	r17
     606:	cf 93       	push	r28
     608:	df 93       	push	r29
     60a:	c0 91 84 00 	lds	r28, 0x0084	; 0x800084 <__TEXT_REGION_LENGTH__+0x7e0084>
     60e:	d0 91 85 00 	lds	r29, 0x0085	; 0x800085 <__TEXT_REGION_LENGTH__+0x7e0085>
     612:	80 91 0c 04 	lds	r24, 0x040C	; 0x80040c <dimmer+0x80>
     616:	81 ff       	sbrs	r24, 1
     618:	18 c0       	rjmp	.+48     	; 0x64a <_ZL27dimmer_zc_interrupt_handlerv.lto_priv.97+0x58>
     61a:	80 91 8a 02 	lds	r24, 0x028A	; 0x80028a <__data_end>
     61e:	8f 5f       	subi	r24, 0xFF	; 255
     620:	80 93 8a 02 	sts	0x028A, r24	; 0x80028a <__data_end>
     624:	89 3c       	cpi	r24, 0xC9	; 201
     626:	08 f4       	brcc	.+2      	; 0x62a <_ZL27dimmer_zc_interrupt_handlerv.lto_priv.97+0x38>
     628:	f1 c1       	rjmp	.+994    	; 0xa0c <__stack+0x10d>
     62a:	8a e5       	ldi	r24, 0x5A	; 90
     62c:	91 e0       	ldi	r25, 0x01	; 1
     62e:	df 91       	pop	r29
     630:	cf 91       	pop	r28
     632:	1f 91       	pop	r17
     634:	0f 91       	pop	r16
     636:	ff 90       	pop	r15
     638:	ef 90       	pop	r14
     63a:	df 90       	pop	r13
     63c:	cf 90       	pop	r12
     63e:	bf 90       	pop	r11
     640:	af 90       	pop	r10
     642:	9f 90       	pop	r9
     644:	8f 90       	pop	r8
     646:	0c 94 34 19 	jmp	0x3268	; 0x3268 <_ZN6Dimmer6_faultEPKc.constprop.59>
     64a:	10 92 8a 02 	sts	0x028A, r1	; 0x80028a <__data_end>
     64e:	0e 94 3a 0e 	call	0x1c74	; 0x1c74 <micros>
     652:	00 91 ff 03 	lds	r16, 0x03FF	; 0x8003ff <dimmer+0x73>
     656:	10 91 00 04 	lds	r17, 0x0400	; 0x800400 <dimmer+0x74>
     65a:	20 91 01 04 	lds	r18, 0x0401	; 0x800401 <dimmer+0x75>
     65e:	30 91 02 04 	lds	r19, 0x0402	; 0x800402 <dimmer+0x76>
     662:	01 2b       	or	r16, r17
     664:	02 2b       	or	r16, r18
     666:	03 2b       	or	r16, r19
     668:	09 f1       	breq	.+66     	; 0x6ac <_ZL27dimmer_zc_interrupt_handlerv.lto_priv.97+0xba>
     66a:	c0 90 ff 03 	lds	r12, 0x03FF	; 0x8003ff <dimmer+0x73>
     66e:	d0 90 00 04 	lds	r13, 0x0400	; 0x800400 <dimmer+0x74>
     672:	e0 90 01 04 	lds	r14, 0x0401	; 0x800401 <dimmer+0x75>
     676:	f0 90 02 04 	lds	r15, 0x0402	; 0x800402 <dimmer+0x76>
     67a:	00 91 03 04 	lds	r16, 0x0403	; 0x800403 <dimmer+0x77>
     67e:	10 91 04 04 	lds	r17, 0x0404	; 0x800404 <dimmer+0x78>
     682:	20 91 05 04 	lds	r18, 0x0405	; 0x800405 <dimmer+0x79>
     686:	30 91 06 04 	lds	r19, 0x0406	; 0x800406 <dimmer+0x7a>
     68a:	46 01       	movw	r8, r12
     68c:	57 01       	movw	r10, r14
     68e:	86 1a       	sub	r8, r22
     690:	97 0a       	sbc	r9, r23
     692:	a8 0a       	sbc	r10, r24
     694:	b9 0a       	sbc	r11, r25
     696:	80 16       	cp	r8, r16
     698:	91 06       	cpc	r9, r17
     69a:	a2 06       	cpc	r10, r18
     69c:	b3 06       	cpc	r11, r19
     69e:	70 f4       	brcc	.+28     	; 0x6bc <_ZL27dimmer_zc_interrupt_handlerv.lto_priv.97+0xca>
     6a0:	80 91 89 04 	lds	r24, 0x0489	; 0x800489 <register_mem+0x78>
     6a4:	8f 5f       	subi	r24, 0xFF	; 255
     6a6:	80 93 89 04 	sts	0x0489, r24	; 0x800489 <register_mem+0x78>
     6aa:	b0 c1       	rjmp	.+864    	; 0xa0c <__stack+0x10d>
     6ac:	60 93 ff 03 	sts	0x03FF, r22	; 0x8003ff <dimmer+0x73>
     6b0:	70 93 00 04 	sts	0x0400, r23	; 0x800400 <dimmer+0x74>
     6b4:	80 93 01 04 	sts	0x0401, r24	; 0x800401 <dimmer+0x75>
     6b8:	90 93 02 04 	sts	0x0402, r25	; 0x800402 <dimmer+0x76>
     6bc:	80 91 0c 04 	lds	r24, 0x040C	; 0x80040c <dimmer+0x80>
     6c0:	82 60       	ori	r24, 0x02	; 2
     6c2:	80 93 0c 04 	sts	0x040C, r24	; 0x80040c <dimmer+0x80>
     6c6:	78 94       	sei
     6c8:	80 91 0b 04 	lds	r24, 0x040B	; 0x80040b <dimmer+0x7f>
     6cc:	81 11       	cpse	r24, r1
     6ce:	81 c0       	rjmp	.+258    	; 0x7d2 <_ZL27dimmer_zc_interrupt_handlerv.lto_priv.97+0x1e0>
     6d0:	80 91 fe 03 	lds	r24, 0x03FE	; 0x8003fe <dimmer+0x72>
     6d4:	81 11       	cpse	r24, r1
     6d6:	18 c0       	rjmp	.+48     	; 0x708 <_ZL27dimmer_zc_interrupt_handlerv.lto_priv.97+0x116>
     6d8:	81 e0       	ldi	r24, 0x01	; 1
     6da:	80 93 fe 03 	sts	0x03FE, r24	; 0x8003fe <dimmer+0x72>
     6de:	f8 94       	cli
     6e0:	ce 01       	movw	r24, r28
     6e2:	a0 e0       	ldi	r26, 0x00	; 0
     6e4:	b0 e0       	ldi	r27, 0x00	; 0
     6e6:	b0 95       	com	r27
     6e8:	a0 95       	com	r26
     6ea:	90 95       	com	r25
     6ec:	81 95       	neg	r24
     6ee:	9f 4f       	sbci	r25, 0xFF	; 255
     6f0:	af 4f       	sbci	r26, 0xFF	; 255
     6f2:	bf 4f       	sbci	r27, 0xFF	; 255
     6f4:	80 93 fa 03 	sts	0x03FA, r24	; 0x8003fa <dimmer+0x6e>
     6f8:	90 93 fb 03 	sts	0x03FB, r25	; 0x8003fb <dimmer+0x6f>
     6fc:	a0 93 fc 03 	sts	0x03FC, r26	; 0x8003fc <dimmer+0x70>
     700:	b0 93 fd 03 	sts	0x03FD, r27	; 0x8003fd <dimmer+0x71>
     704:	78 94       	sei
     706:	5d c0       	rjmp	.+186    	; 0x7c2 <_ZL27dimmer_zc_interrupt_handlerv.lto_priv.97+0x1d0>
     708:	80 91 fe 03 	lds	r24, 0x03FE	; 0x8003fe <dimmer+0x72>
     70c:	8e 31       	cpi	r24, 0x1E	; 30
     70e:	09 f0       	breq	.+2      	; 0x712 <_ZL27dimmer_zc_interrupt_handlerv.lto_priv.97+0x120>
     710:	53 c0       	rjmp	.+166    	; 0x7b8 <_ZL27dimmer_zc_interrupt_handlerv.lto_priv.97+0x1c6>
     712:	f8 94       	cli
     714:	c0 90 fa 03 	lds	r12, 0x03FA	; 0x8003fa <dimmer+0x6e>
     718:	d0 90 fb 03 	lds	r13, 0x03FB	; 0x8003fb <dimmer+0x6f>
     71c:	e0 90 fc 03 	lds	r14, 0x03FC	; 0x8003fc <dimmer+0x70>
     720:	f0 90 fd 03 	lds	r15, 0x03FD	; 0x8003fd <dimmer+0x71>
     724:	ce 01       	movw	r24, r28
     726:	a0 e0       	ldi	r26, 0x00	; 0
     728:	b0 e0       	ldi	r27, 0x00	; 0
     72a:	44 27       	eor	r20, r20
     72c:	55 27       	eor	r21, r21
     72e:	ba 01       	movw	r22, r20
     730:	48 1b       	sub	r20, r24
     732:	59 0b       	sbc	r21, r25
     734:	6a 0b       	sbc	r22, r26
     736:	7b 0b       	sbc	r23, r27
     738:	40 93 fa 03 	sts	0x03FA, r20	; 0x8003fa <dimmer+0x6e>
     73c:	50 93 fb 03 	sts	0x03FB, r21	; 0x8003fb <dimmer+0x6f>
     740:	60 93 fc 03 	sts	0x03FC, r22	; 0x8003fc <dimmer+0x70>
     744:	70 93 fd 03 	sts	0x03FD, r23	; 0x8003fd <dimmer+0x71>
     748:	78 94       	sei
     74a:	20 91 fe 03 	lds	r18, 0x03FE	; 0x8003fe <dimmer+0x72>
     74e:	bc 01       	movw	r22, r24
     750:	cd 01       	movw	r24, r26
     752:	6c 0d       	add	r22, r12
     754:	7d 1d       	adc	r23, r13
     756:	8e 1d       	adc	r24, r14
     758:	9f 1d       	adc	r25, r15
     75a:	30 e0       	ldi	r19, 0x00	; 0
     75c:	40 e0       	ldi	r20, 0x00	; 0
     75e:	50 e0       	ldi	r21, 0x00	; 0
     760:	0e 94 38 2a 	call	0x5470	; 0x5470 <__udivmodsi4>
     764:	30 93 f9 03 	sts	0x03F9, r19	; 0x8003f9 <dimmer+0x6d>
     768:	20 93 f8 03 	sts	0x03F8, r18	; 0x8003f8 <dimmer+0x6c>
     76c:	60 91 f8 03 	lds	r22, 0x03F8	; 0x8003f8 <dimmer+0x6c>
     770:	70 91 f9 03 	lds	r23, 0x03F9	; 0x8003f9 <dimmer+0x6d>
     774:	80 e0       	ldi	r24, 0x00	; 0
     776:	90 e0       	ldi	r25, 0x00	; 0
     778:	0e 94 f3 28 	call	0x51e6	; 0x51e6 <__floatunsisf>
     77c:	60 93 0d 04 	sts	0x040D, r22	; 0x80040d <dimmer+0x81>
     780:	70 93 0e 04 	sts	0x040E, r23	; 0x80040e <dimmer+0x82>
     784:	80 93 0f 04 	sts	0x040F, r24	; 0x80040f <dimmer+0x83>
     788:	90 93 10 04 	sts	0x0410, r25	; 0x800410 <dimmer+0x84>
     78c:	20 91 f8 03 	lds	r18, 0x03F8	; 0x8003f8 <dimmer+0x6c>
     790:	30 91 f9 03 	lds	r19, 0x03F9	; 0x8003f9 <dimmer+0x6d>
     794:	a0 ef       	ldi	r26, 0xF0	; 240
     796:	b2 e0       	ldi	r27, 0x02	; 2
     798:	0e 94 65 2a 	call	0x54ca	; 0x54ca <__umulhisi3>
     79c:	20 e4       	ldi	r18, 0x40	; 64
     79e:	36 e0       	ldi	r19, 0x06	; 6
     7a0:	40 e0       	ldi	r20, 0x00	; 0
     7a2:	50 e0       	ldi	r21, 0x00	; 0
     7a4:	0e 94 38 2a 	call	0x5470	; 0x5470 <__udivmodsi4>
     7a8:	20 93 03 04 	sts	0x0403, r18	; 0x800403 <dimmer+0x77>
     7ac:	30 93 04 04 	sts	0x0404, r19	; 0x800404 <dimmer+0x78>
     7b0:	40 93 05 04 	sts	0x0405, r20	; 0x800405 <dimmer+0x79>
     7b4:	50 93 06 04 	sts	0x0406, r21	; 0x800406 <dimmer+0x7a>
     7b8:	80 91 fe 03 	lds	r24, 0x03FE	; 0x8003fe <dimmer+0x72>
     7bc:	8f 5f       	subi	r24, 0xFF	; 255
     7be:	80 93 fe 03 	sts	0x03FE, r24	; 0x8003fe <dimmer+0x72>
     7c2:	f8 94       	cli
     7c4:	80 91 0c 04 	lds	r24, 0x040C	; 0x80040c <dimmer+0x80>
     7c8:	8d 7f       	andi	r24, 0xFD	; 253
     7ca:	80 93 0c 04 	sts	0x040C, r24	; 0x80040c <dimmer+0x80>
     7ce:	78 94       	sei
     7d0:	1d c1       	rjmp	.+570    	; 0xa0c <__stack+0x10d>
     7d2:	80 91 f8 03 	lds	r24, 0x03F8	; 0x8003f8 <dimmer+0x6c>
     7d6:	90 91 f9 03 	lds	r25, 0x03F9	; 0x8003f9 <dimmer+0x6d>
     7da:	8c 0f       	add	r24, r28
     7dc:	9d 1f       	adc	r25, r29
     7de:	80 54       	subi	r24, 0x40	; 64
     7e0:	91 09       	sbc	r25, r1
     7e2:	20 91 3a 04 	lds	r18, 0x043A	; 0x80043a <register_mem+0x29>
     7e6:	30 91 3b 04 	lds	r19, 0x043B	; 0x80043b <register_mem+0x2a>
     7ea:	82 0f       	add	r24, r18
     7ec:	93 1f       	adc	r25, r19
     7ee:	20 91 0c 04 	lds	r18, 0x040C	; 0x80040c <dimmer+0x80>
     7f2:	f8 94       	cli
     7f4:	20 91 0c 04 	lds	r18, 0x040C	; 0x80040c <dimmer+0x80>
     7f8:	21 60       	ori	r18, 0x01	; 1
     7fa:	20 93 0c 04 	sts	0x040C, r18	; 0x80040c <dimmer+0x80>
     7fe:	90 93 8b 00 	sts	0x008B, r25	; 0x80008b <__TEXT_REGION_LENGTH__+0x7e008b>
     802:	80 93 8a 00 	sts	0x008A, r24	; 0x80008a <__TEXT_REGION_LENGTH__+0x7e008a>
     806:	b2 9a       	sbi	0x16, 2	; 22
     808:	80 91 6f 00 	lds	r24, 0x006F	; 0x80006f <__TEXT_REGION_LENGTH__+0x7e006f>
     80c:	84 60       	ori	r24, 0x04	; 4
     80e:	80 93 6f 00 	sts	0x006F, r24	; 0x80006f <__TEXT_REGION_LENGTH__+0x7e006f>
     812:	78 94       	sei
     814:	f8 94       	cli
     816:	80 91 fa 03 	lds	r24, 0x03FA	; 0x8003fa <dimmer+0x6e>
     81a:	90 91 fb 03 	lds	r25, 0x03FB	; 0x8003fb <dimmer+0x6f>
     81e:	a0 91 fc 03 	lds	r26, 0x03FC	; 0x8003fc <dimmer+0x70>
     822:	b0 91 fd 03 	lds	r27, 0x03FD	; 0x8003fd <dimmer+0x71>
     826:	6e 01       	movw	r12, r28
     828:	e1 2c       	mov	r14, r1
     82a:	f1 2c       	mov	r15, r1
     82c:	44 27       	eor	r20, r20
     82e:	55 27       	eor	r21, r21
     830:	ba 01       	movw	r22, r20
     832:	4c 19       	sub	r20, r12
     834:	5d 09       	sbc	r21, r13
     836:	6e 09       	sbc	r22, r14
     838:	7f 09       	sbc	r23, r15
     83a:	40 93 fa 03 	sts	0x03FA, r20	; 0x8003fa <dimmer+0x6e>
     83e:	50 93 fb 03 	sts	0x03FB, r21	; 0x8003fb <dimmer+0x6f>
     842:	60 93 fc 03 	sts	0x03FC, r22	; 0x8003fc <dimmer+0x70>
     846:	70 93 fd 03 	sts	0x03FD, r23	; 0x8003fd <dimmer+0x71>
     84a:	78 94       	sei
     84c:	c8 0e       	add	r12, r24
     84e:	d9 1e       	adc	r13, r25
     850:	ea 1e       	adc	r14, r26
     852:	fb 1e       	adc	r15, r27
     854:	80 91 f8 03 	lds	r24, 0x03F8	; 0x8003f8 <dimmer+0x6c>
     858:	90 91 f9 03 	lds	r25, 0x03F9	; 0x8003f9 <dimmer+0x6d>
     85c:	64 e1       	ldi	r22, 0x14	; 20
     85e:	70 e0       	ldi	r23, 0x00	; 0
     860:	0e 94 74 2a 	call	0x54e8	; 0x54e8 <__udivmodhi4>
     864:	9b 01       	movw	r18, r22
     866:	40 91 f8 03 	lds	r20, 0x03F8	; 0x8003f8 <dimmer+0x6c>
     86a:	50 91 f9 03 	lds	r21, 0x03F9	; 0x8003f9 <dimmer+0x6d>
     86e:	46 1b       	sub	r20, r22
     870:	57 0b       	sbc	r21, r23
     872:	60 e0       	ldi	r22, 0x00	; 0
     874:	70 e0       	ldi	r23, 0x00	; 0
     876:	4c 15       	cp	r20, r12
     878:	5d 05       	cpc	r21, r13
     87a:	6e 05       	cpc	r22, r14
     87c:	7f 05       	cpc	r23, r15
     87e:	08 f0       	brcs	.+2      	; 0x882 <_ZL27dimmer_zc_interrupt_handlerv.lto_priv.97+0x290>
     880:	56 c0       	rjmp	.+172    	; 0x92e <__stack+0x2f>
     882:	80 91 f8 03 	lds	r24, 0x03F8	; 0x8003f8 <dimmer+0x6c>
     886:	90 91 f9 03 	lds	r25, 0x03F9	; 0x8003f9 <dimmer+0x6d>
     88a:	82 0f       	add	r24, r18
     88c:	93 1f       	adc	r25, r19
     88e:	a0 e0       	ldi	r26, 0x00	; 0
     890:	b0 e0       	ldi	r27, 0x00	; 0
     892:	c8 16       	cp	r12, r24
     894:	d9 06       	cpc	r13, r25
     896:	ea 06       	cpc	r14, r26
     898:	fb 06       	cpc	r15, r27
     89a:	08 f0       	brcs	.+2      	; 0x89e <_ZL27dimmer_zc_interrupt_handlerv.lto_priv.97+0x2ac>
     89c:	48 c0       	rjmp	.+144    	; 0x92e <__stack+0x2f>
     89e:	60 91 0d 04 	lds	r22, 0x040D	; 0x80040d <dimmer+0x81>
     8a2:	70 91 0e 04 	lds	r23, 0x040E	; 0x80040e <dimmer+0x82>
     8a6:	80 91 0f 04 	lds	r24, 0x040F	; 0x80040f <dimmer+0x83>
     8aa:	90 91 10 04 	lds	r25, 0x0410	; 0x800410 <dimmer+0x84>
     8ae:	20 e0       	ldi	r18, 0x00	; 0
     8b0:	30 e0       	ldi	r19, 0x00	; 0
     8b2:	40 e7       	ldi	r20, 0x70	; 112
     8b4:	53 e4       	ldi	r21, 0x43	; 67
     8b6:	0e 94 54 29 	call	0x52a8	; 0x52a8 <__mulsf3>
     8ba:	4b 01       	movw	r8, r22
     8bc:	5c 01       	movw	r10, r24
     8be:	c7 01       	movw	r24, r14
     8c0:	b6 01       	movw	r22, r12
     8c2:	0e 94 f3 28 	call	0x51e6	; 0x51e6 <__floatunsisf>
     8c6:	9b 01       	movw	r18, r22
     8c8:	ac 01       	movw	r20, r24
     8ca:	c5 01       	movw	r24, r10
     8cc:	b4 01       	movw	r22, r8
     8ce:	0e 94 8f 2a 	call	0x551e	; 0x551e <__addsf3>
     8d2:	20 e0       	ldi	r18, 0x00	; 0
     8d4:	30 e0       	ldi	r19, 0x00	; 0
     8d6:	41 e7       	ldi	r20, 0x71	; 113
     8d8:	53 e4       	ldi	r21, 0x43	; 67
     8da:	0e 94 fb 2a 	call	0x55f6	; 0x55f6 <__divsf3>
     8de:	60 93 0d 04 	sts	0x040D, r22	; 0x80040d <dimmer+0x81>
     8e2:	70 93 0e 04 	sts	0x040E, r23	; 0x80040e <dimmer+0x82>
     8e6:	80 93 0f 04 	sts	0x040F, r24	; 0x80040f <dimmer+0x83>
     8ea:	90 93 10 04 	sts	0x0410, r25	; 0x800410 <dimmer+0x84>
     8ee:	60 91 0d 04 	lds	r22, 0x040D	; 0x80040d <dimmer+0x81>
     8f2:	70 91 0e 04 	lds	r23, 0x040E	; 0x80040e <dimmer+0x82>
     8f6:	80 91 0f 04 	lds	r24, 0x040F	; 0x80040f <dimmer+0x83>
     8fa:	90 91 10 04 	lds	r25, 0x0410	; 0x800410 <dimmer+0x84>
     8fe:	c0 91 f8 03 	lds	r28, 0x03F8	; 0x8003f8 <dimmer+0x6c>
     902:	d0 91 f9 03 	lds	r29, 0x03F9	; 0x8003f9 <dimmer+0x6d>
     906:	0e 94 74 2b 	call	0x56e8	; 0x56e8 <__fixunssfsi>
     90a:	c6 17       	cp	r28, r22
     90c:	d7 07       	cpc	r29, r23
     90e:	79 f0       	breq	.+30     	; 0x92e <__stack+0x2f>
     910:	f8 94       	cli
     912:	60 91 0d 04 	lds	r22, 0x040D	; 0x80040d <dimmer+0x81>
     916:	70 91 0e 04 	lds	r23, 0x040E	; 0x80040e <dimmer+0x82>
     91a:	80 91 0f 04 	lds	r24, 0x040F	; 0x80040f <dimmer+0x83>
     91e:	90 91 10 04 	lds	r25, 0x0410	; 0x800410 <dimmer+0x84>
     922:	0e 94 74 2b 	call	0x56e8	; 0x56e8 <__fixunssfsi>
     926:	70 93 f9 03 	sts	0x03F9, r23	; 0x8003f9 <dimmer+0x6d>
     92a:	60 93 f8 03 	sts	0x03F8, r22	; 0x8003f8 <dimmer+0x6c>
     92e:	f8 94       	cli
     930:	80 91 0c 04 	lds	r24, 0x040C	; 0x80040c <dimmer+0x80>
     934:	8d 7f       	andi	r24, 0xFD	; 253
     936:	80 93 0c 04 	sts	0x040C, r24	; 0x80040c <dimmer+0x80>
     93a:	78 94       	sei
     93c:	cc e8       	ldi	r28, 0x8C	; 140
     93e:	d3 e0       	ldi	r29, 0x03	; 3
     940:	01 e1       	ldi	r16, 0x11	; 17
     942:	14 e0       	ldi	r17, 0x04	; 4
     944:	e1 2c       	mov	r14, r1
     946:	f1 2c       	mov	r15, r1
     948:	c8 84       	ldd	r12, Y+8	; 0x08
     94a:	d9 84       	ldd	r13, Y+9	; 0x09
     94c:	c1 14       	cp	r12, r1
     94e:	d1 04       	cpc	r13, r1
     950:	69 f1       	breq	.+90     	; 0x9ac <__stack+0xad>
     952:	80 91 0c 04 	lds	r24, 0x040C	; 0x80040c <dimmer+0x80>
     956:	82 ff       	sbrs	r24, 2
     958:	04 c0       	rjmp	.+8      	; 0x962 <__stack+0x63>
     95a:	21 e0       	ldi	r18, 0x01	; 1
     95c:	c2 16       	cp	r12, r18
     95e:	d1 04       	cpc	r13, r1
     960:	29 f1       	breq	.+74     	; 0x9ac <__stack+0xad>
     962:	2c 81       	ldd	r18, Y+4	; 0x04
     964:	3d 81       	ldd	r19, Y+5	; 0x05
     966:	4e 81       	ldd	r20, Y+6	; 0x06
     968:	5f 81       	ldd	r21, Y+7	; 0x07
     96a:	68 81       	ld	r22, Y
     96c:	79 81       	ldd	r23, Y+1	; 0x01
     96e:	8a 81       	ldd	r24, Y+2	; 0x02
     970:	9b 81       	ldd	r25, Y+3	; 0x03
     972:	0e 94 8f 2a 	call	0x551e	; 0x551e <__addsf3>
     976:	68 83       	st	Y, r22
     978:	79 83       	std	Y+1, r23	; 0x01
     97a:	8a 83       	std	Y+2, r24	; 0x02
     97c:	9b 83       	std	Y+3, r25	; 0x03
     97e:	e1 e0       	ldi	r30, 0x01	; 1
     980:	ce 1a       	sub	r12, r30
     982:	d1 08       	sbc	r13, r1
     984:	d9 86       	std	Y+9, r13	; 0x09
     986:	c8 86       	std	Y+8, r12	; 0x08
     988:	cd 28       	or	r12, r13
     98a:	79 f5       	brne	.+94     	; 0x9ea <__stack+0xeb>
     98c:	8a 85       	ldd	r24, Y+10	; 0x0a
     98e:	9b 85       	ldd	r25, Y+11	; 0x0b
     990:	97 ff       	sbrs	r25, 7
     992:	24 c0       	rjmp	.+72     	; 0x9dc <__stack+0xdd>
     994:	80 e0       	ldi	r24, 0x00	; 0
     996:	90 e0       	ldi	r25, 0x00	; 0
     998:	f8 01       	movw	r30, r16
     99a:	95 87       	std	Z+13, r25	; 0x0d
     99c:	84 87       	std	Z+12, r24	; 0x0c
     99e:	f7 01       	movw	r30, r14
     9a0:	ee 0f       	add	r30, r30
     9a2:	ff 1f       	adc	r31, r31
     9a4:	e0 51       	subi	r30, 0x10	; 16
     9a6:	fc 4f       	sbci	r31, 0xFC	; 252
     9a8:	91 83       	std	Z+1, r25	; 0x01
     9aa:	80 83       	st	Z, r24
     9ac:	ff ef       	ldi	r31, 0xFF	; 255
     9ae:	ef 1a       	sub	r14, r31
     9b0:	ff 0a       	sbc	r15, r31
     9b2:	2c 96       	adiw	r28, 0x0c	; 12
     9b4:	0e 5f       	subi	r16, 0xFE	; 254
     9b6:	1f 4f       	sbci	r17, 0xFF	; 255
     9b8:	24 e0       	ldi	r18, 0x04	; 4
     9ba:	e2 16       	cp	r14, r18
     9bc:	f1 04       	cpc	r15, r1
     9be:	21 f6       	brne	.-120    	; 0x948 <__stack+0x49>
     9c0:	df 91       	pop	r29
     9c2:	cf 91       	pop	r28
     9c4:	1f 91       	pop	r17
     9c6:	0f 91       	pop	r16
     9c8:	ff 90       	pop	r15
     9ca:	ef 90       	pop	r14
     9cc:	df 90       	pop	r13
     9ce:	cf 90       	pop	r12
     9d0:	bf 90       	pop	r11
     9d2:	af 90       	pop	r10
     9d4:	9f 90       	pop	r9
     9d6:	8f 90       	pop	r8
     9d8:	0c 94 27 18 	jmp	0x304e	; 0x304e <_ZN6Dimmer18_calculateChannelsEv.constprop.69>
     9dc:	8f 3f       	cpi	r24, 0xFF	; 255
     9de:	ef e1       	ldi	r30, 0x1F	; 31
     9e0:	9e 07       	cpc	r25, r30
     9e2:	d4 f2       	brlt	.-76     	; 0x998 <__stack+0x99>
     9e4:	8f ef       	ldi	r24, 0xFF	; 255
     9e6:	9f e1       	ldi	r25, 0x1F	; 31
     9e8:	d7 cf       	rjmp	.-82     	; 0x998 <__stack+0x99>
     9ea:	0e 94 6d 2b 	call	0x56da	; 0x56da <__fixsfsi>
     9ee:	77 fd       	sbrc	r23, 7
     9f0:	07 c0       	rjmp	.+14     	; 0xa00 <__stack+0x101>
     9f2:	6f 3f       	cpi	r22, 0xFF	; 255
     9f4:	ff e1       	ldi	r31, 0x1F	; 31
     9f6:	7f 07       	cpc	r23, r31
     9f8:	2c f0       	brlt	.+10     	; 0xa04 <__stack+0x105>
     9fa:	6f ef       	ldi	r22, 0xFF	; 255
     9fc:	7f e1       	ldi	r23, 0x1F	; 31
     9fe:	02 c0       	rjmp	.+4      	; 0xa04 <__stack+0x105>
     a00:	60 e0       	ldi	r22, 0x00	; 0
     a02:	70 e0       	ldi	r23, 0x00	; 0
     a04:	f8 01       	movw	r30, r16
     a06:	75 87       	std	Z+13, r23	; 0x0d
     a08:	64 87       	std	Z+12, r22	; 0x0c
     a0a:	d0 cf       	rjmp	.-96     	; 0x9ac <__stack+0xad>
     a0c:	df 91       	pop	r29
     a0e:	cf 91       	pop	r28
     a10:	1f 91       	pop	r17
     a12:	0f 91       	pop	r16
     a14:	ff 90       	pop	r15
     a16:	ef 90       	pop	r14
     a18:	df 90       	pop	r13
     a1a:	cf 90       	pop	r12
     a1c:	bf 90       	pop	r11
     a1e:	af 90       	pop	r10
     a20:	9f 90       	pop	r9
     a22:	8f 90       	pop	r8
     a24:	08 95       	ret

00000a26 <_Z11init_eepromv>:
     a26:	cf 93       	push	r28
     a28:	df 93       	push	r29
     a2a:	81 e0       	ldi	r24, 0x01	; 1
     a2c:	90 e0       	ldi	r25, 0x00	; 0
     a2e:	a0 e0       	ldi	r26, 0x00	; 0
     a30:	b0 e0       	ldi	r27, 0x00	; 0
     a32:	80 93 8c 04 	sts	0x048C, r24	; 0x80048c <config>
     a36:	90 93 8d 04 	sts	0x048D, r25	; 0x80048d <config+0x1>
     a3a:	a0 93 8e 04 	sts	0x048E, r26	; 0x80048e <config+0x2>
     a3e:	b0 93 8f 04 	sts	0x048F, r27	; 0x80048f <config+0x3>
     a42:	10 92 8d 02 	sts	0x028D, r1	; 0x80028d <eeprom_position+0x1>
     a46:	10 92 8c 02 	sts	0x028C, r1	; 0x80028c <eeprom_position>
     a4a:	c0 e0       	ldi	r28, 0x00	; 0
     a4c:	d0 e0       	ldi	r29, 0x00	; 0
     a4e:	60 e0       	ldi	r22, 0x00	; 0
     a50:	ce 01       	movw	r24, r28
     a52:	0e 94 1a 2a 	call	0x5434	; 0x5434 <eeprom_write_byte>
     a56:	21 96       	adiw	r28, 0x01	; 1
     a58:	c1 15       	cp	r28, r1
     a5a:	84 e0       	ldi	r24, 0x04	; 4
     a5c:	d8 07       	cpc	r29, r24
     a5e:	b9 f7       	brne	.-18     	; 0xa4e <_Z11init_eepromv+0x28>
     a60:	0e 94 08 18 	call	0x3010	; 0x3010 <_ZNK13ConfigStorage3crcEv.constprop.83>
     a64:	90 93 91 04 	sts	0x0491, r25	; 0x800491 <config+0x5>
     a68:	80 93 90 04 	sts	0x0490, r24	; 0x800490 <config+0x4>
     a6c:	80 91 8c 02 	lds	r24, 0x028C	; 0x80028c <eeprom_position>
     a70:	90 91 8d 02 	lds	r25, 0x028D	; 0x80028d <eeprom_position+0x1>
     a74:	df 91       	pop	r29
     a76:	cf 91       	pop	r28
     a78:	0c 94 8f 17 	jmp	0x2f1e	; 0x2f1e <_ZN13ConfigStorage5writeEj.constprop.86>

00000a7c <_Z12reset_configv>:
     a7c:	cf 93       	push	r28
     a7e:	df 93       	push	r29
     a80:	2c e8       	ldi	r18, 0x8C	; 140
     a82:	34 e0       	ldi	r19, 0x04	; 4
     a84:	d9 01       	movw	r26, r18
     a86:	1d 92       	st	X+, r1
     a88:	1d 92       	st	X+, r1
     a8a:	1d 92       	st	X+, r1
     a8c:	1c 92       	st	X, r1
     a8e:	13 97       	sbiw	r26, 0x03	; 3
     a90:	88 e0       	ldi	r24, 0x08	; 8
     a92:	e2 e9       	ldi	r30, 0x92	; 146
     a94:	f4 e0       	ldi	r31, 0x04	; 4
     a96:	ef 01       	movw	r28, r30
     a98:	19 92       	st	Y+, r1
     a9a:	8a 95       	dec	r24
     a9c:	e9 f7       	brne	.-6      	; 0xa98 <_Z12reset_configv+0x1c>
     a9e:	e1 e1       	ldi	r30, 0x11	; 17
     aa0:	f4 e0       	ldi	r31, 0x04	; 4
     aa2:	10 92 8a 04 	sts	0x048A, r1	; 0x80048a <register_mem+0x79>
     aa6:	10 92 89 04 	sts	0x0489, r1	; 0x800489 <register_mem+0x78>
     aaa:	a3 e3       	ldi	r26, 0x33	; 51
     aac:	b4 e0       	ldi	r27, 0x04	; 4
     aae:	84 e1       	ldi	r24, 0x14	; 20
     ab0:	ed 01       	movw	r28, r26
     ab2:	19 92       	st	Y+, r1
     ab4:	8a 95       	dec	r24
     ab6:	e9 f7       	brne	.-6      	; 0xab2 <_Z12reset_configv+0x36>
     ab8:	80 e0       	ldi	r24, 0x00	; 0
     aba:	9c e0       	ldi	r25, 0x0C	; 12
     abc:	90 93 88 04 	sts	0x0488, r25	; 0x800488 <register_mem+0x77>
     ac0:	80 93 87 04 	sts	0x0487, r24	; 0x800487 <register_mem+0x76>
     ac4:	81 e4       	ldi	r24, 0x41	; 65
     ac6:	83 a3       	std	Z+35, r24	; 0x23
     ac8:	8c 91       	ld	r24, X
     aca:	81 60       	ori	r24, 0x01	; 1
     acc:	82 60       	ori	r24, 0x02	; 2
     ace:	8c 93       	st	X, r24
     ad0:	80 e0       	ldi	r24, 0x00	; 0
     ad2:	90 e0       	ldi	r25, 0x00	; 0
     ad4:	a0 ef       	ldi	r26, 0xF0	; 240
     ad6:	b0 e4       	ldi	r27, 0x40	; 64
     ad8:	84 a3       	std	Z+36, r24	; 0x24
     ada:	95 a3       	std	Z+37, r25	; 0x25
     adc:	a6 a3       	std	Z+38, r26	; 0x26
     ade:	b7 a3       	std	Z+39, r27	; 0x27
     ae0:	82 e0       	ldi	r24, 0x02	; 2
     ae2:	80 a7       	std	Z+40, r24	; 0x28
     ae4:	80 ef       	ldi	r24, 0xF0	; 240
     ae6:	90 e0       	ldi	r25, 0x00	; 0
     ae8:	94 a7       	std	Z+44, r25	; 0x2c
     aea:	83 a7       	std	Z+43, r24	; 0x2b
     aec:	88 e5       	ldi	r24, 0x58	; 88
     aee:	92 e0       	ldi	r25, 0x02	; 2
     af0:	96 a7       	std	Z+46, r25	; 0x2e
     af2:	85 a7       	std	Z+45, r24	; 0x2d
     af4:	8d ec       	ldi	r24, 0xCD	; 205
     af6:	9c ec       	ldi	r25, 0xCC	; 204
     af8:	ac e8       	ldi	r26, 0x8C	; 140
     afa:	bf e3       	ldi	r27, 0x3F	; 63
     afc:	87 a7       	std	Z+47, r24	; 0x2f
     afe:	90 ab       	std	Z+48, r25	; 0x30
     b00:	a1 ab       	std	Z+49, r26	; 0x31
     b02:	b2 ab       	std	Z+50, r27	; 0x32
     b04:	8a e0       	ldi	r24, 0x0A	; 10
     b06:	85 ab       	std	Z+53, r24	; 0x35
     b08:	88 ed       	ldi	r24, 0xD8	; 216
     b0a:	83 ab       	std	Z+51, r24	; 0x33
     b0c:	8e ef       	ldi	r24, 0xFE	; 254
     b0e:	9f ef       	ldi	r25, 0xFF	; 255
     b10:	f9 01       	movw	r30, r18
     b12:	95 83       	std	Z+5, r25	; 0x05
     b14:	84 83       	std	Z+4, r24	; 0x04
     b16:	df 91       	pop	r29
     b18:	cf 91       	pop	r28
     b1a:	08 95       	ret

00000b1c <_Z13get_signaturePh>:
     b1c:	dc 01       	movw	r26, r24
     b1e:	91 e2       	ldi	r25, 0x21	; 33
     b20:	e0 e0       	ldi	r30, 0x00	; 0
     b22:	f0 e0       	ldi	r31, 0x00	; 0
     b24:	90 93 57 00 	sts	0x0057, r25	; 0x800057 <__TEXT_REGION_LENGTH__+0x7e0057>
     b28:	e4 91       	lpm	r30, Z
     b2a:	ec 93       	st	X, r30
     b2c:	e2 e0       	ldi	r30, 0x02	; 2
     b2e:	f0 e0       	ldi	r31, 0x00	; 0
     b30:	90 93 57 00 	sts	0x0057, r25	; 0x800057 <__TEXT_REGION_LENGTH__+0x7e0057>
     b34:	e4 91       	lpm	r30, Z
     b36:	11 96       	adiw	r26, 0x01	; 1
     b38:	ec 93       	st	X, r30
     b3a:	11 97       	sbiw	r26, 0x01	; 1
     b3c:	e4 e0       	ldi	r30, 0x04	; 4
     b3e:	f0 e0       	ldi	r31, 0x00	; 0
     b40:	90 93 57 00 	sts	0x0057, r25	; 0x800057 <__TEXT_REGION_LENGTH__+0x7e0057>
     b44:	94 91       	lpm	r25, Z
     b46:	12 96       	adiw	r26, 0x02	; 2
     b48:	9c 93       	st	X, r25
     b4a:	12 97       	sbiw	r26, 0x02	; 2
     b4c:	cd 01       	movw	r24, r26
     b4e:	08 95       	ret

00000b50 <_Z15Serial_printf_PPKcz>:
     b50:	8f 92       	push	r8
     b52:	9f 92       	push	r9
     b54:	af 92       	push	r10
     b56:	bf 92       	push	r11
     b58:	cf 92       	push	r12
     b5a:	df 92       	push	r13
     b5c:	ef 92       	push	r14
     b5e:	ff 92       	push	r15
     b60:	0f 93       	push	r16
     b62:	1f 93       	push	r17
     b64:	cf 93       	push	r28
     b66:	df 93       	push	r29
     b68:	cd b7       	in	r28, 0x3d	; 61
     b6a:	de b7       	in	r29, 0x3e	; 62
     b6c:	c0 54       	subi	r28, 0x40	; 64
     b6e:	d1 09       	sbc	r29, r1
     b70:	0f b6       	in	r0, 0x3f	; 63
     b72:	f8 94       	cli
     b74:	de bf       	out	0x3e, r29	; 62
     b76:	0f be       	out	0x3f, r0	; 63
     b78:	cd bf       	out	0x3d, r28	; 61
     b7a:	ce 01       	movw	r24, r28
     b7c:	81 5b       	subi	r24, 0xB1	; 177
     b7e:	9f 4f       	sbci	r25, 0xFF	; 255
     b80:	fc 01       	movw	r30, r24
     b82:	81 90       	ld	r8, Z+
     b84:	91 90       	ld	r9, Z+
     b86:	6f 01       	movw	r12, r30
     b88:	9f 01       	movw	r18, r30
     b8a:	a4 01       	movw	r20, r8
     b8c:	60 e4       	ldi	r22, 0x40	; 64
     b8e:	70 e0       	ldi	r23, 0x00	; 0
     b90:	8e 54       	subi	r24, 0x4E	; 78
     b92:	91 09       	sbc	r25, r1
     b94:	5c 01       	movw	r10, r24
     b96:	0e 94 61 28 	call	0x50c2	; 0x50c2 <vsnprintf_P>
     b9a:	8c 01       	movw	r16, r24
     b9c:	8f 33       	cpi	r24, 0x3F	; 63
     b9e:	91 05       	cpc	r25, r1
     ba0:	84 f0       	brlt	.+32     	; 0xbc2 <_Z15Serial_printf_PPKcz+0x72>
     ba2:	02 96       	adiw	r24, 0x02	; 2
     ba4:	0e 94 32 2c 	call	0x5864	; 0x5864 <malloc>
     ba8:	7c 01       	movw	r14, r24
     baa:	00 97       	sbiw	r24, 0x00	; 0
     bac:	e1 f0       	breq	.+56     	; 0xbe6 <_Z15Serial_printf_PPKcz+0x96>
     bae:	96 01       	movw	r18, r12
     bb0:	a4 01       	movw	r20, r8
     bb2:	b8 01       	movw	r22, r16
     bb4:	0e 94 61 28 	call	0x50c2	; 0x50c2 <vsnprintf_P>
     bb8:	8c 01       	movw	r16, r24
     bba:	18 16       	cp	r1, r24
     bbc:	19 06       	cpc	r1, r25
     bbe:	5c f4       	brge	.+22     	; 0xbd6 <_Z15Serial_printf_PPKcz+0x86>
     bc0:	04 c0       	rjmp	.+8      	; 0xbca <_Z15Serial_printf_PPKcz+0x7a>
     bc2:	18 16       	cp	r1, r24
     bc4:	19 06       	cpc	r1, r25
     bc6:	6c f4       	brge	.+26     	; 0xbe2 <_Z15Serial_printf_PPKcz+0x92>
     bc8:	75 01       	movw	r14, r10
     bca:	a8 01       	movw	r20, r16
     bcc:	b7 01       	movw	r22, r14
     bce:	89 ea       	ldi	r24, 0xA9	; 169
     bd0:	92 e0       	ldi	r25, 0x02	; 2
     bd2:	0e 94 6c 10 	call	0x20d8	; 0x20d8 <_ZN5Print5writeEPKhj>
     bd6:	ae 14       	cp	r10, r14
     bd8:	bf 04       	cpc	r11, r15
     bda:	19 f0       	breq	.+6      	; 0xbe2 <_Z15Serial_printf_PPKcz+0x92>
     bdc:	c7 01       	movw	r24, r14
     bde:	0e 94 ca 2c 	call	0x5994	; 0x5994 <free>
     be2:	c8 01       	movw	r24, r16
     be4:	02 c0       	rjmp	.+4      	; 0xbea <_Z15Serial_printf_PPKcz+0x9a>
     be6:	80 e0       	ldi	r24, 0x00	; 0
     be8:	90 e0       	ldi	r25, 0x00	; 0
     bea:	c0 5c       	subi	r28, 0xC0	; 192
     bec:	df 4f       	sbci	r29, 0xFF	; 255
     bee:	0f b6       	in	r0, 0x3f	; 63
     bf0:	f8 94       	cli
     bf2:	de bf       	out	0x3e, r29	; 62
     bf4:	0f be       	out	0x3f, r0	; 63
     bf6:	cd bf       	out	0x3d, r28	; 61
     bf8:	df 91       	pop	r29
     bfa:	cf 91       	pop	r28
     bfc:	1f 91       	pop	r17
     bfe:	0f 91       	pop	r16
     c00:	ff 90       	pop	r15
     c02:	ef 90       	pop	r14
     c04:	df 90       	pop	r13
     c06:	cf 90       	pop	r12
     c08:	bf 90       	pop	r11
     c0a:	af 90       	pop	r10
     c0c:	9f 90       	pop	r9
     c0e:	8f 90       	pop	r8
     c10:	08 95       	ret

00000c12 <_Z13print_zcdelayv>:
     c12:	e1 e1       	ldi	r30, 0x11	; 17
     c14:	f4 e0       	ldi	r31, 0x04	; 4
     c16:	82 a5       	ldd	r24, Z+42	; 0x2a
     c18:	8f 93       	push	r24
     c1a:	81 a5       	ldd	r24, Z+41	; 0x29
     c1c:	8f 93       	push	r24
     c1e:	8b ec       	ldi	r24, 0xCB	; 203
     c20:	91 e0       	ldi	r25, 0x01	; 1
     c22:	9f 93       	push	r25
     c24:	8f 93       	push	r24
     c26:	0e 94 a8 05 	call	0xb50	; 0xb50 <_Z15Serial_printf_PPKcz>
     c2a:	0f 90       	pop	r0
     c2c:	0f 90       	pop	r0
     c2e:	0f 90       	pop	r0
     c30:	0f 90       	pop	r0
     c32:	08 95       	ret

00000c34 <_Z13Serial_printfPKcz>:
     c34:	8f 92       	push	r8
     c36:	9f 92       	push	r9
     c38:	af 92       	push	r10
     c3a:	bf 92       	push	r11
     c3c:	cf 92       	push	r12
     c3e:	df 92       	push	r13
     c40:	ef 92       	push	r14
     c42:	ff 92       	push	r15
     c44:	0f 93       	push	r16
     c46:	1f 93       	push	r17
     c48:	cf 93       	push	r28
     c4a:	df 93       	push	r29
     c4c:	cd b7       	in	r28, 0x3d	; 61
     c4e:	de b7       	in	r29, 0x3e	; 62
     c50:	c0 54       	subi	r28, 0x40	; 64
     c52:	d1 09       	sbc	r29, r1
     c54:	0f b6       	in	r0, 0x3f	; 63
     c56:	f8 94       	cli
     c58:	de bf       	out	0x3e, r29	; 62
     c5a:	0f be       	out	0x3f, r0	; 63
     c5c:	cd bf       	out	0x3d, r28	; 61
     c5e:	ce 01       	movw	r24, r28
     c60:	81 5b       	subi	r24, 0xB1	; 177
     c62:	9f 4f       	sbci	r25, 0xFF	; 255
     c64:	fc 01       	movw	r30, r24
     c66:	81 90       	ld	r8, Z+
     c68:	91 90       	ld	r9, Z+
     c6a:	6f 01       	movw	r12, r30
     c6c:	9f 01       	movw	r18, r30
     c6e:	a4 01       	movw	r20, r8
     c70:	60 e4       	ldi	r22, 0x40	; 64
     c72:	70 e0       	ldi	r23, 0x00	; 0
     c74:	8e 54       	subi	r24, 0x4E	; 78
     c76:	91 09       	sbc	r25, r1
     c78:	5c 01       	movw	r10, r24
     c7a:	0e 94 76 2e 	call	0x5cec	; 0x5cec <vsnprintf>
     c7e:	8c 01       	movw	r16, r24
     c80:	8f 33       	cpi	r24, 0x3F	; 63
     c82:	91 05       	cpc	r25, r1
     c84:	84 f0       	brlt	.+32     	; 0xca6 <_Z13Serial_printfPKcz+0x72>
     c86:	02 96       	adiw	r24, 0x02	; 2
     c88:	0e 94 32 2c 	call	0x5864	; 0x5864 <malloc>
     c8c:	7c 01       	movw	r14, r24
     c8e:	00 97       	sbiw	r24, 0x00	; 0
     c90:	e1 f0       	breq	.+56     	; 0xcca <_Z13Serial_printfPKcz+0x96>
     c92:	96 01       	movw	r18, r12
     c94:	a4 01       	movw	r20, r8
     c96:	b8 01       	movw	r22, r16
     c98:	0e 94 76 2e 	call	0x5cec	; 0x5cec <vsnprintf>
     c9c:	8c 01       	movw	r16, r24
     c9e:	18 16       	cp	r1, r24
     ca0:	19 06       	cpc	r1, r25
     ca2:	5c f4       	brge	.+22     	; 0xcba <_Z13Serial_printfPKcz+0x86>
     ca4:	04 c0       	rjmp	.+8      	; 0xcae <_Z13Serial_printfPKcz+0x7a>
     ca6:	18 16       	cp	r1, r24
     ca8:	19 06       	cpc	r1, r25
     caa:	6c f4       	brge	.+26     	; 0xcc6 <_Z13Serial_printfPKcz+0x92>
     cac:	75 01       	movw	r14, r10
     cae:	a8 01       	movw	r20, r16
     cb0:	b7 01       	movw	r22, r14
     cb2:	89 ea       	ldi	r24, 0xA9	; 169
     cb4:	92 e0       	ldi	r25, 0x02	; 2
     cb6:	0e 94 6c 10 	call	0x20d8	; 0x20d8 <_ZN5Print5writeEPKhj>
     cba:	ae 14       	cp	r10, r14
     cbc:	bf 04       	cpc	r11, r15
     cbe:	19 f0       	breq	.+6      	; 0xcc6 <_Z13Serial_printfPKcz+0x92>
     cc0:	c7 01       	movw	r24, r14
     cc2:	0e 94 ca 2c 	call	0x5994	; 0x5994 <free>
     cc6:	c8 01       	movw	r24, r16
     cc8:	02 c0       	rjmp	.+4      	; 0xcce <_Z13Serial_printfPKcz+0x9a>
     cca:	80 e0       	ldi	r24, 0x00	; 0
     ccc:	90 e0       	ldi	r25, 0x00	; 0
     cce:	c0 5c       	subi	r28, 0xC0	; 192
     cd0:	df 4f       	sbci	r29, 0xFF	; 255
     cd2:	0f b6       	in	r0, 0x3f	; 63
     cd4:	f8 94       	cli
     cd6:	de bf       	out	0x3e, r29	; 62
     cd8:	0f be       	out	0x3f, r0	; 63
     cda:	cd bf       	out	0x3d, r28	; 61
     cdc:	df 91       	pop	r29
     cde:	cf 91       	pop	r28
     ce0:	1f 91       	pop	r17
     ce2:	0f 91       	pop	r16
     ce4:	ff 90       	pop	r15
     ce6:	ef 90       	pop	r14
     ce8:	df 90       	pop	r13
     cea:	cf 90       	pop	r12
     cec:	bf 90       	pop	r11
     cee:	af 90       	pop	r10
     cf0:	9f 90       	pop	r9
     cf2:	8f 90       	pop	r8
     cf4:	08 95       	ret

00000cf6 <_Z18Serial_print_floatdhh>:
     cf6:	2f 92       	push	r2
     cf8:	3f 92       	push	r3
     cfa:	4f 92       	push	r4
     cfc:	5f 92       	push	r5
     cfe:	6f 92       	push	r6
     d00:	7f 92       	push	r7
     d02:	8f 92       	push	r8
     d04:	9f 92       	push	r9
     d06:	af 92       	push	r10
     d08:	bf 92       	push	r11
     d0a:	cf 92       	push	r12
     d0c:	df 92       	push	r13
     d0e:	ef 92       	push	r14
     d10:	ff 92       	push	r15
     d12:	0f 93       	push	r16
     d14:	1f 93       	push	r17
     d16:	cf 93       	push	r28
     d18:	df 93       	push	r29
     d1a:	cd b7       	in	r28, 0x3d	; 61
     d1c:	de b7       	in	r29, 0x3e	; 62
     d1e:	a8 97       	sbiw	r28, 0x28	; 40
     d20:	0f b6       	in	r0, 0x3f	; 63
     d22:	f8 94       	cli
     d24:	de bf       	out	0x3e, r29	; 62
     d26:	0f be       	out	0x3f, r0	; 63
     d28:	cd bf       	out	0x3d, r28	; 61
     d2a:	6b 01       	movw	r12, r22
     d2c:	7c 01       	movw	r14, r24
     d2e:	14 2f       	mov	r17, r20
     d30:	02 2f       	mov	r16, r18
     d32:	20 e0       	ldi	r18, 0x00	; 0
     d34:	30 e0       	ldi	r19, 0x00	; 0
     d36:	a9 01       	movw	r20, r18
     d38:	0e 94 a3 2b 	call	0x5746	; 0x5746 <__gesf2>
     d3c:	46 01       	movw	r8, r12
     d3e:	57 01       	movw	r10, r14
     d40:	18 16       	cp	r1, r24
     d42:	24 f0       	brlt	.+8      	; 0xd4c <_Z18Serial_print_floatdhh+0x56>
     d44:	b7 fa       	bst	r11, 7
     d46:	b0 94       	com	r11
     d48:	b7 f8       	bld	r11, 7
     d4a:	b0 94       	com	r11
     d4c:	20 e0       	ldi	r18, 0x00	; 0
     d4e:	30 e0       	ldi	r19, 0x00	; 0
     d50:	40 e8       	ldi	r20, 0x80	; 128
     d52:	5f e3       	ldi	r21, 0x3F	; 63
     d54:	c5 01       	movw	r24, r10
     d56:	b4 01       	movw	r22, r8
     d58:	0e 94 ee 28 	call	0x51dc	; 0x51dc <__cmpsf2>
     d5c:	87 ff       	sbrs	r24, 7
     d5e:	19 c0       	rjmp	.+50     	; 0xd92 <_Z18Serial_print_floatdhh+0x9c>
     d60:	20 e0       	ldi	r18, 0x00	; 0
     d62:	30 e0       	ldi	r19, 0x00	; 0
     d64:	40 e2       	ldi	r20, 0x20	; 32
     d66:	51 e4       	ldi	r21, 0x41	; 65
     d68:	c5 01       	movw	r24, r10
     d6a:	b4 01       	movw	r22, r8
     d6c:	0e 94 54 29 	call	0x52a8	; 0x52a8 <__mulsf3>
     d70:	4b 01       	movw	r8, r22
     d72:	5c 01       	movw	r10, r24
     d74:	20 e0       	ldi	r18, 0x00	; 0
     d76:	30 e0       	ldi	r19, 0x00	; 0
     d78:	40 e8       	ldi	r20, 0x80	; 128
     d7a:	5f e3       	ldi	r21, 0x3F	; 63
     d7c:	0e 94 ee 28 	call	0x51dc	; 0x51dc <__cmpsf2>
     d80:	87 ff       	sbrs	r24, 7
     d82:	19 c0       	rjmp	.+50     	; 0xdb6 <_Z18Serial_print_floatdhh+0xc0>
     d84:	10 17       	cp	r17, r16
     d86:	08 f4       	brcc	.+2      	; 0xd8a <_Z18Serial_print_floatdhh+0x94>
     d88:	0c c1       	rjmp	.+536    	; 0xfa2 <_Z18Serial_print_floatdhh+0x2ac>
     d8a:	15 c0       	rjmp	.+42     	; 0xdb6 <_Z18Serial_print_floatdhh+0xc0>
     d8c:	12 30       	cpi	r17, 0x02	; 2
     d8e:	98 f0       	brcs	.+38     	; 0xdb6 <_Z18Serial_print_floatdhh+0xc0>
     d90:	11 50       	subi	r17, 0x01	; 1
     d92:	20 e0       	ldi	r18, 0x00	; 0
     d94:	30 e0       	ldi	r19, 0x00	; 0
     d96:	40 e2       	ldi	r20, 0x20	; 32
     d98:	51 e4       	ldi	r21, 0x41	; 65
     d9a:	c5 01       	movw	r24, r10
     d9c:	b4 01       	movw	r22, r8
     d9e:	0e 94 fb 2a 	call	0x55f6	; 0x55f6 <__divsf3>
     da2:	4b 01       	movw	r8, r22
     da4:	5c 01       	movw	r10, r24
     da6:	20 e0       	ldi	r18, 0x00	; 0
     da8:	30 e0       	ldi	r19, 0x00	; 0
     daa:	40 e8       	ldi	r20, 0x80	; 128
     dac:	5f e3       	ldi	r21, 0x3F	; 63
     dae:	0e 94 a3 2b 	call	0x5746	; 0x5746 <__gesf2>
     db2:	18 16       	cp	r1, r24
     db4:	5c f3       	brlt	.-42     	; 0xd8c <_Z18Serial_print_floatdhh+0x96>
     db6:	1f 92       	push	r1
     db8:	1f 93       	push	r17
     dba:	84 ec       	ldi	r24, 0xC4	; 196
     dbc:	91 e0       	ldi	r25, 0x01	; 1
     dbe:	9f 93       	push	r25
     dc0:	8f 93       	push	r24
     dc2:	1f 92       	push	r1
     dc4:	88 e0       	ldi	r24, 0x08	; 8
     dc6:	8f 93       	push	r24
     dc8:	5e 01       	movw	r10, r28
     dca:	21 e2       	ldi	r18, 0x21	; 33
     dcc:	a2 0e       	add	r10, r18
     dce:	b1 1c       	adc	r11, r1
     dd0:	bf 92       	push	r11
     dd2:	af 92       	push	r10
     dd4:	0e 94 31 28 	call	0x5062	; 0x5062 <snprintf_P>
     dd8:	ff 92       	push	r15
     dda:	ef 92       	push	r14
     ddc:	df 92       	push	r13
     dde:	cf 92       	push	r12
     de0:	bf 92       	push	r11
     de2:	af 92       	push	r10
     de4:	1f 92       	push	r1
     de6:	80 e2       	ldi	r24, 0x20	; 32
     de8:	8f 93       	push	r24
     dea:	ce 01       	movw	r24, r28
     dec:	01 96       	adiw	r24, 0x01	; 1
     dee:	5c 01       	movw	r10, r24
     df0:	9f 93       	push	r25
     df2:	8f 93       	push	r24
     df4:	0e 94 46 2e 	call	0x5c8c	; 0x5c8c <snprintf>
     df8:	0f b6       	in	r0, 0x3f	; 63
     dfa:	f8 94       	cli
     dfc:	de bf       	out	0x3e, r29	; 62
     dfe:	0f be       	out	0x3f, r0	; 63
     e00:	cd bf       	out	0x3d, r28	; 61
     e02:	80 97       	sbiw	r24, 0x20	; 32
     e04:	a4 f4       	brge	.+40     	; 0xe2e <_Z18Serial_print_floatdhh+0x138>
     e06:	6e e2       	ldi	r22, 0x2E	; 46
     e08:	70 e0       	ldi	r23, 0x00	; 0
     e0a:	c5 01       	movw	r24, r10
     e0c:	0e 94 34 2e 	call	0x5c68	; 0x5c68 <strchr>
     e10:	00 97       	sbiw	r24, 0x00	; 0
     e12:	69 f0       	breq	.+26     	; 0xe2e <_Z18Serial_print_floatdhh+0x138>
     e14:	dc 01       	movw	r26, r24
     e16:	11 96       	adiw	r26, 0x01	; 1
     e18:	fd 01       	movw	r30, r26
     e1a:	01 90       	ld	r0, Z+
     e1c:	00 20       	and	r0, r0
     e1e:	e9 f7       	brne	.-6      	; 0xe1a <_Z18Serial_print_floatdhh+0x124>
     e20:	31 97       	sbiw	r30, 0x01	; 1
     e22:	31 97       	sbiw	r30, 0x01	; 1
     e24:	ae 17       	cp	r26, r30
     e26:	bf 07       	cpc	r27, r31
     e28:	08 f4       	brcc	.+2      	; 0xe2c <_Z18Serial_print_floatdhh+0x136>
     e2a:	bd c0       	rjmp	.+378    	; 0xfa6 <_Z18Serial_print_floatdhh+0x2b0>
     e2c:	01 2f       	mov	r16, r17
     e2e:	a7 01       	movw	r20, r14
     e30:	96 01       	movw	r18, r12
     e32:	c7 01       	movw	r24, r14
     e34:	b6 01       	movw	r22, r12
     e36:	0e 94 f8 2b 	call	0x57f0	; 0x57f0 <__unordsf2>
     e3a:	88 23       	and	r24, r24
     e3c:	19 f0       	breq	.+6      	; 0xe44 <_Z18Serial_print_floatdhh+0x14e>
     e3e:	6e e6       	ldi	r22, 0x6E	; 110
     e40:	71 e0       	ldi	r23, 0x01	; 1
     e42:	27 c0       	rjmp	.+78     	; 0xe92 <_Z18Serial_print_floatdhh+0x19c>
     e44:	46 01       	movw	r8, r12
     e46:	57 01       	movw	r10, r14
     e48:	e8 94       	clt
     e4a:	b7 f8       	bld	r11, 7
     e4c:	2f ef       	ldi	r18, 0xFF	; 255
     e4e:	3f ef       	ldi	r19, 0xFF	; 255
     e50:	4f e7       	ldi	r20, 0x7F	; 127
     e52:	5f e7       	ldi	r21, 0x7F	; 127
     e54:	c5 01       	movw	r24, r10
     e56:	b4 01       	movw	r22, r8
     e58:	0e 94 f8 2b 	call	0x57f0	; 0x57f0 <__unordsf2>
     e5c:	81 11       	cpse	r24, r1
     e5e:	0d c0       	rjmp	.+26     	; 0xe7a <_Z18Serial_print_floatdhh+0x184>
     e60:	2f ef       	ldi	r18, 0xFF	; 255
     e62:	3f ef       	ldi	r19, 0xFF	; 255
     e64:	4f e7       	ldi	r20, 0x7F	; 127
     e66:	5f e7       	ldi	r21, 0x7F	; 127
     e68:	c5 01       	movw	r24, r10
     e6a:	b4 01       	movw	r22, r8
     e6c:	0e 94 ee 28 	call	0x51dc	; 0x51dc <__cmpsf2>
     e70:	18 16       	cp	r1, r24
     e72:	1c f4       	brge	.+6      	; 0xe7a <_Z18Serial_print_floatdhh+0x184>
     e74:	62 e7       	ldi	r22, 0x72	; 114
     e76:	71 e0       	ldi	r23, 0x01	; 1
     e78:	0c c0       	rjmp	.+24     	; 0xe92 <_Z18Serial_print_floatdhh+0x19c>
     e7a:	2f ef       	ldi	r18, 0xFF	; 255
     e7c:	3f ef       	ldi	r19, 0xFF	; 255
     e7e:	4f e7       	ldi	r20, 0x7F	; 127
     e80:	5f e4       	ldi	r21, 0x4F	; 79
     e82:	c7 01       	movw	r24, r14
     e84:	b6 01       	movw	r22, r12
     e86:	0e 94 a3 2b 	call	0x5746	; 0x5746 <__gesf2>
     e8a:	18 16       	cp	r1, r24
     e8c:	3c f4       	brge	.+14     	; 0xe9c <_Z18Serial_print_floatdhh+0x1a6>
     e8e:	66 e7       	ldi	r22, 0x76	; 118
     e90:	71 e0       	ldi	r23, 0x01	; 1
     e92:	89 ea       	ldi	r24, 0xA9	; 169
     e94:	92 e0       	ldi	r25, 0x02	; 2
     e96:	0e 94 db 11 	call	0x23b6	; 0x23b6 <_ZN5Print5writeEPKc>
     e9a:	8c c0       	rjmp	.+280    	; 0xfb4 <_Z18Serial_print_floatdhh+0x2be>
     e9c:	2f ef       	ldi	r18, 0xFF	; 255
     e9e:	3f ef       	ldi	r19, 0xFF	; 255
     ea0:	4f e7       	ldi	r20, 0x7F	; 127
     ea2:	5f ec       	ldi	r21, 0xCF	; 207
     ea4:	c7 01       	movw	r24, r14
     ea6:	b6 01       	movw	r22, r12
     ea8:	0e 94 ee 28 	call	0x51dc	; 0x51dc <__cmpsf2>
     eac:	87 fd       	sbrc	r24, 7
     eae:	ef cf       	rjmp	.-34     	; 0xe8e <_Z18Serial_print_floatdhh+0x198>
     eb0:	20 e0       	ldi	r18, 0x00	; 0
     eb2:	30 e0       	ldi	r19, 0x00	; 0
     eb4:	a9 01       	movw	r20, r18
     eb6:	c7 01       	movw	r24, r14
     eb8:	b6 01       	movw	r22, r12
     eba:	0e 94 ee 28 	call	0x51dc	; 0x51dc <__cmpsf2>
     ebe:	87 ff       	sbrs	r24, 7
     ec0:	0b c0       	rjmp	.+22     	; 0xed8 <_Z18Serial_print_floatdhh+0x1e2>
     ec2:	6d e2       	ldi	r22, 0x2D	; 45
     ec4:	89 ea       	ldi	r24, 0xA9	; 169
     ec6:	92 e0       	ldi	r25, 0x02	; 2
     ec8:	0e 94 aa 11 	call	0x2354	; 0x2354 <_ZN5Print5printEc>
     ecc:	5c 01       	movw	r10, r24
     ece:	f7 fa       	bst	r15, 7
     ed0:	f0 94       	com	r15
     ed2:	f7 f8       	bld	r15, 7
     ed4:	f0 94       	com	r15
     ed6:	02 c0       	rjmp	.+4      	; 0xedc <_Z18Serial_print_floatdhh+0x1e6>
     ed8:	a1 2c       	mov	r10, r1
     eda:	b1 2c       	mov	r11, r1
     edc:	10 e0       	ldi	r17, 0x00	; 0
     ede:	60 e0       	ldi	r22, 0x00	; 0
     ee0:	70 e0       	ldi	r23, 0x00	; 0
     ee2:	80 e0       	ldi	r24, 0x00	; 0
     ee4:	9f e3       	ldi	r25, 0x3F	; 63
     ee6:	01 17       	cp	r16, r17
     ee8:	41 f0       	breq	.+16     	; 0xefa <_Z18Serial_print_floatdhh+0x204>
     eea:	20 e0       	ldi	r18, 0x00	; 0
     eec:	30 e0       	ldi	r19, 0x00	; 0
     eee:	40 e2       	ldi	r20, 0x20	; 32
     ef0:	51 e4       	ldi	r21, 0x41	; 65
     ef2:	0e 94 fb 2a 	call	0x55f6	; 0x55f6 <__divsf3>
     ef6:	1f 5f       	subi	r17, 0xFF	; 255
     ef8:	f6 cf       	rjmp	.-20     	; 0xee6 <_Z18Serial_print_floatdhh+0x1f0>
     efa:	a7 01       	movw	r20, r14
     efc:	96 01       	movw	r18, r12
     efe:	0e 94 8f 2a 	call	0x551e	; 0x551e <__addsf3>
     f02:	2b 01       	movw	r4, r22
     f04:	3c 01       	movw	r6, r24
     f06:	0e 94 74 2b 	call	0x56e8	; 0x56e8 <__fixunssfsi>
     f0a:	6b 01       	movw	r12, r22
     f0c:	7c 01       	movw	r14, r24
     f0e:	2a e0       	ldi	r18, 0x0A	; 10
     f10:	ab 01       	movw	r20, r22
     f12:	bc 01       	movw	r22, r24
     f14:	89 ea       	ldi	r24, 0xA9	; 169
     f16:	92 e0       	ldi	r25, 0x02	; 2
     f18:	0e 94 f0 11 	call	0x23e0	; 0x23e0 <_ZN5Print11printNumberEmh>
     f1c:	1c 01       	movw	r2, r24
     f1e:	2a 0c       	add	r2, r10
     f20:	3b 1c       	adc	r3, r11
     f22:	00 23       	and	r16, r16
     f24:	e1 f1       	breq	.+120    	; 0xf9e <_Z18Serial_print_floatdhh+0x2a8>
     f26:	c7 01       	movw	r24, r14
     f28:	b6 01       	movw	r22, r12
     f2a:	0e 94 f3 28 	call	0x51e6	; 0x51e6 <__floatunsisf>
     f2e:	9b 01       	movw	r18, r22
     f30:	ac 01       	movw	r20, r24
     f32:	c3 01       	movw	r24, r6
     f34:	b2 01       	movw	r22, r4
     f36:	0e 94 8e 2a 	call	0x551c	; 0x551c <__subsf3>
     f3a:	4b 01       	movw	r8, r22
     f3c:	5c 01       	movw	r10, r24
     f3e:	6e e2       	ldi	r22, 0x2E	; 46
     f40:	89 ea       	ldi	r24, 0xA9	; 169
     f42:	92 e0       	ldi	r25, 0x02	; 2
     f44:	0e 94 aa 11 	call	0x2354	; 0x2354 <_ZN5Print5printEc>
     f48:	71 01       	movw	r14, r2
     f4a:	e8 0e       	add	r14, r24
     f4c:	f9 1e       	adc	r15, r25
     f4e:	20 e0       	ldi	r18, 0x00	; 0
     f50:	30 e0       	ldi	r19, 0x00	; 0
     f52:	40 e2       	ldi	r20, 0x20	; 32
     f54:	51 e4       	ldi	r21, 0x41	; 65
     f56:	c5 01       	movw	r24, r10
     f58:	b4 01       	movw	r22, r8
     f5a:	0e 94 54 29 	call	0x52a8	; 0x52a8 <__mulsf3>
     f5e:	2b 01       	movw	r4, r22
     f60:	3c 01       	movw	r6, r24
     f62:	0e 94 74 2b 	call	0x56e8	; 0x56e8 <__fixunssfsi>
     f66:	4b 01       	movw	r8, r22
     f68:	a1 2c       	mov	r10, r1
     f6a:	b1 2c       	mov	r11, r1
     f6c:	2a e0       	ldi	r18, 0x0A	; 10
     f6e:	b5 01       	movw	r22, r10
     f70:	a4 01       	movw	r20, r8
     f72:	89 ea       	ldi	r24, 0xA9	; 169
     f74:	92 e0       	ldi	r25, 0x02	; 2
     f76:	0e 94 f0 11 	call	0x23e0	; 0x23e0 <_ZN5Print11printNumberEmh>
     f7a:	e8 0e       	add	r14, r24
     f7c:	f9 1e       	adc	r15, r25
     f7e:	c5 01       	movw	r24, r10
     f80:	b4 01       	movw	r22, r8
     f82:	0e 94 f3 28 	call	0x51e6	; 0x51e6 <__floatunsisf>
     f86:	9b 01       	movw	r18, r22
     f88:	ac 01       	movw	r20, r24
     f8a:	c3 01       	movw	r24, r6
     f8c:	b2 01       	movw	r22, r4
     f8e:	0e 94 8e 2a 	call	0x551c	; 0x551c <__subsf3>
     f92:	4b 01       	movw	r8, r22
     f94:	5c 01       	movw	r10, r24
     f96:	01 50       	subi	r16, 0x01	; 1
     f98:	d1 f6       	brne	.-76     	; 0xf4e <_Z18Serial_print_floatdhh+0x258>
     f9a:	c7 01       	movw	r24, r14
     f9c:	0b c0       	rjmp	.+22     	; 0xfb4 <_Z18Serial_print_floatdhh+0x2be>
     f9e:	c1 01       	movw	r24, r2
     fa0:	09 c0       	rjmp	.+18     	; 0xfb4 <_Z18Serial_print_floatdhh+0x2be>
     fa2:	1f 5f       	subi	r17, 0xFF	; 255
     fa4:	dd ce       	rjmp	.-582    	; 0xd60 <_Z18Serial_print_floatdhh+0x6a>
     fa6:	80 81       	ld	r24, Z
     fa8:	80 33       	cpi	r24, 0x30	; 48
     faa:	09 f0       	breq	.+2      	; 0xfae <_Z18Serial_print_floatdhh+0x2b8>
     fac:	3f cf       	rjmp	.-386    	; 0xe2c <_Z18Serial_print_floatdhh+0x136>
     fae:	10 82       	st	Z, r1
     fb0:	11 50       	subi	r17, 0x01	; 1
     fb2:	37 cf       	rjmp	.-402    	; 0xe22 <_Z18Serial_print_floatdhh+0x12c>
     fb4:	a8 96       	adiw	r28, 0x28	; 40
     fb6:	0f b6       	in	r0, 0x3f	; 63
     fb8:	f8 94       	cli
     fba:	de bf       	out	0x3e, r29	; 62
     fbc:	0f be       	out	0x3f, r0	; 63
     fbe:	cd bf       	out	0x3d, r28	; 61
     fc0:	df 91       	pop	r29
     fc2:	cf 91       	pop	r28
     fc4:	1f 91       	pop	r17
     fc6:	0f 91       	pop	r16
     fc8:	ff 90       	pop	r15
     fca:	ef 90       	pop	r14
     fcc:	df 90       	pop	r13
     fce:	cf 90       	pop	r12
     fd0:	bf 90       	pop	r11
     fd2:	af 90       	pop	r10
     fd4:	9f 90       	pop	r9
     fd6:	8f 90       	pop	r8
     fd8:	7f 90       	pop	r7
     fda:	6f 90       	pop	r6
     fdc:	5f 90       	pop	r5
     fde:	4f 90       	pop	r4
     fe0:	3f 90       	pop	r3
     fe2:	2f 90       	pop	r2
     fe4:	08 95       	ret

00000fe6 <_ZN6Dimmer14disableChannelEa.isra.2.lto_priv.95>:
     fe6:	82 30       	cpi	r24, 0x02	; 2
     fe8:	41 f0       	breq	.+16     	; 0xffa <_ZN6Dimmer14disableChannelEa.isra.2.lto_priv.95+0x14>
     fea:	83 30       	cpi	r24, 0x03	; 3
     fec:	41 f0       	breq	.+16     	; 0xffe <_ZN6Dimmer14disableChannelEa.isra.2.lto_priv.95+0x18>
     fee:	81 30       	cpi	r24, 0x01	; 1
     ff0:	11 f0       	breq	.+4      	; 0xff6 <_ZN6Dimmer14disableChannelEa.isra.2.lto_priv.95+0x10>
     ff2:	5e 98       	cbi	0x0b, 6	; 11
     ff4:	08 95       	ret
     ff6:	28 98       	cbi	0x05, 0	; 5
     ff8:	08 95       	ret
     ffa:	29 98       	cbi	0x05, 1	; 5
     ffc:	08 95       	ret
     ffe:	2a 98       	cbi	0x05, 2	; 5
    1000:	08 95       	ret

00001002 <__vector_12>:
    1002:	1f 92       	push	r1
    1004:	0f 92       	push	r0
    1006:	0f b6       	in	r0, 0x3f	; 63
    1008:	0f 92       	push	r0
    100a:	11 24       	eor	r1, r1
    100c:	2f 93       	push	r18
    100e:	3f 93       	push	r19
    1010:	4f 93       	push	r20
    1012:	5f 93       	push	r21
    1014:	6f 93       	push	r22
    1016:	7f 93       	push	r23
    1018:	8f 93       	push	r24
    101a:	9f 93       	push	r25
    101c:	af 93       	push	r26
    101e:	bf 93       	push	r27
    1020:	ef 93       	push	r30
    1022:	ff 93       	push	r31
    1024:	e0 91 89 03 	lds	r30, 0x0389	; 0x800389 <pinCmpBAddr>
    1028:	f0 91 8a 03 	lds	r31, 0x038A	; 0x80038a <pinCmpBAddr+0x1>
    102c:	90 81       	ld	r25, Z
    102e:	80 91 8b 03 	lds	r24, 0x038B	; 0x80038b <pinCmpBMask>
    1032:	89 27       	eor	r24, r25
    1034:	80 83       	st	Z, r24
    1036:	80 91 0b 04 	lds	r24, 0x040B	; 0x80040b <dimmer+0x7f>
    103a:	83 30       	cpi	r24, 0x03	; 3
    103c:	19 f4       	brne	.+6      	; 0x1044 <__vector_12+0x42>
    103e:	8a e7       	ldi	r24, 0x7A	; 122
    1040:	91 e0       	ldi	r25, 0x01	; 1
    1042:	06 c0       	rjmp	.+12     	; 0x1050 <__vector_12+0x4e>
    1044:	80 91 6f 00 	lds	r24, 0x006F	; 0x80006f <__TEXT_REGION_LENGTH__+0x7e006f>
    1048:	81 ff       	sbrs	r24, 1
    104a:	05 c0       	rjmp	.+10     	; 0x1056 <__vector_12+0x54>
    104c:	89 e9       	ldi	r24, 0x99	; 153
    104e:	91 e0       	ldi	r25, 0x01	; 1
    1050:	0e 94 34 19 	call	0x3268	; 0x3268 <_ZN6Dimmer6_faultEPKc.constprop.59>
    1054:	26 c0       	rjmp	.+76     	; 0x10a2 <__vector_12+0xa0>
    1056:	80 91 8a 00 	lds	r24, 0x008A	; 0x80008a <__TEXT_REGION_LENGTH__+0x7e008a>
    105a:	90 91 8b 00 	lds	r25, 0x008B	; 0x80008b <__TEXT_REGION_LENGTH__+0x7e008b>
    105e:	90 93 08 04 	sts	0x0408, r25	; 0x800408 <dimmer+0x7c>
    1062:	80 93 07 04 	sts	0x0407, r24	; 0x800407 <dimmer+0x7b>
    1066:	82 e0       	ldi	r24, 0x02	; 2
    1068:	80 93 0b 04 	sts	0x040B, r24	; 0x80040b <dimmer+0x7f>
    106c:	80 91 8a 00 	lds	r24, 0x008A	; 0x80008a <__TEXT_REGION_LENGTH__+0x7e008a>
    1070:	90 91 8b 00 	lds	r25, 0x008B	; 0x80008b <__TEXT_REGION_LENGTH__+0x7e008b>
    1074:	80 5c       	subi	r24, 0xC0	; 192
    1076:	9f 4f       	sbci	r25, 0xFF	; 255
    1078:	90 93 89 00 	sts	0x0089, r25	; 0x800089 <__TEXT_REGION_LENGTH__+0x7e0089>
    107c:	80 93 88 00 	sts	0x0088, r24	; 0x800088 <__TEXT_REGION_LENGTH__+0x7e0088>
    1080:	b1 9a       	sbi	0x16, 1	; 22
    1082:	80 91 6f 00 	lds	r24, 0x006F	; 0x80006f <__TEXT_REGION_LENGTH__+0x7e006f>
    1086:	89 7f       	andi	r24, 0xF9	; 249
    1088:	82 60       	ori	r24, 0x02	; 2
    108a:	80 93 6f 00 	sts	0x006F, r24	; 0x80006f <__TEXT_REGION_LENGTH__+0x7e006f>
    108e:	89 e1       	ldi	r24, 0x19	; 25
    1090:	e7 ed       	ldi	r30, 0xD7	; 215
    1092:	f3 e0       	ldi	r31, 0x03	; 3
    1094:	ae eb       	ldi	r26, 0xBE	; 190
    1096:	b3 e0       	ldi	r27, 0x03	; 3
    1098:	01 90       	ld	r0, Z+
    109a:	0d 92       	st	X+, r0
    109c:	8a 95       	dec	r24
    109e:	e1 f7       	brne	.-8      	; 0x1098 <__vector_12+0x96>
    10a0:	78 94       	sei
    10a2:	ff 91       	pop	r31
    10a4:	ef 91       	pop	r30
    10a6:	bf 91       	pop	r27
    10a8:	af 91       	pop	r26
    10aa:	9f 91       	pop	r25
    10ac:	8f 91       	pop	r24
    10ae:	7f 91       	pop	r23
    10b0:	6f 91       	pop	r22
    10b2:	5f 91       	pop	r21
    10b4:	4f 91       	pop	r20
    10b6:	3f 91       	pop	r19
    10b8:	2f 91       	pop	r18
    10ba:	0f 90       	pop	r0
    10bc:	0f be       	out	0x3f, r0	; 63
    10be:	0f 90       	pop	r0
    10c0:	1f 90       	pop	r1
    10c2:	18 95       	reti

000010c4 <__vector_11>:
    10c4:	1f 92       	push	r1
    10c6:	0f 92       	push	r0
    10c8:	0f b6       	in	r0, 0x3f	; 63
    10ca:	0f 92       	push	r0
    10cc:	11 24       	eor	r1, r1
    10ce:	0f 93       	push	r16
    10d0:	1f 93       	push	r17
    10d2:	2f 93       	push	r18
    10d4:	3f 93       	push	r19
    10d6:	4f 93       	push	r20
    10d8:	5f 93       	push	r21
    10da:	6f 93       	push	r22
    10dc:	7f 93       	push	r23
    10de:	8f 93       	push	r24
    10e0:	9f 93       	push	r25
    10e2:	af 93       	push	r26
    10e4:	bf 93       	push	r27
    10e6:	cf 93       	push	r28
    10e8:	df 93       	push	r29
    10ea:	ef 93       	push	r30
    10ec:	ff 93       	push	r31
    10ee:	80 91 0b 04 	lds	r24, 0x040B	; 0x80040b <dimmer+0x7f>
    10f2:	82 30       	cpi	r24, 0x02	; 2
    10f4:	99 f0       	breq	.+38     	; 0x111c <__vector_11+0x58>
    10f6:	83 30       	cpi	r24, 0x03	; 3
    10f8:	09 f0       	breq	.+2      	; 0x10fc <__vector_11+0x38>
    10fa:	aa c0       	rjmp	.+340    	; 0x1250 <__vector_11+0x18c>
    10fc:	00 91 88 00 	lds	r16, 0x0088	; 0x800088 <__TEXT_REGION_LENGTH__+0x7e0088>
    1100:	10 91 89 00 	lds	r17, 0x0089	; 0x800089 <__TEXT_REGION_LENGTH__+0x7e0089>
    1104:	78 94       	sei
    1106:	c0 91 bc 03 	lds	r28, 0x03BC	; 0x8003bc <dimmer+0x30>
    110a:	d0 91 bd 03 	lds	r29, 0x03BD	; 0x8003bd <dimmer+0x31>
    110e:	ce 01       	movw	r24, r28
    1110:	05 96       	adiw	r24, 0x05	; 5
    1112:	90 93 bd 03 	sts	0x03BD, r25	; 0x8003bd <dimmer+0x31>
    1116:	80 93 bc 03 	sts	0x03BC, r24	; 0x8003bc <dimmer+0x30>
    111a:	5d c0       	rjmp	.+186    	; 0x11d6 <__vector_11+0x112>
    111c:	83 e0       	ldi	r24, 0x03	; 3
    111e:	80 93 0b 04 	sts	0x040B, r24	; 0x80040b <dimmer+0x7f>
    1122:	78 94       	sei
    1124:	20 91 bf 03 	lds	r18, 0x03BF	; 0x8003bf <dimmer+0x33>
    1128:	30 91 c0 03 	lds	r19, 0x03C0	; 0x8003c0 <dimmer+0x34>
    112c:	21 15       	cp	r18, r1
    112e:	31 05       	cpc	r19, r1
    1130:	b9 f1       	breq	.+110    	; 0x11a0 <__vector_11+0xdc>
    1132:	8e eb       	ldi	r24, 0xBE	; 190
    1134:	93 e0       	ldi	r25, 0x03	; 3
    1136:	90 93 bd 03 	sts	0x03BD, r25	; 0x8003bd <dimmer+0x31>
    113a:	80 93 bc 03 	sts	0x03BC, r24	; 0x8003bc <dimmer+0x30>
    113e:	80 91 88 00 	lds	r24, 0x0088	; 0x800088 <__TEXT_REGION_LENGTH__+0x7e0088>
    1142:	90 91 89 00 	lds	r25, 0x0089	; 0x800089 <__TEXT_REGION_LENGTH__+0x7e0089>
    1146:	82 0f       	add	r24, r18
    1148:	93 1f       	adc	r25, r19
    114a:	90 93 89 00 	sts	0x0089, r25	; 0x800089 <__TEXT_REGION_LENGTH__+0x7e0089>
    114e:	80 93 88 00 	sts	0x0088, r24	; 0x800088 <__TEXT_REGION_LENGTH__+0x7e0088>
    1152:	ec e8       	ldi	r30, 0x8C	; 140
    1154:	f3 e0       	ldi	r31, 0x03	; 3
    1156:	82 a9       	ldd	r24, Z+50	; 0x32
    1158:	82 30       	cpi	r24, 0x02	; 2
    115a:	51 f0       	breq	.+20     	; 0x1170 <__vector_11+0xac>
    115c:	83 30       	cpi	r24, 0x03	; 3
    115e:	51 f0       	breq	.+20     	; 0x1174 <__vector_11+0xb0>
    1160:	81 30       	cpi	r24, 0x01	; 1
    1162:	21 f0       	breq	.+8      	; 0x116c <__vector_11+0xa8>
    1164:	8b b1       	in	r24, 0x0b	; 11
    1166:	86 60       	ori	r24, 0x06	; 6
    1168:	8b b9       	out	0x0b, r24	; 11
    116a:	05 c0       	rjmp	.+10     	; 0x1176 <__vector_11+0xb2>
    116c:	28 9a       	sbi	0x05, 0	; 5
    116e:	03 c0       	rjmp	.+6      	; 0x1176 <__vector_11+0xb2>
    1170:	29 9a       	sbi	0x05, 1	; 5
    1172:	01 c0       	rjmp	.+2      	; 0x1176 <__vector_11+0xb2>
    1174:	2a 9a       	sbi	0x05, 2	; 5
    1176:	35 96       	adiw	r30, 0x05	; 5
    1178:	83 a9       	ldd	r24, Z+51	; 0x33
    117a:	94 a9       	ldd	r25, Z+52	; 0x34
    117c:	89 2b       	or	r24, r25
    117e:	59 f7       	brne	.-42     	; 0x1156 <__vector_11+0x92>
    1180:	0d e1       	ldi	r16, 0x1D	; 29
    1182:	14 e0       	ldi	r17, 0x04	; 4
    1184:	c0 e0       	ldi	r28, 0x00	; 0
    1186:	f8 01       	movw	r30, r16
    1188:	81 91       	ld	r24, Z+
    118a:	91 91       	ld	r25, Z+
    118c:	8f 01       	movw	r16, r30
    118e:	89 2b       	or	r24, r25
    1190:	19 f4       	brne	.+6      	; 0x1198 <__vector_11+0xd4>
    1192:	8c 2f       	mov	r24, r28
    1194:	0e 94 f3 07 	call	0xfe6	; 0xfe6 <_ZN6Dimmer14disableChannelEa.isra.2.lto_priv.95>
    1198:	cf 5f       	subi	r28, 0xFF	; 255
    119a:	c4 30       	cpi	r28, 0x04	; 4
    119c:	a1 f7       	brne	.-24     	; 0x1186 <__vector_11+0xc2>
    119e:	5c c0       	rjmp	.+184    	; 0x1258 <__vector_11+0x194>
    11a0:	80 e0       	ldi	r24, 0x00	; 0
    11a2:	0e 94 f3 07 	call	0xfe6	; 0xfe6 <_ZN6Dimmer14disableChannelEa.isra.2.lto_priv.95>
    11a6:	81 e0       	ldi	r24, 0x01	; 1
    11a8:	0e 94 f3 07 	call	0xfe6	; 0xfe6 <_ZN6Dimmer14disableChannelEa.isra.2.lto_priv.95>
    11ac:	82 e0       	ldi	r24, 0x02	; 2
    11ae:	0e 94 f3 07 	call	0xfe6	; 0xfe6 <_ZN6Dimmer14disableChannelEa.isra.2.lto_priv.95>
    11b2:	83 e0       	ldi	r24, 0x03	; 3
    11b4:	0e 94 f3 07 	call	0xfe6	; 0xfe6 <_ZN6Dimmer14disableChannelEa.isra.2.lto_priv.95>
    11b8:	0e 94 a6 1a 	call	0x354c	; 0x354c <_ZN6Dimmer12_endHalfwaveEv.constprop.55>
    11bc:	4d c0       	rjmp	.+154    	; 0x1258 <__vector_11+0x194>
    11be:	29 81       	ldd	r18, Y+1	; 0x01
    11c0:	3a 81       	ldd	r19, Y+2	; 0x02
    11c2:	28 17       	cp	r18, r24
    11c4:	39 07       	cpc	r19, r25
    11c6:	e8 f0       	brcs	.+58     	; 0x1202 <__vector_11+0x13e>
    11c8:	cf 01       	movw	r24, r30
    11ca:	05 96       	adiw	r24, 0x05	; 5
    11cc:	90 93 bd 03 	sts	0x03BD, r25	; 0x8003bd <dimmer+0x31>
    11d0:	80 93 bc 03 	sts	0x03BC, r24	; 0x8003bc <dimmer+0x30>
    11d4:	ef 01       	movw	r28, r30
    11d6:	88 81       	ld	r24, Y
    11d8:	0e 94 f3 07 	call	0xfe6	; 0xfe6 <_ZN6Dimmer14disableChannelEa.isra.2.lto_priv.95>
    11dc:	80 91 88 00 	lds	r24, 0x0088	; 0x800088 <__TEXT_REGION_LENGTH__+0x7e0088>
    11e0:	90 91 89 00 	lds	r25, 0x0089	; 0x800089 <__TEXT_REGION_LENGTH__+0x7e0089>
    11e4:	9c 83       	std	Y+4, r25	; 0x04
    11e6:	8b 83       	std	Y+3, r24	; 0x03
    11e8:	e0 91 bc 03 	lds	r30, 0x03BC	; 0x8003bc <dimmer+0x30>
    11ec:	f0 91 bd 03 	lds	r31, 0x03BD	; 0x8003bd <dimmer+0x31>
    11f0:	81 81       	ldd	r24, Z+1	; 0x01
    11f2:	92 81       	ldd	r25, Z+2	; 0x02
    11f4:	9c 01       	movw	r18, r24
    11f6:	21 50       	subi	r18, 0x01	; 1
    11f8:	31 09       	sbc	r19, r1
    11fa:	2e 3f       	cpi	r18, 0xFE	; 254
    11fc:	3f 4f       	sbci	r19, 0xFF	; 255
    11fe:	f8 f2       	brcs	.-66     	; 0x11be <__vector_11+0xfa>
    1200:	db cf       	rjmp	.-74     	; 0x11b8 <__vector_11+0xf4>
    1202:	80 0f       	add	r24, r16
    1204:	91 1f       	adc	r25, r17
    1206:	f8 94       	cli
    1208:	e0 91 84 00 	lds	r30, 0x0084	; 0x800084 <__TEXT_REGION_LENGTH__+0x7e0084>
    120c:	f0 91 85 00 	lds	r31, 0x0085	; 0x800085 <__TEXT_REGION_LENGTH__+0x7e0085>
    1210:	af 01       	movw	r20, r30
    1212:	60 e0       	ldi	r22, 0x00	; 0
    1214:	70 e0       	ldi	r23, 0x00	; 0
    1216:	e0 17       	cp	r30, r16
    1218:	f1 07       	cpc	r31, r17
    121a:	10 f4       	brcc	.+4      	; 0x1220 <__vector_11+0x15c>
    121c:	6f 5f       	subi	r22, 0xFF	; 255
    121e:	7f 4f       	sbci	r23, 0xFF	; 255
    1220:	82 1b       	sub	r24, r18
    1222:	93 0b       	sbc	r25, r19
    1224:	9c 01       	movw	r18, r24
    1226:	24 1b       	sub	r18, r20
    1228:	35 0b       	sbc	r19, r21
    122a:	29 30       	cpi	r18, 0x09	; 9
    122c:	31 05       	cpc	r19, r1
    122e:	14 f4       	brge	.+4      	; 0x1234 <__vector_11+0x170>
    1230:	ca 01       	movw	r24, r20
    1232:	09 96       	adiw	r24, 0x09	; 9
    1234:	90 93 89 00 	sts	0x0089, r25	; 0x800089 <__TEXT_REGION_LENGTH__+0x7e0089>
    1238:	80 93 88 00 	sts	0x0088, r24	; 0x800088 <__TEXT_REGION_LENGTH__+0x7e0088>
    123c:	80 91 88 00 	lds	r24, 0x0088	; 0x800088 <__TEXT_REGION_LENGTH__+0x7e0088>
    1240:	90 91 89 00 	lds	r25, 0x0089	; 0x800089 <__TEXT_REGION_LENGTH__+0x7e0089>
    1244:	90 93 0a 04 	sts	0x040A, r25	; 0x80040a <dimmer+0x7e>
    1248:	80 93 09 04 	sts	0x0409, r24	; 0x800409 <dimmer+0x7d>
    124c:	78 94       	sei
    124e:	04 c0       	rjmp	.+8      	; 0x1258 <__vector_11+0x194>
    1250:	80 eb       	ldi	r24, 0xB0	; 176
    1252:	91 e0       	ldi	r25, 0x01	; 1
    1254:	0e 94 34 19 	call	0x3268	; 0x3268 <_ZN6Dimmer6_faultEPKc.constprop.59>
    1258:	ff 91       	pop	r31
    125a:	ef 91       	pop	r30
    125c:	df 91       	pop	r29
    125e:	cf 91       	pop	r28
    1260:	bf 91       	pop	r27
    1262:	af 91       	pop	r26
    1264:	9f 91       	pop	r25
    1266:	8f 91       	pop	r24
    1268:	7f 91       	pop	r23
    126a:	6f 91       	pop	r22
    126c:	5f 91       	pop	r21
    126e:	4f 91       	pop	r20
    1270:	3f 91       	pop	r19
    1272:	2f 91       	pop	r18
    1274:	1f 91       	pop	r17
    1276:	0f 91       	pop	r16
    1278:	0f 90       	pop	r0
    127a:	0f be       	out	0x3f, r0	; 63
    127c:	0f 90       	pop	r0
    127e:	1f 90       	pop	r1
    1280:	18 95       	reti

00001282 <__vector_13>:
    1282:	1f 92       	push	r1
    1284:	0f 92       	push	r0
    1286:	0f b6       	in	r0, 0x3f	; 63
    1288:	0f 92       	push	r0
    128a:	11 24       	eor	r1, r1
    128c:	8f 93       	push	r24
    128e:	9f 93       	push	r25
    1290:	af 93       	push	r26
    1292:	bf 93       	push	r27
    1294:	ef 93       	push	r30
    1296:	ff 93       	push	r31
    1298:	ea ef       	ldi	r30, 0xFA	; 250
    129a:	f3 e0       	ldi	r31, 0x03	; 3
    129c:	80 81       	ld	r24, Z
    129e:	91 81       	ldd	r25, Z+1	; 0x01
    12a0:	a2 81       	ldd	r26, Z+2	; 0x02
    12a2:	b3 81       	ldd	r27, Z+3	; 0x03
    12a4:	11 96       	adiw	r26, 0x01	; 1
    12a6:	80 83       	st	Z, r24
    12a8:	91 83       	std	Z+1, r25	; 0x01
    12aa:	a2 83       	std	Z+2, r26	; 0x02
    12ac:	b3 83       	std	Z+3, r27	; 0x03
    12ae:	ff 91       	pop	r31
    12b0:	ef 91       	pop	r30
    12b2:	bf 91       	pop	r27
    12b4:	af 91       	pop	r26
    12b6:	9f 91       	pop	r25
    12b8:	8f 91       	pop	r24
    12ba:	0f 90       	pop	r0
    12bc:	0f be       	out	0x3f, r0	; 63
    12be:	0f 90       	pop	r0
    12c0:	1f 90       	pop	r1
    12c2:	18 95       	reti

000012c4 <_Z12crc16_updatejPKhj>:
    12c4:	fb 01       	movw	r30, r22
    12c6:	46 0f       	add	r20, r22
    12c8:	57 1f       	adc	r21, r23
    12ca:	e4 17       	cp	r30, r20
    12cc:	f5 07       	cpc	r31, r21
    12ce:	91 f0       	breq	.+36     	; 0x12f4 <_Z12crc16_updatejPKhj+0x30>
    12d0:	21 91       	ld	r18, Z+
    12d2:	82 27       	eor	r24, r18
    12d4:	28 e0       	ldi	r18, 0x08	; 8
    12d6:	bc 01       	movw	r22, r24
    12d8:	76 95       	lsr	r23
    12da:	67 95       	ror	r22
    12dc:	80 ff       	sbrs	r24, 0
    12de:	06 c0       	rjmp	.+12     	; 0x12ec <_Z12crc16_updatejPKhj+0x28>
    12e0:	cb 01       	movw	r24, r22
    12e2:	31 e0       	ldi	r19, 0x01	; 1
    12e4:	83 27       	eor	r24, r19
    12e6:	30 ea       	ldi	r19, 0xA0	; 160
    12e8:	93 27       	eor	r25, r19
    12ea:	01 c0       	rjmp	.+2      	; 0x12ee <_Z12crc16_updatejPKhj+0x2a>
    12ec:	cb 01       	movw	r24, r22
    12ee:	21 50       	subi	r18, 0x01	; 1
    12f0:	91 f7       	brne	.-28     	; 0x12d6 <_Z12crc16_updatejPKhj+0x12>
    12f2:	eb cf       	rjmp	.-42     	; 0x12ca <_Z12crc16_updatejPKhj+0x6>
    12f4:	08 95       	ret

000012f6 <_ZN11EEPROMClass3getIA4_iEERT_iS3_.isra.3.lto_priv.102>:
    12f6:	cf 92       	push	r12
    12f8:	df 92       	push	r13
    12fa:	ef 92       	push	r14
    12fc:	ff 92       	push	r15
    12fe:	0f 93       	push	r16
    1300:	1f 93       	push	r17
    1302:	cf 93       	push	r28
    1304:	df 93       	push	r29
    1306:	eb 01       	movw	r28, r22
    1308:	7b 01       	movw	r14, r22
    130a:	28 e0       	ldi	r18, 0x08	; 8
    130c:	e2 0e       	add	r14, r18
    130e:	f1 1c       	adc	r15, r1
    1310:	8b 01       	movw	r16, r22
    1312:	6c 01       	movw	r12, r24
    1314:	c6 1a       	sub	r12, r22
    1316:	d7 0a       	sbc	r13, r23
    1318:	c6 01       	movw	r24, r12
    131a:	80 0f       	add	r24, r16
    131c:	91 1f       	adc	r25, r17
    131e:	0e 94 12 2a 	call	0x5424	; 0x5424 <eeprom_read_byte>
    1322:	f8 01       	movw	r30, r16
    1324:	81 93       	st	Z+, r24
    1326:	8f 01       	movw	r16, r30
    1328:	ee 15       	cp	r30, r14
    132a:	ff 05       	cpc	r31, r15
    132c:	a9 f7       	brne	.-22     	; 0x1318 <_ZN11EEPROMClass3getIA4_iEERT_iS3_.isra.3.lto_priv.102+0x22>
    132e:	ce 01       	movw	r24, r28
    1330:	df 91       	pop	r29
    1332:	cf 91       	pop	r28
    1334:	1f 91       	pop	r17
    1336:	0f 91       	pop	r16
    1338:	ff 90       	pop	r15
    133a:	ef 90       	pop	r14
    133c:	df 90       	pop	r13
    133e:	cf 90       	pop	r12
    1340:	08 95       	ret

00001342 <_ZN11EEPROMClass3getIjEERT_iS2_.isra.2.lto_priv.101>:
    1342:	0f 93       	push	r16
    1344:	1f 93       	push	r17
    1346:	cf 93       	push	r28
    1348:	df 93       	push	r29
    134a:	8c 01       	movw	r16, r24
    134c:	eb 01       	movw	r28, r22
    134e:	0e 94 12 2a 	call	0x5424	; 0x5424 <eeprom_read_byte>
    1352:	88 83       	st	Y, r24
    1354:	c8 01       	movw	r24, r16
    1356:	01 96       	adiw	r24, 0x01	; 1
    1358:	0e 94 12 2a 	call	0x5424	; 0x5424 <eeprom_read_byte>
    135c:	89 83       	std	Y+1, r24	; 0x01
    135e:	ce 01       	movw	r24, r28
    1360:	df 91       	pop	r29
    1362:	cf 91       	pop	r28
    1364:	1f 91       	pop	r17
    1366:	0f 91       	pop	r16
    1368:	08 95       	ret

0000136a <_Z13_write_configb>:
    136a:	cf 92       	push	r12
    136c:	df 92       	push	r13
    136e:	ef 92       	push	r14
    1370:	ff 92       	push	r15
    1372:	0f 93       	push	r16
    1374:	1f 93       	push	r17
    1376:	cf 93       	push	r28
    1378:	df 93       	push	r29
    137a:	cd b7       	in	r28, 0x3d	; 61
    137c:	de b7       	in	r29, 0x3e	; 62
    137e:	2f 97       	sbiw	r28, 0x0f	; 15
    1380:	0f b6       	in	r0, 0x3f	; 63
    1382:	f8 94       	cli
    1384:	de bf       	out	0x3e, r29	; 62
    1386:	0f be       	out	0x3f, r0	; 63
    1388:	cd bf       	out	0x3d, r28	; 61
    138a:	18 2f       	mov	r17, r24
    138c:	88 e0       	ldi	r24, 0x08	; 8
    138e:	ed e1       	ldi	r30, 0x1D	; 29
    1390:	f4 e0       	ldi	r31, 0x04	; 4
    1392:	a2 e9       	ldi	r26, 0x92	; 146
    1394:	b4 e0       	ldi	r27, 0x04	; 4
    1396:	01 90       	ld	r0, Z+
    1398:	0d 92       	st	X+, r0
    139a:	8a 95       	dec	r24
    139c:	e1 f7       	brne	.-8      	; 0x1396 <_Z13_write_configb+0x2c>
    139e:	0e 94 08 18 	call	0x3010	; 0x3010 <_ZNK13ConfigStorage3crcEv.constprop.83>
    13a2:	90 93 91 04 	sts	0x0491, r25	; 0x800491 <config+0x5>
    13a6:	80 93 90 04 	sts	0x0490, r24	; 0x800490 <config+0x4>
    13aa:	11 11       	cpse	r17, r1
    13ac:	d7 c0       	rjmp	.+430    	; 0x155c <_Z13_write_configb+0x1f2>
    13ae:	00 91 8c 02 	lds	r16, 0x028C	; 0x80028c <eeprom_position>
    13b2:	10 91 8d 02 	lds	r17, 0x028D	; 0x80028d <eeprom_position+0x1>
    13b6:	be 01       	movw	r22, r28
    13b8:	6f 5f       	subi	r22, 0xFF	; 255
    13ba:	7f 4f       	sbci	r23, 0xFF	; 255
    13bc:	c8 01       	movw	r24, r16
    13be:	0e 94 95 12 	call	0x252a	; 0x252a <_ZN11EEPROMClass3getImEERT_iS2_.isra.1.lto_priv.100>
    13c2:	40 91 8c 04 	lds	r20, 0x048C	; 0x80048c <config>
    13c6:	50 91 8d 04 	lds	r21, 0x048D	; 0x80048d <config+0x1>
    13ca:	60 91 8e 04 	lds	r22, 0x048E	; 0x80048e <config+0x2>
    13ce:	70 91 8f 04 	lds	r23, 0x048F	; 0x80048f <config+0x3>
    13d2:	89 81       	ldd	r24, Y+1	; 0x01
    13d4:	9a 81       	ldd	r25, Y+2	; 0x02
    13d6:	ab 81       	ldd	r26, Y+3	; 0x03
    13d8:	bc 81       	ldd	r27, Y+4	; 0x04
    13da:	48 17       	cp	r20, r24
    13dc:	59 07       	cpc	r21, r25
    13de:	6a 07       	cpc	r22, r26
    13e0:	7b 07       	cpc	r23, r27
    13e2:	09 f0       	breq	.+2      	; 0x13e6 <_Z13_write_configb+0x7c>
    13e4:	bb c0       	rjmp	.+374    	; 0x155c <_Z13_write_configb+0x1f2>
    13e6:	be 01       	movw	r22, r28
    13e8:	6f 5f       	subi	r22, 0xFF	; 255
    13ea:	7f 4f       	sbci	r23, 0xFF	; 255
    13ec:	c8 01       	movw	r24, r16
    13ee:	04 96       	adiw	r24, 0x04	; 4
    13f0:	0e 94 a1 09 	call	0x1342	; 0x1342 <_ZN11EEPROMClass3getIjEERT_iS2_.isra.2.lto_priv.101>
    13f4:	20 91 90 04 	lds	r18, 0x0490	; 0x800490 <config+0x4>
    13f8:	30 91 91 04 	lds	r19, 0x0491	; 0x800491 <config+0x5>
    13fc:	89 81       	ldd	r24, Y+1	; 0x01
    13fe:	9a 81       	ldd	r25, Y+2	; 0x02
    1400:	28 17       	cp	r18, r24
    1402:	39 07       	cpc	r19, r25
    1404:	09 f0       	breq	.+2      	; 0x1408 <_Z13_write_configb+0x9e>
    1406:	aa c0       	rjmp	.+340    	; 0x155c <_Z13_write_configb+0x1f2>
    1408:	be 01       	movw	r22, r28
    140a:	6f 5f       	subi	r22, 0xFF	; 255
    140c:	7f 4f       	sbci	r23, 0xFF	; 255
    140e:	c8 01       	movw	r24, r16
    1410:	06 96       	adiw	r24, 0x06	; 6
    1412:	0e 94 7b 09 	call	0x12f6	; 0x12f6 <_ZN11EEPROMClass3getIA4_iEERT_iS3_.isra.3.lto_priv.102>
    1416:	48 e0       	ldi	r20, 0x08	; 8
    1418:	50 e0       	ldi	r21, 0x00	; 0
    141a:	62 e9       	ldi	r22, 0x92	; 146
    141c:	74 e0       	ldi	r23, 0x04	; 4
    141e:	ce 01       	movw	r24, r28
    1420:	01 96       	adiw	r24, 0x01	; 1
    1422:	0e 94 1e 2e 	call	0x5c3c	; 0x5c3c <memcmp>
    1426:	89 2b       	or	r24, r25
    1428:	09 f0       	breq	.+2      	; 0x142c <_Z13_write_configb+0xc2>
    142a:	98 c0       	rjmp	.+304    	; 0x155c <_Z13_write_configb+0x1f2>
    142c:	78 01       	movw	r14, r16
    142e:	4e e0       	ldi	r20, 0x0E	; 14
    1430:	e4 0e       	add	r14, r20
    1432:	f1 1c       	adc	r15, r1
    1434:	83 e3       	ldi	r24, 0x33	; 51
    1436:	c8 2e       	mov	r12, r24
    1438:	84 e0       	ldi	r24, 0x04	; 4
    143a:	d8 2e       	mov	r13, r24
    143c:	0e 5d       	subi	r16, 0xDE	; 222
    143e:	1f 4f       	sbci	r17, 0xFF	; 255
    1440:	c7 01       	movw	r24, r14
    1442:	0e 94 12 2a 	call	0x5424	; 0x5424 <eeprom_read_byte>
    1446:	f6 01       	movw	r30, r12
    1448:	91 91       	ld	r25, Z+
    144a:	6f 01       	movw	r12, r30
    144c:	98 13       	cpse	r25, r24
    144e:	86 c0       	rjmp	.+268    	; 0x155c <_Z13_write_configb+0x1f2>
    1450:	ff ef       	ldi	r31, 0xFF	; 255
    1452:	ef 1a       	sub	r14, r31
    1454:	ff 0a       	sbc	r15, r31
    1456:	0e 15       	cp	r16, r14
    1458:	1f 05       	cpc	r17, r15
    145a:	91 f7       	brne	.-28     	; 0x1440 <_Z13_write_configb+0xd6>
    145c:	0e 94 99 0e 	call	0x1d32	; 0x1d32 <millis>
    1460:	60 93 00 01 	sts	0x0100, r22	; 0x800100 <__data_start>
    1464:	70 93 01 01 	sts	0x0101, r23	; 0x800101 <__data_start+0x1>
    1468:	80 93 02 01 	sts	0x0102, r24	; 0x800102 <__data_start+0x2>
    146c:	90 93 03 01 	sts	0x0103, r25	; 0x800103 <__data_start+0x3>
    1470:	1f 86       	std	Y+15, r1	; 0x0f
    1472:	80 91 97 02 	lds	r24, 0x0297	; 0x800297 <dimmer_scheduled_calls>
    1476:	87 7f       	andi	r24, 0xF7	; 247
    1478:	80 93 97 02 	sts	0x0297, r24	; 0x800297 <dimmer_scheduled_calls>
    147c:	80 91 8c 04 	lds	r24, 0x048C	; 0x80048c <config>
    1480:	90 91 8d 04 	lds	r25, 0x048D	; 0x80048d <config+0x1>
    1484:	a0 91 8e 04 	lds	r26, 0x048E	; 0x80048e <config+0x2>
    1488:	b0 91 8f 04 	lds	r27, 0x048F	; 0x80048f <config+0x3>
    148c:	89 87       	std	Y+9, r24	; 0x09
    148e:	9a 87       	std	Y+10, r25	; 0x0a
    1490:	ab 87       	std	Y+11, r26	; 0x0b
    1492:	bc 87       	std	Y+12, r27	; 0x0c
    1494:	80 91 8c 02 	lds	r24, 0x028C	; 0x80028c <eeprom_position>
    1498:	90 91 8d 02 	lds	r25, 0x028D	; 0x80028d <eeprom_position+0x1>
    149c:	9e 87       	std	Y+14, r25	; 0x0e
    149e:	8d 87       	std	Y+13, r24	; 0x0d
    14a0:	88 e1       	ldi	r24, 0x18	; 24
    14a2:	0e 94 a0 1c 	call	0x3940	; 0x3940 <_ZN13SerialTwoWire17beginTransmissionEh.constprop.22>
    14a6:	83 ef       	ldi	r24, 0xF3	; 243
    14a8:	90 e0       	ldi	r25, 0x00	; 0
    14aa:	0e 94 99 1c 	call	0x3932	; 0x3932 <_ZN13SerialTwoWire5writeEi.constprop.23>
    14ae:	47 e0       	ldi	r20, 0x07	; 7
    14b0:	50 e0       	ldi	r21, 0x00	; 0
    14b2:	be 01       	movw	r22, r28
    14b4:	67 5f       	subi	r22, 0xF7	; 247
    14b6:	7f 4f       	sbci	r23, 0xFF	; 255
    14b8:	86 e4       	ldi	r24, 0x46	; 70
    14ba:	93 e0       	ldi	r25, 0x03	; 3
    14bc:	0e 94 7b 11 	call	0x22f6	; 0x22f6 <_ZN13SerialTwoWire5writeEPKhj>
    14c0:	0e 94 57 1c 	call	0x38ae	; 0x38ae <_ZN13SerialTwoWire15endTransmissionEh.constprop.25>
    14c4:	e0 91 8c 02 	lds	r30, 0x028C	; 0x80028c <eeprom_position>
    14c8:	f0 91 8d 02 	lds	r31, 0x028D	; 0x80028d <eeprom_position+0x1>
    14cc:	c9 84       	ldd	r12, Y+9	; 0x09
    14ce:	da 84       	ldd	r13, Y+10	; 0x0a
    14d0:	eb 84       	ldd	r14, Y+11	; 0x0b
    14d2:	fc 84       	ldd	r15, Y+12	; 0x0c
    14d4:	80 91 91 04 	lds	r24, 0x0491	; 0x800491 <config+0x5>
    14d8:	8f 93       	push	r24
    14da:	80 91 90 04 	lds	r24, 0x0490	; 0x800490 <config+0x4>
    14de:	8f 93       	push	r24
    14e0:	8f 85       	ldd	r24, Y+15	; 0x0f
    14e2:	1f 92       	push	r1
    14e4:	8f 93       	push	r24
    14e6:	a7 01       	movw	r20, r14
    14e8:	96 01       	movw	r18, r12
    14ea:	21 50       	subi	r18, 0x01	; 1
    14ec:	31 09       	sbc	r19, r1
    14ee:	41 09       	sbc	r20, r1
    14f0:	51 09       	sbc	r21, r1
    14f2:	ae e1       	ldi	r26, 0x1E	; 30
    14f4:	b0 e0       	ldi	r27, 0x00	; 0
    14f6:	0e 94 5a 2a 	call	0x54b4	; 0x54b4 <__muluhisi3>
    14fa:	8b 01       	movw	r16, r22
    14fc:	9c 01       	movw	r18, r24
    14fe:	cf 01       	movw	r24, r30
    1500:	62 e2       	ldi	r22, 0x22	; 34
    1502:	70 e0       	ldi	r23, 0x00	; 0
    1504:	0e 94 74 2a 	call	0x54e8	; 0x54e8 <__udivmodhi4>
    1508:	d9 01       	movw	r26, r18
    150a:	c8 01       	movw	r24, r16
    150c:	86 0f       	add	r24, r22
    150e:	97 1f       	adc	r25, r23
    1510:	a1 1d       	adc	r26, r1
    1512:	b1 1d       	adc	r27, r1
    1514:	bf 93       	push	r27
    1516:	af 93       	push	r26
    1518:	9f 93       	push	r25
    151a:	8f 93       	push	r24
    151c:	ff 93       	push	r31
    151e:	ef 93       	push	r30
    1520:	ff 92       	push	r15
    1522:	ef 92       	push	r14
    1524:	df 92       	push	r13
    1526:	cf 92       	push	r12
    1528:	8a e0       	ldi	r24, 0x0A	; 10
    152a:	92 e0       	ldi	r25, 0x02	; 2
    152c:	9f 93       	push	r25
    152e:	8f 93       	push	r24
    1530:	0e 94 a8 05 	call	0xb50	; 0xb50 <_Z15Serial_printf_PPKcz>
    1534:	0f b6       	in	r0, 0x3f	; 63
    1536:	f8 94       	cli
    1538:	de bf       	out	0x3e, r29	; 62
    153a:	0f be       	out	0x3f, r0	; 63
    153c:	cd bf       	out	0x3d, r28	; 61
    153e:	2f 96       	adiw	r28, 0x0f	; 15
    1540:	0f b6       	in	r0, 0x3f	; 63
    1542:	f8 94       	cli
    1544:	de bf       	out	0x3e, r29	; 62
    1546:	0f be       	out	0x3f, r0	; 63
    1548:	cd bf       	out	0x3d, r28	; 61
    154a:	df 91       	pop	r29
    154c:	cf 91       	pop	r28
    154e:	1f 91       	pop	r17
    1550:	0f 91       	pop	r16
    1552:	ff 90       	pop	r15
    1554:	ef 90       	pop	r14
    1556:	df 90       	pop	r13
    1558:	cf 90       	pop	r12
    155a:	08 95       	ret
    155c:	80 91 8c 02 	lds	r24, 0x028C	; 0x80028c <eeprom_position>
    1560:	90 91 8d 02 	lds	r25, 0x028D	; 0x80028d <eeprom_position+0x1>
    1564:	9c 01       	movw	r18, r24
    1566:	2c 5b       	subi	r18, 0xBC	; 188
    1568:	3f 4f       	sbci	r19, 0xFF	; 255
    156a:	21 15       	cp	r18, r1
    156c:	34 40       	sbci	r19, 0x04	; 4
    156e:	30 f4       	brcc	.+12     	; 0x157c <_Z13_write_configb+0x212>
    1570:	82 96       	adiw	r24, 0x22	; 34
    1572:	90 93 8d 02 	sts	0x028D, r25	; 0x80028d <eeprom_position+0x1>
    1576:	80 93 8c 02 	sts	0x028C, r24	; 0x80028c <eeprom_position>
    157a:	17 c0       	rjmp	.+46     	; 0x15aa <_Z13_write_configb+0x240>
    157c:	10 92 8d 02 	sts	0x028D, r1	; 0x80028d <eeprom_position+0x1>
    1580:	10 92 8c 02 	sts	0x028C, r1	; 0x80028c <eeprom_position>
    1584:	80 91 8c 04 	lds	r24, 0x048C	; 0x80048c <config>
    1588:	90 91 8d 04 	lds	r25, 0x048D	; 0x80048d <config+0x1>
    158c:	a0 91 8e 04 	lds	r26, 0x048E	; 0x80048e <config+0x2>
    1590:	b0 91 8f 04 	lds	r27, 0x048F	; 0x80048f <config+0x3>
    1594:	01 96       	adiw	r24, 0x01	; 1
    1596:	a1 1d       	adc	r26, r1
    1598:	b1 1d       	adc	r27, r1
    159a:	80 93 8c 04 	sts	0x048C, r24	; 0x80048c <config>
    159e:	90 93 8d 04 	sts	0x048D, r25	; 0x80048d <config+0x1>
    15a2:	a0 93 8e 04 	sts	0x048E, r26	; 0x80048e <config+0x2>
    15a6:	b0 93 8f 04 	sts	0x048F, r27	; 0x80048f <config+0x3>
    15aa:	80 91 8c 02 	lds	r24, 0x028C	; 0x80028c <eeprom_position>
    15ae:	90 91 8d 02 	lds	r25, 0x028D	; 0x80028d <eeprom_position+0x1>
    15b2:	0e 94 8f 17 	call	0x2f1e	; 0x2f1e <_ZN13ConfigStorage5writeEj.constprop.86>
    15b6:	9f 85       	ldd	r25, Y+15	; 0x0f
    15b8:	89 0f       	add	r24, r25
    15ba:	8f 87       	std	Y+15, r24	; 0x0f
    15bc:	0e 94 99 0e 	call	0x1d32	; 0x1d32 <millis>
    15c0:	60 93 00 01 	sts	0x0100, r22	; 0x800100 <__data_start>
    15c4:	70 93 01 01 	sts	0x0101, r23	; 0x800101 <__data_start+0x1>
    15c8:	80 93 02 01 	sts	0x0102, r24	; 0x800102 <__data_start+0x2>
    15cc:	90 93 03 01 	sts	0x0103, r25	; 0x800103 <__data_start+0x3>
    15d0:	50 cf       	rjmp	.-352    	; 0x1472 <_Z13_write_configb+0x108>

000015d2 <_Z22_dimmer_i2c_on_receivei>:
    15d2:	2f 92       	push	r2
    15d4:	3f 92       	push	r3
    15d6:	4f 92       	push	r4
    15d8:	5f 92       	push	r5
    15da:	6f 92       	push	r6
    15dc:	7f 92       	push	r7
    15de:	8f 92       	push	r8
    15e0:	9f 92       	push	r9
    15e2:	af 92       	push	r10
    15e4:	bf 92       	push	r11
    15e6:	cf 92       	push	r12
    15e8:	df 92       	push	r13
    15ea:	ef 92       	push	r14
    15ec:	ff 92       	push	r15
    15ee:	0f 93       	push	r16
    15f0:	1f 93       	push	r17
    15f2:	cf 93       	push	r28
    15f4:	df 93       	push	r29
    15f6:	cd b7       	in	r28, 0x3d	; 61
    15f8:	de b7       	in	r29, 0x3e	; 62
    15fa:	27 97       	sbiw	r28, 0x07	; 7
    15fc:	0f b6       	in	r0, 0x3f	; 63
    15fe:	f8 94       	cli
    1600:	de bf       	out	0x3e, r29	; 62
    1602:	0f be       	out	0x3f, r0	; 63
    1604:	cd bf       	out	0x3d, r28	; 61
    1606:	8c 01       	movw	r16, r24
    1608:	8b e7       	ldi	r24, 0x7B	; 123
    160a:	80 93 8b 04 	sts	0x048B, r24	; 0x80048b <register_mem+0x7a>
    160e:	10 92 1c 04 	sts	0x041C, r1	; 0x80041c <register_mem+0xb>
    1612:	10 92 1b 04 	sts	0x041B, r1	; 0x80041b <register_mem+0xa>
    1616:	41 2c       	mov	r4, r1
    1618:	51 2c       	mov	r5, r1
    161a:	e0 ec       	ldi	r30, 0xC0	; 192
    161c:	6e 2e       	mov	r6, r30
    161e:	ef e7       	ldi	r30, 0x7F	; 127
    1620:	7e 2e       	mov	r7, r30
    1622:	22 24       	eor	r2, r2
    1624:	2a 94       	dec	r2
    1626:	32 2c       	mov	r3, r2
    1628:	78 01       	movw	r14, r16
    162a:	21 e0       	ldi	r18, 0x01	; 1
    162c:	e2 1a       	sub	r14, r18
    162e:	f1 08       	sbc	r15, r1
    1630:	10 16       	cp	r1, r16
    1632:	11 06       	cpc	r1, r17
    1634:	0c f0       	brlt	.+2      	; 0x1638 <_Z22_dimmer_i2c_on_receivei+0x66>
    1636:	96 c2       	rjmp	.+1324   	; 0x1b64 <_Z22_dimmer_i2c_on_receivei+0x592>
    1638:	d0 90 8b 04 	lds	r13, 0x048B	; 0x80048b <register_mem+0x7a>
    163c:	85 e5       	ldi	r24, 0x55	; 85
    163e:	93 e0       	ldi	r25, 0x03	; 3
    1640:	0e 94 5d 0f 	call	0x1eba	; 0x1eba <_ZN12StreamString4readEv>
    1644:	e0 91 8b 04 	lds	r30, 0x048B	; 0x80048b <register_mem+0x7a>
    1648:	e1 50       	subi	r30, 0x01	; 1
    164a:	eb 37       	cpi	r30, 0x7B	; 123
    164c:	08 f0       	brcs	.+2      	; 0x1650 <_Z22_dimmer_i2c_on_receivei+0x7e>
    164e:	eb e7       	ldi	r30, 0x7B	; 123
    1650:	f0 e0       	ldi	r31, 0x00	; 0
    1652:	ef 5e       	subi	r30, 0xEF	; 239
    1654:	fb 4f       	sbci	r31, 0xFB	; 251
    1656:	80 83       	st	Z, r24
    1658:	80 91 8b 04 	lds	r24, 0x048B	; 0x80048b <register_mem+0x7a>
    165c:	91 e0       	ldi	r25, 0x01	; 1
    165e:	98 0f       	add	r25, r24
    1660:	90 93 8b 04 	sts	0x048B, r25	; 0x80048b <register_mem+0x7a>
    1664:	9b e7       	ldi	r25, 0x7B	; 123
    1666:	d9 16       	cp	r13, r25
    1668:	21 f0       	breq	.+8      	; 0x1672 <_Z22_dimmer_i2c_on_receivei+0xa0>
    166a:	ab e0       	ldi	r26, 0x0B	; 11
    166c:	da 12       	cpse	r13, r26
    166e:	05 c0       	rjmp	.+10     	; 0x167a <_Z22_dimmer_i2c_on_receivei+0xa8>
    1670:	8b e7       	ldi	r24, 0x7B	; 123
    1672:	80 93 8b 04 	sts	0x048B, r24	; 0x80048b <register_mem+0x7a>
    1676:	87 01       	movw	r16, r14
    1678:	d7 cf       	rjmp	.-82     	; 0x1628 <_Z22_dimmer_i2c_on_receivei+0x56>
    167a:	ba e0       	ldi	r27, 0x0A	; 10
    167c:	db 12       	cpse	r13, r27
    167e:	fb cf       	rjmp	.-10     	; 0x1676 <_Z22_dimmer_i2c_on_receivei+0xa4>
    1680:	80 91 1a 04 	lds	r24, 0x041A	; 0x80041a <register_mem+0x9>
    1684:	82 35       	cpi	r24, 0x52	; 82
    1686:	09 f4       	brne	.+2      	; 0x168a <_Z22_dimmer_i2c_on_receivei+0xb8>
    1688:	63 c1       	rjmp	.+710    	; 0x1950 <_Z22_dimmer_i2c_on_receivei+0x37e>
    168a:	60 f5       	brcc	.+88     	; 0x16e4 <_Z22_dimmer_i2c_on_receivei+0x112>
    168c:	81 32       	cpi	r24, 0x21	; 33
    168e:	09 f4       	brne	.+2      	; 0x1692 <_Z22_dimmer_i2c_on_receivei+0xc0>
    1690:	15 c1       	rjmp	.+554    	; 0x18bc <_Z22_dimmer_i2c_on_receivei+0x2ea>
    1692:	c8 f4       	brcc	.+50     	; 0x16c6 <_Z22_dimmer_i2c_on_receivei+0xf4>
    1694:	81 31       	cpi	r24, 0x11	; 17
    1696:	09 f4       	brne	.+2      	; 0x169a <_Z22_dimmer_i2c_on_receivei+0xc8>
    1698:	e4 c0       	rjmp	.+456    	; 0x1862 <_Z22_dimmer_i2c_on_receivei+0x290>
    169a:	20 f4       	brcc	.+8      	; 0x16a4 <_Z22_dimmer_i2c_on_receivei+0xd2>
    169c:	80 31       	cpi	r24, 0x10	; 16
    169e:	09 f4       	brne	.+2      	; 0x16a2 <_Z22_dimmer_i2c_on_receivei+0xd0>
    16a0:	7d c0       	rjmp	.+250    	; 0x179c <_Z22_dimmer_i2c_on_receivei+0x1ca>
    16a2:	e9 cf       	rjmp	.-46     	; 0x1676 <_Z22_dimmer_i2c_on_receivei+0xa4>
    16a4:	82 31       	cpi	r24, 0x12	; 18
    16a6:	09 f4       	brne	.+2      	; 0x16aa <_Z22_dimmer_i2c_on_receivei+0xd8>
    16a8:	59 c0       	rjmp	.+178    	; 0x175c <_Z22_dimmer_i2c_on_receivei+0x18a>
    16aa:	80 32       	cpi	r24, 0x20	; 32
    16ac:	21 f7       	brne	.-56     	; 0x1676 <_Z22_dimmer_i2c_on_receivei+0xa4>
    16ae:	40 92 2d 04 	sts	0x042D, r4	; 0x80042d <register_mem+0x1c>
    16b2:	50 92 2e 04 	sts	0x042E, r5	; 0x80042e <register_mem+0x1d>
    16b6:	60 92 2f 04 	sts	0x042F, r6	; 0x80042f <register_mem+0x1e>
    16ba:	70 92 30 04 	sts	0x0430, r7	; 0x800430 <register_mem+0x1f>
    16be:	80 91 97 02 	lds	r24, 0x0297	; 0x800297 <dimmer_scheduled_calls>
    16c2:	84 60       	ori	r24, 0x04	; 4
    16c4:	06 c1       	rjmp	.+524    	; 0x18d2 <_Z22_dimmer_i2c_on_receivei+0x300>
    16c6:	83 32       	cpi	r24, 0x23	; 35
    16c8:	09 f4       	brne	.+2      	; 0x16cc <_Z22_dimmer_i2c_on_receivei+0xfa>
    16ca:	12 c1       	rjmp	.+548    	; 0x18f0 <_Z22_dimmer_i2c_on_receivei+0x31e>
    16cc:	08 f4       	brcc	.+2      	; 0x16d0 <_Z22_dimmer_i2c_on_receivei+0xfe>
    16ce:	04 c1       	rjmp	.+520    	; 0x18d8 <_Z22_dimmer_i2c_on_receivei+0x306>
    16d0:	80 35       	cpi	r24, 0x50	; 80
    16d2:	09 f4       	brne	.+2      	; 0x16d6 <_Z22_dimmer_i2c_on_receivei+0x104>
    16d4:	36 c1       	rjmp	.+620    	; 0x1942 <_Z22_dimmer_i2c_on_receivei+0x370>
    16d6:	81 35       	cpi	r24, 0x51	; 81
    16d8:	71 f6       	brne	.-100    	; 0x1676 <_Z22_dimmer_i2c_on_receivei+0xa4>
    16da:	0e 94 3e 05 	call	0xa7c	; 0xa7c <_Z12reset_configv>
    16de:	0e 94 13 05 	call	0xa26	; 0xa26 <_Z11init_eepromv>
    16e2:	c9 cf       	rjmp	.-110    	; 0x1676 <_Z22_dimmer_i2c_on_receivei+0xa4>
    16e4:	83 38       	cpi	r24, 0x83	; 131
    16e6:	09 f4       	brne	.+2      	; 0x16ea <_Z22_dimmer_i2c_on_receivei+0x118>
    16e8:	ed c1       	rjmp	.+986    	; 0x1ac4 <_Z22_dimmer_i2c_on_receivei+0x4f2>
    16ea:	88 f4       	brcc	.+34     	; 0x170e <_Z22_dimmer_i2c_on_receivei+0x13c>
    16ec:	84 35       	cpi	r24, 0x54	; 84
    16ee:	09 f4       	brne	.+2      	; 0x16f2 <_Z22_dimmer_i2c_on_receivei+0x120>
    16f0:	f5 c1       	rjmp	.+1002   	; 0x1adc <_Z22_dimmer_i2c_on_receivei+0x50a>
    16f2:	08 f4       	brcc	.+2      	; 0x16f6 <_Z22_dimmer_i2c_on_receivei+0x124>
    16f4:	8e c1       	rjmp	.+796    	; 0x1a12 <_Z22_dimmer_i2c_on_receivei+0x440>
    16f6:	85 35       	cpi	r24, 0x55	; 85
    16f8:	09 f4       	brne	.+2      	; 0x16fc <_Z22_dimmer_i2c_on_receivei+0x12a>
    16fa:	8e c1       	rjmp	.+796    	; 0x1a18 <_Z22_dimmer_i2c_on_receivei+0x446>
    16fc:	82 38       	cpi	r24, 0x82	; 130
    16fe:	09 f0       	breq	.+2      	; 0x1702 <_Z22_dimmer_i2c_on_receivei+0x130>
    1700:	ba cf       	rjmp	.-140    	; 0x1676 <_Z22_dimmer_i2c_on_receivei+0xa4>
    1702:	80 91 3a 04 	lds	r24, 0x043A	; 0x80043a <register_mem+0x29>
    1706:	90 91 3b 04 	lds	r25, 0x043B	; 0x80043b <register_mem+0x2a>
    170a:	01 97       	sbiw	r24, 0x01	; 1
    170c:	e0 c1       	rjmp	.+960    	; 0x1ace <_Z22_dimmer_i2c_on_receivei+0x4fc>
    170e:	82 39       	cpi	r24, 0x92	; 146
    1710:	09 f4       	brne	.+2      	; 0x1714 <_Z22_dimmer_i2c_on_receivei+0x142>
    1712:	9b c1       	rjmp	.+822    	; 0x1a4a <_Z22_dimmer_i2c_on_receivei+0x478>
    1714:	c0 f4       	brcc	.+48     	; 0x1746 <_Z22_dimmer_i2c_on_receivei+0x174>
    1716:	81 39       	cpi	r24, 0x91	; 145
    1718:	09 f0       	breq	.+2      	; 0x171c <_Z22_dimmer_i2c_on_receivei+0x14a>
    171a:	ad cf       	rjmp	.-166    	; 0x1676 <_Z22_dimmer_i2c_on_receivei+0xa4>
    171c:	1f 92       	push	r1
    171e:	83 e2       	ldi	r24, 0x23	; 35
    1720:	8f 93       	push	r24
    1722:	1f 92       	push	r1
    1724:	87 e1       	ldi	r24, 0x17	; 23
    1726:	8f 93       	push	r24
    1728:	86 ef       	ldi	r24, 0xF6	; 246
    172a:	91 e0       	ldi	r25, 0x01	; 1
    172c:	9f 93       	push	r25
    172e:	8f 93       	push	r24
    1730:	0e 94 a8 05 	call	0xb50	; 0xb50 <_Z15Serial_printf_PPKcz>
    1734:	03 e3       	ldi	r16, 0x33	; 51
    1736:	14 e0       	ldi	r17, 0x04	; 4
    1738:	0f 90       	pop	r0
    173a:	0f 90       	pop	r0
    173c:	0f 90       	pop	r0
    173e:	0f 90       	pop	r0
    1740:	0f 90       	pop	r0
    1742:	0f 90       	pop	r0
    1744:	d4 c1       	rjmp	.+936    	; 0x1aee <_Z22_dimmer_i2c_on_receivei+0x51c>
    1746:	83 39       	cpi	r24, 0x93	; 147
    1748:	09 f4       	brne	.+2      	; 0x174c <_Z22_dimmer_i2c_on_receivei+0x17a>
    174a:	fe c0       	rjmp	.+508    	; 0x1948 <_Z22_dimmer_i2c_on_receivei+0x376>
    174c:	8e 3e       	cpi	r24, 0xEE	; 238
    174e:	09 f0       	breq	.+2      	; 0x1752 <_Z22_dimmer_i2c_on_receivei+0x180>
    1750:	92 cf       	rjmp	.-220    	; 0x1676 <_Z22_dimmer_i2c_on_receivei+0xa4>
    1752:	01 e1       	ldi	r16, 0x11	; 17
    1754:	14 e0       	ldi	r17, 0x04	; 4
    1756:	c1 2c       	mov	r12, r1
    1758:	d1 2c       	mov	r13, r1
    175a:	e2 c1       	rjmp	.+964    	; 0x1b20 <_Z22_dimmer_i2c_on_receivei+0x54e>
    175c:	02 50       	subi	r16, 0x02	; 2
    175e:	11 09       	sbc	r17, r1
    1760:	1e 14       	cp	r1, r14
    1762:	1f 04       	cpc	r1, r15
    1764:	6c f4       	brge	.+26     	; 0x1780 <_Z22_dimmer_i2c_on_receivei+0x1ae>
    1766:	85 e5       	ldi	r24, 0x55	; 85
    1768:	93 e0       	ldi	r25, 0x03	; 3
    176a:	0e 94 5d 0f 	call	0x1eba	; 0x1eba <_ZN12StreamString4readEv>
    176e:	28 2f       	mov	r18, r24
    1770:	2f 70       	andi	r18, 0x0F	; 15
    1772:	99 27       	eor	r25, r25
    1774:	74 e0       	ldi	r23, 0x04	; 4
    1776:	95 95       	asr	r25
    1778:	87 95       	ror	r24
    177a:	7a 95       	dec	r23
    177c:	e1 f7       	brne	.-8      	; 0x1776 <_Z22_dimmer_i2c_on_receivei+0x1a4>
    177e:	02 c0       	rjmp	.+4      	; 0x1784 <_Z22_dimmer_i2c_on_receivei+0x1b2>
    1780:	20 e0       	ldi	r18, 0x00	; 0
    1782:	88 e0       	ldi	r24, 0x08	; 8
    1784:	88 0f       	add	r24, r24
    1786:	90 91 1b 04 	lds	r25, 0x041B	; 0x80041b <register_mem+0xa>
    178a:	89 0f       	add	r24, r25
    178c:	80 93 1b 04 	sts	0x041B, r24	; 0x80041b <register_mem+0xa>
    1790:	22 0f       	add	r18, r18
    1792:	23 5f       	subi	r18, 0xF3	; 243
    1794:	20 93 8b 04 	sts	0x048B, r18	; 0x80048b <register_mem+0x7a>
    1798:	78 01       	movw	r14, r16
    179a:	6d cf       	rjmp	.-294    	; 0x1676 <_Z22_dimmer_i2c_on_receivei+0xa4>
    179c:	00 91 14 04 	lds	r16, 0x0414	; 0x800414 <register_mem+0x3>
    17a0:	10 91 15 04 	lds	r17, 0x0415	; 0x800415 <register_mem+0x4>
    17a4:	80 91 13 04 	lds	r24, 0x0413	; 0x800413 <register_mem+0x2>
    17a8:	8f 3f       	cpi	r24, 0xFF	; 255
    17aa:	91 f5       	brne	.+100    	; 0x1810 <_Z22_dimmer_i2c_on_receivei+0x23e>
    17ac:	5d e1       	ldi	r21, 0x1D	; 29
    17ae:	85 2e       	mov	r8, r21
    17b0:	54 e0       	ldi	r21, 0x04	; 4
    17b2:	95 2e       	mov	r9, r21
    17b4:	6c e8       	ldi	r22, 0x8C	; 140
    17b6:	a6 2e       	mov	r10, r22
    17b8:	63 e0       	ldi	r22, 0x03	; 3
    17ba:	b6 2e       	mov	r11, r22
    17bc:	c1 2c       	mov	r12, r1
    17be:	d1 2c       	mov	r13, r1
    17c0:	17 fd       	sbrc	r17, 7
    17c2:	06 c0       	rjmp	.+12     	; 0x17d0 <_Z22_dimmer_i2c_on_receivei+0x1fe>
    17c4:	0f 3f       	cpi	r16, 0xFF	; 255
    17c6:	ef e1       	ldi	r30, 0x1F	; 31
    17c8:	1e 07       	cpc	r17, r30
    17ca:	2c f4       	brge	.+10     	; 0x17d6 <_Z22_dimmer_i2c_on_receivei+0x204>
    17cc:	c8 01       	movw	r24, r16
    17ce:	05 c0       	rjmp	.+10     	; 0x17da <_Z22_dimmer_i2c_on_receivei+0x208>
    17d0:	80 e0       	ldi	r24, 0x00	; 0
    17d2:	90 e0       	ldi	r25, 0x00	; 0
    17d4:	02 c0       	rjmp	.+4      	; 0x17da <_Z22_dimmer_i2c_on_receivei+0x208>
    17d6:	8f ef       	ldi	r24, 0xFF	; 255
    17d8:	9f e1       	ldi	r25, 0x1F	; 31
    17da:	d4 01       	movw	r26, r8
    17dc:	8d 93       	st	X+, r24
    17de:	9d 93       	st	X+, r25
    17e0:	4d 01       	movw	r8, r26
    17e2:	f5 01       	movw	r30, r10
    17e4:	11 86       	std	Z+9, r1	; 0x09
    17e6:	10 86       	std	Z+8, r1	; 0x08
    17e8:	f6 01       	movw	r30, r12
    17ea:	ee 0f       	add	r30, r30
    17ec:	ff 1f       	adc	r31, r31
    17ee:	e0 51       	subi	r30, 0x10	; 16
    17f0:	fc 4f       	sbci	r31, 0xFC	; 252
    17f2:	31 82       	std	Z+1, r3	; 0x01
    17f4:	20 82       	st	Z, r2
    17f6:	0e 94 27 18 	call	0x304e	; 0x304e <_ZN6Dimmer18_calculateChannelsEv.constprop.69>
    17fa:	ff ef       	ldi	r31, 0xFF	; 255
    17fc:	cf 1a       	sub	r12, r31
    17fe:	df 0a       	sbc	r13, r31
    1800:	2c e0       	ldi	r18, 0x0C	; 12
    1802:	a2 0e       	add	r10, r18
    1804:	b1 1c       	adc	r11, r1
    1806:	84 e0       	ldi	r24, 0x04	; 4
    1808:	c8 16       	cp	r12, r24
    180a:	d1 04       	cpc	r13, r1
    180c:	c9 f6       	brne	.-78     	; 0x17c0 <_Z22_dimmer_i2c_on_receivei+0x1ee>
    180e:	33 cf       	rjmp	.-410    	; 0x1676 <_Z22_dimmer_i2c_on_receivei+0xa4>
    1810:	08 2e       	mov	r0, r24
    1812:	00 0c       	add	r0, r0
    1814:	99 0b       	sbc	r25, r25
    1816:	17 fd       	sbrc	r17, 7
    1818:	07 c0       	rjmp	.+14     	; 0x1828 <_Z22_dimmer_i2c_on_receivei+0x256>
    181a:	0f 3f       	cpi	r16, 0xFF	; 255
    181c:	af e1       	ldi	r26, 0x1F	; 31
    181e:	1a 07       	cpc	r17, r26
    1820:	2c f0       	brlt	.+10     	; 0x182c <_Z22_dimmer_i2c_on_receivei+0x25a>
    1822:	0f ef       	ldi	r16, 0xFF	; 255
    1824:	1f e1       	ldi	r17, 0x1F	; 31
    1826:	02 c0       	rjmp	.+4      	; 0x182c <_Z22_dimmer_i2c_on_receivei+0x25a>
    1828:	00 e0       	ldi	r16, 0x00	; 0
    182a:	10 e0       	ldi	r17, 0x00	; 0
    182c:	fc 01       	movw	r30, r24
    182e:	ee 0f       	add	r30, r30
    1830:	ff 1f       	adc	r31, r31
    1832:	e3 5e       	subi	r30, 0xE3	; 227
    1834:	fb 4f       	sbci	r31, 0xFB	; 251
    1836:	11 83       	std	Z+1, r17	; 0x01
    1838:	00 83       	st	Z, r16
    183a:	2c e0       	ldi	r18, 0x0C	; 12
    183c:	28 9f       	mul	r18, r24
    183e:	f0 01       	movw	r30, r0
    1840:	29 9f       	mul	r18, r25
    1842:	f0 0d       	add	r31, r0
    1844:	11 24       	eor	r1, r1
    1846:	e4 57       	subi	r30, 0x74	; 116
    1848:	fc 4f       	sbci	r31, 0xFC	; 252
    184a:	11 86       	std	Z+9, r1	; 0x09
    184c:	10 86       	std	Z+8, r1	; 0x08
    184e:	88 0f       	add	r24, r24
    1850:	99 1f       	adc	r25, r25
    1852:	fc 01       	movw	r30, r24
    1854:	e0 51       	subi	r30, 0x10	; 16
    1856:	fc 4f       	sbci	r31, 0xFC	; 252
    1858:	31 82       	std	Z+1, r3	; 0x01
    185a:	20 82       	st	Z, r2
    185c:	0e 94 27 18 	call	0x304e	; 0x304e <_ZN6Dimmer18_calculateChannelsEv.constprop.69>
    1860:	0a cf       	rjmp	.-492    	; 0x1676 <_Z22_dimmer_i2c_on_receivei+0xa4>
    1862:	80 90 16 04 	lds	r8, 0x0416	; 0x800416 <register_mem+0x5>
    1866:	90 90 17 04 	lds	r9, 0x0417	; 0x800417 <register_mem+0x6>
    186a:	a0 90 18 04 	lds	r10, 0x0418	; 0x800418 <register_mem+0x7>
    186e:	b0 90 19 04 	lds	r11, 0x0419	; 0x800419 <register_mem+0x8>
    1872:	c0 90 14 04 	lds	r12, 0x0414	; 0x800414 <register_mem+0x3>
    1876:	d0 90 15 04 	lds	r13, 0x0415	; 0x800415 <register_mem+0x4>
    187a:	e0 91 11 04 	lds	r30, 0x0411	; 0x800411 <register_mem>
    187e:	f0 91 12 04 	lds	r31, 0x0412	; 0x800412 <register_mem+0x1>
    1882:	ff 83       	std	Y+7, r31	; 0x07
    1884:	ee 83       	std	Y+6, r30	; 0x06
    1886:	80 91 13 04 	lds	r24, 0x0413	; 0x800413 <register_mem+0x2>
    188a:	8f 3f       	cpi	r24, 0xFF	; 255
    188c:	79 f4       	brne	.+30     	; 0x18ac <_Z22_dimmer_i2c_on_receivei+0x2da>
    188e:	1d 82       	std	Y+5, r1	; 0x05
    1890:	95 01       	movw	r18, r10
    1892:	84 01       	movw	r16, r8
    1894:	a6 01       	movw	r20, r12
    1896:	6e 81       	ldd	r22, Y+6	; 0x06
    1898:	7f 81       	ldd	r23, Y+7	; 0x07
    189a:	8d 81       	ldd	r24, Y+5	; 0x05
    189c:	0e 94 b7 1a 	call	0x356e	; 0x356e <_ZN6Dimmer7setFadeEaiifb.constprop.49>
    18a0:	fd 81       	ldd	r31, Y+5	; 0x05
    18a2:	ff 5f       	subi	r31, 0xFF	; 255
    18a4:	fd 83       	std	Y+5, r31	; 0x05
    18a6:	f4 30       	cpi	r31, 0x04	; 4
    18a8:	99 f7       	brne	.-26     	; 0x1890 <_Z22_dimmer_i2c_on_receivei+0x2be>
    18aa:	e5 ce       	rjmp	.-566    	; 0x1676 <_Z22_dimmer_i2c_on_receivei+0xa4>
    18ac:	95 01       	movw	r18, r10
    18ae:	84 01       	movw	r16, r8
    18b0:	a6 01       	movw	r20, r12
    18b2:	6e 81       	ldd	r22, Y+6	; 0x06
    18b4:	7f 81       	ldd	r23, Y+7	; 0x07
    18b6:	0e 94 b7 1a 	call	0x356e	; 0x356e <_ZN6Dimmer7setFadeEaiifb.constprop.49>
    18ba:	dd ce       	rjmp	.-582    	; 0x1676 <_Z22_dimmer_i2c_on_receivei+0xa4>
    18bc:	40 92 2d 04 	sts	0x042D, r4	; 0x80042d <register_mem+0x1c>
    18c0:	50 92 2e 04 	sts	0x042E, r5	; 0x80042e <register_mem+0x1d>
    18c4:	60 92 2f 04 	sts	0x042F, r6	; 0x80042f <register_mem+0x1e>
    18c8:	70 92 30 04 	sts	0x0430, r7	; 0x800430 <register_mem+0x1f>
    18cc:	80 91 97 02 	lds	r24, 0x0297	; 0x800297 <dimmer_scheduled_calls>
    18d0:	82 60       	ori	r24, 0x02	; 2
    18d2:	80 93 97 02 	sts	0x0297, r24	; 0x800297 <dimmer_scheduled_calls>
    18d6:	2f c0       	rjmp	.+94     	; 0x1936 <_Z22_dimmer_i2c_on_receivei+0x364>
    18d8:	10 92 32 04 	sts	0x0432, r1	; 0x800432 <register_mem+0x21>
    18dc:	10 92 31 04 	sts	0x0431, r1	; 0x800431 <register_mem+0x20>
    18e0:	80 91 97 02 	lds	r24, 0x0297	; 0x800297 <dimmer_scheduled_calls>
    18e4:	81 60       	ori	r24, 0x01	; 1
    18e6:	80 93 97 02 	sts	0x0297, r24	; 0x800297 <dimmer_scheduled_calls>
    18ea:	42 e0       	ldi	r20, 0x02	; 2
    18ec:	61 e2       	ldi	r22, 0x21	; 33
    18ee:	25 c0       	rjmp	.+74     	; 0x193a <_Z22_dimmer_i2c_on_receivei+0x368>
    18f0:	80 91 f8 03 	lds	r24, 0x03F8	; 0x8003f8 <dimmer+0x6c>
    18f4:	90 91 f9 03 	lds	r25, 0x03F9	; 0x8003f9 <dimmer+0x6d>
    18f8:	89 2b       	or	r24, r25
    18fa:	89 f0       	breq	.+34     	; 0x191e <_Z22_dimmer_i2c_on_receivei+0x34c>
    18fc:	60 91 f8 03 	lds	r22, 0x03F8	; 0x8003f8 <dimmer+0x6c>
    1900:	70 91 f9 03 	lds	r23, 0x03F9	; 0x8003f9 <dimmer+0x6d>
    1904:	80 e0       	ldi	r24, 0x00	; 0
    1906:	90 e0       	ldi	r25, 0x00	; 0
    1908:	0e 94 f3 28 	call	0x51e6	; 0x51e6 <__floatunsisf>
    190c:	9b 01       	movw	r18, r22
    190e:	ac 01       	movw	r20, r24
    1910:	60 e0       	ldi	r22, 0x00	; 0
    1912:	74 e2       	ldi	r23, 0x24	; 36
    1914:	84 e7       	ldi	r24, 0x74	; 116
    1916:	99 e4       	ldi	r25, 0x49	; 73
    1918:	0e 94 fb 2a 	call	0x55f6	; 0x55f6 <__divsf3>
    191c:	04 c0       	rjmp	.+8      	; 0x1926 <_Z22_dimmer_i2c_on_receivei+0x354>
    191e:	60 e0       	ldi	r22, 0x00	; 0
    1920:	70 e0       	ldi	r23, 0x00	; 0
    1922:	80 ec       	ldi	r24, 0xC0	; 192
    1924:	9f e7       	ldi	r25, 0x7F	; 127
    1926:	60 93 2d 04 	sts	0x042D, r22	; 0x80042d <register_mem+0x1c>
    192a:	70 93 2e 04 	sts	0x042E, r23	; 0x80042e <register_mem+0x1d>
    192e:	80 93 2f 04 	sts	0x042F, r24	; 0x80042f <register_mem+0x1e>
    1932:	90 93 30 04 	sts	0x0430, r25	; 0x800430 <register_mem+0x1f>
    1936:	44 e0       	ldi	r20, 0x04	; 4
    1938:	6d e1       	ldi	r22, 0x1D	; 29
    193a:	c7 01       	movw	r24, r14
    193c:	0e 94 ce 02 	call	0x59c	; 0x59c <_Z30i2c_slave_set_register_addressiha>
    1940:	9a ce       	rjmp	.-716    	; 0x1676 <_Z22_dimmer_i2c_on_receivei+0xa4>
    1942:	0e 94 3d 16 	call	0x2c7a	; 0x2c7a <_Z12write_configv>
    1946:	97 ce       	rjmp	.-722    	; 0x1676 <_Z22_dimmer_i2c_on_receivei+0xa4>
    1948:	81 e0       	ldi	r24, 0x01	; 1
    194a:	0e 94 b5 09 	call	0x136a	; 0x136a <_Z13_write_configb>
    194e:	93 ce       	rjmp	.-730    	; 0x1676 <_Z22_dimmer_i2c_on_receivei+0xa4>
    1950:	02 50       	subi	r16, 0x02	; 2
    1952:	11 09       	sbc	r17, r1
    1954:	1e 14       	cp	r1, r14
    1956:	1f 04       	cpc	r1, r15
    1958:	0c f0       	brlt	.+2      	; 0x195c <_Z22_dimmer_i2c_on_receivei+0x38a>
    195a:	1e cf       	rjmp	.-452    	; 0x1798 <_Z22_dimmer_i2c_on_receivei+0x1c6>
    195c:	85 e5       	ldi	r24, 0x55	; 85
    195e:	93 e0       	ldi	r25, 0x03	; 3
    1960:	0e 94 5d 0f 	call	0x1eba	; 0x1eba <_ZN12StreamString4readEv>
    1964:	f8 2e       	mov	r15, r24
    1966:	99 27       	eor	r25, r25
    1968:	83 30       	cpi	r24, 0x03	; 3
    196a:	91 05       	cpc	r25, r1
    196c:	41 f1       	breq	.+80     	; 0x19be <_Z22_dimmer_i2c_on_receivei+0x3ec>
    196e:	7c f4       	brge	.+30     	; 0x198e <_Z22_dimmer_i2c_on_receivei+0x3bc>
    1970:	81 30       	cpi	r24, 0x01	; 1
    1972:	91 05       	cpc	r25, r1
    1974:	b9 f0       	breq	.+46     	; 0x19a4 <_Z22_dimmer_i2c_on_receivei+0x3d2>
    1976:	02 97       	sbiw	r24, 0x02	; 2
    1978:	09 f0       	breq	.+2      	; 0x197c <_Z22_dimmer_i2c_on_receivei+0x3aa>
    197a:	0e cf       	rjmp	.-484    	; 0x1798 <_Z22_dimmer_i2c_on_receivei+0x1c6>
    197c:	10 92 2d 04 	sts	0x042D, r1	; 0x80042d <register_mem+0x1c>
    1980:	10 92 2e 04 	sts	0x042E, r1	; 0x80042e <register_mem+0x1d>
    1984:	10 92 2f 04 	sts	0x042F, r1	; 0x80042f <register_mem+0x1e>
    1988:	10 92 30 04 	sts	0x0430, r1	; 0x800430 <register_mem+0x1f>
    198c:	39 c0       	rjmp	.+114    	; 0x1a00 <_Z22_dimmer_i2c_on_receivei+0x42e>
    198e:	84 30       	cpi	r24, 0x04	; 4
    1990:	91 05       	cpc	r25, r1
    1992:	01 f1       	breq	.+64     	; 0x19d4 <_Z22_dimmer_i2c_on_receivei+0x402>
    1994:	05 97       	sbiw	r24, 0x05	; 5
    1996:	09 f0       	breq	.+2      	; 0x199a <_Z22_dimmer_i2c_on_receivei+0x3c8>
    1998:	ff ce       	rjmp	.-514    	; 0x1798 <_Z22_dimmer_i2c_on_receivei+0x1c6>
    199a:	60 91 3e 04 	lds	r22, 0x043E	; 0x80043e <register_mem+0x2d>
    199e:	70 91 3f 04 	lds	r23, 0x043F	; 0x80043f <register_mem+0x2e>
    19a2:	1c c0       	rjmp	.+56     	; 0x19dc <_Z22_dimmer_i2c_on_receivei+0x40a>
    19a4:	80 e0       	ldi	r24, 0x00	; 0
    19a6:	90 e0       	ldi	r25, 0x00	; 0
    19a8:	a0 e0       	ldi	r26, 0x00	; 0
    19aa:	b0 e4       	ldi	r27, 0x40	; 64
    19ac:	80 93 2d 04 	sts	0x042D, r24	; 0x80042d <register_mem+0x1c>
    19b0:	90 93 2e 04 	sts	0x042E, r25	; 0x80042e <register_mem+0x1d>
    19b4:	a0 93 2f 04 	sts	0x042F, r26	; 0x80042f <register_mem+0x1e>
    19b8:	b0 93 30 04 	sts	0x0430, r27	; 0x800430 <register_mem+0x1f>
    19bc:	21 c0       	rjmp	.+66     	; 0x1a00 <_Z22_dimmer_i2c_on_receivei+0x42e>
    19be:	60 91 3a 04 	lds	r22, 0x043A	; 0x80043a <register_mem+0x29>
    19c2:	70 91 3b 04 	lds	r23, 0x043B	; 0x80043b <register_mem+0x2a>
    19c6:	07 2e       	mov	r0, r23
    19c8:	00 0c       	add	r0, r0
    19ca:	88 0b       	sbc	r24, r24
    19cc:	99 0b       	sbc	r25, r25
    19ce:	0e 94 f5 28 	call	0x51ea	; 0x51ea <__floatsisf>
    19d2:	08 c0       	rjmp	.+16     	; 0x19e4 <_Z22_dimmer_i2c_on_receivei+0x412>
    19d4:	60 91 3c 04 	lds	r22, 0x043C	; 0x80043c <register_mem+0x2b>
    19d8:	70 91 3d 04 	lds	r23, 0x043D	; 0x80043d <register_mem+0x2c>
    19dc:	80 e0       	ldi	r24, 0x00	; 0
    19de:	90 e0       	ldi	r25, 0x00	; 0
    19e0:	0e 94 f3 28 	call	0x51e6	; 0x51e6 <__floatunsisf>
    19e4:	20 e0       	ldi	r18, 0x00	; 0
    19e6:	30 e0       	ldi	r19, 0x00	; 0
    19e8:	40 e0       	ldi	r20, 0x00	; 0
    19ea:	5f e3       	ldi	r21, 0x3F	; 63
    19ec:	0e 94 54 29 	call	0x52a8	; 0x52a8 <__mulsf3>
    19f0:	60 93 2d 04 	sts	0x042D, r22	; 0x80042d <register_mem+0x1c>
    19f4:	70 93 2e 04 	sts	0x042E, r23	; 0x80042e <register_mem+0x1d>
    19f8:	80 93 2f 04 	sts	0x042F, r24	; 0x80042f <register_mem+0x1e>
    19fc:	90 93 30 04 	sts	0x0430, r25	; 0x800430 <register_mem+0x1f>
    1a00:	ff 20       	and	r15, r15
    1a02:	09 f4       	brne	.+2      	; 0x1a06 <_Z22_dimmer_i2c_on_receivei+0x434>
    1a04:	c9 ce       	rjmp	.-622    	; 0x1798 <_Z22_dimmer_i2c_on_receivei+0x1c6>
    1a06:	44 e0       	ldi	r20, 0x04	; 4
    1a08:	6d e1       	ldi	r22, 0x1D	; 29
    1a0a:	c8 01       	movw	r24, r16
    1a0c:	0e 94 ce 02 	call	0x59c	; 0x59c <_Z30i2c_slave_set_register_addressiha>
    1a10:	c3 ce       	rjmp	.-634    	; 0x1798 <_Z22_dimmer_i2c_on_receivei+0x1c6>
    1a12:	0e 94 e6 13 	call	0x27cc	; 0x27cc <_Z19display_dimmer_infov>
    1a16:	2f ce       	rjmp	.-930    	; 0x1676 <_Z22_dimmer_i2c_on_receivei+0xa4>
    1a18:	10 92 93 02 	sts	0x0293, r1	; 0x800293 <print_metrics_timeout>
    1a1c:	10 92 94 02 	sts	0x0294, r1	; 0x800294 <print_metrics_timeout+0x1>
    1a20:	10 92 95 02 	sts	0x0295, r1	; 0x800295 <print_metrics_timeout+0x2>
    1a24:	10 92 96 02 	sts	0x0296, r1	; 0x800296 <print_metrics_timeout+0x3>
    1a28:	02 50       	subi	r16, 0x02	; 2
    1a2a:	11 09       	sbc	r17, r1
    1a2c:	1e 14       	cp	r1, r14
    1a2e:	1f 04       	cpc	r1, r15
    1a30:	0c f0       	brlt	.+2      	; 0x1a34 <_Z22_dimmer_i2c_on_receivei+0x462>
    1a32:	92 c0       	rjmp	.+292    	; 0x1b58 <_Z22_dimmer_i2c_on_receivei+0x586>
    1a34:	85 e5       	ldi	r24, 0x55	; 85
    1a36:	93 e0       	ldi	r25, 0x03	; 3
    1a38:	0e 94 5d 0f 	call	0x1eba	; 0x1eba <_ZN12StreamString4readEv>
    1a3c:	89 2b       	or	r24, r25
    1a3e:	09 f0       	breq	.+2      	; 0x1a42 <_Z22_dimmer_i2c_on_receivei+0x470>
    1a40:	8b c0       	rjmp	.+278    	; 0x1b58 <_Z22_dimmer_i2c_on_receivei+0x586>
    1a42:	80 91 97 02 	lds	r24, 0x0297	; 0x800297 <dimmer_scheduled_calls>
    1a46:	8f 7e       	andi	r24, 0xEF	; 239
    1a48:	8a c0       	rjmp	.+276    	; 0x1b5e <_Z22_dimmer_i2c_on_receivei+0x58c>
    1a4a:	68 01       	movw	r12, r16
    1a4c:	92 e0       	ldi	r25, 0x02	; 2
    1a4e:	c9 1a       	sub	r12, r25
    1a50:	d1 08       	sbc	r13, r1
    1a52:	a4 e0       	ldi	r26, 0x04	; 4
    1a54:	ea 16       	cp	r14, r26
    1a56:	f1 04       	cpc	r15, r1
    1a58:	24 f1       	brlt	.+72     	; 0x1aa2 <_Z22_dimmer_i2c_on_receivei+0x4d0>
    1a5a:	19 82       	std	Y+1, r1	; 0x01
    1a5c:	1a 82       	std	Y+2, r1	; 0x02
    1a5e:	1b 82       	std	Y+3, r1	; 0x03
    1a60:	1c 82       	std	Y+4, r1	; 0x04
    1a62:	64 e0       	ldi	r22, 0x04	; 4
    1a64:	70 e0       	ldi	r23, 0x00	; 0
    1a66:	ce 01       	movw	r24, r28
    1a68:	01 96       	adiw	r24, 0x01	; 1
    1a6a:	0e 94 f3 1b 	call	0x37e6	; 0x37e6 <_ZN6Stream9readBytesEPcj.constprop.32>
    1a6e:	76 01       	movw	r14, r12
    1a70:	e8 1a       	sub	r14, r24
    1a72:	f9 0a       	sbc	r15, r25
    1a74:	20 e0       	ldi	r18, 0x00	; 0
    1a76:	30 e0       	ldi	r19, 0x00	; 0
    1a78:	40 e8       	ldi	r20, 0x80	; 128
    1a7a:	51 e4       	ldi	r21, 0x41	; 65
    1a7c:	69 81       	ldd	r22, Y+1	; 0x01
    1a7e:	7a 81       	ldd	r23, Y+2	; 0x02
    1a80:	8b 81       	ldd	r24, Y+3	; 0x03
    1a82:	9c 81       	ldd	r25, Y+4	; 0x04
    1a84:	0e 94 54 29 	call	0x52a8	; 0x52a8 <__mulsf3>
    1a88:	20 e0       	ldi	r18, 0x00	; 0
    1a8a:	30 e0       	ldi	r19, 0x00	; 0
    1a8c:	40 e0       	ldi	r20, 0x00	; 0
    1a8e:	5e e3       	ldi	r21, 0x3E	; 62
    1a90:	0e 94 54 29 	call	0x52a8	; 0x52a8 <__mulsf3>
    1a94:	0e 94 6d 2b 	call	0x56da	; 0x56da <__fixsfsi>
    1a98:	70 93 3b 04 	sts	0x043B, r23	; 0x80043b <register_mem+0x2a>
    1a9c:	60 93 3a 04 	sts	0x043A, r22	; 0x80043a <register_mem+0x29>
    1aa0:	1a c0       	rjmp	.+52     	; 0x1ad6 <_Z22_dimmer_i2c_on_receivei+0x504>
    1aa2:	78 01       	movw	r14, r16
    1aa4:	b3 e0       	ldi	r27, 0x03	; 3
    1aa6:	eb 1a       	sub	r14, r27
    1aa8:	f1 08       	sbc	r15, r1
    1aaa:	e2 e0       	ldi	r30, 0x02	; 2
    1aac:	ce 16       	cp	r12, r30
    1aae:	d1 04       	cpc	r13, r1
    1ab0:	94 f0       	brlt	.+36     	; 0x1ad6 <_Z22_dimmer_i2c_on_receivei+0x504>
    1ab2:	62 e0       	ldi	r22, 0x02	; 2
    1ab4:	70 e0       	ldi	r23, 0x00	; 0
    1ab6:	8a e3       	ldi	r24, 0x3A	; 58
    1ab8:	94 e0       	ldi	r25, 0x04	; 4
    1aba:	0e 94 f3 1b 	call	0x37e6	; 0x37e6 <_ZN6Stream9readBytesEPcj.constprop.32>
    1abe:	e8 1a       	sub	r14, r24
    1ac0:	f9 0a       	sbc	r15, r25
    1ac2:	09 c0       	rjmp	.+18     	; 0x1ad6 <_Z22_dimmer_i2c_on_receivei+0x504>
    1ac4:	80 91 3a 04 	lds	r24, 0x043A	; 0x80043a <register_mem+0x29>
    1ac8:	90 91 3b 04 	lds	r25, 0x043B	; 0x80043b <register_mem+0x2a>
    1acc:	01 96       	adiw	r24, 0x01	; 1
    1ace:	90 93 3b 04 	sts	0x043B, r25	; 0x80043b <register_mem+0x2a>
    1ad2:	80 93 3a 04 	sts	0x043A, r24	; 0x80043a <register_mem+0x29>
    1ad6:	0e 94 09 06 	call	0xc12	; 0xc12 <_Z13print_zcdelayv>
    1ada:	cd cd       	rjmp	.-1126   	; 0x1676 <_Z22_dimmer_i2c_on_receivei+0xa4>
    1adc:	10 92 8f 02 	sts	0x028F, r1	; 0x80028f <next_temp_check>
    1ae0:	10 92 90 02 	sts	0x0290, r1	; 0x800290 <next_temp_check+0x1>
    1ae4:	10 92 91 02 	sts	0x0291, r1	; 0x800291 <next_temp_check+0x2>
    1ae8:	10 92 92 02 	sts	0x0292, r1	; 0x800292 <next_temp_check+0x3>
    1aec:	c4 cd       	rjmp	.-1144   	; 0x1676 <_Z22_dimmer_i2c_on_receivei+0xa4>
    1aee:	f8 01       	movw	r30, r16
    1af0:	81 91       	ld	r24, Z+
    1af2:	8f 01       	movw	r16, r30
    1af4:	1f 92       	push	r1
    1af6:	8f 93       	push	r24
    1af8:	81 ef       	ldi	r24, 0xF1	; 241
    1afa:	91 e0       	ldi	r25, 0x01	; 1
    1afc:	9f 93       	push	r25
    1afe:	8f 93       	push	r24
    1b00:	0e 94 a8 05 	call	0xb50	; 0xb50 <_Z15Serial_printf_PPKcz>
    1b04:	0f 90       	pop	r0
    1b06:	0f 90       	pop	r0
    1b08:	0f 90       	pop	r0
    1b0a:	0f 90       	pop	r0
    1b0c:	e7 e4       	ldi	r30, 0x47	; 71
    1b0e:	f4 e0       	ldi	r31, 0x04	; 4
    1b10:	e0 17       	cp	r30, r16
    1b12:	f1 07       	cpc	r31, r17
    1b14:	61 f7       	brne	.-40     	; 0x1aee <_Z22_dimmer_i2c_on_receivei+0x51c>
    1b16:	89 ea       	ldi	r24, 0xA9	; 169
    1b18:	92 e0       	ldi	r25, 0x02	; 2
    1b1a:	0e 94 39 12 	call	0x2472	; 0x2472 <_ZN5Print7printlnEv>
    1b1e:	ab cd       	rjmp	.-1194   	; 0x1676 <_Z22_dimmer_i2c_on_receivei+0xa4>
    1b20:	d8 01       	movw	r26, r16
    1b22:	8d 91       	ld	r24, X+
    1b24:	8d 01       	movw	r16, r26
    1b26:	bf ef       	ldi	r27, 0xFF	; 255
    1b28:	cb 1a       	sub	r12, r27
    1b2a:	db 0a       	sbc	r13, r27
    1b2c:	1f 92       	push	r1
    1b2e:	8f 93       	push	r24
    1b30:	1f 92       	push	r1
    1b32:	8f 93       	push	r24
    1b34:	df 92       	push	r13
    1b36:	cf 92       	push	r12
    1b38:	ec ed       	ldi	r30, 0xDC	; 220
    1b3a:	f1 e0       	ldi	r31, 0x01	; 1
    1b3c:	ff 93       	push	r31
    1b3e:	ef 93       	push	r30
    1b40:	0e 94 a8 05 	call	0xb50	; 0xb50 <_Z15Serial_printf_PPKcz>
    1b44:	0f b6       	in	r0, 0x3f	; 63
    1b46:	f8 94       	cli
    1b48:	de bf       	out	0x3e, r29	; 62
    1b4a:	0f be       	out	0x3f, r0	; 63
    1b4c:	cd bf       	out	0x3d, r28	; 61
    1b4e:	9b e7       	ldi	r25, 0x7B	; 123
    1b50:	c9 16       	cp	r12, r25
    1b52:	d1 04       	cpc	r13, r1
    1b54:	29 f7       	brne	.-54     	; 0x1b20 <_Z22_dimmer_i2c_on_receivei+0x54e>
    1b56:	8f cd       	rjmp	.-1250   	; 0x1676 <_Z22_dimmer_i2c_on_receivei+0xa4>
    1b58:	80 91 97 02 	lds	r24, 0x0297	; 0x800297 <dimmer_scheduled_calls>
    1b5c:	80 61       	ori	r24, 0x10	; 16
    1b5e:	80 93 97 02 	sts	0x0297, r24	; 0x800297 <dimmer_scheduled_calls>
    1b62:	1a ce       	rjmp	.-972    	; 0x1798 <_Z22_dimmer_i2c_on_receivei+0x1c6>
    1b64:	27 96       	adiw	r28, 0x07	; 7
    1b66:	0f b6       	in	r0, 0x3f	; 63
    1b68:	f8 94       	cli
    1b6a:	de bf       	out	0x3e, r29	; 62
    1b6c:	0f be       	out	0x3f, r0	; 63
    1b6e:	cd bf       	out	0x3d, r28	; 61
    1b70:	df 91       	pop	r29
    1b72:	cf 91       	pop	r28
    1b74:	1f 91       	pop	r17
    1b76:	0f 91       	pop	r16
    1b78:	ff 90       	pop	r15
    1b7a:	ef 90       	pop	r14
    1b7c:	df 90       	pop	r13
    1b7e:	cf 90       	pop	r12
    1b80:	bf 90       	pop	r11
    1b82:	af 90       	pop	r10
    1b84:	9f 90       	pop	r9
    1b86:	8f 90       	pop	r8
    1b88:	7f 90       	pop	r7
    1b8a:	6f 90       	pop	r6
    1b8c:	5f 90       	pop	r5
    1b8e:	4f 90       	pop	r4
    1b90:	3f 90       	pop	r3
    1b92:	2f 90       	pop	r2
    1b94:	08 95       	ret

00001b96 <_ZN5EERef6updateEh>:
    1b96:	ff 92       	push	r15
    1b98:	0f 93       	push	r16
    1b9a:	1f 93       	push	r17
    1b9c:	cf 93       	push	r28
    1b9e:	df 93       	push	r29
    1ba0:	ec 01       	movw	r28, r24
    1ba2:	f6 2e       	mov	r15, r22
    1ba4:	08 81       	ld	r16, Y
    1ba6:	19 81       	ldd	r17, Y+1	; 0x01
    1ba8:	c8 01       	movw	r24, r16
    1baa:	0e 94 12 2a 	call	0x5424	; 0x5424 <eeprom_read_byte>
    1bae:	f8 16       	cp	r15, r24
    1bb0:	21 f0       	breq	.+8      	; 0x1bba <_ZN5EERef6updateEh+0x24>
    1bb2:	6f 2d       	mov	r22, r15
    1bb4:	c8 01       	movw	r24, r16
    1bb6:	0e 94 1a 2a 	call	0x5434	; 0x5434 <eeprom_write_byte>
    1bba:	ce 01       	movw	r24, r28
    1bbc:	df 91       	pop	r29
    1bbe:	cf 91       	pop	r28
    1bc0:	1f 91       	pop	r17
    1bc2:	0f 91       	pop	r16
    1bc4:	ff 90       	pop	r15
    1bc6:	08 95       	ret

00001bc8 <_ZN12StreamString5flushEv>:
    1bc8:	08 95       	ret

00001bca <_ZN12StreamString4peekEv>:
    1bca:	dc 01       	movw	r26, r24
    1bcc:	50 96       	adiw	r26, 0x10	; 16
    1bce:	2d 91       	ld	r18, X+
    1bd0:	3c 91       	ld	r19, X
    1bd2:	51 97       	sbiw	r26, 0x11	; 17
    1bd4:	23 2b       	or	r18, r19
    1bd6:	39 f0       	breq	.+14     	; 0x1be6 <_ZN12StreamString4peekEv+0x1c>
    1bd8:	1c 96       	adiw	r26, 0x0c	; 12
    1bda:	ed 91       	ld	r30, X+
    1bdc:	fc 91       	ld	r31, X
    1bde:	1d 97       	sbiw	r26, 0x0d	; 13
    1be0:	80 81       	ld	r24, Z
    1be2:	90 e0       	ldi	r25, 0x00	; 0
    1be4:	08 95       	ret
    1be6:	8f ef       	ldi	r24, 0xFF	; 255
    1be8:	9f ef       	ldi	r25, 0xFF	; 255
    1bea:	08 95       	ret

00001bec <_ZN12StreamString9availableEv>:
    1bec:	fc 01       	movw	r30, r24
    1bee:	80 89       	ldd	r24, Z+16	; 0x10
    1bf0:	91 89       	ldd	r25, Z+17	; 0x11
    1bf2:	08 95       	ret

00001bf4 <_ZN13SerialTwoWire5flushEv>:
    1bf4:	08 95       	ret

00001bf6 <nothing.lto_priv.94>:
    1bf6:	08 95       	ret

00001bf8 <__cxa_pure_virtual>:
    1bf8:	0e 94 19 2e 	call	0x5c32	; 0x5c32 <abort>

00001bfc <pinMode>:
    1bfc:	cf 93       	push	r28
    1bfe:	df 93       	push	r29
    1c00:	90 e0       	ldi	r25, 0x00	; 0
    1c02:	fc 01       	movw	r30, r24
    1c04:	e0 5d       	subi	r30, 0xD0	; 208
    1c06:	fa 4f       	sbci	r31, 0xFA	; 250
    1c08:	24 91       	lpm	r18, Z
    1c0a:	fc 01       	movw	r30, r24
    1c0c:	e4 5e       	subi	r30, 0xE4	; 228
    1c0e:	fa 4f       	sbci	r31, 0xFA	; 250
    1c10:	84 91       	lpm	r24, Z
    1c12:	88 23       	and	r24, r24
    1c14:	61 f1       	breq	.+88     	; 0x1c6e <pinMode+0x72>
    1c16:	90 e0       	ldi	r25, 0x00	; 0
    1c18:	88 0f       	add	r24, r24
    1c1a:	99 1f       	adc	r25, r25
    1c1c:	fc 01       	movw	r30, r24
    1c1e:	e8 51       	subi	r30, 0x18	; 24
    1c20:	fd 4f       	sbci	r31, 0xFD	; 253
    1c22:	c5 91       	lpm	r28, Z+
    1c24:	d4 91       	lpm	r29, Z
    1c26:	fc 01       	movw	r30, r24
    1c28:	ee 5e       	subi	r30, 0xEE	; 238
    1c2a:	fa 4f       	sbci	r31, 0xFA	; 250
    1c2c:	a5 91       	lpm	r26, Z+
    1c2e:	b4 91       	lpm	r27, Z
    1c30:	61 11       	cpse	r22, r1
    1c32:	09 c0       	rjmp	.+18     	; 0x1c46 <pinMode+0x4a>
    1c34:	9f b7       	in	r25, 0x3f	; 63
    1c36:	f8 94       	cli
    1c38:	88 81       	ld	r24, Y
    1c3a:	20 95       	com	r18
    1c3c:	82 23       	and	r24, r18
    1c3e:	88 83       	st	Y, r24
    1c40:	ec 91       	ld	r30, X
    1c42:	2e 23       	and	r18, r30
    1c44:	0b c0       	rjmp	.+22     	; 0x1c5c <pinMode+0x60>
    1c46:	62 30       	cpi	r22, 0x02	; 2
    1c48:	61 f4       	brne	.+24     	; 0x1c62 <pinMode+0x66>
    1c4a:	9f b7       	in	r25, 0x3f	; 63
    1c4c:	f8 94       	cli
    1c4e:	88 81       	ld	r24, Y
    1c50:	32 2f       	mov	r19, r18
    1c52:	30 95       	com	r19
    1c54:	83 23       	and	r24, r19
    1c56:	88 83       	st	Y, r24
    1c58:	ec 91       	ld	r30, X
    1c5a:	2e 2b       	or	r18, r30
    1c5c:	2c 93       	st	X, r18
    1c5e:	9f bf       	out	0x3f, r25	; 63
    1c60:	06 c0       	rjmp	.+12     	; 0x1c6e <pinMode+0x72>
    1c62:	8f b7       	in	r24, 0x3f	; 63
    1c64:	f8 94       	cli
    1c66:	e8 81       	ld	r30, Y
    1c68:	2e 2b       	or	r18, r30
    1c6a:	28 83       	st	Y, r18
    1c6c:	8f bf       	out	0x3f, r24	; 63
    1c6e:	df 91       	pop	r29
    1c70:	cf 91       	pop	r28
    1c72:	08 95       	ret

00001c74 <micros>:
    1c74:	3f b7       	in	r19, 0x3f	; 63
    1c76:	f8 94       	cli
    1c78:	80 91 a5 02 	lds	r24, 0x02A5	; 0x8002a5 <timer0_overflow_count>
    1c7c:	90 91 a6 02 	lds	r25, 0x02A6	; 0x8002a6 <timer0_overflow_count+0x1>
    1c80:	a0 91 a7 02 	lds	r26, 0x02A7	; 0x8002a7 <timer0_overflow_count+0x2>
    1c84:	b0 91 a8 02 	lds	r27, 0x02A8	; 0x8002a8 <timer0_overflow_count+0x3>
    1c88:	26 b5       	in	r18, 0x26	; 38
    1c8a:	a8 9b       	sbis	0x15, 0	; 21
    1c8c:	05 c0       	rjmp	.+10     	; 0x1c98 <micros+0x24>
    1c8e:	2f 3f       	cpi	r18, 0xFF	; 255
    1c90:	19 f0       	breq	.+6      	; 0x1c98 <micros+0x24>
    1c92:	01 96       	adiw	r24, 0x01	; 1
    1c94:	a1 1d       	adc	r26, r1
    1c96:	b1 1d       	adc	r27, r1
    1c98:	3f bf       	out	0x3f, r19	; 63
    1c9a:	ba 2f       	mov	r27, r26
    1c9c:	a9 2f       	mov	r26, r25
    1c9e:	98 2f       	mov	r25, r24
    1ca0:	88 27       	eor	r24, r24
    1ca2:	82 0f       	add	r24, r18
    1ca4:	91 1d       	adc	r25, r1
    1ca6:	a1 1d       	adc	r26, r1
    1ca8:	b1 1d       	adc	r27, r1
    1caa:	bc 01       	movw	r22, r24
    1cac:	cd 01       	movw	r24, r26
    1cae:	42 e0       	ldi	r20, 0x02	; 2
    1cb0:	66 0f       	add	r22, r22
    1cb2:	77 1f       	adc	r23, r23
    1cb4:	88 1f       	adc	r24, r24
    1cb6:	99 1f       	adc	r25, r25
    1cb8:	4a 95       	dec	r20
    1cba:	d1 f7       	brne	.-12     	; 0x1cb0 <micros+0x3c>
    1cbc:	08 95       	ret

00001cbe <delay>:
    1cbe:	8f 92       	push	r8
    1cc0:	9f 92       	push	r9
    1cc2:	af 92       	push	r10
    1cc4:	bf 92       	push	r11
    1cc6:	cf 92       	push	r12
    1cc8:	df 92       	push	r13
    1cca:	ef 92       	push	r14
    1ccc:	ff 92       	push	r15
    1cce:	6b 01       	movw	r12, r22
    1cd0:	7c 01       	movw	r14, r24
    1cd2:	0e 94 3a 0e 	call	0x1c74	; 0x1c74 <micros>
    1cd6:	4b 01       	movw	r8, r22
    1cd8:	5c 01       	movw	r10, r24
    1cda:	c1 14       	cp	r12, r1
    1cdc:	d1 04       	cpc	r13, r1
    1cde:	e1 04       	cpc	r14, r1
    1ce0:	f1 04       	cpc	r15, r1
    1ce2:	f1 f0       	breq	.+60     	; 0x1d20 <delay+0x62>
    1ce4:	0e 94 3a 0e 	call	0x1c74	; 0x1c74 <micros>
    1ce8:	dc 01       	movw	r26, r24
    1cea:	cb 01       	movw	r24, r22
    1cec:	88 19       	sub	r24, r8
    1cee:	99 09       	sbc	r25, r9
    1cf0:	aa 09       	sbc	r26, r10
    1cf2:	bb 09       	sbc	r27, r11
    1cf4:	88 3e       	cpi	r24, 0xE8	; 232
    1cf6:	93 40       	sbci	r25, 0x03	; 3
    1cf8:	a1 05       	cpc	r26, r1
    1cfa:	b1 05       	cpc	r27, r1
    1cfc:	70 f3       	brcs	.-36     	; 0x1cda <delay+0x1c>
    1cfe:	21 e0       	ldi	r18, 0x01	; 1
    1d00:	c2 1a       	sub	r12, r18
    1d02:	d1 08       	sbc	r13, r1
    1d04:	e1 08       	sbc	r14, r1
    1d06:	f1 08       	sbc	r15, r1
    1d08:	88 ee       	ldi	r24, 0xE8	; 232
    1d0a:	88 0e       	add	r8, r24
    1d0c:	83 e0       	ldi	r24, 0x03	; 3
    1d0e:	98 1e       	adc	r9, r24
    1d10:	a1 1c       	adc	r10, r1
    1d12:	b1 1c       	adc	r11, r1
    1d14:	c1 14       	cp	r12, r1
    1d16:	d1 04       	cpc	r13, r1
    1d18:	e1 04       	cpc	r14, r1
    1d1a:	f1 04       	cpc	r15, r1
    1d1c:	19 f7       	brne	.-58     	; 0x1ce4 <delay+0x26>
    1d1e:	dd cf       	rjmp	.-70     	; 0x1cda <delay+0x1c>
    1d20:	ff 90       	pop	r15
    1d22:	ef 90       	pop	r14
    1d24:	df 90       	pop	r13
    1d26:	cf 90       	pop	r12
    1d28:	bf 90       	pop	r11
    1d2a:	af 90       	pop	r10
    1d2c:	9f 90       	pop	r9
    1d2e:	8f 90       	pop	r8
    1d30:	08 95       	ret

00001d32 <millis>:
    1d32:	2f b7       	in	r18, 0x3f	; 63
    1d34:	f8 94       	cli
    1d36:	60 91 a1 02 	lds	r22, 0x02A1	; 0x8002a1 <timer0_millis>
    1d3a:	70 91 a2 02 	lds	r23, 0x02A2	; 0x8002a2 <timer0_millis+0x1>
    1d3e:	80 91 a3 02 	lds	r24, 0x02A3	; 0x8002a3 <timer0_millis+0x2>
    1d42:	90 91 a4 02 	lds	r25, 0x02A4	; 0x8002a4 <timer0_millis+0x3>
    1d46:	2f bf       	out	0x3f, r18	; 63
    1d48:	08 95       	ret

00001d4a <__vector_16>:
    1d4a:	1f 92       	push	r1
    1d4c:	0f 92       	push	r0
    1d4e:	0f b6       	in	r0, 0x3f	; 63
    1d50:	0f 92       	push	r0
    1d52:	11 24       	eor	r1, r1
    1d54:	2f 93       	push	r18
    1d56:	3f 93       	push	r19
    1d58:	8f 93       	push	r24
    1d5a:	9f 93       	push	r25
    1d5c:	af 93       	push	r26
    1d5e:	bf 93       	push	r27
    1d60:	80 91 a1 02 	lds	r24, 0x02A1	; 0x8002a1 <timer0_millis>
    1d64:	90 91 a2 02 	lds	r25, 0x02A2	; 0x8002a2 <timer0_millis+0x1>
    1d68:	a0 91 a3 02 	lds	r26, 0x02A3	; 0x8002a3 <timer0_millis+0x2>
    1d6c:	b0 91 a4 02 	lds	r27, 0x02A4	; 0x8002a4 <timer0_millis+0x3>
    1d70:	30 91 a0 02 	lds	r19, 0x02A0	; 0x8002a0 <timer0_fract>
    1d74:	23 e0       	ldi	r18, 0x03	; 3
    1d76:	23 0f       	add	r18, r19
    1d78:	2d 37       	cpi	r18, 0x7D	; 125
    1d7a:	20 f4       	brcc	.+8      	; 0x1d84 <__vector_16+0x3a>
    1d7c:	01 96       	adiw	r24, 0x01	; 1
    1d7e:	a1 1d       	adc	r26, r1
    1d80:	b1 1d       	adc	r27, r1
    1d82:	05 c0       	rjmp	.+10     	; 0x1d8e <__vector_16+0x44>
    1d84:	26 e8       	ldi	r18, 0x86	; 134
    1d86:	23 0f       	add	r18, r19
    1d88:	02 96       	adiw	r24, 0x02	; 2
    1d8a:	a1 1d       	adc	r26, r1
    1d8c:	b1 1d       	adc	r27, r1
    1d8e:	20 93 a0 02 	sts	0x02A0, r18	; 0x8002a0 <timer0_fract>
    1d92:	80 93 a1 02 	sts	0x02A1, r24	; 0x8002a1 <timer0_millis>
    1d96:	90 93 a2 02 	sts	0x02A2, r25	; 0x8002a2 <timer0_millis+0x1>
    1d9a:	a0 93 a3 02 	sts	0x02A3, r26	; 0x8002a3 <timer0_millis+0x2>
    1d9e:	b0 93 a4 02 	sts	0x02A4, r27	; 0x8002a4 <timer0_millis+0x3>
    1da2:	80 91 a5 02 	lds	r24, 0x02A5	; 0x8002a5 <timer0_overflow_count>
    1da6:	90 91 a6 02 	lds	r25, 0x02A6	; 0x8002a6 <timer0_overflow_count+0x1>
    1daa:	a0 91 a7 02 	lds	r26, 0x02A7	; 0x8002a7 <timer0_overflow_count+0x2>
    1dae:	b0 91 a8 02 	lds	r27, 0x02A8	; 0x8002a8 <timer0_overflow_count+0x3>
    1db2:	01 96       	adiw	r24, 0x01	; 1
    1db4:	a1 1d       	adc	r26, r1
    1db6:	b1 1d       	adc	r27, r1
    1db8:	80 93 a5 02 	sts	0x02A5, r24	; 0x8002a5 <timer0_overflow_count>
    1dbc:	90 93 a6 02 	sts	0x02A6, r25	; 0x8002a6 <timer0_overflow_count+0x1>
    1dc0:	a0 93 a7 02 	sts	0x02A7, r26	; 0x8002a7 <timer0_overflow_count+0x2>
    1dc4:	b0 93 a8 02 	sts	0x02A8, r27	; 0x8002a8 <timer0_overflow_count+0x3>
    1dc8:	bf 91       	pop	r27
    1dca:	af 91       	pop	r26
    1dcc:	9f 91       	pop	r25
    1dce:	8f 91       	pop	r24
    1dd0:	3f 91       	pop	r19
    1dd2:	2f 91       	pop	r18
    1dd4:	0f 90       	pop	r0
    1dd6:	0f be       	out	0x3f, r0	; 63
    1dd8:	0f 90       	pop	r0
    1dda:	1f 90       	pop	r1
    1ddc:	18 95       	reti

00001dde <_ZN6String7reserveEj>:
    1dde:	0f 93       	push	r16
    1de0:	1f 93       	push	r17
    1de2:	cf 93       	push	r28
    1de4:	df 93       	push	r29
    1de6:	ec 01       	movw	r28, r24
    1de8:	88 81       	ld	r24, Y
    1dea:	99 81       	ldd	r25, Y+1	; 0x01
    1dec:	00 97       	sbiw	r24, 0x00	; 0
    1dee:	29 f0       	breq	.+10     	; 0x1dfa <_ZN6String7reserveEj+0x1c>
    1df0:	2a 81       	ldd	r18, Y+2	; 0x02
    1df2:	3b 81       	ldd	r19, Y+3	; 0x03
    1df4:	26 17       	cp	r18, r22
    1df6:	37 07       	cpc	r19, r23
    1df8:	88 f4       	brcc	.+34     	; 0x1e1c <_ZN6String7reserveEj+0x3e>
    1dfa:	8b 01       	movw	r16, r22
    1dfc:	6f 5f       	subi	r22, 0xFF	; 255
    1dfe:	7f 4f       	sbci	r23, 0xFF	; 255
    1e00:	0e 94 53 2d 	call	0x5aa6	; 0x5aa6 <realloc>
    1e04:	00 97       	sbiw	r24, 0x00	; 0
    1e06:	61 f0       	breq	.+24     	; 0x1e20 <_ZN6String7reserveEj+0x42>
    1e08:	99 83       	std	Y+1, r25	; 0x01
    1e0a:	88 83       	st	Y, r24
    1e0c:	1b 83       	std	Y+3, r17	; 0x03
    1e0e:	0a 83       	std	Y+2, r16	; 0x02
    1e10:	2c 81       	ldd	r18, Y+4	; 0x04
    1e12:	3d 81       	ldd	r19, Y+5	; 0x05
    1e14:	23 2b       	or	r18, r19
    1e16:	11 f4       	brne	.+4      	; 0x1e1c <_ZN6String7reserveEj+0x3e>
    1e18:	fc 01       	movw	r30, r24
    1e1a:	10 82       	st	Z, r1
    1e1c:	81 e0       	ldi	r24, 0x01	; 1
    1e1e:	01 c0       	rjmp	.+2      	; 0x1e22 <_ZN6String7reserveEj+0x44>
    1e20:	80 e0       	ldi	r24, 0x00	; 0
    1e22:	df 91       	pop	r29
    1e24:	cf 91       	pop	r28
    1e26:	1f 91       	pop	r17
    1e28:	0f 91       	pop	r16
    1e2a:	08 95       	ret

00001e2c <_ZN6String6concatEc>:
    1e2c:	ef 92       	push	r14
    1e2e:	ff 92       	push	r15
    1e30:	0f 93       	push	r16
    1e32:	1f 93       	push	r17
    1e34:	cf 93       	push	r28
    1e36:	df 93       	push	r29
    1e38:	00 d0       	rcall	.+0      	; 0x1e3a <_ZN6String6concatEc+0xe>
    1e3a:	cd b7       	in	r28, 0x3d	; 61
    1e3c:	de b7       	in	r29, 0x3e	; 62
    1e3e:	8c 01       	movw	r16, r24
    1e40:	69 83       	std	Y+1, r22	; 0x01
    1e42:	1a 82       	std	Y+2, r1	; 0x02
    1e44:	fc 01       	movw	r30, r24
    1e46:	e4 80       	ldd	r14, Z+4	; 0x04
    1e48:	f5 80       	ldd	r15, Z+5	; 0x05
    1e4a:	ff ef       	ldi	r31, 0xFF	; 255
    1e4c:	ef 1a       	sub	r14, r31
    1e4e:	ff 0a       	sbc	r15, r31
    1e50:	b7 01       	movw	r22, r14
    1e52:	0e 94 ef 0e 	call	0x1dde	; 0x1dde <_ZN6String7reserveEj>
    1e56:	88 23       	and	r24, r24
    1e58:	81 f0       	breq	.+32     	; 0x1e7a <_ZN6String6concatEc+0x4e>
    1e5a:	f8 01       	movw	r30, r16
    1e5c:	20 81       	ld	r18, Z
    1e5e:	31 81       	ldd	r19, Z+1	; 0x01
    1e60:	84 81       	ldd	r24, Z+4	; 0x04
    1e62:	95 81       	ldd	r25, Z+5	; 0x05
    1e64:	be 01       	movw	r22, r28
    1e66:	6f 5f       	subi	r22, 0xFF	; 255
    1e68:	7f 4f       	sbci	r23, 0xFF	; 255
    1e6a:	82 0f       	add	r24, r18
    1e6c:	93 1f       	adc	r25, r19
    1e6e:	0e 94 3f 2e 	call	0x5c7e	; 0x5c7e <strcpy>
    1e72:	f8 01       	movw	r30, r16
    1e74:	f5 82       	std	Z+5, r15	; 0x05
    1e76:	e4 82       	std	Z+4, r14	; 0x04
    1e78:	81 e0       	ldi	r24, 0x01	; 1
    1e7a:	0f 90       	pop	r0
    1e7c:	0f 90       	pop	r0
    1e7e:	df 91       	pop	r29
    1e80:	cf 91       	pop	r28
    1e82:	1f 91       	pop	r17
    1e84:	0f 91       	pop	r16
    1e86:	ff 90       	pop	r15
    1e88:	ef 90       	pop	r14
    1e8a:	08 95       	ret

00001e8c <_ZN12StreamString5writeEh>:
    1e8c:	0c 96       	adiw	r24, 0x0c	; 12
    1e8e:	0e 94 16 0f 	call	0x1e2c	; 0x1e2c <_ZN6String6concatEc>
    1e92:	90 e0       	ldi	r25, 0x00	; 0
    1e94:	08 95       	ret

00001e96 <_ZN6String10invalidateEv>:
    1e96:	cf 93       	push	r28
    1e98:	df 93       	push	r29
    1e9a:	ec 01       	movw	r28, r24
    1e9c:	88 81       	ld	r24, Y
    1e9e:	99 81       	ldd	r25, Y+1	; 0x01
    1ea0:	00 97       	sbiw	r24, 0x00	; 0
    1ea2:	11 f0       	breq	.+4      	; 0x1ea8 <_ZN6String10invalidateEv+0x12>
    1ea4:	0e 94 ca 2c 	call	0x5994	; 0x5994 <free>
    1ea8:	19 82       	std	Y+1, r1	; 0x01
    1eaa:	18 82       	st	Y, r1
    1eac:	1d 82       	std	Y+5, r1	; 0x05
    1eae:	1c 82       	std	Y+4, r1	; 0x04
    1eb0:	1b 82       	std	Y+3, r1	; 0x03
    1eb2:	1a 82       	std	Y+2, r1	; 0x02
    1eb4:	df 91       	pop	r29
    1eb6:	cf 91       	pop	r28
    1eb8:	08 95       	ret

00001eba <_ZN12StreamString4readEv>:
    1eba:	1f 93       	push	r17
    1ebc:	cf 93       	push	r28
    1ebe:	df 93       	push	r29
    1ec0:	fc 01       	movw	r30, r24
    1ec2:	40 89       	ldd	r20, Z+16	; 0x10
    1ec4:	51 89       	ldd	r21, Z+17	; 0x11
    1ec6:	41 15       	cp	r20, r1
    1ec8:	51 05       	cpc	r21, r1
    1eca:	f9 f0       	breq	.+62     	; 0x1f0a <_ZN12StreamString4readEv+0x50>
    1ecc:	ec 01       	movw	r28, r24
    1ece:	84 85       	ldd	r24, Z+12	; 0x0c
    1ed0:	95 85       	ldd	r25, Z+13	; 0x0d
    1ed2:	bc 01       	movw	r22, r24
    1ed4:	fb 01       	movw	r30, r22
    1ed6:	11 91       	ld	r17, Z+
    1ed8:	bf 01       	movw	r22, r30
    1eda:	41 50       	subi	r20, 0x01	; 1
    1edc:	51 09       	sbc	r21, r1
    1ede:	59 8b       	std	Y+17, r21	; 0x11
    1ee0:	48 8b       	std	Y+16, r20	; 0x10
    1ee2:	0e 94 2b 2e 	call	0x5c56	; 0x5c56 <memcpy>
    1ee6:	ec 85       	ldd	r30, Y+12	; 0x0c
    1ee8:	fd 85       	ldd	r31, Y+13	; 0x0d
    1eea:	88 89       	ldd	r24, Y+16	; 0x10
    1eec:	99 89       	ldd	r25, Y+17	; 0x11
    1eee:	e8 0f       	add	r30, r24
    1ef0:	f9 1f       	adc	r31, r25
    1ef2:	10 82       	st	Z, r1
    1ef4:	88 89       	ldd	r24, Y+16	; 0x10
    1ef6:	99 89       	ldd	r25, Y+17	; 0x11
    1ef8:	89 2b       	or	r24, r25
    1efa:	21 f4       	brne	.+8      	; 0x1f04 <_ZN12StreamString4readEv+0x4a>
    1efc:	ce 01       	movw	r24, r28
    1efe:	0c 96       	adiw	r24, 0x0c	; 12
    1f00:	0e 94 4b 0f 	call	0x1e96	; 0x1e96 <_ZN6String10invalidateEv>
    1f04:	81 2f       	mov	r24, r17
    1f06:	90 e0       	ldi	r25, 0x00	; 0
    1f08:	02 c0       	rjmp	.+4      	; 0x1f0e <_ZN12StreamString4readEv+0x54>
    1f0a:	8f ef       	ldi	r24, 0xFF	; 255
    1f0c:	9f ef       	ldi	r25, 0xFF	; 255
    1f0e:	df 91       	pop	r29
    1f10:	cf 91       	pop	r28
    1f12:	1f 91       	pop	r17
    1f14:	08 95       	ret

00001f16 <_ZN12StreamString5writeEPKhj>:
    1f16:	cf 92       	push	r12
    1f18:	df 92       	push	r13
    1f1a:	ef 92       	push	r14
    1f1c:	ff 92       	push	r15
    1f1e:	0f 93       	push	r16
    1f20:	1f 93       	push	r17
    1f22:	cf 93       	push	r28
    1f24:	df 93       	push	r29
    1f26:	8c 01       	movw	r16, r24
    1f28:	7b 01       	movw	r14, r22
    1f2a:	ea 01       	movw	r28, r20
    1f2c:	0c 96       	adiw	r24, 0x0c	; 12
    1f2e:	6c 01       	movw	r12, r24
    1f30:	67 2b       	or	r22, r23
    1f32:	39 f0       	breq	.+14     	; 0x1f42 <_ZN12StreamString5writeEPKhj+0x2c>
    1f34:	20 97       	sbiw	r28, 0x00	; 0
    1f36:	29 f0       	breq	.+10     	; 0x1f42 <_ZN12StreamString5writeEPKhj+0x2c>
    1f38:	ba 01       	movw	r22, r20
    1f3a:	0e 94 ef 0e 	call	0x1dde	; 0x1dde <_ZN6String7reserveEj>
    1f3e:	81 11       	cpse	r24, r1
    1f40:	06 c0       	rjmp	.+12     	; 0x1f4e <_ZN12StreamString5writeEPKhj+0x38>
    1f42:	c6 01       	movw	r24, r12
    1f44:	0e 94 4b 0f 	call	0x1e96	; 0x1e96 <_ZN6String10invalidateEv>
    1f48:	80 e0       	ldi	r24, 0x00	; 0
    1f4a:	90 e0       	ldi	r25, 0x00	; 0
    1f4c:	16 c0       	rjmp	.+44     	; 0x1f7a <_ZN12StreamString5writeEPKhj+0x64>
    1f4e:	d8 01       	movw	r26, r16
    1f50:	51 96       	adiw	r26, 0x11	; 17
    1f52:	dc 93       	st	X, r29
    1f54:	ce 93       	st	-X, r28
    1f56:	50 97       	sbiw	r26, 0x10	; 16
    1f58:	ae 01       	movw	r20, r28
    1f5a:	b7 01       	movw	r22, r14
    1f5c:	1c 96       	adiw	r26, 0x0c	; 12
    1f5e:	8d 91       	ld	r24, X+
    1f60:	9c 91       	ld	r25, X
    1f62:	1d 97       	sbiw	r26, 0x0d	; 13
    1f64:	0e 94 2b 2e 	call	0x5c56	; 0x5c56 <memcpy>
    1f68:	d8 01       	movw	r26, r16
    1f6a:	1c 96       	adiw	r26, 0x0c	; 12
    1f6c:	ed 91       	ld	r30, X+
    1f6e:	fc 91       	ld	r31, X
    1f70:	1d 97       	sbiw	r26, 0x0d	; 13
    1f72:	ec 0f       	add	r30, r28
    1f74:	fd 1f       	adc	r31, r29
    1f76:	10 82       	st	Z, r1
    1f78:	ce 01       	movw	r24, r28
    1f7a:	df 91       	pop	r29
    1f7c:	cf 91       	pop	r28
    1f7e:	1f 91       	pop	r17
    1f80:	0f 91       	pop	r16
    1f82:	ff 90       	pop	r15
    1f84:	ef 90       	pop	r14
    1f86:	df 90       	pop	r13
    1f88:	cf 90       	pop	r12
    1f8a:	08 95       	ret

00001f8c <_ZN6StringD1Ev>:
    1f8c:	fc 01       	movw	r30, r24
    1f8e:	80 81       	ld	r24, Z
    1f90:	91 81       	ldd	r25, Z+1	; 0x01
    1f92:	0c 94 ca 2c 	jmp	0x5994	; 0x5994 <free>

00001f96 <_ZN13SerialTwoWire10_addBufferEv.part.4.constprop.19>:
    1f96:	0f 93       	push	r16
    1f98:	1f 93       	push	r17
    1f9a:	cf 93       	push	r28
    1f9c:	df 93       	push	r29
    1f9e:	00 d0       	rcall	.+0      	; 0x1fa0 <_ZN13SerialTwoWire10_addBufferEv.part.4.constprop.19+0xa>
    1fa0:	00 d0       	rcall	.+0      	; 0x1fa2 <_ZN13SerialTwoWire10_addBufferEv.part.4.constprop.19+0xc>
    1fa2:	00 d0       	rcall	.+0      	; 0x1fa4 <_ZN13SerialTwoWire10_addBufferEv.part.4.constprop.19+0xe>
    1fa4:	cd b7       	in	r28, 0x3d	; 61
    1fa6:	de b7       	in	r29, 0x3e	; 62
    1fa8:	40 e1       	ldi	r20, 0x10	; 16
    1faa:	50 e0       	ldi	r21, 0x00	; 0
    1fac:	60 e0       	ldi	r22, 0x00	; 0
    1fae:	70 e0       	ldi	r23, 0x00	; 0
    1fb0:	80 91 7b 03 	lds	r24, 0x037B	; 0x80037b <Wire+0x35>
    1fb4:	90 91 7c 03 	lds	r25, 0x037C	; 0x80037c <Wire+0x36>
    1fb8:	0e 94 e2 25 	call	0x4bc4	; 0x4bc4 <strtoul>
    1fbc:	20 91 65 03 	lds	r18, 0x0365	; 0x800365 <Wire+0x1f>
    1fc0:	30 91 66 03 	lds	r19, 0x0366	; 0x800366 <Wire+0x20>
    1fc4:	21 15       	cp	r18, r1
    1fc6:	31 05       	cpc	r19, r1
    1fc8:	d9 f4       	brne	.+54     	; 0x2000 <_ZN13SerialTwoWire10_addBufferEv.part.4.constprop.19+0x6a>
    1fca:	00 91 52 03 	lds	r16, 0x0352	; 0x800352 <Wire+0xc>
    1fce:	10 e0       	ldi	r17, 0x00	; 0
    1fd0:	20 e0       	ldi	r18, 0x00	; 0
    1fd2:	30 e0       	ldi	r19, 0x00	; 0
    1fd4:	60 17       	cp	r22, r16
    1fd6:	71 07       	cpc	r23, r17
    1fd8:	82 07       	cpc	r24, r18
    1fda:	93 07       	cpc	r25, r19
    1fdc:	a1 f0       	breq	.+40     	; 0x2006 <_ZN13SerialTwoWire10_addBufferEv.part.4.constprop.19+0x70>
    1fde:	00 91 53 03 	lds	r16, 0x0353	; 0x800353 <Wire+0xd>
    1fe2:	10 e0       	ldi	r17, 0x00	; 0
    1fe4:	20 e0       	ldi	r18, 0x00	; 0
    1fe6:	30 e0       	ldi	r19, 0x00	; 0
    1fe8:	60 17       	cp	r22, r16
    1fea:	71 07       	cpc	r23, r17
    1fec:	82 07       	cpc	r24, r18
    1fee:	93 07       	cpc	r25, r19
    1ff0:	51 f0       	breq	.+20     	; 0x2006 <_ZN13SerialTwoWire10_addBufferEv.part.4.constprop.19+0x70>
    1ff2:	8f ef       	ldi	r24, 0xFF	; 255
    1ff4:	9f ef       	ldi	r25, 0xFF	; 255
    1ff6:	90 93 7a 03 	sts	0x037A, r25	; 0x80037a <Wire+0x34>
    1ffa:	80 93 79 03 	sts	0x0379, r24	; 0x800379 <Wire+0x33>
    1ffe:	13 c0       	rjmp	.+38     	; 0x2026 <_ZN13SerialTwoWire10_addBufferEv.part.4.constprop.19+0x90>
    2000:	2c 3d       	cpi	r18, 0xDC	; 220
    2002:	31 05       	cpc	r19, r1
    2004:	b0 f7       	brcc	.-20     	; 0x1ff2 <_ZN13SerialTwoWire10_addBufferEv.part.4.constprop.19+0x5c>
    2006:	85 e5       	ldi	r24, 0x55	; 85
    2008:	93 e0       	ldi	r25, 0x03	; 3
    200a:	0e 94 46 0f 	call	0x1e8c	; 0x1e8c <_ZN12StreamString5writeEh>
    200e:	ce 01       	movw	r24, r28
    2010:	01 96       	adiw	r24, 0x01	; 1
    2012:	0e 94 d5 1b 	call	0x37aa	; 0x37aa <_ZN6StringC2EPKc.constprop.37>
    2016:	ce 01       	movw	r24, r28
    2018:	01 96       	adiw	r24, 0x01	; 1
    201a:	0e 94 98 1b 	call	0x3730	; 0x3730 <_ZN6String4moveERS_.constprop.40>
    201e:	ce 01       	movw	r24, r28
    2020:	01 96       	adiw	r24, 0x01	; 1
    2022:	0e 94 c6 0f 	call	0x1f8c	; 0x1f8c <_ZN6StringD1Ev>
    2026:	26 96       	adiw	r28, 0x06	; 6
    2028:	0f b6       	in	r0, 0x3f	; 63
    202a:	f8 94       	cli
    202c:	de bf       	out	0x3e, r29	; 62
    202e:	0f be       	out	0x3f, r0	; 63
    2030:	cd bf       	out	0x3d, r28	; 61
    2032:	df 91       	pop	r29
    2034:	cf 91       	pop	r28
    2036:	1f 91       	pop	r17
    2038:	0f 91       	pop	r16
    203a:	08 95       	ret

0000203c <__vector_2>:
    203c:	1f 92       	push	r1
    203e:	0f 92       	push	r0
    2040:	0f b6       	in	r0, 0x3f	; 63
    2042:	0f 92       	push	r0
    2044:	11 24       	eor	r1, r1
    2046:	2f 93       	push	r18
    2048:	3f 93       	push	r19
    204a:	4f 93       	push	r20
    204c:	5f 93       	push	r21
    204e:	6f 93       	push	r22
    2050:	7f 93       	push	r23
    2052:	8f 93       	push	r24
    2054:	9f 93       	push	r25
    2056:	af 93       	push	r26
    2058:	bf 93       	push	r27
    205a:	ef 93       	push	r30
    205c:	ff 93       	push	r31
    205e:	e0 91 06 01 	lds	r30, 0x0106	; 0x800106 <intFunc.lto_priv.98+0x2>
    2062:	f0 91 07 01 	lds	r31, 0x0107	; 0x800107 <intFunc.lto_priv.98+0x3>
    2066:	09 95       	icall
    2068:	ff 91       	pop	r31
    206a:	ef 91       	pop	r30
    206c:	bf 91       	pop	r27
    206e:	af 91       	pop	r26
    2070:	9f 91       	pop	r25
    2072:	8f 91       	pop	r24
    2074:	7f 91       	pop	r23
    2076:	6f 91       	pop	r22
    2078:	5f 91       	pop	r21
    207a:	4f 91       	pop	r20
    207c:	3f 91       	pop	r19
    207e:	2f 91       	pop	r18
    2080:	0f 90       	pop	r0
    2082:	0f be       	out	0x3f, r0	; 63
    2084:	0f 90       	pop	r0
    2086:	1f 90       	pop	r1
    2088:	18 95       	reti

0000208a <__vector_1>:
    208a:	1f 92       	push	r1
    208c:	0f 92       	push	r0
    208e:	0f b6       	in	r0, 0x3f	; 63
    2090:	0f 92       	push	r0
    2092:	11 24       	eor	r1, r1
    2094:	2f 93       	push	r18
    2096:	3f 93       	push	r19
    2098:	4f 93       	push	r20
    209a:	5f 93       	push	r21
    209c:	6f 93       	push	r22
    209e:	7f 93       	push	r23
    20a0:	8f 93       	push	r24
    20a2:	9f 93       	push	r25
    20a4:	af 93       	push	r26
    20a6:	bf 93       	push	r27
    20a8:	ef 93       	push	r30
    20aa:	ff 93       	push	r31
    20ac:	e0 91 04 01 	lds	r30, 0x0104	; 0x800104 <intFunc.lto_priv.98>
    20b0:	f0 91 05 01 	lds	r31, 0x0105	; 0x800105 <intFunc.lto_priv.98+0x1>
    20b4:	09 95       	icall
    20b6:	ff 91       	pop	r31
    20b8:	ef 91       	pop	r30
    20ba:	bf 91       	pop	r27
    20bc:	af 91       	pop	r26
    20be:	9f 91       	pop	r25
    20c0:	8f 91       	pop	r24
    20c2:	7f 91       	pop	r23
    20c4:	6f 91       	pop	r22
    20c6:	5f 91       	pop	r21
    20c8:	4f 91       	pop	r20
    20ca:	3f 91       	pop	r19
    20cc:	2f 91       	pop	r18
    20ce:	0f 90       	pop	r0
    20d0:	0f be       	out	0x3f, r0	; 63
    20d2:	0f 90       	pop	r0
    20d4:	1f 90       	pop	r1
    20d6:	18 95       	reti

000020d8 <_ZN5Print5writeEPKhj>:
    20d8:	cf 92       	push	r12
    20da:	df 92       	push	r13
    20dc:	ef 92       	push	r14
    20de:	ff 92       	push	r15
    20e0:	0f 93       	push	r16
    20e2:	1f 93       	push	r17
    20e4:	cf 93       	push	r28
    20e6:	df 93       	push	r29
    20e8:	6c 01       	movw	r12, r24
    20ea:	7a 01       	movw	r14, r20
    20ec:	8b 01       	movw	r16, r22
    20ee:	c0 e0       	ldi	r28, 0x00	; 0
    20f0:	d0 e0       	ldi	r29, 0x00	; 0
    20f2:	ce 15       	cp	r28, r14
    20f4:	df 05       	cpc	r29, r15
    20f6:	81 f0       	breq	.+32     	; 0x2118 <_ZN5Print5writeEPKhj+0x40>
    20f8:	d8 01       	movw	r26, r16
    20fa:	6d 91       	ld	r22, X+
    20fc:	8d 01       	movw	r16, r26
    20fe:	d6 01       	movw	r26, r12
    2100:	ed 91       	ld	r30, X+
    2102:	fc 91       	ld	r31, X
    2104:	01 90       	ld	r0, Z+
    2106:	f0 81       	ld	r31, Z
    2108:	e0 2d       	mov	r30, r0
    210a:	c6 01       	movw	r24, r12
    210c:	09 95       	icall
    210e:	89 2b       	or	r24, r25
    2110:	11 f0       	breq	.+4      	; 0x2116 <_ZN5Print5writeEPKhj+0x3e>
    2112:	21 96       	adiw	r28, 0x01	; 1
    2114:	ee cf       	rjmp	.-36     	; 0x20f2 <_ZN5Print5writeEPKhj+0x1a>
    2116:	7e 01       	movw	r14, r28
    2118:	c7 01       	movw	r24, r14
    211a:	df 91       	pop	r29
    211c:	cf 91       	pop	r28
    211e:	1f 91       	pop	r17
    2120:	0f 91       	pop	r16
    2122:	ff 90       	pop	r15
    2124:	ef 90       	pop	r14
    2126:	df 90       	pop	r13
    2128:	cf 90       	pop	r12
    212a:	08 95       	ret

0000212c <_ZN14HardwareSerial17availableForWriteEv>:
    212c:	fc 01       	movw	r30, r24
    212e:	53 8d       	ldd	r21, Z+27	; 0x1b
    2130:	44 8d       	ldd	r20, Z+28	; 0x1c
    2132:	25 2f       	mov	r18, r21
    2134:	30 e0       	ldi	r19, 0x00	; 0
    2136:	84 2f       	mov	r24, r20
    2138:	90 e0       	ldi	r25, 0x00	; 0
    213a:	82 1b       	sub	r24, r18
    213c:	93 0b       	sbc	r25, r19
    213e:	54 17       	cp	r21, r20
    2140:	10 f0       	brcs	.+4      	; 0x2146 <_ZN14HardwareSerial17availableForWriteEv+0x1a>
    2142:	cf 96       	adiw	r24, 0x3f	; 63
    2144:	08 95       	ret
    2146:	01 97       	sbiw	r24, 0x01	; 1
    2148:	08 95       	ret

0000214a <_ZN14HardwareSerial4readEv>:
    214a:	fc 01       	movw	r30, r24
    214c:	91 8d       	ldd	r25, Z+25	; 0x19
    214e:	82 8d       	ldd	r24, Z+26	; 0x1a
    2150:	98 17       	cp	r25, r24
    2152:	61 f0       	breq	.+24     	; 0x216c <_ZN14HardwareSerial4readEv+0x22>
    2154:	82 8d       	ldd	r24, Z+26	; 0x1a
    2156:	df 01       	movw	r26, r30
    2158:	a8 0f       	add	r26, r24
    215a:	b1 1d       	adc	r27, r1
    215c:	5d 96       	adiw	r26, 0x1d	; 29
    215e:	8c 91       	ld	r24, X
    2160:	92 8d       	ldd	r25, Z+26	; 0x1a
    2162:	9f 5f       	subi	r25, 0xFF	; 255
    2164:	9f 73       	andi	r25, 0x3F	; 63
    2166:	92 8f       	std	Z+26, r25	; 0x1a
    2168:	90 e0       	ldi	r25, 0x00	; 0
    216a:	08 95       	ret
    216c:	8f ef       	ldi	r24, 0xFF	; 255
    216e:	9f ef       	ldi	r25, 0xFF	; 255
    2170:	08 95       	ret

00002172 <_ZN14HardwareSerial4peekEv>:
    2172:	fc 01       	movw	r30, r24
    2174:	91 8d       	ldd	r25, Z+25	; 0x19
    2176:	82 8d       	ldd	r24, Z+26	; 0x1a
    2178:	98 17       	cp	r25, r24
    217a:	31 f0       	breq	.+12     	; 0x2188 <_ZN14HardwareSerial4peekEv+0x16>
    217c:	82 8d       	ldd	r24, Z+26	; 0x1a
    217e:	e8 0f       	add	r30, r24
    2180:	f1 1d       	adc	r31, r1
    2182:	85 8d       	ldd	r24, Z+29	; 0x1d
    2184:	90 e0       	ldi	r25, 0x00	; 0
    2186:	08 95       	ret
    2188:	8f ef       	ldi	r24, 0xFF	; 255
    218a:	9f ef       	ldi	r25, 0xFF	; 255
    218c:	08 95       	ret

0000218e <_ZN14HardwareSerial9availableEv>:
    218e:	fc 01       	movw	r30, r24
    2190:	91 8d       	ldd	r25, Z+25	; 0x19
    2192:	22 8d       	ldd	r18, Z+26	; 0x1a
    2194:	89 2f       	mov	r24, r25
    2196:	90 e0       	ldi	r25, 0x00	; 0
    2198:	80 5c       	subi	r24, 0xC0	; 192
    219a:	9f 4f       	sbci	r25, 0xFF	; 255
    219c:	82 1b       	sub	r24, r18
    219e:	91 09       	sbc	r25, r1
    21a0:	8f 73       	andi	r24, 0x3F	; 63
    21a2:	99 27       	eor	r25, r25
    21a4:	08 95       	ret

000021a6 <_Z17Serial0_availablev>:
    21a6:	89 ea       	ldi	r24, 0xA9	; 169
    21a8:	92 e0       	ldi	r25, 0x02	; 2
    21aa:	0e 94 c7 10 	call	0x218e	; 0x218e <_ZN14HardwareSerial9availableEv>
    21ae:	21 e0       	ldi	r18, 0x01	; 1
    21b0:	89 2b       	or	r24, r25
    21b2:	09 f4       	brne	.+2      	; 0x21b6 <_Z17Serial0_availablev+0x10>
    21b4:	20 e0       	ldi	r18, 0x00	; 0
    21b6:	82 2f       	mov	r24, r18
    21b8:	08 95       	ret

000021ba <_ZN14HardwareSerial17_tx_udr_empty_irqEv>:
    21ba:	fc 01       	movw	r30, r24
    21bc:	84 8d       	ldd	r24, Z+28	; 0x1c
    21be:	df 01       	movw	r26, r30
    21c0:	a8 0f       	add	r26, r24
    21c2:	b1 1d       	adc	r27, r1
    21c4:	a3 5a       	subi	r26, 0xA3	; 163
    21c6:	bf 4f       	sbci	r27, 0xFF	; 255
    21c8:	2c 91       	ld	r18, X
    21ca:	84 8d       	ldd	r24, Z+28	; 0x1c
    21cc:	90 e0       	ldi	r25, 0x00	; 0
    21ce:	01 96       	adiw	r24, 0x01	; 1
    21d0:	8f 73       	andi	r24, 0x3F	; 63
    21d2:	99 27       	eor	r25, r25
    21d4:	84 8f       	std	Z+28, r24	; 0x1c
    21d6:	a6 89       	ldd	r26, Z+22	; 0x16
    21d8:	b7 89       	ldd	r27, Z+23	; 0x17
    21da:	2c 93       	st	X, r18
    21dc:	a0 89       	ldd	r26, Z+16	; 0x10
    21de:	b1 89       	ldd	r27, Z+17	; 0x11
    21e0:	8c 91       	ld	r24, X
    21e2:	83 70       	andi	r24, 0x03	; 3
    21e4:	80 64       	ori	r24, 0x40	; 64
    21e6:	8c 93       	st	X, r24
    21e8:	93 8d       	ldd	r25, Z+27	; 0x1b
    21ea:	84 8d       	ldd	r24, Z+28	; 0x1c
    21ec:	98 13       	cpse	r25, r24
    21ee:	06 c0       	rjmp	.+12     	; 0x21fc <_ZN14HardwareSerial17_tx_udr_empty_irqEv+0x42>
    21f0:	02 88       	ldd	r0, Z+18	; 0x12
    21f2:	f3 89       	ldd	r31, Z+19	; 0x13
    21f4:	e0 2d       	mov	r30, r0
    21f6:	80 81       	ld	r24, Z
    21f8:	8f 7d       	andi	r24, 0xDF	; 223
    21fa:	80 83       	st	Z, r24
    21fc:	08 95       	ret

000021fe <_ZN14HardwareSerial5writeEh>:
    21fe:	ef 92       	push	r14
    2200:	ff 92       	push	r15
    2202:	0f 93       	push	r16
    2204:	1f 93       	push	r17
    2206:	cf 93       	push	r28
    2208:	df 93       	push	r29
    220a:	ec 01       	movw	r28, r24
    220c:	81 e0       	ldi	r24, 0x01	; 1
    220e:	88 8f       	std	Y+24, r24	; 0x18
    2210:	9b 8d       	ldd	r25, Y+27	; 0x1b
    2212:	8c 8d       	ldd	r24, Y+28	; 0x1c
    2214:	98 13       	cpse	r25, r24
    2216:	05 c0       	rjmp	.+10     	; 0x2222 <_ZN14HardwareSerial5writeEh+0x24>
    2218:	e8 89       	ldd	r30, Y+16	; 0x10
    221a:	f9 89       	ldd	r31, Y+17	; 0x11
    221c:	80 81       	ld	r24, Z
    221e:	85 fd       	sbrc	r24, 5
    2220:	26 c0       	rjmp	.+76     	; 0x226e <_ZN14HardwareSerial5writeEh+0x70>
    2222:	f6 2e       	mov	r15, r22
    2224:	0b 8d       	ldd	r16, Y+27	; 0x1b
    2226:	10 e0       	ldi	r17, 0x00	; 0
    2228:	0f 5f       	subi	r16, 0xFF	; 255
    222a:	1f 4f       	sbci	r17, 0xFF	; 255
    222c:	0f 73       	andi	r16, 0x3F	; 63
    222e:	11 27       	eor	r17, r17
    2230:	e0 2e       	mov	r14, r16
    2232:	8c 8d       	ldd	r24, Y+28	; 0x1c
    2234:	e8 12       	cpse	r14, r24
    2236:	0c c0       	rjmp	.+24     	; 0x2250 <_ZN14HardwareSerial5writeEh+0x52>
    2238:	0f b6       	in	r0, 0x3f	; 63
    223a:	07 fc       	sbrc	r0, 7
    223c:	fa cf       	rjmp	.-12     	; 0x2232 <_ZN14HardwareSerial5writeEh+0x34>
    223e:	e8 89       	ldd	r30, Y+16	; 0x10
    2240:	f9 89       	ldd	r31, Y+17	; 0x11
    2242:	80 81       	ld	r24, Z
    2244:	85 ff       	sbrs	r24, 5
    2246:	f5 cf       	rjmp	.-22     	; 0x2232 <_ZN14HardwareSerial5writeEh+0x34>
    2248:	ce 01       	movw	r24, r28
    224a:	0e 94 dd 10 	call	0x21ba	; 0x21ba <_ZN14HardwareSerial17_tx_udr_empty_irqEv>
    224e:	f1 cf       	rjmp	.-30     	; 0x2232 <_ZN14HardwareSerial5writeEh+0x34>
    2250:	8b 8d       	ldd	r24, Y+27	; 0x1b
    2252:	fe 01       	movw	r30, r28
    2254:	e8 0f       	add	r30, r24
    2256:	f1 1d       	adc	r31, r1
    2258:	e3 5a       	subi	r30, 0xA3	; 163
    225a:	ff 4f       	sbci	r31, 0xFF	; 255
    225c:	f0 82       	st	Z, r15
    225e:	9f b7       	in	r25, 0x3f	; 63
    2260:	f8 94       	cli
    2262:	0b 8f       	std	Y+27, r16	; 0x1b
    2264:	ea 89       	ldd	r30, Y+18	; 0x12
    2266:	fb 89       	ldd	r31, Y+19	; 0x13
    2268:	80 81       	ld	r24, Z
    226a:	80 62       	ori	r24, 0x20	; 32
    226c:	0a c0       	rjmp	.+20     	; 0x2282 <_ZN14HardwareSerial5writeEh+0x84>
    226e:	9f b7       	in	r25, 0x3f	; 63
    2270:	f8 94       	cli
    2272:	ee 89       	ldd	r30, Y+22	; 0x16
    2274:	ff 89       	ldd	r31, Y+23	; 0x17
    2276:	60 83       	st	Z, r22
    2278:	e8 89       	ldd	r30, Y+16	; 0x10
    227a:	f9 89       	ldd	r31, Y+17	; 0x11
    227c:	80 81       	ld	r24, Z
    227e:	83 70       	andi	r24, 0x03	; 3
    2280:	80 64       	ori	r24, 0x40	; 64
    2282:	80 83       	st	Z, r24
    2284:	9f bf       	out	0x3f, r25	; 63
    2286:	81 e0       	ldi	r24, 0x01	; 1
    2288:	90 e0       	ldi	r25, 0x00	; 0
    228a:	df 91       	pop	r29
    228c:	cf 91       	pop	r28
    228e:	1f 91       	pop	r17
    2290:	0f 91       	pop	r16
    2292:	ff 90       	pop	r15
    2294:	ef 90       	pop	r14
    2296:	08 95       	ret

00002298 <_ZN14HardwareSerial5flushEv>:
    2298:	cf 93       	push	r28
    229a:	df 93       	push	r29
    229c:	ec 01       	movw	r28, r24
    229e:	88 8d       	ldd	r24, Y+24	; 0x18
    22a0:	88 23       	and	r24, r24
    22a2:	c9 f0       	breq	.+50     	; 0x22d6 <_ZN14HardwareSerial5flushEv+0x3e>
    22a4:	ea 89       	ldd	r30, Y+18	; 0x12
    22a6:	fb 89       	ldd	r31, Y+19	; 0x13
    22a8:	80 81       	ld	r24, Z
    22aa:	85 fd       	sbrc	r24, 5
    22ac:	05 c0       	rjmp	.+10     	; 0x22b8 <_ZN14HardwareSerial5flushEv+0x20>
    22ae:	a8 89       	ldd	r26, Y+16	; 0x10
    22b0:	b9 89       	ldd	r27, Y+17	; 0x11
    22b2:	8c 91       	ld	r24, X
    22b4:	86 fd       	sbrc	r24, 6
    22b6:	0f c0       	rjmp	.+30     	; 0x22d6 <_ZN14HardwareSerial5flushEv+0x3e>
    22b8:	0f b6       	in	r0, 0x3f	; 63
    22ba:	07 fc       	sbrc	r0, 7
    22bc:	f5 cf       	rjmp	.-22     	; 0x22a8 <_ZN14HardwareSerial5flushEv+0x10>
    22be:	80 81       	ld	r24, Z
    22c0:	85 ff       	sbrs	r24, 5
    22c2:	f2 cf       	rjmp	.-28     	; 0x22a8 <_ZN14HardwareSerial5flushEv+0x10>
    22c4:	a8 89       	ldd	r26, Y+16	; 0x10
    22c6:	b9 89       	ldd	r27, Y+17	; 0x11
    22c8:	8c 91       	ld	r24, X
    22ca:	85 ff       	sbrs	r24, 5
    22cc:	ed cf       	rjmp	.-38     	; 0x22a8 <_ZN14HardwareSerial5flushEv+0x10>
    22ce:	ce 01       	movw	r24, r28
    22d0:	0e 94 dd 10 	call	0x21ba	; 0x21ba <_ZN14HardwareSerial17_tx_udr_empty_irqEv>
    22d4:	e7 cf       	rjmp	.-50     	; 0x22a4 <_ZN14HardwareSerial5flushEv+0xc>
    22d6:	df 91       	pop	r29
    22d8:	cf 91       	pop	r28
    22da:	08 95       	ret

000022dc <_ZN13SerialTwoWire9availableEv>:
    22dc:	fc 01       	movw	r30, r24
    22de:	83 a9       	ldd	r24, Z+51	; 0x33
    22e0:	94 a9       	ldd	r25, Z+52	; 0x34
    22e2:	89 2b       	or	r24, r25
    22e4:	29 f4       	brne	.+10     	; 0x22f0 <_ZN13SerialTwoWire9availableEv+0x14>
    22e6:	81 e0       	ldi	r24, 0x01	; 1
    22e8:	27 8d       	ldd	r18, Z+31	; 0x1f
    22ea:	30 a1       	ldd	r19, Z+32	; 0x20
    22ec:	23 2b       	or	r18, r19
    22ee:	09 f4       	brne	.+2      	; 0x22f2 <_ZN13SerialTwoWire9availableEv+0x16>
    22f0:	80 e0       	ldi	r24, 0x00	; 0
    22f2:	90 e0       	ldi	r25, 0x00	; 0
    22f4:	08 95       	ret

000022f6 <_ZN13SerialTwoWire5writeEPKhj>:
    22f6:	cf 92       	push	r12
    22f8:	df 92       	push	r13
    22fa:	ef 92       	push	r14
    22fc:	ff 92       	push	r15
    22fe:	0f 93       	push	r16
    2300:	1f 93       	push	r17
    2302:	cf 93       	push	r28
    2304:	df 93       	push	r29
    2306:	8a 01       	movw	r16, r20
    2308:	eb 01       	movw	r28, r22
    230a:	6b 01       	movw	r12, r22
    230c:	c4 0e       	add	r12, r20
    230e:	d5 1e       	adc	r13, r21
    2310:	81 96       	adiw	r24, 0x21	; 33
    2312:	7c 01       	movw	r14, r24
    2314:	cc 15       	cp	r28, r12
    2316:	dd 05       	cpc	r29, r13
    2318:	29 f0       	breq	.+10     	; 0x2324 <_ZN13SerialTwoWire5writeEPKhj+0x2e>
    231a:	69 91       	ld	r22, Y+
    231c:	c7 01       	movw	r24, r14
    231e:	0e 94 46 0f 	call	0x1e8c	; 0x1e8c <_ZN12StreamString5writeEh>
    2322:	f8 cf       	rjmp	.-16     	; 0x2314 <_ZN13SerialTwoWire5writeEPKhj+0x1e>
    2324:	c8 01       	movw	r24, r16
    2326:	df 91       	pop	r29
    2328:	cf 91       	pop	r28
    232a:	1f 91       	pop	r17
    232c:	0f 91       	pop	r16
    232e:	ff 90       	pop	r15
    2330:	ef 90       	pop	r14
    2332:	df 90       	pop	r13
    2334:	cf 90       	pop	r12
    2336:	08 95       	ret

00002338 <_ZN5Print17availableForWriteEv>:
    2338:	80 e0       	ldi	r24, 0x00	; 0
    233a:	90 e0       	ldi	r25, 0x00	; 0
    233c:	08 95       	ret

0000233e <_ZN13SerialTwoWire4peekEv>:
    233e:	0f 96       	adiw	r24, 0x0f	; 15
    2340:	0c 94 e5 0d 	jmp	0x1bca	; 0x1bca <_ZN12StreamString4peekEv>

00002344 <_ZN13SerialTwoWire4readEv>:
    2344:	0f 96       	adiw	r24, 0x0f	; 15
    2346:	0c 94 5d 0f 	jmp	0x1eba	; 0x1eba <_ZN12StreamString4readEv>

0000234a <_ZN13SerialTwoWire5writeEh>:
    234a:	8d 96       	adiw	r24, 0x2d	; 45
    234c:	0e 94 16 0f 	call	0x1e2c	; 0x1e2c <_ZN6String6concatEc>
    2350:	90 e0       	ldi	r25, 0x00	; 0
    2352:	08 95       	ret

00002354 <_ZN5Print5printEc>:
    2354:	dc 01       	movw	r26, r24
    2356:	ed 91       	ld	r30, X+
    2358:	fc 91       	ld	r31, X
    235a:	01 90       	ld	r0, Z+
    235c:	f0 81       	ld	r31, Z
    235e:	e0 2d       	mov	r30, r0
    2360:	09 94       	ijmp

00002362 <_ZN5Print5printEPK19__FlashStringHelper>:
    2362:	ef 92       	push	r14
    2364:	ff 92       	push	r15
    2366:	0f 93       	push	r16
    2368:	1f 93       	push	r17
    236a:	cf 93       	push	r28
    236c:	df 93       	push	r29
    236e:	8c 01       	movw	r16, r24
    2370:	7b 01       	movw	r14, r22
    2372:	c0 e0       	ldi	r28, 0x00	; 0
    2374:	d0 e0       	ldi	r29, 0x00	; 0
    2376:	f7 01       	movw	r30, r14
    2378:	ec 0f       	add	r30, r28
    237a:	fd 1f       	adc	r31, r29
    237c:	64 91       	lpm	r22, Z
    237e:	66 23       	and	r22, r22
    2380:	61 f0       	breq	.+24     	; 0x239a <_ZN5Print5printEPK19__FlashStringHelper+0x38>
    2382:	d8 01       	movw	r26, r16
    2384:	ed 91       	ld	r30, X+
    2386:	fc 91       	ld	r31, X
    2388:	01 90       	ld	r0, Z+
    238a:	f0 81       	ld	r31, Z
    238c:	e0 2d       	mov	r30, r0
    238e:	c8 01       	movw	r24, r16
    2390:	09 95       	icall
    2392:	89 2b       	or	r24, r25
    2394:	11 f0       	breq	.+4      	; 0x239a <_ZN5Print5printEPK19__FlashStringHelper+0x38>
    2396:	21 96       	adiw	r28, 0x01	; 1
    2398:	ee cf       	rjmp	.-36     	; 0x2376 <_ZN5Print5printEPK19__FlashStringHelper+0x14>
    239a:	ce 01       	movw	r24, r28
    239c:	df 91       	pop	r29
    239e:	cf 91       	pop	r28
    23a0:	1f 91       	pop	r17
    23a2:	0f 91       	pop	r16
    23a4:	ff 90       	pop	r15
    23a6:	ef 90       	pop	r14
    23a8:	08 95       	ret

000023aa <_Z3remv>:
    23aa:	62 ef       	ldi	r22, 0xF2	; 242
    23ac:	72 e0       	ldi	r23, 0x02	; 2
    23ae:	89 ea       	ldi	r24, 0xA9	; 169
    23b0:	92 e0       	ldi	r25, 0x02	; 2
    23b2:	0c 94 b1 11 	jmp	0x2362	; 0x2362 <_ZN5Print5printEPK19__FlashStringHelper>

000023b6 <_ZN5Print5writeEPKc>:
    23b6:	61 15       	cp	r22, r1
    23b8:	71 05       	cpc	r23, r1
    23ba:	79 f0       	breq	.+30     	; 0x23da <_ZN5Print5writeEPKc+0x24>
    23bc:	fb 01       	movw	r30, r22
    23be:	01 90       	ld	r0, Z+
    23c0:	00 20       	and	r0, r0
    23c2:	e9 f7       	brne	.-6      	; 0x23be <_ZN5Print5writeEPKc+0x8>
    23c4:	31 97       	sbiw	r30, 0x01	; 1
    23c6:	af 01       	movw	r20, r30
    23c8:	46 1b       	sub	r20, r22
    23ca:	57 0b       	sbc	r21, r23
    23cc:	dc 01       	movw	r26, r24
    23ce:	ed 91       	ld	r30, X+
    23d0:	fc 91       	ld	r31, X
    23d2:	02 80       	ldd	r0, Z+2	; 0x02
    23d4:	f3 81       	ldd	r31, Z+3	; 0x03
    23d6:	e0 2d       	mov	r30, r0
    23d8:	09 94       	ijmp
    23da:	80 e0       	ldi	r24, 0x00	; 0
    23dc:	90 e0       	ldi	r25, 0x00	; 0
    23de:	08 95       	ret

000023e0 <_ZN5Print11printNumberEmh>:
    23e0:	8f 92       	push	r8
    23e2:	9f 92       	push	r9
    23e4:	af 92       	push	r10
    23e6:	bf 92       	push	r11
    23e8:	ef 92       	push	r14
    23ea:	ff 92       	push	r15
    23ec:	0f 93       	push	r16
    23ee:	1f 93       	push	r17
    23f0:	cf 93       	push	r28
    23f2:	df 93       	push	r29
    23f4:	cd b7       	in	r28, 0x3d	; 61
    23f6:	de b7       	in	r29, 0x3e	; 62
    23f8:	a1 97       	sbiw	r28, 0x21	; 33
    23fa:	0f b6       	in	r0, 0x3f	; 63
    23fc:	f8 94       	cli
    23fe:	de bf       	out	0x3e, r29	; 62
    2400:	0f be       	out	0x3f, r0	; 63
    2402:	cd bf       	out	0x3d, r28	; 61
    2404:	7c 01       	movw	r14, r24
    2406:	fa 01       	movw	r30, r20
    2408:	cb 01       	movw	r24, r22
    240a:	19 a2       	std	Y+33, r1	; 0x21
    240c:	22 30       	cpi	r18, 0x02	; 2
    240e:	08 f4       	brcc	.+2      	; 0x2412 <_ZN5Print11printNumberEmh+0x32>
    2410:	2a e0       	ldi	r18, 0x0A	; 10
    2412:	8e 01       	movw	r16, r28
    2414:	0f 5d       	subi	r16, 0xDF	; 223
    2416:	1f 4f       	sbci	r17, 0xFF	; 255
    2418:	82 2e       	mov	r8, r18
    241a:	91 2c       	mov	r9, r1
    241c:	a1 2c       	mov	r10, r1
    241e:	b1 2c       	mov	r11, r1
    2420:	bf 01       	movw	r22, r30
    2422:	a5 01       	movw	r20, r10
    2424:	94 01       	movw	r18, r8
    2426:	0e 94 38 2a 	call	0x5470	; 0x5470 <__udivmodsi4>
    242a:	f9 01       	movw	r30, r18
    242c:	ca 01       	movw	r24, r20
    242e:	01 50       	subi	r16, 0x01	; 1
    2430:	11 09       	sbc	r17, r1
    2432:	6a 30       	cpi	r22, 0x0A	; 10
    2434:	14 f4       	brge	.+4      	; 0x243a <_ZN5Print11printNumberEmh+0x5a>
    2436:	60 5d       	subi	r22, 0xD0	; 208
    2438:	01 c0       	rjmp	.+2      	; 0x243c <_ZN5Print11printNumberEmh+0x5c>
    243a:	69 5c       	subi	r22, 0xC9	; 201
    243c:	d8 01       	movw	r26, r16
    243e:	6c 93       	st	X, r22
    2440:	23 2b       	or	r18, r19
    2442:	24 2b       	or	r18, r20
    2444:	25 2b       	or	r18, r21
    2446:	61 f7       	brne	.-40     	; 0x2420 <_ZN5Print11printNumberEmh+0x40>
    2448:	b8 01       	movw	r22, r16
    244a:	c7 01       	movw	r24, r14
    244c:	0e 94 db 11 	call	0x23b6	; 0x23b6 <_ZN5Print5writeEPKc>
    2450:	a1 96       	adiw	r28, 0x21	; 33
    2452:	0f b6       	in	r0, 0x3f	; 63
    2454:	f8 94       	cli
    2456:	de bf       	out	0x3e, r29	; 62
    2458:	0f be       	out	0x3f, r0	; 63
    245a:	cd bf       	out	0x3d, r28	; 61
    245c:	df 91       	pop	r29
    245e:	cf 91       	pop	r28
    2460:	1f 91       	pop	r17
    2462:	0f 91       	pop	r16
    2464:	ff 90       	pop	r15
    2466:	ef 90       	pop	r14
    2468:	bf 90       	pop	r11
    246a:	af 90       	pop	r10
    246c:	9f 90       	pop	r9
    246e:	8f 90       	pop	r8
    2470:	08 95       	ret

00002472 <_ZN5Print7printlnEv>:
    2472:	68 ec       	ldi	r22, 0xC8	; 200
    2474:	71 e0       	ldi	r23, 0x01	; 1
    2476:	0c 94 db 11 	jmp	0x23b6	; 0x23b6 <_ZN5Print5writeEPKc>

0000247a <__vector_19>:
    247a:	1f 92       	push	r1
    247c:	0f 92       	push	r0
    247e:	0f b6       	in	r0, 0x3f	; 63
    2480:	0f 92       	push	r0
    2482:	11 24       	eor	r1, r1
    2484:	2f 93       	push	r18
    2486:	3f 93       	push	r19
    2488:	4f 93       	push	r20
    248a:	5f 93       	push	r21
    248c:	6f 93       	push	r22
    248e:	7f 93       	push	r23
    2490:	8f 93       	push	r24
    2492:	9f 93       	push	r25
    2494:	af 93       	push	r26
    2496:	bf 93       	push	r27
    2498:	ef 93       	push	r30
    249a:	ff 93       	push	r31
    249c:	89 ea       	ldi	r24, 0xA9	; 169
    249e:	92 e0       	ldi	r25, 0x02	; 2
    24a0:	0e 94 dd 10 	call	0x21ba	; 0x21ba <_ZN14HardwareSerial17_tx_udr_empty_irqEv>
    24a4:	ff 91       	pop	r31
    24a6:	ef 91       	pop	r30
    24a8:	bf 91       	pop	r27
    24aa:	af 91       	pop	r26
    24ac:	9f 91       	pop	r25
    24ae:	8f 91       	pop	r24
    24b0:	7f 91       	pop	r23
    24b2:	6f 91       	pop	r22
    24b4:	5f 91       	pop	r21
    24b6:	4f 91       	pop	r20
    24b8:	3f 91       	pop	r19
    24ba:	2f 91       	pop	r18
    24bc:	0f 90       	pop	r0
    24be:	0f be       	out	0x3f, r0	; 63
    24c0:	0f 90       	pop	r0
    24c2:	1f 90       	pop	r1
    24c4:	18 95       	reti

000024c6 <__vector_18>:
    24c6:	1f 92       	push	r1
    24c8:	0f 92       	push	r0
    24ca:	0f b6       	in	r0, 0x3f	; 63
    24cc:	0f 92       	push	r0
    24ce:	11 24       	eor	r1, r1
    24d0:	2f 93       	push	r18
    24d2:	8f 93       	push	r24
    24d4:	9f 93       	push	r25
    24d6:	ef 93       	push	r30
    24d8:	ff 93       	push	r31
    24da:	e0 91 b9 02 	lds	r30, 0x02B9	; 0x8002b9 <Serial+0x10>
    24de:	f0 91 ba 02 	lds	r31, 0x02BA	; 0x8002ba <Serial+0x11>
    24e2:	80 81       	ld	r24, Z
    24e4:	e0 91 bf 02 	lds	r30, 0x02BF	; 0x8002bf <Serial+0x16>
    24e8:	f0 91 c0 02 	lds	r31, 0x02C0	; 0x8002c0 <Serial+0x17>
    24ec:	82 fd       	sbrc	r24, 2
    24ee:	12 c0       	rjmp	.+36     	; 0x2514 <__vector_18+0x4e>
    24f0:	90 81       	ld	r25, Z
    24f2:	80 91 c2 02 	lds	r24, 0x02C2	; 0x8002c2 <Serial+0x19>
    24f6:	8f 5f       	subi	r24, 0xFF	; 255
    24f8:	8f 73       	andi	r24, 0x3F	; 63
    24fa:	20 91 c3 02 	lds	r18, 0x02C3	; 0x8002c3 <Serial+0x1a>
    24fe:	82 17       	cp	r24, r18
    2500:	51 f0       	breq	.+20     	; 0x2516 <__vector_18+0x50>
    2502:	e0 91 c2 02 	lds	r30, 0x02C2	; 0x8002c2 <Serial+0x19>
    2506:	f0 e0       	ldi	r31, 0x00	; 0
    2508:	e7 55       	subi	r30, 0x57	; 87
    250a:	fd 4f       	sbci	r31, 0xFD	; 253
    250c:	95 8f       	std	Z+29, r25	; 0x1d
    250e:	80 93 c2 02 	sts	0x02C2, r24	; 0x8002c2 <Serial+0x19>
    2512:	01 c0       	rjmp	.+2      	; 0x2516 <__vector_18+0x50>
    2514:	80 81       	ld	r24, Z
    2516:	ff 91       	pop	r31
    2518:	ef 91       	pop	r30
    251a:	9f 91       	pop	r25
    251c:	8f 91       	pop	r24
    251e:	2f 91       	pop	r18
    2520:	0f 90       	pop	r0
    2522:	0f be       	out	0x3f, r0	; 63
    2524:	0f 90       	pop	r0
    2526:	1f 90       	pop	r1
    2528:	18 95       	reti

0000252a <_ZN11EEPROMClass3getImEERT_iS2_.isra.1.lto_priv.100>:
    252a:	cf 92       	push	r12
    252c:	df 92       	push	r13
    252e:	ef 92       	push	r14
    2530:	ff 92       	push	r15
    2532:	0f 93       	push	r16
    2534:	1f 93       	push	r17
    2536:	cf 93       	push	r28
    2538:	df 93       	push	r29
    253a:	eb 01       	movw	r28, r22
    253c:	7b 01       	movw	r14, r22
    253e:	24 e0       	ldi	r18, 0x04	; 4
    2540:	e2 0e       	add	r14, r18
    2542:	f1 1c       	adc	r15, r1
    2544:	8b 01       	movw	r16, r22
    2546:	6c 01       	movw	r12, r24
    2548:	c6 1a       	sub	r12, r22
    254a:	d7 0a       	sbc	r13, r23
    254c:	c6 01       	movw	r24, r12
    254e:	80 0f       	add	r24, r16
    2550:	91 1f       	adc	r25, r17
    2552:	0e 94 12 2a 	call	0x5424	; 0x5424 <eeprom_read_byte>
    2556:	f8 01       	movw	r30, r16
    2558:	81 93       	st	Z+, r24
    255a:	8f 01       	movw	r16, r30
    255c:	ee 15       	cp	r30, r14
    255e:	ff 05       	cpc	r31, r15
    2560:	a9 f7       	brne	.-22     	; 0x254c <_ZN11EEPROMClass3getImEERT_iS2_.isra.1.lto_priv.100+0x22>
    2562:	ce 01       	movw	r24, r28
    2564:	df 91       	pop	r29
    2566:	cf 91       	pop	r28
    2568:	1f 91       	pop	r17
    256a:	0f 91       	pop	r16
    256c:	ff 90       	pop	r15
    256e:	ef 90       	pop	r14
    2570:	df 90       	pop	r13
    2572:	cf 90       	pop	r12
    2574:	08 95       	ret

00002576 <_Z19get_ntc_temperaturev>:
    2576:	8f 92       	push	r8
    2578:	9f 92       	push	r9
    257a:	af 92       	push	r10
    257c:	bf 92       	push	r11
    257e:	cf 92       	push	r12
    2580:	df 92       	push	r13
    2582:	ef 92       	push	r14
    2584:	ff 92       	push	r15
    2586:	cf 93       	push	r28
    2588:	df 93       	push	r29
    258a:	0e 94 44 1c 	call	0x3888	; 0x3888 <analogRead.constprop.29>
    258e:	ec 01       	movw	r28, r24
    2590:	61 e0       	ldi	r22, 0x01	; 1
    2592:	70 e0       	ldi	r23, 0x00	; 0
    2594:	80 e0       	ldi	r24, 0x00	; 0
    2596:	90 e0       	ldi	r25, 0x00	; 0
    2598:	0e 94 5f 0e 	call	0x1cbe	; 0x1cbe <delay>
    259c:	0e 94 44 1c 	call	0x3888	; 0x3888 <analogRead.constprop.29>
    25a0:	8c 0f       	add	r24, r28
    25a2:	9d 1f       	adc	r25, r29
    25a4:	bc 01       	movw	r22, r24
    25a6:	76 95       	lsr	r23
    25a8:	67 95       	ror	r22
    25aa:	80 e0       	ldi	r24, 0x00	; 0
    25ac:	90 e0       	ldi	r25, 0x00	; 0
    25ae:	0e 94 f3 28 	call	0x51e6	; 0x51e6 <__floatunsisf>
    25b2:	9b 01       	movw	r18, r22
    25b4:	ac 01       	movw	r20, r24
    25b6:	60 e0       	ldi	r22, 0x00	; 0
    25b8:	70 ec       	ldi	r23, 0xC0	; 192
    25ba:	8f e7       	ldi	r24, 0x7F	; 127
    25bc:	94 e4       	ldi	r25, 0x44	; 68
    25be:	0e 94 fb 2a 	call	0x55f6	; 0x55f6 <__divsf3>
    25c2:	20 e0       	ldi	r18, 0x00	; 0
    25c4:	30 e0       	ldi	r19, 0x00	; 0
    25c6:	40 e8       	ldi	r20, 0x80	; 128
    25c8:	5f e3       	ldi	r21, 0x3F	; 63
    25ca:	0e 94 8e 2a 	call	0x551c	; 0x551c <__subsf3>
    25ce:	20 e0       	ldi	r18, 0x00	; 0
    25d0:	30 e4       	ldi	r19, 0x40	; 64
    25d2:	4e e4       	ldi	r20, 0x4E	; 78
    25d4:	55 e4       	ldi	r21, 0x45	; 69
    25d6:	0e 94 54 29 	call	0x52a8	; 0x52a8 <__mulsf3>
    25da:	20 e0       	ldi	r18, 0x00	; 0
    25dc:	30 e4       	ldi	r19, 0x40	; 64
    25de:	4c e1       	ldi	r20, 0x1C	; 28
    25e0:	56 e4       	ldi	r21, 0x46	; 70
    25e2:	0e 94 fb 2a 	call	0x55f6	; 0x55f6 <__divsf3>
    25e6:	0e 94 b0 2b 	call	0x5760	; 0x5760 <log>
    25ea:	20 e0       	ldi	r18, 0x00	; 0
    25ec:	30 ee       	ldi	r19, 0xE0	; 224
    25ee:	46 e7       	ldi	r20, 0x76	; 118
    25f0:	55 e4       	ldi	r21, 0x45	; 69
    25f2:	0e 94 fb 2a 	call	0x55f6	; 0x55f6 <__divsf3>
    25f6:	2f e0       	ldi	r18, 0x0F	; 15
    25f8:	3f ec       	ldi	r19, 0xCF	; 207
    25fa:	4b e5       	ldi	r20, 0x5B	; 91
    25fc:	5b e3       	ldi	r21, 0x3B	; 59
    25fe:	0e 94 8f 2a 	call	0x551e	; 0x551e <__addsf3>
    2602:	9b 01       	movw	r18, r22
    2604:	ac 01       	movw	r20, r24
    2606:	60 e0       	ldi	r22, 0x00	; 0
    2608:	70 e0       	ldi	r23, 0x00	; 0
    260a:	80 e8       	ldi	r24, 0x80	; 128
    260c:	9f e3       	ldi	r25, 0x3F	; 63
    260e:	0e 94 fb 2a 	call	0x55f6	; 0x55f6 <__divsf3>
    2612:	4b 01       	movw	r8, r22
    2614:	5c 01       	movw	r10, r24
    2616:	60 91 45 04 	lds	r22, 0x0445	; 0x800445 <register_mem+0x34>
    261a:	06 2e       	mov	r0, r22
    261c:	00 0c       	add	r0, r0
    261e:	77 0b       	sbc	r23, r23
    2620:	88 0b       	sbc	r24, r24
    2622:	99 0b       	sbc	r25, r25
    2624:	0e 94 f5 28 	call	0x51ea	; 0x51ea <__floatsisf>
    2628:	20 e0       	ldi	r18, 0x00	; 0
    262a:	30 e0       	ldi	r19, 0x00	; 0
    262c:	40 e8       	ldi	r20, 0x80	; 128
    262e:	5e e3       	ldi	r21, 0x3E	; 62
    2630:	0e 94 54 29 	call	0x52a8	; 0x52a8 <__mulsf3>
    2634:	6b 01       	movw	r12, r22
    2636:	7c 01       	movw	r14, r24
    2638:	23 e3       	ldi	r18, 0x33	; 51
    263a:	33 e9       	ldi	r19, 0x93	; 147
    263c:	48 e8       	ldi	r20, 0x88	; 136
    263e:	53 e4       	ldi	r21, 0x43	; 67
    2640:	c5 01       	movw	r24, r10
    2642:	b4 01       	movw	r22, r8
    2644:	0e 94 8e 2a 	call	0x551c	; 0x551c <__subsf3>
    2648:	9b 01       	movw	r18, r22
    264a:	ac 01       	movw	r20, r24
    264c:	c7 01       	movw	r24, r14
    264e:	b6 01       	movw	r22, r12
    2650:	0e 94 8f 2a 	call	0x551e	; 0x551e <__addsf3>
    2654:	df 91       	pop	r29
    2656:	cf 91       	pop	r28
    2658:	ff 90       	pop	r15
    265a:	ef 90       	pop	r14
    265c:	df 90       	pop	r13
    265e:	cf 90       	pop	r12
    2660:	bf 90       	pop	r11
    2662:	af 90       	pop	r10
    2664:	9f 90       	pop	r9
    2666:	8f 90       	pop	r8
    2668:	08 95       	ret

0000266a <_Z8read_vccv>:
    266a:	cf 92       	push	r12
    266c:	df 92       	push	r13
    266e:	ef 92       	push	r14
    2670:	ff 92       	push	r15
    2672:	cf 93       	push	r28
    2674:	df 93       	push	r29
    2676:	8e e4       	ldi	r24, 0x4E	; 78
    2678:	80 93 7c 00 	sts	0x007C, r24	; 0x80007c <__TEXT_REGION_LENGTH__+0x7e007c>
    267c:	68 e2       	ldi	r22, 0x28	; 40
    267e:	70 e0       	ldi	r23, 0x00	; 0
    2680:	80 e0       	ldi	r24, 0x00	; 0
    2682:	90 e0       	ldi	r25, 0x00	; 0
    2684:	0e 94 5f 0e 	call	0x1cbe	; 0x1cbe <delay>
    2688:	80 91 7a 00 	lds	r24, 0x007A	; 0x80007a <__TEXT_REGION_LENGTH__+0x7e007a>
    268c:	80 64       	ori	r24, 0x40	; 64
    268e:	80 93 7a 00 	sts	0x007A, r24	; 0x80007a <__TEXT_REGION_LENGTH__+0x7e007a>
    2692:	80 91 7a 00 	lds	r24, 0x007A	; 0x80007a <__TEXT_REGION_LENGTH__+0x7e007a>
    2696:	86 fd       	sbrc	r24, 6
    2698:	fc cf       	rjmp	.-8      	; 0x2692 <_Z8read_vccv+0x28>
    269a:	c0 91 78 00 	lds	r28, 0x0078	; 0x800078 <__TEXT_REGION_LENGTH__+0x7e0078>
    269e:	d0 91 79 00 	lds	r29, 0x0079	; 0x800079 <__TEXT_REGION_LENGTH__+0x7e0079>
    26a2:	20 e0       	ldi	r18, 0x00	; 0
    26a4:	30 e0       	ldi	r19, 0x00	; 0
    26a6:	4a e7       	ldi	r20, 0x7A	; 122
    26a8:	59 e4       	ldi	r21, 0x49	; 73
    26aa:	60 91 40 04 	lds	r22, 0x0440	; 0x800440 <register_mem+0x2f>
    26ae:	70 91 41 04 	lds	r23, 0x0441	; 0x800441 <register_mem+0x30>
    26b2:	80 91 42 04 	lds	r24, 0x0442	; 0x800442 <register_mem+0x31>
    26b6:	90 91 43 04 	lds	r25, 0x0443	; 0x800443 <register_mem+0x32>
    26ba:	0e 94 54 29 	call	0x52a8	; 0x52a8 <__mulsf3>
    26be:	6b 01       	movw	r12, r22
    26c0:	7c 01       	movw	r14, r24
    26c2:	be 01       	movw	r22, r28
    26c4:	80 e0       	ldi	r24, 0x00	; 0
    26c6:	90 e0       	ldi	r25, 0x00	; 0
    26c8:	0e 94 f3 28 	call	0x51e6	; 0x51e6 <__floatunsisf>
    26cc:	9b 01       	movw	r18, r22
    26ce:	ac 01       	movw	r20, r24
    26d0:	c7 01       	movw	r24, r14
    26d2:	b6 01       	movw	r22, r12
    26d4:	0e 94 fb 2a 	call	0x55f6	; 0x55f6 <__divsf3>
    26d8:	0e 94 74 2b 	call	0x56e8	; 0x56e8 <__fixunssfsi>
    26dc:	cb 01       	movw	r24, r22
    26de:	df 91       	pop	r29
    26e0:	cf 91       	pop	r28
    26e2:	ff 90       	pop	r15
    26e4:	ef 90       	pop	r14
    26e6:	df 90       	pop	r13
    26e8:	cf 90       	pop	r12
    26ea:	08 95       	ret

000026ec <_Z24get_internal_temperaturev>:
    26ec:	4f 92       	push	r4
    26ee:	5f 92       	push	r5
    26f0:	6f 92       	push	r6
    26f2:	7f 92       	push	r7
    26f4:	8f 92       	push	r8
    26f6:	9f 92       	push	r9
    26f8:	af 92       	push	r10
    26fa:	bf 92       	push	r11
    26fc:	cf 92       	push	r12
    26fe:	df 92       	push	r13
    2700:	ef 92       	push	r14
    2702:	ff 92       	push	r15
    2704:	88 ec       	ldi	r24, 0xC8	; 200
    2706:	80 93 7c 00 	sts	0x007C, r24	; 0x80007c <__TEXT_REGION_LENGTH__+0x7e007c>
    270a:	80 91 7a 00 	lds	r24, 0x007A	; 0x80007a <__TEXT_REGION_LENGTH__+0x7e007a>
    270e:	80 68       	ori	r24, 0x80	; 128
    2710:	80 93 7a 00 	sts	0x007A, r24	; 0x80007a <__TEXT_REGION_LENGTH__+0x7e007a>
    2714:	68 e2       	ldi	r22, 0x28	; 40
    2716:	70 e0       	ldi	r23, 0x00	; 0
    2718:	80 e0       	ldi	r24, 0x00	; 0
    271a:	90 e0       	ldi	r25, 0x00	; 0
    271c:	0e 94 5f 0e 	call	0x1cbe	; 0x1cbe <delay>
    2720:	80 91 7a 00 	lds	r24, 0x007A	; 0x80007a <__TEXT_REGION_LENGTH__+0x7e007a>
    2724:	80 64       	ori	r24, 0x40	; 64
    2726:	80 93 7a 00 	sts	0x007A, r24	; 0x80007a <__TEXT_REGION_LENGTH__+0x7e007a>
    272a:	80 91 7a 00 	lds	r24, 0x007A	; 0x80007a <__TEXT_REGION_LENGTH__+0x7e007a>
    272e:	86 fd       	sbrc	r24, 6
    2730:	fc cf       	rjmp	.-8      	; 0x272a <_Z24get_internal_temperaturev+0x3e>
    2732:	60 91 78 00 	lds	r22, 0x0078	; 0x800078 <__TEXT_REGION_LENGTH__+0x7e0078>
    2736:	70 91 79 00 	lds	r23, 0x0079	; 0x800079 <__TEXT_REGION_LENGTH__+0x7e0079>
    273a:	80 e0       	ldi	r24, 0x00	; 0
    273c:	90 e0       	ldi	r25, 0x00	; 0
    273e:	0e 94 f3 28 	call	0x51e6	; 0x51e6 <__floatunsisf>
    2742:	4b 01       	movw	r8, r22
    2744:	5c 01       	movw	r10, r24
    2746:	80 91 8e 02 	lds	r24, 0x028E	; 0x80028e <is_Atmega328PB>
    274a:	81 11       	cpse	r24, r1
    274c:	09 c0       	rjmp	.+18     	; 0x2760 <_Z24get_internal_temperaturev+0x74>
    274e:	9e ea       	ldi	r25, 0xAE	; 174
    2750:	c9 2e       	mov	r12, r25
    2752:	97 e2       	ldi	r25, 0x27	; 39
    2754:	d9 2e       	mov	r13, r25
    2756:	92 ea       	ldi	r25, 0xA2	; 162
    2758:	e9 2e       	mov	r14, r25
    275a:	93 e4       	ldi	r25, 0x43	; 67
    275c:	f9 2e       	mov	r15, r25
    275e:	06 c0       	rjmp	.+12     	; 0x276c <_Z24get_internal_temperaturev+0x80>
    2760:	c1 2c       	mov	r12, r1
    2762:	d1 2c       	mov	r13, r1
    2764:	87 e7       	ldi	r24, 0x77	; 119
    2766:	e8 2e       	mov	r14, r24
    2768:	83 e4       	ldi	r24, 0x43	; 67
    276a:	f8 2e       	mov	r15, r24
    276c:	60 91 44 04 	lds	r22, 0x0444	; 0x800444 <register_mem+0x33>
    2770:	06 2e       	mov	r0, r22
    2772:	00 0c       	add	r0, r0
    2774:	77 0b       	sbc	r23, r23
    2776:	88 0b       	sbc	r24, r24
    2778:	99 0b       	sbc	r25, r25
    277a:	0e 94 f5 28 	call	0x51ea	; 0x51ea <__floatsisf>
    277e:	20 e0       	ldi	r18, 0x00	; 0
    2780:	30 e0       	ldi	r19, 0x00	; 0
    2782:	40 e8       	ldi	r20, 0x80	; 128
    2784:	5e e3       	ldi	r21, 0x3E	; 62
    2786:	0e 94 54 29 	call	0x52a8	; 0x52a8 <__mulsf3>
    278a:	2b 01       	movw	r4, r22
    278c:	3c 01       	movw	r6, r24
    278e:	a7 01       	movw	r20, r14
    2790:	96 01       	movw	r18, r12
    2792:	c5 01       	movw	r24, r10
    2794:	b4 01       	movw	r22, r8
    2796:	0e 94 8e 2a 	call	0x551c	; 0x551c <__subsf3>
    279a:	26 ef       	ldi	r18, 0xF6	; 246
    279c:	38 e2       	ldi	r19, 0x28	; 40
    279e:	4c e9       	ldi	r20, 0x9C	; 156
    27a0:	5f e3       	ldi	r21, 0x3F	; 63
    27a2:	0e 94 fb 2a 	call	0x55f6	; 0x55f6 <__divsf3>
    27a6:	9b 01       	movw	r18, r22
    27a8:	ac 01       	movw	r20, r24
    27aa:	c3 01       	movw	r24, r6
    27ac:	b2 01       	movw	r22, r4
    27ae:	0e 94 8f 2a 	call	0x551e	; 0x551e <__addsf3>
    27b2:	ff 90       	pop	r15
    27b4:	ef 90       	pop	r14
    27b6:	df 90       	pop	r13
    27b8:	cf 90       	pop	r12
    27ba:	bf 90       	pop	r11
    27bc:	af 90       	pop	r10
    27be:	9f 90       	pop	r9
    27c0:	8f 90       	pop	r8
    27c2:	7f 90       	pop	r7
    27c4:	6f 90       	pop	r6
    27c6:	5f 90       	pop	r5
    27c8:	4f 90       	pop	r4
    27ca:	08 95       	ret

000027cc <_Z19display_dimmer_infov>:
    27cc:	cf 92       	push	r12
    27ce:	df 92       	push	r13
    27d0:	ef 92       	push	r14
    27d2:	ff 92       	push	r15
    27d4:	0f 93       	push	r16
    27d6:	1f 93       	push	r17
    27d8:	cf 93       	push	r28
    27da:	df 93       	push	r29
    27dc:	cd b7       	in	r28, 0x3d	; 61
    27de:	de b7       	in	r29, 0x3e	; 62
    27e0:	67 97       	sbiw	r28, 0x17	; 23
    27e2:	0f b6       	in	r0, 0x3f	; 63
    27e4:	f8 94       	cli
    27e6:	de bf       	out	0x3e, r29	; 62
    27e8:	0f be       	out	0x3f, r0	; 63
    27ea:	cd bf       	out	0x3d, r28	; 61
    27ec:	0e 94 d5 11 	call	0x23aa	; 0x23aa <_Z3remv>
    27f0:	8f e7       	ldi	r24, 0x7F	; 127
    27f2:	94 e0       	ldi	r25, 0x04	; 4
    27f4:	0e 94 16 18 	call	0x302c	; 0x302c <_ZN5Print7printlnEPK19__FlashStringHelper.constprop.70>
    27f8:	89 ea       	ldi	r24, 0xA9	; 169
    27fa:	92 e0       	ldi	r25, 0x02	; 2
    27fc:	0e 94 4c 11 	call	0x2298	; 0x2298 <_ZN14HardwareSerial5flushEv>
    2800:	0e 94 d5 11 	call	0x23aa	; 0x23aa <_Z3remv>
    2804:	ce 01       	movw	r24, r28
    2806:	01 96       	adiw	r24, 0x01	; 1
    2808:	0e 94 8e 05 	call	0xb1c	; 0xb1c <_Z13get_signaturePh>
    280c:	89 e0       	ldi	r24, 0x09	; 9
    280e:	e0 e0       	ldi	r30, 0x00	; 0
    2810:	f0 e0       	ldi	r31, 0x00	; 0
    2812:	80 93 57 00 	sts	0x0057, r24	; 0x800057 <__TEXT_REGION_LENGTH__+0x7e0057>
    2816:	e4 91       	lpm	r30, Z
    2818:	ec 83       	std	Y+4, r30	; 0x04
    281a:	e3 e0       	ldi	r30, 0x03	; 3
    281c:	f0 e0       	ldi	r31, 0x00	; 0
    281e:	80 93 57 00 	sts	0x0057, r24	; 0x800057 <__TEXT_REGION_LENGTH__+0x7e0057>
    2822:	e4 91       	lpm	r30, Z
    2824:	ed 83       	std	Y+5, r30	; 0x05
    2826:	e2 e0       	ldi	r30, 0x02	; 2
    2828:	f0 e0       	ldi	r31, 0x00	; 0
    282a:	80 93 57 00 	sts	0x0057, r24	; 0x800057 <__TEXT_REGION_LENGTH__+0x7e0057>
    282e:	84 91       	lpm	r24, Z
    2830:	8e 83       	std	Y+6, r24	; 0x06
    2832:	1f 82       	std	Y+7, r1	; 0x07
    2834:	89 81       	ldd	r24, Y+1	; 0x01
    2836:	8e 31       	cpi	r24, 0x1E	; 30
    2838:	89 f4       	brne	.+34     	; 0x285c <_Z19display_dimmer_infov+0x90>
    283a:	8a 81       	ldd	r24, Y+2	; 0x02
    283c:	85 39       	cpi	r24, 0x95	; 149
    283e:	71 f4       	brne	.+28     	; 0x285c <_Z19display_dimmer_infov+0x90>
    2840:	8b 81       	ldd	r24, Y+3	; 0x03
    2842:	8f 30       	cpi	r24, 0x0F	; 15
    2844:	29 f0       	breq	.+10     	; 0x2850 <_Z19display_dimmer_infov+0x84>
    2846:	86 31       	cpi	r24, 0x16	; 22
    2848:	49 f4       	brne	.+18     	; 0x285c <_Z19display_dimmer_infov+0x90>
    284a:	68 ef       	ldi	r22, 0xF8	; 248
    284c:	72 e0       	ldi	r23, 0x02	; 2
    284e:	02 c0       	rjmp	.+4      	; 0x2854 <_Z19display_dimmer_infov+0x88>
    2850:	64 e0       	ldi	r22, 0x04	; 4
    2852:	73 e0       	ldi	r23, 0x03	; 3
    2854:	ce 01       	movw	r24, r28
    2856:	07 96       	adiw	r24, 0x07	; 7
    2858:	0e 94 d8 27 	call	0x4fb0	; 0x4fb0 <strcpy_P>
    285c:	8e 81       	ldd	r24, Y+6	; 0x06
    285e:	1f 92       	push	r1
    2860:	8f 93       	push	r24
    2862:	8d 81       	ldd	r24, Y+5	; 0x05
    2864:	1f 92       	push	r1
    2866:	8f 93       	push	r24
    2868:	8c 81       	ldd	r24, Y+4	; 0x04
    286a:	1f 92       	push	r1
    286c:	8f 93       	push	r24
    286e:	8b 81       	ldd	r24, Y+3	; 0x03
    2870:	1f 92       	push	r1
    2872:	8f 93       	push	r24
    2874:	8a 81       	ldd	r24, Y+2	; 0x02
    2876:	1f 92       	push	r1
    2878:	8f 93       	push	r24
    287a:	89 81       	ldd	r24, Y+1	; 0x01
    287c:	1f 92       	push	r1
    287e:	8f 93       	push	r24
    2880:	81 e5       	ldi	r24, 0x51	; 81
    2882:	94 e0       	ldi	r25, 0x04	; 4
    2884:	9f 93       	push	r25
    2886:	8f 93       	push	r24
    2888:	0e 94 a8 05 	call	0xb50	; 0xb50 <_Z15Serial_printf_PPKcz>
    288c:	0f b6       	in	r0, 0x3f	; 63
    288e:	f8 94       	cli
    2890:	de bf       	out	0x3e, r29	; 62
    2892:	0f be       	out	0x3f, r0	; 63
    2894:	cd bf       	out	0x3d, r28	; 61
    2896:	8f 81       	ldd	r24, Y+7	; 0x07
    2898:	88 23       	and	r24, r24
    289a:	71 f0       	breq	.+28     	; 0x28b8 <_Z19display_dimmer_infov+0xec>
    289c:	ce 01       	movw	r24, r28
    289e:	07 96       	adiw	r24, 0x07	; 7
    28a0:	9f 93       	push	r25
    28a2:	8f 93       	push	r24
    28a4:	89 e4       	ldi	r24, 0x49	; 73
    28a6:	94 e0       	ldi	r25, 0x04	; 4
    28a8:	9f 93       	push	r25
    28aa:	8f 93       	push	r24
    28ac:	0e 94 a8 05 	call	0xb50	; 0xb50 <_Z15Serial_printf_PPKcz>
    28b0:	0f 90       	pop	r0
    28b2:	0f 90       	pop	r0
    28b4:	0f 90       	pop	r0
    28b6:	0f 90       	pop	r0
    28b8:	1f 92       	push	r1
    28ba:	80 e1       	ldi	r24, 0x10	; 16
    28bc:	8f 93       	push	r24
    28be:	81 e4       	ldi	r24, 0x41	; 65
    28c0:	94 e0       	ldi	r25, 0x04	; 4
    28c2:	9f 93       	push	r25
    28c4:	8f 93       	push	r24
    28c6:	0e 94 a8 05 	call	0xb50	; 0xb50 <_Z15Serial_printf_PPKcz>
    28ca:	89 ea       	ldi	r24, 0xA9	; 169
    28cc:	92 e0       	ldi	r25, 0x02	; 2
    28ce:	0e 94 4c 11 	call	0x2298	; 0x2298 <_ZN14HardwareSerial5flushEv>
    28d2:	0e 94 d5 11 	call	0x23aa	; 0x23aa <_Z3remv>
    28d6:	68 e3       	ldi	r22, 0x38	; 56
    28d8:	74 e0       	ldi	r23, 0x04	; 4
    28da:	89 ea       	ldi	r24, 0xA9	; 169
    28dc:	92 e0       	ldi	r25, 0x02	; 2
    28de:	0e 94 b1 11 	call	0x2362	; 0x2362 <_ZN5Print5printEPK19__FlashStringHelper>
    28e2:	80 91 8c 04 	lds	r24, 0x048C	; 0x80048c <config>
    28e6:	90 91 8d 04 	lds	r25, 0x048D	; 0x80048d <config+0x1>
    28ea:	a0 91 8e 04 	lds	r26, 0x048E	; 0x80048e <config+0x2>
    28ee:	b0 91 8f 04 	lds	r27, 0x048F	; 0x80048f <config+0x3>
    28f2:	9c 01       	movw	r18, r24
    28f4:	ad 01       	movw	r20, r26
    28f6:	21 50       	subi	r18, 0x01	; 1
    28f8:	31 09       	sbc	r19, r1
    28fa:	41 09       	sbc	r20, r1
    28fc:	51 09       	sbc	r21, r1
    28fe:	ae e1       	ldi	r26, 0x1E	; 30
    2900:	b0 e0       	ldi	r27, 0x00	; 0
    2902:	0e 94 5a 2a 	call	0x54b4	; 0x54b4 <__muluhisi3>
    2906:	8b 01       	movw	r16, r22
    2908:	9c 01       	movw	r18, r24
    290a:	80 91 8c 02 	lds	r24, 0x028C	; 0x80028c <eeprom_position>
    290e:	90 91 8d 02 	lds	r25, 0x028D	; 0x80028d <eeprom_position+0x1>
    2912:	62 e2       	ldi	r22, 0x22	; 34
    2914:	70 e0       	ldi	r23, 0x00	; 0
    2916:	0e 94 74 2a 	call	0x54e8	; 0x54e8 <__udivmodhi4>
    291a:	d9 01       	movw	r26, r18
    291c:	c8 01       	movw	r24, r16
    291e:	86 0f       	add	r24, r22
    2920:	97 1f       	adc	r25, r23
    2922:	a1 1d       	adc	r26, r1
    2924:	b1 1d       	adc	r27, r1
    2926:	bf 93       	push	r27
    2928:	af 93       	push	r26
    292a:	9f 93       	push	r25
    292c:	8f 93       	push	r24
    292e:	8a e2       	ldi	r24, 0x2A	; 42
    2930:	94 e0       	ldi	r25, 0x04	; 4
    2932:	9f 93       	push	r25
    2934:	8f 93       	push	r24
    2936:	0e 94 a8 05 	call	0xb50	; 0xb50 <_Z15Serial_printf_PPKcz>
    293a:	62 e2       	ldi	r22, 0x22	; 34
    293c:	74 e0       	ldi	r23, 0x04	; 4
    293e:	89 ea       	ldi	r24, 0xA9	; 169
    2940:	92 e0       	ldi	r25, 0x02	; 2
    2942:	0e 94 b1 11 	call	0x2362	; 0x2362 <_ZN5Print5printEPK19__FlashStringHelper>
    2946:	65 e1       	ldi	r22, 0x15	; 21
    2948:	74 e0       	ldi	r23, 0x04	; 4
    294a:	89 ea       	ldi	r24, 0xA9	; 169
    294c:	92 e0       	ldi	r25, 0x02	; 2
    294e:	0e 94 b1 11 	call	0x2362	; 0x2362 <_ZN5Print5printEPK19__FlashStringHelper>
    2952:	6c e0       	ldi	r22, 0x0C	; 12
    2954:	74 e0       	ldi	r23, 0x04	; 4
    2956:	89 ea       	ldi	r24, 0xA9	; 169
    2958:	92 e0       	ldi	r25, 0x02	; 2
    295a:	0e 94 b1 11 	call	0x2362	; 0x2362 <_ZN5Print5printEPK19__FlashStringHelper>
    295e:	66 e0       	ldi	r22, 0x06	; 6
    2960:	74 e0       	ldi	r23, 0x04	; 4
    2962:	89 ea       	ldi	r24, 0xA9	; 169
    2964:	92 e0       	ldi	r25, 0x02	; 2
    2966:	0e 94 b1 11 	call	0x2362	; 0x2362 <_ZN5Print5printEPK19__FlashStringHelper>
    296a:	1f 92       	push	r1
    296c:	87 e1       	ldi	r24, 0x17	; 23
    296e:	8f 93       	push	r24
    2970:	8c ef       	ldi	r24, 0xFC	; 252
    2972:	93 e0       	ldi	r25, 0x03	; 3
    2974:	9f 93       	push	r25
    2976:	8f 93       	push	r24
    2978:	0e 94 a8 05 	call	0xb50	; 0xb50 <_Z15Serial_printf_PPKcz>
    297c:	6e ee       	ldi	r22, 0xEE	; 238
    297e:	73 e0       	ldi	r23, 0x03	; 3
    2980:	89 ea       	ldi	r24, 0xA9	; 169
    2982:	92 e0       	ldi	r25, 0x02	; 2
    2984:	0e 94 b1 11 	call	0x2362	; 0x2362 <_ZN5Print5printEPK19__FlashStringHelper>
    2988:	28 e0       	ldi	r18, 0x08	; 8
    298a:	46 e0       	ldi	r20, 0x06	; 6
    298c:	60 e0       	ldi	r22, 0x00	; 0
    298e:	70 e0       	ldi	r23, 0x00	; 0
    2990:	80 e0       	ldi	r24, 0x00	; 0
    2992:	9f e3       	ldi	r25, 0x3F	; 63
    2994:	0e 94 7b 06 	call	0xcf6	; 0xcf6 <_Z18Serial_print_floatdhh>
    2998:	64 ed       	ldi	r22, 0xD4	; 212
    299a:	73 e0       	ldi	r23, 0x03	; 3
    299c:	89 ea       	ldi	r24, 0xA9	; 169
    299e:	92 e0       	ldi	r25, 0x02	; 2
    29a0:	0e 94 b1 11 	call	0x2362	; 0x2362 <_ZN5Print5printEPK19__FlashStringHelper>
    29a4:	8e e0       	ldi	r24, 0x0E	; 14
    29a6:	c8 2e       	mov	r12, r24
    29a8:	81 e0       	ldi	r24, 0x01	; 1
    29aa:	d8 2e       	mov	r13, r24
    29ac:	9d e1       	ldi	r25, 0x1D	; 29
    29ae:	e9 2e       	mov	r14, r25
    29b0:	94 e0       	ldi	r25, 0x04	; 4
    29b2:	f9 2e       	mov	r15, r25
    29b4:	0f b6       	in	r0, 0x3f	; 63
    29b6:	f8 94       	cli
    29b8:	de bf       	out	0x3e, r29	; 62
    29ba:	0f be       	out	0x3f, r0	; 63
    29bc:	cd bf       	out	0x3d, r28	; 61
    29be:	10 e0       	ldi	r17, 0x00	; 0
    29c0:	f6 01       	movw	r30, r12
    29c2:	41 91       	ld	r20, Z+
    29c4:	6f 01       	movw	r12, r30
    29c6:	50 e0       	ldi	r21, 0x00	; 0
    29c8:	60 e0       	ldi	r22, 0x00	; 0
    29ca:	70 e0       	ldi	r23, 0x00	; 0
    29cc:	2a e0       	ldi	r18, 0x0A	; 10
    29ce:	89 ea       	ldi	r24, 0xA9	; 169
    29d0:	92 e0       	ldi	r25, 0x02	; 2
    29d2:	0e 94 f0 11 	call	0x23e0	; 0x23e0 <_ZN5Print11printNumberEmh>
    29d6:	6f e2       	ldi	r22, 0x2F	; 47
    29d8:	89 ea       	ldi	r24, 0xA9	; 169
    29da:	92 e0       	ldi	r25, 0x02	; 2
    29dc:	0e 94 aa 11 	call	0x2354	; 0x2354 <_ZN5Print5printEc>
    29e0:	f7 01       	movw	r30, r14
    29e2:	41 91       	ld	r20, Z+
    29e4:	51 91       	ld	r21, Z+
    29e6:	7f 01       	movw	r14, r30
    29e8:	60 e0       	ldi	r22, 0x00	; 0
    29ea:	70 e0       	ldi	r23, 0x00	; 0
    29ec:	2a e0       	ldi	r18, 0x0A	; 10
    29ee:	89 ea       	ldi	r24, 0xA9	; 169
    29f0:	92 e0       	ldi	r25, 0x02	; 2
    29f2:	0e 94 f0 11 	call	0x23e0	; 0x23e0 <_ZN5Print11printNumberEmh>
    29f6:	13 30       	cpi	r17, 0x03	; 3
    29f8:	29 f0       	breq	.+10     	; 0x2a04 <_Z19display_dimmer_infov+0x238>
    29fa:	6c e2       	ldi	r22, 0x2C	; 44
    29fc:	89 ea       	ldi	r24, 0xA9	; 169
    29fe:	92 e0       	ldi	r25, 0x02	; 2
    2a00:	0e 94 aa 11 	call	0x2354	; 0x2354 <_ZN5Print5printEc>
    2a04:	1f 5f       	subi	r17, 0xFF	; 255
    2a06:	14 30       	cpi	r17, 0x04	; 4
    2a08:	d9 f6       	brne	.-74     	; 0x29c0 <_Z19display_dimmer_infov+0x1f4>
    2a0a:	89 ea       	ldi	r24, 0xA9	; 169
    2a0c:	92 e0       	ldi	r25, 0x02	; 2
    2a0e:	0e 94 39 12 	call	0x2472	; 0x2472 <_ZN5Print7printlnEv>
    2a12:	89 ea       	ldi	r24, 0xA9	; 169
    2a14:	92 e0       	ldi	r25, 0x02	; 2
    2a16:	0e 94 4c 11 	call	0x2298	; 0x2298 <_ZN14HardwareSerial5flushEv>
    2a1a:	0e 94 d5 11 	call	0x23aa	; 0x23aa <_Z3remv>
    2a1e:	6c ec       	ldi	r22, 0xCC	; 204
    2a20:	73 e0       	ldi	r23, 0x03	; 3
    2a22:	89 ea       	ldi	r24, 0xA9	; 169
    2a24:	92 e0       	ldi	r25, 0x02	; 2
    2a26:	0e 94 b1 11 	call	0x2362	; 0x2362 <_ZN5Print5printEPK19__FlashStringHelper>
    2a2a:	80 91 f8 03 	lds	r24, 0x03F8	; 0x8003f8 <dimmer+0x6c>
    2a2e:	90 91 f9 03 	lds	r25, 0x03F9	; 0x8003f9 <dimmer+0x6d>
    2a32:	89 2b       	or	r24, r25
    2a34:	89 f0       	breq	.+34     	; 0x2a58 <_Z19display_dimmer_infov+0x28c>
    2a36:	60 91 f8 03 	lds	r22, 0x03F8	; 0x8003f8 <dimmer+0x6c>
    2a3a:	70 91 f9 03 	lds	r23, 0x03F9	; 0x8003f9 <dimmer+0x6d>
    2a3e:	80 e0       	ldi	r24, 0x00	; 0
    2a40:	90 e0       	ldi	r25, 0x00	; 0
    2a42:	0e 94 f3 28 	call	0x51e6	; 0x51e6 <__floatunsisf>
    2a46:	9b 01       	movw	r18, r22
    2a48:	ac 01       	movw	r20, r24
    2a4a:	60 e0       	ldi	r22, 0x00	; 0
    2a4c:	74 e2       	ldi	r23, 0x24	; 36
    2a4e:	84 e7       	ldi	r24, 0x74	; 116
    2a50:	99 e4       	ldi	r25, 0x49	; 73
    2a52:	0e 94 fb 2a 	call	0x55f6	; 0x55f6 <__divsf3>
    2a56:	04 c0       	rjmp	.+8      	; 0x2a60 <_Z19display_dimmer_infov+0x294>
    2a58:	60 e0       	ldi	r22, 0x00	; 0
    2a5a:	70 e0       	ldi	r23, 0x00	; 0
    2a5c:	80 ec       	ldi	r24, 0xC0	; 192
    2a5e:	9f e7       	ldi	r25, 0x7F	; 127
    2a60:	9f 93       	push	r25
    2a62:	8f 93       	push	r24
    2a64:	7f 93       	push	r23
    2a66:	6f 93       	push	r22
    2a68:	80 91 33 04 	lds	r24, 0x0433	; 0x800433 <register_mem+0x22>
    2a6c:	81 70       	andi	r24, 0x01	; 1
    2a6e:	1f 92       	push	r1
    2a70:	8f 93       	push	r24
    2a72:	81 eb       	ldi	r24, 0xB1	; 177
    2a74:	93 e0       	ldi	r25, 0x03	; 3
    2a76:	9f 93       	push	r25
    2a78:	8f 93       	push	r24
    2a7a:	0e 94 a8 05 	call	0xb50	; 0xb50 <_Z15Serial_printf_PPKcz>
    2a7e:	60 91 40 04 	lds	r22, 0x0440	; 0x800440 <register_mem+0x2f>
    2a82:	70 91 41 04 	lds	r23, 0x0441	; 0x800441 <register_mem+0x30>
    2a86:	80 91 42 04 	lds	r24, 0x0442	; 0x800442 <register_mem+0x31>
    2a8a:	90 91 43 04 	lds	r25, 0x0443	; 0x800443 <register_mem+0x32>
    2a8e:	24 e0       	ldi	r18, 0x04	; 4
    2a90:	44 e0       	ldi	r20, 0x04	; 4
    2a92:	0e 94 7b 06 	call	0xcf6	; 0xcf6 <_Z18Serial_print_floatdhh>
    2a96:	6c e2       	ldi	r22, 0x2C	; 44
    2a98:	89 ea       	ldi	r24, 0xA9	; 169
    2a9a:	92 e0       	ldi	r25, 0x02	; 2
    2a9c:	0e 94 aa 11 	call	0x2354	; 0x2354 <_ZN5Print5printEc>
    2aa0:	60 91 45 04 	lds	r22, 0x0445	; 0x800445 <register_mem+0x34>
    2aa4:	06 2e       	mov	r0, r22
    2aa6:	00 0c       	add	r0, r0
    2aa8:	77 0b       	sbc	r23, r23
    2aaa:	88 0b       	sbc	r24, r24
    2aac:	99 0b       	sbc	r25, r25
    2aae:	0e 94 f5 28 	call	0x51ea	; 0x51ea <__floatsisf>
    2ab2:	20 e0       	ldi	r18, 0x00	; 0
    2ab4:	30 e0       	ldi	r19, 0x00	; 0
    2ab6:	40 e8       	ldi	r20, 0x80	; 128
    2ab8:	5e e3       	ldi	r21, 0x3E	; 62
    2aba:	0e 94 54 29 	call	0x52a8	; 0x52a8 <__mulsf3>
    2abe:	16 2f       	mov	r17, r22
    2ac0:	07 2f       	mov	r16, r23
    2ac2:	f8 2e       	mov	r15, r24
    2ac4:	e9 2e       	mov	r14, r25
    2ac6:	0e 94 bb 12 	call	0x2576	; 0x2576 <_Z19get_ntc_temperaturev>
    2aca:	ef 92       	push	r14
    2acc:	ff 92       	push	r15
    2ace:	0f 93       	push	r16
    2ad0:	1f 93       	push	r17
    2ad2:	9f 93       	push	r25
    2ad4:	8f 93       	push	r24
    2ad6:	7f 93       	push	r23
    2ad8:	6f 93       	push	r22
    2ada:	80 ea       	ldi	r24, 0xA0	; 160
    2adc:	93 e0       	ldi	r25, 0x03	; 3
    2ade:	9f 93       	push	r25
    2ae0:	8f 93       	push	r24
    2ae2:	0e 94 a8 05 	call	0xb50	; 0xb50 <_Z15Serial_printf_PPKcz>
    2ae6:	60 91 44 04 	lds	r22, 0x0444	; 0x800444 <register_mem+0x33>
    2aea:	06 2e       	mov	r0, r22
    2aec:	00 0c       	add	r0, r0
    2aee:	77 0b       	sbc	r23, r23
    2af0:	88 0b       	sbc	r24, r24
    2af2:	99 0b       	sbc	r25, r25
    2af4:	0e 94 f5 28 	call	0x51ea	; 0x51ea <__floatsisf>
    2af8:	20 e0       	ldi	r18, 0x00	; 0
    2afa:	30 e0       	ldi	r19, 0x00	; 0
    2afc:	40 e8       	ldi	r20, 0x80	; 128
    2afe:	5e e3       	ldi	r21, 0x3E	; 62
    2b00:	0e 94 54 29 	call	0x52a8	; 0x52a8 <__mulsf3>
    2b04:	16 2f       	mov	r17, r22
    2b06:	07 2f       	mov	r16, r23
    2b08:	f8 2e       	mov	r15, r24
    2b0a:	e9 2e       	mov	r14, r25
    2b0c:	0e 94 76 13 	call	0x26ec	; 0x26ec <_Z24get_internal_temperaturev>
    2b10:	ef 92       	push	r14
    2b12:	ff 92       	push	r15
    2b14:	0f 93       	push	r16
    2b16:	1f 93       	push	r17
    2b18:	9f 93       	push	r25
    2b1a:	8f 93       	push	r24
    2b1c:	7f 93       	push	r23
    2b1e:	6f 93       	push	r22
    2b20:	8b e8       	ldi	r24, 0x8B	; 139
    2b22:	93 e0       	ldi	r25, 0x03	; 3
    2b24:	9f 93       	push	r25
    2b26:	8f 93       	push	r24
    2b28:	0e 94 a8 05 	call	0xb50	; 0xb50 <_Z15Serial_printf_PPKcz>
    2b2c:	80 91 46 04 	lds	r24, 0x0446	; 0x800446 <register_mem+0x35>
    2b30:	1f 92       	push	r1
    2b32:	8f 93       	push	r24
    2b34:	80 91 39 04 	lds	r24, 0x0439	; 0x800439 <register_mem+0x28>
    2b38:	1f 92       	push	r1
    2b3a:	8f 93       	push	r24
    2b3c:	80 91 34 04 	lds	r24, 0x0434	; 0x800434 <register_mem+0x23>
    2b40:	1f 92       	push	r1
    2b42:	8f 93       	push	r24
    2b44:	80 e7       	ldi	r24, 0x70	; 112
    2b46:	93 e0       	ldi	r25, 0x03	; 3
    2b48:	9f 93       	push	r25
    2b4a:	8f 93       	push	r24
    2b4c:	0e 94 a8 05 	call	0xb50	; 0xb50 <_Z15Serial_printf_PPKcz>
    2b50:	0f b6       	in	r0, 0x3f	; 63
    2b52:	f8 94       	cli
    2b54:	de bf       	out	0x3e, r29	; 62
    2b56:	0f be       	out	0x3f, r0	; 63
    2b58:	cd bf       	out	0x3d, r28	; 61
    2b5a:	0e 94 35 13 	call	0x266a	; 0x266a <_Z8read_vccv>
    2b5e:	bc 01       	movw	r22, r24
    2b60:	80 e0       	ldi	r24, 0x00	; 0
    2b62:	90 e0       	ldi	r25, 0x00	; 0
    2b64:	0e 94 f3 28 	call	0x51e6	; 0x51e6 <__floatunsisf>
    2b68:	20 e0       	ldi	r18, 0x00	; 0
    2b6a:	30 e0       	ldi	r19, 0x00	; 0
    2b6c:	4a e7       	ldi	r20, 0x7A	; 122
    2b6e:	54 e4       	ldi	r21, 0x44	; 68
    2b70:	0e 94 fb 2a 	call	0x55f6	; 0x55f6 <__divsf3>
    2b74:	9f 93       	push	r25
    2b76:	8f 93       	push	r24
    2b78:	7f 93       	push	r23
    2b7a:	6f 93       	push	r22
    2b7c:	86 e6       	ldi	r24, 0x66	; 102
    2b7e:	93 e0       	ldi	r25, 0x03	; 3
    2b80:	9f 93       	push	r25
    2b82:	8f 93       	push	r24
    2b84:	0e 94 a8 05 	call	0xb50	; 0xb50 <_Z15Serial_printf_PPKcz>
    2b88:	e0 90 3e 04 	lds	r14, 0x043E	; 0x80043e <register_mem+0x2d>
    2b8c:	f0 90 3f 04 	lds	r15, 0x043F	; 0x80043f <register_mem+0x2e>
    2b90:	00 91 3c 04 	lds	r16, 0x043C	; 0x80043c <register_mem+0x2b>
    2b94:	10 91 3d 04 	lds	r17, 0x043D	; 0x80043d <register_mem+0x2c>
    2b98:	b7 01       	movw	r22, r14
    2b9a:	80 e0       	ldi	r24, 0x00	; 0
    2b9c:	90 e0       	ldi	r25, 0x00	; 0
    2b9e:	0e 94 f3 28 	call	0x51e6	; 0x51e6 <__floatunsisf>
    2ba2:	20 e0       	ldi	r18, 0x00	; 0
    2ba4:	30 e0       	ldi	r19, 0x00	; 0
    2ba6:	40 e0       	ldi	r20, 0x00	; 0
    2ba8:	5f e3       	ldi	r21, 0x3F	; 63
    2baa:	0e 94 54 29 	call	0x52a8	; 0x52a8 <__mulsf3>
    2bae:	9f 93       	push	r25
    2bb0:	8f 93       	push	r24
    2bb2:	7f 93       	push	r23
    2bb4:	6f 93       	push	r22
    2bb6:	ff 92       	push	r15
    2bb8:	ef 92       	push	r14
    2bba:	b8 01       	movw	r22, r16
    2bbc:	80 e0       	ldi	r24, 0x00	; 0
    2bbe:	90 e0       	ldi	r25, 0x00	; 0
    2bc0:	0e 94 f3 28 	call	0x51e6	; 0x51e6 <__floatunsisf>
    2bc4:	20 e0       	ldi	r18, 0x00	; 0
    2bc6:	30 e0       	ldi	r19, 0x00	; 0
    2bc8:	40 e0       	ldi	r20, 0x00	; 0
    2bca:	5f e3       	ldi	r21, 0x3F	; 63
    2bcc:	0e 94 54 29 	call	0x52a8	; 0x52a8 <__mulsf3>
    2bd0:	9f 93       	push	r25
    2bd2:	8f 93       	push	r24
    2bd4:	7f 93       	push	r23
    2bd6:	6f 93       	push	r22
    2bd8:	1f 93       	push	r17
    2bda:	0f 93       	push	r16
    2bdc:	87 e4       	ldi	r24, 0x47	; 71
    2bde:	93 e0       	ldi	r25, 0x03	; 3
    2be0:	9f 93       	push	r25
    2be2:	8f 93       	push	r24
    2be4:	0e 94 a8 05 	call	0xb50	; 0xb50 <_Z15Serial_printf_PPKcz>
    2be8:	00 91 3a 04 	lds	r16, 0x043A	; 0x80043a <register_mem+0x29>
    2bec:	10 91 3b 04 	lds	r17, 0x043B	; 0x80043b <register_mem+0x2a>
    2bf0:	b8 01       	movw	r22, r16
    2bf2:	01 2e       	mov	r0, r17
    2bf4:	00 0c       	add	r0, r0
    2bf6:	88 0b       	sbc	r24, r24
    2bf8:	99 0b       	sbc	r25, r25
    2bfa:	0e 94 f5 28 	call	0x51ea	; 0x51ea <__floatsisf>
    2bfe:	20 e0       	ldi	r18, 0x00	; 0
    2c00:	30 e0       	ldi	r19, 0x00	; 0
    2c02:	40 e0       	ldi	r20, 0x00	; 0
    2c04:	5f e3       	ldi	r21, 0x3F	; 63
    2c06:	0e 94 54 29 	call	0x52a8	; 0x52a8 <__mulsf3>
    2c0a:	9f 93       	push	r25
    2c0c:	8f 93       	push	r24
    2c0e:	7f 93       	push	r23
    2c10:	6f 93       	push	r22
    2c12:	1f 93       	push	r17
    2c14:	0f 93       	push	r16
    2c16:	89 e3       	ldi	r24, 0x39	; 57
    2c18:	93 e0       	ldi	r25, 0x03	; 3
    2c1a:	9f 93       	push	r25
    2c1c:	8f 93       	push	r24
    2c1e:	0e 94 a8 05 	call	0xb50	; 0xb50 <_Z15Serial_printf_PPKcz>
    2c22:	0e 94 d5 11 	call	0x23aa	; 0x23aa <_Z3remv>
    2c26:	80 91 8b 02 	lds	r24, 0x028B	; 0x80028b <eeprom_crc_error>
    2c2a:	1f 92       	push	r1
    2c2c:	8f 93       	push	r24
    2c2e:	80 91 8a 04 	lds	r24, 0x048A	; 0x80048a <register_mem+0x79>
    2c32:	1f 92       	push	r1
    2c34:	8f 93       	push	r24
    2c36:	80 91 89 04 	lds	r24, 0x0489	; 0x800489 <register_mem+0x78>
    2c3a:	1f 92       	push	r1
    2c3c:	8f 93       	push	r24
    2c3e:	8f e0       	ldi	r24, 0x0F	; 15
    2c40:	93 e0       	ldi	r25, 0x03	; 3
    2c42:	9f 93       	push	r25
    2c44:	8f 93       	push	r24
    2c46:	0e 94 a8 05 	call	0xb50	; 0xb50 <_Z15Serial_printf_PPKcz>
    2c4a:	0f b6       	in	r0, 0x3f	; 63
    2c4c:	f8 94       	cli
    2c4e:	de bf       	out	0x3e, r29	; 62
    2c50:	0f be       	out	0x3f, r0	; 63
    2c52:	cd bf       	out	0x3d, r28	; 61
    2c54:	89 ea       	ldi	r24, 0xA9	; 169
    2c56:	92 e0       	ldi	r25, 0x02	; 2
    2c58:	0e 94 4c 11 	call	0x2298	; 0x2298 <_ZN14HardwareSerial5flushEv>
    2c5c:	67 96       	adiw	r28, 0x17	; 23
    2c5e:	0f b6       	in	r0, 0x3f	; 63
    2c60:	f8 94       	cli
    2c62:	de bf       	out	0x3e, r29	; 62
    2c64:	0f be       	out	0x3f, r0	; 63
    2c66:	cd bf       	out	0x3d, r28	; 61
    2c68:	df 91       	pop	r29
    2c6a:	cf 91       	pop	r28
    2c6c:	1f 91       	pop	r17
    2c6e:	0f 91       	pop	r16
    2c70:	ff 90       	pop	r15
    2c72:	ef 90       	pop	r14
    2c74:	df 90       	pop	r13
    2c76:	cf 90       	pop	r12
    2c78:	08 95       	ret

00002c7a <_Z12write_configv>:
    2c7a:	8f 92       	push	r8
    2c7c:	9f 92       	push	r9
    2c7e:	af 92       	push	r10
    2c80:	bf 92       	push	r11
    2c82:	cf 92       	push	r12
    2c84:	df 92       	push	r13
    2c86:	ef 92       	push	r14
    2c88:	ff 92       	push	r15
    2c8a:	0e 94 99 0e 	call	0x1d32	; 0x1d32 <millis>
    2c8e:	6b 01       	movw	r12, r22
    2c90:	7c 01       	movw	r14, r24
    2c92:	80 91 97 02 	lds	r24, 0x0297	; 0x800297 <dimmer_scheduled_calls>
    2c96:	83 fd       	sbrc	r24, 3
    2c98:	35 c0       	rjmp	.+106    	; 0x2d04 <_Z12write_configv+0x8a>
    2c9a:	80 90 00 01 	lds	r8, 0x0100	; 0x800100 <__data_start>
    2c9e:	90 90 01 01 	lds	r9, 0x0101	; 0x800101 <__data_start+0x1>
    2ca2:	a0 90 02 01 	lds	r10, 0x0102	; 0x800102 <__data_start+0x2>
    2ca6:	b0 90 03 01 	lds	r11, 0x0103	; 0x800103 <__data_start+0x3>
    2caa:	0e 94 99 0e 	call	0x1d32	; 0x1d32 <millis>
    2cae:	c8 18       	sub	r12, r8
    2cb0:	d9 08       	sbc	r13, r9
    2cb2:	ea 08       	sbc	r14, r10
    2cb4:	fb 08       	sbc	r15, r11
    2cb6:	29 e8       	ldi	r18, 0x89	; 137
    2cb8:	c2 16       	cp	r12, r18
    2cba:	23 e1       	ldi	r18, 0x13	; 19
    2cbc:	d2 06       	cpc	r13, r18
    2cbe:	e1 04       	cpc	r14, r1
    2cc0:	f1 04       	cpc	r15, r1
    2cc2:	3c f4       	brge	.+14     	; 0x2cd2 <_Z12write_configv+0x58>
    2cc4:	38 e8       	ldi	r19, 0x88	; 136
    2cc6:	c3 2e       	mov	r12, r19
    2cc8:	33 e1       	ldi	r19, 0x13	; 19
    2cca:	d3 2e       	mov	r13, r19
    2ccc:	e1 2c       	mov	r14, r1
    2cce:	f1 2c       	mov	r15, r1
    2cd0:	06 c0       	rjmp	.+12     	; 0x2cde <_Z12write_configv+0x64>
    2cd2:	24 ef       	ldi	r18, 0xF4	; 244
    2cd4:	c2 2e       	mov	r12, r18
    2cd6:	dd 24       	eor	r13, r13
    2cd8:	d3 94       	inc	r13
    2cda:	e1 2c       	mov	r14, r1
    2cdc:	f1 2c       	mov	r15, r1
    2cde:	dc 01       	movw	r26, r24
    2ce0:	cb 01       	movw	r24, r22
    2ce2:	8c 0d       	add	r24, r12
    2ce4:	9d 1d       	adc	r25, r13
    2ce6:	ae 1d       	adc	r26, r14
    2ce8:	bf 1d       	adc	r27, r15
    2cea:	80 93 00 01 	sts	0x0100, r24	; 0x800100 <__data_start>
    2cee:	90 93 01 01 	sts	0x0101, r25	; 0x800101 <__data_start+0x1>
    2cf2:	a0 93 02 01 	sts	0x0102, r26	; 0x800102 <__data_start+0x2>
    2cf6:	b0 93 03 01 	sts	0x0103, r27	; 0x800103 <__data_start+0x3>
    2cfa:	80 91 97 02 	lds	r24, 0x0297	; 0x800297 <dimmer_scheduled_calls>
    2cfe:	88 60       	ori	r24, 0x08	; 8
    2d00:	80 93 97 02 	sts	0x0297, r24	; 0x800297 <dimmer_scheduled_calls>
    2d04:	ff 90       	pop	r15
    2d06:	ef 90       	pop	r14
    2d08:	df 90       	pop	r13
    2d0a:	cf 90       	pop	r12
    2d0c:	bf 90       	pop	r11
    2d0e:	af 90       	pop	r10
    2d10:	9f 90       	pop	r9
    2d12:	8f 90       	pop	r8
    2d14:	08 95       	ret

00002d16 <_Z11serialEventv>:
    2d16:	cf 92       	push	r12
    2d18:	df 92       	push	r13
    2d1a:	ef 92       	push	r14
    2d1c:	ff 92       	push	r15
    2d1e:	0f 93       	push	r16
    2d20:	1f 93       	push	r17
    2d22:	cf 93       	push	r28
    2d24:	df 93       	push	r29
    2d26:	00 d0       	rcall	.+0      	; 0x2d28 <_Z11serialEventv+0x12>
    2d28:	00 d0       	rcall	.+0      	; 0x2d2a <_Z11serialEventv+0x14>
    2d2a:	00 d0       	rcall	.+0      	; 0x2d2c <_Z11serialEventv+0x16>
    2d2c:	cd b7       	in	r28, 0x3d	; 61
    2d2e:	de b7       	in	r29, 0x3e	; 62
    2d30:	82 e0       	ldi	r24, 0x02	; 2
    2d32:	e8 2e       	mov	r14, r24
    2d34:	f1 2c       	mov	r15, r1
    2d36:	cc 24       	eor	r12, r12
    2d38:	c3 94       	inc	r12
    2d3a:	d1 2c       	mov	r13, r1
    2d3c:	80 91 81 03 	lds	r24, 0x0381	; 0x800381 <Wire+0x3b>
    2d40:	90 91 82 03 	lds	r25, 0x0382	; 0x800382 <Wire+0x3c>
    2d44:	dc 01       	movw	r26, r24
    2d46:	ed 91       	ld	r30, X+
    2d48:	fc 91       	ld	r31, X
    2d4a:	00 84       	ldd	r0, Z+8	; 0x08
    2d4c:	f1 85       	ldd	r31, Z+9	; 0x09
    2d4e:	e0 2d       	mov	r30, r0
    2d50:	09 95       	icall
    2d52:	89 2b       	or	r24, r25
    2d54:	09 f4       	brne	.+2      	; 0x2d58 <_Z11serialEventv+0x42>
    2d56:	ce c0       	rjmp	.+412    	; 0x2ef4 <_Z11serialEventv+0x1de>
    2d58:	80 91 81 03 	lds	r24, 0x0381	; 0x800381 <Wire+0x3b>
    2d5c:	90 91 82 03 	lds	r25, 0x0382	; 0x800382 <Wire+0x3c>
    2d60:	dc 01       	movw	r26, r24
    2d62:	ed 91       	ld	r30, X+
    2d64:	fc 91       	ld	r31, X
    2d66:	02 84       	ldd	r0, Z+10	; 0x0a
    2d68:	f3 85       	ldd	r31, Z+11	; 0x0b
    2d6a:	e0 2d       	mov	r30, r0
    2d6c:	09 95       	icall
    2d6e:	8c 01       	movw	r16, r24
    2d70:	8d 30       	cpi	r24, 0x0D	; 13
    2d72:	21 f3       	breq	.-56     	; 0x2d3c <_Z11serialEventv+0x26>
    2d74:	20 91 79 03 	lds	r18, 0x0379	; 0x800379 <Wire+0x33>
    2d78:	30 91 7a 03 	lds	r19, 0x037A	; 0x80037a <Wire+0x34>
    2d7c:	8a 30       	cpi	r24, 0x0A	; 10
    2d7e:	09 f0       	breq	.+2      	; 0x2d82 <_Z11serialEventv+0x6c>
    2d80:	5a c0       	rjmp	.+180    	; 0x2e36 <_Z11serialEventv+0x120>
    2d82:	12 16       	cp	r1, r18
    2d84:	13 06       	cpc	r1, r19
    2d86:	0c f0       	brlt	.+2      	; 0x2d8a <_Z11serialEventv+0x74>
    2d88:	51 c0       	rjmp	.+162    	; 0x2e2c <_Z11serialEventv+0x116>
    2d8a:	80 91 7f 03 	lds	r24, 0x037F	; 0x80037f <Wire+0x39>
    2d8e:	90 91 80 03 	lds	r25, 0x0380	; 0x800380 <Wire+0x3a>
    2d92:	02 97       	sbiw	r24, 0x02	; 2
    2d94:	11 f4       	brne	.+4      	; 0x2d9a <_Z11serialEventv+0x84>
    2d96:	0e 94 cb 0f 	call	0x1f96	; 0x1f96 <_ZN13SerialTwoWire10_addBufferEv.part.4.constprop.19>
    2d9a:	80 91 65 03 	lds	r24, 0x0365	; 0x800365 <Wire+0x1f>
    2d9e:	90 91 66 03 	lds	r25, 0x0366	; 0x800366 <Wire+0x20>
    2da2:	02 97       	sbiw	r24, 0x02	; 2
    2da4:	08 f4       	brcc	.+2      	; 0x2da8 <_Z11serialEventv+0x92>
    2da6:	42 c0       	rjmp	.+132    	; 0x2e2c <_Z11serialEventv+0x116>
    2da8:	80 91 79 03 	lds	r24, 0x0379	; 0x800379 <Wire+0x33>
    2dac:	90 91 7a 03 	lds	r25, 0x037A	; 0x80037a <Wire+0x34>
    2db0:	81 30       	cpi	r24, 0x01	; 1
    2db2:	91 05       	cpc	r25, r1
    2db4:	b9 f4       	brne	.+46     	; 0x2de4 <_Z11serialEventv+0xce>
    2db6:	85 e5       	ldi	r24, 0x55	; 85
    2db8:	93 e0       	ldi	r25, 0x03	; 3
    2dba:	0e 94 5d 0f 	call	0x1eba	; 0x1eba <_ZN12StreamString4readEv>
    2dbe:	20 91 52 03 	lds	r18, 0x0352	; 0x800352 <Wire+0xc>
    2dc2:	30 e0       	ldi	r19, 0x00	; 0
    2dc4:	82 17       	cp	r24, r18
    2dc6:	93 07       	cpc	r25, r19
    2dc8:	51 f4       	brne	.+20     	; 0x2dde <_Z11serialEventv+0xc8>
    2dca:	e0 91 83 03 	lds	r30, 0x0383	; 0x800383 <Wire+0x3d>
    2dce:	f0 91 84 03 	lds	r31, 0x0384	; 0x800384 <Wire+0x3e>
    2dd2:	80 91 65 03 	lds	r24, 0x0365	; 0x800365 <Wire+0x1f>
    2dd6:	90 91 66 03 	lds	r25, 0x0366	; 0x800366 <Wire+0x20>
    2dda:	09 95       	icall
    2ddc:	27 c0       	rjmp	.+78     	; 0x2e2c <_Z11serialEventv+0x116>
    2dde:	10 92 53 03 	sts	0x0353, r1	; 0x800353 <Wire+0xd>
    2de2:	24 c0       	rjmp	.+72     	; 0x2e2c <_Z11serialEventv+0x116>
    2de4:	02 97       	sbiw	r24, 0x02	; 2
    2de6:	11 f5       	brne	.+68     	; 0x2e2c <_Z11serialEventv+0x116>
    2de8:	e0 91 61 03 	lds	r30, 0x0361	; 0x800361 <Wire+0x1b>
    2dec:	f0 91 62 03 	lds	r31, 0x0362	; 0x800362 <Wire+0x1c>
    2df0:	30 97       	sbiw	r30, 0x00	; 0
    2df2:	11 f0       	breq	.+4      	; 0x2df8 <_Z11serialEventv+0xe2>
    2df4:	01 81       	ldd	r16, Z+1	; 0x01
    2df6:	01 c0       	rjmp	.+2      	; 0x2dfa <_Z11serialEventv+0xe4>
    2df8:	00 e0       	ldi	r16, 0x00	; 0
    2dfa:	80 91 52 03 	lds	r24, 0x0352	; 0x800352 <Wire+0xc>
    2dfe:	0e 94 a0 1c 	call	0x3940	; 0x3940 <_ZN13SerialTwoWire17beginTransmissionEh.constprop.22>
    2e02:	e0 91 85 03 	lds	r30, 0x0385	; 0x800385 <Wire+0x3f>
    2e06:	f0 91 86 03 	lds	r31, 0x0386	; 0x800386 <Wire+0x40>
    2e0a:	09 95       	icall
    2e0c:	10 e0       	ldi	r17, 0x00	; 0
    2e0e:	80 91 77 03 	lds	r24, 0x0377	; 0x800377 <Wire+0x31>
    2e12:	90 91 78 03 	lds	r25, 0x0378	; 0x800378 <Wire+0x32>
    2e16:	08 17       	cp	r16, r24
    2e18:	19 07       	cpc	r17, r25
    2e1a:	30 f0       	brcs	.+12     	; 0x2e28 <_Z11serialEventv+0x112>
    2e1c:	6f ef       	ldi	r22, 0xFF	; 255
    2e1e:	87 e6       	ldi	r24, 0x67	; 103
    2e20:	93 e0       	ldi	r25, 0x03	; 3
    2e22:	0e 94 46 0f 	call	0x1e8c	; 0x1e8c <_ZN12StreamString5writeEh>
    2e26:	f3 cf       	rjmp	.-26     	; 0x2e0e <_Z11serialEventv+0xf8>
    2e28:	0e 94 57 1c 	call	0x38ae	; 0x38ae <_ZN13SerialTwoWire15endTransmissionEh.constprop.25>
    2e2c:	10 92 7a 03 	sts	0x037A, r1	; 0x80037a <Wire+0x34>
    2e30:	10 92 79 03 	sts	0x0379, r1	; 0x800379 <Wire+0x33>
    2e34:	52 c0       	rjmp	.+164    	; 0x2eda <_Z11serialEventv+0x1c4>
    2e36:	2f 3f       	cpi	r18, 0xFF	; 255
    2e38:	bf ef       	ldi	r27, 0xFF	; 255
    2e3a:	3b 07       	cpc	r19, r27
    2e3c:	09 f4       	brne	.+2      	; 0x2e40 <_Z11serialEventv+0x12a>
    2e3e:	7e cf       	rjmp	.-260    	; 0x2d3c <_Z11serialEventv+0x26>
    2e40:	23 2b       	or	r18, r19
    2e42:	91 f0       	breq	.+36     	; 0x2e68 <_Z11serialEventv+0x152>
    2e44:	8c 32       	cpi	r24, 0x2C	; 44
    2e46:	09 f4       	brne	.+2      	; 0x2e4a <_Z11serialEventv+0x134>
    2e48:	79 cf       	rjmp	.-270    	; 0x2d3c <_Z11serialEventv+0x26>
    2e4a:	68 2f       	mov	r22, r24
    2e4c:	8b e7       	ldi	r24, 0x7B	; 123
    2e4e:	93 e0       	ldi	r25, 0x03	; 3
    2e50:	0e 94 16 0f 	call	0x1e2c	; 0x1e2c <_ZN6String6concatEc>
    2e54:	80 91 7f 03 	lds	r24, 0x037F	; 0x80037f <Wire+0x39>
    2e58:	90 91 80 03 	lds	r25, 0x0380	; 0x800380 <Wire+0x3a>
    2e5c:	02 97       	sbiw	r24, 0x02	; 2
    2e5e:	09 f0       	breq	.+2      	; 0x2e62 <_Z11serialEventv+0x14c>
    2e60:	6d cf       	rjmp	.-294    	; 0x2d3c <_Z11serialEventv+0x26>
    2e62:	0e 94 cb 0f 	call	0x1f96	; 0x1f96 <_ZN13SerialTwoWire10_addBufferEv.part.4.constprop.19>
    2e66:	6a cf       	rjmp	.-300    	; 0x2d3c <_Z11serialEventv+0x26>
    2e68:	80 91 7f 03 	lds	r24, 0x037F	; 0x80037f <Wire+0x39>
    2e6c:	90 91 80 03 	lds	r25, 0x0380	; 0x800380 <Wire+0x3a>
    2e70:	00 97       	sbiw	r24, 0x00	; 0
    2e72:	39 f4       	brne	.+14     	; 0x2e82 <_Z11serialEventv+0x16c>
    2e74:	c8 01       	movw	r24, r16
    2e76:	99 27       	eor	r25, r25
    2e78:	0e 94 af 27 	call	0x4f5e	; 0x4f5e <isspace>
    2e7c:	89 2b       	or	r24, r25
    2e7e:	21 f0       	breq	.+8      	; 0x2e88 <_Z11serialEventv+0x172>
    2e80:	5d cf       	rjmp	.-326    	; 0x2d3c <_Z11serialEventv+0x26>
    2e82:	40 97       	sbiw	r24, 0x10	; 16
    2e84:	08 f0       	brcs	.+2      	; 0x2e88 <_Z11serialEventv+0x172>
    2e86:	5a cf       	rjmp	.-332    	; 0x2d3c <_Z11serialEventv+0x26>
    2e88:	60 2f       	mov	r22, r16
    2e8a:	8b e7       	ldi	r24, 0x7B	; 123
    2e8c:	93 e0       	ldi	r25, 0x03	; 3
    2e8e:	0e 94 16 0f 	call	0x1e2c	; 0x1e2c <_ZN6String6concatEc>
    2e92:	00 91 7b 03 	lds	r16, 0x037B	; 0x80037b <Wire+0x35>
    2e96:	10 91 7c 03 	lds	r17, 0x037C	; 0x80037c <Wire+0x36>
    2e9a:	6c ec       	ldi	r22, 0xCC	; 204
    2e9c:	74 e0       	ldi	r23, 0x04	; 4
    2e9e:	c8 01       	movw	r24, r16
    2ea0:	0e 94 c5 27 	call	0x4f8a	; 0x4f8a <strcasecmp_P>
    2ea4:	89 2b       	or	r24, r25
    2ea6:	49 f4       	brne	.+18     	; 0x2eba <_Z11serialEventv+0x1a4>
    2ea8:	81 e6       	ldi	r24, 0x61	; 97
    2eaa:	93 e0       	ldi	r25, 0x03	; 3
    2eac:	0e 94 4b 0f 	call	0x1e96	; 0x1e96 <_ZN6String10invalidateEv>
    2eb0:	d0 92 7a 03 	sts	0x037A, r13	; 0x80037a <Wire+0x34>
    2eb4:	c0 92 79 03 	sts	0x0379, r12	; 0x800379 <Wire+0x33>
    2eb8:	10 c0       	rjmp	.+32     	; 0x2eda <_Z11serialEventv+0x1c4>
    2eba:	65 ec       	ldi	r22, 0xC5	; 197
    2ebc:	74 e0       	ldi	r23, 0x04	; 4
    2ebe:	c8 01       	movw	r24, r16
    2ec0:	0e 94 c5 27 	call	0x4f8a	; 0x4f8a <strcasecmp_P>
    2ec4:	89 2b       	or	r24, r25
    2ec6:	09 f0       	breq	.+2      	; 0x2eca <_Z11serialEventv+0x1b4>
    2ec8:	39 cf       	rjmp	.-398    	; 0x2d3c <_Z11serialEventv+0x26>
    2eca:	81 e6       	ldi	r24, 0x61	; 97
    2ecc:	93 e0       	ldi	r25, 0x03	; 3
    2ece:	0e 94 4b 0f 	call	0x1e96	; 0x1e96 <_ZN6String10invalidateEv>
    2ed2:	f0 92 7a 03 	sts	0x037A, r15	; 0x80037a <Wire+0x34>
    2ed6:	e0 92 79 03 	sts	0x0379, r14	; 0x800379 <Wire+0x33>
    2eda:	ce 01       	movw	r24, r28
    2edc:	01 96       	adiw	r24, 0x01	; 1
    2ede:	0e 94 d5 1b 	call	0x37aa	; 0x37aa <_ZN6StringC2EPKc.constprop.37>
    2ee2:	ce 01       	movw	r24, r28
    2ee4:	01 96       	adiw	r24, 0x01	; 1
    2ee6:	0e 94 98 1b 	call	0x3730	; 0x3730 <_ZN6String4moveERS_.constprop.40>
    2eea:	ce 01       	movw	r24, r28
    2eec:	01 96       	adiw	r24, 0x01	; 1
    2eee:	0e 94 c6 0f 	call	0x1f8c	; 0x1f8c <_ZN6StringD1Ev>
    2ef2:	24 cf       	rjmp	.-440    	; 0x2d3c <_Z11serialEventv+0x26>
    2ef4:	26 96       	adiw	r28, 0x06	; 6
    2ef6:	0f b6       	in	r0, 0x3f	; 63
    2ef8:	f8 94       	cli
    2efa:	de bf       	out	0x3e, r29	; 62
    2efc:	0f be       	out	0x3f, r0	; 63
    2efe:	cd bf       	out	0x3d, r28	; 61
    2f00:	df 91       	pop	r29
    2f02:	cf 91       	pop	r28
    2f04:	1f 91       	pop	r17
    2f06:	0f 91       	pop	r16
    2f08:	ff 90       	pop	r15
    2f0a:	ef 90       	pop	r14
    2f0c:	df 90       	pop	r13
    2f0e:	cf 90       	pop	r12
    2f10:	08 95       	ret

00002f12 <_Z14serialEventRunv>:
    2f12:	0e 94 d3 10 	call	0x21a6	; 0x21a6 <_Z17Serial0_availablev>
    2f16:	81 11       	cpse	r24, r1
    2f18:	0c 94 8b 16 	jmp	0x2d16	; 0x2d16 <_Z11serialEventv>
    2f1c:	08 95       	ret

00002f1e <_ZN13ConfigStorage5writeEj.constprop.86>:
    2f1e:	af 92       	push	r10
    2f20:	bf 92       	push	r11
    2f22:	cf 92       	push	r12
    2f24:	df 92       	push	r13
    2f26:	ef 92       	push	r14
    2f28:	ff 92       	push	r15
    2f2a:	0f 93       	push	r16
    2f2c:	1f 93       	push	r17
    2f2e:	cf 93       	push	r28
    2f30:	df 93       	push	r29
    2f32:	00 d0       	rcall	.+0      	; 0x2f34 <_ZN13ConfigStorage5writeEj.constprop.86+0x16>
    2f34:	cd b7       	in	r28, 0x3d	; 61
    2f36:	de b7       	in	r29, 0x3e	; 62
    2f38:	8c 01       	movw	r16, r24
    2f3a:	30 e9       	ldi	r19, 0x90	; 144
    2f3c:	a3 2e       	mov	r10, r19
    2f3e:	34 e0       	ldi	r19, 0x04	; 4
    2f40:	b3 2e       	mov	r11, r19
    2f42:	4c e8       	ldi	r20, 0x8C	; 140
    2f44:	e4 2e       	mov	r14, r20
    2f46:	44 e0       	ldi	r20, 0x04	; 4
    2f48:	f4 2e       	mov	r15, r20
    2f4a:	8c 58       	subi	r24, 0x8C	; 140
    2f4c:	94 40       	sbci	r25, 0x04	; 4
    2f4e:	6c 01       	movw	r12, r24
    2f50:	c7 01       	movw	r24, r14
    2f52:	8c 0d       	add	r24, r12
    2f54:	9d 1d       	adc	r25, r13
    2f56:	f7 01       	movw	r30, r14
    2f58:	61 91       	ld	r22, Z+
    2f5a:	7f 01       	movw	r14, r30
    2f5c:	9a 83       	std	Y+2, r25	; 0x02
    2f5e:	89 83       	std	Y+1, r24	; 0x01
    2f60:	ce 01       	movw	r24, r28
    2f62:	01 96       	adiw	r24, 0x01	; 1
    2f64:	0e 94 cb 0d 	call	0x1b96	; 0x1b96 <_ZN5EERef6updateEh>
    2f68:	ae 14       	cp	r10, r14
    2f6a:	bf 04       	cpc	r11, r15
    2f6c:	89 f7       	brne	.-30     	; 0x2f50 <_ZN13ConfigStorage5writeEj.constprop.86+0x32>
    2f6e:	c8 01       	movw	r24, r16
    2f70:	04 96       	adiw	r24, 0x04	; 4
    2f72:	60 91 90 04 	lds	r22, 0x0490	; 0x800490 <config+0x4>
    2f76:	9a 83       	std	Y+2, r25	; 0x02
    2f78:	89 83       	std	Y+1, r24	; 0x01
    2f7a:	ce 01       	movw	r24, r28
    2f7c:	01 96       	adiw	r24, 0x01	; 1
    2f7e:	0e 94 cb 0d 	call	0x1b96	; 0x1b96 <_ZN5EERef6updateEh>
    2f82:	60 91 91 04 	lds	r22, 0x0491	; 0x800491 <config+0x5>
    2f86:	c8 01       	movw	r24, r16
    2f88:	05 96       	adiw	r24, 0x05	; 5
    2f8a:	9a 83       	std	Y+2, r25	; 0x02
    2f8c:	89 83       	std	Y+1, r24	; 0x01
    2f8e:	ce 01       	movw	r24, r28
    2f90:	01 96       	adiw	r24, 0x01	; 1
    2f92:	0e 94 cb 0d 	call	0x1b96	; 0x1b96 <_ZN5EERef6updateEh>
    2f96:	92 e9       	ldi	r25, 0x92	; 146
    2f98:	e9 2e       	mov	r14, r25
    2f9a:	94 e0       	ldi	r25, 0x04	; 4
    2f9c:	f9 2e       	mov	r15, r25
    2f9e:	2a e9       	ldi	r18, 0x9A	; 154
    2fa0:	a2 2e       	mov	r10, r18
    2fa2:	24 e0       	ldi	r18, 0x04	; 4
    2fa4:	b2 2e       	mov	r11, r18
    2fa6:	c6 01       	movw	r24, r12
    2fa8:	8e 0d       	add	r24, r14
    2faa:	9f 1d       	adc	r25, r15
    2fac:	f7 01       	movw	r30, r14
    2fae:	61 91       	ld	r22, Z+
    2fb0:	7f 01       	movw	r14, r30
    2fb2:	9a 83       	std	Y+2, r25	; 0x02
    2fb4:	89 83       	std	Y+1, r24	; 0x01
    2fb6:	ce 01       	movw	r24, r28
    2fb8:	01 96       	adiw	r24, 0x01	; 1
    2fba:	0e 94 cb 0d 	call	0x1b96	; 0x1b96 <_ZN5EERef6updateEh>
    2fbe:	ae 14       	cp	r10, r14
    2fc0:	bf 04       	cpc	r11, r15
    2fc2:	89 f7       	brne	.-30     	; 0x2fa6 <_ZN13ConfigStorage5writeEj.constprop.86+0x88>
    2fc4:	83 e3       	ldi	r24, 0x33	; 51
    2fc6:	e8 2e       	mov	r14, r24
    2fc8:	84 e0       	ldi	r24, 0x04	; 4
    2fca:	f8 2e       	mov	r15, r24
    2fcc:	68 01       	movw	r12, r16
    2fce:	f2 e2       	ldi	r31, 0x22	; 34
    2fd0:	cf 0e       	add	r12, r31
    2fd2:	d1 1c       	adc	r13, r1
    2fd4:	02 5f       	subi	r16, 0xF2	; 242
    2fd6:	1f 4f       	sbci	r17, 0xFF	; 255
    2fd8:	f7 01       	movw	r30, r14
    2fda:	61 91       	ld	r22, Z+
    2fdc:	7f 01       	movw	r14, r30
    2fde:	1a 83       	std	Y+2, r17	; 0x02
    2fe0:	09 83       	std	Y+1, r16	; 0x01
    2fe2:	ce 01       	movw	r24, r28
    2fe4:	01 96       	adiw	r24, 0x01	; 1
    2fe6:	0e 94 cb 0d 	call	0x1b96	; 0x1b96 <_ZN5EERef6updateEh>
    2fea:	0f 5f       	subi	r16, 0xFF	; 255
    2fec:	1f 4f       	sbci	r17, 0xFF	; 255
    2fee:	0c 15       	cp	r16, r12
    2ff0:	1d 05       	cpc	r17, r13
    2ff2:	91 f7       	brne	.-28     	; 0x2fd8 <_ZN13ConfigStorage5writeEj.constprop.86+0xba>
    2ff4:	c8 01       	movw	r24, r16
    2ff6:	0f 90       	pop	r0
    2ff8:	0f 90       	pop	r0
    2ffa:	df 91       	pop	r29
    2ffc:	cf 91       	pop	r28
    2ffe:	1f 91       	pop	r17
    3000:	0f 91       	pop	r16
    3002:	ff 90       	pop	r15
    3004:	ef 90       	pop	r14
    3006:	df 90       	pop	r13
    3008:	cf 90       	pop	r12
    300a:	bf 90       	pop	r11
    300c:	af 90       	pop	r10
    300e:	08 95       	ret

00003010 <_ZNK13ConfigStorage3crcEv.constprop.83>:
    3010:	44 e1       	ldi	r20, 0x14	; 20
    3012:	50 e0       	ldi	r21, 0x00	; 0
    3014:	63 e3       	ldi	r22, 0x33	; 51
    3016:	74 e0       	ldi	r23, 0x04	; 4
    3018:	8f ef       	ldi	r24, 0xFF	; 255
    301a:	9f ef       	ldi	r25, 0xFF	; 255
    301c:	0e 94 62 09 	call	0x12c4	; 0x12c4 <_Z12crc16_updatejPKhj>
    3020:	48 e0       	ldi	r20, 0x08	; 8
    3022:	50 e0       	ldi	r21, 0x00	; 0
    3024:	62 e9       	ldi	r22, 0x92	; 146
    3026:	74 e0       	ldi	r23, 0x04	; 4
    3028:	0c 94 62 09 	jmp	0x12c4	; 0x12c4 <_Z12crc16_updatejPKhj>

0000302c <_ZN5Print7printlnEPK19__FlashStringHelper.constprop.70>:
    302c:	cf 93       	push	r28
    302e:	df 93       	push	r29
    3030:	bc 01       	movw	r22, r24
    3032:	89 ea       	ldi	r24, 0xA9	; 169
    3034:	92 e0       	ldi	r25, 0x02	; 2
    3036:	0e 94 b1 11 	call	0x2362	; 0x2362 <_ZN5Print5printEPK19__FlashStringHelper>
    303a:	ec 01       	movw	r28, r24
    303c:	89 ea       	ldi	r24, 0xA9	; 169
    303e:	92 e0       	ldi	r25, 0x02	; 2
    3040:	0e 94 39 12 	call	0x2472	; 0x2472 <_ZN5Print7printlnEv>
    3044:	8c 0f       	add	r24, r28
    3046:	9d 1f       	adc	r25, r29
    3048:	df 91       	pop	r29
    304a:	cf 91       	pop	r28
    304c:	08 95       	ret

0000304e <_ZN6Dimmer18_calculateChannelsEv.constprop.69>:
    304e:	4f 92       	push	r4
    3050:	5f 92       	push	r5
    3052:	6f 92       	push	r6
    3054:	7f 92       	push	r7
    3056:	af 92       	push	r10
    3058:	bf 92       	push	r11
    305a:	cf 92       	push	r12
    305c:	df 92       	push	r13
    305e:	ef 92       	push	r14
    3060:	ff 92       	push	r15
    3062:	0f 93       	push	r16
    3064:	1f 93       	push	r17
    3066:	cf 93       	push	r28
    3068:	df 93       	push	r29
    306a:	cd b7       	in	r28, 0x3d	; 61
    306c:	de b7       	in	r29, 0x3e	; 62
    306e:	6e 97       	sbiw	r28, 0x1e	; 30
    3070:	0f b6       	in	r0, 0x3f	; 63
    3072:	f8 94       	cli
    3074:	de bf       	out	0x3e, r29	; 62
    3076:	0f be       	out	0x3f, r0	; 63
    3078:	cd bf       	out	0x3d, r28	; 61
    307a:	f8 94       	cli
    307c:	80 91 0c 04 	lds	r24, 0x040C	; 0x80040c <dimmer+0x80>
    3080:	82 ff       	sbrs	r24, 2
    3082:	0b c0       	rjmp	.+22     	; 0x309a <_ZN6Dimmer18_calculateChannelsEv.constprop.69+0x4c>
    3084:	80 91 0c 04 	lds	r24, 0x040C	; 0x80040c <dimmer+0x80>
    3088:	88 60       	ori	r24, 0x08	; 8
    308a:	80 93 0c 04 	sts	0x040C, r24	; 0x80040c <dimmer+0x80>
    308e:	78 94       	sei
    3090:	81 ef       	ldi	r24, 0xF1	; 241
    3092:	94 e0       	ldi	r25, 0x04	; 4
    3094:	0e 94 16 18 	call	0x302c	; 0x302c <_ZN5Print7printlnEPK19__FlashStringHelper.constprop.70>
    3098:	d2 c0       	rjmp	.+420    	; 0x323e <_ZN6Dimmer18_calculateChannelsEv.constprop.69+0x1f0>
    309a:	80 91 0c 04 	lds	r24, 0x040C	; 0x80040c <dimmer+0x80>
    309e:	84 60       	ori	r24, 0x04	; 4
    30a0:	80 93 0c 04 	sts	0x040C, r24	; 0x80040c <dimmer+0x80>
    30a4:	78 94       	sei
    30a6:	8e 01       	movw	r16, r28
    30a8:	0f 5f       	subi	r16, 0xFF	; 255
    30aa:	1f 4f       	sbci	r17, 0xFF	; 255
    30ac:	89 e1       	ldi	r24, 0x19	; 25
    30ae:	d8 01       	movw	r26, r16
    30b0:	1d 92       	st	X+, r1
    30b2:	8a 95       	dec	r24
    30b4:	e9 f7       	brne	.-6      	; 0x30b0 <_ZN6Dimmer18_calculateChannelsEv.constprop.69+0x62>
    30b6:	e0 91 3c 04 	lds	r30, 0x043C	; 0x80043c <register_mem+0x2b>
    30ba:	f0 91 3d 04 	lds	r31, 0x043D	; 0x80043d <register_mem+0x2c>
    30be:	c0 90 3e 04 	lds	r12, 0x043E	; 0x80043e <register_mem+0x2d>
    30c2:	d0 90 3f 04 	lds	r13, 0x043F	; 0x80043f <register_mem+0x2e>
    30c6:	9d e1       	ldi	r25, 0x1D	; 29
    30c8:	e9 2e       	mov	r14, r25
    30ca:	94 e0       	ldi	r25, 0x04	; 4
    30cc:	f9 2e       	mov	r15, r25
    30ce:	40 e0       	ldi	r20, 0x00	; 0
    30d0:	50 e0       	ldi	r21, 0x00	; 0
    30d2:	aa 24       	eor	r10, r10
    30d4:	aa 94       	dec	r10
    30d6:	ba 2c       	mov	r11, r10
    30d8:	80 91 0c 04 	lds	r24, 0x040C	; 0x80040c <dimmer+0x80>
    30dc:	83 ff       	sbrs	r24, 3
    30de:	12 c0       	rjmp	.+36     	; 0x3104 <_ZN6Dimmer18_calculateChannelsEv.constprop.69+0xb6>
    30e0:	f8 94       	cli
    30e2:	80 91 0c 04 	lds	r24, 0x040C	; 0x80040c <dimmer+0x80>
    30e6:	83 7f       	andi	r24, 0xF3	; 243
    30e8:	80 93 0c 04 	sts	0x040C, r24	; 0x80040c <dimmer+0x80>
    30ec:	78 94       	sei
    30ee:	6b ec       	ldi	r22, 0xCB	; 203
    30f0:	71 e0       	ldi	r23, 0x01	; 1
    30f2:	89 ea       	ldi	r24, 0xA9	; 169
    30f4:	92 e0       	ldi	r25, 0x02	; 2
    30f6:	0e 94 db 11 	call	0x23b6	; 0x23b6 <_ZN5Print5writeEPKc>
    30fa:	89 ea       	ldi	r24, 0xA9	; 169
    30fc:	92 e0       	ldi	r25, 0x02	; 2
    30fe:	0e 94 39 12 	call	0x2472	; 0x2472 <_ZN5Print7printlnEv>
    3102:	9d c0       	rjmp	.+314    	; 0x323e <_ZN6Dimmer18_calculateChannelsEv.constprop.69+0x1f0>
    3104:	d7 01       	movw	r26, r14
    3106:	2d 91       	ld	r18, X+
    3108:	3d 91       	ld	r19, X+
    310a:	7d 01       	movw	r14, r26
    310c:	2f 3f       	cpi	r18, 0xFF	; 255
    310e:	bf e1       	ldi	r27, 0x1F	; 31
    3110:	3b 07       	cpc	r19, r27
    3112:	58 f0       	brcs	.+22     	; 0x312a <_ZN6Dimmer18_calculateChannelsEv.constprop.69+0xdc>
    3114:	25 e0       	ldi	r18, 0x05	; 5
    3116:	42 03       	mulsu	r20, r18
    3118:	d0 01       	movw	r26, r0
    311a:	11 24       	eor	r1, r1
    311c:	a0 0f       	add	r26, r16
    311e:	b1 1f       	adc	r27, r17
    3120:	12 96       	adiw	r26, 0x02	; 2
    3122:	bc 92       	st	X, r11
    3124:	ae 92       	st	-X, r10
    3126:	11 97       	sbiw	r26, 0x01	; 1
    3128:	31 c0       	rjmp	.+98     	; 0x318c <_ZN6Dimmer18_calculateChannelsEv.constprop.69+0x13e>
    312a:	21 15       	cp	r18, r1
    312c:	31 05       	cpc	r19, r1
    312e:	81 f1       	breq	.+96     	; 0x3190 <_ZN6Dimmer18_calculateChannelsEv.constprop.69+0x142>
    3130:	a0 91 f8 03 	lds	r26, 0x03F8	; 0x8003f8 <dimmer+0x6c>
    3134:	b0 91 f9 03 	lds	r27, 0x03F9	; 0x8003f9 <dimmer+0x6d>
    3138:	0e 94 65 2a 	call	0x54ca	; 0x54ca <__umulhisi3>
    313c:	2b 01       	movw	r4, r22
    313e:	3c 01       	movw	r6, r24
    3140:	8d e0       	ldi	r24, 0x0D	; 13
    3142:	76 94       	lsr	r7
    3144:	67 94       	ror	r6
    3146:	57 94       	ror	r5
    3148:	47 94       	ror	r4
    314a:	8a 95       	dec	r24
    314c:	d1 f7       	brne	.-12     	; 0x3142 <_ZN6Dimmer18_calculateChannelsEv.constprop.69+0xf4>
    314e:	4e 16       	cp	r4, r30
    3150:	5f 06       	cpc	r5, r31
    3152:	58 f0       	brcs	.+22     	; 0x316a <_ZN6Dimmer18_calculateChannelsEv.constprop.69+0x11c>
    3154:	80 91 f8 03 	lds	r24, 0x03F8	; 0x8003f8 <dimmer+0x6c>
    3158:	90 91 f9 03 	lds	r25, 0x03F9	; 0x8003f9 <dimmer+0x6d>
    315c:	8c 19       	sub	r24, r12
    315e:	9d 09       	sbc	r25, r13
    3160:	48 16       	cp	r4, r24
    3162:	59 06       	cpc	r5, r25
    3164:	38 f4       	brcc	.+14     	; 0x3174 <_ZN6Dimmer18_calculateChannelsEv.constprop.69+0x126>
    3166:	b2 01       	movw	r22, r4
    3168:	01 c0       	rjmp	.+2      	; 0x316c <_ZN6Dimmer18_calculateChannelsEv.constprop.69+0x11e>
    316a:	bf 01       	movw	r22, r30
    316c:	61 15       	cp	r22, r1
    316e:	71 05       	cpc	r23, r1
    3170:	79 f0       	breq	.+30     	; 0x3190 <_ZN6Dimmer18_calculateChannelsEv.constprop.69+0x142>
    3172:	02 c0       	rjmp	.+4      	; 0x3178 <_ZN6Dimmer18_calculateChannelsEv.constprop.69+0x12a>
    3174:	6f ef       	ldi	r22, 0xFF	; 255
    3176:	7f ef       	ldi	r23, 0xFF	; 255
    3178:	35 e0       	ldi	r19, 0x05	; 5
    317a:	43 03       	mulsu	r20, r19
    317c:	d0 01       	movw	r26, r0
    317e:	11 24       	eor	r1, r1
    3180:	a0 0f       	add	r26, r16
    3182:	b1 1f       	adc	r27, r17
    3184:	12 96       	adiw	r26, 0x02	; 2
    3186:	7c 93       	st	X, r23
    3188:	6e 93       	st	-X, r22
    318a:	11 97       	sbiw	r26, 0x01	; 1
    318c:	5c 93       	st	X, r21
    318e:	4f 5f       	subi	r20, 0xFF	; 255
    3190:	5f 5f       	subi	r21, 0xFF	; 255
    3192:	54 30       	cpi	r21, 0x04	; 4
    3194:	09 f0       	breq	.+2      	; 0x3198 <_ZN6Dimmer18_calculateChannelsEv.constprop.69+0x14a>
    3196:	a0 cf       	rjmp	.-192    	; 0x30d8 <_ZN6Dimmer18_calculateChannelsEv.constprop.69+0x8a>
    3198:	42 30       	cpi	r20, 0x02	; 2
    319a:	84 f4       	brge	.+32     	; 0x31bc <_ZN6Dimmer18_calculateChannelsEv.constprop.69+0x16e>
    319c:	f8 94       	cli
    319e:	89 e1       	ldi	r24, 0x19	; 25
    31a0:	f8 01       	movw	r30, r16
    31a2:	a7 ed       	ldi	r26, 0xD7	; 215
    31a4:	b3 e0       	ldi	r27, 0x03	; 3
    31a6:	01 90       	ld	r0, Z+
    31a8:	0d 92       	st	X+, r0
    31aa:	8a 95       	dec	r24
    31ac:	e1 f7       	brne	.-8      	; 0x31a6 <_ZN6Dimmer18_calculateChannelsEv.constprop.69+0x158>
    31ae:	80 91 0c 04 	lds	r24, 0x040C	; 0x80040c <dimmer+0x80>
    31b2:	8b 7f       	andi	r24, 0xFB	; 251
    31b4:	80 93 0c 04 	sts	0x040C, r24	; 0x80040c <dimmer+0x80>
    31b8:	78 94       	sei
    31ba:	41 c0       	rjmp	.+130    	; 0x323e <_ZN6Dimmer18_calculateChannelsEv.constprop.69+0x1f0>
    31bc:	41 50       	subi	r20, 0x01	; 1
    31be:	60 e0       	ldi	r22, 0x00	; 0
    31c0:	70 e0       	ldi	r23, 0x00	; 0
    31c2:	c4 2e       	mov	r12, r20
    31c4:	d1 2c       	mov	r13, r1
    31c6:	20 e0       	ldi	r18, 0x00	; 0
    31c8:	56 01       	movw	r10, r12
    31ca:	a6 1a       	sub	r10, r22
    31cc:	b7 0a       	sbc	r11, r23
    31ce:	82 2f       	mov	r24, r18
    31d0:	02 2e       	mov	r0, r18
    31d2:	00 0c       	add	r0, r0
    31d4:	99 0b       	sbc	r25, r25
    31d6:	8a 15       	cp	r24, r10
    31d8:	9b 05       	cpc	r25, r11
    31da:	64 f5       	brge	.+88     	; 0x3234 <_ZN6Dimmer18_calculateChannelsEv.constprop.69+0x1e6>
    31dc:	a5 e0       	ldi	r26, 0x05	; 5
    31de:	2a 02       	muls	r18, r26
    31e0:	c0 01       	movw	r24, r0
    31e2:	11 24       	eor	r1, r1
    31e4:	78 01       	movw	r14, r16
    31e6:	e8 0e       	add	r14, r24
    31e8:	f9 1e       	adc	r15, r25
    31ea:	05 96       	adiw	r24, 0x05	; 5
    31ec:	80 0f       	add	r24, r16
    31ee:	91 1f       	adc	r25, r17
    31f0:	f7 01       	movw	r30, r14
    31f2:	a1 81       	ldd	r26, Z+1	; 0x01
    31f4:	b2 81       	ldd	r27, Z+2	; 0x02
    31f6:	fc 01       	movw	r30, r24
    31f8:	61 80       	ldd	r6, Z+1	; 0x01
    31fa:	72 80       	ldd	r7, Z+2	; 0x02
    31fc:	6a 16       	cp	r6, r26
    31fe:	7b 06       	cpc	r7, r27
    3200:	b8 f4       	brcc	.+46     	; 0x3230 <_ZN6Dimmer18_calculateChannelsEv.constprop.69+0x1e2>
    3202:	35 e0       	ldi	r19, 0x05	; 5
    3204:	f7 01       	movw	r30, r14
    3206:	de 01       	movw	r26, r28
    3208:	5a 96       	adiw	r26, 0x1a	; 26
    320a:	01 90       	ld	r0, Z+
    320c:	0d 92       	st	X+, r0
    320e:	3a 95       	dec	r19
    3210:	e1 f7       	brne	.-8      	; 0x320a <_ZN6Dimmer18_calculateChannelsEv.constprop.69+0x1bc>
    3212:	35 e0       	ldi	r19, 0x05	; 5
    3214:	fc 01       	movw	r30, r24
    3216:	d7 01       	movw	r26, r14
    3218:	01 90       	ld	r0, Z+
    321a:	0d 92       	st	X+, r0
    321c:	3a 95       	dec	r19
    321e:	e1 f7       	brne	.-8      	; 0x3218 <_ZN6Dimmer18_calculateChannelsEv.constprop.69+0x1ca>
    3220:	35 e0       	ldi	r19, 0x05	; 5
    3222:	fe 01       	movw	r30, r28
    3224:	7a 96       	adiw	r30, 0x1a	; 26
    3226:	dc 01       	movw	r26, r24
    3228:	01 90       	ld	r0, Z+
    322a:	0d 92       	st	X+, r0
    322c:	3a 95       	dec	r19
    322e:	e1 f7       	brne	.-8      	; 0x3228 <_ZN6Dimmer18_calculateChannelsEv.constprop.69+0x1da>
    3230:	2f 5f       	subi	r18, 0xFF	; 255
    3232:	cd cf       	rjmp	.-102    	; 0x31ce <_ZN6Dimmer18_calculateChannelsEv.constprop.69+0x180>
    3234:	6f 5f       	subi	r22, 0xFF	; 255
    3236:	7f 4f       	sbci	r23, 0xFF	; 255
    3238:	64 17       	cp	r22, r20
    323a:	2c f2       	brlt	.-118    	; 0x31c6 <_ZN6Dimmer18_calculateChannelsEv.constprop.69+0x178>
    323c:	af cf       	rjmp	.-162    	; 0x319c <_ZN6Dimmer18_calculateChannelsEv.constprop.69+0x14e>
    323e:	6e 96       	adiw	r28, 0x1e	; 30
    3240:	0f b6       	in	r0, 0x3f	; 63
    3242:	f8 94       	cli
    3244:	de bf       	out	0x3e, r29	; 62
    3246:	0f be       	out	0x3f, r0	; 63
    3248:	cd bf       	out	0x3d, r28	; 61
    324a:	df 91       	pop	r29
    324c:	cf 91       	pop	r28
    324e:	1f 91       	pop	r17
    3250:	0f 91       	pop	r16
    3252:	ff 90       	pop	r15
    3254:	ef 90       	pop	r14
    3256:	df 90       	pop	r13
    3258:	cf 90       	pop	r12
    325a:	bf 90       	pop	r11
    325c:	af 90       	pop	r10
    325e:	7f 90       	pop	r7
    3260:	6f 90       	pop	r6
    3262:	5f 90       	pop	r5
    3264:	4f 90       	pop	r4
    3266:	08 95       	ret

00003268 <_ZN6Dimmer6_faultEPKc.constprop.59>:
    3268:	2f 92       	push	r2
    326a:	3f 92       	push	r3
    326c:	4f 92       	push	r4
    326e:	5f 92       	push	r5
    3270:	6f 92       	push	r6
    3272:	7f 92       	push	r7
    3274:	8f 92       	push	r8
    3276:	9f 92       	push	r9
    3278:	af 92       	push	r10
    327a:	bf 92       	push	r11
    327c:	cf 92       	push	r12
    327e:	df 92       	push	r13
    3280:	ef 92       	push	r14
    3282:	ff 92       	push	r15
    3284:	0f 93       	push	r16
    3286:	1f 93       	push	r17
    3288:	cf 93       	push	r28
    328a:	df 93       	push	r29
    328c:	cd b7       	in	r28, 0x3d	; 61
    328e:	de b7       	in	r29, 0x3e	; 62
    3290:	2b 97       	sbiw	r28, 0x0b	; 11
    3292:	0f b6       	in	r0, 0x3f	; 63
    3294:	f8 94       	cli
    3296:	de bf       	out	0x3e, r29	; 62
    3298:	0f be       	out	0x3f, r0	; 63
    329a:	cd bf       	out	0x3d, r28	; 61
    329c:	4c 01       	movw	r8, r24
    329e:	80 91 84 00 	lds	r24, 0x0084	; 0x800084 <__TEXT_REGION_LENGTH__+0x7e0084>
    32a2:	90 91 85 00 	lds	r25, 0x0085	; 0x800085 <__TEXT_REGION_LENGTH__+0x7e0085>
    32a6:	9e 83       	std	Y+6, r25	; 0x06
    32a8:	8d 83       	std	Y+5, r24	; 0x05
    32aa:	e0 90 88 00 	lds	r14, 0x0088	; 0x800088 <__TEXT_REGION_LENGTH__+0x7e0088>
    32ae:	f0 90 89 00 	lds	r15, 0x0089	; 0x800089 <__TEXT_REGION_LENGTH__+0x7e0089>
    32b2:	c0 90 8a 00 	lds	r12, 0x008A	; 0x80008a <__TEXT_REGION_LENGTH__+0x7e008a>
    32b6:	d0 90 8b 00 	lds	r13, 0x008B	; 0x80008b <__TEXT_REGION_LENGTH__+0x7e008b>
    32ba:	a0 90 07 04 	lds	r10, 0x0407	; 0x800407 <dimmer+0x7b>
    32be:	b0 90 08 04 	lds	r11, 0x0408	; 0x800408 <dimmer+0x7c>
    32c2:	20 90 09 04 	lds	r2, 0x0409	; 0x800409 <dimmer+0x7d>
    32c6:	30 90 0a 04 	lds	r3, 0x040A	; 0x80040a <dimmer+0x7e>
    32ca:	90 91 6f 00 	lds	r25, 0x006F	; 0x80006f <__TEXT_REGION_LENGTH__+0x7e006f>
    32ce:	9f 83       	std	Y+7, r25	; 0x07
    32d0:	e6 b3       	in	r30, 0x16	; 22
    32d2:	e8 87       	std	Y+8, r30	; 0x08
    32d4:	f0 91 0b 04 	lds	r31, 0x040B	; 0x80040b <dimmer+0x7f>
    32d8:	fb 87       	std	Y+11, r31	; 0x0b
    32da:	50 90 0c 04 	lds	r5, 0x040C	; 0x80040c <dimmer+0x80>
    32de:	20 91 bc 03 	lds	r18, 0x03BC	; 0x8003bc <dimmer+0x30>
    32e2:	30 91 bd 03 	lds	r19, 0x03BD	; 0x8003bd <dimmer+0x31>
    32e6:	2e 5b       	subi	r18, 0xBE	; 190
    32e8:	33 40       	sbci	r19, 0x03	; 3
    32ea:	4d ec       	ldi	r20, 0xCD	; 205
    32ec:	5c ec       	ldi	r21, 0xCC	; 204
    32ee:	24 9f       	mul	r18, r20
    32f0:	c0 01       	movw	r24, r0
    32f2:	25 9f       	mul	r18, r21
    32f4:	90 0d       	add	r25, r0
    32f6:	34 9f       	mul	r19, r20
    32f8:	90 0d       	add	r25, r0
    32fa:	11 24       	eor	r1, r1
    32fc:	65 e0       	ldi	r22, 0x05	; 5
    32fe:	70 e0       	ldi	r23, 0x00	; 0
    3300:	0e 94 74 2a 	call	0x54e8	; 0x54e8 <__udivmodhi4>
    3304:	8b 01       	movw	r16, r22
    3306:	8e e0       	ldi	r24, 0x0E	; 14
    3308:	91 e0       	ldi	r25, 0x01	; 1
    330a:	9a 87       	std	Y+10, r25	; 0x0a
    330c:	89 87       	std	Y+9, r24	; 0x09
    330e:	9e 01       	movw	r18, r28
    3310:	2f 5f       	subi	r18, 0xFF	; 255
    3312:	3f 4f       	sbci	r19, 0xFF	; 255
    3314:	dc 01       	movw	r26, r24
    3316:	39 01       	movw	r6, r18
    3318:	8d 91       	ld	r24, X+
    331a:	90 e0       	ldi	r25, 0x00	; 0
    331c:	fc 01       	movw	r30, r24
    331e:	e3 52       	subi	r30, 0x23	; 35
    3320:	fb 4f       	sbci	r31, 0xFB	; 251
    3322:	54 91       	lpm	r21, Z
    3324:	fc 01       	movw	r30, r24
    3326:	e0 5d       	subi	r30, 0xD0	; 208
    3328:	fa 4f       	sbci	r31, 0xFA	; 250
    332a:	44 91       	lpm	r20, Z
    332c:	fc 01       	movw	r30, r24
    332e:	e4 5e       	subi	r30, 0xE4	; 228
    3330:	fa 4f       	sbci	r31, 0xFA	; 250
    3332:	e4 91       	lpm	r30, Z
    3334:	ee 23       	and	r30, r30
    3336:	a9 f1       	breq	.+106    	; 0x33a2 <_ZN6Dimmer6_faultEPKc.constprop.59+0x13a>
    3338:	55 23       	and	r21, r21
    333a:	39 f1       	breq	.+78     	; 0x338a <_ZN6Dimmer6_faultEPKc.constprop.59+0x122>
    333c:	53 30       	cpi	r21, 0x03	; 3
    333e:	91 f0       	breq	.+36     	; 0x3364 <_ZN6Dimmer6_faultEPKc.constprop.59+0xfc>
    3340:	38 f4       	brcc	.+14     	; 0x3350 <_ZN6Dimmer6_faultEPKc.constprop.59+0xe8>
    3342:	51 30       	cpi	r21, 0x01	; 1
    3344:	a9 f0       	breq	.+42     	; 0x3370 <_ZN6Dimmer6_faultEPKc.constprop.59+0x108>
    3346:	52 30       	cpi	r21, 0x02	; 2
    3348:	01 f5       	brne	.+64     	; 0x338a <_ZN6Dimmer6_faultEPKc.constprop.59+0x122>
    334a:	84 b5       	in	r24, 0x24	; 36
    334c:	8f 7d       	andi	r24, 0xDF	; 223
    334e:	12 c0       	rjmp	.+36     	; 0x3374 <_ZN6Dimmer6_faultEPKc.constprop.59+0x10c>
    3350:	57 30       	cpi	r21, 0x07	; 7
    3352:	91 f0       	breq	.+36     	; 0x3378 <_ZN6Dimmer6_faultEPKc.constprop.59+0x110>
    3354:	58 30       	cpi	r21, 0x08	; 8
    3356:	a1 f0       	breq	.+40     	; 0x3380 <_ZN6Dimmer6_faultEPKc.constprop.59+0x118>
    3358:	54 30       	cpi	r21, 0x04	; 4
    335a:	b9 f4       	brne	.+46     	; 0x338a <_ZN6Dimmer6_faultEPKc.constprop.59+0x122>
    335c:	80 91 80 00 	lds	r24, 0x0080	; 0x800080 <__TEXT_REGION_LENGTH__+0x7e0080>
    3360:	8f 7d       	andi	r24, 0xDF	; 223
    3362:	03 c0       	rjmp	.+6      	; 0x336a <_ZN6Dimmer6_faultEPKc.constprop.59+0x102>
    3364:	80 91 80 00 	lds	r24, 0x0080	; 0x800080 <__TEXT_REGION_LENGTH__+0x7e0080>
    3368:	8f 77       	andi	r24, 0x7F	; 127
    336a:	80 93 80 00 	sts	0x0080, r24	; 0x800080 <__TEXT_REGION_LENGTH__+0x7e0080>
    336e:	0d c0       	rjmp	.+26     	; 0x338a <_ZN6Dimmer6_faultEPKc.constprop.59+0x122>
    3370:	84 b5       	in	r24, 0x24	; 36
    3372:	8f 77       	andi	r24, 0x7F	; 127
    3374:	84 bd       	out	0x24, r24	; 36
    3376:	09 c0       	rjmp	.+18     	; 0x338a <_ZN6Dimmer6_faultEPKc.constprop.59+0x122>
    3378:	80 91 b0 00 	lds	r24, 0x00B0	; 0x8000b0 <__TEXT_REGION_LENGTH__+0x7e00b0>
    337c:	8f 77       	andi	r24, 0x7F	; 127
    337e:	03 c0       	rjmp	.+6      	; 0x3386 <_ZN6Dimmer6_faultEPKc.constprop.59+0x11e>
    3380:	80 91 b0 00 	lds	r24, 0x00B0	; 0x8000b0 <__TEXT_REGION_LENGTH__+0x7e00b0>
    3384:	8f 7d       	andi	r24, 0xDF	; 223
    3386:	80 93 b0 00 	sts	0x00B0, r24	; 0x8000b0 <__TEXT_REGION_LENGTH__+0x7e00b0>
    338a:	f0 e0       	ldi	r31, 0x00	; 0
    338c:	ee 0f       	add	r30, r30
    338e:	ff 1f       	adc	r31, r31
    3390:	ed 52       	subi	r30, 0x2D	; 45
    3392:	fb 4f       	sbci	r31, 0xFB	; 251
    3394:	65 91       	lpm	r22, Z+
    3396:	74 91       	lpm	r23, Z
    3398:	fb 01       	movw	r30, r22
    339a:	80 81       	ld	r24, Z
    339c:	48 23       	and	r20, r24
    339e:	81 e0       	ldi	r24, 0x01	; 1
    33a0:	09 f4       	brne	.+2      	; 0x33a4 <_ZN6Dimmer6_faultEPKc.constprop.59+0x13c>
    33a2:	80 e0       	ldi	r24, 0x00	; 0
    33a4:	f9 01       	movw	r30, r18
    33a6:	81 93       	st	Z+, r24
    33a8:	9f 01       	movw	r18, r30
    33aa:	f1 e0       	ldi	r31, 0x01	; 1
    33ac:	a2 31       	cpi	r26, 0x12	; 18
    33ae:	bf 07       	cpc	r27, r31
    33b0:	09 f0       	breq	.+2      	; 0x33b4 <_ZN6Dimmer6_faultEPKc.constprop.59+0x14c>
    33b2:	b2 cf       	rjmp	.-156    	; 0x3318 <_ZN6Dimmer6_faultEPKc.constprop.59+0xb0>
    33b4:	f8 94       	cli
    33b6:	e9 98       	cbi	0x1d, 1	; 29
    33b8:	8b ef       	ldi	r24, 0xFB	; 251
    33ba:	9d e0       	ldi	r25, 0x0D	; 13
    33bc:	90 93 07 01 	sts	0x0107, r25	; 0x800107 <intFunc.lto_priv.98+0x3>
    33c0:	80 93 06 01 	sts	0x0106, r24	; 0x800106 <intFunc.lto_priv.98+0x2>
    33c4:	41 2c       	mov	r4, r1
    33c6:	84 2d       	mov	r24, r4
    33c8:	0e 94 f3 07 	call	0xfe6	; 0xfe6 <_ZN6Dimmer14disableChannelEa.isra.2.lto_priv.95>
    33cc:	60 e0       	ldi	r22, 0x00	; 0
    33ce:	e9 85       	ldd	r30, Y+9	; 0x09
    33d0:	fa 85       	ldd	r31, Y+10	; 0x0a
    33d2:	81 91       	ld	r24, Z+
    33d4:	fa 87       	std	Y+10, r31	; 0x0a
    33d6:	e9 87       	std	Y+9, r30	; 0x09
    33d8:	0e 94 fe 0d 	call	0x1bfc	; 0x1bfc <pinMode>
    33dc:	43 94       	inc	r4
    33de:	f4 e0       	ldi	r31, 0x04	; 4
    33e0:	4f 12       	cpse	r4, r31
    33e2:	f1 cf       	rjmp	.-30     	; 0x33c6 <_ZN6Dimmer6_faultEPKc.constprop.59+0x15e>
    33e4:	81 e0       	ldi	r24, 0x01	; 1
    33e6:	80 93 0b 04 	sts	0x040B, r24	; 0x80040b <dimmer+0x7f>
    33ea:	80 91 6f 00 	lds	r24, 0x006F	; 0x80006f <__TEXT_REGION_LENGTH__+0x7e006f>
    33ee:	88 7f       	andi	r24, 0xF8	; 248
    33f0:	80 93 6f 00 	sts	0x006F, r24	; 0x80006f <__TEXT_REGION_LENGTH__+0x7e006f>
    33f4:	78 94       	sei
    33f6:	b4 01       	movw	r22, r8
    33f8:	89 ea       	ldi	r24, 0xA9	; 169
    33fa:	92 e0       	ldi	r25, 0x02	; 2
    33fc:	0e 94 db 11 	call	0x23b6	; 0x23b6 <_ZN5Print5writeEPKc>
    3400:	89 ea       	ldi	r24, 0xA9	; 169
    3402:	92 e0       	ldi	r25, 0x02	; 2
    3404:	0e 94 39 12 	call	0x2472	; 0x2472 <_ZN5Print7printlnEv>
    3408:	df 92       	push	r13
    340a:	cf 92       	push	r12
    340c:	c7 01       	movw	r24, r14
    340e:	80 54       	subi	r24, 0x40	; 64
    3410:	91 09       	sbc	r25, r1
    3412:	9f 93       	push	r25
    3414:	8f 93       	push	r24
    3416:	ff 92       	push	r15
    3418:	ef 92       	push	r14
    341a:	8e 81       	ldd	r24, Y+6	; 0x06
    341c:	8f 93       	push	r24
    341e:	9d 81       	ldd	r25, Y+5	; 0x05
    3420:	9f 93       	push	r25
    3422:	83 ed       	ldi	r24, 0xD3	; 211
    3424:	91 e0       	ldi	r25, 0x01	; 1
    3426:	9f 93       	push	r25
    3428:	8f 93       	push	r24
    342a:	0e 94 1a 06 	call	0xc34	; 0xc34 <_Z13Serial_printfPKcz>
    342e:	3f 92       	push	r3
    3430:	2f 92       	push	r2
    3432:	bf 92       	push	r11
    3434:	af 92       	push	r10
    3436:	83 ef       	ldi	r24, 0xF3	; 243
    3438:	91 e0       	ldi	r25, 0x01	; 1
    343a:	9f 93       	push	r25
    343c:	8f 93       	push	r24
    343e:	0e 94 1a 06 	call	0xc34	; 0xc34 <_Z13Serial_printfPKcz>
    3442:	85 2d       	mov	r24, r5
    3444:	81 70       	andi	r24, 0x01	; 1
    3446:	1f 92       	push	r1
    3448:	8f 93       	push	r24
    344a:	85 2d       	mov	r24, r5
    344c:	82 70       	andi	r24, 0x02	; 2
    344e:	1f 92       	push	r1
    3450:	8f 93       	push	r24
    3452:	8f 81       	ldd	r24, Y+7	; 0x07
    3454:	84 70       	andi	r24, 0x04	; 4
    3456:	1f 92       	push	r1
    3458:	8f 93       	push	r24
    345a:	8f 81       	ldd	r24, Y+7	; 0x07
    345c:	82 70       	andi	r24, 0x02	; 2
    345e:	1f 92       	push	r1
    3460:	8f 93       	push	r24
    3462:	8c e0       	ldi	r24, 0x0C	; 12
    3464:	92 e0       	ldi	r25, 0x02	; 2
    3466:	9f 93       	push	r25
    3468:	8f 93       	push	r24
    346a:	0e 94 1a 06 	call	0xc34	; 0xc34 <_Z13Serial_printfPKcz>
    346e:	88 85       	ldd	r24, Y+8	; 0x08
    3470:	84 70       	andi	r24, 0x04	; 4
    3472:	1f 92       	push	r1
    3474:	8f 93       	push	r24
    3476:	88 85       	ldd	r24, Y+8	; 0x08
    3478:	82 70       	andi	r24, 0x02	; 2
    347a:	1f 92       	push	r1
    347c:	8f 93       	push	r24
    347e:	83 e3       	ldi	r24, 0x33	; 51
    3480:	92 e0       	ldi	r25, 0x02	; 2
    3482:	9f 93       	push	r25
    3484:	8f 93       	push	r24
    3486:	0e 94 1a 06 	call	0xc34	; 0xc34 <_Z13Serial_printfPKcz>
    348a:	0f b6       	in	r0, 0x3f	; 63
    348c:	f8 94       	cli
    348e:	de bf       	out	0x3e, r29	; 62
    3490:	0f be       	out	0x3f, r0	; 63
    3492:	cd bf       	out	0x3d, r28	; 61
    3494:	11 27       	eor	r17, r17
    3496:	1f 93       	push	r17
    3498:	0f 93       	push	r16
    349a:	1f 92       	push	r1
    349c:	fb 85       	ldd	r31, Y+11	; 0x0b
    349e:	ff 93       	push	r31
    34a0:	86 e4       	ldi	r24, 0x46	; 70
    34a2:	92 e0       	ldi	r25, 0x02	; 2
    34a4:	9f 93       	push	r25
    34a6:	8f 93       	push	r24
    34a8:	0e 94 1a 06 	call	0xc34	; 0xc34 <_Z13Serial_printfPKcz>
    34ac:	0f 90       	pop	r0
    34ae:	0f 90       	pop	r0
    34b0:	0f 90       	pop	r0
    34b2:	0f 90       	pop	r0
    34b4:	0f 90       	pop	r0
    34b6:	0f 90       	pop	r0
    34b8:	10 e0       	ldi	r17, 0x00	; 0
    34ba:	05 e0       	ldi	r16, 0x05	; 5
    34bc:	82 e6       	ldi	r24, 0x62	; 98
    34be:	e8 2e       	mov	r14, r24
    34c0:	82 e0       	ldi	r24, 0x02	; 2
    34c2:	f8 2e       	mov	r15, r24
    34c4:	21 2f       	mov	r18, r17
    34c6:	01 2e       	mov	r0, r17
    34c8:	00 0c       	add	r0, r0
    34ca:	33 0b       	sbc	r19, r19
    34cc:	02 9f       	mul	r16, r18
    34ce:	f0 01       	movw	r30, r0
    34d0:	03 9f       	mul	r16, r19
    34d2:	f0 0d       	add	r31, r0
    34d4:	11 24       	eor	r1, r1
    34d6:	e4 57       	subi	r30, 0x74	; 116
    34d8:	fc 4f       	sbci	r31, 0xFC	; 252
    34da:	83 a9       	ldd	r24, Z+51	; 0x33
    34dc:	94 a9       	ldd	r25, Z+52	; 0x34
    34de:	00 97       	sbiw	r24, 0x00	; 0
    34e0:	e1 f0       	breq	.+56     	; 0x351a <_ZN6Dimmer6_faultEPKc.constprop.59+0x2b2>
    34e2:	22 a9       	ldd	r18, Z+50	; 0x32
    34e4:	d3 01       	movw	r26, r6
    34e6:	a2 0f       	add	r26, r18
    34e8:	b1 1d       	adc	r27, r1
    34ea:	4c 91       	ld	r20, X
    34ec:	1f 92       	push	r1
    34ee:	4f 93       	push	r20
    34f0:	46 a9       	ldd	r20, Z+54	; 0x36
    34f2:	4f 93       	push	r20
    34f4:	45 a9       	ldd	r20, Z+53	; 0x35
    34f6:	4f 93       	push	r20
    34f8:	9f 93       	push	r25
    34fa:	8f 93       	push	r24
    34fc:	1f 92       	push	r1
    34fe:	2f 93       	push	r18
    3500:	3f 93       	push	r19
    3502:	1f 93       	push	r17
    3504:	ff 92       	push	r15
    3506:	ef 92       	push	r14
    3508:	0e 94 1a 06 	call	0xc34	; 0xc34 <_Z13Serial_printfPKcz>
    350c:	1f 5f       	subi	r17, 0xFF	; 255
    350e:	0f b6       	in	r0, 0x3f	; 63
    3510:	f8 94       	cli
    3512:	de bf       	out	0x3e, r29	; 62
    3514:	0f be       	out	0x3f, r0	; 63
    3516:	cd bf       	out	0x3d, r28	; 61
    3518:	d5 cf       	rjmp	.-86     	; 0x34c4 <_ZN6Dimmer6_faultEPKc.constprop.59+0x25c>
    351a:	2b 96       	adiw	r28, 0x0b	; 11
    351c:	0f b6       	in	r0, 0x3f	; 63
    351e:	f8 94       	cli
    3520:	de bf       	out	0x3e, r29	; 62
    3522:	0f be       	out	0x3f, r0	; 63
    3524:	cd bf       	out	0x3d, r28	; 61
    3526:	df 91       	pop	r29
    3528:	cf 91       	pop	r28
    352a:	1f 91       	pop	r17
    352c:	0f 91       	pop	r16
    352e:	ff 90       	pop	r15
    3530:	ef 90       	pop	r14
    3532:	df 90       	pop	r13
    3534:	cf 90       	pop	r12
    3536:	bf 90       	pop	r11
    3538:	af 90       	pop	r10
    353a:	9f 90       	pop	r9
    353c:	8f 90       	pop	r8
    353e:	7f 90       	pop	r7
    3540:	6f 90       	pop	r6
    3542:	5f 90       	pop	r5
    3544:	4f 90       	pop	r4
    3546:	3f 90       	pop	r3
    3548:	2f 90       	pop	r2
    354a:	08 95       	ret

0000354c <_ZN6Dimmer12_endHalfwaveEv.constprop.55>:
    354c:	f8 94       	cli
    354e:	ec e0       	ldi	r30, 0x0C	; 12
    3550:	f4 e0       	ldi	r31, 0x04	; 4
    3552:	80 81       	ld	r24, Z
    3554:	8e 7f       	andi	r24, 0xFE	; 254
    3556:	80 83       	st	Z, r24
    3558:	84 e0       	ldi	r24, 0x04	; 4
    355a:	80 93 0b 04 	sts	0x040B, r24	; 0x80040b <dimmer+0x7f>
    355e:	b1 9a       	sbi	0x16, 1	; 22
    3560:	ef e6       	ldi	r30, 0x6F	; 111
    3562:	f0 e0       	ldi	r31, 0x00	; 0
    3564:	80 81       	ld	r24, Z
    3566:	8d 7f       	andi	r24, 0xFD	; 253
    3568:	80 83       	st	Z, r24
    356a:	78 94       	sei
    356c:	08 95       	ret

0000356e <_ZN6Dimmer7setFadeEaiifb.constprop.49>:
    356e:	4f 92       	push	r4
    3570:	5f 92       	push	r5
    3572:	6f 92       	push	r6
    3574:	7f 92       	push	r7
    3576:	8f 92       	push	r8
    3578:	9f 92       	push	r9
    357a:	af 92       	push	r10
    357c:	bf 92       	push	r11
    357e:	cf 92       	push	r12
    3580:	df 92       	push	r13
    3582:	ef 92       	push	r14
    3584:	ff 92       	push	r15
    3586:	0f 93       	push	r16
    3588:	1f 93       	push	r17
    358a:	cf 93       	push	r28
    358c:	df 93       	push	r29
    358e:	7a 01       	movw	r14, r20
    3590:	48 01       	movw	r8, r16
    3592:	59 01       	movw	r10, r18
    3594:	c8 2e       	mov	r12, r24
    3596:	88 0f       	add	r24, r24
    3598:	dd 08       	sbc	r13, r13
    359a:	f6 01       	movw	r30, r12
    359c:	ee 0f       	add	r30, r30
    359e:	ff 1f       	adc	r31, r31
    35a0:	e0 51       	subi	r30, 0x10	; 16
    35a2:	fc 4f       	sbci	r31, 0xFC	; 252
    35a4:	8f ef       	ldi	r24, 0xFF	; 255
    35a6:	9f ef       	ldi	r25, 0xFF	; 255
    35a8:	91 83       	std	Z+1, r25	; 0x01
    35aa:	80 83       	st	Z, r24
    35ac:	6f 3f       	cpi	r22, 0xFF	; 255
    35ae:	8f ef       	ldi	r24, 0xFF	; 255
    35b0:	78 07       	cpc	r23, r24
    35b2:	41 f4       	brne	.+16     	; 0x35c4 <_ZN6Dimmer7setFadeEaiifb.constprop.49+0x56>
    35b4:	f6 01       	movw	r30, r12
    35b6:	ee 0f       	add	r30, r30
    35b8:	ff 1f       	adc	r31, r31
    35ba:	e3 5e       	subi	r30, 0xE3	; 227
    35bc:	fb 4f       	sbci	r31, 0xFB	; 251
    35be:	c0 81       	ld	r28, Z
    35c0:	d1 81       	ldd	r29, Z+1	; 0x01
    35c2:	01 c0       	rjmp	.+2      	; 0x35c6 <_ZN6Dimmer7setFadeEaiifb.constprop.49+0x58>
    35c4:	eb 01       	movw	r28, r22
    35c6:	d7 fd       	sbrc	r29, 7
    35c8:	07 c0       	rjmp	.+14     	; 0x35d8 <_ZN6Dimmer7setFadeEaiifb.constprop.49+0x6a>
    35ca:	cf 3f       	cpi	r28, 0xFF	; 255
    35cc:	ef e1       	ldi	r30, 0x1F	; 31
    35ce:	de 07       	cpc	r29, r30
    35d0:	2c f0       	brlt	.+10     	; 0x35dc <_ZN6Dimmer7setFadeEaiifb.constprop.49+0x6e>
    35d2:	cf ef       	ldi	r28, 0xFF	; 255
    35d4:	df e1       	ldi	r29, 0x1F	; 31
    35d6:	02 c0       	rjmp	.+4      	; 0x35dc <_ZN6Dimmer7setFadeEaiifb.constprop.49+0x6e>
    35d8:	c0 e0       	ldi	r28, 0x00	; 0
    35da:	d0 e0       	ldi	r29, 0x00	; 0
    35dc:	f7 fc       	sbrc	r15, 7
    35de:	07 c0       	rjmp	.+14     	; 0x35ee <_ZN6Dimmer7setFadeEaiifb.constprop.49+0x80>
    35e0:	ff ef       	ldi	r31, 0xFF	; 255
    35e2:	ef 16       	cp	r14, r31
    35e4:	ff e1       	ldi	r31, 0x1F	; 31
    35e6:	ff 06       	cpc	r15, r31
    35e8:	2c f4       	brge	.+10     	; 0x35f4 <_ZN6Dimmer7setFadeEaiifb.constprop.49+0x86>
    35ea:	b7 01       	movw	r22, r14
    35ec:	05 c0       	rjmp	.+10     	; 0x35f8 <_ZN6Dimmer7setFadeEaiifb.constprop.49+0x8a>
    35ee:	60 e0       	ldi	r22, 0x00	; 0
    35f0:	70 e0       	ldi	r23, 0x00	; 0
    35f2:	02 c0       	rjmp	.+4      	; 0x35f8 <_ZN6Dimmer7setFadeEaiifb.constprop.49+0x8a>
    35f4:	6f ef       	ldi	r22, 0xFF	; 255
    35f6:	7f e1       	ldi	r23, 0x1F	; 31
    35f8:	6c 1b       	sub	r22, r28
    35fa:	7d 0b       	sbc	r23, r29
    35fc:	07 2e       	mov	r0, r23
    35fe:	00 0c       	add	r0, r0
    3600:	88 0b       	sbc	r24, r24
    3602:	99 0b       	sbc	r25, r25
    3604:	0e 94 f5 28 	call	0x51ea	; 0x51ea <__floatsisf>
    3608:	2b 01       	movw	r4, r22
    360a:	3c 01       	movw	r6, r24
    360c:	20 e0       	ldi	r18, 0x00	; 0
    360e:	30 e0       	ldi	r19, 0x00	; 0
    3610:	40 e0       	ldi	r20, 0x00	; 0
    3612:	59 e3       	ldi	r21, 0x39	; 57
    3614:	0e 94 54 29 	call	0x52a8	; 0x52a8 <__mulsf3>
    3618:	a5 01       	movw	r20, r10
    361a:	94 01       	movw	r18, r8
    361c:	0e 94 54 29 	call	0x52a8	; 0x52a8 <__mulsf3>
    3620:	4b 01       	movw	r8, r22
    3622:	5c 01       	movw	r10, r24
    3624:	20 e0       	ldi	r18, 0x00	; 0
    3626:	30 e0       	ldi	r19, 0x00	; 0
    3628:	a9 01       	movw	r20, r18
    362a:	0e 94 a3 2b 	call	0x5746	; 0x5746 <__gesf2>
    362e:	18 16       	cp	r1, r24
    3630:	24 f0       	brlt	.+8      	; 0x363a <_ZN6Dimmer7setFadeEaiifb.constprop.49+0xcc>
    3632:	b7 fa       	bst	r11, 7
    3634:	b0 94       	com	r11
    3636:	b7 f8       	bld	r11, 7
    3638:	b0 94       	com	r11
    363a:	80 91 f8 03 	lds	r24, 0x03F8	; 0x8003f8 <dimmer+0x6c>
    363e:	90 91 f9 03 	lds	r25, 0x03F9	; 0x8003f9 <dimmer+0x6d>
    3642:	89 2b       	or	r24, r25
    3644:	89 f0       	breq	.+34     	; 0x3668 <_ZN6Dimmer7setFadeEaiifb.constprop.49+0xfa>
    3646:	60 91 f8 03 	lds	r22, 0x03F8	; 0x8003f8 <dimmer+0x6c>
    364a:	70 91 f9 03 	lds	r23, 0x03F9	; 0x8003f9 <dimmer+0x6d>
    364e:	80 e0       	ldi	r24, 0x00	; 0
    3650:	90 e0       	ldi	r25, 0x00	; 0
    3652:	0e 94 f3 28 	call	0x51e6	; 0x51e6 <__floatunsisf>
    3656:	9b 01       	movw	r18, r22
    3658:	ac 01       	movw	r20, r24
    365a:	60 e0       	ldi	r22, 0x00	; 0
    365c:	74 e2       	ldi	r23, 0x24	; 36
    365e:	84 e7       	ldi	r24, 0x74	; 116
    3660:	99 e4       	ldi	r25, 0x49	; 73
    3662:	0e 94 fb 2a 	call	0x55f6	; 0x55f6 <__divsf3>
    3666:	04 c0       	rjmp	.+8      	; 0x3670 <_ZN6Dimmer7setFadeEaiifb.constprop.49+0x102>
    3668:	60 e0       	ldi	r22, 0x00	; 0
    366a:	70 e0       	ldi	r23, 0x00	; 0
    366c:	80 ec       	ldi	r24, 0xC0	; 192
    366e:	9f e7       	ldi	r25, 0x7F	; 127
    3670:	9b 01       	movw	r18, r22
    3672:	ac 01       	movw	r20, r24
    3674:	0e 94 8f 2a 	call	0x551e	; 0x551e <__addsf3>
    3678:	a5 01       	movw	r20, r10
    367a:	94 01       	movw	r18, r8
    367c:	0e 94 54 29 	call	0x52a8	; 0x52a8 <__mulsf3>
    3680:	0e 94 74 2b 	call	0x56e8	; 0x56e8 <__fixunssfsi>
    3684:	2c e0       	ldi	r18, 0x0C	; 12
    3686:	2c 9d       	mul	r18, r12
    3688:	f0 01       	movw	r30, r0
    368a:	2d 9d       	mul	r18, r13
    368c:	f0 0d       	add	r31, r0
    368e:	11 24       	eor	r1, r1
    3690:	e4 57       	subi	r30, 0x74	; 116
    3692:	fc 4f       	sbci	r31, 0xFC	; 252
    3694:	71 87       	std	Z+9, r23	; 0x09
    3696:	60 87       	std	Z+8, r22	; 0x08
    3698:	62 30       	cpi	r22, 0x02	; 2
    369a:	71 05       	cpc	r23, r1
    369c:	68 f0       	brcs	.+26     	; 0x36b8 <_ZN6Dimmer7setFadeEaiifb.constprop.49+0x14a>
    369e:	80 e0       	ldi	r24, 0x00	; 0
    36a0:	90 e0       	ldi	r25, 0x00	; 0
    36a2:	0e 94 f3 28 	call	0x51e6	; 0x51e6 <__floatunsisf>
    36a6:	9b 01       	movw	r18, r22
    36a8:	ac 01       	movw	r20, r24
    36aa:	c3 01       	movw	r24, r6
    36ac:	b2 01       	movw	r22, r4
    36ae:	0e 94 fb 2a 	call	0x55f6	; 0x55f6 <__divsf3>
    36b2:	4b 01       	movw	r8, r22
    36b4:	5c 01       	movw	r10, r24
    36b6:	03 c0       	rjmp	.+6      	; 0x36be <_ZN6Dimmer7setFadeEaiifb.constprop.49+0x150>
    36b8:	81 2c       	mov	r8, r1
    36ba:	91 2c       	mov	r9, r1
    36bc:	54 01       	movw	r10, r8
    36be:	8c e0       	ldi	r24, 0x0C	; 12
    36c0:	8c 9d       	mul	r24, r12
    36c2:	80 01       	movw	r16, r0
    36c4:	8d 9d       	mul	r24, r13
    36c6:	10 0d       	add	r17, r0
    36c8:	11 24       	eor	r1, r1
    36ca:	04 57       	subi	r16, 0x74	; 116
    36cc:	1c 4f       	sbci	r17, 0xFC	; 252
    36ce:	f8 01       	movw	r30, r16
    36d0:	84 82       	std	Z+4, r8	; 0x04
    36d2:	95 82       	std	Z+5, r9	; 0x05
    36d4:	a6 82       	std	Z+6, r10	; 0x06
    36d6:	b7 82       	std	Z+7, r11	; 0x07
    36d8:	be 01       	movw	r22, r28
    36da:	dd 0f       	add	r29, r29
    36dc:	88 0b       	sbc	r24, r24
    36de:	99 0b       	sbc	r25, r25
    36e0:	0e 94 f5 28 	call	0x51ea	; 0x51ea <__floatsisf>
    36e4:	f8 01       	movw	r30, r16
    36e6:	60 83       	st	Z, r22
    36e8:	71 83       	std	Z+1, r23	; 0x01
    36ea:	82 83       	std	Z+2, r24	; 0x02
    36ec:	93 83       	std	Z+3, r25	; 0x03
    36ee:	f3 86       	std	Z+11, r15	; 0x0b
    36f0:	e2 86       	std	Z+10, r14	; 0x0a
    36f2:	20 e0       	ldi	r18, 0x00	; 0
    36f4:	30 e0       	ldi	r19, 0x00	; 0
    36f6:	a9 01       	movw	r20, r18
    36f8:	c5 01       	movw	r24, r10
    36fa:	b4 01       	movw	r22, r8
    36fc:	0e 94 ee 28 	call	0x51dc	; 0x51dc <__cmpsf2>
    3700:	81 11       	cpse	r24, r1
    3702:	05 c0       	rjmp	.+10     	; 0x370e <_ZN6Dimmer7setFadeEaiifb.constprop.49+0x1a0>
    3704:	81 e0       	ldi	r24, 0x01	; 1
    3706:	90 e0       	ldi	r25, 0x00	; 0
    3708:	f8 01       	movw	r30, r16
    370a:	91 87       	std	Z+9, r25	; 0x09
    370c:	80 87       	std	Z+8, r24	; 0x08
    370e:	df 91       	pop	r29
    3710:	cf 91       	pop	r28
    3712:	1f 91       	pop	r17
    3714:	0f 91       	pop	r16
    3716:	ff 90       	pop	r15
    3718:	ef 90       	pop	r14
    371a:	df 90       	pop	r13
    371c:	cf 90       	pop	r12
    371e:	bf 90       	pop	r11
    3720:	af 90       	pop	r10
    3722:	9f 90       	pop	r9
    3724:	8f 90       	pop	r8
    3726:	7f 90       	pop	r7
    3728:	6f 90       	pop	r6
    372a:	5f 90       	pop	r5
    372c:	4f 90       	pop	r4
    372e:	08 95       	ret

00003730 <_ZN6String4moveERS_.constprop.40>:
    3730:	cf 93       	push	r28
    3732:	df 93       	push	r29
    3734:	ec 01       	movw	r28, r24
    3736:	80 91 7b 03 	lds	r24, 0x037B	; 0x80037b <Wire+0x35>
    373a:	90 91 7c 03 	lds	r25, 0x037C	; 0x80037c <Wire+0x36>
    373e:	00 97       	sbiw	r24, 0x00	; 0
    3740:	c9 f0       	breq	.+50     	; 0x3774 <_ZN6String4moveERS_.constprop.40+0x44>
    3742:	68 81       	ld	r22, Y
    3744:	79 81       	ldd	r23, Y+1	; 0x01
    3746:	61 15       	cp	r22, r1
    3748:	71 05       	cpc	r23, r1
    374a:	91 f0       	breq	.+36     	; 0x3770 <_ZN6String4moveERS_.constprop.40+0x40>
    374c:	40 91 7d 03 	lds	r20, 0x037D	; 0x80037d <Wire+0x37>
    3750:	50 91 7e 03 	lds	r21, 0x037E	; 0x80037e <Wire+0x38>
    3754:	2c 81       	ldd	r18, Y+4	; 0x04
    3756:	3d 81       	ldd	r19, Y+5	; 0x05
    3758:	42 17       	cp	r20, r18
    375a:	53 07       	cpc	r21, r19
    375c:	48 f0       	brcs	.+18     	; 0x3770 <_ZN6String4moveERS_.constprop.40+0x40>
    375e:	0e 94 3f 2e 	call	0x5c7e	; 0x5c7e <strcpy>
    3762:	8c 81       	ldd	r24, Y+4	; 0x04
    3764:	9d 81       	ldd	r25, Y+5	; 0x05
    3766:	90 93 80 03 	sts	0x0380, r25	; 0x800380 <Wire+0x3a>
    376a:	80 93 7f 03 	sts	0x037F, r24	; 0x80037f <Wire+0x39>
    376e:	18 c0       	rjmp	.+48     	; 0x37a0 <_ZN6String4moveERS_.constprop.40+0x70>
    3770:	0e 94 ca 2c 	call	0x5994	; 0x5994 <free>
    3774:	88 81       	ld	r24, Y
    3776:	99 81       	ldd	r25, Y+1	; 0x01
    3778:	90 93 7c 03 	sts	0x037C, r25	; 0x80037c <Wire+0x36>
    377c:	80 93 7b 03 	sts	0x037B, r24	; 0x80037b <Wire+0x35>
    3780:	8a 81       	ldd	r24, Y+2	; 0x02
    3782:	9b 81       	ldd	r25, Y+3	; 0x03
    3784:	90 93 7e 03 	sts	0x037E, r25	; 0x80037e <Wire+0x38>
    3788:	80 93 7d 03 	sts	0x037D, r24	; 0x80037d <Wire+0x37>
    378c:	8c 81       	ldd	r24, Y+4	; 0x04
    378e:	9d 81       	ldd	r25, Y+5	; 0x05
    3790:	90 93 80 03 	sts	0x0380, r25	; 0x800380 <Wire+0x3a>
    3794:	80 93 7f 03 	sts	0x037F, r24	; 0x80037f <Wire+0x39>
    3798:	19 82       	std	Y+1, r1	; 0x01
    379a:	18 82       	st	Y, r1
    379c:	1b 82       	std	Y+3, r1	; 0x03
    379e:	1a 82       	std	Y+2, r1	; 0x02
    37a0:	1d 82       	std	Y+5, r1	; 0x05
    37a2:	1c 82       	std	Y+4, r1	; 0x04
    37a4:	df 91       	pop	r29
    37a6:	cf 91       	pop	r28
    37a8:	08 95       	ret

000037aa <_ZN6StringC2EPKc.constprop.37>:
    37aa:	cf 93       	push	r28
    37ac:	df 93       	push	r29
    37ae:	ec 01       	movw	r28, r24
    37b0:	19 82       	std	Y+1, r1	; 0x01
    37b2:	18 82       	st	Y, r1
    37b4:	1b 82       	std	Y+3, r1	; 0x03
    37b6:	1a 82       	std	Y+2, r1	; 0x02
    37b8:	1d 82       	std	Y+5, r1	; 0x05
    37ba:	1c 82       	std	Y+4, r1	; 0x04
    37bc:	60 e0       	ldi	r22, 0x00	; 0
    37be:	70 e0       	ldi	r23, 0x00	; 0
    37c0:	0e 94 ef 0e 	call	0x1dde	; 0x1dde <_ZN6String7reserveEj>
    37c4:	81 11       	cpse	r24, r1
    37c6:	05 c0       	rjmp	.+10     	; 0x37d2 <_ZN6StringC2EPKc.constprop.37+0x28>
    37c8:	ce 01       	movw	r24, r28
    37ca:	df 91       	pop	r29
    37cc:	cf 91       	pop	r28
    37ce:	0c 94 4b 0f 	jmp	0x1e96	; 0x1e96 <_ZN6String10invalidateEv>
    37d2:	1d 82       	std	Y+5, r1	; 0x05
    37d4:	1c 82       	std	Y+4, r1	; 0x04
    37d6:	6a ec       	ldi	r22, 0xCA	; 202
    37d8:	71 e0       	ldi	r23, 0x01	; 1
    37da:	88 81       	ld	r24, Y
    37dc:	99 81       	ldd	r25, Y+1	; 0x01
    37de:	df 91       	pop	r29
    37e0:	cf 91       	pop	r28
    37e2:	0c 94 3f 2e 	jmp	0x5c7e	; 0x5c7e <strcpy>

000037e6 <_ZN6Stream9readBytesEPcj.constprop.32>:
    37e6:	8f 92       	push	r8
    37e8:	9f 92       	push	r9
    37ea:	af 92       	push	r10
    37ec:	bf 92       	push	r11
    37ee:	ef 92       	push	r14
    37f0:	ff 92       	push	r15
    37f2:	0f 93       	push	r16
    37f4:	1f 93       	push	r17
    37f6:	cf 93       	push	r28
    37f8:	df 93       	push	r29
    37fa:	8b 01       	movw	r16, r22
    37fc:	7c 01       	movw	r14, r24
    37fe:	c0 e0       	ldi	r28, 0x00	; 0
    3800:	d0 e0       	ldi	r29, 0x00	; 0
    3802:	c0 17       	cp	r28, r16
    3804:	d1 07       	cpc	r29, r17
    3806:	a1 f1       	breq	.+104    	; 0x3870 <_ZN6Stream9readBytesEPcj.constprop.32+0x8a>
    3808:	0e 94 99 0e 	call	0x1d32	; 0x1d32 <millis>
    380c:	60 93 4e 03 	sts	0x034E, r22	; 0x80034e <Wire+0x8>
    3810:	70 93 4f 03 	sts	0x034F, r23	; 0x80034f <Wire+0x9>
    3814:	80 93 50 03 	sts	0x0350, r24	; 0x800350 <Wire+0xa>
    3818:	90 93 51 03 	sts	0x0351, r25	; 0x800351 <Wire+0xb>
    381c:	85 e5       	ldi	r24, 0x55	; 85
    381e:	93 e0       	ldi	r25, 0x03	; 3
    3820:	0e 94 5d 0f 	call	0x1eba	; 0x1eba <_ZN12StreamString4readEv>
    3824:	97 ff       	sbrs	r25, 7
    3826:	1f c0       	rjmp	.+62     	; 0x3866 <_ZN6Stream9readBytesEPcj.constprop.32+0x80>
    3828:	0e 94 99 0e 	call	0x1d32	; 0x1d32 <millis>
    382c:	80 90 4e 03 	lds	r8, 0x034E	; 0x80034e <Wire+0x8>
    3830:	90 90 4f 03 	lds	r9, 0x034F	; 0x80034f <Wire+0x9>
    3834:	a0 90 50 03 	lds	r10, 0x0350	; 0x800350 <Wire+0xa>
    3838:	b0 90 51 03 	lds	r11, 0x0351	; 0x800351 <Wire+0xb>
    383c:	dc 01       	movw	r26, r24
    383e:	cb 01       	movw	r24, r22
    3840:	88 19       	sub	r24, r8
    3842:	99 09       	sbc	r25, r9
    3844:	aa 09       	sbc	r26, r10
    3846:	bb 09       	sbc	r27, r11
    3848:	80 90 4a 03 	lds	r8, 0x034A	; 0x80034a <Wire+0x4>
    384c:	90 90 4b 03 	lds	r9, 0x034B	; 0x80034b <Wire+0x5>
    3850:	a0 90 4c 03 	lds	r10, 0x034C	; 0x80034c <Wire+0x6>
    3854:	b0 90 4d 03 	lds	r11, 0x034D	; 0x80034d <Wire+0x7>
    3858:	88 15       	cp	r24, r8
    385a:	99 05       	cpc	r25, r9
    385c:	aa 05       	cpc	r26, r10
    385e:	bb 05       	cpc	r27, r11
    3860:	e8 f2       	brcs	.-70     	; 0x381c <_ZN6Stream9readBytesEPcj.constprop.32+0x36>
    3862:	8e 01       	movw	r16, r28
    3864:	05 c0       	rjmp	.+10     	; 0x3870 <_ZN6Stream9readBytesEPcj.constprop.32+0x8a>
    3866:	f7 01       	movw	r30, r14
    3868:	81 93       	st	Z+, r24
    386a:	7f 01       	movw	r14, r30
    386c:	21 96       	adiw	r28, 0x01	; 1
    386e:	c9 cf       	rjmp	.-110    	; 0x3802 <_ZN6Stream9readBytesEPcj.constprop.32+0x1c>
    3870:	c8 01       	movw	r24, r16
    3872:	df 91       	pop	r29
    3874:	cf 91       	pop	r28
    3876:	1f 91       	pop	r17
    3878:	0f 91       	pop	r16
    387a:	ff 90       	pop	r15
    387c:	ef 90       	pop	r14
    387e:	bf 90       	pop	r11
    3880:	af 90       	pop	r10
    3882:	9f 90       	pop	r9
    3884:	8f 90       	pop	r8
    3886:	08 95       	ret

00003888 <analogRead.constprop.29>:
    3888:	80 e4       	ldi	r24, 0x40	; 64
    388a:	80 93 7c 00 	sts	0x007C, r24	; 0x80007c <__TEXT_REGION_LENGTH__+0x7e007c>
    388e:	80 91 7a 00 	lds	r24, 0x007A	; 0x80007a <__TEXT_REGION_LENGTH__+0x7e007a>
    3892:	80 64       	ori	r24, 0x40	; 64
    3894:	80 93 7a 00 	sts	0x007A, r24	; 0x80007a <__TEXT_REGION_LENGTH__+0x7e007a>
    3898:	80 91 7a 00 	lds	r24, 0x007A	; 0x80007a <__TEXT_REGION_LENGTH__+0x7e007a>
    389c:	86 fd       	sbrc	r24, 6
    389e:	fc cf       	rjmp	.-8      	; 0x3898 <analogRead.constprop.29+0x10>
    38a0:	80 91 78 00 	lds	r24, 0x0078	; 0x800078 <__TEXT_REGION_LENGTH__+0x7e0078>
    38a4:	20 91 79 00 	lds	r18, 0x0079	; 0x800079 <__TEXT_REGION_LENGTH__+0x7e0079>
    38a8:	90 e0       	ldi	r25, 0x00	; 0
    38aa:	92 2b       	or	r25, r18
    38ac:	08 95       	ret

000038ae <_ZN13SerialTwoWire15endTransmissionEh.constprop.25>:
    38ae:	cf 93       	push	r28
    38b0:	df 93       	push	r29
    38b2:	6c ec       	ldi	r22, 0xCC	; 204
    38b4:	74 e0       	ldi	r23, 0x04	; 4
    38b6:	80 91 81 03 	lds	r24, 0x0381	; 0x800381 <Wire+0x3b>
    38ba:	90 91 82 03 	lds	r25, 0x0382	; 0x800382 <Wire+0x3c>
    38be:	0e 94 b1 11 	call	0x2362	; 0x2362 <_ZN5Print5printEPK19__FlashStringHelper>
    38c2:	80 91 77 03 	lds	r24, 0x0377	; 0x800377 <Wire+0x31>
    38c6:	90 91 78 03 	lds	r25, 0x0378	; 0x800378 <Wire+0x32>
    38ca:	89 2b       	or	r24, r25
    38cc:	21 f1       	breq	.+72     	; 0x3916 <_ZN13SerialTwoWire15endTransmissionEh.constprop.25+0x68>
    38ce:	87 e6       	ldi	r24, 0x67	; 103
    38d0:	93 e0       	ldi	r25, 0x03	; 3
    38d2:	0e 94 5d 0f 	call	0x1eba	; 0x1eba <_ZN12StreamString4readEv>
    38d6:	ec 01       	movw	r28, r24
    38d8:	ac 01       	movw	r20, r24
    38da:	55 27       	eor	r21, r21
    38dc:	84 e0       	ldi	r24, 0x04	; 4
    38de:	55 95       	asr	r21
    38e0:	47 95       	ror	r20
    38e2:	8a 95       	dec	r24
    38e4:	e1 f7       	brne	.-8      	; 0x38de <_ZN13SerialTwoWire15endTransmissionEh.constprop.25+0x30>
    38e6:	05 2e       	mov	r0, r21
    38e8:	00 0c       	add	r0, r0
    38ea:	66 0b       	sbc	r22, r22
    38ec:	77 0b       	sbc	r23, r23
    38ee:	20 e1       	ldi	r18, 0x10	; 16
    38f0:	80 91 81 03 	lds	r24, 0x0381	; 0x800381 <Wire+0x3b>
    38f4:	90 91 82 03 	lds	r25, 0x0382	; 0x800382 <Wire+0x3c>
    38f8:	0e 94 f0 11 	call	0x23e0	; 0x23e0 <_ZN5Print11printNumberEmh>
    38fc:	4c 2f       	mov	r20, r28
    38fe:	4f 70       	andi	r20, 0x0F	; 15
    3900:	50 e0       	ldi	r21, 0x00	; 0
    3902:	60 e0       	ldi	r22, 0x00	; 0
    3904:	70 e0       	ldi	r23, 0x00	; 0
    3906:	20 e1       	ldi	r18, 0x10	; 16
    3908:	80 91 81 03 	lds	r24, 0x0381	; 0x800381 <Wire+0x3b>
    390c:	90 91 82 03 	lds	r25, 0x0382	; 0x800382 <Wire+0x3c>
    3910:	0e 94 f0 11 	call	0x23e0	; 0x23e0 <_ZN5Print11printNumberEmh>
    3914:	d6 cf       	rjmp	.-84     	; 0x38c2 <_ZN13SerialTwoWire15endTransmissionEh.constprop.25+0x14>
    3916:	83 e7       	ldi	r24, 0x73	; 115
    3918:	93 e0       	ldi	r25, 0x03	; 3
    391a:	0e 94 4b 0f 	call	0x1e96	; 0x1e96 <_ZN6String10invalidateEv>
    391e:	80 91 81 03 	lds	r24, 0x0381	; 0x800381 <Wire+0x3b>
    3922:	90 91 82 03 	lds	r25, 0x0382	; 0x800382 <Wire+0x3c>
    3926:	0e 94 39 12 	call	0x2472	; 0x2472 <_ZN5Print7printlnEv>
    392a:	80 e0       	ldi	r24, 0x00	; 0
    392c:	df 91       	pop	r29
    392e:	cf 91       	pop	r28
    3930:	08 95       	ret

00003932 <_ZN13SerialTwoWire5writeEi.constprop.23>:
    3932:	68 2f       	mov	r22, r24
    3934:	83 e7       	ldi	r24, 0x73	; 115
    3936:	93 e0       	ldi	r25, 0x03	; 3
    3938:	0e 94 16 0f 	call	0x1e2c	; 0x1e2c <_ZN6String6concatEc>
    393c:	90 e0       	ldi	r25, 0x00	; 0
    393e:	08 95       	ret

00003940 <_ZN13SerialTwoWire17beginTransmissionEh.constprop.22>:
    3940:	cf 93       	push	r28
    3942:	c8 2f       	mov	r28, r24
    3944:	83 e7       	ldi	r24, 0x73	; 115
    3946:	93 e0       	ldi	r25, 0x03	; 3
    3948:	0e 94 4b 0f 	call	0x1e96	; 0x1e96 <_ZN6String10invalidateEv>
    394c:	6c 2f       	mov	r22, r28
    394e:	87 e6       	ldi	r24, 0x67	; 103
    3950:	93 e0       	ldi	r25, 0x03	; 3
    3952:	cf 91       	pop	r28
    3954:	0c 94 46 0f 	jmp	0x1e8c	; 0x1e8c <_ZN12StreamString5writeEh>

00003958 <main>:
    3958:	cf 93       	push	r28
    395a:	df 93       	push	r29
    395c:	cd b7       	in	r28, 0x3d	; 61
    395e:	de b7       	in	r29, 0x3e	; 62
    3960:	64 97       	sbiw	r28, 0x14	; 20
    3962:	0f b6       	in	r0, 0x3f	; 63
    3964:	f8 94       	cli
    3966:	de bf       	out	0x3e, r29	; 62
    3968:	0f be       	out	0x3f, r0	; 63
    396a:	cd bf       	out	0x3d, r28	; 61
    396c:	78 94       	sei
    396e:	84 b5       	in	r24, 0x24	; 36
    3970:	82 60       	ori	r24, 0x02	; 2
    3972:	84 bd       	out	0x24, r24	; 36
    3974:	84 b5       	in	r24, 0x24	; 36
    3976:	81 60       	ori	r24, 0x01	; 1
    3978:	84 bd       	out	0x24, r24	; 36
    397a:	85 b5       	in	r24, 0x25	; 37
    397c:	82 60       	ori	r24, 0x02	; 2
    397e:	85 bd       	out	0x25, r24	; 37
    3980:	85 b5       	in	r24, 0x25	; 37
    3982:	81 60       	ori	r24, 0x01	; 1
    3984:	85 bd       	out	0x25, r24	; 37
    3986:	80 91 6e 00 	lds	r24, 0x006E	; 0x80006e <__TEXT_REGION_LENGTH__+0x7e006e>
    398a:	81 60       	ori	r24, 0x01	; 1
    398c:	80 93 6e 00 	sts	0x006E, r24	; 0x80006e <__TEXT_REGION_LENGTH__+0x7e006e>
    3990:	10 92 81 00 	sts	0x0081, r1	; 0x800081 <__TEXT_REGION_LENGTH__+0x7e0081>
    3994:	80 91 81 00 	lds	r24, 0x0081	; 0x800081 <__TEXT_REGION_LENGTH__+0x7e0081>
    3998:	82 60       	ori	r24, 0x02	; 2
    399a:	80 93 81 00 	sts	0x0081, r24	; 0x800081 <__TEXT_REGION_LENGTH__+0x7e0081>
    399e:	80 91 81 00 	lds	r24, 0x0081	; 0x800081 <__TEXT_REGION_LENGTH__+0x7e0081>
    39a2:	81 60       	ori	r24, 0x01	; 1
    39a4:	80 93 81 00 	sts	0x0081, r24	; 0x800081 <__TEXT_REGION_LENGTH__+0x7e0081>
    39a8:	80 91 80 00 	lds	r24, 0x0080	; 0x800080 <__TEXT_REGION_LENGTH__+0x7e0080>
    39ac:	81 60       	ori	r24, 0x01	; 1
    39ae:	80 93 80 00 	sts	0x0080, r24	; 0x800080 <__TEXT_REGION_LENGTH__+0x7e0080>
    39b2:	80 91 b1 00 	lds	r24, 0x00B1	; 0x8000b1 <__TEXT_REGION_LENGTH__+0x7e00b1>
    39b6:	84 60       	ori	r24, 0x04	; 4
    39b8:	80 93 b1 00 	sts	0x00B1, r24	; 0x8000b1 <__TEXT_REGION_LENGTH__+0x7e00b1>
    39bc:	80 91 b0 00 	lds	r24, 0x00B0	; 0x8000b0 <__TEXT_REGION_LENGTH__+0x7e00b0>
    39c0:	81 60       	ori	r24, 0x01	; 1
    39c2:	80 93 b0 00 	sts	0x00B0, r24	; 0x8000b0 <__TEXT_REGION_LENGTH__+0x7e00b0>
    39c6:	80 91 7a 00 	lds	r24, 0x007A	; 0x80007a <__TEXT_REGION_LENGTH__+0x7e007a>
    39ca:	84 60       	ori	r24, 0x04	; 4
    39cc:	80 93 7a 00 	sts	0x007A, r24	; 0x80007a <__TEXT_REGION_LENGTH__+0x7e007a>
    39d0:	80 91 7a 00 	lds	r24, 0x007A	; 0x80007a <__TEXT_REGION_LENGTH__+0x7e007a>
    39d4:	82 60       	ori	r24, 0x02	; 2
    39d6:	80 93 7a 00 	sts	0x007A, r24	; 0x80007a <__TEXT_REGION_LENGTH__+0x7e007a>
    39da:	80 91 7a 00 	lds	r24, 0x007A	; 0x80007a <__TEXT_REGION_LENGTH__+0x7e007a>
    39de:	81 60       	ori	r24, 0x01	; 1
    39e0:	80 93 7a 00 	sts	0x007A, r24	; 0x80007a <__TEXT_REGION_LENGTH__+0x7e007a>
    39e4:	80 91 7a 00 	lds	r24, 0x007A	; 0x80007a <__TEXT_REGION_LENGTH__+0x7e007a>
    39e8:	80 68       	ori	r24, 0x80	; 128
    39ea:	80 93 7a 00 	sts	0x007A, r24	; 0x80007a <__TEXT_REGION_LENGTH__+0x7e007a>
    39ee:	10 92 c1 00 	sts	0x00C1, r1	; 0x8000c1 <__TEXT_REGION_LENGTH__+0x7e00c1>
    39f2:	ce 01       	movw	r24, r28
    39f4:	40 96       	adiw	r24, 0x10	; 16
    39f6:	0e 94 8e 05 	call	0xb1c	; 0xb1c <_Z13get_signaturePh>
    39fa:	43 e0       	ldi	r20, 0x03	; 3
    39fc:	50 e0       	ldi	r21, 0x00	; 0
    39fe:	6a ea       	ldi	r22, 0xAA	; 170
    3a00:	72 e0       	ldi	r23, 0x02	; 2
    3a02:	0e 94 b8 27 	call	0x4f70	; 0x4f70 <memcmp_P>
    3a06:	21 e0       	ldi	r18, 0x01	; 1
    3a08:	89 2b       	or	r24, r25
    3a0a:	09 f0       	breq	.+2      	; 0x3a0e <main+0xb6>
    3a0c:	20 e0       	ldi	r18, 0x00	; 0
    3a0e:	20 93 8e 02 	sts	0x028E, r18	; 0x80028e <is_Atmega328PB>
    3a12:	e0 91 b9 02 	lds	r30, 0x02B9	; 0x8002b9 <Serial+0x10>
    3a16:	f0 91 ba 02 	lds	r31, 0x02BA	; 0x8002ba <Serial+0x11>
    3a1a:	82 e0       	ldi	r24, 0x02	; 2
    3a1c:	80 83       	st	Z, r24
    3a1e:	e0 91 b9 02 	lds	r30, 0x02B9	; 0x8002b9 <Serial+0x10>
    3a22:	f0 91 ba 02 	lds	r31, 0x02BA	; 0x8002ba <Serial+0x11>
    3a26:	10 82       	st	Z, r1
    3a28:	e0 91 b5 02 	lds	r30, 0x02B5	; 0x8002b5 <Serial+0xc>
    3a2c:	f0 91 b6 02 	lds	r31, 0x02B6	; 0x8002b6 <Serial+0xd>
    3a30:	10 82       	st	Z, r1
    3a32:	e0 91 b7 02 	lds	r30, 0x02B7	; 0x8002b7 <Serial+0xe>
    3a36:	f0 91 b8 02 	lds	r31, 0x02B8	; 0x8002b8 <Serial+0xf>
    3a3a:	80 e1       	ldi	r24, 0x10	; 16
    3a3c:	80 83       	st	Z, r24
    3a3e:	10 92 c1 02 	sts	0x02C1, r1	; 0x8002c1 <Serial+0x18>
    3a42:	e0 91 bd 02 	lds	r30, 0x02BD	; 0x8002bd <Serial+0x14>
    3a46:	f0 91 be 02 	lds	r31, 0x02BE	; 0x8002be <Serial+0x15>
    3a4a:	86 e0       	ldi	r24, 0x06	; 6
    3a4c:	80 83       	st	Z, r24
    3a4e:	e0 91 bb 02 	lds	r30, 0x02BB	; 0x8002bb <Serial+0x12>
    3a52:	f0 91 bc 02 	lds	r31, 0x02BC	; 0x8002bc <Serial+0x13>
    3a56:	80 81       	ld	r24, Z
    3a58:	80 61       	ori	r24, 0x10	; 16
    3a5a:	80 83       	st	Z, r24
    3a5c:	e0 91 bb 02 	lds	r30, 0x02BB	; 0x8002bb <Serial+0x12>
    3a60:	f0 91 bc 02 	lds	r31, 0x02BC	; 0x8002bc <Serial+0x13>
    3a64:	80 81       	ld	r24, Z
    3a66:	88 60       	ori	r24, 0x08	; 8
    3a68:	80 83       	st	Z, r24
    3a6a:	e0 91 bb 02 	lds	r30, 0x02BB	; 0x8002bb <Serial+0x12>
    3a6e:	f0 91 bc 02 	lds	r31, 0x02BC	; 0x8002bc <Serial+0x13>
    3a72:	80 81       	ld	r24, Z
    3a74:	80 68       	ori	r24, 0x80	; 128
    3a76:	80 83       	st	Z, r24
    3a78:	e0 91 bb 02 	lds	r30, 0x02BB	; 0x8002bb <Serial+0x12>
    3a7c:	f0 91 bc 02 	lds	r31, 0x02BC	; 0x8002bc <Serial+0x13>
    3a80:	80 81       	ld	r24, Z
    3a82:	8f 7d       	andi	r24, 0xDF	; 223
    3a84:	80 83       	st	Z, r24
    3a86:	80 ea       	ldi	r24, 0xA0	; 160
    3a88:	92 e0       	ldi	r25, 0x02	; 2
    3a8a:	0e 94 16 18 	call	0x302c	; 0x302c <_ZN5Print7printlnEPK19__FlashStringHelper.constprop.70>
    3a8e:	89 ea       	ldi	r24, 0xA9	; 169
    3a90:	92 e0       	ldi	r25, 0x02	; 2
    3a92:	0e 94 4c 11 	call	0x2298	; 0x2298 <_ZN14HardwareSerial5flushEv>
    3a96:	60 e0       	ldi	r22, 0x00	; 0
    3a98:	8e e0       	ldi	r24, 0x0E	; 14
    3a9a:	0e 94 fe 0d 	call	0x1bfc	; 0x1bfc <pinMode>
    3a9e:	e1 e1       	ldi	r30, 0x11	; 17
    3aa0:	f4 e0       	ldi	r31, 0x04	; 4
    3aa2:	8b e7       	ldi	r24, 0x7B	; 123
    3aa4:	df 01       	movw	r26, r30
    3aa6:	1d 92       	st	X+, r1
    3aa8:	8a 95       	dec	r24
    3aaa:	e9 f7       	brne	.-6      	; 0x3aa6 <main+0x14e>
    3aac:	8f ef       	ldi	r24, 0xFF	; 255
    3aae:	9f ef       	ldi	r25, 0xFF	; 255
    3ab0:	90 93 12 04 	sts	0x0412, r25	; 0x800412 <register_mem+0x1>
    3ab4:	80 93 11 04 	sts	0x0411, r24	; 0x800411 <register_mem>
    3ab8:	fe 01       	movw	r30, r28
    3aba:	31 96       	adiw	r30, 0x01	; 1
    3abc:	1f 01       	movw	r2, r30
    3abe:	cf 01       	movw	r24, r30
    3ac0:	0e 94 d5 1b 	call	0x37aa	; 0x37aa <_ZN6StringC2EPKc.constprop.37>
    3ac4:	c1 01       	movw	r24, r2
    3ac6:	0e 94 98 1b 	call	0x3730	; 0x3730 <_ZN6String4moveERS_.constprop.40>
    3aca:	c1 01       	movw	r24, r2
    3acc:	0e 94 c6 0f 	call	0x1f8c	; 0x1f8c <_ZN6StringD1Ev>
    3ad0:	10 92 7a 03 	sts	0x037A, r1	; 0x80037a <Wire+0x34>
    3ad4:	10 92 79 03 	sts	0x0379, r1	; 0x800379 <Wire+0x33>
    3ad8:	10 92 52 03 	sts	0x0352, r1	; 0x800352 <Wire+0xc>
    3adc:	81 e6       	ldi	r24, 0x61	; 97
    3ade:	93 e0       	ldi	r25, 0x03	; 3
    3ae0:	0e 94 4b 0f 	call	0x1e96	; 0x1e96 <_ZN6String10invalidateEv>
    3ae4:	83 e7       	ldi	r24, 0x73	; 115
    3ae6:	93 e0       	ldi	r25, 0x03	; 3
    3ae8:	0e 94 4b 0f 	call	0x1e96	; 0x1e96 <_ZN6String10invalidateEv>
    3aec:	87 e1       	ldi	r24, 0x17	; 23
    3aee:	80 93 52 03 	sts	0x0352, r24	; 0x800352 <Wire+0xc>
    3af2:	89 ee       	ldi	r24, 0xE9	; 233
    3af4:	9a e0       	ldi	r25, 0x0A	; 10
    3af6:	90 93 84 03 	sts	0x0384, r25	; 0x800384 <Wire+0x3e>
    3afa:	80 93 83 03 	sts	0x0383, r24	; 0x800383 <Wire+0x3d>
    3afe:	89 ed       	ldi	r24, 0xD9	; 217
    3b00:	92 e0       	ldi	r25, 0x02	; 2
    3b02:	90 93 86 03 	sts	0x0386, r25	; 0x800386 <Wire+0x40>
    3b06:	80 93 85 03 	sts	0x0385, r24	; 0x800385 <Wire+0x3f>
    3b0a:	10 92 8d 02 	sts	0x028D, r1	; 0x80028d <eeprom_position+0x1>
    3b0e:	10 92 8c 02 	sts	0x028C, r1	; 0x80028c <eeprom_position>
    3b12:	00 e0       	ldi	r16, 0x00	; 0
    3b14:	10 e0       	ldi	r17, 0x00	; 0
    3b16:	41 2c       	mov	r4, r1
    3b18:	51 2c       	mov	r5, r1
    3b1a:	32 01       	movw	r6, r4
    3b1c:	0c 3f       	cpi	r16, 0xFC	; 252
    3b1e:	f3 e0       	ldi	r31, 0x03	; 3
    3b20:	1f 07       	cpc	r17, r31
    3b22:	b9 f0       	breq	.+46     	; 0x3b52 <main+0x1fa>
    3b24:	b1 01       	movw	r22, r2
    3b26:	c8 01       	movw	r24, r16
    3b28:	0e 94 95 12 	call	0x252a	; 0x252a <_ZN11EEPROMClass3getImEERT_iS2_.isra.1.lto_priv.100>
    3b2c:	89 81       	ldd	r24, Y+1	; 0x01
    3b2e:	9a 81       	ldd	r25, Y+2	; 0x02
    3b30:	ab 81       	ldd	r26, Y+3	; 0x03
    3b32:	bc 81       	ldd	r27, Y+4	; 0x04
    3b34:	84 15       	cp	r24, r4
    3b36:	95 05       	cpc	r25, r5
    3b38:	a6 05       	cpc	r26, r6
    3b3a:	b7 05       	cpc	r27, r7
    3b3c:	18 f4       	brcc	.+6      	; 0x3b44 <main+0x1ec>
    3b3e:	0e 5d       	subi	r16, 0xDE	; 222
    3b40:	1f 4f       	sbci	r17, 0xFF	; 255
    3b42:	ec cf       	rjmp	.-40     	; 0x3b1c <main+0x1c4>
    3b44:	10 93 8d 02 	sts	0x028D, r17	; 0x80028d <eeprom_position+0x1>
    3b48:	00 93 8c 02 	sts	0x028C, r16	; 0x80028c <eeprom_position>
    3b4c:	2c 01       	movw	r4, r24
    3b4e:	3d 01       	movw	r6, r26
    3b50:	f6 cf       	rjmp	.-20     	; 0x3b3e <main+0x1e6>
    3b52:	00 91 8c 02 	lds	r16, 0x028C	; 0x80028c <eeprom_position>
    3b56:	10 91 8d 02 	lds	r17, 0x028D	; 0x80028d <eeprom_position+0x1>
    3b5a:	6c e8       	ldi	r22, 0x8C	; 140
    3b5c:	74 e0       	ldi	r23, 0x04	; 4
    3b5e:	c8 01       	movw	r24, r16
    3b60:	0e 94 95 12 	call	0x252a	; 0x252a <_ZN11EEPROMClass3getImEERT_iS2_.isra.1.lto_priv.100>
    3b64:	60 e9       	ldi	r22, 0x90	; 144
    3b66:	74 e0       	ldi	r23, 0x04	; 4
    3b68:	c8 01       	movw	r24, r16
    3b6a:	04 96       	adiw	r24, 0x04	; 4
    3b6c:	0e 94 a1 09 	call	0x1342	; 0x1342 <_ZN11EEPROMClass3getIjEERT_iS2_.isra.2.lto_priv.101>
    3b70:	62 e9       	ldi	r22, 0x92	; 146
    3b72:	74 e0       	ldi	r23, 0x04	; 4
    3b74:	c8 01       	movw	r24, r16
    3b76:	06 96       	adiw	r24, 0x06	; 6
    3b78:	0e 94 7b 09 	call	0x12f6	; 0x12f6 <_ZN11EEPROMClass3getIA4_iEERT_iS3_.isra.3.lto_priv.102>
    3b7c:	43 e3       	ldi	r20, 0x33	; 51
    3b7e:	c4 2e       	mov	r12, r20
    3b80:	44 e0       	ldi	r20, 0x04	; 4
    3b82:	d4 2e       	mov	r13, r20
    3b84:	58 01       	movw	r10, r16
    3b86:	22 e2       	ldi	r18, 0x22	; 34
    3b88:	a2 0e       	add	r10, r18
    3b8a:	b1 1c       	adc	r11, r1
    3b8c:	a8 01       	movw	r20, r16
    3b8e:	42 5f       	subi	r20, 0xF2	; 242
    3b90:	5f 4f       	sbci	r21, 0xFF	; 255
    3b92:	7a 01       	movw	r14, r20
    3b94:	c7 01       	movw	r24, r14
    3b96:	0e 94 12 2a 	call	0x5424	; 0x5424 <eeprom_read_byte>
    3b9a:	d6 01       	movw	r26, r12
    3b9c:	8d 93       	st	X+, r24
    3b9e:	6d 01       	movw	r12, r26
    3ba0:	bf ef       	ldi	r27, 0xFF	; 255
    3ba2:	eb 1a       	sub	r14, r27
    3ba4:	fb 0a       	sbc	r15, r27
    3ba6:	ae 14       	cp	r10, r14
    3ba8:	bf 04       	cpc	r11, r15
    3baa:	a1 f7       	brne	.-24     	; 0x3b94 <main+0x23c>
    3bac:	0e 94 08 18 	call	0x3010	; 0x3010 <_ZNK13ConfigStorage3crcEv.constprop.83>
    3bb0:	7c 01       	movw	r14, r24
    3bb2:	ff 92       	push	r15
    3bb4:	8f 93       	push	r24
    3bb6:	80 91 91 04 	lds	r24, 0x0491	; 0x800491 <config+0x5>
    3bba:	8f 93       	push	r24
    3bbc:	80 91 90 04 	lds	r24, 0x0490	; 0x800490 <config+0x4>
    3bc0:	8f 93       	push	r24
    3bc2:	a3 01       	movw	r20, r6
    3bc4:	92 01       	movw	r18, r4
    3bc6:	21 50       	subi	r18, 0x01	; 1
    3bc8:	31 09       	sbc	r19, r1
    3bca:	41 09       	sbc	r20, r1
    3bcc:	51 09       	sbc	r21, r1
    3bce:	ae e1       	ldi	r26, 0x1E	; 30
    3bd0:	b0 e0       	ldi	r27, 0x00	; 0
    3bd2:	0e 94 5a 2a 	call	0x54b4	; 0x54b4 <__muluhisi3>
    3bd6:	4b 01       	movw	r8, r22
    3bd8:	5c 01       	movw	r10, r24
    3bda:	c8 01       	movw	r24, r16
    3bdc:	62 e2       	ldi	r22, 0x22	; 34
    3bde:	70 e0       	ldi	r23, 0x00	; 0
    3be0:	0e 94 74 2a 	call	0x54e8	; 0x54e8 <__udivmodhi4>
    3be4:	d5 01       	movw	r26, r10
    3be6:	c4 01       	movw	r24, r8
    3be8:	86 0f       	add	r24, r22
    3bea:	97 1f       	adc	r25, r23
    3bec:	a1 1d       	adc	r26, r1
    3bee:	b1 1d       	adc	r27, r1
    3bf0:	bf 93       	push	r27
    3bf2:	af 93       	push	r26
    3bf4:	9f 93       	push	r25
    3bf6:	8f 93       	push	r24
    3bf8:	1f 93       	push	r17
    3bfa:	0f 93       	push	r16
    3bfc:	7f 92       	push	r7
    3bfe:	6f 92       	push	r6
    3c00:	5f 92       	push	r5
    3c02:	4f 92       	push	r4
    3c04:	8d e4       	ldi	r24, 0x4D	; 77
    3c06:	92 e0       	ldi	r25, 0x02	; 2
    3c08:	9f 93       	push	r25
    3c0a:	8f 93       	push	r24
    3c0c:	0e 94 a8 05 	call	0xb50	; 0xb50 <_Z15Serial_printf_PPKcz>
    3c10:	0f b6       	in	r0, 0x3f	; 63
    3c12:	f8 94       	cli
    3c14:	de bf       	out	0x3e, r29	; 62
    3c16:	0f be       	out	0x3f, r0	; 63
    3c18:	cd bf       	out	0x3d, r28	; 61
    3c1a:	80 91 90 04 	lds	r24, 0x0490	; 0x800490 <config+0x4>
    3c1e:	90 91 91 04 	lds	r25, 0x0491	; 0x800491 <config+0x5>
    3c22:	e8 16       	cp	r14, r24
    3c24:	f9 06       	cpc	r15, r25
    3c26:	59 f0       	breq	.+22     	; 0x3c3e <main+0x2e6>
    3c28:	87 e3       	ldi	r24, 0x37	; 55
    3c2a:	92 e0       	ldi	r25, 0x02	; 2
    3c2c:	0e 94 16 18 	call	0x302c	; 0x302c <_ZN5Print7printlnEPK19__FlashStringHelper.constprop.70>
    3c30:	0e 94 3e 05 	call	0xa7c	; 0xa7c <_Z12reset_configv>
    3c34:	0e 94 13 05 	call	0xa26	; 0xa26 <_Z11init_eepromv>
    3c38:	81 e0       	ldi	r24, 0x01	; 1
    3c3a:	80 93 8b 02 	sts	0x028B, r24	; 0x80028b <eeprom_crc_error>
    3c3e:	80 e0       	ldi	r24, 0x00	; 0
    3c40:	9c e0       	ldi	r25, 0x0C	; 12
    3c42:	90 93 88 04 	sts	0x0488, r25	; 0x800488 <register_mem+0x77>
    3c46:	80 93 87 04 	sts	0x0487, r24	; 0x800487 <register_mem+0x76>
    3c4a:	f8 94       	cli
    3c4c:	10 92 f9 03 	sts	0x03F9, r1	; 0x8003f9 <dimmer+0x6d>
    3c50:	10 92 f8 03 	sts	0x03F8, r1	; 0x8003f8 <dimmer+0x6c>
    3c54:	10 92 fe 03 	sts	0x03FE, r1	; 0x8003fe <dimmer+0x72>
    3c58:	10 92 ff 03 	sts	0x03FF, r1	; 0x8003ff <dimmer+0x73>
    3c5c:	10 92 00 04 	sts	0x0400, r1	; 0x800400 <dimmer+0x74>
    3c60:	10 92 01 04 	sts	0x0401, r1	; 0x800401 <dimmer+0x75>
    3c64:	10 92 02 04 	sts	0x0402, r1	; 0x800402 <dimmer+0x76>
    3c68:	10 92 0b 04 	sts	0x040B, r1	; 0x80040b <dimmer+0x7f>
    3c6c:	3e e0       	ldi	r19, 0x0E	; 14
    3c6e:	e3 2e       	mov	r14, r19
    3c70:	31 e0       	ldi	r19, 0x01	; 1
    3c72:	f3 2e       	mov	r15, r19
    3c74:	10 e0       	ldi	r17, 0x00	; 0
    3c76:	81 2f       	mov	r24, r17
    3c78:	0e 94 f3 07 	call	0xfe6	; 0xfe6 <_ZN6Dimmer14disableChannelEa.isra.2.lto_priv.95>
    3c7c:	61 e0       	ldi	r22, 0x01	; 1
    3c7e:	d7 01       	movw	r26, r14
    3c80:	8d 91       	ld	r24, X+
    3c82:	7d 01       	movw	r14, r26
    3c84:	0e 94 fe 0d 	call	0x1bfc	; 0x1bfc <pinMode>
    3c88:	1f 5f       	subi	r17, 0xFF	; 255
    3c8a:	14 30       	cpi	r17, 0x04	; 4
    3c8c:	a1 f7       	brne	.-24     	; 0x3c76 <main+0x31e>
    3c8e:	10 92 80 00 	sts	0x0080, r1	; 0x800080 <__TEXT_REGION_LENGTH__+0x7e0080>
    3c92:	82 e0       	ldi	r24, 0x02	; 2
    3c94:	80 93 81 00 	sts	0x0081, r24	; 0x800081 <__TEXT_REGION_LENGTH__+0x7e0081>
    3c98:	10 92 82 00 	sts	0x0082, r1	; 0x800082 <__TEXT_REGION_LENGTH__+0x7e0082>
    3c9c:	60 e0       	ldi	r22, 0x00	; 0
    3c9e:	83 e0       	ldi	r24, 0x03	; 3
    3ca0:	0e 94 fe 0d 	call	0x1bfc	; 0x1bfc <pinMode>
    3ca4:	89 ef       	ldi	r24, 0xF9	; 249
    3ca6:	92 e0       	ldi	r25, 0x02	; 2
    3ca8:	90 93 07 01 	sts	0x0107, r25	; 0x800107 <intFunc.lto_priv.98+0x3>
    3cac:	80 93 06 01 	sts	0x0106, r24	; 0x800106 <intFunc.lto_priv.98+0x2>
    3cb0:	80 91 69 00 	lds	r24, 0x0069	; 0x800069 <__TEXT_REGION_LENGTH__+0x7e0069>
    3cb4:	8c 60       	ori	r24, 0x0C	; 12
    3cb6:	80 93 69 00 	sts	0x0069, r24	; 0x800069 <__TEXT_REGION_LENGTH__+0x7e0069>
    3cba:	e9 9a       	sbi	0x1d, 1	; 29
    3cbc:	86 b3       	in	r24, 0x16	; 22
    3cbe:	87 60       	ori	r24, 0x07	; 7
    3cc0:	86 bb       	out	0x16, r24	; 22
    3cc2:	80 91 6f 00 	lds	r24, 0x006F	; 0x80006f <__TEXT_REGION_LENGTH__+0x7e006f>
    3cc6:	81 60       	ori	r24, 0x01	; 1
    3cc8:	80 93 6f 00 	sts	0x006F, r24	; 0x80006f <__TEXT_REGION_LENGTH__+0x7e006f>
    3ccc:	78 94       	sei
    3cce:	64 e6       	ldi	r22, 0x64	; 100
    3cd0:	70 e0       	ldi	r23, 0x00	; 0
    3cd2:	80 e0       	ldi	r24, 0x00	; 0
    3cd4:	90 e0       	ldi	r25, 0x00	; 0
    3cd6:	0e 94 5f 0e 	call	0x1cbe	; 0x1cbe <delay>
    3cda:	87 e8       	ldi	r24, 0x87	; 135
    3cdc:	92 e0       	ldi	r25, 0x02	; 2
    3cde:	0e 94 16 18 	call	0x302c	; 0x302c <_ZN5Print7printlnEPK19__FlashStringHelper.constprop.70>
    3ce2:	89 ea       	ldi	r24, 0xA9	; 169
    3ce4:	92 e0       	ldi	r25, 0x02	; 2
    3ce6:	0e 94 4c 11 	call	0x2298	; 0x2298 <_ZN14HardwareSerial5flushEv>
    3cea:	f8 94       	cli
    3cec:	80 91 6f 00 	lds	r24, 0x006F	; 0x80006f <__TEXT_REGION_LENGTH__+0x7e006f>
    3cf0:	88 7f       	andi	r24, 0xF8	; 248
    3cf2:	80 93 6f 00 	sts	0x006F, r24	; 0x80006f <__TEXT_REGION_LENGTH__+0x7e006f>
    3cf6:	86 b3       	in	r24, 0x16	; 22
    3cf8:	87 60       	ori	r24, 0x07	; 7
    3cfa:	86 bb       	out	0x16, r24	; 22
    3cfc:	80 91 6f 00 	lds	r24, 0x006F	; 0x80006f <__TEXT_REGION_LENGTH__+0x7e006f>
    3d00:	81 60       	ori	r24, 0x01	; 1
    3d02:	80 93 6f 00 	sts	0x006F, r24	; 0x80006f <__TEXT_REGION_LENGTH__+0x7e006f>
    3d06:	10 92 0b 04 	sts	0x040B, r1	; 0x80040b <dimmer+0x7f>
    3d0a:	10 92 f9 03 	sts	0x03F9, r1	; 0x8003f9 <dimmer+0x6d>
    3d0e:	10 92 f8 03 	sts	0x03F8, r1	; 0x8003f8 <dimmer+0x6c>
    3d12:	10 92 fe 03 	sts	0x03FE, r1	; 0x8003fe <dimmer+0x72>
    3d16:	78 94       	sei
    3d18:	0e 94 99 0e 	call	0x1d32	; 0x1d32 <millis>
    3d1c:	6b 01       	movw	r12, r22
    3d1e:	7c 01       	movw	r14, r24
    3d20:	b0 e1       	ldi	r27, 0x10	; 16
    3d22:	cb 0e       	add	r12, r27
    3d24:	b7 e2       	ldi	r27, 0x27	; 39
    3d26:	db 1e       	adc	r13, r27
    3d28:	e1 1c       	adc	r14, r1
    3d2a:	f1 1c       	adc	r15, r1
    3d2c:	80 91 f8 03 	lds	r24, 0x03F8	; 0x8003f8 <dimmer+0x6c>
    3d30:	90 91 f9 03 	lds	r25, 0x03F9	; 0x8003f9 <dimmer+0x6d>
    3d34:	89 2b       	or	r24, r25
    3d36:	09 f0       	breq	.+2      	; 0x3d3a <main+0x3e2>
    3d38:	73 c2       	rjmp	.+1254   	; 0x4220 <main+0x8c8>
    3d3a:	0e 94 99 0e 	call	0x1d32	; 0x1d32 <millis>
    3d3e:	c6 16       	cp	r12, r22
    3d40:	d7 06       	cpc	r13, r23
    3d42:	e8 06       	cpc	r14, r24
    3d44:	f9 06       	cpc	r15, r25
    3d46:	90 f7       	brcc	.-28     	; 0x3d2c <main+0x3d4>
    3d48:	8a e7       	ldi	r24, 0x7A	; 122
    3d4a:	92 e0       	ldi	r25, 0x02	; 2
    3d4c:	0e 94 16 18 	call	0x302c	; 0x302c <_ZN5Print7printlnEPK19__FlashStringHelper.constprop.70>
    3d50:	89 ea       	ldi	r24, 0xA9	; 169
    3d52:	92 e0       	ldi	r25, 0x02	; 2
    3d54:	0e 94 4c 11 	call	0x2298	; 0x2298 <_ZN14HardwareSerial5flushEv>
    3d58:	f8 94       	cli
    3d5a:	80 ed       	ldi	r24, 0xD0	; 208
    3d5c:	97 e0       	ldi	r25, 0x07	; 7
    3d5e:	90 93 1e 04 	sts	0x041E, r25	; 0x80041e <register_mem+0xd>
    3d62:	80 93 1d 04 	sts	0x041D, r24	; 0x80041d <register_mem+0xc>
    3d66:	10 92 95 03 	sts	0x0395, r1	; 0x800395 <dimmer+0x9>
    3d6a:	10 92 94 03 	sts	0x0394, r1	; 0x800394 <dimmer+0x8>
    3d6e:	0f ef       	ldi	r16, 0xFF	; 255
    3d70:	1f ef       	ldi	r17, 0xFF	; 255
    3d72:	10 93 f1 03 	sts	0x03F1, r17	; 0x8003f1 <dimmer+0x65>
    3d76:	00 93 f0 03 	sts	0x03F0, r16	; 0x8003f0 <dimmer+0x64>
    3d7a:	0e 94 27 18 	call	0x304e	; 0x304e <_ZN6Dimmer18_calculateChannelsEv.constprop.69>
    3d7e:	8c ef       	ldi	r24, 0xFC	; 252
    3d80:	98 e0       	ldi	r25, 0x08	; 8
    3d82:	90 93 20 04 	sts	0x0420, r25	; 0x800420 <register_mem+0xf>
    3d86:	80 93 1f 04 	sts	0x041F, r24	; 0x80041f <register_mem+0xe>
    3d8a:	10 92 a1 03 	sts	0x03A1, r1	; 0x8003a1 <dimmer+0x15>
    3d8e:	10 92 a0 03 	sts	0x03A0, r1	; 0x8003a0 <dimmer+0x14>
    3d92:	10 93 f3 03 	sts	0x03F3, r17	; 0x8003f3 <dimmer+0x67>
    3d96:	00 93 f2 03 	sts	0x03F2, r16	; 0x8003f2 <dimmer+0x66>
    3d9a:	0e 94 27 18 	call	0x304e	; 0x304e <_ZN6Dimmer18_calculateChannelsEv.constprop.69>
    3d9e:	85 e8       	ldi	r24, 0x85	; 133
    3da0:	9c e1       	ldi	r25, 0x1C	; 28
    3da2:	90 93 22 04 	sts	0x0422, r25	; 0x800422 <register_mem+0x11>
    3da6:	80 93 21 04 	sts	0x0421, r24	; 0x800421 <register_mem+0x10>
    3daa:	10 92 ad 03 	sts	0x03AD, r1	; 0x8003ad <dimmer+0x21>
    3dae:	10 92 ac 03 	sts	0x03AC, r1	; 0x8003ac <dimmer+0x20>
    3db2:	10 93 f5 03 	sts	0x03F5, r17	; 0x8003f5 <dimmer+0x69>
    3db6:	00 93 f4 03 	sts	0x03F4, r16	; 0x8003f4 <dimmer+0x68>
    3dba:	0e 94 27 18 	call	0x304e	; 0x304e <_ZN6Dimmer18_calculateChannelsEv.constprop.69>
    3dbe:	8d ef       	ldi	r24, 0xFD	; 253
    3dc0:	98 e0       	ldi	r25, 0x08	; 8
    3dc2:	90 93 24 04 	sts	0x0424, r25	; 0x800424 <register_mem+0x13>
    3dc6:	80 93 23 04 	sts	0x0423, r24	; 0x800423 <register_mem+0x12>
    3dca:	10 92 b9 03 	sts	0x03B9, r1	; 0x8003b9 <dimmer+0x2d>
    3dce:	10 92 b8 03 	sts	0x03B8, r1	; 0x8003b8 <dimmer+0x2c>
    3dd2:	10 93 f7 03 	sts	0x03F7, r17	; 0x8003f7 <dimmer+0x6b>
    3dd6:	00 93 f6 03 	sts	0x03F6, r16	; 0x8003f6 <dimmer+0x6a>
    3dda:	0e 94 27 18 	call	0x304e	; 0x304e <_ZN6Dimmer18_calculateChannelsEv.constprop.69>
    3dde:	78 94       	sei
    3de0:	0e 94 e6 13 	call	0x27cc	; 0x27cc <_Z19display_dimmer_infov>
    3de4:	80 91 97 02 	lds	r24, 0x0297	; 0x800297 <dimmer_scheduled_calls>
    3de8:	80 ff       	sbrs	r24, 0
    3dea:	09 c0       	rjmp	.+18     	; 0x3dfe <main+0x4a6>
    3dec:	8e 7f       	andi	r24, 0xFE	; 254
    3dee:	80 93 97 02 	sts	0x0297, r24	; 0x800297 <dimmer_scheduled_calls>
    3df2:	0e 94 35 13 	call	0x266a	; 0x266a <_Z8read_vccv>
    3df6:	90 93 32 04 	sts	0x0432, r25	; 0x800432 <register_mem+0x21>
    3dfa:	80 93 31 04 	sts	0x0431, r24	; 0x800431 <register_mem+0x20>
    3dfe:	80 91 97 02 	lds	r24, 0x0297	; 0x800297 <dimmer_scheduled_calls>
    3e02:	81 ff       	sbrs	r24, 1
    3e04:	0d c0       	rjmp	.+26     	; 0x3e20 <main+0x4c8>
    3e06:	8d 7f       	andi	r24, 0xFD	; 253
    3e08:	80 93 97 02 	sts	0x0297, r24	; 0x800297 <dimmer_scheduled_calls>
    3e0c:	0e 94 76 13 	call	0x26ec	; 0x26ec <_Z24get_internal_temperaturev>
    3e10:	60 93 2d 04 	sts	0x042D, r22	; 0x80042d <register_mem+0x1c>
    3e14:	70 93 2e 04 	sts	0x042E, r23	; 0x80042e <register_mem+0x1d>
    3e18:	80 93 2f 04 	sts	0x042F, r24	; 0x80042f <register_mem+0x1e>
    3e1c:	90 93 30 04 	sts	0x0430, r25	; 0x800430 <register_mem+0x1f>
    3e20:	80 91 97 02 	lds	r24, 0x0297	; 0x800297 <dimmer_scheduled_calls>
    3e24:	82 ff       	sbrs	r24, 2
    3e26:	0d c0       	rjmp	.+26     	; 0x3e42 <main+0x4ea>
    3e28:	8b 7f       	andi	r24, 0xFB	; 251
    3e2a:	80 93 97 02 	sts	0x0297, r24	; 0x800297 <dimmer_scheduled_calls>
    3e2e:	0e 94 bb 12 	call	0x2576	; 0x2576 <_Z19get_ntc_temperaturev>
    3e32:	60 93 2d 04 	sts	0x042D, r22	; 0x80042d <register_mem+0x1c>
    3e36:	70 93 2e 04 	sts	0x042E, r23	; 0x80042e <register_mem+0x1d>
    3e3a:	80 93 2f 04 	sts	0x042F, r24	; 0x80042f <register_mem+0x1e>
    3e3e:	90 93 30 04 	sts	0x0430, r25	; 0x800430 <register_mem+0x1f>
    3e42:	80 91 97 02 	lds	r24, 0x0297	; 0x800297 <dimmer_scheduled_calls>
    3e46:	84 ff       	sbrs	r24, 4
    3e48:	a1 c0       	rjmp	.+322    	; 0x3f8c <main+0x634>
    3e4a:	0e 94 99 0e 	call	0x1d32	; 0x1d32 <millis>
    3e4e:	00 91 93 02 	lds	r16, 0x0293	; 0x800293 <print_metrics_timeout>
    3e52:	10 91 94 02 	lds	r17, 0x0294	; 0x800294 <print_metrics_timeout+0x1>
    3e56:	20 91 95 02 	lds	r18, 0x0295	; 0x800295 <print_metrics_timeout+0x2>
    3e5a:	30 91 96 02 	lds	r19, 0x0296	; 0x800296 <print_metrics_timeout+0x3>
    3e5e:	06 17       	cp	r16, r22
    3e60:	17 07       	cpc	r17, r23
    3e62:	28 07       	cpc	r18, r24
    3e64:	39 07       	cpc	r19, r25
    3e66:	08 f0       	brcs	.+2      	; 0x3e6a <main+0x512>
    3e68:	91 c0       	rjmp	.+290    	; 0x3f8c <main+0x634>
    3e6a:	0e 94 99 0e 	call	0x1d32	; 0x1d32 <millis>
    3e6e:	dc 01       	movw	r26, r24
    3e70:	cb 01       	movw	r24, r22
    3e72:	88 57       	subi	r24, 0x78	; 120
    3e74:	9c 4e       	sbci	r25, 0xEC	; 236
    3e76:	af 4f       	sbci	r26, 0xFF	; 255
    3e78:	bf 4f       	sbci	r27, 0xFF	; 255
    3e7a:	80 93 93 02 	sts	0x0293, r24	; 0x800293 <print_metrics_timeout>
    3e7e:	90 93 94 02 	sts	0x0294, r25	; 0x800294 <print_metrics_timeout+0x1>
    3e82:	a0 93 95 02 	sts	0x0295, r26	; 0x800295 <print_metrics_timeout+0x2>
    3e86:	b0 93 96 02 	sts	0x0296, r27	; 0x800296 <print_metrics_timeout+0x3>
    3e8a:	62 ee       	ldi	r22, 0xE2	; 226
    3e8c:	72 e0       	ldi	r23, 0x02	; 2
    3e8e:	89 ea       	ldi	r24, 0xA9	; 169
    3e90:	92 e0       	ldi	r25, 0x02	; 2
    3e92:	0e 94 b1 11 	call	0x2362	; 0x2362 <_ZN5Print5printEPK19__FlashStringHelper>
    3e96:	0e 94 bb 12 	call	0x2576	; 0x2576 <_Z19get_ntc_temperaturev>
    3e9a:	9f 93       	push	r25
    3e9c:	8f 93       	push	r24
    3e9e:	7f 93       	push	r23
    3ea0:	6f 93       	push	r22
    3ea2:	a8 ed       	ldi	r26, 0xD8	; 216
    3ea4:	b2 e0       	ldi	r27, 0x02	; 2
    3ea6:	bf 93       	push	r27
    3ea8:	af 93       	push	r26
    3eaa:	0e 94 a8 05 	call	0xb50	; 0xb50 <_Z15Serial_printf_PPKcz>
    3eae:	0e 94 76 13 	call	0x26ec	; 0x26ec <_Z24get_internal_temperaturev>
    3eb2:	9f 93       	push	r25
    3eb4:	8f 93       	push	r24
    3eb6:	7f 93       	push	r23
    3eb8:	6f 93       	push	r22
    3eba:	29 ec       	ldi	r18, 0xC9	; 201
    3ebc:	32 e0       	ldi	r19, 0x02	; 2
    3ebe:	3f 93       	push	r19
    3ec0:	2f 93       	push	r18
    3ec2:	0e 94 a8 05 	call	0xb50	; 0xb50 <_Z15Serial_printf_PPKcz>
    3ec6:	0e 94 35 13 	call	0x266a	; 0x266a <_Z8read_vccv>
    3eca:	9f 93       	push	r25
    3ecc:	8f 93       	push	r24
    3ece:	81 ec       	ldi	r24, 0xC1	; 193
    3ed0:	92 e0       	ldi	r25, 0x02	; 2
    3ed2:	9f 93       	push	r25
    3ed4:	8f 93       	push	r24
    3ed6:	0e 94 a8 05 	call	0xb50	; 0xb50 <_Z15Serial_printf_PPKcz>
    3eda:	00 91 f8 03 	lds	r16, 0x03F8	; 0x8003f8 <dimmer+0x6c>
    3ede:	10 91 f9 03 	lds	r17, 0x03F9	; 0x8003f9 <dimmer+0x6d>
    3ee2:	80 91 f8 03 	lds	r24, 0x03F8	; 0x8003f8 <dimmer+0x6c>
    3ee6:	90 91 f9 03 	lds	r25, 0x03F9	; 0x8003f9 <dimmer+0x6d>
    3eea:	0f b6       	in	r0, 0x3f	; 63
    3eec:	f8 94       	cli
    3eee:	de bf       	out	0x3e, r29	; 62
    3ef0:	0f be       	out	0x3f, r0	; 63
    3ef2:	cd bf       	out	0x3d, r28	; 61
    3ef4:	89 2b       	or	r24, r25
    3ef6:	09 f4       	brne	.+2      	; 0x3efa <main+0x5a2>
    3ef8:	9b c1       	rjmp	.+822    	; 0x4230 <main+0x8d8>
    3efa:	60 91 f8 03 	lds	r22, 0x03F8	; 0x8003f8 <dimmer+0x6c>
    3efe:	70 91 f9 03 	lds	r23, 0x03F9	; 0x8003f9 <dimmer+0x6d>
    3f02:	80 e0       	ldi	r24, 0x00	; 0
    3f04:	90 e0       	ldi	r25, 0x00	; 0
    3f06:	0e 94 f3 28 	call	0x51e6	; 0x51e6 <__floatunsisf>
    3f0a:	9b 01       	movw	r18, r22
    3f0c:	ac 01       	movw	r20, r24
    3f0e:	60 e0       	ldi	r22, 0x00	; 0
    3f10:	74 e2       	ldi	r23, 0x24	; 36
    3f12:	84 e7       	ldi	r24, 0x74	; 116
    3f14:	99 e4       	ldi	r25, 0x49	; 73
    3f16:	0e 94 fb 2a 	call	0x55f6	; 0x55f6 <__divsf3>
    3f1a:	1f 93       	push	r17
    3f1c:	0f 93       	push	r16
    3f1e:	9f 93       	push	r25
    3f20:	8f 93       	push	r24
    3f22:	7f 93       	push	r23
    3f24:	6f 93       	push	r22
    3f26:	e3 eb       	ldi	r30, 0xB3	; 179
    3f28:	f2 e0       	ldi	r31, 0x02	; 2
    3f2a:	ff 93       	push	r31
    3f2c:	ef 93       	push	r30
    3f2e:	0e 94 a8 05 	call	0xb50	; 0xb50 <_Z15Serial_printf_PPKcz>
    3f32:	6e ea       	ldi	r22, 0xAE	; 174
    3f34:	72 e0       	ldi	r23, 0x02	; 2
    3f36:	89 ea       	ldi	r24, 0xA9	; 169
    3f38:	92 e0       	ldi	r25, 0x02	; 2
    3f3a:	0e 94 b1 11 	call	0x2362	; 0x2362 <_ZN5Print5printEPK19__FlashStringHelper>
    3f3e:	0d e1       	ldi	r16, 0x1D	; 29
    3f40:	14 e0       	ldi	r17, 0x04	; 4
    3f42:	0f b6       	in	r0, 0x3f	; 63
    3f44:	f8 94       	cli
    3f46:	de bf       	out	0x3e, r29	; 62
    3f48:	0f be       	out	0x3f, r0	; 63
    3f4a:	cd bf       	out	0x3d, r28	; 61
    3f4c:	f1 2c       	mov	r15, r1
    3f4e:	d8 01       	movw	r26, r16
    3f50:	4d 91       	ld	r20, X+
    3f52:	5d 91       	ld	r21, X+
    3f54:	8d 01       	movw	r16, r26
    3f56:	60 e0       	ldi	r22, 0x00	; 0
    3f58:	70 e0       	ldi	r23, 0x00	; 0
    3f5a:	2a e0       	ldi	r18, 0x0A	; 10
    3f5c:	89 ea       	ldi	r24, 0xA9	; 169
    3f5e:	92 e0       	ldi	r25, 0x02	; 2
    3f60:	0e 94 f0 11 	call	0x23e0	; 0x23e0 <_ZN5Print11printNumberEmh>
    3f64:	b3 e0       	ldi	r27, 0x03	; 3
    3f66:	fb 16       	cp	r15, r27
    3f68:	29 f0       	breq	.+10     	; 0x3f74 <main+0x61c>
    3f6a:	6c e2       	ldi	r22, 0x2C	; 44
    3f6c:	89 ea       	ldi	r24, 0xA9	; 169
    3f6e:	92 e0       	ldi	r25, 0x02	; 2
    3f70:	0e 94 aa 11 	call	0x2354	; 0x2354 <_ZN5Print5printEc>
    3f74:	f3 94       	inc	r15
    3f76:	e4 e0       	ldi	r30, 0x04	; 4
    3f78:	fe 12       	cpse	r15, r30
    3f7a:	e9 cf       	rjmp	.-46     	; 0x3f4e <main+0x5f6>
    3f7c:	89 ea       	ldi	r24, 0xA9	; 169
    3f7e:	92 e0       	ldi	r25, 0x02	; 2
    3f80:	0e 94 39 12 	call	0x2472	; 0x2472 <_ZN5Print7printlnEv>
    3f84:	89 ea       	ldi	r24, 0xA9	; 169
    3f86:	92 e0       	ldi	r25, 0x02	; 2
    3f88:	0e 94 4c 11 	call	0x2298	; 0x2298 <_ZN14HardwareSerial5flushEv>
    3f8c:	0e 94 99 0e 	call	0x1d32	; 0x1d32 <millis>
    3f90:	00 91 9c 02 	lds	r16, 0x029C	; 0x80029c <next_fading_event_check>
    3f94:	10 91 9d 02 	lds	r17, 0x029D	; 0x80029d <next_fading_event_check+0x1>
    3f98:	20 91 9e 02 	lds	r18, 0x029E	; 0x80029e <next_fading_event_check+0x2>
    3f9c:	30 91 9f 02 	lds	r19, 0x029F	; 0x80029f <next_fading_event_check+0x3>
    3fa0:	06 17       	cp	r16, r22
    3fa2:	17 07       	cpc	r17, r23
    3fa4:	28 07       	cpc	r18, r24
    3fa6:	39 07       	cpc	r19, r25
    3fa8:	08 f0       	brcs	.+2      	; 0x3fac <main+0x654>
    3faa:	45 c0       	rjmp	.+138    	; 0x4036 <main+0x6de>
    3fac:	80 e0       	ldi	r24, 0x00	; 0
    3fae:	90 e0       	ldi	r25, 0x00	; 0
    3fb0:	81 01       	movw	r16, r2
    3fb2:	f8 94       	cli
    3fb4:	fc 01       	movw	r30, r24
    3fb6:	ee 0f       	add	r30, r30
    3fb8:	ff 1f       	adc	r31, r31
    3fba:	e0 51       	subi	r30, 0x10	; 16
    3fbc:	fc 4f       	sbci	r31, 0xFC	; 252
    3fbe:	20 81       	ld	r18, Z
    3fc0:	31 81       	ldd	r19, Z+1	; 0x01
    3fc2:	2f 3f       	cpi	r18, 0xFF	; 255
    3fc4:	3f 4f       	sbci	r19, 0xFF	; 255
    3fc6:	71 f0       	breq	.+28     	; 0x3fe4 <main+0x68c>
    3fc8:	20 81       	ld	r18, Z
    3fca:	31 81       	ldd	r19, Z+1	; 0x01
    3fcc:	af ef       	ldi	r26, 0xFF	; 255
    3fce:	bf ef       	ldi	r27, 0xFF	; 255
    3fd0:	b1 83       	std	Z+1, r27	; 0x01
    3fd2:	a0 83       	st	Z, r26
    3fd4:	78 94       	sei
    3fd6:	f8 01       	movw	r30, r16
    3fd8:	80 83       	st	Z, r24
    3fda:	32 83       	std	Z+2, r19	; 0x02
    3fdc:	21 83       	std	Z+1, r18	; 0x01
    3fde:	0d 5f       	subi	r16, 0xFD	; 253
    3fe0:	1f 4f       	sbci	r17, 0xFF	; 255
    3fe2:	01 c0       	rjmp	.+2      	; 0x3fe6 <main+0x68e>
    3fe4:	78 94       	sei
    3fe6:	01 96       	adiw	r24, 0x01	; 1
    3fe8:	84 30       	cpi	r24, 0x04	; 4
    3fea:	91 05       	cpc	r25, r1
    3fec:	11 f7       	brne	.-60     	; 0x3fb2 <main+0x65a>
    3fee:	20 16       	cp	r2, r16
    3ff0:	31 06       	cpc	r3, r17
    3ff2:	89 f0       	breq	.+34     	; 0x4016 <main+0x6be>
    3ff4:	88 e1       	ldi	r24, 0x18	; 24
    3ff6:	0e 94 a0 1c 	call	0x3940	; 0x3940 <_ZN13SerialTwoWire17beginTransmissionEh.constprop.22>
    3ffa:	82 ef       	ldi	r24, 0xF2	; 242
    3ffc:	90 e0       	ldi	r25, 0x00	; 0
    3ffe:	0e 94 99 1c 	call	0x3932	; 0x3932 <_ZN13SerialTwoWire5writeEi.constprop.23>
    4002:	a8 01       	movw	r20, r16
    4004:	42 19       	sub	r20, r2
    4006:	53 09       	sbc	r21, r3
    4008:	b1 01       	movw	r22, r2
    400a:	86 e4       	ldi	r24, 0x46	; 70
    400c:	93 e0       	ldi	r25, 0x03	; 3
    400e:	0e 94 7b 11 	call	0x22f6	; 0x22f6 <_ZN13SerialTwoWire5writeEPKhj>
    4012:	0e 94 57 1c 	call	0x38ae	; 0x38ae <_ZN13SerialTwoWire15endTransmissionEh.constprop.25>
    4016:	0e 94 99 0e 	call	0x1d32	; 0x1d32 <millis>
    401a:	dc 01       	movw	r26, r24
    401c:	cb 01       	movw	r24, r22
    401e:	8c 59       	subi	r24, 0x9C	; 156
    4020:	9f 4f       	sbci	r25, 0xFF	; 255
    4022:	af 4f       	sbci	r26, 0xFF	; 255
    4024:	bf 4f       	sbci	r27, 0xFF	; 255
    4026:	80 93 9c 02 	sts	0x029C, r24	; 0x80029c <next_fading_event_check>
    402a:	90 93 9d 02 	sts	0x029D, r25	; 0x80029d <next_fading_event_check+0x1>
    402e:	a0 93 9e 02 	sts	0x029E, r26	; 0x80029e <next_fading_event_check+0x2>
    4032:	b0 93 9f 02 	sts	0x029F, r27	; 0x80029f <next_fading_event_check+0x3>
    4036:	80 91 97 02 	lds	r24, 0x0297	; 0x800297 <dimmer_scheduled_calls>
    403a:	83 ff       	sbrs	r24, 3
    403c:	10 c0       	rjmp	.+32     	; 0x405e <main+0x706>
    403e:	0e 94 99 0e 	call	0x1d32	; 0x1d32 <millis>
    4042:	00 91 00 01 	lds	r16, 0x0100	; 0x800100 <__data_start>
    4046:	10 91 01 01 	lds	r17, 0x0101	; 0x800101 <__data_start+0x1>
    404a:	20 91 02 01 	lds	r18, 0x0102	; 0x800102 <__data_start+0x2>
    404e:	30 91 03 01 	lds	r19, 0x0103	; 0x800103 <__data_start+0x3>
    4052:	06 17       	cp	r16, r22
    4054:	17 07       	cpc	r17, r23
    4056:	28 07       	cpc	r18, r24
    4058:	39 07       	cpc	r19, r25
    405a:	08 f4       	brcc	.+2      	; 0x405e <main+0x706>
    405c:	ee c0       	rjmp	.+476    	; 0x423a <main+0x8e2>
    405e:	0e 94 99 0e 	call	0x1d32	; 0x1d32 <millis>
    4062:	00 91 8f 02 	lds	r16, 0x028F	; 0x80028f <next_temp_check>
    4066:	10 91 90 02 	lds	r17, 0x0290	; 0x800290 <next_temp_check+0x1>
    406a:	20 91 91 02 	lds	r18, 0x0291	; 0x800291 <next_temp_check+0x2>
    406e:	30 91 92 02 	lds	r19, 0x0292	; 0x800292 <next_temp_check+0x3>
    4072:	06 17       	cp	r16, r22
    4074:	17 07       	cpc	r17, r23
    4076:	28 07       	cpc	r18, r24
    4078:	39 07       	cpc	r19, r25
    407a:	08 f0       	brcs	.+2      	; 0x407e <main+0x726>
    407c:	ce c0       	rjmp	.+412    	; 0x421a <main+0x8c2>
    407e:	0e 94 bb 12 	call	0x2576	; 0x2576 <_Z19get_ntc_temperaturev>
    4082:	2b 01       	movw	r4, r22
    4084:	3c 01       	movw	r6, r24
    4086:	0e 94 6d 2b 	call	0x56da	; 0x56da <__fixsfsi>
    408a:	4b 01       	movw	r8, r22
    408c:	5c 01       	movw	r10, r24
    408e:	0e 94 76 13 	call	0x26ec	; 0x26ec <_Z24get_internal_temperaturev>
    4092:	6b 01       	movw	r12, r22
    4094:	7c 01       	movw	r14, r24
    4096:	0e 94 6d 2b 	call	0x56da	; 0x56da <__fixsfsi>
    409a:	7c 8b       	std	Y+20, r23	; 0x14
    409c:	6b 8b       	std	Y+19, r22	; 0x13
    409e:	68 15       	cp	r22, r8
    40a0:	79 05       	cpc	r23, r9
    40a2:	14 f4       	brge	.+4      	; 0x40a8 <main+0x750>
    40a4:	9c 8a       	std	Y+20, r9	; 0x14
    40a6:	8b 8a       	std	Y+19, r8	; 0x13
    40a8:	0e 94 99 0e 	call	0x1d32	; 0x1d32 <millis>
    40ac:	4b 01       	movw	r8, r22
    40ae:	5c 01       	movw	r10, r24
    40b0:	20 91 39 04 	lds	r18, 0x0439	; 0x800439 <register_mem+0x28>
    40b4:	30 e0       	ldi	r19, 0x00	; 0
    40b6:	a8 ee       	ldi	r26, 0xE8	; 232
    40b8:	b3 e0       	ldi	r27, 0x03	; 3
    40ba:	0e 94 65 2a 	call	0x54ca	; 0x54ca <__umulhisi3>
    40be:	86 0e       	add	r8, r22
    40c0:	97 1e       	adc	r9, r23
    40c2:	a8 1e       	adc	r10, r24
    40c4:	b9 1e       	adc	r11, r25
    40c6:	80 92 8f 02 	sts	0x028F, r8	; 0x80028f <next_temp_check>
    40ca:	90 92 90 02 	sts	0x0290, r9	; 0x800290 <next_temp_check+0x1>
    40ce:	a0 92 91 02 	sts	0x0291, r10	; 0x800291 <next_temp_check+0x2>
    40d2:	b0 92 92 02 	sts	0x0292, r11	; 0x800292 <next_temp_check+0x3>
    40d6:	80 91 34 04 	lds	r24, 0x0434	; 0x800434 <register_mem+0x23>
    40da:	88 23       	and	r24, r24
    40dc:	b1 f1       	breq	.+108    	; 0x414a <main+0x7f2>
    40de:	90 e0       	ldi	r25, 0x00	; 0
    40e0:	4b 89       	ldd	r20, Y+19	; 0x13
    40e2:	5c 89       	ldd	r21, Y+20	; 0x14
    40e4:	84 17       	cp	r24, r20
    40e6:	95 07       	cpc	r25, r21
    40e8:	84 f5       	brge	.+96     	; 0x414a <main+0x7f2>
    40ea:	b1 2c       	mov	r11, r1
    40ec:	00 e0       	ldi	r16, 0x00	; 0
    40ee:	10 e0       	ldi	r17, 0x00	; 0
    40f0:	20 e2       	ldi	r18, 0x20	; 32
    40f2:	31 e4       	ldi	r19, 0x41	; 65
    40f4:	40 e0       	ldi	r20, 0x00	; 0
    40f6:	50 e0       	ldi	r21, 0x00	; 0
    40f8:	6f ef       	ldi	r22, 0xFF	; 255
    40fa:	7f ef       	ldi	r23, 0xFF	; 255
    40fc:	8b 2d       	mov	r24, r11
    40fe:	0e 94 b7 1a 	call	0x356e	; 0x356e <_ZN6Dimmer7setFadeEaiifb.constprop.49>
    4102:	b3 94       	inc	r11
    4104:	54 e0       	ldi	r21, 0x04	; 4
    4106:	b5 12       	cpse	r11, r21
    4108:	f1 cf       	rjmp	.-30     	; 0x40ec <main+0x794>
    410a:	80 91 33 04 	lds	r24, 0x0433	; 0x800433 <register_mem+0x22>
    410e:	84 60       	ori	r24, 0x04	; 4
    4110:	80 93 33 04 	sts	0x0433, r24	; 0x800433 <register_mem+0x22>
    4114:	80 91 8a 04 	lds	r24, 0x048A	; 0x80048a <register_mem+0x79>
    4118:	8f 5f       	subi	r24, 0xFF	; 255
    411a:	80 93 8a 04 	sts	0x048A, r24	; 0x80048a <register_mem+0x79>
    411e:	0e 94 3d 16 	call	0x2c7a	; 0x2c7a <_Z12write_configv>
    4122:	88 e1       	ldi	r24, 0x18	; 24
    4124:	0e 94 a0 1c 	call	0x3940	; 0x3940 <_ZN13SerialTwoWire17beginTransmissionEh.constprop.22>
    4128:	81 ef       	ldi	r24, 0xF1	; 241
    412a:	90 e0       	ldi	r25, 0x00	; 0
    412c:	0e 94 99 1c 	call	0x3932	; 0x3932 <_ZN13SerialTwoWire5writeEi.constprop.23>
    4130:	6b 89       	ldd	r22, Y+19	; 0x13
    4132:	86 e4       	ldi	r24, 0x46	; 70
    4134:	93 e0       	ldi	r25, 0x03	; 3
    4136:	0e 94 a5 11 	call	0x234a	; 0x234a <_ZN13SerialTwoWire5writeEh>
    413a:	60 91 34 04 	lds	r22, 0x0434	; 0x800434 <register_mem+0x23>
    413e:	86 e4       	ldi	r24, 0x46	; 70
    4140:	93 e0       	ldi	r25, 0x03	; 3
    4142:	0e 94 a5 11 	call	0x234a	; 0x234a <_ZN13SerialTwoWire5writeEh>
    4146:	0e 94 57 1c 	call	0x38ae	; 0x38ae <_ZN13SerialTwoWire15endTransmissionEh.constprop.25>
    414a:	80 91 33 04 	lds	r24, 0x0433	; 0x800433 <register_mem+0x22>
    414e:	81 ff       	sbrs	r24, 1
    4150:	64 c0       	rjmp	.+200    	; 0x421a <main+0x8c2>
    4152:	0e 94 99 0e 	call	0x1d32	; 0x1d32 <millis>
    4156:	00 91 98 02 	lds	r16, 0x0298	; 0x800298 <next_event_metrics_event>
    415a:	10 91 99 02 	lds	r17, 0x0299	; 0x800299 <next_event_metrics_event+0x1>
    415e:	20 91 9a 02 	lds	r18, 0x029A	; 0x80029a <next_event_metrics_event+0x2>
    4162:	30 91 9b 02 	lds	r19, 0x029B	; 0x80029b <next_event_metrics_event+0x3>
    4166:	06 17       	cp	r16, r22
    4168:	17 07       	cpc	r17, r23
    416a:	28 07       	cpc	r18, r24
    416c:	39 07       	cpc	r19, r25
    416e:	08 f0       	brcs	.+2      	; 0x4172 <main+0x81a>
    4170:	54 c0       	rjmp	.+168    	; 0x421a <main+0x8c2>
    4172:	8b 89       	ldd	r24, Y+19	; 0x13
    4174:	89 83       	std	Y+1, r24	; 0x01
    4176:	0e 94 35 13 	call	0x266a	; 0x266a <_Z8read_vccv>
    417a:	9b 83       	std	Y+3, r25	; 0x03
    417c:	8a 83       	std	Y+2, r24	; 0x02
    417e:	80 91 f8 03 	lds	r24, 0x03F8	; 0x8003f8 <dimmer+0x6c>
    4182:	90 91 f9 03 	lds	r25, 0x03F9	; 0x8003f9 <dimmer+0x6d>
    4186:	89 2b       	or	r24, r25
    4188:	89 f0       	breq	.+34     	; 0x41ac <main+0x854>
    418a:	60 91 f8 03 	lds	r22, 0x03F8	; 0x8003f8 <dimmer+0x6c>
    418e:	70 91 f9 03 	lds	r23, 0x03F9	; 0x8003f9 <dimmer+0x6d>
    4192:	80 e0       	ldi	r24, 0x00	; 0
    4194:	90 e0       	ldi	r25, 0x00	; 0
    4196:	0e 94 f3 28 	call	0x51e6	; 0x51e6 <__floatunsisf>
    419a:	9b 01       	movw	r18, r22
    419c:	ac 01       	movw	r20, r24
    419e:	60 e0       	ldi	r22, 0x00	; 0
    41a0:	74 e2       	ldi	r23, 0x24	; 36
    41a2:	84 e7       	ldi	r24, 0x74	; 116
    41a4:	99 e4       	ldi	r25, 0x49	; 73
    41a6:	0e 94 fb 2a 	call	0x55f6	; 0x55f6 <__divsf3>
    41aa:	04 c0       	rjmp	.+8      	; 0x41b4 <main+0x85c>
    41ac:	60 e0       	ldi	r22, 0x00	; 0
    41ae:	70 e0       	ldi	r23, 0x00	; 0
    41b0:	80 ec       	ldi	r24, 0xC0	; 192
    41b2:	9f e7       	ldi	r25, 0x7F	; 127
    41b4:	6c 83       	std	Y+4, r22	; 0x04
    41b6:	7d 83       	std	Y+5, r23	; 0x05
    41b8:	8e 83       	std	Y+6, r24	; 0x06
    41ba:	9f 83       	std	Y+7, r25	; 0x07
    41bc:	48 86       	std	Y+8, r4	; 0x08
    41be:	59 86       	std	Y+9, r5	; 0x09
    41c0:	6a 86       	std	Y+10, r6	; 0x0a
    41c2:	7b 86       	std	Y+11, r7	; 0x0b
    41c4:	cc 86       	std	Y+12, r12	; 0x0c
    41c6:	dd 86       	std	Y+13, r13	; 0x0d
    41c8:	ee 86       	std	Y+14, r14	; 0x0e
    41ca:	ff 86       	std	Y+15, r15	; 0x0f
    41cc:	0e 94 99 0e 	call	0x1d32	; 0x1d32 <millis>
    41d0:	6b 01       	movw	r12, r22
    41d2:	7c 01       	movw	r14, r24
    41d4:	20 91 46 04 	lds	r18, 0x0446	; 0x800446 <register_mem+0x35>
    41d8:	30 e0       	ldi	r19, 0x00	; 0
    41da:	a8 ee       	ldi	r26, 0xE8	; 232
    41dc:	b3 e0       	ldi	r27, 0x03	; 3
    41de:	0e 94 65 2a 	call	0x54ca	; 0x54ca <__umulhisi3>
    41e2:	c6 0e       	add	r12, r22
    41e4:	d7 1e       	adc	r13, r23
    41e6:	e8 1e       	adc	r14, r24
    41e8:	f9 1e       	adc	r15, r25
    41ea:	c0 92 98 02 	sts	0x0298, r12	; 0x800298 <next_event_metrics_event>
    41ee:	d0 92 99 02 	sts	0x0299, r13	; 0x800299 <next_event_metrics_event+0x1>
    41f2:	e0 92 9a 02 	sts	0x029A, r14	; 0x80029a <next_event_metrics_event+0x2>
    41f6:	f0 92 9b 02 	sts	0x029B, r15	; 0x80029b <next_event_metrics_event+0x3>
    41fa:	88 e1       	ldi	r24, 0x18	; 24
    41fc:	0e 94 a0 1c 	call	0x3940	; 0x3940 <_ZN13SerialTwoWire17beginTransmissionEh.constprop.22>
    4200:	80 ef       	ldi	r24, 0xF0	; 240
    4202:	90 e0       	ldi	r25, 0x00	; 0
    4204:	0e 94 99 1c 	call	0x3932	; 0x3932 <_ZN13SerialTwoWire5writeEi.constprop.23>
    4208:	4f e0       	ldi	r20, 0x0F	; 15
    420a:	50 e0       	ldi	r21, 0x00	; 0
    420c:	b1 01       	movw	r22, r2
    420e:	86 e4       	ldi	r24, 0x46	; 70
    4210:	93 e0       	ldi	r25, 0x03	; 3
    4212:	0e 94 7b 11 	call	0x22f6	; 0x22f6 <_ZN13SerialTwoWire5writeEPKhj>
    4216:	0e 94 57 1c 	call	0x38ae	; 0x38ae <_ZN13SerialTwoWire15endTransmissionEh.constprop.25>
    421a:	0e 94 89 17 	call	0x2f12	; 0x2f12 <_Z14serialEventRunv>
    421e:	e2 cd       	rjmp	.-1084   	; 0x3de4 <main+0x48c>
    4220:	f8 94       	cli
    4222:	81 e0       	ldi	r24, 0x01	; 1
    4224:	80 93 0b 04 	sts	0x040B, r24	; 0x80040b <dimmer+0x7f>
    4228:	10 92 0c 04 	sts	0x040C, r1	; 0x80040c <dimmer+0x80>
    422c:	78 94       	sei
    422e:	94 cd       	rjmp	.-1240   	; 0x3d58 <main+0x400>
    4230:	60 e0       	ldi	r22, 0x00	; 0
    4232:	70 e0       	ldi	r23, 0x00	; 0
    4234:	80 ec       	ldi	r24, 0xC0	; 192
    4236:	9f e7       	ldi	r25, 0x7F	; 127
    4238:	70 ce       	rjmp	.-800    	; 0x3f1a <main+0x5c2>
    423a:	80 e0       	ldi	r24, 0x00	; 0
    423c:	0e 94 b5 09 	call	0x136a	; 0x136a <_Z13_write_configb>
    4240:	0e cf       	rjmp	.-484    	; 0x405e <main+0x706>

00004242 <_GLOBAL__sub_D_Wire>:
    4242:	0f 93       	push	r16
    4244:	1f 93       	push	r17
    4246:	cf 93       	push	r28
    4248:	df 93       	push	r29
    424a:	c6 e4       	ldi	r28, 0x46	; 70
    424c:	d3 e0       	ldi	r29, 0x03	; 3
    424e:	8c e4       	ldi	r24, 0x4C	; 76
    4250:	91 e0       	ldi	r25, 0x01	; 1
    4252:	99 83       	std	Y+1, r25	; 0x01
    4254:	88 83       	st	Y, r24
    4256:	8b e7       	ldi	r24, 0x7B	; 123
    4258:	93 e0       	ldi	r25, 0x03	; 3
    425a:	0e 94 c6 0f 	call	0x1f8c	; 0x1f8c <_ZN6StringD1Ev>
    425e:	08 e2       	ldi	r16, 0x28	; 40
    4260:	11 e0       	ldi	r17, 0x01	; 1
    4262:	1a a3       	std	Y+34, r17	; 0x22
    4264:	09 a3       	std	Y+33, r16	; 0x21
    4266:	83 e7       	ldi	r24, 0x73	; 115
    4268:	93 e0       	ldi	r25, 0x03	; 3
    426a:	0e 94 c6 0f 	call	0x1f8c	; 0x1f8c <_ZN6StringD1Ev>
    426e:	18 8b       	std	Y+16, r17	; 0x10
    4270:	0f 87       	std	Y+15, r16	; 0x0f
    4272:	81 e6       	ldi	r24, 0x61	; 97
    4274:	93 e0       	ldi	r25, 0x03	; 3
    4276:	df 91       	pop	r29
    4278:	cf 91       	pop	r28
    427a:	1f 91       	pop	r17
    427c:	0f 91       	pop	r16
    427e:	0c 94 c6 0f 	jmp	0x1f8c	; 0x1f8c <_ZN6StringD1Ev>

00004282 <_GLOBAL__I_65535_0_config_storage.cpp.o.3712>:
    4282:	8f 92       	push	r8
    4284:	9f 92       	push	r9
    4286:	af 92       	push	r10
    4288:	bf 92       	push	r11
    428a:	cf 92       	push	r12
    428c:	df 92       	push	r13
    428e:	ef 92       	push	r14
    4290:	ff 92       	push	r15
    4292:	0f 93       	push	r16
    4294:	1f 93       	push	r17
    4296:	cf 93       	push	r28
    4298:	df 93       	push	r29
    429a:	09 ea       	ldi	r16, 0xA9	; 169
    429c:	12 e0       	ldi	r17, 0x02	; 2
    429e:	d8 01       	movw	r26, r16
    42a0:	13 96       	adiw	r26, 0x03	; 3
    42a2:	1c 92       	st	X, r1
    42a4:	1e 92       	st	-X, r1
    42a6:	12 97       	sbiw	r26, 0x02	; 2
    42a8:	88 ee       	ldi	r24, 0xE8	; 232
    42aa:	88 2e       	mov	r8, r24
    42ac:	83 e0       	ldi	r24, 0x03	; 3
    42ae:	98 2e       	mov	r9, r24
    42b0:	a1 2c       	mov	r10, r1
    42b2:	b1 2c       	mov	r11, r1
    42b4:	f8 01       	movw	r30, r16
    42b6:	84 82       	std	Z+4, r8	; 0x04
    42b8:	95 82       	std	Z+5, r9	; 0x05
    42ba:	a6 82       	std	Z+6, r10	; 0x06
    42bc:	b7 82       	std	Z+7, r11	; 0x07
    42be:	86 e1       	ldi	r24, 0x16	; 22
    42c0:	91 e0       	ldi	r25, 0x01	; 1
    42c2:	91 83       	std	Z+1, r25	; 0x01
    42c4:	80 83       	st	Z, r24
    42c6:	85 ec       	ldi	r24, 0xC5	; 197
    42c8:	90 e0       	ldi	r25, 0x00	; 0
    42ca:	95 87       	std	Z+13, r25	; 0x0d
    42cc:	84 87       	std	Z+12, r24	; 0x0c
    42ce:	84 ec       	ldi	r24, 0xC4	; 196
    42d0:	90 e0       	ldi	r25, 0x00	; 0
    42d2:	97 87       	std	Z+15, r25	; 0x0f
    42d4:	86 87       	std	Z+14, r24	; 0x0e
    42d6:	80 ec       	ldi	r24, 0xC0	; 192
    42d8:	90 e0       	ldi	r25, 0x00	; 0
    42da:	91 8b       	std	Z+17, r25	; 0x11
    42dc:	80 8b       	std	Z+16, r24	; 0x10
    42de:	81 ec       	ldi	r24, 0xC1	; 193
    42e0:	90 e0       	ldi	r25, 0x00	; 0
    42e2:	93 8b       	std	Z+19, r25	; 0x13
    42e4:	82 8b       	std	Z+18, r24	; 0x12
    42e6:	82 ec       	ldi	r24, 0xC2	; 194
    42e8:	90 e0       	ldi	r25, 0x00	; 0
    42ea:	95 8b       	std	Z+21, r25	; 0x15
    42ec:	84 8b       	std	Z+20, r24	; 0x14
    42ee:	86 ec       	ldi	r24, 0xC6	; 198
    42f0:	90 e0       	ldi	r25, 0x00	; 0
    42f2:	97 8b       	std	Z+23, r25	; 0x17
    42f4:	86 8b       	std	Z+22, r24	; 0x16
    42f6:	11 8e       	std	Z+25, r1	; 0x19
    42f8:	12 8e       	std	Z+26, r1	; 0x1a
    42fa:	13 8e       	std	Z+27, r1	; 0x1b
    42fc:	14 8e       	std	Z+28, r1	; 0x1c
    42fe:	c6 e4       	ldi	r28, 0x46	; 70
    4300:	d3 e0       	ldi	r29, 0x03	; 3
    4302:	1b 82       	std	Y+3, r1	; 0x03
    4304:	1a 82       	std	Y+2, r1	; 0x02
    4306:	8c 82       	std	Y+4, r8	; 0x04
    4308:	9d 82       	std	Y+5, r9	; 0x05
    430a:	ae 82       	std	Y+6, r10	; 0x06
    430c:	bf 82       	std	Y+7, r11	; 0x07
    430e:	8c e4       	ldi	r24, 0x4C	; 76
    4310:	91 e0       	ldi	r25, 0x01	; 1
    4312:	99 83       	std	Y+1, r25	; 0x01
    4314:	88 83       	st	Y, r24
    4316:	1c 86       	std	Y+12, r1	; 0x0c
    4318:	1d 86       	std	Y+13, r1	; 0x0d
    431a:	1e 86       	std	Y+14, r1	; 0x0e
    431c:	1a 8a       	std	Y+18, r1	; 0x12
    431e:	19 8a       	std	Y+17, r1	; 0x11
    4320:	9a e3       	ldi	r25, 0x3A	; 58
    4322:	c9 2e       	mov	r12, r25
    4324:	91 e0       	ldi	r25, 0x01	; 1
    4326:	d9 2e       	mov	r13, r25
    4328:	d8 8a       	std	Y+16, r13	; 0x10
    432a:	cf 86       	std	Y+15, r12	; 0x0f
    432c:	8b 8a       	std	Y+19, r8	; 0x13
    432e:	9c 8a       	std	Y+20, r9	; 0x14
    4330:	ad 8a       	std	Y+21, r10	; 0x15
    4332:	be 8a       	std	Y+22, r11	; 0x16
    4334:	81 e6       	ldi	r24, 0x61	; 97
    4336:	93 e0       	ldi	r25, 0x03	; 3
    4338:	0e 94 d5 1b 	call	0x37aa	; 0x37aa <_ZN6StringC2EPKc.constprop.37>
    433c:	28 e2       	ldi	r18, 0x28	; 40
    433e:	e2 2e       	mov	r14, r18
    4340:	21 e0       	ldi	r18, 0x01	; 1
    4342:	f2 2e       	mov	r15, r18
    4344:	f8 8a       	std	Y+16, r15	; 0x10
    4346:	ef 86       	std	Y+15, r14	; 0x0f
    4348:	1c a2       	std	Y+36, r1	; 0x24
    434a:	1b a2       	std	Y+35, r1	; 0x23
    434c:	da a2       	std	Y+34, r13	; 0x22
    434e:	c9 a2       	std	Y+33, r12	; 0x21
    4350:	8d a2       	std	Y+37, r8	; 0x25
    4352:	9e a2       	std	Y+38, r9	; 0x26
    4354:	af a2       	std	Y+39, r10	; 0x27
    4356:	b8 a6       	std	Y+40, r11	; 0x28
    4358:	83 e7       	ldi	r24, 0x73	; 115
    435a:	93 e0       	ldi	r25, 0x03	; 3
    435c:	0e 94 d5 1b 	call	0x37aa	; 0x37aa <_ZN6StringC2EPKc.constprop.37>
    4360:	fa a2       	std	Y+34, r15	; 0x22
    4362:	e9 a2       	std	Y+33, r14	; 0x21
    4364:	1c aa       	std	Y+52, r1	; 0x34
    4366:	1b aa       	std	Y+51, r1	; 0x33
    4368:	8b e7       	ldi	r24, 0x7B	; 123
    436a:	93 e0       	ldi	r25, 0x03	; 3
    436c:	0e 94 d5 1b 	call	0x37aa	; 0x37aa <_ZN6StringC2EPKc.constprop.37>
    4370:	1c af       	std	Y+60, r17	; 0x3c
    4372:	0b af       	std	Y+59, r16	; 0x3b
    4374:	8b e8       	ldi	r24, 0x8B	; 139
    4376:	96 e1       	ldi	r25, 0x16	; 22
    4378:	90 93 88 03 	sts	0x0388, r25	; 0x800388 <Wire+0x42>
    437c:	80 93 87 03 	sts	0x0387, r24	; 0x800387 <Wire+0x41>
    4380:	ec e8       	ldi	r30, 0x8C	; 140
    4382:	f3 e0       	ldi	r31, 0x03	; 3
    4384:	8c e6       	ldi	r24, 0x6C	; 108
    4386:	df 01       	movw	r26, r30
    4388:	1d 92       	st	X+, r1
    438a:	8a 95       	dec	r24
    438c:	e9 f7       	brne	.-6      	; 0x4388 <_GLOBAL__I_65535_0_config_storage.cpp.o.3712+0x106>
    438e:	10 92 f9 03 	sts	0x03F9, r1	; 0x8003f9 <dimmer+0x6d>
    4392:	10 92 f8 03 	sts	0x03F8, r1	; 0x8003f8 <dimmer+0x6c>
    4396:	10 92 fe 03 	sts	0x03FE, r1	; 0x8003fe <dimmer+0x72>
    439a:	10 92 0b 04 	sts	0x040B, r1	; 0x80040b <dimmer+0x7f>
    439e:	10 92 0c 04 	sts	0x040C, r1	; 0x80040c <dimmer+0x80>
    43a2:	61 e0       	ldi	r22, 0x01	; 1
    43a4:	85 e0       	ldi	r24, 0x05	; 5
    43a6:	0e 94 fe 0d 	call	0x1bfc	; 0x1bfc <pinMode>
    43aa:	e5 e3       	ldi	r30, 0x35	; 53
    43ac:	f5 e0       	ldi	r31, 0x05	; 5
    43ae:	e4 91       	lpm	r30, Z
    43b0:	e0 93 8b 03 	sts	0x038B, r30	; 0x80038b <pinCmpBMask>
    43b4:	e1 e2       	ldi	r30, 0x21	; 33
    43b6:	f5 e0       	ldi	r31, 0x05	; 5
    43b8:	e4 91       	lpm	r30, Z
    43ba:	f0 e0       	ldi	r31, 0x00	; 0
    43bc:	ee 0f       	add	r30, r30
    43be:	ff 1f       	adc	r31, r31
    43c0:	ee 5e       	subi	r30, 0xEE	; 238
    43c2:	fa 4f       	sbci	r31, 0xFA	; 250
    43c4:	85 91       	lpm	r24, Z+
    43c6:	94 91       	lpm	r25, Z
    43c8:	90 93 8a 03 	sts	0x038A, r25	; 0x80038a <pinCmpBAddr+0x1>
    43cc:	80 93 89 03 	sts	0x0389, r24	; 0x800389 <pinCmpBAddr>
    43d0:	8f ef       	ldi	r24, 0xFF	; 255
    43d2:	9f ef       	ldi	r25, 0xFF	; 255
    43d4:	90 93 f1 03 	sts	0x03F1, r25	; 0x8003f1 <dimmer+0x65>
    43d8:	80 93 f0 03 	sts	0x03F0, r24	; 0x8003f0 <dimmer+0x64>
    43dc:	90 93 f3 03 	sts	0x03F3, r25	; 0x8003f3 <dimmer+0x67>
    43e0:	80 93 f2 03 	sts	0x03F2, r24	; 0x8003f2 <dimmer+0x66>
    43e4:	90 93 f5 03 	sts	0x03F5, r25	; 0x8003f5 <dimmer+0x69>
    43e8:	80 93 f4 03 	sts	0x03F4, r24	; 0x8003f4 <dimmer+0x68>
    43ec:	90 93 f7 03 	sts	0x03F7, r25	; 0x8003f7 <dimmer+0x6b>
    43f0:	80 93 f6 03 	sts	0x03F6, r24	; 0x8003f6 <dimmer+0x6a>
    43f4:	10 92 ff 03 	sts	0x03FF, r1	; 0x8003ff <dimmer+0x73>
    43f8:	10 92 00 04 	sts	0x0400, r1	; 0x800400 <dimmer+0x74>
    43fc:	10 92 01 04 	sts	0x0401, r1	; 0x800401 <dimmer+0x75>
    4400:	10 92 02 04 	sts	0x0402, r1	; 0x800402 <dimmer+0x76>
    4404:	8e e3       	ldi	r24, 0x3E	; 62
    4406:	9c e1       	ldi	r25, 0x1C	; 28
    4408:	a0 e0       	ldi	r26, 0x00	; 0
    440a:	b0 e0       	ldi	r27, 0x00	; 0
    440c:	80 93 03 04 	sts	0x0403, r24	; 0x800403 <dimmer+0x77>
    4410:	90 93 04 04 	sts	0x0404, r25	; 0x800404 <dimmer+0x78>
    4414:	a0 93 05 04 	sts	0x0405, r26	; 0x800405 <dimmer+0x79>
    4418:	b0 93 06 04 	sts	0x0406, r27	; 0x800406 <dimmer+0x7a>
    441c:	ec e8       	ldi	r30, 0x8C	; 140
    441e:	f4 e0       	ldi	r31, 0x04	; 4
    4420:	83 e3       	ldi	r24, 0x33	; 51
    4422:	94 e0       	ldi	r25, 0x04	; 4
    4424:	97 87       	std	Z+15, r25	; 0x0f
    4426:	86 87       	std	Z+14, r24	; 0x0e
    4428:	10 82       	st	Z, r1
    442a:	11 82       	std	Z+1, r1	; 0x01
    442c:	12 82       	std	Z+2, r1	; 0x02
    442e:	13 82       	std	Z+3, r1	; 0x03
    4430:	15 82       	std	Z+5, r1	; 0x05
    4432:	14 82       	std	Z+4, r1	; 0x04
    4434:	88 e0       	ldi	r24, 0x08	; 8
    4436:	e2 e9       	ldi	r30, 0x92	; 146
    4438:	f4 e0       	ldi	r31, 0x04	; 4
    443a:	df 01       	movw	r26, r30
    443c:	1d 92       	st	X+, r1
    443e:	8a 95       	dec	r24
    4440:	e9 f7       	brne	.-6      	; 0x443c <_GLOBAL__I_65535_0_config_storage.cpp.o.3712+0x1ba>
    4442:	df 91       	pop	r29
    4444:	cf 91       	pop	r28
    4446:	1f 91       	pop	r17
    4448:	0f 91       	pop	r16
    444a:	ff 90       	pop	r15
    444c:	ef 90       	pop	r14
    444e:	df 90       	pop	r13
    4450:	cf 90       	pop	r12
    4452:	bf 90       	pop	r11
    4454:	af 90       	pop	r10
    4456:	9f 90       	pop	r9
    4458:	8f 90       	pop	r8
    445a:	08 95       	ret

0000445c <vfprintf>:
    445c:	a0 e1       	ldi	r26, 0x10	; 16
    445e:	b0 e0       	ldi	r27, 0x00	; 0
    4460:	e4 e3       	ldi	r30, 0x34	; 52
    4462:	f2 e2       	ldi	r31, 0x22	; 34
    4464:	0c 94 ab 25 	jmp	0x4b56	; 0x4b56 <__prologue_saves__>
    4468:	7c 01       	movw	r14, r24
    446a:	1b 01       	movw	r2, r22
    446c:	6a 01       	movw	r12, r20
    446e:	fc 01       	movw	r30, r24
    4470:	17 82       	std	Z+7, r1	; 0x07
    4472:	16 82       	std	Z+6, r1	; 0x06
    4474:	83 81       	ldd	r24, Z+3	; 0x03
    4476:	81 ff       	sbrs	r24, 1
    4478:	44 c3       	rjmp	.+1672   	; 0x4b02 <vfprintf+0x6a6>
    447a:	9e 01       	movw	r18, r28
    447c:	2f 5f       	subi	r18, 0xFF	; 255
    447e:	3f 4f       	sbci	r19, 0xFF	; 255
    4480:	39 01       	movw	r6, r18
    4482:	f7 01       	movw	r30, r14
    4484:	93 81       	ldd	r25, Z+3	; 0x03
    4486:	f1 01       	movw	r30, r2
    4488:	93 fd       	sbrc	r25, 3
    448a:	85 91       	lpm	r24, Z+
    448c:	93 ff       	sbrs	r25, 3
    448e:	81 91       	ld	r24, Z+
    4490:	1f 01       	movw	r2, r30
    4492:	88 23       	and	r24, r24
    4494:	09 f4       	brne	.+2      	; 0x4498 <vfprintf+0x3c>
    4496:	31 c3       	rjmp	.+1634   	; 0x4afa <vfprintf+0x69e>
    4498:	85 32       	cpi	r24, 0x25	; 37
    449a:	39 f4       	brne	.+14     	; 0x44aa <vfprintf+0x4e>
    449c:	93 fd       	sbrc	r25, 3
    449e:	85 91       	lpm	r24, Z+
    44a0:	93 ff       	sbrs	r25, 3
    44a2:	81 91       	ld	r24, Z+
    44a4:	1f 01       	movw	r2, r30
    44a6:	85 32       	cpi	r24, 0x25	; 37
    44a8:	39 f4       	brne	.+14     	; 0x44b8 <vfprintf+0x5c>
    44aa:	b7 01       	movw	r22, r14
    44ac:	90 e0       	ldi	r25, 0x00	; 0
    44ae:	0e 94 f5 27 	call	0x4fea	; 0x4fea <fputc>
    44b2:	56 01       	movw	r10, r12
    44b4:	65 01       	movw	r12, r10
    44b6:	e5 cf       	rjmp	.-54     	; 0x4482 <vfprintf+0x26>
    44b8:	10 e0       	ldi	r17, 0x00	; 0
    44ba:	51 2c       	mov	r5, r1
    44bc:	91 2c       	mov	r9, r1
    44be:	ff e1       	ldi	r31, 0x1F	; 31
    44c0:	f9 15       	cp	r31, r9
    44c2:	d8 f0       	brcs	.+54     	; 0x44fa <vfprintf+0x9e>
    44c4:	8b 32       	cpi	r24, 0x2B	; 43
    44c6:	79 f0       	breq	.+30     	; 0x44e6 <vfprintf+0x8a>
    44c8:	38 f4       	brcc	.+14     	; 0x44d8 <vfprintf+0x7c>
    44ca:	80 32       	cpi	r24, 0x20	; 32
    44cc:	79 f0       	breq	.+30     	; 0x44ec <vfprintf+0x90>
    44ce:	83 32       	cpi	r24, 0x23	; 35
    44d0:	a1 f4       	brne	.+40     	; 0x44fa <vfprintf+0x9e>
    44d2:	f9 2d       	mov	r31, r9
    44d4:	f0 61       	ori	r31, 0x10	; 16
    44d6:	2e c0       	rjmp	.+92     	; 0x4534 <vfprintf+0xd8>
    44d8:	8d 32       	cpi	r24, 0x2D	; 45
    44da:	61 f0       	breq	.+24     	; 0x44f4 <vfprintf+0x98>
    44dc:	80 33       	cpi	r24, 0x30	; 48
    44de:	69 f4       	brne	.+26     	; 0x44fa <vfprintf+0x9e>
    44e0:	29 2d       	mov	r18, r9
    44e2:	21 60       	ori	r18, 0x01	; 1
    44e4:	2d c0       	rjmp	.+90     	; 0x4540 <vfprintf+0xe4>
    44e6:	39 2d       	mov	r19, r9
    44e8:	32 60       	ori	r19, 0x02	; 2
    44ea:	93 2e       	mov	r9, r19
    44ec:	89 2d       	mov	r24, r9
    44ee:	84 60       	ori	r24, 0x04	; 4
    44f0:	98 2e       	mov	r9, r24
    44f2:	2a c0       	rjmp	.+84     	; 0x4548 <vfprintf+0xec>
    44f4:	e9 2d       	mov	r30, r9
    44f6:	e8 60       	ori	r30, 0x08	; 8
    44f8:	15 c0       	rjmp	.+42     	; 0x4524 <vfprintf+0xc8>
    44fa:	97 fc       	sbrc	r9, 7
    44fc:	2d c0       	rjmp	.+90     	; 0x4558 <vfprintf+0xfc>
    44fe:	20 ed       	ldi	r18, 0xD0	; 208
    4500:	28 0f       	add	r18, r24
    4502:	2a 30       	cpi	r18, 0x0A	; 10
    4504:	88 f4       	brcc	.+34     	; 0x4528 <vfprintf+0xcc>
    4506:	96 fe       	sbrs	r9, 6
    4508:	06 c0       	rjmp	.+12     	; 0x4516 <vfprintf+0xba>
    450a:	3a e0       	ldi	r19, 0x0A	; 10
    450c:	13 9f       	mul	r17, r19
    450e:	20 0d       	add	r18, r0
    4510:	11 24       	eor	r1, r1
    4512:	12 2f       	mov	r17, r18
    4514:	19 c0       	rjmp	.+50     	; 0x4548 <vfprintf+0xec>
    4516:	8a e0       	ldi	r24, 0x0A	; 10
    4518:	58 9e       	mul	r5, r24
    451a:	20 0d       	add	r18, r0
    451c:	11 24       	eor	r1, r1
    451e:	52 2e       	mov	r5, r18
    4520:	e9 2d       	mov	r30, r9
    4522:	e0 62       	ori	r30, 0x20	; 32
    4524:	9e 2e       	mov	r9, r30
    4526:	10 c0       	rjmp	.+32     	; 0x4548 <vfprintf+0xec>
    4528:	8e 32       	cpi	r24, 0x2E	; 46
    452a:	31 f4       	brne	.+12     	; 0x4538 <vfprintf+0xdc>
    452c:	96 fc       	sbrc	r9, 6
    452e:	e5 c2       	rjmp	.+1482   	; 0x4afa <vfprintf+0x69e>
    4530:	f9 2d       	mov	r31, r9
    4532:	f0 64       	ori	r31, 0x40	; 64
    4534:	9f 2e       	mov	r9, r31
    4536:	08 c0       	rjmp	.+16     	; 0x4548 <vfprintf+0xec>
    4538:	8c 36       	cpi	r24, 0x6C	; 108
    453a:	21 f4       	brne	.+8      	; 0x4544 <vfprintf+0xe8>
    453c:	29 2d       	mov	r18, r9
    453e:	20 68       	ori	r18, 0x80	; 128
    4540:	92 2e       	mov	r9, r18
    4542:	02 c0       	rjmp	.+4      	; 0x4548 <vfprintf+0xec>
    4544:	88 36       	cpi	r24, 0x68	; 104
    4546:	41 f4       	brne	.+16     	; 0x4558 <vfprintf+0xfc>
    4548:	f1 01       	movw	r30, r2
    454a:	93 fd       	sbrc	r25, 3
    454c:	85 91       	lpm	r24, Z+
    454e:	93 ff       	sbrs	r25, 3
    4550:	81 91       	ld	r24, Z+
    4552:	1f 01       	movw	r2, r30
    4554:	81 11       	cpse	r24, r1
    4556:	b3 cf       	rjmp	.-154    	; 0x44be <vfprintf+0x62>
    4558:	9b eb       	ldi	r25, 0xBB	; 187
    455a:	98 0f       	add	r25, r24
    455c:	93 30       	cpi	r25, 0x03	; 3
    455e:	20 f4       	brcc	.+8      	; 0x4568 <vfprintf+0x10c>
    4560:	99 2d       	mov	r25, r9
    4562:	90 61       	ori	r25, 0x10	; 16
    4564:	80 5e       	subi	r24, 0xE0	; 224
    4566:	07 c0       	rjmp	.+14     	; 0x4576 <vfprintf+0x11a>
    4568:	9b e9       	ldi	r25, 0x9B	; 155
    456a:	98 0f       	add	r25, r24
    456c:	93 30       	cpi	r25, 0x03	; 3
    456e:	08 f0       	brcs	.+2      	; 0x4572 <vfprintf+0x116>
    4570:	66 c1       	rjmp	.+716    	; 0x483e <vfprintf+0x3e2>
    4572:	99 2d       	mov	r25, r9
    4574:	9f 7e       	andi	r25, 0xEF	; 239
    4576:	96 ff       	sbrs	r25, 6
    4578:	16 e0       	ldi	r17, 0x06	; 6
    457a:	9f 73       	andi	r25, 0x3F	; 63
    457c:	99 2e       	mov	r9, r25
    457e:	85 36       	cpi	r24, 0x65	; 101
    4580:	19 f4       	brne	.+6      	; 0x4588 <vfprintf+0x12c>
    4582:	90 64       	ori	r25, 0x40	; 64
    4584:	99 2e       	mov	r9, r25
    4586:	08 c0       	rjmp	.+16     	; 0x4598 <vfprintf+0x13c>
    4588:	86 36       	cpi	r24, 0x66	; 102
    458a:	21 f4       	brne	.+8      	; 0x4594 <vfprintf+0x138>
    458c:	39 2f       	mov	r19, r25
    458e:	30 68       	ori	r19, 0x80	; 128
    4590:	93 2e       	mov	r9, r19
    4592:	02 c0       	rjmp	.+4      	; 0x4598 <vfprintf+0x13c>
    4594:	11 11       	cpse	r17, r1
    4596:	11 50       	subi	r17, 0x01	; 1
    4598:	97 fe       	sbrs	r9, 7
    459a:	07 c0       	rjmp	.+14     	; 0x45aa <vfprintf+0x14e>
    459c:	1c 33       	cpi	r17, 0x3C	; 60
    459e:	50 f4       	brcc	.+20     	; 0x45b4 <vfprintf+0x158>
    45a0:	44 24       	eor	r4, r4
    45a2:	43 94       	inc	r4
    45a4:	41 0e       	add	r4, r17
    45a6:	27 e0       	ldi	r18, 0x07	; 7
    45a8:	0b c0       	rjmp	.+22     	; 0x45c0 <vfprintf+0x164>
    45aa:	18 30       	cpi	r17, 0x08	; 8
    45ac:	38 f0       	brcs	.+14     	; 0x45bc <vfprintf+0x160>
    45ae:	27 e0       	ldi	r18, 0x07	; 7
    45b0:	17 e0       	ldi	r17, 0x07	; 7
    45b2:	05 c0       	rjmp	.+10     	; 0x45be <vfprintf+0x162>
    45b4:	27 e0       	ldi	r18, 0x07	; 7
    45b6:	9c e3       	ldi	r25, 0x3C	; 60
    45b8:	49 2e       	mov	r4, r25
    45ba:	02 c0       	rjmp	.+4      	; 0x45c0 <vfprintf+0x164>
    45bc:	21 2f       	mov	r18, r17
    45be:	41 2c       	mov	r4, r1
    45c0:	56 01       	movw	r10, r12
    45c2:	84 e0       	ldi	r24, 0x04	; 4
    45c4:	a8 0e       	add	r10, r24
    45c6:	b1 1c       	adc	r11, r1
    45c8:	f6 01       	movw	r30, r12
    45ca:	60 81       	ld	r22, Z
    45cc:	71 81       	ldd	r23, Z+1	; 0x01
    45ce:	82 81       	ldd	r24, Z+2	; 0x02
    45d0:	93 81       	ldd	r25, Z+3	; 0x03
    45d2:	04 2d       	mov	r16, r4
    45d4:	a3 01       	movw	r20, r6
    45d6:	0e 94 d7 26 	call	0x4dae	; 0x4dae <__ftoa_engine>
    45da:	6c 01       	movw	r12, r24
    45dc:	f9 81       	ldd	r31, Y+1	; 0x01
    45de:	fc 87       	std	Y+12, r31	; 0x0c
    45e0:	f0 ff       	sbrs	r31, 0
    45e2:	02 c0       	rjmp	.+4      	; 0x45e8 <vfprintf+0x18c>
    45e4:	f3 ff       	sbrs	r31, 3
    45e6:	06 c0       	rjmp	.+12     	; 0x45f4 <vfprintf+0x198>
    45e8:	91 fc       	sbrc	r9, 1
    45ea:	06 c0       	rjmp	.+12     	; 0x45f8 <vfprintf+0x19c>
    45ec:	92 fe       	sbrs	r9, 2
    45ee:	06 c0       	rjmp	.+12     	; 0x45fc <vfprintf+0x1a0>
    45f0:	00 e2       	ldi	r16, 0x20	; 32
    45f2:	05 c0       	rjmp	.+10     	; 0x45fe <vfprintf+0x1a2>
    45f4:	0d e2       	ldi	r16, 0x2D	; 45
    45f6:	03 c0       	rjmp	.+6      	; 0x45fe <vfprintf+0x1a2>
    45f8:	0b e2       	ldi	r16, 0x2B	; 43
    45fa:	01 c0       	rjmp	.+2      	; 0x45fe <vfprintf+0x1a2>
    45fc:	00 e0       	ldi	r16, 0x00	; 0
    45fe:	8c 85       	ldd	r24, Y+12	; 0x0c
    4600:	8c 70       	andi	r24, 0x0C	; 12
    4602:	19 f0       	breq	.+6      	; 0x460a <vfprintf+0x1ae>
    4604:	01 11       	cpse	r16, r1
    4606:	5a c2       	rjmp	.+1204   	; 0x4abc <vfprintf+0x660>
    4608:	9b c2       	rjmp	.+1334   	; 0x4b40 <vfprintf+0x6e4>
    460a:	97 fe       	sbrs	r9, 7
    460c:	10 c0       	rjmp	.+32     	; 0x462e <vfprintf+0x1d2>
    460e:	4c 0c       	add	r4, r12
    4610:	fc 85       	ldd	r31, Y+12	; 0x0c
    4612:	f4 ff       	sbrs	r31, 4
    4614:	04 c0       	rjmp	.+8      	; 0x461e <vfprintf+0x1c2>
    4616:	8a 81       	ldd	r24, Y+2	; 0x02
    4618:	81 33       	cpi	r24, 0x31	; 49
    461a:	09 f4       	brne	.+2      	; 0x461e <vfprintf+0x1c2>
    461c:	4a 94       	dec	r4
    461e:	14 14       	cp	r1, r4
    4620:	74 f5       	brge	.+92     	; 0x467e <vfprintf+0x222>
    4622:	28 e0       	ldi	r18, 0x08	; 8
    4624:	24 15       	cp	r18, r4
    4626:	78 f5       	brcc	.+94     	; 0x4686 <vfprintf+0x22a>
    4628:	88 e0       	ldi	r24, 0x08	; 8
    462a:	48 2e       	mov	r4, r24
    462c:	2c c0       	rjmp	.+88     	; 0x4686 <vfprintf+0x22a>
    462e:	96 fc       	sbrc	r9, 6
    4630:	2a c0       	rjmp	.+84     	; 0x4686 <vfprintf+0x22a>
    4632:	81 2f       	mov	r24, r17
    4634:	90 e0       	ldi	r25, 0x00	; 0
    4636:	8c 15       	cp	r24, r12
    4638:	9d 05       	cpc	r25, r13
    463a:	9c f0       	brlt	.+38     	; 0x4662 <vfprintf+0x206>
    463c:	3c ef       	ldi	r19, 0xFC	; 252
    463e:	c3 16       	cp	r12, r19
    4640:	3f ef       	ldi	r19, 0xFF	; 255
    4642:	d3 06       	cpc	r13, r19
    4644:	74 f0       	brlt	.+28     	; 0x4662 <vfprintf+0x206>
    4646:	89 2d       	mov	r24, r9
    4648:	80 68       	ori	r24, 0x80	; 128
    464a:	98 2e       	mov	r9, r24
    464c:	0a c0       	rjmp	.+20     	; 0x4662 <vfprintf+0x206>
    464e:	e2 e0       	ldi	r30, 0x02	; 2
    4650:	f0 e0       	ldi	r31, 0x00	; 0
    4652:	ec 0f       	add	r30, r28
    4654:	fd 1f       	adc	r31, r29
    4656:	e1 0f       	add	r30, r17
    4658:	f1 1d       	adc	r31, r1
    465a:	80 81       	ld	r24, Z
    465c:	80 33       	cpi	r24, 0x30	; 48
    465e:	19 f4       	brne	.+6      	; 0x4666 <vfprintf+0x20a>
    4660:	11 50       	subi	r17, 0x01	; 1
    4662:	11 11       	cpse	r17, r1
    4664:	f4 cf       	rjmp	.-24     	; 0x464e <vfprintf+0x1f2>
    4666:	97 fe       	sbrs	r9, 7
    4668:	0e c0       	rjmp	.+28     	; 0x4686 <vfprintf+0x22a>
    466a:	44 24       	eor	r4, r4
    466c:	43 94       	inc	r4
    466e:	41 0e       	add	r4, r17
    4670:	81 2f       	mov	r24, r17
    4672:	90 e0       	ldi	r25, 0x00	; 0
    4674:	c8 16       	cp	r12, r24
    4676:	d9 06       	cpc	r13, r25
    4678:	2c f4       	brge	.+10     	; 0x4684 <vfprintf+0x228>
    467a:	1c 19       	sub	r17, r12
    467c:	04 c0       	rjmp	.+8      	; 0x4686 <vfprintf+0x22a>
    467e:	44 24       	eor	r4, r4
    4680:	43 94       	inc	r4
    4682:	01 c0       	rjmp	.+2      	; 0x4686 <vfprintf+0x22a>
    4684:	10 e0       	ldi	r17, 0x00	; 0
    4686:	97 fe       	sbrs	r9, 7
    4688:	06 c0       	rjmp	.+12     	; 0x4696 <vfprintf+0x23a>
    468a:	1c 14       	cp	r1, r12
    468c:	1d 04       	cpc	r1, r13
    468e:	34 f4       	brge	.+12     	; 0x469c <vfprintf+0x240>
    4690:	c6 01       	movw	r24, r12
    4692:	01 96       	adiw	r24, 0x01	; 1
    4694:	05 c0       	rjmp	.+10     	; 0x46a0 <vfprintf+0x244>
    4696:	85 e0       	ldi	r24, 0x05	; 5
    4698:	90 e0       	ldi	r25, 0x00	; 0
    469a:	02 c0       	rjmp	.+4      	; 0x46a0 <vfprintf+0x244>
    469c:	81 e0       	ldi	r24, 0x01	; 1
    469e:	90 e0       	ldi	r25, 0x00	; 0
    46a0:	01 11       	cpse	r16, r1
    46a2:	01 96       	adiw	r24, 0x01	; 1
    46a4:	11 23       	and	r17, r17
    46a6:	31 f0       	breq	.+12     	; 0x46b4 <vfprintf+0x258>
    46a8:	21 2f       	mov	r18, r17
    46aa:	30 e0       	ldi	r19, 0x00	; 0
    46ac:	2f 5f       	subi	r18, 0xFF	; 255
    46ae:	3f 4f       	sbci	r19, 0xFF	; 255
    46b0:	82 0f       	add	r24, r18
    46b2:	93 1f       	adc	r25, r19
    46b4:	25 2d       	mov	r18, r5
    46b6:	30 e0       	ldi	r19, 0x00	; 0
    46b8:	82 17       	cp	r24, r18
    46ba:	93 07       	cpc	r25, r19
    46bc:	14 f4       	brge	.+4      	; 0x46c2 <vfprintf+0x266>
    46be:	58 1a       	sub	r5, r24
    46c0:	01 c0       	rjmp	.+2      	; 0x46c4 <vfprintf+0x268>
    46c2:	51 2c       	mov	r5, r1
    46c4:	89 2d       	mov	r24, r9
    46c6:	89 70       	andi	r24, 0x09	; 9
    46c8:	49 f4       	brne	.+18     	; 0x46dc <vfprintf+0x280>
    46ca:	55 20       	and	r5, r5
    46cc:	39 f0       	breq	.+14     	; 0x46dc <vfprintf+0x280>
    46ce:	b7 01       	movw	r22, r14
    46d0:	80 e2       	ldi	r24, 0x20	; 32
    46d2:	90 e0       	ldi	r25, 0x00	; 0
    46d4:	0e 94 f5 27 	call	0x4fea	; 0x4fea <fputc>
    46d8:	5a 94       	dec	r5
    46da:	f7 cf       	rjmp	.-18     	; 0x46ca <vfprintf+0x26e>
    46dc:	00 23       	and	r16, r16
    46de:	29 f0       	breq	.+10     	; 0x46ea <vfprintf+0x28e>
    46e0:	b7 01       	movw	r22, r14
    46e2:	80 2f       	mov	r24, r16
    46e4:	90 e0       	ldi	r25, 0x00	; 0
    46e6:	0e 94 f5 27 	call	0x4fea	; 0x4fea <fputc>
    46ea:	93 fc       	sbrc	r9, 3
    46ec:	09 c0       	rjmp	.+18     	; 0x4700 <vfprintf+0x2a4>
    46ee:	55 20       	and	r5, r5
    46f0:	39 f0       	breq	.+14     	; 0x4700 <vfprintf+0x2a4>
    46f2:	b7 01       	movw	r22, r14
    46f4:	80 e3       	ldi	r24, 0x30	; 48
    46f6:	90 e0       	ldi	r25, 0x00	; 0
    46f8:	0e 94 f5 27 	call	0x4fea	; 0x4fea <fputc>
    46fc:	5a 94       	dec	r5
    46fe:	f7 cf       	rjmp	.-18     	; 0x46ee <vfprintf+0x292>
    4700:	97 fe       	sbrs	r9, 7
    4702:	4c c0       	rjmp	.+152    	; 0x479c <vfprintf+0x340>
    4704:	46 01       	movw	r8, r12
    4706:	d7 fe       	sbrs	r13, 7
    4708:	02 c0       	rjmp	.+4      	; 0x470e <vfprintf+0x2b2>
    470a:	81 2c       	mov	r8, r1
    470c:	91 2c       	mov	r9, r1
    470e:	c6 01       	movw	r24, r12
    4710:	88 19       	sub	r24, r8
    4712:	99 09       	sbc	r25, r9
    4714:	f3 01       	movw	r30, r6
    4716:	e8 0f       	add	r30, r24
    4718:	f9 1f       	adc	r31, r25
    471a:	fe 87       	std	Y+14, r31	; 0x0e
    471c:	ed 87       	std	Y+13, r30	; 0x0d
    471e:	96 01       	movw	r18, r12
    4720:	24 19       	sub	r18, r4
    4722:	31 09       	sbc	r19, r1
    4724:	38 8b       	std	Y+16, r19	; 0x10
    4726:	2f 87       	std	Y+15, r18	; 0x0f
    4728:	01 2f       	mov	r16, r17
    472a:	10 e0       	ldi	r17, 0x00	; 0
    472c:	11 95       	neg	r17
    472e:	01 95       	neg	r16
    4730:	11 09       	sbc	r17, r1
    4732:	3f ef       	ldi	r19, 0xFF	; 255
    4734:	83 16       	cp	r8, r19
    4736:	93 06       	cpc	r9, r19
    4738:	29 f4       	brne	.+10     	; 0x4744 <vfprintf+0x2e8>
    473a:	b7 01       	movw	r22, r14
    473c:	8e e2       	ldi	r24, 0x2E	; 46
    473e:	90 e0       	ldi	r25, 0x00	; 0
    4740:	0e 94 f5 27 	call	0x4fea	; 0x4fea <fputc>
    4744:	c8 14       	cp	r12, r8
    4746:	d9 04       	cpc	r13, r9
    4748:	4c f0       	brlt	.+18     	; 0x475c <vfprintf+0x300>
    474a:	8f 85       	ldd	r24, Y+15	; 0x0f
    474c:	98 89       	ldd	r25, Y+16	; 0x10
    474e:	88 15       	cp	r24, r8
    4750:	99 05       	cpc	r25, r9
    4752:	24 f4       	brge	.+8      	; 0x475c <vfprintf+0x300>
    4754:	ed 85       	ldd	r30, Y+13	; 0x0d
    4756:	fe 85       	ldd	r31, Y+14	; 0x0e
    4758:	81 81       	ldd	r24, Z+1	; 0x01
    475a:	01 c0       	rjmp	.+2      	; 0x475e <vfprintf+0x302>
    475c:	80 e3       	ldi	r24, 0x30	; 48
    475e:	f1 e0       	ldi	r31, 0x01	; 1
    4760:	8f 1a       	sub	r8, r31
    4762:	91 08       	sbc	r9, r1
    4764:	2d 85       	ldd	r18, Y+13	; 0x0d
    4766:	3e 85       	ldd	r19, Y+14	; 0x0e
    4768:	2f 5f       	subi	r18, 0xFF	; 255
    476a:	3f 4f       	sbci	r19, 0xFF	; 255
    476c:	3e 87       	std	Y+14, r19	; 0x0e
    476e:	2d 87       	std	Y+13, r18	; 0x0d
    4770:	80 16       	cp	r8, r16
    4772:	91 06       	cpc	r9, r17
    4774:	2c f0       	brlt	.+10     	; 0x4780 <vfprintf+0x324>
    4776:	b7 01       	movw	r22, r14
    4778:	90 e0       	ldi	r25, 0x00	; 0
    477a:	0e 94 f5 27 	call	0x4fea	; 0x4fea <fputc>
    477e:	d9 cf       	rjmp	.-78     	; 0x4732 <vfprintf+0x2d6>
    4780:	c8 14       	cp	r12, r8
    4782:	d9 04       	cpc	r13, r9
    4784:	41 f4       	brne	.+16     	; 0x4796 <vfprintf+0x33a>
    4786:	9a 81       	ldd	r25, Y+2	; 0x02
    4788:	96 33       	cpi	r25, 0x36	; 54
    478a:	20 f4       	brcc	.+8      	; 0x4794 <vfprintf+0x338>
    478c:	95 33       	cpi	r25, 0x35	; 53
    478e:	19 f4       	brne	.+6      	; 0x4796 <vfprintf+0x33a>
    4790:	3c 85       	ldd	r19, Y+12	; 0x0c
    4792:	34 ff       	sbrs	r19, 4
    4794:	81 e3       	ldi	r24, 0x31	; 49
    4796:	b7 01       	movw	r22, r14
    4798:	90 e0       	ldi	r25, 0x00	; 0
    479a:	4e c0       	rjmp	.+156    	; 0x4838 <vfprintf+0x3dc>
    479c:	8a 81       	ldd	r24, Y+2	; 0x02
    479e:	81 33       	cpi	r24, 0x31	; 49
    47a0:	19 f0       	breq	.+6      	; 0x47a8 <vfprintf+0x34c>
    47a2:	9c 85       	ldd	r25, Y+12	; 0x0c
    47a4:	9f 7e       	andi	r25, 0xEF	; 239
    47a6:	9c 87       	std	Y+12, r25	; 0x0c
    47a8:	b7 01       	movw	r22, r14
    47aa:	90 e0       	ldi	r25, 0x00	; 0
    47ac:	0e 94 f5 27 	call	0x4fea	; 0x4fea <fputc>
    47b0:	11 11       	cpse	r17, r1
    47b2:	05 c0       	rjmp	.+10     	; 0x47be <vfprintf+0x362>
    47b4:	94 fc       	sbrc	r9, 4
    47b6:	18 c0       	rjmp	.+48     	; 0x47e8 <vfprintf+0x38c>
    47b8:	85 e6       	ldi	r24, 0x65	; 101
    47ba:	90 e0       	ldi	r25, 0x00	; 0
    47bc:	17 c0       	rjmp	.+46     	; 0x47ec <vfprintf+0x390>
    47be:	b7 01       	movw	r22, r14
    47c0:	8e e2       	ldi	r24, 0x2E	; 46
    47c2:	90 e0       	ldi	r25, 0x00	; 0
    47c4:	0e 94 f5 27 	call	0x4fea	; 0x4fea <fputc>
    47c8:	1e 5f       	subi	r17, 0xFE	; 254
    47ca:	82 e0       	ldi	r24, 0x02	; 2
    47cc:	01 e0       	ldi	r16, 0x01	; 1
    47ce:	08 0f       	add	r16, r24
    47d0:	f3 01       	movw	r30, r6
    47d2:	e8 0f       	add	r30, r24
    47d4:	f1 1d       	adc	r31, r1
    47d6:	80 81       	ld	r24, Z
    47d8:	b7 01       	movw	r22, r14
    47da:	90 e0       	ldi	r25, 0x00	; 0
    47dc:	0e 94 f5 27 	call	0x4fea	; 0x4fea <fputc>
    47e0:	80 2f       	mov	r24, r16
    47e2:	01 13       	cpse	r16, r17
    47e4:	f3 cf       	rjmp	.-26     	; 0x47cc <vfprintf+0x370>
    47e6:	e6 cf       	rjmp	.-52     	; 0x47b4 <vfprintf+0x358>
    47e8:	85 e4       	ldi	r24, 0x45	; 69
    47ea:	90 e0       	ldi	r25, 0x00	; 0
    47ec:	b7 01       	movw	r22, r14
    47ee:	0e 94 f5 27 	call	0x4fea	; 0x4fea <fputc>
    47f2:	d7 fc       	sbrc	r13, 7
    47f4:	06 c0       	rjmp	.+12     	; 0x4802 <vfprintf+0x3a6>
    47f6:	c1 14       	cp	r12, r1
    47f8:	d1 04       	cpc	r13, r1
    47fa:	41 f4       	brne	.+16     	; 0x480c <vfprintf+0x3b0>
    47fc:	ec 85       	ldd	r30, Y+12	; 0x0c
    47fe:	e4 ff       	sbrs	r30, 4
    4800:	05 c0       	rjmp	.+10     	; 0x480c <vfprintf+0x3b0>
    4802:	d1 94       	neg	r13
    4804:	c1 94       	neg	r12
    4806:	d1 08       	sbc	r13, r1
    4808:	8d e2       	ldi	r24, 0x2D	; 45
    480a:	01 c0       	rjmp	.+2      	; 0x480e <vfprintf+0x3b2>
    480c:	8b e2       	ldi	r24, 0x2B	; 43
    480e:	b7 01       	movw	r22, r14
    4810:	90 e0       	ldi	r25, 0x00	; 0
    4812:	0e 94 f5 27 	call	0x4fea	; 0x4fea <fputc>
    4816:	80 e3       	ldi	r24, 0x30	; 48
    4818:	2a e0       	ldi	r18, 0x0A	; 10
    481a:	c2 16       	cp	r12, r18
    481c:	d1 04       	cpc	r13, r1
    481e:	2c f0       	brlt	.+10     	; 0x482a <vfprintf+0x3ce>
    4820:	8f 5f       	subi	r24, 0xFF	; 255
    4822:	fa e0       	ldi	r31, 0x0A	; 10
    4824:	cf 1a       	sub	r12, r31
    4826:	d1 08       	sbc	r13, r1
    4828:	f7 cf       	rjmp	.-18     	; 0x4818 <vfprintf+0x3bc>
    482a:	b7 01       	movw	r22, r14
    482c:	90 e0       	ldi	r25, 0x00	; 0
    482e:	0e 94 f5 27 	call	0x4fea	; 0x4fea <fputc>
    4832:	b7 01       	movw	r22, r14
    4834:	c6 01       	movw	r24, r12
    4836:	c0 96       	adiw	r24, 0x30	; 48
    4838:	0e 94 f5 27 	call	0x4fea	; 0x4fea <fputc>
    483c:	54 c1       	rjmp	.+680    	; 0x4ae6 <vfprintf+0x68a>
    483e:	83 36       	cpi	r24, 0x63	; 99
    4840:	31 f0       	breq	.+12     	; 0x484e <vfprintf+0x3f2>
    4842:	83 37       	cpi	r24, 0x73	; 115
    4844:	79 f0       	breq	.+30     	; 0x4864 <vfprintf+0x408>
    4846:	83 35       	cpi	r24, 0x53	; 83
    4848:	09 f0       	breq	.+2      	; 0x484c <vfprintf+0x3f0>
    484a:	56 c0       	rjmp	.+172    	; 0x48f8 <vfprintf+0x49c>
    484c:	20 c0       	rjmp	.+64     	; 0x488e <vfprintf+0x432>
    484e:	56 01       	movw	r10, r12
    4850:	32 e0       	ldi	r19, 0x02	; 2
    4852:	a3 0e       	add	r10, r19
    4854:	b1 1c       	adc	r11, r1
    4856:	f6 01       	movw	r30, r12
    4858:	80 81       	ld	r24, Z
    485a:	89 83       	std	Y+1, r24	; 0x01
    485c:	01 e0       	ldi	r16, 0x01	; 1
    485e:	10 e0       	ldi	r17, 0x00	; 0
    4860:	63 01       	movw	r12, r6
    4862:	12 c0       	rjmp	.+36     	; 0x4888 <vfprintf+0x42c>
    4864:	56 01       	movw	r10, r12
    4866:	f2 e0       	ldi	r31, 0x02	; 2
    4868:	af 0e       	add	r10, r31
    486a:	b1 1c       	adc	r11, r1
    486c:	f6 01       	movw	r30, r12
    486e:	c0 80       	ld	r12, Z
    4870:	d1 80       	ldd	r13, Z+1	; 0x01
    4872:	96 fe       	sbrs	r9, 6
    4874:	03 c0       	rjmp	.+6      	; 0x487c <vfprintf+0x420>
    4876:	61 2f       	mov	r22, r17
    4878:	70 e0       	ldi	r23, 0x00	; 0
    487a:	02 c0       	rjmp	.+4      	; 0x4880 <vfprintf+0x424>
    487c:	6f ef       	ldi	r22, 0xFF	; 255
    487e:	7f ef       	ldi	r23, 0xFF	; 255
    4880:	c6 01       	movw	r24, r12
    4882:	0e 94 ea 27 	call	0x4fd4	; 0x4fd4 <strnlen>
    4886:	8c 01       	movw	r16, r24
    4888:	f9 2d       	mov	r31, r9
    488a:	ff 77       	andi	r31, 0x7F	; 127
    488c:	14 c0       	rjmp	.+40     	; 0x48b6 <vfprintf+0x45a>
    488e:	56 01       	movw	r10, r12
    4890:	22 e0       	ldi	r18, 0x02	; 2
    4892:	a2 0e       	add	r10, r18
    4894:	b1 1c       	adc	r11, r1
    4896:	f6 01       	movw	r30, r12
    4898:	c0 80       	ld	r12, Z
    489a:	d1 80       	ldd	r13, Z+1	; 0x01
    489c:	96 fe       	sbrs	r9, 6
    489e:	03 c0       	rjmp	.+6      	; 0x48a6 <vfprintf+0x44a>
    48a0:	61 2f       	mov	r22, r17
    48a2:	70 e0       	ldi	r23, 0x00	; 0
    48a4:	02 c0       	rjmp	.+4      	; 0x48aa <vfprintf+0x44e>
    48a6:	6f ef       	ldi	r22, 0xFF	; 255
    48a8:	7f ef       	ldi	r23, 0xFF	; 255
    48aa:	c6 01       	movw	r24, r12
    48ac:	0e 94 df 27 	call	0x4fbe	; 0x4fbe <strnlen_P>
    48b0:	8c 01       	movw	r16, r24
    48b2:	f9 2d       	mov	r31, r9
    48b4:	f0 68       	ori	r31, 0x80	; 128
    48b6:	9f 2e       	mov	r9, r31
    48b8:	f3 fd       	sbrc	r31, 3
    48ba:	1a c0       	rjmp	.+52     	; 0x48f0 <vfprintf+0x494>
    48bc:	85 2d       	mov	r24, r5
    48be:	90 e0       	ldi	r25, 0x00	; 0
    48c0:	08 17       	cp	r16, r24
    48c2:	19 07       	cpc	r17, r25
    48c4:	a8 f4       	brcc	.+42     	; 0x48f0 <vfprintf+0x494>
    48c6:	b7 01       	movw	r22, r14
    48c8:	80 e2       	ldi	r24, 0x20	; 32
    48ca:	90 e0       	ldi	r25, 0x00	; 0
    48cc:	0e 94 f5 27 	call	0x4fea	; 0x4fea <fputc>
    48d0:	5a 94       	dec	r5
    48d2:	f4 cf       	rjmp	.-24     	; 0x48bc <vfprintf+0x460>
    48d4:	f6 01       	movw	r30, r12
    48d6:	97 fc       	sbrc	r9, 7
    48d8:	85 91       	lpm	r24, Z+
    48da:	97 fe       	sbrs	r9, 7
    48dc:	81 91       	ld	r24, Z+
    48de:	6f 01       	movw	r12, r30
    48e0:	b7 01       	movw	r22, r14
    48e2:	90 e0       	ldi	r25, 0x00	; 0
    48e4:	0e 94 f5 27 	call	0x4fea	; 0x4fea <fputc>
    48e8:	51 10       	cpse	r5, r1
    48ea:	5a 94       	dec	r5
    48ec:	01 50       	subi	r16, 0x01	; 1
    48ee:	11 09       	sbc	r17, r1
    48f0:	01 15       	cp	r16, r1
    48f2:	11 05       	cpc	r17, r1
    48f4:	79 f7       	brne	.-34     	; 0x48d4 <vfprintf+0x478>
    48f6:	f7 c0       	rjmp	.+494    	; 0x4ae6 <vfprintf+0x68a>
    48f8:	84 36       	cpi	r24, 0x64	; 100
    48fa:	11 f0       	breq	.+4      	; 0x4900 <vfprintf+0x4a4>
    48fc:	89 36       	cpi	r24, 0x69	; 105
    48fe:	61 f5       	brne	.+88     	; 0x4958 <vfprintf+0x4fc>
    4900:	56 01       	movw	r10, r12
    4902:	97 fe       	sbrs	r9, 7
    4904:	09 c0       	rjmp	.+18     	; 0x4918 <vfprintf+0x4bc>
    4906:	24 e0       	ldi	r18, 0x04	; 4
    4908:	a2 0e       	add	r10, r18
    490a:	b1 1c       	adc	r11, r1
    490c:	f6 01       	movw	r30, r12
    490e:	60 81       	ld	r22, Z
    4910:	71 81       	ldd	r23, Z+1	; 0x01
    4912:	82 81       	ldd	r24, Z+2	; 0x02
    4914:	93 81       	ldd	r25, Z+3	; 0x03
    4916:	0a c0       	rjmp	.+20     	; 0x492c <vfprintf+0x4d0>
    4918:	f2 e0       	ldi	r31, 0x02	; 2
    491a:	af 0e       	add	r10, r31
    491c:	b1 1c       	adc	r11, r1
    491e:	f6 01       	movw	r30, r12
    4920:	60 81       	ld	r22, Z
    4922:	71 81       	ldd	r23, Z+1	; 0x01
    4924:	07 2e       	mov	r0, r23
    4926:	00 0c       	add	r0, r0
    4928:	88 0b       	sbc	r24, r24
    492a:	99 0b       	sbc	r25, r25
    492c:	f9 2d       	mov	r31, r9
    492e:	ff 76       	andi	r31, 0x6F	; 111
    4930:	9f 2e       	mov	r9, r31
    4932:	97 ff       	sbrs	r25, 7
    4934:	09 c0       	rjmp	.+18     	; 0x4948 <vfprintf+0x4ec>
    4936:	90 95       	com	r25
    4938:	80 95       	com	r24
    493a:	70 95       	com	r23
    493c:	61 95       	neg	r22
    493e:	7f 4f       	sbci	r23, 0xFF	; 255
    4940:	8f 4f       	sbci	r24, 0xFF	; 255
    4942:	9f 4f       	sbci	r25, 0xFF	; 255
    4944:	f0 68       	ori	r31, 0x80	; 128
    4946:	9f 2e       	mov	r9, r31
    4948:	2a e0       	ldi	r18, 0x0A	; 10
    494a:	30 e0       	ldi	r19, 0x00	; 0
    494c:	a3 01       	movw	r20, r6
    494e:	0e 94 8d 28 	call	0x511a	; 0x511a <__ultoa_invert>
    4952:	c8 2e       	mov	r12, r24
    4954:	c6 18       	sub	r12, r6
    4956:	3f c0       	rjmp	.+126    	; 0x49d6 <vfprintf+0x57a>
    4958:	09 2d       	mov	r16, r9
    495a:	85 37       	cpi	r24, 0x75	; 117
    495c:	21 f4       	brne	.+8      	; 0x4966 <vfprintf+0x50a>
    495e:	0f 7e       	andi	r16, 0xEF	; 239
    4960:	2a e0       	ldi	r18, 0x0A	; 10
    4962:	30 e0       	ldi	r19, 0x00	; 0
    4964:	1d c0       	rjmp	.+58     	; 0x49a0 <vfprintf+0x544>
    4966:	09 7f       	andi	r16, 0xF9	; 249
    4968:	8f 36       	cpi	r24, 0x6F	; 111
    496a:	91 f0       	breq	.+36     	; 0x4990 <vfprintf+0x534>
    496c:	18 f4       	brcc	.+6      	; 0x4974 <vfprintf+0x518>
    496e:	88 35       	cpi	r24, 0x58	; 88
    4970:	59 f0       	breq	.+22     	; 0x4988 <vfprintf+0x52c>
    4972:	c3 c0       	rjmp	.+390    	; 0x4afa <vfprintf+0x69e>
    4974:	80 37       	cpi	r24, 0x70	; 112
    4976:	19 f0       	breq	.+6      	; 0x497e <vfprintf+0x522>
    4978:	88 37       	cpi	r24, 0x78	; 120
    497a:	11 f0       	breq	.+4      	; 0x4980 <vfprintf+0x524>
    497c:	be c0       	rjmp	.+380    	; 0x4afa <vfprintf+0x69e>
    497e:	00 61       	ori	r16, 0x10	; 16
    4980:	04 ff       	sbrs	r16, 4
    4982:	09 c0       	rjmp	.+18     	; 0x4996 <vfprintf+0x53a>
    4984:	04 60       	ori	r16, 0x04	; 4
    4986:	07 c0       	rjmp	.+14     	; 0x4996 <vfprintf+0x53a>
    4988:	94 fe       	sbrs	r9, 4
    498a:	08 c0       	rjmp	.+16     	; 0x499c <vfprintf+0x540>
    498c:	06 60       	ori	r16, 0x06	; 6
    498e:	06 c0       	rjmp	.+12     	; 0x499c <vfprintf+0x540>
    4990:	28 e0       	ldi	r18, 0x08	; 8
    4992:	30 e0       	ldi	r19, 0x00	; 0
    4994:	05 c0       	rjmp	.+10     	; 0x49a0 <vfprintf+0x544>
    4996:	20 e1       	ldi	r18, 0x10	; 16
    4998:	30 e0       	ldi	r19, 0x00	; 0
    499a:	02 c0       	rjmp	.+4      	; 0x49a0 <vfprintf+0x544>
    499c:	20 e1       	ldi	r18, 0x10	; 16
    499e:	32 e0       	ldi	r19, 0x02	; 2
    49a0:	56 01       	movw	r10, r12
    49a2:	07 ff       	sbrs	r16, 7
    49a4:	09 c0       	rjmp	.+18     	; 0x49b8 <vfprintf+0x55c>
    49a6:	84 e0       	ldi	r24, 0x04	; 4
    49a8:	a8 0e       	add	r10, r24
    49aa:	b1 1c       	adc	r11, r1
    49ac:	f6 01       	movw	r30, r12
    49ae:	60 81       	ld	r22, Z
    49b0:	71 81       	ldd	r23, Z+1	; 0x01
    49b2:	82 81       	ldd	r24, Z+2	; 0x02
    49b4:	93 81       	ldd	r25, Z+3	; 0x03
    49b6:	08 c0       	rjmp	.+16     	; 0x49c8 <vfprintf+0x56c>
    49b8:	f2 e0       	ldi	r31, 0x02	; 2
    49ba:	af 0e       	add	r10, r31
    49bc:	b1 1c       	adc	r11, r1
    49be:	f6 01       	movw	r30, r12
    49c0:	60 81       	ld	r22, Z
    49c2:	71 81       	ldd	r23, Z+1	; 0x01
    49c4:	80 e0       	ldi	r24, 0x00	; 0
    49c6:	90 e0       	ldi	r25, 0x00	; 0
    49c8:	a3 01       	movw	r20, r6
    49ca:	0e 94 8d 28 	call	0x511a	; 0x511a <__ultoa_invert>
    49ce:	c8 2e       	mov	r12, r24
    49d0:	c6 18       	sub	r12, r6
    49d2:	0f 77       	andi	r16, 0x7F	; 127
    49d4:	90 2e       	mov	r9, r16
    49d6:	96 fe       	sbrs	r9, 6
    49d8:	0b c0       	rjmp	.+22     	; 0x49f0 <vfprintf+0x594>
    49da:	09 2d       	mov	r16, r9
    49dc:	0e 7f       	andi	r16, 0xFE	; 254
    49de:	c1 16       	cp	r12, r17
    49e0:	50 f4       	brcc	.+20     	; 0x49f6 <vfprintf+0x59a>
    49e2:	94 fe       	sbrs	r9, 4
    49e4:	0a c0       	rjmp	.+20     	; 0x49fa <vfprintf+0x59e>
    49e6:	92 fc       	sbrc	r9, 2
    49e8:	08 c0       	rjmp	.+16     	; 0x49fa <vfprintf+0x59e>
    49ea:	09 2d       	mov	r16, r9
    49ec:	0e 7e       	andi	r16, 0xEE	; 238
    49ee:	05 c0       	rjmp	.+10     	; 0x49fa <vfprintf+0x59e>
    49f0:	dc 2c       	mov	r13, r12
    49f2:	09 2d       	mov	r16, r9
    49f4:	03 c0       	rjmp	.+6      	; 0x49fc <vfprintf+0x5a0>
    49f6:	dc 2c       	mov	r13, r12
    49f8:	01 c0       	rjmp	.+2      	; 0x49fc <vfprintf+0x5a0>
    49fa:	d1 2e       	mov	r13, r17
    49fc:	04 ff       	sbrs	r16, 4
    49fe:	0d c0       	rjmp	.+26     	; 0x4a1a <vfprintf+0x5be>
    4a00:	fe 01       	movw	r30, r28
    4a02:	ec 0d       	add	r30, r12
    4a04:	f1 1d       	adc	r31, r1
    4a06:	80 81       	ld	r24, Z
    4a08:	80 33       	cpi	r24, 0x30	; 48
    4a0a:	11 f4       	brne	.+4      	; 0x4a10 <vfprintf+0x5b4>
    4a0c:	09 7e       	andi	r16, 0xE9	; 233
    4a0e:	09 c0       	rjmp	.+18     	; 0x4a22 <vfprintf+0x5c6>
    4a10:	02 ff       	sbrs	r16, 2
    4a12:	06 c0       	rjmp	.+12     	; 0x4a20 <vfprintf+0x5c4>
    4a14:	d3 94       	inc	r13
    4a16:	d3 94       	inc	r13
    4a18:	04 c0       	rjmp	.+8      	; 0x4a22 <vfprintf+0x5c6>
    4a1a:	80 2f       	mov	r24, r16
    4a1c:	86 78       	andi	r24, 0x86	; 134
    4a1e:	09 f0       	breq	.+2      	; 0x4a22 <vfprintf+0x5c6>
    4a20:	d3 94       	inc	r13
    4a22:	03 fd       	sbrc	r16, 3
    4a24:	11 c0       	rjmp	.+34     	; 0x4a48 <vfprintf+0x5ec>
    4a26:	00 ff       	sbrs	r16, 0
    4a28:	06 c0       	rjmp	.+12     	; 0x4a36 <vfprintf+0x5da>
    4a2a:	1c 2d       	mov	r17, r12
    4a2c:	d5 14       	cp	r13, r5
    4a2e:	80 f4       	brcc	.+32     	; 0x4a50 <vfprintf+0x5f4>
    4a30:	15 0d       	add	r17, r5
    4a32:	1d 19       	sub	r17, r13
    4a34:	0d c0       	rjmp	.+26     	; 0x4a50 <vfprintf+0x5f4>
    4a36:	d5 14       	cp	r13, r5
    4a38:	58 f4       	brcc	.+22     	; 0x4a50 <vfprintf+0x5f4>
    4a3a:	b7 01       	movw	r22, r14
    4a3c:	80 e2       	ldi	r24, 0x20	; 32
    4a3e:	90 e0       	ldi	r25, 0x00	; 0
    4a40:	0e 94 f5 27 	call	0x4fea	; 0x4fea <fputc>
    4a44:	d3 94       	inc	r13
    4a46:	f7 cf       	rjmp	.-18     	; 0x4a36 <vfprintf+0x5da>
    4a48:	d5 14       	cp	r13, r5
    4a4a:	10 f4       	brcc	.+4      	; 0x4a50 <vfprintf+0x5f4>
    4a4c:	5d 18       	sub	r5, r13
    4a4e:	01 c0       	rjmp	.+2      	; 0x4a52 <vfprintf+0x5f6>
    4a50:	51 2c       	mov	r5, r1
    4a52:	04 ff       	sbrs	r16, 4
    4a54:	10 c0       	rjmp	.+32     	; 0x4a76 <vfprintf+0x61a>
    4a56:	b7 01       	movw	r22, r14
    4a58:	80 e3       	ldi	r24, 0x30	; 48
    4a5a:	90 e0       	ldi	r25, 0x00	; 0
    4a5c:	0e 94 f5 27 	call	0x4fea	; 0x4fea <fputc>
    4a60:	02 ff       	sbrs	r16, 2
    4a62:	17 c0       	rjmp	.+46     	; 0x4a92 <vfprintf+0x636>
    4a64:	01 fd       	sbrc	r16, 1
    4a66:	03 c0       	rjmp	.+6      	; 0x4a6e <vfprintf+0x612>
    4a68:	88 e7       	ldi	r24, 0x78	; 120
    4a6a:	90 e0       	ldi	r25, 0x00	; 0
    4a6c:	02 c0       	rjmp	.+4      	; 0x4a72 <vfprintf+0x616>
    4a6e:	88 e5       	ldi	r24, 0x58	; 88
    4a70:	90 e0       	ldi	r25, 0x00	; 0
    4a72:	b7 01       	movw	r22, r14
    4a74:	0c c0       	rjmp	.+24     	; 0x4a8e <vfprintf+0x632>
    4a76:	80 2f       	mov	r24, r16
    4a78:	86 78       	andi	r24, 0x86	; 134
    4a7a:	59 f0       	breq	.+22     	; 0x4a92 <vfprintf+0x636>
    4a7c:	01 ff       	sbrs	r16, 1
    4a7e:	02 c0       	rjmp	.+4      	; 0x4a84 <vfprintf+0x628>
    4a80:	8b e2       	ldi	r24, 0x2B	; 43
    4a82:	01 c0       	rjmp	.+2      	; 0x4a86 <vfprintf+0x62a>
    4a84:	80 e2       	ldi	r24, 0x20	; 32
    4a86:	07 fd       	sbrc	r16, 7
    4a88:	8d e2       	ldi	r24, 0x2D	; 45
    4a8a:	b7 01       	movw	r22, r14
    4a8c:	90 e0       	ldi	r25, 0x00	; 0
    4a8e:	0e 94 f5 27 	call	0x4fea	; 0x4fea <fputc>
    4a92:	c1 16       	cp	r12, r17
    4a94:	38 f4       	brcc	.+14     	; 0x4aa4 <vfprintf+0x648>
    4a96:	b7 01       	movw	r22, r14
    4a98:	80 e3       	ldi	r24, 0x30	; 48
    4a9a:	90 e0       	ldi	r25, 0x00	; 0
    4a9c:	0e 94 f5 27 	call	0x4fea	; 0x4fea <fputc>
    4aa0:	11 50       	subi	r17, 0x01	; 1
    4aa2:	f7 cf       	rjmp	.-18     	; 0x4a92 <vfprintf+0x636>
    4aa4:	ca 94       	dec	r12
    4aa6:	f3 01       	movw	r30, r6
    4aa8:	ec 0d       	add	r30, r12
    4aaa:	f1 1d       	adc	r31, r1
    4aac:	80 81       	ld	r24, Z
    4aae:	b7 01       	movw	r22, r14
    4ab0:	90 e0       	ldi	r25, 0x00	; 0
    4ab2:	0e 94 f5 27 	call	0x4fea	; 0x4fea <fputc>
    4ab6:	c1 10       	cpse	r12, r1
    4ab8:	f5 cf       	rjmp	.-22     	; 0x4aa4 <vfprintf+0x648>
    4aba:	15 c0       	rjmp	.+42     	; 0x4ae6 <vfprintf+0x68a>
    4abc:	f4 e0       	ldi	r31, 0x04	; 4
    4abe:	f5 15       	cp	r31, r5
    4ac0:	60 f5       	brcc	.+88     	; 0x4b1a <vfprintf+0x6be>
    4ac2:	84 e0       	ldi	r24, 0x04	; 4
    4ac4:	58 1a       	sub	r5, r24
    4ac6:	93 fe       	sbrs	r9, 3
    4ac8:	1f c0       	rjmp	.+62     	; 0x4b08 <vfprintf+0x6ac>
    4aca:	01 11       	cpse	r16, r1
    4acc:	27 c0       	rjmp	.+78     	; 0x4b1c <vfprintf+0x6c0>
    4ace:	2c 85       	ldd	r18, Y+12	; 0x0c
    4ad0:	23 ff       	sbrs	r18, 3
    4ad2:	2a c0       	rjmp	.+84     	; 0x4b28 <vfprintf+0x6cc>
    4ad4:	02 ec       	ldi	r16, 0xC2	; 194
    4ad6:	10 e0       	ldi	r17, 0x00	; 0
    4ad8:	39 2d       	mov	r19, r9
    4ada:	30 71       	andi	r19, 0x10	; 16
    4adc:	93 2e       	mov	r9, r19
    4ade:	f8 01       	movw	r30, r16
    4ae0:	84 91       	lpm	r24, Z
    4ae2:	81 11       	cpse	r24, r1
    4ae4:	24 c0       	rjmp	.+72     	; 0x4b2e <vfprintf+0x6d2>
    4ae6:	55 20       	and	r5, r5
    4ae8:	09 f4       	brne	.+2      	; 0x4aec <vfprintf+0x690>
    4aea:	e4 cc       	rjmp	.-1592   	; 0x44b4 <vfprintf+0x58>
    4aec:	b7 01       	movw	r22, r14
    4aee:	80 e2       	ldi	r24, 0x20	; 32
    4af0:	90 e0       	ldi	r25, 0x00	; 0
    4af2:	0e 94 f5 27 	call	0x4fea	; 0x4fea <fputc>
    4af6:	5a 94       	dec	r5
    4af8:	f6 cf       	rjmp	.-20     	; 0x4ae6 <vfprintf+0x68a>
    4afa:	f7 01       	movw	r30, r14
    4afc:	86 81       	ldd	r24, Z+6	; 0x06
    4afe:	97 81       	ldd	r25, Z+7	; 0x07
    4b00:	26 c0       	rjmp	.+76     	; 0x4b4e <vfprintf+0x6f2>
    4b02:	8f ef       	ldi	r24, 0xFF	; 255
    4b04:	9f ef       	ldi	r25, 0xFF	; 255
    4b06:	23 c0       	rjmp	.+70     	; 0x4b4e <vfprintf+0x6f2>
    4b08:	b7 01       	movw	r22, r14
    4b0a:	80 e2       	ldi	r24, 0x20	; 32
    4b0c:	90 e0       	ldi	r25, 0x00	; 0
    4b0e:	0e 94 f5 27 	call	0x4fea	; 0x4fea <fputc>
    4b12:	5a 94       	dec	r5
    4b14:	51 10       	cpse	r5, r1
    4b16:	f8 cf       	rjmp	.-16     	; 0x4b08 <vfprintf+0x6ac>
    4b18:	d8 cf       	rjmp	.-80     	; 0x4aca <vfprintf+0x66e>
    4b1a:	51 2c       	mov	r5, r1
    4b1c:	b7 01       	movw	r22, r14
    4b1e:	80 2f       	mov	r24, r16
    4b20:	90 e0       	ldi	r25, 0x00	; 0
    4b22:	0e 94 f5 27 	call	0x4fea	; 0x4fea <fputc>
    4b26:	d3 cf       	rjmp	.-90     	; 0x4ace <vfprintf+0x672>
    4b28:	06 ec       	ldi	r16, 0xC6	; 198
    4b2a:	10 e0       	ldi	r17, 0x00	; 0
    4b2c:	d5 cf       	rjmp	.-86     	; 0x4ad8 <vfprintf+0x67c>
    4b2e:	91 10       	cpse	r9, r1
    4b30:	80 52       	subi	r24, 0x20	; 32
    4b32:	b7 01       	movw	r22, r14
    4b34:	90 e0       	ldi	r25, 0x00	; 0
    4b36:	0e 94 f5 27 	call	0x4fea	; 0x4fea <fputc>
    4b3a:	0f 5f       	subi	r16, 0xFF	; 255
    4b3c:	1f 4f       	sbci	r17, 0xFF	; 255
    4b3e:	cf cf       	rjmp	.-98     	; 0x4ade <vfprintf+0x682>
    4b40:	23 e0       	ldi	r18, 0x03	; 3
    4b42:	25 15       	cp	r18, r5
    4b44:	10 f4       	brcc	.+4      	; 0x4b4a <vfprintf+0x6ee>
    4b46:	83 e0       	ldi	r24, 0x03	; 3
    4b48:	bd cf       	rjmp	.-134    	; 0x4ac4 <vfprintf+0x668>
    4b4a:	51 2c       	mov	r5, r1
    4b4c:	c0 cf       	rjmp	.-128    	; 0x4ace <vfprintf+0x672>
    4b4e:	60 96       	adiw	r28, 0x10	; 16
    4b50:	e2 e1       	ldi	r30, 0x12	; 18
    4b52:	0c 94 c7 25 	jmp	0x4b8e	; 0x4b8e <__epilogue_restores__>

00004b56 <__prologue_saves__>:
    4b56:	2f 92       	push	r2
    4b58:	3f 92       	push	r3
    4b5a:	4f 92       	push	r4
    4b5c:	5f 92       	push	r5
    4b5e:	6f 92       	push	r6
    4b60:	7f 92       	push	r7
    4b62:	8f 92       	push	r8
    4b64:	9f 92       	push	r9
    4b66:	af 92       	push	r10
    4b68:	bf 92       	push	r11
    4b6a:	cf 92       	push	r12
    4b6c:	df 92       	push	r13
    4b6e:	ef 92       	push	r14
    4b70:	ff 92       	push	r15
    4b72:	0f 93       	push	r16
    4b74:	1f 93       	push	r17
    4b76:	cf 93       	push	r28
    4b78:	df 93       	push	r29
    4b7a:	cd b7       	in	r28, 0x3d	; 61
    4b7c:	de b7       	in	r29, 0x3e	; 62
    4b7e:	ca 1b       	sub	r28, r26
    4b80:	db 0b       	sbc	r29, r27
    4b82:	0f b6       	in	r0, 0x3f	; 63
    4b84:	f8 94       	cli
    4b86:	de bf       	out	0x3e, r29	; 62
    4b88:	0f be       	out	0x3f, r0	; 63
    4b8a:	cd bf       	out	0x3d, r28	; 61
    4b8c:	09 94       	ijmp

00004b8e <__epilogue_restores__>:
    4b8e:	2a 88       	ldd	r2, Y+18	; 0x12
    4b90:	39 88       	ldd	r3, Y+17	; 0x11
    4b92:	48 88       	ldd	r4, Y+16	; 0x10
    4b94:	5f 84       	ldd	r5, Y+15	; 0x0f
    4b96:	6e 84       	ldd	r6, Y+14	; 0x0e
    4b98:	7d 84       	ldd	r7, Y+13	; 0x0d
    4b9a:	8c 84       	ldd	r8, Y+12	; 0x0c
    4b9c:	9b 84       	ldd	r9, Y+11	; 0x0b
    4b9e:	aa 84       	ldd	r10, Y+10	; 0x0a
    4ba0:	b9 84       	ldd	r11, Y+9	; 0x09
    4ba2:	c8 84       	ldd	r12, Y+8	; 0x08
    4ba4:	df 80       	ldd	r13, Y+7	; 0x07
    4ba6:	ee 80       	ldd	r14, Y+6	; 0x06
    4ba8:	fd 80       	ldd	r15, Y+5	; 0x05
    4baa:	0c 81       	ldd	r16, Y+4	; 0x04
    4bac:	1b 81       	ldd	r17, Y+3	; 0x03
    4bae:	aa 81       	ldd	r26, Y+2	; 0x02
    4bb0:	b9 81       	ldd	r27, Y+1	; 0x01
    4bb2:	ce 0f       	add	r28, r30
    4bb4:	d1 1d       	adc	r29, r1
    4bb6:	0f b6       	in	r0, 0x3f	; 63
    4bb8:	f8 94       	cli
    4bba:	de bf       	out	0x3e, r29	; 62
    4bbc:	0f be       	out	0x3f, r0	; 63
    4bbe:	cd bf       	out	0x3d, r28	; 61
    4bc0:	ed 01       	movw	r28, r26
    4bc2:	08 95       	ret

00004bc4 <strtoul>:
    4bc4:	a0 e0       	ldi	r26, 0x00	; 0
    4bc6:	b0 e0       	ldi	r27, 0x00	; 0
    4bc8:	e8 ee       	ldi	r30, 0xE8	; 232
    4bca:	f5 e2       	ldi	r31, 0x25	; 37
    4bcc:	0c 94 ac 25 	jmp	0x4b58	; 0x4b58 <__prologue_saves__+0x2>
    4bd0:	5c 01       	movw	r10, r24
    4bd2:	6b 01       	movw	r12, r22
    4bd4:	7a 01       	movw	r14, r20
    4bd6:	61 15       	cp	r22, r1
    4bd8:	71 05       	cpc	r23, r1
    4bda:	19 f0       	breq	.+6      	; 0x4be2 <strtoul+0x1e>
    4bdc:	fb 01       	movw	r30, r22
    4bde:	91 83       	std	Z+1, r25	; 0x01
    4be0:	80 83       	st	Z, r24
    4be2:	e1 14       	cp	r14, r1
    4be4:	f1 04       	cpc	r15, r1
    4be6:	29 f0       	breq	.+10     	; 0x4bf2 <strtoul+0x2e>
    4be8:	c7 01       	movw	r24, r14
    4bea:	02 97       	sbiw	r24, 0x02	; 2
    4bec:	83 97       	sbiw	r24, 0x23	; 35
    4bee:	08 f0       	brcs	.+2      	; 0x4bf2 <strtoul+0x2e>
    4bf0:	c9 c0       	rjmp	.+402    	; 0x4d84 <strtoul+0x1c0>
    4bf2:	e5 01       	movw	r28, r10
    4bf4:	21 96       	adiw	r28, 0x01	; 1
    4bf6:	f5 01       	movw	r30, r10
    4bf8:	10 81       	ld	r17, Z
    4bfa:	81 2f       	mov	r24, r17
    4bfc:	90 e0       	ldi	r25, 0x00	; 0
    4bfe:	0e 94 af 27 	call	0x4f5e	; 0x4f5e <isspace>
    4c02:	89 2b       	or	r24, r25
    4c04:	11 f0       	breq	.+4      	; 0x4c0a <strtoul+0x46>
    4c06:	5e 01       	movw	r10, r28
    4c08:	f4 cf       	rjmp	.-24     	; 0x4bf2 <strtoul+0x2e>
    4c0a:	1d 32       	cpi	r17, 0x2D	; 45
    4c0c:	29 f4       	brne	.+10     	; 0x4c18 <strtoul+0x54>
    4c0e:	21 96       	adiw	r28, 0x01	; 1
    4c10:	f5 01       	movw	r30, r10
    4c12:	11 81       	ldd	r17, Z+1	; 0x01
    4c14:	01 e0       	ldi	r16, 0x01	; 1
    4c16:	07 c0       	rjmp	.+14     	; 0x4c26 <strtoul+0x62>
    4c18:	1b 32       	cpi	r17, 0x2B	; 43
    4c1a:	21 f4       	brne	.+8      	; 0x4c24 <strtoul+0x60>
    4c1c:	e5 01       	movw	r28, r10
    4c1e:	22 96       	adiw	r28, 0x02	; 2
    4c20:	f5 01       	movw	r30, r10
    4c22:	11 81       	ldd	r17, Z+1	; 0x01
    4c24:	00 e0       	ldi	r16, 0x00	; 0
    4c26:	e1 14       	cp	r14, r1
    4c28:	f1 04       	cpc	r15, r1
    4c2a:	b1 f0       	breq	.+44     	; 0x4c58 <strtoul+0x94>
    4c2c:	f0 e1       	ldi	r31, 0x10	; 16
    4c2e:	ef 16       	cp	r14, r31
    4c30:	f1 04       	cpc	r15, r1
    4c32:	29 f4       	brne	.+10     	; 0x4c3e <strtoul+0x7a>
    4c34:	b0 c0       	rjmp	.+352    	; 0x4d96 <strtoul+0x1d2>
    4c36:	10 e3       	ldi	r17, 0x30	; 48
    4c38:	e1 14       	cp	r14, r1
    4c3a:	f1 04       	cpc	r15, r1
    4c3c:	01 f1       	breq	.+64     	; 0x4c7e <strtoul+0xba>
    4c3e:	2a e0       	ldi	r18, 0x0A	; 10
    4c40:	e2 16       	cp	r14, r18
    4c42:	f1 04       	cpc	r15, r1
    4c44:	b1 f1       	breq	.+108    	; 0x4cb2 <strtoul+0xee>
    4c46:	80 e1       	ldi	r24, 0x10	; 16
    4c48:	e8 16       	cp	r14, r24
    4c4a:	f1 04       	cpc	r15, r1
    4c4c:	71 f0       	breq	.+28     	; 0x4c6a <strtoul+0xa6>
    4c4e:	e8 e0       	ldi	r30, 0x08	; 8
    4c50:	ee 16       	cp	r14, r30
    4c52:	f1 04       	cpc	r15, r1
    4c54:	f1 f4       	brne	.+60     	; 0x4c92 <strtoul+0xce>
    4c56:	13 c0       	rjmp	.+38     	; 0x4c7e <strtoul+0xba>
    4c58:	10 33       	cpi	r17, 0x30	; 48
    4c5a:	41 f5       	brne	.+80     	; 0x4cac <strtoul+0xe8>
    4c5c:	88 81       	ld	r24, Y
    4c5e:	8f 7d       	andi	r24, 0xDF	; 223
    4c60:	88 35       	cpi	r24, 0x58	; 88
    4c62:	49 f7       	brne	.-46     	; 0x4c36 <strtoul+0x72>
    4c64:	19 81       	ldd	r17, Y+1	; 0x01
    4c66:	22 96       	adiw	r28, 0x02	; 2
    4c68:	02 60       	ori	r16, 0x02	; 2
    4c6a:	f0 e1       	ldi	r31, 0x10	; 16
    4c6c:	ef 2e       	mov	r14, r31
    4c6e:	f1 2c       	mov	r15, r1
    4c70:	88 24       	eor	r8, r8
    4c72:	8a 94       	dec	r8
    4c74:	98 2c       	mov	r9, r8
    4c76:	a8 2c       	mov	r10, r8
    4c78:	af e0       	ldi	r26, 0x0F	; 15
    4c7a:	ba 2e       	mov	r11, r26
    4c7c:	20 c0       	rjmp	.+64     	; 0x4cbe <strtoul+0xfa>
    4c7e:	78 e0       	ldi	r23, 0x08	; 8
    4c80:	e7 2e       	mov	r14, r23
    4c82:	f1 2c       	mov	r15, r1
    4c84:	88 24       	eor	r8, r8
    4c86:	8a 94       	dec	r8
    4c88:	98 2c       	mov	r9, r8
    4c8a:	a8 2c       	mov	r10, r8
    4c8c:	ef e1       	ldi	r30, 0x1F	; 31
    4c8e:	be 2e       	mov	r11, r30
    4c90:	16 c0       	rjmp	.+44     	; 0x4cbe <strtoul+0xfa>
    4c92:	6f ef       	ldi	r22, 0xFF	; 255
    4c94:	7f ef       	ldi	r23, 0xFF	; 255
    4c96:	cb 01       	movw	r24, r22
    4c98:	97 01       	movw	r18, r14
    4c9a:	0f 2c       	mov	r0, r15
    4c9c:	00 0c       	add	r0, r0
    4c9e:	44 0b       	sbc	r20, r20
    4ca0:	55 0b       	sbc	r21, r21
    4ca2:	0e 94 38 2a 	call	0x5470	; 0x5470 <__udivmodsi4>
    4ca6:	49 01       	movw	r8, r18
    4ca8:	5a 01       	movw	r10, r20
    4caa:	09 c0       	rjmp	.+18     	; 0x4cbe <strtoul+0xfa>
    4cac:	8a e0       	ldi	r24, 0x0A	; 10
    4cae:	e8 2e       	mov	r14, r24
    4cb0:	f1 2c       	mov	r15, r1
    4cb2:	69 e9       	ldi	r22, 0x99	; 153
    4cb4:	86 2e       	mov	r8, r22
    4cb6:	98 2c       	mov	r9, r8
    4cb8:	a8 2c       	mov	r10, r8
    4cba:	69 e1       	ldi	r22, 0x19	; 25
    4cbc:	b6 2e       	mov	r11, r22
    4cbe:	40 e0       	ldi	r20, 0x00	; 0
    4cc0:	60 e0       	ldi	r22, 0x00	; 0
    4cc2:	70 e0       	ldi	r23, 0x00	; 0
    4cc4:	cb 01       	movw	r24, r22
    4cc6:	27 01       	movw	r4, r14
    4cc8:	0f 2c       	mov	r0, r15
    4cca:	00 0c       	add	r0, r0
    4ccc:	66 08       	sbc	r6, r6
    4cce:	77 08       	sbc	r7, r7
    4cd0:	fe 01       	movw	r30, r28
    4cd2:	50 ed       	ldi	r21, 0xD0	; 208
    4cd4:	35 2e       	mov	r3, r21
    4cd6:	31 0e       	add	r3, r17
    4cd8:	29 e0       	ldi	r18, 0x09	; 9
    4cda:	23 15       	cp	r18, r3
    4cdc:	70 f4       	brcc	.+28     	; 0x4cfa <strtoul+0x136>
    4cde:	2f eb       	ldi	r18, 0xBF	; 191
    4ce0:	21 0f       	add	r18, r17
    4ce2:	2a 31       	cpi	r18, 0x1A	; 26
    4ce4:	18 f4       	brcc	.+6      	; 0x4cec <strtoul+0x128>
    4ce6:	39 ec       	ldi	r19, 0xC9	; 201
    4ce8:	33 2e       	mov	r3, r19
    4cea:	06 c0       	rjmp	.+12     	; 0x4cf8 <strtoul+0x134>
    4cec:	2f e9       	ldi	r18, 0x9F	; 159
    4cee:	21 0f       	add	r18, r17
    4cf0:	2a 31       	cpi	r18, 0x1A	; 26
    4cf2:	30 f5       	brcc	.+76     	; 0x4d40 <strtoul+0x17c>
    4cf4:	29 ea       	ldi	r18, 0xA9	; 169
    4cf6:	32 2e       	mov	r3, r18
    4cf8:	31 0e       	add	r3, r17
    4cfa:	23 2d       	mov	r18, r3
    4cfc:	30 e0       	ldi	r19, 0x00	; 0
    4cfe:	2e 15       	cp	r18, r14
    4d00:	3f 05       	cpc	r19, r15
    4d02:	f4 f4       	brge	.+60     	; 0x4d40 <strtoul+0x17c>
    4d04:	4f 3f       	cpi	r20, 0xFF	; 255
    4d06:	c9 f0       	breq	.+50     	; 0x4d3a <strtoul+0x176>
    4d08:	86 16       	cp	r8, r22
    4d0a:	97 06       	cpc	r9, r23
    4d0c:	a8 06       	cpc	r10, r24
    4d0e:	b9 06       	cpc	r11, r25
    4d10:	88 f0       	brcs	.+34     	; 0x4d34 <strtoul+0x170>
    4d12:	a3 01       	movw	r20, r6
    4d14:	92 01       	movw	r18, r4
    4d16:	0e 94 28 2a 	call	0x5450	; 0x5450 <__mulsi3>
    4d1a:	23 2d       	mov	r18, r3
    4d1c:	30 e0       	ldi	r19, 0x00	; 0
    4d1e:	40 e0       	ldi	r20, 0x00	; 0
    4d20:	50 e0       	ldi	r21, 0x00	; 0
    4d22:	62 0f       	add	r22, r18
    4d24:	73 1f       	adc	r23, r19
    4d26:	84 1f       	adc	r24, r20
    4d28:	95 1f       	adc	r25, r21
    4d2a:	62 17       	cp	r22, r18
    4d2c:	73 07       	cpc	r23, r19
    4d2e:	84 07       	cpc	r24, r20
    4d30:	95 07       	cpc	r25, r21
    4d32:	10 f4       	brcc	.+4      	; 0x4d38 <strtoul+0x174>
    4d34:	4f ef       	ldi	r20, 0xFF	; 255
    4d36:	01 c0       	rjmp	.+2      	; 0x4d3a <strtoul+0x176>
    4d38:	41 e0       	ldi	r20, 0x01	; 1
    4d3a:	21 96       	adiw	r28, 0x01	; 1
    4d3c:	10 81       	ld	r17, Z
    4d3e:	c8 cf       	rjmp	.-112    	; 0x4cd0 <strtoul+0x10c>
    4d40:	c1 14       	cp	r12, r1
    4d42:	d1 04       	cpc	r13, r1
    4d44:	51 f0       	breq	.+20     	; 0x4d5a <strtoul+0x196>
    4d46:	44 23       	and	r20, r20
    4d48:	11 f0       	breq	.+4      	; 0x4d4e <strtoul+0x18a>
    4d4a:	21 97       	sbiw	r28, 0x01	; 1
    4d4c:	03 c0       	rjmp	.+6      	; 0x4d54 <strtoul+0x190>
    4d4e:	01 ff       	sbrs	r16, 1
    4d50:	04 c0       	rjmp	.+8      	; 0x4d5a <strtoul+0x196>
    4d52:	22 97       	sbiw	r28, 0x02	; 2
    4d54:	f6 01       	movw	r30, r12
    4d56:	d1 83       	std	Z+1, r29	; 0x01
    4d58:	c0 83       	st	Z, r28
    4d5a:	00 ff       	sbrs	r16, 0
    4d5c:	07 c0       	rjmp	.+14     	; 0x4d6c <strtoul+0x1a8>
    4d5e:	90 95       	com	r25
    4d60:	80 95       	com	r24
    4d62:	70 95       	com	r23
    4d64:	61 95       	neg	r22
    4d66:	7f 4f       	sbci	r23, 0xFF	; 255
    4d68:	8f 4f       	sbci	r24, 0xFF	; 255
    4d6a:	9f 4f       	sbci	r25, 0xFF	; 255
    4d6c:	4f 3f       	cpi	r20, 0xFF	; 255
    4d6e:	79 f4       	brne	.+30     	; 0x4d8e <strtoul+0x1ca>
    4d70:	82 e2       	ldi	r24, 0x22	; 34
    4d72:	90 e0       	ldi	r25, 0x00	; 0
    4d74:	90 93 9d 04 	sts	0x049D, r25	; 0x80049d <errno+0x1>
    4d78:	80 93 9c 04 	sts	0x049C, r24	; 0x80049c <errno>
    4d7c:	3f ef       	ldi	r19, 0xFF	; 255
    4d7e:	2f ef       	ldi	r18, 0xFF	; 255
    4d80:	9f ef       	ldi	r25, 0xFF	; 255
    4d82:	0d c0       	rjmp	.+26     	; 0x4d9e <strtoul+0x1da>
    4d84:	40 e0       	ldi	r20, 0x00	; 0
    4d86:	30 e0       	ldi	r19, 0x00	; 0
    4d88:	20 e0       	ldi	r18, 0x00	; 0
    4d8a:	90 e0       	ldi	r25, 0x00	; 0
    4d8c:	08 c0       	rjmp	.+16     	; 0x4d9e <strtoul+0x1da>
    4d8e:	46 2f       	mov	r20, r22
    4d90:	37 2f       	mov	r19, r23
    4d92:	28 2f       	mov	r18, r24
    4d94:	04 c0       	rjmp	.+8      	; 0x4d9e <strtoul+0x1da>
    4d96:	10 33       	cpi	r17, 0x30	; 48
    4d98:	09 f0       	breq	.+2      	; 0x4d9c <strtoul+0x1d8>
    4d9a:	67 cf       	rjmp	.-306    	; 0x4c6a <strtoul+0xa6>
    4d9c:	5f cf       	rjmp	.-322    	; 0x4c5c <strtoul+0x98>
    4d9e:	64 2f       	mov	r22, r20
    4da0:	73 2f       	mov	r23, r19
    4da2:	82 2f       	mov	r24, r18
    4da4:	cd b7       	in	r28, 0x3d	; 61
    4da6:	de b7       	in	r29, 0x3e	; 62
    4da8:	e1 e1       	ldi	r30, 0x11	; 17
    4daa:	0c 94 c8 25 	jmp	0x4b90	; 0x4b90 <__epilogue_restores__+0x2>

00004dae <__ftoa_engine>:
    4dae:	28 30       	cpi	r18, 0x08	; 8
    4db0:	08 f0       	brcs	.+2      	; 0x4db4 <__ftoa_engine+0x6>
    4db2:	27 e0       	ldi	r18, 0x07	; 7
    4db4:	33 27       	eor	r19, r19
    4db6:	da 01       	movw	r26, r20
    4db8:	99 0f       	add	r25, r25
    4dba:	31 1d       	adc	r19, r1
    4dbc:	87 fd       	sbrc	r24, 7
    4dbe:	91 60       	ori	r25, 0x01	; 1
    4dc0:	00 96       	adiw	r24, 0x00	; 0
    4dc2:	61 05       	cpc	r22, r1
    4dc4:	71 05       	cpc	r23, r1
    4dc6:	39 f4       	brne	.+14     	; 0x4dd6 <__ftoa_engine+0x28>
    4dc8:	32 60       	ori	r19, 0x02	; 2
    4dca:	2e 5f       	subi	r18, 0xFE	; 254
    4dcc:	3d 93       	st	X+, r19
    4dce:	30 e3       	ldi	r19, 0x30	; 48
    4dd0:	2a 95       	dec	r18
    4dd2:	e1 f7       	brne	.-8      	; 0x4dcc <__ftoa_engine+0x1e>
    4dd4:	08 95       	ret
    4dd6:	9f 3f       	cpi	r25, 0xFF	; 255
    4dd8:	30 f0       	brcs	.+12     	; 0x4de6 <__ftoa_engine+0x38>
    4dda:	80 38       	cpi	r24, 0x80	; 128
    4ddc:	71 05       	cpc	r23, r1
    4dde:	61 05       	cpc	r22, r1
    4de0:	09 f0       	breq	.+2      	; 0x4de4 <__ftoa_engine+0x36>
    4de2:	3c 5f       	subi	r19, 0xFC	; 252
    4de4:	3c 5f       	subi	r19, 0xFC	; 252
    4de6:	3d 93       	st	X+, r19
    4de8:	91 30       	cpi	r25, 0x01	; 1
    4dea:	08 f0       	brcs	.+2      	; 0x4dee <__ftoa_engine+0x40>
    4dec:	80 68       	ori	r24, 0x80	; 128
    4dee:	91 1d       	adc	r25, r1
    4df0:	df 93       	push	r29
    4df2:	cf 93       	push	r28
    4df4:	1f 93       	push	r17
    4df6:	0f 93       	push	r16
    4df8:	ff 92       	push	r15
    4dfa:	ef 92       	push	r14
    4dfc:	19 2f       	mov	r17, r25
    4dfe:	98 7f       	andi	r25, 0xF8	; 248
    4e00:	96 95       	lsr	r25
    4e02:	e9 2f       	mov	r30, r25
    4e04:	96 95       	lsr	r25
    4e06:	96 95       	lsr	r25
    4e08:	e9 0f       	add	r30, r25
    4e0a:	ff 27       	eor	r31, r31
    4e0c:	ec 5d       	subi	r30, 0xDC	; 220
    4e0e:	fe 4f       	sbci	r31, 0xFE	; 254
    4e10:	99 27       	eor	r25, r25
    4e12:	33 27       	eor	r19, r19
    4e14:	ee 24       	eor	r14, r14
    4e16:	ff 24       	eor	r15, r15
    4e18:	a7 01       	movw	r20, r14
    4e1a:	e7 01       	movw	r28, r14
    4e1c:	05 90       	lpm	r0, Z+
    4e1e:	08 94       	sec
    4e20:	07 94       	ror	r0
    4e22:	28 f4       	brcc	.+10     	; 0x4e2e <__ftoa_engine+0x80>
    4e24:	36 0f       	add	r19, r22
    4e26:	e7 1e       	adc	r14, r23
    4e28:	f8 1e       	adc	r15, r24
    4e2a:	49 1f       	adc	r20, r25
    4e2c:	51 1d       	adc	r21, r1
    4e2e:	66 0f       	add	r22, r22
    4e30:	77 1f       	adc	r23, r23
    4e32:	88 1f       	adc	r24, r24
    4e34:	99 1f       	adc	r25, r25
    4e36:	06 94       	lsr	r0
    4e38:	a1 f7       	brne	.-24     	; 0x4e22 <__ftoa_engine+0x74>
    4e3a:	05 90       	lpm	r0, Z+
    4e3c:	07 94       	ror	r0
    4e3e:	28 f4       	brcc	.+10     	; 0x4e4a <__ftoa_engine+0x9c>
    4e40:	e7 0e       	add	r14, r23
    4e42:	f8 1e       	adc	r15, r24
    4e44:	49 1f       	adc	r20, r25
    4e46:	56 1f       	adc	r21, r22
    4e48:	c1 1d       	adc	r28, r1
    4e4a:	77 0f       	add	r23, r23
    4e4c:	88 1f       	adc	r24, r24
    4e4e:	99 1f       	adc	r25, r25
    4e50:	66 1f       	adc	r22, r22
    4e52:	06 94       	lsr	r0
    4e54:	a1 f7       	brne	.-24     	; 0x4e3e <__ftoa_engine+0x90>
    4e56:	05 90       	lpm	r0, Z+
    4e58:	07 94       	ror	r0
    4e5a:	28 f4       	brcc	.+10     	; 0x4e66 <__ftoa_engine+0xb8>
    4e5c:	f8 0e       	add	r15, r24
    4e5e:	49 1f       	adc	r20, r25
    4e60:	56 1f       	adc	r21, r22
    4e62:	c7 1f       	adc	r28, r23
    4e64:	d1 1d       	adc	r29, r1
    4e66:	88 0f       	add	r24, r24
    4e68:	99 1f       	adc	r25, r25
    4e6a:	66 1f       	adc	r22, r22
    4e6c:	77 1f       	adc	r23, r23
    4e6e:	06 94       	lsr	r0
    4e70:	a1 f7       	brne	.-24     	; 0x4e5a <__ftoa_engine+0xac>
    4e72:	05 90       	lpm	r0, Z+
    4e74:	07 94       	ror	r0
    4e76:	20 f4       	brcc	.+8      	; 0x4e80 <__ftoa_engine+0xd2>
    4e78:	49 0f       	add	r20, r25
    4e7a:	56 1f       	adc	r21, r22
    4e7c:	c7 1f       	adc	r28, r23
    4e7e:	d8 1f       	adc	r29, r24
    4e80:	99 0f       	add	r25, r25
    4e82:	66 1f       	adc	r22, r22
    4e84:	77 1f       	adc	r23, r23
    4e86:	88 1f       	adc	r24, r24
    4e88:	06 94       	lsr	r0
    4e8a:	a9 f7       	brne	.-22     	; 0x4e76 <__ftoa_engine+0xc8>
    4e8c:	84 91       	lpm	r24, Z
    4e8e:	10 95       	com	r17
    4e90:	17 70       	andi	r17, 0x07	; 7
    4e92:	41 f0       	breq	.+16     	; 0x4ea4 <__ftoa_engine+0xf6>
    4e94:	d6 95       	lsr	r29
    4e96:	c7 95       	ror	r28
    4e98:	57 95       	ror	r21
    4e9a:	47 95       	ror	r20
    4e9c:	f7 94       	ror	r15
    4e9e:	e7 94       	ror	r14
    4ea0:	1a 95       	dec	r17
    4ea2:	c1 f7       	brne	.-16     	; 0x4e94 <__ftoa_engine+0xe6>
    4ea4:	ea ec       	ldi	r30, 0xCA	; 202
    4ea6:	f0 e0       	ldi	r31, 0x00	; 0
    4ea8:	68 94       	set
    4eaa:	15 90       	lpm	r1, Z+
    4eac:	15 91       	lpm	r17, Z+
    4eae:	35 91       	lpm	r19, Z+
    4eb0:	65 91       	lpm	r22, Z+
    4eb2:	95 91       	lpm	r25, Z+
    4eb4:	05 90       	lpm	r0, Z+
    4eb6:	7f e2       	ldi	r23, 0x2F	; 47
    4eb8:	73 95       	inc	r23
    4eba:	e1 18       	sub	r14, r1
    4ebc:	f1 0a       	sbc	r15, r17
    4ebe:	43 0b       	sbc	r20, r19
    4ec0:	56 0b       	sbc	r21, r22
    4ec2:	c9 0b       	sbc	r28, r25
    4ec4:	d0 09       	sbc	r29, r0
    4ec6:	c0 f7       	brcc	.-16     	; 0x4eb8 <__ftoa_engine+0x10a>
    4ec8:	e1 0c       	add	r14, r1
    4eca:	f1 1e       	adc	r15, r17
    4ecc:	43 1f       	adc	r20, r19
    4ece:	56 1f       	adc	r21, r22
    4ed0:	c9 1f       	adc	r28, r25
    4ed2:	d0 1d       	adc	r29, r0
    4ed4:	7e f4       	brtc	.+30     	; 0x4ef4 <__ftoa_engine+0x146>
    4ed6:	70 33       	cpi	r23, 0x30	; 48
    4ed8:	11 f4       	brne	.+4      	; 0x4ede <__ftoa_engine+0x130>
    4eda:	8a 95       	dec	r24
    4edc:	e6 cf       	rjmp	.-52     	; 0x4eaa <__ftoa_engine+0xfc>
    4ede:	e8 94       	clt
    4ee0:	01 50       	subi	r16, 0x01	; 1
    4ee2:	30 f0       	brcs	.+12     	; 0x4ef0 <__ftoa_engine+0x142>
    4ee4:	08 0f       	add	r16, r24
    4ee6:	0a f4       	brpl	.+2      	; 0x4eea <__ftoa_engine+0x13c>
    4ee8:	00 27       	eor	r16, r16
    4eea:	02 17       	cp	r16, r18
    4eec:	08 f4       	brcc	.+2      	; 0x4ef0 <__ftoa_engine+0x142>
    4eee:	20 2f       	mov	r18, r16
    4ef0:	23 95       	inc	r18
    4ef2:	02 2f       	mov	r16, r18
    4ef4:	7a 33       	cpi	r23, 0x3A	; 58
    4ef6:	28 f0       	brcs	.+10     	; 0x4f02 <__ftoa_engine+0x154>
    4ef8:	79 e3       	ldi	r23, 0x39	; 57
    4efa:	7d 93       	st	X+, r23
    4efc:	2a 95       	dec	r18
    4efe:	e9 f7       	brne	.-6      	; 0x4efa <__ftoa_engine+0x14c>
    4f00:	10 c0       	rjmp	.+32     	; 0x4f22 <__ftoa_engine+0x174>
    4f02:	7d 93       	st	X+, r23
    4f04:	2a 95       	dec	r18
    4f06:	89 f6       	brne	.-94     	; 0x4eaa <__ftoa_engine+0xfc>
    4f08:	06 94       	lsr	r0
    4f0a:	97 95       	ror	r25
    4f0c:	67 95       	ror	r22
    4f0e:	37 95       	ror	r19
    4f10:	17 95       	ror	r17
    4f12:	17 94       	ror	r1
    4f14:	e1 18       	sub	r14, r1
    4f16:	f1 0a       	sbc	r15, r17
    4f18:	43 0b       	sbc	r20, r19
    4f1a:	56 0b       	sbc	r21, r22
    4f1c:	c9 0b       	sbc	r28, r25
    4f1e:	d0 09       	sbc	r29, r0
    4f20:	98 f0       	brcs	.+38     	; 0x4f48 <__ftoa_engine+0x19a>
    4f22:	23 95       	inc	r18
    4f24:	7e 91       	ld	r23, -X
    4f26:	73 95       	inc	r23
    4f28:	7a 33       	cpi	r23, 0x3A	; 58
    4f2a:	08 f0       	brcs	.+2      	; 0x4f2e <__ftoa_engine+0x180>
    4f2c:	70 e3       	ldi	r23, 0x30	; 48
    4f2e:	7c 93       	st	X, r23
    4f30:	20 13       	cpse	r18, r16
    4f32:	b8 f7       	brcc	.-18     	; 0x4f22 <__ftoa_engine+0x174>
    4f34:	7e 91       	ld	r23, -X
    4f36:	70 61       	ori	r23, 0x10	; 16
    4f38:	7d 93       	st	X+, r23
    4f3a:	30 f0       	brcs	.+12     	; 0x4f48 <__ftoa_engine+0x19a>
    4f3c:	83 95       	inc	r24
    4f3e:	71 e3       	ldi	r23, 0x31	; 49
    4f40:	7d 93       	st	X+, r23
    4f42:	70 e3       	ldi	r23, 0x30	; 48
    4f44:	2a 95       	dec	r18
    4f46:	e1 f7       	brne	.-8      	; 0x4f40 <__ftoa_engine+0x192>
    4f48:	11 24       	eor	r1, r1
    4f4a:	ef 90       	pop	r14
    4f4c:	ff 90       	pop	r15
    4f4e:	0f 91       	pop	r16
    4f50:	1f 91       	pop	r17
    4f52:	cf 91       	pop	r28
    4f54:	df 91       	pop	r29
    4f56:	99 27       	eor	r25, r25
    4f58:	87 fd       	sbrc	r24, 7
    4f5a:	90 95       	com	r25
    4f5c:	08 95       	ret

00004f5e <isspace>:
    4f5e:	91 11       	cpse	r25, r1
    4f60:	0c 94 eb 28 	jmp	0x51d6	; 0x51d6 <__ctype_isfalse>
    4f64:	80 32       	cpi	r24, 0x20	; 32
    4f66:	19 f0       	breq	.+6      	; 0x4f6e <isspace+0x10>
    4f68:	89 50       	subi	r24, 0x09	; 9
    4f6a:	85 50       	subi	r24, 0x05	; 5
    4f6c:	c8 f7       	brcc	.-14     	; 0x4f60 <isspace+0x2>
    4f6e:	08 95       	ret

00004f70 <memcmp_P>:
    4f70:	fb 01       	movw	r30, r22
    4f72:	dc 01       	movw	r26, r24
    4f74:	04 c0       	rjmp	.+8      	; 0x4f7e <memcmp_P+0xe>
    4f76:	8d 91       	ld	r24, X+
    4f78:	05 90       	lpm	r0, Z+
    4f7a:	80 19       	sub	r24, r0
    4f7c:	21 f4       	brne	.+8      	; 0x4f86 <memcmp_P+0x16>
    4f7e:	41 50       	subi	r20, 0x01	; 1
    4f80:	50 40       	sbci	r21, 0x00	; 0
    4f82:	c8 f7       	brcc	.-14     	; 0x4f76 <memcmp_P+0x6>
    4f84:	88 1b       	sub	r24, r24
    4f86:	99 0b       	sbc	r25, r25
    4f88:	08 95       	ret

00004f8a <strcasecmp_P>:
    4f8a:	fb 01       	movw	r30, r22
    4f8c:	dc 01       	movw	r26, r24
    4f8e:	8d 91       	ld	r24, X+
    4f90:	81 34       	cpi	r24, 0x41	; 65
    4f92:	1c f0       	brlt	.+6      	; 0x4f9a <strcasecmp_P+0x10>
    4f94:	8b 35       	cpi	r24, 0x5B	; 91
    4f96:	0c f4       	brge	.+2      	; 0x4f9a <strcasecmp_P+0x10>
    4f98:	80 5e       	subi	r24, 0xE0	; 224
    4f9a:	65 91       	lpm	r22, Z+
    4f9c:	61 34       	cpi	r22, 0x41	; 65
    4f9e:	1c f0       	brlt	.+6      	; 0x4fa6 <strcasecmp_P+0x1c>
    4fa0:	6b 35       	cpi	r22, 0x5B	; 91
    4fa2:	0c f4       	brge	.+2      	; 0x4fa6 <strcasecmp_P+0x1c>
    4fa4:	60 5e       	subi	r22, 0xE0	; 224
    4fa6:	86 1b       	sub	r24, r22
    4fa8:	61 11       	cpse	r22, r1
    4faa:	89 f3       	breq	.-30     	; 0x4f8e <strcasecmp_P+0x4>
    4fac:	99 0b       	sbc	r25, r25
    4fae:	08 95       	ret

00004fb0 <strcpy_P>:
    4fb0:	fb 01       	movw	r30, r22
    4fb2:	dc 01       	movw	r26, r24
    4fb4:	05 90       	lpm	r0, Z+
    4fb6:	0d 92       	st	X+, r0
    4fb8:	00 20       	and	r0, r0
    4fba:	e1 f7       	brne	.-8      	; 0x4fb4 <strcpy_P+0x4>
    4fbc:	08 95       	ret

00004fbe <strnlen_P>:
    4fbe:	fc 01       	movw	r30, r24
    4fc0:	05 90       	lpm	r0, Z+
    4fc2:	61 50       	subi	r22, 0x01	; 1
    4fc4:	70 40       	sbci	r23, 0x00	; 0
    4fc6:	01 10       	cpse	r0, r1
    4fc8:	d8 f7       	brcc	.-10     	; 0x4fc0 <strnlen_P+0x2>
    4fca:	80 95       	com	r24
    4fcc:	90 95       	com	r25
    4fce:	8e 0f       	add	r24, r30
    4fd0:	9f 1f       	adc	r25, r31
    4fd2:	08 95       	ret

00004fd4 <strnlen>:
    4fd4:	fc 01       	movw	r30, r24
    4fd6:	61 50       	subi	r22, 0x01	; 1
    4fd8:	70 40       	sbci	r23, 0x00	; 0
    4fda:	01 90       	ld	r0, Z+
    4fdc:	01 10       	cpse	r0, r1
    4fde:	d8 f7       	brcc	.-10     	; 0x4fd6 <strnlen+0x2>
    4fe0:	80 95       	com	r24
    4fe2:	90 95       	com	r25
    4fe4:	8e 0f       	add	r24, r30
    4fe6:	9f 1f       	adc	r25, r31
    4fe8:	08 95       	ret

00004fea <fputc>:
    4fea:	0f 93       	push	r16
    4fec:	1f 93       	push	r17
    4fee:	cf 93       	push	r28
    4ff0:	df 93       	push	r29
    4ff2:	fb 01       	movw	r30, r22
    4ff4:	23 81       	ldd	r18, Z+3	; 0x03
    4ff6:	21 fd       	sbrc	r18, 1
    4ff8:	03 c0       	rjmp	.+6      	; 0x5000 <fputc+0x16>
    4ffa:	8f ef       	ldi	r24, 0xFF	; 255
    4ffc:	9f ef       	ldi	r25, 0xFF	; 255
    4ffe:	2c c0       	rjmp	.+88     	; 0x5058 <fputc+0x6e>
    5000:	22 ff       	sbrs	r18, 2
    5002:	16 c0       	rjmp	.+44     	; 0x5030 <fputc+0x46>
    5004:	46 81       	ldd	r20, Z+6	; 0x06
    5006:	57 81       	ldd	r21, Z+7	; 0x07
    5008:	24 81       	ldd	r18, Z+4	; 0x04
    500a:	35 81       	ldd	r19, Z+5	; 0x05
    500c:	42 17       	cp	r20, r18
    500e:	53 07       	cpc	r21, r19
    5010:	44 f4       	brge	.+16     	; 0x5022 <fputc+0x38>
    5012:	a0 81       	ld	r26, Z
    5014:	b1 81       	ldd	r27, Z+1	; 0x01
    5016:	9d 01       	movw	r18, r26
    5018:	2f 5f       	subi	r18, 0xFF	; 255
    501a:	3f 4f       	sbci	r19, 0xFF	; 255
    501c:	31 83       	std	Z+1, r19	; 0x01
    501e:	20 83       	st	Z, r18
    5020:	8c 93       	st	X, r24
    5022:	26 81       	ldd	r18, Z+6	; 0x06
    5024:	37 81       	ldd	r19, Z+7	; 0x07
    5026:	2f 5f       	subi	r18, 0xFF	; 255
    5028:	3f 4f       	sbci	r19, 0xFF	; 255
    502a:	37 83       	std	Z+7, r19	; 0x07
    502c:	26 83       	std	Z+6, r18	; 0x06
    502e:	14 c0       	rjmp	.+40     	; 0x5058 <fputc+0x6e>
    5030:	8b 01       	movw	r16, r22
    5032:	ec 01       	movw	r28, r24
    5034:	fb 01       	movw	r30, r22
    5036:	00 84       	ldd	r0, Z+8	; 0x08
    5038:	f1 85       	ldd	r31, Z+9	; 0x09
    503a:	e0 2d       	mov	r30, r0
    503c:	09 95       	icall
    503e:	89 2b       	or	r24, r25
    5040:	e1 f6       	brne	.-72     	; 0x4ffa <fputc+0x10>
    5042:	d8 01       	movw	r26, r16
    5044:	16 96       	adiw	r26, 0x06	; 6
    5046:	8d 91       	ld	r24, X+
    5048:	9c 91       	ld	r25, X
    504a:	17 97       	sbiw	r26, 0x07	; 7
    504c:	01 96       	adiw	r24, 0x01	; 1
    504e:	17 96       	adiw	r26, 0x07	; 7
    5050:	9c 93       	st	X, r25
    5052:	8e 93       	st	-X, r24
    5054:	16 97       	sbiw	r26, 0x06	; 6
    5056:	ce 01       	movw	r24, r28
    5058:	df 91       	pop	r29
    505a:	cf 91       	pop	r28
    505c:	1f 91       	pop	r17
    505e:	0f 91       	pop	r16
    5060:	08 95       	ret

00005062 <snprintf_P>:
    5062:	ae e0       	ldi	r26, 0x0E	; 14
    5064:	b0 e0       	ldi	r27, 0x00	; 0
    5066:	e7 e3       	ldi	r30, 0x37	; 55
    5068:	f8 e2       	ldi	r31, 0x28	; 40
    506a:	0c 94 b9 25 	jmp	0x4b72	; 0x4b72 <__prologue_saves__+0x1c>
    506e:	0d 89       	ldd	r16, Y+21	; 0x15
    5070:	1e 89       	ldd	r17, Y+22	; 0x16
    5072:	8f 89       	ldd	r24, Y+23	; 0x17
    5074:	98 8d       	ldd	r25, Y+24	; 0x18
    5076:	2e e0       	ldi	r18, 0x0E	; 14
    5078:	2c 83       	std	Y+4, r18	; 0x04
    507a:	1a 83       	std	Y+2, r17	; 0x02
    507c:	09 83       	std	Y+1, r16	; 0x01
    507e:	97 ff       	sbrs	r25, 7
    5080:	02 c0       	rjmp	.+4      	; 0x5086 <snprintf_P+0x24>
    5082:	80 e0       	ldi	r24, 0x00	; 0
    5084:	90 e8       	ldi	r25, 0x80	; 128
    5086:	01 97       	sbiw	r24, 0x01	; 1
    5088:	9e 83       	std	Y+6, r25	; 0x06
    508a:	8d 83       	std	Y+5, r24	; 0x05
    508c:	ae 01       	movw	r20, r28
    508e:	45 5e       	subi	r20, 0xE5	; 229
    5090:	5f 4f       	sbci	r21, 0xFF	; 255
    5092:	69 8d       	ldd	r22, Y+25	; 0x19
    5094:	7a 8d       	ldd	r23, Y+26	; 0x1a
    5096:	ce 01       	movw	r24, r28
    5098:	01 96       	adiw	r24, 0x01	; 1
    509a:	0e 94 2e 22 	call	0x445c	; 0x445c <vfprintf>
    509e:	4d 81       	ldd	r20, Y+5	; 0x05
    50a0:	5e 81       	ldd	r21, Y+6	; 0x06
    50a2:	57 fd       	sbrc	r21, 7
    50a4:	0a c0       	rjmp	.+20     	; 0x50ba <snprintf_P+0x58>
    50a6:	2f 81       	ldd	r18, Y+7	; 0x07
    50a8:	38 85       	ldd	r19, Y+8	; 0x08
    50aa:	42 17       	cp	r20, r18
    50ac:	53 07       	cpc	r21, r19
    50ae:	0c f4       	brge	.+2      	; 0x50b2 <snprintf_P+0x50>
    50b0:	9a 01       	movw	r18, r20
    50b2:	f8 01       	movw	r30, r16
    50b4:	e2 0f       	add	r30, r18
    50b6:	f3 1f       	adc	r31, r19
    50b8:	10 82       	st	Z, r1
    50ba:	2e 96       	adiw	r28, 0x0e	; 14
    50bc:	e4 e0       	ldi	r30, 0x04	; 4
    50be:	0c 94 d5 25 	jmp	0x4baa	; 0x4baa <__epilogue_restores__+0x1c>

000050c2 <vsnprintf_P>:
    50c2:	ae e0       	ldi	r26, 0x0E	; 14
    50c4:	b0 e0       	ldi	r27, 0x00	; 0
    50c6:	e7 e6       	ldi	r30, 0x67	; 103
    50c8:	f8 e2       	ldi	r31, 0x28	; 40
    50ca:	0c 94 b9 25 	jmp	0x4b72	; 0x4b72 <__prologue_saves__+0x1c>
    50ce:	8c 01       	movw	r16, r24
    50d0:	fa 01       	movw	r30, r20
    50d2:	8e e0       	ldi	r24, 0x0E	; 14
    50d4:	8c 83       	std	Y+4, r24	; 0x04
    50d6:	1a 83       	std	Y+2, r17	; 0x02
    50d8:	09 83       	std	Y+1, r16	; 0x01
    50da:	77 ff       	sbrs	r23, 7
    50dc:	02 c0       	rjmp	.+4      	; 0x50e2 <vsnprintf_P+0x20>
    50de:	60 e0       	ldi	r22, 0x00	; 0
    50e0:	70 e8       	ldi	r23, 0x80	; 128
    50e2:	cb 01       	movw	r24, r22
    50e4:	01 97       	sbiw	r24, 0x01	; 1
    50e6:	9e 83       	std	Y+6, r25	; 0x06
    50e8:	8d 83       	std	Y+5, r24	; 0x05
    50ea:	a9 01       	movw	r20, r18
    50ec:	bf 01       	movw	r22, r30
    50ee:	ce 01       	movw	r24, r28
    50f0:	01 96       	adiw	r24, 0x01	; 1
    50f2:	0e 94 2e 22 	call	0x445c	; 0x445c <vfprintf>
    50f6:	4d 81       	ldd	r20, Y+5	; 0x05
    50f8:	5e 81       	ldd	r21, Y+6	; 0x06
    50fa:	57 fd       	sbrc	r21, 7
    50fc:	0a c0       	rjmp	.+20     	; 0x5112 <vsnprintf_P+0x50>
    50fe:	2f 81       	ldd	r18, Y+7	; 0x07
    5100:	38 85       	ldd	r19, Y+8	; 0x08
    5102:	42 17       	cp	r20, r18
    5104:	53 07       	cpc	r21, r19
    5106:	0c f4       	brge	.+2      	; 0x510a <vsnprintf_P+0x48>
    5108:	9a 01       	movw	r18, r20
    510a:	f8 01       	movw	r30, r16
    510c:	e2 0f       	add	r30, r18
    510e:	f3 1f       	adc	r31, r19
    5110:	10 82       	st	Z, r1
    5112:	2e 96       	adiw	r28, 0x0e	; 14
    5114:	e4 e0       	ldi	r30, 0x04	; 4
    5116:	0c 94 d5 25 	jmp	0x4baa	; 0x4baa <__epilogue_restores__+0x1c>

0000511a <__ultoa_invert>:
    511a:	fa 01       	movw	r30, r20
    511c:	aa 27       	eor	r26, r26
    511e:	28 30       	cpi	r18, 0x08	; 8
    5120:	51 f1       	breq	.+84     	; 0x5176 <__ultoa_invert+0x5c>
    5122:	20 31       	cpi	r18, 0x10	; 16
    5124:	81 f1       	breq	.+96     	; 0x5186 <__ultoa_invert+0x6c>
    5126:	e8 94       	clt
    5128:	6f 93       	push	r22
    512a:	6e 7f       	andi	r22, 0xFE	; 254
    512c:	6e 5f       	subi	r22, 0xFE	; 254
    512e:	7f 4f       	sbci	r23, 0xFF	; 255
    5130:	8f 4f       	sbci	r24, 0xFF	; 255
    5132:	9f 4f       	sbci	r25, 0xFF	; 255
    5134:	af 4f       	sbci	r26, 0xFF	; 255
    5136:	b1 e0       	ldi	r27, 0x01	; 1
    5138:	3e d0       	rcall	.+124    	; 0x51b6 <__ultoa_invert+0x9c>
    513a:	b4 e0       	ldi	r27, 0x04	; 4
    513c:	3c d0       	rcall	.+120    	; 0x51b6 <__ultoa_invert+0x9c>
    513e:	67 0f       	add	r22, r23
    5140:	78 1f       	adc	r23, r24
    5142:	89 1f       	adc	r24, r25
    5144:	9a 1f       	adc	r25, r26
    5146:	a1 1d       	adc	r26, r1
    5148:	68 0f       	add	r22, r24
    514a:	79 1f       	adc	r23, r25
    514c:	8a 1f       	adc	r24, r26
    514e:	91 1d       	adc	r25, r1
    5150:	a1 1d       	adc	r26, r1
    5152:	6a 0f       	add	r22, r26
    5154:	71 1d       	adc	r23, r1
    5156:	81 1d       	adc	r24, r1
    5158:	91 1d       	adc	r25, r1
    515a:	a1 1d       	adc	r26, r1
    515c:	20 d0       	rcall	.+64     	; 0x519e <__ultoa_invert+0x84>
    515e:	09 f4       	brne	.+2      	; 0x5162 <__ultoa_invert+0x48>
    5160:	68 94       	set
    5162:	3f 91       	pop	r19
    5164:	2a e0       	ldi	r18, 0x0A	; 10
    5166:	26 9f       	mul	r18, r22
    5168:	11 24       	eor	r1, r1
    516a:	30 19       	sub	r19, r0
    516c:	30 5d       	subi	r19, 0xD0	; 208
    516e:	31 93       	st	Z+, r19
    5170:	de f6       	brtc	.-74     	; 0x5128 <__ultoa_invert+0xe>
    5172:	cf 01       	movw	r24, r30
    5174:	08 95       	ret
    5176:	46 2f       	mov	r20, r22
    5178:	47 70       	andi	r20, 0x07	; 7
    517a:	40 5d       	subi	r20, 0xD0	; 208
    517c:	41 93       	st	Z+, r20
    517e:	b3 e0       	ldi	r27, 0x03	; 3
    5180:	0f d0       	rcall	.+30     	; 0x51a0 <__ultoa_invert+0x86>
    5182:	c9 f7       	brne	.-14     	; 0x5176 <__ultoa_invert+0x5c>
    5184:	f6 cf       	rjmp	.-20     	; 0x5172 <__ultoa_invert+0x58>
    5186:	46 2f       	mov	r20, r22
    5188:	4f 70       	andi	r20, 0x0F	; 15
    518a:	40 5d       	subi	r20, 0xD0	; 208
    518c:	4a 33       	cpi	r20, 0x3A	; 58
    518e:	18 f0       	brcs	.+6      	; 0x5196 <__ultoa_invert+0x7c>
    5190:	49 5d       	subi	r20, 0xD9	; 217
    5192:	31 fd       	sbrc	r19, 1
    5194:	40 52       	subi	r20, 0x20	; 32
    5196:	41 93       	st	Z+, r20
    5198:	02 d0       	rcall	.+4      	; 0x519e <__ultoa_invert+0x84>
    519a:	a9 f7       	brne	.-22     	; 0x5186 <__ultoa_invert+0x6c>
    519c:	ea cf       	rjmp	.-44     	; 0x5172 <__ultoa_invert+0x58>
    519e:	b4 e0       	ldi	r27, 0x04	; 4
    51a0:	a6 95       	lsr	r26
    51a2:	97 95       	ror	r25
    51a4:	87 95       	ror	r24
    51a6:	77 95       	ror	r23
    51a8:	67 95       	ror	r22
    51aa:	ba 95       	dec	r27
    51ac:	c9 f7       	brne	.-14     	; 0x51a0 <__ultoa_invert+0x86>
    51ae:	00 97       	sbiw	r24, 0x00	; 0
    51b0:	61 05       	cpc	r22, r1
    51b2:	71 05       	cpc	r23, r1
    51b4:	08 95       	ret
    51b6:	9b 01       	movw	r18, r22
    51b8:	ac 01       	movw	r20, r24
    51ba:	0a 2e       	mov	r0, r26
    51bc:	06 94       	lsr	r0
    51be:	57 95       	ror	r21
    51c0:	47 95       	ror	r20
    51c2:	37 95       	ror	r19
    51c4:	27 95       	ror	r18
    51c6:	ba 95       	dec	r27
    51c8:	c9 f7       	brne	.-14     	; 0x51bc <__ultoa_invert+0xa2>
    51ca:	62 0f       	add	r22, r18
    51cc:	73 1f       	adc	r23, r19
    51ce:	84 1f       	adc	r24, r20
    51d0:	95 1f       	adc	r25, r21
    51d2:	a0 1d       	adc	r26, r0
    51d4:	08 95       	ret

000051d6 <__ctype_isfalse>:
    51d6:	99 27       	eor	r25, r25
    51d8:	88 27       	eor	r24, r24

000051da <__ctype_istrue>:
    51da:	08 95       	ret

000051dc <__cmpsf2>:
    51dc:	0e 94 30 29 	call	0x5260	; 0x5260 <__fp_cmp>
    51e0:	08 f4       	brcc	.+2      	; 0x51e4 <__cmpsf2+0x8>
    51e2:	81 e0       	ldi	r24, 0x01	; 1
    51e4:	08 95       	ret

000051e6 <__floatunsisf>:
    51e6:	e8 94       	clt
    51e8:	09 c0       	rjmp	.+18     	; 0x51fc <__floatsisf+0x12>

000051ea <__floatsisf>:
    51ea:	97 fb       	bst	r25, 7
    51ec:	3e f4       	brtc	.+14     	; 0x51fc <__floatsisf+0x12>
    51ee:	90 95       	com	r25
    51f0:	80 95       	com	r24
    51f2:	70 95       	com	r23
    51f4:	61 95       	neg	r22
    51f6:	7f 4f       	sbci	r23, 0xFF	; 255
    51f8:	8f 4f       	sbci	r24, 0xFF	; 255
    51fa:	9f 4f       	sbci	r25, 0xFF	; 255
    51fc:	99 23       	and	r25, r25
    51fe:	a9 f0       	breq	.+42     	; 0x522a <__floatsisf+0x40>
    5200:	f9 2f       	mov	r31, r25
    5202:	96 e9       	ldi	r25, 0x96	; 150
    5204:	bb 27       	eor	r27, r27
    5206:	93 95       	inc	r25
    5208:	f6 95       	lsr	r31
    520a:	87 95       	ror	r24
    520c:	77 95       	ror	r23
    520e:	67 95       	ror	r22
    5210:	b7 95       	ror	r27
    5212:	f1 11       	cpse	r31, r1
    5214:	f8 cf       	rjmp	.-16     	; 0x5206 <__floatsisf+0x1c>
    5216:	fa f4       	brpl	.+62     	; 0x5256 <__floatsisf+0x6c>
    5218:	bb 0f       	add	r27, r27
    521a:	11 f4       	brne	.+4      	; 0x5220 <__floatsisf+0x36>
    521c:	60 ff       	sbrs	r22, 0
    521e:	1b c0       	rjmp	.+54     	; 0x5256 <__floatsisf+0x6c>
    5220:	6f 5f       	subi	r22, 0xFF	; 255
    5222:	7f 4f       	sbci	r23, 0xFF	; 255
    5224:	8f 4f       	sbci	r24, 0xFF	; 255
    5226:	9f 4f       	sbci	r25, 0xFF	; 255
    5228:	16 c0       	rjmp	.+44     	; 0x5256 <__floatsisf+0x6c>
    522a:	88 23       	and	r24, r24
    522c:	11 f0       	breq	.+4      	; 0x5232 <__floatsisf+0x48>
    522e:	96 e9       	ldi	r25, 0x96	; 150
    5230:	11 c0       	rjmp	.+34     	; 0x5254 <__floatsisf+0x6a>
    5232:	77 23       	and	r23, r23
    5234:	21 f0       	breq	.+8      	; 0x523e <__floatsisf+0x54>
    5236:	9e e8       	ldi	r25, 0x8E	; 142
    5238:	87 2f       	mov	r24, r23
    523a:	76 2f       	mov	r23, r22
    523c:	05 c0       	rjmp	.+10     	; 0x5248 <__floatsisf+0x5e>
    523e:	66 23       	and	r22, r22
    5240:	71 f0       	breq	.+28     	; 0x525e <__floatsisf+0x74>
    5242:	96 e8       	ldi	r25, 0x86	; 134
    5244:	86 2f       	mov	r24, r22
    5246:	70 e0       	ldi	r23, 0x00	; 0
    5248:	60 e0       	ldi	r22, 0x00	; 0
    524a:	2a f0       	brmi	.+10     	; 0x5256 <__floatsisf+0x6c>
    524c:	9a 95       	dec	r25
    524e:	66 0f       	add	r22, r22
    5250:	77 1f       	adc	r23, r23
    5252:	88 1f       	adc	r24, r24
    5254:	da f7       	brpl	.-10     	; 0x524c <__floatsisf+0x62>
    5256:	88 0f       	add	r24, r24
    5258:	96 95       	lsr	r25
    525a:	87 95       	ror	r24
    525c:	97 f9       	bld	r25, 7
    525e:	08 95       	ret

00005260 <__fp_cmp>:
    5260:	99 0f       	add	r25, r25
    5262:	00 08       	sbc	r0, r0
    5264:	55 0f       	add	r21, r21
    5266:	aa 0b       	sbc	r26, r26
    5268:	e0 e8       	ldi	r30, 0x80	; 128
    526a:	fe ef       	ldi	r31, 0xFE	; 254
    526c:	16 16       	cp	r1, r22
    526e:	17 06       	cpc	r1, r23
    5270:	e8 07       	cpc	r30, r24
    5272:	f9 07       	cpc	r31, r25
    5274:	c0 f0       	brcs	.+48     	; 0x52a6 <__fp_cmp+0x46>
    5276:	12 16       	cp	r1, r18
    5278:	13 06       	cpc	r1, r19
    527a:	e4 07       	cpc	r30, r20
    527c:	f5 07       	cpc	r31, r21
    527e:	98 f0       	brcs	.+38     	; 0x52a6 <__fp_cmp+0x46>
    5280:	62 1b       	sub	r22, r18
    5282:	73 0b       	sbc	r23, r19
    5284:	84 0b       	sbc	r24, r20
    5286:	95 0b       	sbc	r25, r21
    5288:	39 f4       	brne	.+14     	; 0x5298 <__fp_cmp+0x38>
    528a:	0a 26       	eor	r0, r26
    528c:	61 f0       	breq	.+24     	; 0x52a6 <__fp_cmp+0x46>
    528e:	23 2b       	or	r18, r19
    5290:	24 2b       	or	r18, r20
    5292:	25 2b       	or	r18, r21
    5294:	21 f4       	brne	.+8      	; 0x529e <__fp_cmp+0x3e>
    5296:	08 95       	ret
    5298:	0a 26       	eor	r0, r26
    529a:	09 f4       	brne	.+2      	; 0x529e <__fp_cmp+0x3e>
    529c:	a1 40       	sbci	r26, 0x01	; 1
    529e:	a6 95       	lsr	r26
    52a0:	8f ef       	ldi	r24, 0xFF	; 255
    52a2:	81 1d       	adc	r24, r1
    52a4:	81 1d       	adc	r24, r1
    52a6:	08 95       	ret

000052a8 <__mulsf3>:
    52a8:	0e 94 67 29 	call	0x52ce	; 0x52ce <__mulsf3x>
    52ac:	0c 94 d8 29 	jmp	0x53b0	; 0x53b0 <__fp_round>
    52b0:	0e 94 ca 29 	call	0x5394	; 0x5394 <__fp_pscA>
    52b4:	38 f0       	brcs	.+14     	; 0x52c4 <__mulsf3+0x1c>
    52b6:	0e 94 d1 29 	call	0x53a2	; 0x53a2 <__fp_pscB>
    52ba:	20 f0       	brcs	.+8      	; 0x52c4 <__mulsf3+0x1c>
    52bc:	95 23       	and	r25, r21
    52be:	11 f0       	breq	.+4      	; 0x52c4 <__mulsf3+0x1c>
    52c0:	0c 94 c1 29 	jmp	0x5382	; 0x5382 <__fp_inf>
    52c4:	0c 94 c7 29 	jmp	0x538e	; 0x538e <__fp_nan>
    52c8:	11 24       	eor	r1, r1
    52ca:	0c 94 0c 2a 	jmp	0x5418	; 0x5418 <__fp_szero>

000052ce <__mulsf3x>:
    52ce:	0e 94 e9 29 	call	0x53d2	; 0x53d2 <__fp_split3>
    52d2:	70 f3       	brcs	.-36     	; 0x52b0 <__mulsf3+0x8>

000052d4 <__mulsf3_pse>:
    52d4:	95 9f       	mul	r25, r21
    52d6:	c1 f3       	breq	.-16     	; 0x52c8 <__mulsf3+0x20>
    52d8:	95 0f       	add	r25, r21
    52da:	50 e0       	ldi	r21, 0x00	; 0
    52dc:	55 1f       	adc	r21, r21
    52de:	62 9f       	mul	r22, r18
    52e0:	f0 01       	movw	r30, r0
    52e2:	72 9f       	mul	r23, r18
    52e4:	bb 27       	eor	r27, r27
    52e6:	f0 0d       	add	r31, r0
    52e8:	b1 1d       	adc	r27, r1
    52ea:	63 9f       	mul	r22, r19
    52ec:	aa 27       	eor	r26, r26
    52ee:	f0 0d       	add	r31, r0
    52f0:	b1 1d       	adc	r27, r1
    52f2:	aa 1f       	adc	r26, r26
    52f4:	64 9f       	mul	r22, r20
    52f6:	66 27       	eor	r22, r22
    52f8:	b0 0d       	add	r27, r0
    52fa:	a1 1d       	adc	r26, r1
    52fc:	66 1f       	adc	r22, r22
    52fe:	82 9f       	mul	r24, r18
    5300:	22 27       	eor	r18, r18
    5302:	b0 0d       	add	r27, r0
    5304:	a1 1d       	adc	r26, r1
    5306:	62 1f       	adc	r22, r18
    5308:	73 9f       	mul	r23, r19
    530a:	b0 0d       	add	r27, r0
    530c:	a1 1d       	adc	r26, r1
    530e:	62 1f       	adc	r22, r18
    5310:	83 9f       	mul	r24, r19
    5312:	a0 0d       	add	r26, r0
    5314:	61 1d       	adc	r22, r1
    5316:	22 1f       	adc	r18, r18
    5318:	74 9f       	mul	r23, r20
    531a:	33 27       	eor	r19, r19
    531c:	a0 0d       	add	r26, r0
    531e:	61 1d       	adc	r22, r1
    5320:	23 1f       	adc	r18, r19
    5322:	84 9f       	mul	r24, r20
    5324:	60 0d       	add	r22, r0
    5326:	21 1d       	adc	r18, r1
    5328:	82 2f       	mov	r24, r18
    532a:	76 2f       	mov	r23, r22
    532c:	6a 2f       	mov	r22, r26
    532e:	11 24       	eor	r1, r1
    5330:	9f 57       	subi	r25, 0x7F	; 127
    5332:	50 40       	sbci	r21, 0x00	; 0
    5334:	9a f0       	brmi	.+38     	; 0x535c <__mulsf3_pse+0x88>
    5336:	f1 f0       	breq	.+60     	; 0x5374 <__mulsf3_pse+0xa0>
    5338:	88 23       	and	r24, r24
    533a:	4a f0       	brmi	.+18     	; 0x534e <__mulsf3_pse+0x7a>
    533c:	ee 0f       	add	r30, r30
    533e:	ff 1f       	adc	r31, r31
    5340:	bb 1f       	adc	r27, r27
    5342:	66 1f       	adc	r22, r22
    5344:	77 1f       	adc	r23, r23
    5346:	88 1f       	adc	r24, r24
    5348:	91 50       	subi	r25, 0x01	; 1
    534a:	50 40       	sbci	r21, 0x00	; 0
    534c:	a9 f7       	brne	.-22     	; 0x5338 <__mulsf3_pse+0x64>
    534e:	9e 3f       	cpi	r25, 0xFE	; 254
    5350:	51 05       	cpc	r21, r1
    5352:	80 f0       	brcs	.+32     	; 0x5374 <__mulsf3_pse+0xa0>
    5354:	0c 94 c1 29 	jmp	0x5382	; 0x5382 <__fp_inf>
    5358:	0c 94 0c 2a 	jmp	0x5418	; 0x5418 <__fp_szero>
    535c:	5f 3f       	cpi	r21, 0xFF	; 255
    535e:	e4 f3       	brlt	.-8      	; 0x5358 <__mulsf3_pse+0x84>
    5360:	98 3e       	cpi	r25, 0xE8	; 232
    5362:	d4 f3       	brlt	.-12     	; 0x5358 <__mulsf3_pse+0x84>
    5364:	86 95       	lsr	r24
    5366:	77 95       	ror	r23
    5368:	67 95       	ror	r22
    536a:	b7 95       	ror	r27
    536c:	f7 95       	ror	r31
    536e:	e7 95       	ror	r30
    5370:	9f 5f       	subi	r25, 0xFF	; 255
    5372:	c1 f7       	brne	.-16     	; 0x5364 <__mulsf3_pse+0x90>
    5374:	fe 2b       	or	r31, r30
    5376:	88 0f       	add	r24, r24
    5378:	91 1d       	adc	r25, r1
    537a:	96 95       	lsr	r25
    537c:	87 95       	ror	r24
    537e:	97 f9       	bld	r25, 7
    5380:	08 95       	ret

00005382 <__fp_inf>:
    5382:	97 f9       	bld	r25, 7
    5384:	9f 67       	ori	r25, 0x7F	; 127
    5386:	80 e8       	ldi	r24, 0x80	; 128
    5388:	70 e0       	ldi	r23, 0x00	; 0
    538a:	60 e0       	ldi	r22, 0x00	; 0
    538c:	08 95       	ret

0000538e <__fp_nan>:
    538e:	9f ef       	ldi	r25, 0xFF	; 255
    5390:	80 ec       	ldi	r24, 0xC0	; 192
    5392:	08 95       	ret

00005394 <__fp_pscA>:
    5394:	00 24       	eor	r0, r0
    5396:	0a 94       	dec	r0
    5398:	16 16       	cp	r1, r22
    539a:	17 06       	cpc	r1, r23
    539c:	18 06       	cpc	r1, r24
    539e:	09 06       	cpc	r0, r25
    53a0:	08 95       	ret

000053a2 <__fp_pscB>:
    53a2:	00 24       	eor	r0, r0
    53a4:	0a 94       	dec	r0
    53a6:	12 16       	cp	r1, r18
    53a8:	13 06       	cpc	r1, r19
    53aa:	14 06       	cpc	r1, r20
    53ac:	05 06       	cpc	r0, r21
    53ae:	08 95       	ret

000053b0 <__fp_round>:
    53b0:	09 2e       	mov	r0, r25
    53b2:	03 94       	inc	r0
    53b4:	00 0c       	add	r0, r0
    53b6:	11 f4       	brne	.+4      	; 0x53bc <__fp_round+0xc>
    53b8:	88 23       	and	r24, r24
    53ba:	52 f0       	brmi	.+20     	; 0x53d0 <__fp_round+0x20>
    53bc:	bb 0f       	add	r27, r27
    53be:	40 f4       	brcc	.+16     	; 0x53d0 <__fp_round+0x20>
    53c0:	bf 2b       	or	r27, r31
    53c2:	11 f4       	brne	.+4      	; 0x53c8 <__fp_round+0x18>
    53c4:	60 ff       	sbrs	r22, 0
    53c6:	04 c0       	rjmp	.+8      	; 0x53d0 <__fp_round+0x20>
    53c8:	6f 5f       	subi	r22, 0xFF	; 255
    53ca:	7f 4f       	sbci	r23, 0xFF	; 255
    53cc:	8f 4f       	sbci	r24, 0xFF	; 255
    53ce:	9f 4f       	sbci	r25, 0xFF	; 255
    53d0:	08 95       	ret

000053d2 <__fp_split3>:
    53d2:	57 fd       	sbrc	r21, 7
    53d4:	90 58       	subi	r25, 0x80	; 128
    53d6:	44 0f       	add	r20, r20
    53d8:	55 1f       	adc	r21, r21
    53da:	59 f0       	breq	.+22     	; 0x53f2 <__fp_splitA+0x10>
    53dc:	5f 3f       	cpi	r21, 0xFF	; 255
    53de:	71 f0       	breq	.+28     	; 0x53fc <__fp_splitA+0x1a>
    53e0:	47 95       	ror	r20

000053e2 <__fp_splitA>:
    53e2:	88 0f       	add	r24, r24
    53e4:	97 fb       	bst	r25, 7
    53e6:	99 1f       	adc	r25, r25
    53e8:	61 f0       	breq	.+24     	; 0x5402 <__fp_splitA+0x20>
    53ea:	9f 3f       	cpi	r25, 0xFF	; 255
    53ec:	79 f0       	breq	.+30     	; 0x540c <__fp_splitA+0x2a>
    53ee:	87 95       	ror	r24
    53f0:	08 95       	ret
    53f2:	12 16       	cp	r1, r18
    53f4:	13 06       	cpc	r1, r19
    53f6:	14 06       	cpc	r1, r20
    53f8:	55 1f       	adc	r21, r21
    53fa:	f2 cf       	rjmp	.-28     	; 0x53e0 <__fp_split3+0xe>
    53fc:	46 95       	lsr	r20
    53fe:	f1 df       	rcall	.-30     	; 0x53e2 <__fp_splitA>
    5400:	08 c0       	rjmp	.+16     	; 0x5412 <__fp_splitA+0x30>
    5402:	16 16       	cp	r1, r22
    5404:	17 06       	cpc	r1, r23
    5406:	18 06       	cpc	r1, r24
    5408:	99 1f       	adc	r25, r25
    540a:	f1 cf       	rjmp	.-30     	; 0x53ee <__fp_splitA+0xc>
    540c:	86 95       	lsr	r24
    540e:	71 05       	cpc	r23, r1
    5410:	61 05       	cpc	r22, r1
    5412:	08 94       	sec
    5414:	08 95       	ret

00005416 <__fp_zero>:
    5416:	e8 94       	clt

00005418 <__fp_szero>:
    5418:	bb 27       	eor	r27, r27
    541a:	66 27       	eor	r22, r22
    541c:	77 27       	eor	r23, r23
    541e:	cb 01       	movw	r24, r22
    5420:	97 f9       	bld	r25, 7
    5422:	08 95       	ret

00005424 <eeprom_read_byte>:
    5424:	f9 99       	sbic	0x1f, 1	; 31
    5426:	fe cf       	rjmp	.-4      	; 0x5424 <eeprom_read_byte>
    5428:	92 bd       	out	0x22, r25	; 34
    542a:	81 bd       	out	0x21, r24	; 33
    542c:	f8 9a       	sbi	0x1f, 0	; 31
    542e:	99 27       	eor	r25, r25
    5430:	80 b5       	in	r24, 0x20	; 32
    5432:	08 95       	ret

00005434 <eeprom_write_byte>:
    5434:	26 2f       	mov	r18, r22

00005436 <eeprom_write_r18>:
    5436:	f9 99       	sbic	0x1f, 1	; 31
    5438:	fe cf       	rjmp	.-4      	; 0x5436 <eeprom_write_r18>
    543a:	1f ba       	out	0x1f, r1	; 31
    543c:	92 bd       	out	0x22, r25	; 34
    543e:	81 bd       	out	0x21, r24	; 33
    5440:	20 bd       	out	0x20, r18	; 32
    5442:	0f b6       	in	r0, 0x3f	; 63
    5444:	f8 94       	cli
    5446:	fa 9a       	sbi	0x1f, 2	; 31
    5448:	f9 9a       	sbi	0x1f, 1	; 31
    544a:	0f be       	out	0x3f, r0	; 63
    544c:	01 96       	adiw	r24, 0x01	; 1
    544e:	08 95       	ret

00005450 <__mulsi3>:
    5450:	db 01       	movw	r26, r22
    5452:	8f 93       	push	r24
    5454:	9f 93       	push	r25
    5456:	0e 94 5a 2a 	call	0x54b4	; 0x54b4 <__muluhisi3>
    545a:	bf 91       	pop	r27
    545c:	af 91       	pop	r26
    545e:	a2 9f       	mul	r26, r18
    5460:	80 0d       	add	r24, r0
    5462:	91 1d       	adc	r25, r1
    5464:	a3 9f       	mul	r26, r19
    5466:	90 0d       	add	r25, r0
    5468:	b2 9f       	mul	r27, r18
    546a:	90 0d       	add	r25, r0
    546c:	11 24       	eor	r1, r1
    546e:	08 95       	ret

00005470 <__udivmodsi4>:
    5470:	a1 e2       	ldi	r26, 0x21	; 33
    5472:	1a 2e       	mov	r1, r26
    5474:	aa 1b       	sub	r26, r26
    5476:	bb 1b       	sub	r27, r27
    5478:	fd 01       	movw	r30, r26
    547a:	0d c0       	rjmp	.+26     	; 0x5496 <__udivmodsi4_ep>

0000547c <__udivmodsi4_loop>:
    547c:	aa 1f       	adc	r26, r26
    547e:	bb 1f       	adc	r27, r27
    5480:	ee 1f       	adc	r30, r30
    5482:	ff 1f       	adc	r31, r31
    5484:	a2 17       	cp	r26, r18
    5486:	b3 07       	cpc	r27, r19
    5488:	e4 07       	cpc	r30, r20
    548a:	f5 07       	cpc	r31, r21
    548c:	20 f0       	brcs	.+8      	; 0x5496 <__udivmodsi4_ep>
    548e:	a2 1b       	sub	r26, r18
    5490:	b3 0b       	sbc	r27, r19
    5492:	e4 0b       	sbc	r30, r20
    5494:	f5 0b       	sbc	r31, r21

00005496 <__udivmodsi4_ep>:
    5496:	66 1f       	adc	r22, r22
    5498:	77 1f       	adc	r23, r23
    549a:	88 1f       	adc	r24, r24
    549c:	99 1f       	adc	r25, r25
    549e:	1a 94       	dec	r1
    54a0:	69 f7       	brne	.-38     	; 0x547c <__udivmodsi4_loop>
    54a2:	60 95       	com	r22
    54a4:	70 95       	com	r23
    54a6:	80 95       	com	r24
    54a8:	90 95       	com	r25
    54aa:	9b 01       	movw	r18, r22
    54ac:	ac 01       	movw	r20, r24
    54ae:	bd 01       	movw	r22, r26
    54b0:	cf 01       	movw	r24, r30
    54b2:	08 95       	ret

000054b4 <__muluhisi3>:
    54b4:	0e 94 65 2a 	call	0x54ca	; 0x54ca <__umulhisi3>
    54b8:	a5 9f       	mul	r26, r21
    54ba:	90 0d       	add	r25, r0
    54bc:	b4 9f       	mul	r27, r20
    54be:	90 0d       	add	r25, r0
    54c0:	a4 9f       	mul	r26, r20
    54c2:	80 0d       	add	r24, r0
    54c4:	91 1d       	adc	r25, r1
    54c6:	11 24       	eor	r1, r1
    54c8:	08 95       	ret

000054ca <__umulhisi3>:
    54ca:	a2 9f       	mul	r26, r18
    54cc:	b0 01       	movw	r22, r0
    54ce:	b3 9f       	mul	r27, r19
    54d0:	c0 01       	movw	r24, r0
    54d2:	a3 9f       	mul	r26, r19
    54d4:	70 0d       	add	r23, r0
    54d6:	81 1d       	adc	r24, r1
    54d8:	11 24       	eor	r1, r1
    54da:	91 1d       	adc	r25, r1
    54dc:	b2 9f       	mul	r27, r18
    54de:	70 0d       	add	r23, r0
    54e0:	81 1d       	adc	r24, r1
    54e2:	11 24       	eor	r1, r1
    54e4:	91 1d       	adc	r25, r1
    54e6:	08 95       	ret

000054e8 <__udivmodhi4>:
    54e8:	aa 1b       	sub	r26, r26
    54ea:	bb 1b       	sub	r27, r27
    54ec:	51 e1       	ldi	r21, 0x11	; 17
    54ee:	07 c0       	rjmp	.+14     	; 0x54fe <__udivmodhi4_ep>

000054f0 <__udivmodhi4_loop>:
    54f0:	aa 1f       	adc	r26, r26
    54f2:	bb 1f       	adc	r27, r27
    54f4:	a6 17       	cp	r26, r22
    54f6:	b7 07       	cpc	r27, r23
    54f8:	10 f0       	brcs	.+4      	; 0x54fe <__udivmodhi4_ep>
    54fa:	a6 1b       	sub	r26, r22
    54fc:	b7 0b       	sbc	r27, r23

000054fe <__udivmodhi4_ep>:
    54fe:	88 1f       	adc	r24, r24
    5500:	99 1f       	adc	r25, r25
    5502:	5a 95       	dec	r21
    5504:	a9 f7       	brne	.-22     	; 0x54f0 <__udivmodhi4_loop>
    5506:	80 95       	com	r24
    5508:	90 95       	com	r25
    550a:	bc 01       	movw	r22, r24
    550c:	cd 01       	movw	r24, r26
    550e:	08 95       	ret

00005510 <__tablejump2__>:
    5510:	ee 0f       	add	r30, r30
    5512:	ff 1f       	adc	r31, r31
    5514:	05 90       	lpm	r0, Z+
    5516:	f4 91       	lpm	r31, Z
    5518:	e0 2d       	mov	r30, r0
    551a:	09 94       	ijmp

0000551c <__subsf3>:
    551c:	50 58       	subi	r21, 0x80	; 128

0000551e <__addsf3>:
    551e:	bb 27       	eor	r27, r27
    5520:	aa 27       	eor	r26, r26
    5522:	0e 94 a6 2a 	call	0x554c	; 0x554c <__addsf3x>
    5526:	0c 94 d8 29 	jmp	0x53b0	; 0x53b0 <__fp_round>
    552a:	0e 94 ca 29 	call	0x5394	; 0x5394 <__fp_pscA>
    552e:	38 f0       	brcs	.+14     	; 0x553e <__addsf3+0x20>
    5530:	0e 94 d1 29 	call	0x53a2	; 0x53a2 <__fp_pscB>
    5534:	20 f0       	brcs	.+8      	; 0x553e <__addsf3+0x20>
    5536:	39 f4       	brne	.+14     	; 0x5546 <__addsf3+0x28>
    5538:	9f 3f       	cpi	r25, 0xFF	; 255
    553a:	19 f4       	brne	.+6      	; 0x5542 <__addsf3+0x24>
    553c:	26 f4       	brtc	.+8      	; 0x5546 <__addsf3+0x28>
    553e:	0c 94 c7 29 	jmp	0x538e	; 0x538e <__fp_nan>
    5542:	0e f4       	brtc	.+2      	; 0x5546 <__addsf3+0x28>
    5544:	e0 95       	com	r30
    5546:	e7 fb       	bst	r30, 7
    5548:	0c 94 c1 29 	jmp	0x5382	; 0x5382 <__fp_inf>

0000554c <__addsf3x>:
    554c:	e9 2f       	mov	r30, r25
    554e:	0e 94 e9 29 	call	0x53d2	; 0x53d2 <__fp_split3>
    5552:	58 f3       	brcs	.-42     	; 0x552a <__addsf3+0xc>
    5554:	ba 17       	cp	r27, r26
    5556:	62 07       	cpc	r22, r18
    5558:	73 07       	cpc	r23, r19
    555a:	84 07       	cpc	r24, r20
    555c:	95 07       	cpc	r25, r21
    555e:	20 f0       	brcs	.+8      	; 0x5568 <__addsf3x+0x1c>
    5560:	79 f4       	brne	.+30     	; 0x5580 <__addsf3x+0x34>
    5562:	a6 f5       	brtc	.+104    	; 0x55cc <__addsf3x+0x80>
    5564:	0c 94 0b 2a 	jmp	0x5416	; 0x5416 <__fp_zero>
    5568:	0e f4       	brtc	.+2      	; 0x556c <__addsf3x+0x20>
    556a:	e0 95       	com	r30
    556c:	0b 2e       	mov	r0, r27
    556e:	ba 2f       	mov	r27, r26
    5570:	a0 2d       	mov	r26, r0
    5572:	0b 01       	movw	r0, r22
    5574:	b9 01       	movw	r22, r18
    5576:	90 01       	movw	r18, r0
    5578:	0c 01       	movw	r0, r24
    557a:	ca 01       	movw	r24, r20
    557c:	a0 01       	movw	r20, r0
    557e:	11 24       	eor	r1, r1
    5580:	ff 27       	eor	r31, r31
    5582:	59 1b       	sub	r21, r25
    5584:	99 f0       	breq	.+38     	; 0x55ac <__addsf3x+0x60>
    5586:	59 3f       	cpi	r21, 0xF9	; 249
    5588:	50 f4       	brcc	.+20     	; 0x559e <__addsf3x+0x52>
    558a:	50 3e       	cpi	r21, 0xE0	; 224
    558c:	68 f1       	brcs	.+90     	; 0x55e8 <__addsf3x+0x9c>
    558e:	1a 16       	cp	r1, r26
    5590:	f0 40       	sbci	r31, 0x00	; 0
    5592:	a2 2f       	mov	r26, r18
    5594:	23 2f       	mov	r18, r19
    5596:	34 2f       	mov	r19, r20
    5598:	44 27       	eor	r20, r20
    559a:	58 5f       	subi	r21, 0xF8	; 248
    559c:	f3 cf       	rjmp	.-26     	; 0x5584 <__addsf3x+0x38>
    559e:	46 95       	lsr	r20
    55a0:	37 95       	ror	r19
    55a2:	27 95       	ror	r18
    55a4:	a7 95       	ror	r26
    55a6:	f0 40       	sbci	r31, 0x00	; 0
    55a8:	53 95       	inc	r21
    55aa:	c9 f7       	brne	.-14     	; 0x559e <__addsf3x+0x52>
    55ac:	7e f4       	brtc	.+30     	; 0x55cc <__addsf3x+0x80>
    55ae:	1f 16       	cp	r1, r31
    55b0:	ba 0b       	sbc	r27, r26
    55b2:	62 0b       	sbc	r22, r18
    55b4:	73 0b       	sbc	r23, r19
    55b6:	84 0b       	sbc	r24, r20
    55b8:	ba f0       	brmi	.+46     	; 0x55e8 <__addsf3x+0x9c>
    55ba:	91 50       	subi	r25, 0x01	; 1
    55bc:	a1 f0       	breq	.+40     	; 0x55e6 <__addsf3x+0x9a>
    55be:	ff 0f       	add	r31, r31
    55c0:	bb 1f       	adc	r27, r27
    55c2:	66 1f       	adc	r22, r22
    55c4:	77 1f       	adc	r23, r23
    55c6:	88 1f       	adc	r24, r24
    55c8:	c2 f7       	brpl	.-16     	; 0x55ba <__addsf3x+0x6e>
    55ca:	0e c0       	rjmp	.+28     	; 0x55e8 <__addsf3x+0x9c>
    55cc:	ba 0f       	add	r27, r26
    55ce:	62 1f       	adc	r22, r18
    55d0:	73 1f       	adc	r23, r19
    55d2:	84 1f       	adc	r24, r20
    55d4:	48 f4       	brcc	.+18     	; 0x55e8 <__addsf3x+0x9c>
    55d6:	87 95       	ror	r24
    55d8:	77 95       	ror	r23
    55da:	67 95       	ror	r22
    55dc:	b7 95       	ror	r27
    55de:	f7 95       	ror	r31
    55e0:	9e 3f       	cpi	r25, 0xFE	; 254
    55e2:	08 f0       	brcs	.+2      	; 0x55e6 <__addsf3x+0x9a>
    55e4:	b0 cf       	rjmp	.-160    	; 0x5546 <__addsf3+0x28>
    55e6:	93 95       	inc	r25
    55e8:	88 0f       	add	r24, r24
    55ea:	08 f0       	brcs	.+2      	; 0x55ee <__addsf3x+0xa2>
    55ec:	99 27       	eor	r25, r25
    55ee:	ee 0f       	add	r30, r30
    55f0:	97 95       	ror	r25
    55f2:	87 95       	ror	r24
    55f4:	08 95       	ret

000055f6 <__divsf3>:
    55f6:	0e 94 0f 2b 	call	0x561e	; 0x561e <__divsf3x>
    55fa:	0c 94 d8 29 	jmp	0x53b0	; 0x53b0 <__fp_round>
    55fe:	0e 94 d1 29 	call	0x53a2	; 0x53a2 <__fp_pscB>
    5602:	58 f0       	brcs	.+22     	; 0x561a <__divsf3+0x24>
    5604:	0e 94 ca 29 	call	0x5394	; 0x5394 <__fp_pscA>
    5608:	40 f0       	brcs	.+16     	; 0x561a <__divsf3+0x24>
    560a:	29 f4       	brne	.+10     	; 0x5616 <__divsf3+0x20>
    560c:	5f 3f       	cpi	r21, 0xFF	; 255
    560e:	29 f0       	breq	.+10     	; 0x561a <__divsf3+0x24>
    5610:	0c 94 c1 29 	jmp	0x5382	; 0x5382 <__fp_inf>
    5614:	51 11       	cpse	r21, r1
    5616:	0c 94 0c 2a 	jmp	0x5418	; 0x5418 <__fp_szero>
    561a:	0c 94 c7 29 	jmp	0x538e	; 0x538e <__fp_nan>

0000561e <__divsf3x>:
    561e:	0e 94 e9 29 	call	0x53d2	; 0x53d2 <__fp_split3>
    5622:	68 f3       	brcs	.-38     	; 0x55fe <__divsf3+0x8>

00005624 <__divsf3_pse>:
    5624:	99 23       	and	r25, r25
    5626:	b1 f3       	breq	.-20     	; 0x5614 <__divsf3+0x1e>
    5628:	55 23       	and	r21, r21
    562a:	91 f3       	breq	.-28     	; 0x5610 <__divsf3+0x1a>
    562c:	95 1b       	sub	r25, r21
    562e:	55 0b       	sbc	r21, r21
    5630:	bb 27       	eor	r27, r27
    5632:	aa 27       	eor	r26, r26
    5634:	62 17       	cp	r22, r18
    5636:	73 07       	cpc	r23, r19
    5638:	84 07       	cpc	r24, r20
    563a:	38 f0       	brcs	.+14     	; 0x564a <__divsf3_pse+0x26>
    563c:	9f 5f       	subi	r25, 0xFF	; 255
    563e:	5f 4f       	sbci	r21, 0xFF	; 255
    5640:	22 0f       	add	r18, r18
    5642:	33 1f       	adc	r19, r19
    5644:	44 1f       	adc	r20, r20
    5646:	aa 1f       	adc	r26, r26
    5648:	a9 f3       	breq	.-22     	; 0x5634 <__divsf3_pse+0x10>
    564a:	35 d0       	rcall	.+106    	; 0x56b6 <__divsf3_pse+0x92>
    564c:	0e 2e       	mov	r0, r30
    564e:	3a f0       	brmi	.+14     	; 0x565e <__divsf3_pse+0x3a>
    5650:	e0 e8       	ldi	r30, 0x80	; 128
    5652:	32 d0       	rcall	.+100    	; 0x56b8 <__divsf3_pse+0x94>
    5654:	91 50       	subi	r25, 0x01	; 1
    5656:	50 40       	sbci	r21, 0x00	; 0
    5658:	e6 95       	lsr	r30
    565a:	00 1c       	adc	r0, r0
    565c:	ca f7       	brpl	.-14     	; 0x5650 <__divsf3_pse+0x2c>
    565e:	2b d0       	rcall	.+86     	; 0x56b6 <__divsf3_pse+0x92>
    5660:	fe 2f       	mov	r31, r30
    5662:	29 d0       	rcall	.+82     	; 0x56b6 <__divsf3_pse+0x92>
    5664:	66 0f       	add	r22, r22
    5666:	77 1f       	adc	r23, r23
    5668:	88 1f       	adc	r24, r24
    566a:	bb 1f       	adc	r27, r27
    566c:	26 17       	cp	r18, r22
    566e:	37 07       	cpc	r19, r23
    5670:	48 07       	cpc	r20, r24
    5672:	ab 07       	cpc	r26, r27
    5674:	b0 e8       	ldi	r27, 0x80	; 128
    5676:	09 f0       	breq	.+2      	; 0x567a <__divsf3_pse+0x56>
    5678:	bb 0b       	sbc	r27, r27
    567a:	80 2d       	mov	r24, r0
    567c:	bf 01       	movw	r22, r30
    567e:	ff 27       	eor	r31, r31
    5680:	93 58       	subi	r25, 0x83	; 131
    5682:	5f 4f       	sbci	r21, 0xFF	; 255
    5684:	3a f0       	brmi	.+14     	; 0x5694 <__divsf3_pse+0x70>
    5686:	9e 3f       	cpi	r25, 0xFE	; 254
    5688:	51 05       	cpc	r21, r1
    568a:	78 f0       	brcs	.+30     	; 0x56aa <__divsf3_pse+0x86>
    568c:	0c 94 c1 29 	jmp	0x5382	; 0x5382 <__fp_inf>
    5690:	0c 94 0c 2a 	jmp	0x5418	; 0x5418 <__fp_szero>
    5694:	5f 3f       	cpi	r21, 0xFF	; 255
    5696:	e4 f3       	brlt	.-8      	; 0x5690 <__divsf3_pse+0x6c>
    5698:	98 3e       	cpi	r25, 0xE8	; 232
    569a:	d4 f3       	brlt	.-12     	; 0x5690 <__divsf3_pse+0x6c>
    569c:	86 95       	lsr	r24
    569e:	77 95       	ror	r23
    56a0:	67 95       	ror	r22
    56a2:	b7 95       	ror	r27
    56a4:	f7 95       	ror	r31
    56a6:	9f 5f       	subi	r25, 0xFF	; 255
    56a8:	c9 f7       	brne	.-14     	; 0x569c <__divsf3_pse+0x78>
    56aa:	88 0f       	add	r24, r24
    56ac:	91 1d       	adc	r25, r1
    56ae:	96 95       	lsr	r25
    56b0:	87 95       	ror	r24
    56b2:	97 f9       	bld	r25, 7
    56b4:	08 95       	ret
    56b6:	e1 e0       	ldi	r30, 0x01	; 1
    56b8:	66 0f       	add	r22, r22
    56ba:	77 1f       	adc	r23, r23
    56bc:	88 1f       	adc	r24, r24
    56be:	bb 1f       	adc	r27, r27
    56c0:	62 17       	cp	r22, r18
    56c2:	73 07       	cpc	r23, r19
    56c4:	84 07       	cpc	r24, r20
    56c6:	ba 07       	cpc	r27, r26
    56c8:	20 f0       	brcs	.+8      	; 0x56d2 <__divsf3_pse+0xae>
    56ca:	62 1b       	sub	r22, r18
    56cc:	73 0b       	sbc	r23, r19
    56ce:	84 0b       	sbc	r24, r20
    56d0:	ba 0b       	sbc	r27, r26
    56d2:	ee 1f       	adc	r30, r30
    56d4:	88 f7       	brcc	.-30     	; 0x56b8 <__divsf3_pse+0x94>
    56d6:	e0 95       	com	r30
    56d8:	08 95       	ret

000056da <__fixsfsi>:
    56da:	0e 94 74 2b 	call	0x56e8	; 0x56e8 <__fixunssfsi>
    56de:	68 94       	set
    56e0:	b1 11       	cpse	r27, r1
    56e2:	0c 94 0c 2a 	jmp	0x5418	; 0x5418 <__fp_szero>
    56e6:	08 95       	ret

000056e8 <__fixunssfsi>:
    56e8:	0e 94 f1 29 	call	0x53e2	; 0x53e2 <__fp_splitA>
    56ec:	88 f0       	brcs	.+34     	; 0x5710 <__fixunssfsi+0x28>
    56ee:	9f 57       	subi	r25, 0x7F	; 127
    56f0:	98 f0       	brcs	.+38     	; 0x5718 <__fixunssfsi+0x30>
    56f2:	b9 2f       	mov	r27, r25
    56f4:	99 27       	eor	r25, r25
    56f6:	b7 51       	subi	r27, 0x17	; 23
    56f8:	b0 f0       	brcs	.+44     	; 0x5726 <__fixunssfsi+0x3e>
    56fa:	e1 f0       	breq	.+56     	; 0x5734 <__fixunssfsi+0x4c>
    56fc:	66 0f       	add	r22, r22
    56fe:	77 1f       	adc	r23, r23
    5700:	88 1f       	adc	r24, r24
    5702:	99 1f       	adc	r25, r25
    5704:	1a f0       	brmi	.+6      	; 0x570c <__fixunssfsi+0x24>
    5706:	ba 95       	dec	r27
    5708:	c9 f7       	brne	.-14     	; 0x56fc <__fixunssfsi+0x14>
    570a:	14 c0       	rjmp	.+40     	; 0x5734 <__fixunssfsi+0x4c>
    570c:	b1 30       	cpi	r27, 0x01	; 1
    570e:	91 f0       	breq	.+36     	; 0x5734 <__fixunssfsi+0x4c>
    5710:	0e 94 0b 2a 	call	0x5416	; 0x5416 <__fp_zero>
    5714:	b1 e0       	ldi	r27, 0x01	; 1
    5716:	08 95       	ret
    5718:	0c 94 0b 2a 	jmp	0x5416	; 0x5416 <__fp_zero>
    571c:	67 2f       	mov	r22, r23
    571e:	78 2f       	mov	r23, r24
    5720:	88 27       	eor	r24, r24
    5722:	b8 5f       	subi	r27, 0xF8	; 248
    5724:	39 f0       	breq	.+14     	; 0x5734 <__fixunssfsi+0x4c>
    5726:	b9 3f       	cpi	r27, 0xF9	; 249
    5728:	cc f3       	brlt	.-14     	; 0x571c <__fixunssfsi+0x34>
    572a:	86 95       	lsr	r24
    572c:	77 95       	ror	r23
    572e:	67 95       	ror	r22
    5730:	b3 95       	inc	r27
    5732:	d9 f7       	brne	.-10     	; 0x572a <__fixunssfsi+0x42>
    5734:	3e f4       	brtc	.+14     	; 0x5744 <__fixunssfsi+0x5c>
    5736:	90 95       	com	r25
    5738:	80 95       	com	r24
    573a:	70 95       	com	r23
    573c:	61 95       	neg	r22
    573e:	7f 4f       	sbci	r23, 0xFF	; 255
    5740:	8f 4f       	sbci	r24, 0xFF	; 255
    5742:	9f 4f       	sbci	r25, 0xFF	; 255
    5744:	08 95       	ret

00005746 <__gesf2>:
    5746:	0e 94 30 29 	call	0x5260	; 0x5260 <__fp_cmp>
    574a:	08 f4       	brcc	.+2      	; 0x574e <__gesf2+0x8>
    574c:	8f ef       	ldi	r24, 0xFF	; 255
    574e:	08 95       	ret
    5750:	16 f0       	brts	.+4      	; 0x5756 <__gesf2+0x10>
    5752:	0c 94 fd 2b 	jmp	0x57fa	; 0x57fa <__fp_mpack>
    5756:	0c 94 c7 29 	jmp	0x538e	; 0x538e <__fp_nan>
    575a:	68 94       	set
    575c:	0c 94 c1 29 	jmp	0x5382	; 0x5382 <__fp_inf>

00005760 <log>:
    5760:	0e 94 f1 29 	call	0x53e2	; 0x53e2 <__fp_splitA>
    5764:	a8 f3       	brcs	.-22     	; 0x5750 <__gesf2+0xa>
    5766:	99 23       	and	r25, r25
    5768:	c1 f3       	breq	.-16     	; 0x575a <__gesf2+0x14>
    576a:	ae f3       	brts	.-22     	; 0x5756 <__gesf2+0x10>
    576c:	df 93       	push	r29
    576e:	cf 93       	push	r28
    5770:	1f 93       	push	r17
    5772:	0f 93       	push	r16
    5774:	ff 92       	push	r15
    5776:	c9 2f       	mov	r28, r25
    5778:	dd 27       	eor	r29, r29
    577a:	88 23       	and	r24, r24
    577c:	2a f0       	brmi	.+10     	; 0x5788 <log+0x28>
    577e:	21 97       	sbiw	r28, 0x01	; 1
    5780:	66 0f       	add	r22, r22
    5782:	77 1f       	adc	r23, r23
    5784:	88 1f       	adc	r24, r24
    5786:	da f7       	brpl	.-10     	; 0x577e <log+0x1e>
    5788:	20 e0       	ldi	r18, 0x00	; 0
    578a:	30 e0       	ldi	r19, 0x00	; 0
    578c:	40 e8       	ldi	r20, 0x80	; 128
    578e:	5f eb       	ldi	r21, 0xBF	; 191
    5790:	9f e3       	ldi	r25, 0x3F	; 63
    5792:	88 39       	cpi	r24, 0x98	; 152
    5794:	20 f0       	brcs	.+8      	; 0x579e <log+0x3e>
    5796:	80 3e       	cpi	r24, 0xE0	; 224
    5798:	38 f0       	brcs	.+14     	; 0x57a8 <log+0x48>
    579a:	21 96       	adiw	r28, 0x01	; 1
    579c:	8f 77       	andi	r24, 0x7F	; 127
    579e:	0e 94 8f 2a 	call	0x551e	; 0x551e <__addsf3>
    57a2:	e8 e6       	ldi	r30, 0x68	; 104
    57a4:	f0 e0       	ldi	r31, 0x00	; 0
    57a6:	04 c0       	rjmp	.+8      	; 0x57b0 <log+0x50>
    57a8:	0e 94 8f 2a 	call	0x551e	; 0x551e <__addsf3>
    57ac:	e5 e9       	ldi	r30, 0x95	; 149
    57ae:	f0 e0       	ldi	r31, 0x00	; 0
    57b0:	0e 94 0b 2c 	call	0x5816	; 0x5816 <__fp_powser>
    57b4:	8b 01       	movw	r16, r22
    57b6:	be 01       	movw	r22, r28
    57b8:	ec 01       	movw	r28, r24
    57ba:	fb 2e       	mov	r15, r27
    57bc:	6f 57       	subi	r22, 0x7F	; 127
    57be:	71 09       	sbc	r23, r1
    57c0:	75 95       	asr	r23
    57c2:	77 1f       	adc	r23, r23
    57c4:	88 0b       	sbc	r24, r24
    57c6:	99 0b       	sbc	r25, r25
    57c8:	0e 94 f5 28 	call	0x51ea	; 0x51ea <__floatsisf>
    57cc:	28 e1       	ldi	r18, 0x18	; 24
    57ce:	32 e7       	ldi	r19, 0x72	; 114
    57d0:	41 e3       	ldi	r20, 0x31	; 49
    57d2:	5f e3       	ldi	r21, 0x3F	; 63
    57d4:	0e 94 67 29 	call	0x52ce	; 0x52ce <__mulsf3x>
    57d8:	af 2d       	mov	r26, r15
    57da:	98 01       	movw	r18, r16
    57dc:	ae 01       	movw	r20, r28
    57de:	ff 90       	pop	r15
    57e0:	0f 91       	pop	r16
    57e2:	1f 91       	pop	r17
    57e4:	cf 91       	pop	r28
    57e6:	df 91       	pop	r29
    57e8:	0e 94 a6 2a 	call	0x554c	; 0x554c <__addsf3x>
    57ec:	0c 94 d8 29 	jmp	0x53b0	; 0x53b0 <__fp_round>

000057f0 <__unordsf2>:
    57f0:	0e 94 30 29 	call	0x5260	; 0x5260 <__fp_cmp>
    57f4:	88 0b       	sbc	r24, r24
    57f6:	99 0b       	sbc	r25, r25
    57f8:	08 95       	ret

000057fa <__fp_mpack>:
    57fa:	9f 3f       	cpi	r25, 0xFF	; 255
    57fc:	31 f0       	breq	.+12     	; 0x580a <__fp_mpack_finite+0xc>

000057fe <__fp_mpack_finite>:
    57fe:	91 50       	subi	r25, 0x01	; 1
    5800:	20 f4       	brcc	.+8      	; 0x580a <__fp_mpack_finite+0xc>
    5802:	87 95       	ror	r24
    5804:	77 95       	ror	r23
    5806:	67 95       	ror	r22
    5808:	b7 95       	ror	r27
    580a:	88 0f       	add	r24, r24
    580c:	91 1d       	adc	r25, r1
    580e:	96 95       	lsr	r25
    5810:	87 95       	ror	r24
    5812:	97 f9       	bld	r25, 7
    5814:	08 95       	ret

00005816 <__fp_powser>:
    5816:	df 93       	push	r29
    5818:	cf 93       	push	r28
    581a:	1f 93       	push	r17
    581c:	0f 93       	push	r16
    581e:	ff 92       	push	r15
    5820:	ef 92       	push	r14
    5822:	df 92       	push	r13
    5824:	7b 01       	movw	r14, r22
    5826:	8c 01       	movw	r16, r24
    5828:	68 94       	set
    582a:	06 c0       	rjmp	.+12     	; 0x5838 <__fp_powser+0x22>
    582c:	da 2e       	mov	r13, r26
    582e:	ef 01       	movw	r28, r30
    5830:	0e 94 67 29 	call	0x52ce	; 0x52ce <__mulsf3x>
    5834:	fe 01       	movw	r30, r28
    5836:	e8 94       	clt
    5838:	a5 91       	lpm	r26, Z+
    583a:	25 91       	lpm	r18, Z+
    583c:	35 91       	lpm	r19, Z+
    583e:	45 91       	lpm	r20, Z+
    5840:	55 91       	lpm	r21, Z+
    5842:	a6 f3       	brts	.-24     	; 0x582c <__fp_powser+0x16>
    5844:	ef 01       	movw	r28, r30
    5846:	0e 94 a6 2a 	call	0x554c	; 0x554c <__addsf3x>
    584a:	fe 01       	movw	r30, r28
    584c:	97 01       	movw	r18, r14
    584e:	a8 01       	movw	r20, r16
    5850:	da 94       	dec	r13
    5852:	69 f7       	brne	.-38     	; 0x582e <__fp_powser+0x18>
    5854:	df 90       	pop	r13
    5856:	ef 90       	pop	r14
    5858:	ff 90       	pop	r15
    585a:	0f 91       	pop	r16
    585c:	1f 91       	pop	r17
    585e:	cf 91       	pop	r28
    5860:	df 91       	pop	r29
    5862:	08 95       	ret

00005864 <malloc>:
    5864:	0f 93       	push	r16
    5866:	1f 93       	push	r17
    5868:	cf 93       	push	r28
    586a:	df 93       	push	r29
    586c:	82 30       	cpi	r24, 0x02	; 2
    586e:	91 05       	cpc	r25, r1
    5870:	10 f4       	brcc	.+4      	; 0x5876 <malloc+0x12>
    5872:	82 e0       	ldi	r24, 0x02	; 2
    5874:	90 e0       	ldi	r25, 0x00	; 0
    5876:	e0 91 a0 04 	lds	r30, 0x04A0	; 0x8004a0 <__flp>
    587a:	f0 91 a1 04 	lds	r31, 0x04A1	; 0x8004a1 <__flp+0x1>
    587e:	20 e0       	ldi	r18, 0x00	; 0
    5880:	30 e0       	ldi	r19, 0x00	; 0
    5882:	a0 e0       	ldi	r26, 0x00	; 0
    5884:	b0 e0       	ldi	r27, 0x00	; 0
    5886:	30 97       	sbiw	r30, 0x00	; 0
    5888:	19 f1       	breq	.+70     	; 0x58d0 <malloc+0x6c>
    588a:	40 81       	ld	r20, Z
    588c:	51 81       	ldd	r21, Z+1	; 0x01
    588e:	02 81       	ldd	r16, Z+2	; 0x02
    5890:	13 81       	ldd	r17, Z+3	; 0x03
    5892:	48 17       	cp	r20, r24
    5894:	59 07       	cpc	r21, r25
    5896:	c8 f0       	brcs	.+50     	; 0x58ca <malloc+0x66>
    5898:	84 17       	cp	r24, r20
    589a:	95 07       	cpc	r25, r21
    589c:	69 f4       	brne	.+26     	; 0x58b8 <malloc+0x54>
    589e:	10 97       	sbiw	r26, 0x00	; 0
    58a0:	31 f0       	breq	.+12     	; 0x58ae <malloc+0x4a>
    58a2:	12 96       	adiw	r26, 0x02	; 2
    58a4:	0c 93       	st	X, r16
    58a6:	12 97       	sbiw	r26, 0x02	; 2
    58a8:	13 96       	adiw	r26, 0x03	; 3
    58aa:	1c 93       	st	X, r17
    58ac:	27 c0       	rjmp	.+78     	; 0x58fc <malloc+0x98>
    58ae:	00 93 a0 04 	sts	0x04A0, r16	; 0x8004a0 <__flp>
    58b2:	10 93 a1 04 	sts	0x04A1, r17	; 0x8004a1 <__flp+0x1>
    58b6:	22 c0       	rjmp	.+68     	; 0x58fc <malloc+0x98>
    58b8:	21 15       	cp	r18, r1
    58ba:	31 05       	cpc	r19, r1
    58bc:	19 f0       	breq	.+6      	; 0x58c4 <malloc+0x60>
    58be:	42 17       	cp	r20, r18
    58c0:	53 07       	cpc	r21, r19
    58c2:	18 f4       	brcc	.+6      	; 0x58ca <malloc+0x66>
    58c4:	9a 01       	movw	r18, r20
    58c6:	bd 01       	movw	r22, r26
    58c8:	ef 01       	movw	r28, r30
    58ca:	df 01       	movw	r26, r30
    58cc:	f8 01       	movw	r30, r16
    58ce:	db cf       	rjmp	.-74     	; 0x5886 <malloc+0x22>
    58d0:	21 15       	cp	r18, r1
    58d2:	31 05       	cpc	r19, r1
    58d4:	f9 f0       	breq	.+62     	; 0x5914 <malloc+0xb0>
    58d6:	28 1b       	sub	r18, r24
    58d8:	39 0b       	sbc	r19, r25
    58da:	24 30       	cpi	r18, 0x04	; 4
    58dc:	31 05       	cpc	r19, r1
    58de:	80 f4       	brcc	.+32     	; 0x5900 <malloc+0x9c>
    58e0:	8a 81       	ldd	r24, Y+2	; 0x02
    58e2:	9b 81       	ldd	r25, Y+3	; 0x03
    58e4:	61 15       	cp	r22, r1
    58e6:	71 05       	cpc	r23, r1
    58e8:	21 f0       	breq	.+8      	; 0x58f2 <malloc+0x8e>
    58ea:	fb 01       	movw	r30, r22
    58ec:	93 83       	std	Z+3, r25	; 0x03
    58ee:	82 83       	std	Z+2, r24	; 0x02
    58f0:	04 c0       	rjmp	.+8      	; 0x58fa <malloc+0x96>
    58f2:	90 93 a1 04 	sts	0x04A1, r25	; 0x8004a1 <__flp+0x1>
    58f6:	80 93 a0 04 	sts	0x04A0, r24	; 0x8004a0 <__flp>
    58fa:	fe 01       	movw	r30, r28
    58fc:	32 96       	adiw	r30, 0x02	; 2
    58fe:	44 c0       	rjmp	.+136    	; 0x5988 <malloc+0x124>
    5900:	fe 01       	movw	r30, r28
    5902:	e2 0f       	add	r30, r18
    5904:	f3 1f       	adc	r31, r19
    5906:	81 93       	st	Z+, r24
    5908:	91 93       	st	Z+, r25
    590a:	22 50       	subi	r18, 0x02	; 2
    590c:	31 09       	sbc	r19, r1
    590e:	39 83       	std	Y+1, r19	; 0x01
    5910:	28 83       	st	Y, r18
    5912:	3a c0       	rjmp	.+116    	; 0x5988 <malloc+0x124>
    5914:	20 91 9e 04 	lds	r18, 0x049E	; 0x80049e <__brkval>
    5918:	30 91 9f 04 	lds	r19, 0x049F	; 0x80049f <__brkval+0x1>
    591c:	23 2b       	or	r18, r19
    591e:	41 f4       	brne	.+16     	; 0x5930 <malloc+0xcc>
    5920:	20 91 0a 01 	lds	r18, 0x010A	; 0x80010a <__malloc_heap_start>
    5924:	30 91 0b 01 	lds	r19, 0x010B	; 0x80010b <__malloc_heap_start+0x1>
    5928:	30 93 9f 04 	sts	0x049F, r19	; 0x80049f <__brkval+0x1>
    592c:	20 93 9e 04 	sts	0x049E, r18	; 0x80049e <__brkval>
    5930:	20 91 08 01 	lds	r18, 0x0108	; 0x800108 <__malloc_heap_end>
    5934:	30 91 09 01 	lds	r19, 0x0109	; 0x800109 <__malloc_heap_end+0x1>
    5938:	21 15       	cp	r18, r1
    593a:	31 05       	cpc	r19, r1
    593c:	41 f4       	brne	.+16     	; 0x594e <malloc+0xea>
    593e:	2d b7       	in	r18, 0x3d	; 61
    5940:	3e b7       	in	r19, 0x3e	; 62
    5942:	40 91 0c 01 	lds	r20, 0x010C	; 0x80010c <__malloc_margin>
    5946:	50 91 0d 01 	lds	r21, 0x010D	; 0x80010d <__malloc_margin+0x1>
    594a:	24 1b       	sub	r18, r20
    594c:	35 0b       	sbc	r19, r21
    594e:	e0 91 9e 04 	lds	r30, 0x049E	; 0x80049e <__brkval>
    5952:	f0 91 9f 04 	lds	r31, 0x049F	; 0x80049f <__brkval+0x1>
    5956:	e2 17       	cp	r30, r18
    5958:	f3 07       	cpc	r31, r19
    595a:	a0 f4       	brcc	.+40     	; 0x5984 <malloc+0x120>
    595c:	2e 1b       	sub	r18, r30
    595e:	3f 0b       	sbc	r19, r31
    5960:	28 17       	cp	r18, r24
    5962:	39 07       	cpc	r19, r25
    5964:	78 f0       	brcs	.+30     	; 0x5984 <malloc+0x120>
    5966:	ac 01       	movw	r20, r24
    5968:	4e 5f       	subi	r20, 0xFE	; 254
    596a:	5f 4f       	sbci	r21, 0xFF	; 255
    596c:	24 17       	cp	r18, r20
    596e:	35 07       	cpc	r19, r21
    5970:	48 f0       	brcs	.+18     	; 0x5984 <malloc+0x120>
    5972:	4e 0f       	add	r20, r30
    5974:	5f 1f       	adc	r21, r31
    5976:	50 93 9f 04 	sts	0x049F, r21	; 0x80049f <__brkval+0x1>
    597a:	40 93 9e 04 	sts	0x049E, r20	; 0x80049e <__brkval>
    597e:	81 93       	st	Z+, r24
    5980:	91 93       	st	Z+, r25
    5982:	02 c0       	rjmp	.+4      	; 0x5988 <malloc+0x124>
    5984:	e0 e0       	ldi	r30, 0x00	; 0
    5986:	f0 e0       	ldi	r31, 0x00	; 0
    5988:	cf 01       	movw	r24, r30
    598a:	df 91       	pop	r29
    598c:	cf 91       	pop	r28
    598e:	1f 91       	pop	r17
    5990:	0f 91       	pop	r16
    5992:	08 95       	ret

00005994 <free>:
    5994:	cf 93       	push	r28
    5996:	df 93       	push	r29
    5998:	00 97       	sbiw	r24, 0x00	; 0
    599a:	09 f4       	brne	.+2      	; 0x599e <free+0xa>
    599c:	81 c0       	rjmp	.+258    	; 0x5aa0 <free+0x10c>
    599e:	fc 01       	movw	r30, r24
    59a0:	32 97       	sbiw	r30, 0x02	; 2
    59a2:	13 82       	std	Z+3, r1	; 0x03
    59a4:	12 82       	std	Z+2, r1	; 0x02
    59a6:	a0 91 a0 04 	lds	r26, 0x04A0	; 0x8004a0 <__flp>
    59aa:	b0 91 a1 04 	lds	r27, 0x04A1	; 0x8004a1 <__flp+0x1>
    59ae:	10 97       	sbiw	r26, 0x00	; 0
    59b0:	81 f4       	brne	.+32     	; 0x59d2 <free+0x3e>
    59b2:	20 81       	ld	r18, Z
    59b4:	31 81       	ldd	r19, Z+1	; 0x01
    59b6:	82 0f       	add	r24, r18
    59b8:	93 1f       	adc	r25, r19
    59ba:	20 91 9e 04 	lds	r18, 0x049E	; 0x80049e <__brkval>
    59be:	30 91 9f 04 	lds	r19, 0x049F	; 0x80049f <__brkval+0x1>
    59c2:	28 17       	cp	r18, r24
    59c4:	39 07       	cpc	r19, r25
    59c6:	51 f5       	brne	.+84     	; 0x5a1c <free+0x88>
    59c8:	f0 93 9f 04 	sts	0x049F, r31	; 0x80049f <__brkval+0x1>
    59cc:	e0 93 9e 04 	sts	0x049E, r30	; 0x80049e <__brkval>
    59d0:	67 c0       	rjmp	.+206    	; 0x5aa0 <free+0x10c>
    59d2:	ed 01       	movw	r28, r26
    59d4:	20 e0       	ldi	r18, 0x00	; 0
    59d6:	30 e0       	ldi	r19, 0x00	; 0
    59d8:	ce 17       	cp	r28, r30
    59da:	df 07       	cpc	r29, r31
    59dc:	40 f4       	brcc	.+16     	; 0x59ee <free+0x5a>
    59de:	4a 81       	ldd	r20, Y+2	; 0x02
    59e0:	5b 81       	ldd	r21, Y+3	; 0x03
    59e2:	9e 01       	movw	r18, r28
    59e4:	41 15       	cp	r20, r1
    59e6:	51 05       	cpc	r21, r1
    59e8:	f1 f0       	breq	.+60     	; 0x5a26 <free+0x92>
    59ea:	ea 01       	movw	r28, r20
    59ec:	f5 cf       	rjmp	.-22     	; 0x59d8 <free+0x44>
    59ee:	d3 83       	std	Z+3, r29	; 0x03
    59f0:	c2 83       	std	Z+2, r28	; 0x02
    59f2:	40 81       	ld	r20, Z
    59f4:	51 81       	ldd	r21, Z+1	; 0x01
    59f6:	84 0f       	add	r24, r20
    59f8:	95 1f       	adc	r25, r21
    59fa:	c8 17       	cp	r28, r24
    59fc:	d9 07       	cpc	r29, r25
    59fe:	59 f4       	brne	.+22     	; 0x5a16 <free+0x82>
    5a00:	88 81       	ld	r24, Y
    5a02:	99 81       	ldd	r25, Y+1	; 0x01
    5a04:	84 0f       	add	r24, r20
    5a06:	95 1f       	adc	r25, r21
    5a08:	02 96       	adiw	r24, 0x02	; 2
    5a0a:	91 83       	std	Z+1, r25	; 0x01
    5a0c:	80 83       	st	Z, r24
    5a0e:	8a 81       	ldd	r24, Y+2	; 0x02
    5a10:	9b 81       	ldd	r25, Y+3	; 0x03
    5a12:	93 83       	std	Z+3, r25	; 0x03
    5a14:	82 83       	std	Z+2, r24	; 0x02
    5a16:	21 15       	cp	r18, r1
    5a18:	31 05       	cpc	r19, r1
    5a1a:	29 f4       	brne	.+10     	; 0x5a26 <free+0x92>
    5a1c:	f0 93 a1 04 	sts	0x04A1, r31	; 0x8004a1 <__flp+0x1>
    5a20:	e0 93 a0 04 	sts	0x04A0, r30	; 0x8004a0 <__flp>
    5a24:	3d c0       	rjmp	.+122    	; 0x5aa0 <free+0x10c>
    5a26:	e9 01       	movw	r28, r18
    5a28:	fb 83       	std	Y+3, r31	; 0x03
    5a2a:	ea 83       	std	Y+2, r30	; 0x02
    5a2c:	49 91       	ld	r20, Y+
    5a2e:	59 91       	ld	r21, Y+
    5a30:	c4 0f       	add	r28, r20
    5a32:	d5 1f       	adc	r29, r21
    5a34:	ec 17       	cp	r30, r28
    5a36:	fd 07       	cpc	r31, r29
    5a38:	61 f4       	brne	.+24     	; 0x5a52 <free+0xbe>
    5a3a:	80 81       	ld	r24, Z
    5a3c:	91 81       	ldd	r25, Z+1	; 0x01
    5a3e:	84 0f       	add	r24, r20
    5a40:	95 1f       	adc	r25, r21
    5a42:	02 96       	adiw	r24, 0x02	; 2
    5a44:	e9 01       	movw	r28, r18
    5a46:	99 83       	std	Y+1, r25	; 0x01
    5a48:	88 83       	st	Y, r24
    5a4a:	82 81       	ldd	r24, Z+2	; 0x02
    5a4c:	93 81       	ldd	r25, Z+3	; 0x03
    5a4e:	9b 83       	std	Y+3, r25	; 0x03
    5a50:	8a 83       	std	Y+2, r24	; 0x02
    5a52:	e0 e0       	ldi	r30, 0x00	; 0
    5a54:	f0 e0       	ldi	r31, 0x00	; 0
    5a56:	12 96       	adiw	r26, 0x02	; 2
    5a58:	8d 91       	ld	r24, X+
    5a5a:	9c 91       	ld	r25, X
    5a5c:	13 97       	sbiw	r26, 0x03	; 3
    5a5e:	00 97       	sbiw	r24, 0x00	; 0
    5a60:	19 f0       	breq	.+6      	; 0x5a68 <free+0xd4>
    5a62:	fd 01       	movw	r30, r26
    5a64:	dc 01       	movw	r26, r24
    5a66:	f7 cf       	rjmp	.-18     	; 0x5a56 <free+0xc2>
    5a68:	8d 91       	ld	r24, X+
    5a6a:	9c 91       	ld	r25, X
    5a6c:	11 97       	sbiw	r26, 0x01	; 1
    5a6e:	9d 01       	movw	r18, r26
    5a70:	2e 5f       	subi	r18, 0xFE	; 254
    5a72:	3f 4f       	sbci	r19, 0xFF	; 255
    5a74:	82 0f       	add	r24, r18
    5a76:	93 1f       	adc	r25, r19
    5a78:	20 91 9e 04 	lds	r18, 0x049E	; 0x80049e <__brkval>
    5a7c:	30 91 9f 04 	lds	r19, 0x049F	; 0x80049f <__brkval+0x1>
    5a80:	28 17       	cp	r18, r24
    5a82:	39 07       	cpc	r19, r25
    5a84:	69 f4       	brne	.+26     	; 0x5aa0 <free+0x10c>
    5a86:	30 97       	sbiw	r30, 0x00	; 0
    5a88:	29 f4       	brne	.+10     	; 0x5a94 <free+0x100>
    5a8a:	10 92 a1 04 	sts	0x04A1, r1	; 0x8004a1 <__flp+0x1>
    5a8e:	10 92 a0 04 	sts	0x04A0, r1	; 0x8004a0 <__flp>
    5a92:	02 c0       	rjmp	.+4      	; 0x5a98 <free+0x104>
    5a94:	13 82       	std	Z+3, r1	; 0x03
    5a96:	12 82       	std	Z+2, r1	; 0x02
    5a98:	b0 93 9f 04 	sts	0x049F, r27	; 0x80049f <__brkval+0x1>
    5a9c:	a0 93 9e 04 	sts	0x049E, r26	; 0x80049e <__brkval>
    5aa0:	df 91       	pop	r29
    5aa2:	cf 91       	pop	r28
    5aa4:	08 95       	ret

00005aa6 <realloc>:
    5aa6:	a0 e0       	ldi	r26, 0x00	; 0
    5aa8:	b0 e0       	ldi	r27, 0x00	; 0
    5aaa:	e9 e5       	ldi	r30, 0x59	; 89
    5aac:	fd e2       	ldi	r31, 0x2D	; 45
    5aae:	0c 94 af 25 	jmp	0x4b5e	; 0x4b5e <__prologue_saves__+0x8>
    5ab2:	ec 01       	movw	r28, r24
    5ab4:	00 97       	sbiw	r24, 0x00	; 0
    5ab6:	21 f4       	brne	.+8      	; 0x5ac0 <realloc+0x1a>
    5ab8:	cb 01       	movw	r24, r22
    5aba:	0e 94 32 2c 	call	0x5864	; 0x5864 <malloc>
    5abe:	b4 c0       	rjmp	.+360    	; 0x5c28 <realloc+0x182>
    5ac0:	fc 01       	movw	r30, r24
    5ac2:	e6 0f       	add	r30, r22
    5ac4:	f7 1f       	adc	r31, r23
    5ac6:	9c 01       	movw	r18, r24
    5ac8:	22 50       	subi	r18, 0x02	; 2
    5aca:	31 09       	sbc	r19, r1
    5acc:	e2 17       	cp	r30, r18
    5ace:	f3 07       	cpc	r31, r19
    5ad0:	08 f4       	brcc	.+2      	; 0x5ad4 <realloc+0x2e>
    5ad2:	a8 c0       	rjmp	.+336    	; 0x5c24 <realloc+0x17e>
    5ad4:	d9 01       	movw	r26, r18
    5ad6:	0d 91       	ld	r16, X+
    5ad8:	1c 91       	ld	r17, X
    5ada:	11 97       	sbiw	r26, 0x01	; 1
    5adc:	06 17       	cp	r16, r22
    5ade:	17 07       	cpc	r17, r23
    5ae0:	b0 f0       	brcs	.+44     	; 0x5b0e <realloc+0x68>
    5ae2:	05 30       	cpi	r16, 0x05	; 5
    5ae4:	11 05       	cpc	r17, r1
    5ae6:	08 f4       	brcc	.+2      	; 0x5aea <realloc+0x44>
    5ae8:	9b c0       	rjmp	.+310    	; 0x5c20 <realloc+0x17a>
    5aea:	c8 01       	movw	r24, r16
    5aec:	04 97       	sbiw	r24, 0x04	; 4
    5aee:	86 17       	cp	r24, r22
    5af0:	97 07       	cpc	r25, r23
    5af2:	08 f4       	brcc	.+2      	; 0x5af6 <realloc+0x50>
    5af4:	95 c0       	rjmp	.+298    	; 0x5c20 <realloc+0x17a>
    5af6:	02 50       	subi	r16, 0x02	; 2
    5af8:	11 09       	sbc	r17, r1
    5afa:	06 1b       	sub	r16, r22
    5afc:	17 0b       	sbc	r17, r23
    5afe:	01 93       	st	Z+, r16
    5b00:	11 93       	st	Z+, r17
    5b02:	6d 93       	st	X+, r22
    5b04:	7c 93       	st	X, r23
    5b06:	cf 01       	movw	r24, r30
    5b08:	0e 94 ca 2c 	call	0x5994	; 0x5994 <free>
    5b0c:	89 c0       	rjmp	.+274    	; 0x5c20 <realloc+0x17a>
    5b0e:	5b 01       	movw	r10, r22
    5b10:	a0 1a       	sub	r10, r16
    5b12:	b1 0a       	sbc	r11, r17
    5b14:	4c 01       	movw	r8, r24
    5b16:	80 0e       	add	r8, r16
    5b18:	91 1e       	adc	r9, r17
    5b1a:	a0 91 a0 04 	lds	r26, 0x04A0	; 0x8004a0 <__flp>
    5b1e:	b0 91 a1 04 	lds	r27, 0x04A1	; 0x8004a1 <__flp+0x1>
    5b22:	61 2c       	mov	r6, r1
    5b24:	71 2c       	mov	r7, r1
    5b26:	e1 2c       	mov	r14, r1
    5b28:	f1 2c       	mov	r15, r1
    5b2a:	10 97       	sbiw	r26, 0x00	; 0
    5b2c:	09 f4       	brne	.+2      	; 0x5b30 <realloc+0x8a>
    5b2e:	46 c0       	rjmp	.+140    	; 0x5bbc <realloc+0x116>
    5b30:	8d 91       	ld	r24, X+
    5b32:	9c 91       	ld	r25, X
    5b34:	11 97       	sbiw	r26, 0x01	; 1
    5b36:	a8 15       	cp	r26, r8
    5b38:	b9 05       	cpc	r27, r9
    5b3a:	b1 f5       	brne	.+108    	; 0x5ba8 <realloc+0x102>
    5b3c:	6c 01       	movw	r12, r24
    5b3e:	42 e0       	ldi	r20, 0x02	; 2
    5b40:	c4 0e       	add	r12, r20
    5b42:	d1 1c       	adc	r13, r1
    5b44:	ca 14       	cp	r12, r10
    5b46:	db 04       	cpc	r13, r11
    5b48:	78 f1       	brcs	.+94     	; 0x5ba8 <realloc+0x102>
    5b4a:	4c 01       	movw	r8, r24
    5b4c:	8a 18       	sub	r8, r10
    5b4e:	9b 08       	sbc	r9, r11
    5b50:	64 01       	movw	r12, r8
    5b52:	42 e0       	ldi	r20, 0x02	; 2
    5b54:	c4 0e       	add	r12, r20
    5b56:	d1 1c       	adc	r13, r1
    5b58:	12 96       	adiw	r26, 0x02	; 2
    5b5a:	bc 90       	ld	r11, X
    5b5c:	12 97       	sbiw	r26, 0x02	; 2
    5b5e:	13 96       	adiw	r26, 0x03	; 3
    5b60:	ac 91       	ld	r26, X
    5b62:	b5 e0       	ldi	r27, 0x05	; 5
    5b64:	cb 16       	cp	r12, r27
    5b66:	d1 04       	cpc	r13, r1
    5b68:	40 f0       	brcs	.+16     	; 0x5b7a <realloc+0xd4>
    5b6a:	b2 82       	std	Z+2, r11	; 0x02
    5b6c:	a3 83       	std	Z+3, r26	; 0x03
    5b6e:	91 82       	std	Z+1, r9	; 0x01
    5b70:	80 82       	st	Z, r8
    5b72:	d9 01       	movw	r26, r18
    5b74:	6d 93       	st	X+, r22
    5b76:	7c 93       	st	X, r23
    5b78:	09 c0       	rjmp	.+18     	; 0x5b8c <realloc+0xe6>
    5b7a:	0e 5f       	subi	r16, 0xFE	; 254
    5b7c:	1f 4f       	sbci	r17, 0xFF	; 255
    5b7e:	80 0f       	add	r24, r16
    5b80:	91 1f       	adc	r25, r17
    5b82:	f9 01       	movw	r30, r18
    5b84:	91 83       	std	Z+1, r25	; 0x01
    5b86:	80 83       	st	Z, r24
    5b88:	eb 2d       	mov	r30, r11
    5b8a:	fa 2f       	mov	r31, r26
    5b8c:	e1 14       	cp	r14, r1
    5b8e:	f1 04       	cpc	r15, r1
    5b90:	31 f0       	breq	.+12     	; 0x5b9e <realloc+0xf8>
    5b92:	d7 01       	movw	r26, r14
    5b94:	13 96       	adiw	r26, 0x03	; 3
    5b96:	fc 93       	st	X, r31
    5b98:	ee 93       	st	-X, r30
    5b9a:	12 97       	sbiw	r26, 0x02	; 2
    5b9c:	41 c0       	rjmp	.+130    	; 0x5c20 <realloc+0x17a>
    5b9e:	f0 93 a1 04 	sts	0x04A1, r31	; 0x8004a1 <__flp+0x1>
    5ba2:	e0 93 a0 04 	sts	0x04A0, r30	; 0x8004a0 <__flp>
    5ba6:	3c c0       	rjmp	.+120    	; 0x5c20 <realloc+0x17a>
    5ba8:	68 16       	cp	r6, r24
    5baa:	79 06       	cpc	r7, r25
    5bac:	08 f4       	brcc	.+2      	; 0x5bb0 <realloc+0x10a>
    5bae:	3c 01       	movw	r6, r24
    5bb0:	7d 01       	movw	r14, r26
    5bb2:	12 96       	adiw	r26, 0x02	; 2
    5bb4:	0d 90       	ld	r0, X+
    5bb6:	bc 91       	ld	r27, X
    5bb8:	a0 2d       	mov	r26, r0
    5bba:	b7 cf       	rjmp	.-146    	; 0x5b2a <realloc+0x84>
    5bbc:	80 91 9e 04 	lds	r24, 0x049E	; 0x80049e <__brkval>
    5bc0:	90 91 9f 04 	lds	r25, 0x049F	; 0x80049f <__brkval+0x1>
    5bc4:	88 16       	cp	r8, r24
    5bc6:	99 06       	cpc	r9, r25
    5bc8:	e1 f4       	brne	.+56     	; 0x5c02 <realloc+0x15c>
    5bca:	66 16       	cp	r6, r22
    5bcc:	77 06       	cpc	r7, r23
    5bce:	c8 f4       	brcc	.+50     	; 0x5c02 <realloc+0x15c>
    5bd0:	80 91 08 01 	lds	r24, 0x0108	; 0x800108 <__malloc_heap_end>
    5bd4:	90 91 09 01 	lds	r25, 0x0109	; 0x800109 <__malloc_heap_end+0x1>
    5bd8:	00 97       	sbiw	r24, 0x00	; 0
    5bda:	41 f4       	brne	.+16     	; 0x5bec <realloc+0x146>
    5bdc:	8d b7       	in	r24, 0x3d	; 61
    5bde:	9e b7       	in	r25, 0x3e	; 62
    5be0:	40 91 0c 01 	lds	r20, 0x010C	; 0x80010c <__malloc_margin>
    5be4:	50 91 0d 01 	lds	r21, 0x010D	; 0x80010d <__malloc_margin+0x1>
    5be8:	84 1b       	sub	r24, r20
    5bea:	95 0b       	sbc	r25, r21
    5bec:	e8 17       	cp	r30, r24
    5bee:	f9 07       	cpc	r31, r25
    5bf0:	c8 f4       	brcc	.+50     	; 0x5c24 <realloc+0x17e>
    5bf2:	f0 93 9f 04 	sts	0x049F, r31	; 0x80049f <__brkval+0x1>
    5bf6:	e0 93 9e 04 	sts	0x049E, r30	; 0x80049e <__brkval>
    5bfa:	f9 01       	movw	r30, r18
    5bfc:	71 83       	std	Z+1, r23	; 0x01
    5bfe:	60 83       	st	Z, r22
    5c00:	0f c0       	rjmp	.+30     	; 0x5c20 <realloc+0x17a>
    5c02:	cb 01       	movw	r24, r22
    5c04:	0e 94 32 2c 	call	0x5864	; 0x5864 <malloc>
    5c08:	7c 01       	movw	r14, r24
    5c0a:	00 97       	sbiw	r24, 0x00	; 0
    5c0c:	59 f0       	breq	.+22     	; 0x5c24 <realloc+0x17e>
    5c0e:	a8 01       	movw	r20, r16
    5c10:	be 01       	movw	r22, r28
    5c12:	0e 94 2b 2e 	call	0x5c56	; 0x5c56 <memcpy>
    5c16:	ce 01       	movw	r24, r28
    5c18:	0e 94 ca 2c 	call	0x5994	; 0x5994 <free>
    5c1c:	c7 01       	movw	r24, r14
    5c1e:	04 c0       	rjmp	.+8      	; 0x5c28 <realloc+0x182>
    5c20:	ce 01       	movw	r24, r28
    5c22:	02 c0       	rjmp	.+4      	; 0x5c28 <realloc+0x182>
    5c24:	80 e0       	ldi	r24, 0x00	; 0
    5c26:	90 e0       	ldi	r25, 0x00	; 0
    5c28:	cd b7       	in	r28, 0x3d	; 61
    5c2a:	de b7       	in	r29, 0x3e	; 62
    5c2c:	ee e0       	ldi	r30, 0x0E	; 14
    5c2e:	0c 94 cb 25 	jmp	0x4b96	; 0x4b96 <__epilogue_restores__+0x8>

00005c32 <abort>:
    5c32:	81 e0       	ldi	r24, 0x01	; 1
    5c34:	90 e0       	ldi	r25, 0x00	; 0
    5c36:	f8 94       	cli
    5c38:	0c 94 a2 2e 	jmp	0x5d44	; 0x5d44 <__do_global_dtors>

00005c3c <memcmp>:
    5c3c:	fb 01       	movw	r30, r22
    5c3e:	dc 01       	movw	r26, r24
    5c40:	04 c0       	rjmp	.+8      	; 0x5c4a <memcmp+0xe>
    5c42:	8d 91       	ld	r24, X+
    5c44:	01 90       	ld	r0, Z+
    5c46:	80 19       	sub	r24, r0
    5c48:	21 f4       	brne	.+8      	; 0x5c52 <memcmp+0x16>
    5c4a:	41 50       	subi	r20, 0x01	; 1
    5c4c:	50 40       	sbci	r21, 0x00	; 0
    5c4e:	c8 f7       	brcc	.-14     	; 0x5c42 <memcmp+0x6>
    5c50:	88 1b       	sub	r24, r24
    5c52:	99 0b       	sbc	r25, r25
    5c54:	08 95       	ret

00005c56 <memcpy>:
    5c56:	fb 01       	movw	r30, r22
    5c58:	dc 01       	movw	r26, r24
    5c5a:	02 c0       	rjmp	.+4      	; 0x5c60 <memcpy+0xa>
    5c5c:	01 90       	ld	r0, Z+
    5c5e:	0d 92       	st	X+, r0
    5c60:	41 50       	subi	r20, 0x01	; 1
    5c62:	50 40       	sbci	r21, 0x00	; 0
    5c64:	d8 f7       	brcc	.-10     	; 0x5c5c <memcpy+0x6>
    5c66:	08 95       	ret

00005c68 <strchr>:
    5c68:	fc 01       	movw	r30, r24
    5c6a:	81 91       	ld	r24, Z+
    5c6c:	86 17       	cp	r24, r22
    5c6e:	21 f0       	breq	.+8      	; 0x5c78 <strchr+0x10>
    5c70:	88 23       	and	r24, r24
    5c72:	d9 f7       	brne	.-10     	; 0x5c6a <strchr+0x2>
    5c74:	99 27       	eor	r25, r25
    5c76:	08 95       	ret
    5c78:	31 97       	sbiw	r30, 0x01	; 1
    5c7a:	cf 01       	movw	r24, r30
    5c7c:	08 95       	ret

00005c7e <strcpy>:
    5c7e:	fb 01       	movw	r30, r22
    5c80:	dc 01       	movw	r26, r24
    5c82:	01 90       	ld	r0, Z+
    5c84:	0d 92       	st	X+, r0
    5c86:	00 20       	and	r0, r0
    5c88:	e1 f7       	brne	.-8      	; 0x5c82 <strcpy+0x4>
    5c8a:	08 95       	ret

00005c8c <snprintf>:
    5c8c:	ae e0       	ldi	r26, 0x0E	; 14
    5c8e:	b0 e0       	ldi	r27, 0x00	; 0
    5c90:	ec e4       	ldi	r30, 0x4C	; 76
    5c92:	fe e2       	ldi	r31, 0x2E	; 46
    5c94:	0c 94 b9 25 	jmp	0x4b72	; 0x4b72 <__prologue_saves__+0x1c>
    5c98:	0d 89       	ldd	r16, Y+21	; 0x15
    5c9a:	1e 89       	ldd	r17, Y+22	; 0x16
    5c9c:	8f 89       	ldd	r24, Y+23	; 0x17
    5c9e:	98 8d       	ldd	r25, Y+24	; 0x18
    5ca0:	26 e0       	ldi	r18, 0x06	; 6
    5ca2:	2c 83       	std	Y+4, r18	; 0x04
    5ca4:	1a 83       	std	Y+2, r17	; 0x02
    5ca6:	09 83       	std	Y+1, r16	; 0x01
    5ca8:	97 ff       	sbrs	r25, 7
    5caa:	02 c0       	rjmp	.+4      	; 0x5cb0 <snprintf+0x24>
    5cac:	80 e0       	ldi	r24, 0x00	; 0
    5cae:	90 e8       	ldi	r25, 0x80	; 128
    5cb0:	01 97       	sbiw	r24, 0x01	; 1
    5cb2:	9e 83       	std	Y+6, r25	; 0x06
    5cb4:	8d 83       	std	Y+5, r24	; 0x05
    5cb6:	ae 01       	movw	r20, r28
    5cb8:	45 5e       	subi	r20, 0xE5	; 229
    5cba:	5f 4f       	sbci	r21, 0xFF	; 255
    5cbc:	69 8d       	ldd	r22, Y+25	; 0x19
    5cbe:	7a 8d       	ldd	r23, Y+26	; 0x1a
    5cc0:	ce 01       	movw	r24, r28
    5cc2:	01 96       	adiw	r24, 0x01	; 1
    5cc4:	0e 94 2e 22 	call	0x445c	; 0x445c <vfprintf>
    5cc8:	4d 81       	ldd	r20, Y+5	; 0x05
    5cca:	5e 81       	ldd	r21, Y+6	; 0x06
    5ccc:	57 fd       	sbrc	r21, 7
    5cce:	0a c0       	rjmp	.+20     	; 0x5ce4 <snprintf+0x58>
    5cd0:	2f 81       	ldd	r18, Y+7	; 0x07
    5cd2:	38 85       	ldd	r19, Y+8	; 0x08
    5cd4:	42 17       	cp	r20, r18
    5cd6:	53 07       	cpc	r21, r19
    5cd8:	0c f4       	brge	.+2      	; 0x5cdc <snprintf+0x50>
    5cda:	9a 01       	movw	r18, r20
    5cdc:	f8 01       	movw	r30, r16
    5cde:	e2 0f       	add	r30, r18
    5ce0:	f3 1f       	adc	r31, r19
    5ce2:	10 82       	st	Z, r1
    5ce4:	2e 96       	adiw	r28, 0x0e	; 14
    5ce6:	e4 e0       	ldi	r30, 0x04	; 4
    5ce8:	0c 94 d5 25 	jmp	0x4baa	; 0x4baa <__epilogue_restores__+0x1c>

00005cec <vsnprintf>:
    5cec:	ae e0       	ldi	r26, 0x0E	; 14
    5cee:	b0 e0       	ldi	r27, 0x00	; 0
    5cf0:	ec e7       	ldi	r30, 0x7C	; 124
    5cf2:	fe e2       	ldi	r31, 0x2E	; 46
    5cf4:	0c 94 b9 25 	jmp	0x4b72	; 0x4b72 <__prologue_saves__+0x1c>
    5cf8:	8c 01       	movw	r16, r24
    5cfa:	fa 01       	movw	r30, r20
    5cfc:	86 e0       	ldi	r24, 0x06	; 6
    5cfe:	8c 83       	std	Y+4, r24	; 0x04
    5d00:	1a 83       	std	Y+2, r17	; 0x02
    5d02:	09 83       	std	Y+1, r16	; 0x01
    5d04:	77 ff       	sbrs	r23, 7
    5d06:	02 c0       	rjmp	.+4      	; 0x5d0c <vsnprintf+0x20>
    5d08:	60 e0       	ldi	r22, 0x00	; 0
    5d0a:	70 e8       	ldi	r23, 0x80	; 128
    5d0c:	cb 01       	movw	r24, r22
    5d0e:	01 97       	sbiw	r24, 0x01	; 1
    5d10:	9e 83       	std	Y+6, r25	; 0x06
    5d12:	8d 83       	std	Y+5, r24	; 0x05
    5d14:	a9 01       	movw	r20, r18
    5d16:	bf 01       	movw	r22, r30
    5d18:	ce 01       	movw	r24, r28
    5d1a:	01 96       	adiw	r24, 0x01	; 1
    5d1c:	0e 94 2e 22 	call	0x445c	; 0x445c <vfprintf>
    5d20:	4d 81       	ldd	r20, Y+5	; 0x05
    5d22:	5e 81       	ldd	r21, Y+6	; 0x06
    5d24:	57 fd       	sbrc	r21, 7
    5d26:	0a c0       	rjmp	.+20     	; 0x5d3c <vsnprintf+0x50>
    5d28:	2f 81       	ldd	r18, Y+7	; 0x07
    5d2a:	38 85       	ldd	r19, Y+8	; 0x08
    5d2c:	42 17       	cp	r20, r18
    5d2e:	53 07       	cpc	r21, r19
    5d30:	0c f4       	brge	.+2      	; 0x5d34 <vsnprintf+0x48>
    5d32:	9a 01       	movw	r18, r20
    5d34:	f8 01       	movw	r30, r16
    5d36:	e2 0f       	add	r30, r18
    5d38:	f3 1f       	adc	r31, r19
    5d3a:	10 82       	st	Z, r1
    5d3c:	2e 96       	adiw	r28, 0x0e	; 14
    5d3e:	e4 e0       	ldi	r30, 0x04	; 4
    5d40:	0c 94 d5 25 	jmp	0x4baa	; 0x4baa <__epilogue_restores__+0x1c>

00005d44 <__do_global_dtors>:
    5d44:	12 e0       	ldi	r17, 0x02	; 2
    5d46:	c3 ea       	ldi	r28, 0xA3	; 163
    5d48:	d2 e0       	ldi	r29, 0x02	; 2
    5d4a:	04 c0       	rjmp	.+8      	; 0x5d54 <__do_global_dtors+0x10>
    5d4c:	fe 01       	movw	r30, r28
    5d4e:	0e 94 88 2a 	call	0x5510	; 0x5510 <__tablejump2__>
    5d52:	21 96       	adiw	r28, 0x01	; 1
    5d54:	c4 3a       	cpi	r28, 0xA4	; 164
    5d56:	d1 07       	cpc	r29, r17
    5d58:	c9 f7       	brne	.-14     	; 0x5d4c <__do_global_dtors+0x8>
    5d5a:	f8 94       	cli

00005d5c <__stop_program>:
    5d5c:	ff cf       	rjmp	.-2      	; 0x5d5c <__stop_program>
