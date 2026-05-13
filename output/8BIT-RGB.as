opt subtitle "Microchip Technology Omniscient Code Generator v1.45 (PRO mode) build 201711160504"

opt pagewidth 120

	opt pm

	processor	SC8F072
opt include "F:\Program Files\SCMCU_IDE_V2.00.16\data\include\sc8f072.cgen.inc"
clrc	macro
	bcf	3,0
	endm
clrz	macro
	bcf	3,2
	endm
setc	macro
	bsf	3,0
	endm
setz	macro
	bsf	3,2
	endm
skipc	macro
	btfss	3,0
	endm
skipz	macro
	btfss	3,2
	endm
skipnc	macro
	btfsc	3,0
	endm
skipnz	macro
	btfsc	3,2
	endm
	FNCALL	_main,_delay_ms
	FNCALL	_main,_effect_init
	FNCALL	_main,_effects_update
	FNCALL	_main,_key_scan
	FNCALL	_main,_system_clock_init
	FNCALL	_main,_ws2812_gpio_init
	FNCALL	_main,_ws2812_update_RGB
	FNCALL	_key_scan,___awmod
	FNCALL	_key_scan,_delay_ms
	FNCALL	_key_scan,_effect_execute
	FNCALL	_key_scan,_ws2812_update_RGB
	FNCALL	_ws2812_update_RGB,___awmod
	FNCALL	_ws2812_update_RGB,_effect_execute
	FNCALL	_ws2812_update_RGB,_ws2812_reset
	FNCALL	_ws2812_update_RGB,_ws2812_send_color
	FNCALL	_ws2812_send_color,_ws2812_send_byte
	FNCALL	_ws2812_reset,_delay_ms
	FNCALL	_effect_execute,_breath_init
	FNCALL	_effect_execute,_chase_init
	FNCALL	_effect_execute,_expand_init
	FNCALL	_effect_execute,_marquee_init
	FNCALL	_effect_execute,_police_init
	FNCALL	_effect_execute,_stack_init
	FNCALL	_effect_execute,_twinkle_init
	FNCALL	_effects_update,_breath_update
	FNCALL	_effects_update,_chase_update
	FNCALL	_effects_update,_expand_update
	FNCALL	_effects_update,_marquee_update
	FNCALL	_effects_update,_police_update
	FNCALL	_effects_update,_stack_update
	FNCALL	_effects_update,_twinkle_update
	FNCALL	_twinkle_update,___awdiv
	FNCALL	_twinkle_update,___awmod
	FNCALL	_twinkle_update,___bmul
	FNCALL	_twinkle_update,___wmul
	FNCALL	_stack_update,_stack_init
	FNCALL	_marquee_update,___awmod
	FNCALL	_expand_update,___awmod
	FNCALL	_expand_update,_random_value
	FNCALL	_random_value,___wmul
	FNCALL	_chase_update,___awmod
	FNCALL	_breath_update,___awmod
	FNCALL	_breath_update,___bmul
	FNCALL	_effect_init,_breath_init
	FNCALL	_effect_init,_chase_init
	FNCALL	_effect_init,_expand_init
	FNCALL	_effect_init,_marquee_init
	FNCALL	_effect_init,_police_init
	FNCALL	_effect_init,_stack_init
	FNCALL	_effect_init,_twinkle_init
	FNCALL	_twinkle_init,___bmul
	FNCALL	_twinkle_init,___lwmod
	FNCALL	_twinkle_init,___wmul
	FNROOT	_main
	global	random_value@rand_state
	global	_power_state
	global	_stack_target
	global	_expand_seed
	global	_expand_r
	global	_expand_dir
	global	_breath_val
	global	_breath_dir
psect	idataBANK0,class=CODE,space=0,delta=2,noexec
global __pidataBANK0
__pidataBANK0:
	file	"H:\8bit-RGB\effects.c"
	line	222

;initializer for random_value@rand_state
	retlw	039h
	retlw	030h

	file	"H:\8bit-RGB\main.c"
	line	157

;initializer for _power_state
	retlw	01h
	file	"H:\8bit-RGB\effects.c"
	line	355

;initializer for _stack_target
	retlw	017h
	line	219

;initializer for _expand_seed
	retlw	01h
	line	218

;initializer for _expand_r
	retlw	0FFh
	line	217

;initializer for _expand_dir
	retlw	01h
	line	11

;initializer for _breath_val
	retlw	019h
	line	12

;initializer for _breath_dir
	retlw	01h
	global	_effects
psect	strings,class=STRING,delta=2,noexec
global __pstrings
__pstrings:
stringtab:
	global    __stringtab
__stringtab:
;	String table - string pointers are 1 byte each
stringcode:stringdir:
movlw high(stringdir)
movwf pclath
movf fsr,w
incf fsr
	addwf pc
	global __stringbase
__stringbase:
	retlw	0
psect	strings
	global    __end_of__stringtab
__end_of__stringtab:
	file	"H:\8bit-RGB\effects.c"
	line	453
_effects:
	retlw	low((fp__breath_init-fpbase))
	retlw	low((fp__breath_update-fpbase))
	retlw	low((fp__twinkle_init-fpbase))
	retlw	low((fp__twinkle_update-fpbase))
	retlw	low((fp__chase_init-fpbase))
	retlw	low((fp__chase_update-fpbase))
	retlw	low((fp__expand_init-fpbase))
	retlw	low((fp__expand_update-fpbase))
	retlw	low((fp__marquee_init-fpbase))
	retlw	low((fp__marquee_update-fpbase))
	retlw	low((fp__stack_init-fpbase))
	retlw	low((fp__stack_update-fpbase))
	retlw	low((fp__police_init-fpbase))
	retlw	low((fp__police_update-fpbase))
	global __end_of_effects
__end_of_effects:
	global	_effects
	global	_stars
	global	_system_tick_ms
	global	_key_pressed
	global	_key_press_counter
	global	_police_counter
	global	_police_state
	global	stack_update@counter
	global	_stack_delay
	global	_stack_lit_count
	global	_stack_runner
	global	marquee_update@color_index
	global	marquee_update@counter
	global	_marquee_pos
	global	expand_update@counter
	global	_expand_b
	global	_expand_g
	global	_expand_size
	global	chase_update@counter
	global	_chase_color_idx
	global	_chase_pos
	global	_twinkle_counter
	global	breath_update@counter
	global	_breath_transition
	global	_breath_color
	global	_current_effect
	global	_leds
	global	_OSCCON
_OSCCON	set	20
	global	_TRISB
_TRISB	set	5
	global	_GIE
_GIE	set	95
	global	_RB1
_RB1	set	49
	global	_ANSEL1
_ANSEL1	set	148
	global	_ANSEL0
_ANSEL0	set	147
	global	_WPUA
_WPUA	set	136
	global	_TRISA
_TRISA	set	133
	global	_RA0
_RA0	set	1072
; #config settings
	file	"8BIT-RGB.as"
	line	#
psect cinit,class=CODE,delta=2
global start_initialization
start_initialization:

global __initialization
__initialization:
psect	bssBANK0,class=BANK0,space=1,noexec
global __pbssBANK0
__pbssBANK0:
_stars:
       ds      24

_system_tick_ms:
       ds      2

_key_pressed:
       ds      1

_key_press_counter:
       ds      1

_police_counter:
       ds      1

_police_state:
       ds      1

stack_update@counter:
       ds      1

_stack_delay:
       ds      1

_stack_lit_count:
       ds      1

_stack_runner:
       ds      1

marquee_update@color_index:
       ds      1

marquee_update@counter:
       ds      1

_marquee_pos:
       ds      1

expand_update@counter:
       ds      1

_expand_b:
       ds      1

_expand_g:
       ds      1

_expand_size:
       ds      1

chase_update@counter:
       ds      1

_chase_color_idx:
       ds      1

_chase_pos:
       ds      1

_twinkle_counter:
       ds      1

breath_update@counter:
       ds      1

_breath_transition:
       ds      1

_breath_color:
       ds      1

_current_effect:
       ds      1

psect	dataBANK0,class=BANK0,space=1,noexec
global __pdataBANK0
__pdataBANK0:
	file	"H:\8bit-RGB\effects.c"
	line	222
random_value@rand_state:
       ds      2

psect	dataBANK0
	file	"H:\8bit-RGB\main.c"
	line	157
_power_state:
       ds      1

psect	dataBANK0
	file	"H:\8bit-RGB\effects.c"
	line	355
_stack_target:
       ds      1

psect	dataBANK0
	file	"H:\8bit-RGB\effects.c"
	line	219
_expand_seed:
       ds      1

psect	dataBANK0
	file	"H:\8bit-RGB\effects.c"
	line	218
_expand_r:
       ds      1

psect	dataBANK0
	file	"H:\8bit-RGB\effects.c"
	line	217
_expand_dir:
       ds      1

psect	dataBANK0
	file	"H:\8bit-RGB\effects.c"
	line	11
_breath_val:
       ds      1

psect	dataBANK0
	file	"H:\8bit-RGB\effects.c"
	line	12
_breath_dir:
       ds      1

psect	bssBANK1,class=BANK1,space=1,noexec
global __pbssBANK1
__pbssBANK1:
_leds:
       ds      72

	file	"8BIT-RGB.as"
	line	#
; Initialize objects allocated to BANK0
	global __pidataBANK0
psect cinit,class=CODE,delta=2,merge=1
	fcall	__pidataBANK0+0		;fetch initializer
	movwf	__pdataBANK0+0&07fh		
	fcall	__pidataBANK0+1		;fetch initializer
	movwf	__pdataBANK0+1&07fh		
	fcall	__pidataBANK0+2		;fetch initializer
	movwf	__pdataBANK0+2&07fh		
	fcall	__pidataBANK0+3		;fetch initializer
	movwf	__pdataBANK0+3&07fh		
	fcall	__pidataBANK0+4		;fetch initializer
	movwf	__pdataBANK0+4&07fh		
	fcall	__pidataBANK0+5		;fetch initializer
	movwf	__pdataBANK0+5&07fh		
	fcall	__pidataBANK0+6		;fetch initializer
	movwf	__pdataBANK0+6&07fh		
	fcall	__pidataBANK0+7		;fetch initializer
	movwf	__pdataBANK0+7&07fh		
	fcall	__pidataBANK0+8		;fetch initializer
	movwf	__pdataBANK0+8&07fh		
	line	#
psect clrtext,class=CODE,delta=2
global clear_ram0
;	Called with FSR containing the base address, and
;	W with the last address+1
clear_ram0:
	clrwdt			;clear the watchdog before getting into this loop
clrloop0:
	clrf	indf		;clear RAM location pointed to by FSR
	incf	fsr,f		;increment pointer
	xorwf	fsr,w		;XOR with final address
	btfsc	status,2	;have we reached the end yet?
	retlw	0		;all done for this memory range, return
	xorwf	fsr,w		;XOR again to restore value
	goto	clrloop0		;do the next byte

; Clear objects allocated to BANK1
psect cinit,class=CODE,delta=2,merge=1
	bcf	status, 7	;select IRP bank0
	movlw	low(__pbssBANK1)
	movwf	fsr
	movlw	low((__pbssBANK1)+048h)
	fcall	clear_ram0
; Clear objects allocated to BANK0
psect cinit,class=CODE,delta=2,merge=1
	movlw	low(__pbssBANK0)
	movwf	fsr
	movlw	low((__pbssBANK0)+031h)
	fcall	clear_ram0
psect cinit,class=CODE,delta=2,merge=1
global end_of_initialization,__end_of__initialization

;End of C runtime variable initialization code

end_of_initialization:
__end_of__initialization:
clrf status
ljmp _main	;jump to C main() function
psect	cstackCOMMON,class=COMMON,space=1,noexec
global __pcstackCOMMON
__pcstackCOMMON:
?_breath_init:	; 1 bytes @ 0x0
??_breath_init:	; 1 bytes @ 0x0
?_breath_update:	; 1 bytes @ 0x0
?_twinkle_init:	; 1 bytes @ 0x0
?_twinkle_update:	; 1 bytes @ 0x0
?_chase_init:	; 1 bytes @ 0x0
??_chase_init:	; 1 bytes @ 0x0
?_chase_update:	; 1 bytes @ 0x0
?_random_value:	; 1 bytes @ 0x0
?_expand_init:	; 1 bytes @ 0x0
??_expand_init:	; 1 bytes @ 0x0
?_expand_update:	; 1 bytes @ 0x0
?_marquee_init:	; 1 bytes @ 0x0
??_marquee_init:	; 1 bytes @ 0x0
?_marquee_update:	; 1 bytes @ 0x0
?_stack_init:	; 1 bytes @ 0x0
??_stack_init:	; 1 bytes @ 0x0
?_stack_update:	; 1 bytes @ 0x0
?_police_init:	; 1 bytes @ 0x0
??_police_init:	; 1 bytes @ 0x0
?_police_update:	; 1 bytes @ 0x0
??_police_update:	; 1 bytes @ 0x0
?_effect_init:	; 1 bytes @ 0x0
?_effect_execute:	; 1 bytes @ 0x0
?_effects_update:	; 1 bytes @ 0x0
?_system_clock_init:	; 1 bytes @ 0x0
??_system_clock_init:	; 1 bytes @ 0x0
?_delay_ms:	; 1 bytes @ 0x0
?_ws2812_send_byte:	; 1 bytes @ 0x0
??_ws2812_send_byte:	; 1 bytes @ 0x0
?_ws2812_reset:	; 1 bytes @ 0x0
?_ws2812_gpio_init:	; 1 bytes @ 0x0
??_ws2812_gpio_init:	; 1 bytes @ 0x0
?_key_scan:	; 1 bytes @ 0x0
?_main:	; 1 bytes @ 0x0
?___bmul:	; 1 bytes @ 0x0
	global	?___wmul
?___wmul:	; 2 bytes @ 0x0
	global	?___awmod
?___awmod:	; 2 bytes @ 0x0
	global	chase_init@i
chase_init@i:	; 1 bytes @ 0x0
	global	expand_init@i
expand_init@i:	; 1 bytes @ 0x0
	global	marquee_init@i
marquee_init@i:	; 1 bytes @ 0x0
	global	stack_init@i
stack_init@i:	; 1 bytes @ 0x0
	global	police_init@i
police_init@i:	; 1 bytes @ 0x0
	global	police_update@g
police_update@g:	; 1 bytes @ 0x0
	global	system_clock_init@i
system_clock_init@i:	; 1 bytes @ 0x0
	global	ws2812_send_byte@byte
ws2812_send_byte@byte:	; 1 bytes @ 0x0
	global	___bmul@multiplicand
___bmul@multiplicand:	; 1 bytes @ 0x0
	global	delay_ms@ms
delay_ms@ms:	; 2 bytes @ 0x0
	global	___wmul@multiplier
___wmul@multiplier:	; 2 bytes @ 0x0
	global	___awmod@divisor
___awmod@divisor:	; 2 bytes @ 0x0
	ds	1
??_stack_update:	; 1 bytes @ 0x1
?_ws2812_send_color:	; 1 bytes @ 0x1
??___bmul:	; 1 bytes @ 0x1
	global	marquee_init@i_407
marquee_init@i_407:	; 1 bytes @ 0x1
	global	stack_update@i
stack_update@i:	; 1 bytes @ 0x1
	global	police_update@r
police_update@r:	; 1 bytes @ 0x1
	global	___bmul@product
___bmul@product:	; 1 bytes @ 0x1
	global	ws2812_send_color@color
ws2812_send_color@color:	; 3 bytes @ 0x1
	ds	1
??_delay_ms:	; 1 bytes @ 0x2
	global	stack_update@i_428
stack_update@i_428:	; 1 bytes @ 0x2
	global	police_update@b
police_update@b:	; 1 bytes @ 0x2
	global	___bmul@multiplier
___bmul@multiplier:	; 1 bytes @ 0x2
	global	delay_ms@i
delay_ms@i:	; 2 bytes @ 0x2
	global	___wmul@multiplicand
___wmul@multiplicand:	; 2 bytes @ 0x2
	global	___awmod@dividend
___awmod@dividend:	; 2 bytes @ 0x2
	ds	1
	global	police_update@i
police_update@i:	; 1 bytes @ 0x3
	ds	1
??_ws2812_send_color:	; 1 bytes @ 0x4
??___wmul:	; 1 bytes @ 0x4
??___awmod:	; 1 bytes @ 0x4
	global	___awmod@counter
___awmod@counter:	; 1 bytes @ 0x4
	global	delay_ms@j
delay_ms@j:	; 2 bytes @ 0x4
	global	___wmul@product
___wmul@product:	; 2 bytes @ 0x4
	ds	1
	global	___awmod@sign
___awmod@sign:	; 1 bytes @ 0x5
	ds	1
??_breath_update:	; 1 bytes @ 0x6
??_chase_update:	; 1 bytes @ 0x6
??_random_value:	; 1 bytes @ 0x6
??_marquee_update:	; 1 bytes @ 0x6
??_ws2812_reset:	; 1 bytes @ 0x6
	global	?___awdiv
?___awdiv:	; 2 bytes @ 0x6
	global	?___lwmod
?___lwmod:	; 2 bytes @ 0x6
	global	breath_update@r
breath_update@r:	; 1 bytes @ 0x6
	global	chase_update@old_pos
chase_update@old_pos:	; 1 bytes @ 0x6
	global	marquee_update@old_pos
marquee_update@old_pos:	; 1 bytes @ 0x6
	global	___awdiv@divisor
___awdiv@divisor:	; 2 bytes @ 0x6
	global	___lwmod@divisor
___lwmod@divisor:	; 2 bytes @ 0x6
	ds	1
	global	breath_update@g
breath_update@g:	; 1 bytes @ 0x7
	global	chase_update@r
chase_update@r:	; 1 bytes @ 0x7
	global	marquee_update@r
marquee_update@r:	; 1 bytes @ 0x7
	ds	1
	global	breath_update@b
breath_update@b:	; 1 bytes @ 0x8
	global	chase_update@g
chase_update@g:	; 1 bytes @ 0x8
	global	random_value@seed
random_value@seed:	; 1 bytes @ 0x8
	global	marquee_update@g
marquee_update@g:	; 1 bytes @ 0x8
	global	___awdiv@dividend
___awdiv@dividend:	; 2 bytes @ 0x8
	global	___lwmod@dividend
___lwmod@dividend:	; 2 bytes @ 0x8
	ds	1
??_expand_update:	; 1 bytes @ 0x9
	global	breath_update@old_val
breath_update@old_val:	; 1 bytes @ 0x9
	global	chase_update@b
chase_update@b:	; 1 bytes @ 0x9
	global	expand_update@left
expand_update@left:	; 1 bytes @ 0x9
	global	marquee_update@b
marquee_update@b:	; 1 bytes @ 0x9
	ds	1
??___awdiv:	; 1 bytes @ 0xA
??___lwmod:	; 1 bytes @ 0xA
	global	breath_update@new_val
breath_update@new_val:	; 1 bytes @ 0xA
	global	chase_update@pos
chase_update@pos:	; 1 bytes @ 0xA
	global	expand_update@right
expand_update@right:	; 1 bytes @ 0xA
	global	marquee_update@pos
marquee_update@pos:	; 1 bytes @ 0xA
	global	___awdiv@counter
___awdiv@counter:	; 1 bytes @ 0xA
	global	___lwmod@counter
___lwmod@counter:	; 1 bytes @ 0xA
	ds	1
??_twinkle_init:	; 1 bytes @ 0xB
	global	breath_update@i
breath_update@i:	; 1 bytes @ 0xB
	global	twinkle_init@i
twinkle_init@i:	; 1 bytes @ 0xB
	global	chase_update@i_382
chase_update@i_382:	; 1 bytes @ 0xB
	global	expand_update@left_402
expand_update@left_402:	; 1 bytes @ 0xB
	global	marquee_update@i_415
marquee_update@i_415:	; 1 bytes @ 0xB
	global	___awdiv@sign
___awdiv@sign:	; 1 bytes @ 0xB
	ds	1
	global	twinkle_init@i_363
twinkle_init@i_363:	; 1 bytes @ 0xC
	global	chase_update@i
chase_update@i:	; 1 bytes @ 0xC
	global	expand_update@right_403
expand_update@right_403:	; 1 bytes @ 0xC
	global	marquee_update@i
marquee_update@i:	; 1 bytes @ 0xC
	global	___awdiv@quotient
___awdiv@quotient:	; 2 bytes @ 0xC
	ds	1
??_effect_init:	; 1 bytes @ 0xD
??_effect_execute:	; 1 bytes @ 0xD
	global	expand_update@i
expand_update@i:	; 1 bytes @ 0xD
	global	effect_execute@mode
effect_execute@mode:	; 1 bytes @ 0xD
	ds	1
??_effects_update:	; 1 bytes @ 0xE
??_key_scan:	; 1 bytes @ 0xE
??_main:	; 1 bytes @ 0xE
psect	cstackBANK0,class=BANK0,space=1,noexec
global __pcstackBANK0
__pcstackBANK0:
??_twinkle_update:	; 1 bytes @ 0x0
?_ws2812_update_RGB:	; 1 bytes @ 0x0
	global	ws2812_update_RGB@num
ws2812_update_RGB@num:	; 1 bytes @ 0x0
	ds	1
??_ws2812_update_RGB:	; 1 bytes @ 0x1
	ds	1
	global	twinkle_update@color
twinkle_update@color:	; 1 bytes @ 0x2
	global	ws2812_update_RGB@next_mode
ws2812_update_RGB@next_mode:	; 1 bytes @ 0x2
	ds	1
	global	twinkle_update@brightness
twinkle_update@brightness:	; 1 bytes @ 0x3
	global	ws2812_update_RGB@key_was_pressed
ws2812_update_RGB@key_was_pressed:	; 1 bytes @ 0x3
	ds	1
	global	twinkle_update@i
twinkle_update@i:	; 1 bytes @ 0x4
	global	ws2812_update_RGB@leds
ws2812_update_RGB@leds:	; 1 bytes @ 0x4
	ds	1
	global	twinkle_update@i_369
twinkle_update@i_369:	; 1 bytes @ 0x5
	global	ws2812_update_RGB@i
ws2812_update_RGB@i:	; 1 bytes @ 0x5
	ds	1
	global	key_scan@next_mode
key_scan@next_mode:	; 1 bytes @ 0x6
	ds	1
	global	key_scan@i
key_scan@i:	; 1 bytes @ 0x7
	ds	1
	global	main@update_counter
main@update_counter:	; 2 bytes @ 0x8
	ds	2
;!
;!Data Sizes:
;!    Strings     0
;!    Constant    14
;!    Data        9
;!    BSS         121
;!    Persistent  0
;!    Stack       0
;!
;!Auto Spaces:
;!    Space          Size  Autos    Used
;!    COMMON           14     14      14
;!    BANK0            80     10      68
;!    BANK1            80      0      72

;!
;!Pointer List with Targets:
;!
;!    ws2812_update_RGB@leds	PTR struct . size(1) Largest target is 72
;!		 -> leds(BANK1[72]), 
;!
;!    S38$update	PTR FTN()void  size(1) Largest target is 1
;!		 -> police_update(), stack_update(), marquee_update(), expand_update(), 
;!		 -> chase_update(), twinkle_update(), breath_update(), 
;!
;!    effects.update	PTR FTN()void  size(1) Largest target is 1
;!		 -> police_update(), stack_update(), marquee_update(), expand_update(), 
;!		 -> chase_update(), twinkle_update(), breath_update(), 
;!
;!    S38$init	PTR FTN()void  size(1) Largest target is 1
;!		 -> police_init(), stack_init(), marquee_init(), expand_init(), 
;!		 -> chase_init(), twinkle_init(), breath_init(), 
;!
;!    effects.init	PTR FTN()void  size(1) Largest target is 1
;!		 -> police_init(), stack_init(), marquee_init(), expand_init(), 
;!		 -> chase_init(), twinkle_init(), breath_init(), 
;!


;!
;!Critical Paths under _main in COMMON
;!
;!    _key_scan->_effect_execute
;!    _ws2812_update_RGB->_effect_execute
;!    _ws2812_send_color->_ws2812_send_byte
;!    _ws2812_reset->_delay_ms
;!    _effect_execute->_twinkle_init
;!    _effects_update->_expand_update
;!    _twinkle_update->___awdiv
;!    ___awdiv->___wmul
;!    _stack_update->_stack_init
;!    _marquee_update->___awmod
;!    _expand_update->_random_value
;!    _random_value->___wmul
;!    _chase_update->___awmod
;!    _breath_update->___awmod
;!    _effect_init->_twinkle_init
;!    _twinkle_init->___lwmod
;!    ___lwmod->___wmul
;!
;!Critical Paths under _main in BANK0
;!
;!    _main->_key_scan
;!    _key_scan->_ws2812_update_RGB
;!    _effects_update->_twinkle_update
;!
;!Critical Paths under _main in BANK1
;!
;!    None.

;;
;;Main: autosize = 0, tempsize = 0, incstack = 0, save=0
;;

;!
;!Call Graph Tables:
;!
;! ---------------------------------------------------------------------------------
;! (Depth) Function   	        Calls       Base Space   Used Autos Params    Refs
;! ---------------------------------------------------------------------------------
;! (0) _main                                                 2     2      0   64934
;!                                              8 BANK0      2     2      0
;!                           _delay_ms
;!                        _effect_init
;!                     _effects_update
;!                           _key_scan
;!                  _system_clock_init
;!                   _ws2812_gpio_init
;!                  _ws2812_update_RGB
;! ---------------------------------------------------------------------------------
;! (1) _ws2812_gpio_init                                     0     0      0       0
;! ---------------------------------------------------------------------------------
;! (1) _system_clock_init                                    1     1      0      46
;!                                              0 COMMON     1     1      0
;! ---------------------------------------------------------------------------------
;! (1) _key_scan                                             2     2      0   20493
;!                                              6 BANK0      2     2      0
;!                            ___awmod
;!                           _delay_ms
;!                     _effect_execute
;!                  _ws2812_update_RGB
;! ---------------------------------------------------------------------------------
;! (1) _ws2812_update_RGB                                    6     5      1   10476
;!                                              0 BANK0      6     5      1
;!                            ___awmod
;!                     _effect_execute
;!                       _ws2812_reset
;!                  _ws2812_send_color
;! ---------------------------------------------------------------------------------
;! (2) _ws2812_send_color                                    3     0      3     297
;!                                              1 COMMON     3     0      3
;!                   _ws2812_send_byte
;! ---------------------------------------------------------------------------------
;! (3) _ws2812_send_byte                                     1     1      0     176
;!                                              0 COMMON     1     1      0
;! ---------------------------------------------------------------------------------
;! (2) _ws2812_reset                                         0     0      0     251
;!                           _delay_ms
;! ---------------------------------------------------------------------------------
;! (3) _delay_ms                                             6     4      2     251
;!                                              0 COMMON     6     4      2
;! ---------------------------------------------------------------------------------
;! (2) _effect_execute                                       1     1      0    7437
;!                                             13 COMMON     1     1      0
;!                        _breath_init *
;!                         _chase_init *
;!                        _expand_init *
;!                       _marquee_init *
;!                        _police_init *
;!                         _stack_init *
;!                       _twinkle_init *
;! ---------------------------------------------------------------------------------
;! (1) _effects_update                                       0     0      0   26250
;!                      _breath_update *
;!                       _chase_update *
;!                      _expand_update *
;!                     _marquee_update *
;!                      _police_update *
;!                       _stack_update *
;!                     _twinkle_update *
;! ---------------------------------------------------------------------------------
;! (2) _twinkle_update                                       6     6      0    9455
;!                                              0 BANK0      6     6      0
;!                            ___awdiv
;!                            ___awmod
;!                             ___bmul
;!                             ___wmul
;! ---------------------------------------------------------------------------------
;! (3) ___awdiv                                              8     4      4     512
;!                                              6 COMMON     8     4      4
;!                             ___wmul (ARG)
;! ---------------------------------------------------------------------------------
;! (2) _stack_update                                         2     2      0     336
;!                                              1 COMMON     2     2      0
;!                         _stack_init
;! ---------------------------------------------------------------------------------
;! (2) _police_update                                        4     4      0     183
;!                                              0 COMMON     4     4      0
;! ---------------------------------------------------------------------------------
;! (2) _marquee_update                                       7     7      0    2551
;!                                              6 COMMON     7     7      0
;!                            ___awmod
;! ---------------------------------------------------------------------------------
;! (2) _expand_update                                        5     5      0    8352
;!                                              9 COMMON     5     5      0
;!                            ___awmod
;!                       _random_value
;! ---------------------------------------------------------------------------------
;! (3) _random_value                                         3     3      0    5778
;!                                              6 COMMON     3     3      0
;!                             ___wmul
;! ---------------------------------------------------------------------------------
;! (2) _chase_update                                         7     7      0    2551
;!                                              6 COMMON     7     7      0
;!                            ___awmod
;! ---------------------------------------------------------------------------------
;! (2) _breath_update                                        6     6      0    2822
;!                                              6 COMMON     6     6      0
;!                            ___awmod
;!                             ___bmul
;! ---------------------------------------------------------------------------------
;! (2) ___awmod                                              6     2      4    2194
;!                                              0 COMMON     6     2      4
;! ---------------------------------------------------------------------------------
;! (1) _effect_init                                          0     0      0    7393
;!                        _breath_init *
;!                         _chase_init *
;!                        _expand_init *
;!                       _marquee_init *
;!                        _police_init *
;!                         _stack_init *
;!                       _twinkle_init *
;! ---------------------------------------------------------------------------------
;! (3) _twinkle_init                                         2     2      0    6721
;!                                             11 COMMON     2     2      0
;!                             ___bmul
;!                            ___lwmod
;!                             ___wmul
;! ---------------------------------------------------------------------------------
;! (4) ___wmul                                               6     2      4    5756
;!                                              0 COMMON     6     2      4
;! ---------------------------------------------------------------------------------
;! (4) ___lwmod                                              5     1      4     371
;!                                              6 COMMON     5     1      4
;!                             ___wmul (ARG)
;! ---------------------------------------------------------------------------------
;! (4) ___bmul                                               3     2      1     304
;!                                              0 COMMON     3     2      1
;! ---------------------------------------------------------------------------------
;! (3) _stack_init                                           1     1      0     112
;!                                              0 COMMON     1     1      0
;! ---------------------------------------------------------------------------------
;! (3) _police_init                                          1     1      0     112
;!                                              0 COMMON     1     1      0
;! ---------------------------------------------------------------------------------
;! (3) _marquee_init                                         2     2      0     224
;!                                              0 COMMON     2     2      0
;! ---------------------------------------------------------------------------------
;! (3) _expand_init                                          1     1      0     112
;!                                              0 COMMON     1     1      0
;! ---------------------------------------------------------------------------------
;! (3) _chase_init                                           1     1      0     112
;!                                              0 COMMON     1     1      0
;! ---------------------------------------------------------------------------------
;! (3) _breath_init                                          0     0      0       0
;! ---------------------------------------------------------------------------------
;! Estimated maximum stack depth 4
;! ---------------------------------------------------------------------------------
;!
;! Call Graph Graphs:
;!
;! _main (ROOT)
;!   _delay_ms
;!   _effect_init
;!     _breath_init *
;!     _chase_init *
;!     _expand_init *
;!     _marquee_init *
;!     _police_init *
;!     _stack_init *
;!     _twinkle_init *
;!       ___bmul
;!       ___lwmod
;!         ___wmul (ARG)
;!       ___wmul
;!   _effects_update
;!     _breath_update *
;!       ___awmod
;!       ___bmul
;!     _chase_update *
;!       ___awmod
;!     _expand_update *
;!       ___awmod
;!       _random_value
;!         ___wmul
;!     _marquee_update *
;!       ___awmod
;!     _police_update *
;!     _stack_update *
;!       _stack_init
;!     _twinkle_update *
;!       ___awdiv
;!         ___wmul (ARG)
;!       ___awmod
;!       ___bmul
;!       ___wmul
;!   _key_scan
;!     ___awmod
;!     _delay_ms
;!     _effect_execute
;!       _breath_init *
;!       _chase_init *
;!       _expand_init *
;!       _marquee_init *
;!       _police_init *
;!       _stack_init *
;!       _twinkle_init *
;!         ___bmul
;!         ___lwmod
;!           ___wmul (ARG)
;!         ___wmul
;!     _ws2812_update_RGB
;!       ___awmod
;!       _effect_execute
;!         _breath_init *
;!         _chase_init *
;!         _expand_init *
;!         _marquee_init *
;!         _police_init *
;!         _stack_init *
;!         _twinkle_init *
;!           ___bmul
;!           ___lwmod
;!             ___wmul (ARG)
;!           ___wmul
;!       _ws2812_reset
;!         _delay_ms
;!       _ws2812_send_color
;!         _ws2812_send_byte
;!   _system_clock_init
;!   _ws2812_gpio_init
;!   _ws2812_update_RGB
;!     ___awmod
;!     _effect_execute
;!       _breath_init *
;!       _chase_init *
;!       _expand_init *
;!       _marquee_init *
;!       _police_init *
;!       _stack_init *
;!       _twinkle_init *
;!         ___bmul
;!         ___lwmod
;!           ___wmul (ARG)
;!         ___wmul
;!     _ws2812_reset
;!       _delay_ms
;!     _ws2812_send_color
;!       _ws2812_send_byte
;!

;! Address spaces:

;!Name               Size   Autos  Total    Cost      Usage
;!BANK1               50      0      48       6       90.0%
;!BITBANK1            50      0       0       5        0.0%
;!SFR1                 0      0       0       2        0.0%
;!BITSFR1              0      0       0       2        0.0%
;!BANK0               50      A      44       4       85.0%
;!BITBANK0            50      0       0       3        0.0%
;!SFR0                 0      0       0       1        0.0%
;!BITSFR0              0      0       0       1        0.0%
;!COMMON               E      E       E       1      100.0%
;!BITCOMMON            E      0       0       0        0.0%
;!CODE                 0      0       0       0        0.0%
;!DATA                 0      0      9A       8        0.0%
;!ABS                  0      0      9A       7        0.0%
;!NULL                 0      0       0       0        0.0%
;!STACK                0      0       0       2        0.0%

	global	_main

;; *************** function _main *****************
;; Defined at:
;;		line 217 in file "H:\8bit-RGB\main.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;  update_count    2    8[BANK0 ] unsigned int 
;; Return value:  Size  Location     Type
;;                  1    wreg      void 
;; Registers used:
;;		wreg, fsr0l, fsr0h, status,2, status,0, pclath, cstack
;; Tracked objects:
;;		On entry : B00/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1
;;      Params:         0       0       0
;;      Locals:         0       2       0
;;      Temps:          0       0       0
;;      Totals:         0       2       0
;;Total ram usage:        2 bytes
;; Hardware stack levels required when called:    5
;; This function calls:
;;		_delay_ms
;;		_effect_init
;;		_effects_update
;;		_key_scan
;;		_system_clock_init
;;		_ws2812_gpio_init
;;		_ws2812_update_RGB
;; This function is called by:
;;		Startup code after reset
;; This function uses a non-reentrant model
;;
psect	maintext,global,class=CODE,delta=2,split=1,group=0
	file	"H:\8bit-RGB\main.c"
	line	217
global __pmaintext
__pmaintext:	;psect for function _main
psect	maintext
	file	"H:\8bit-RGB\main.c"
	line	217
	global	__size_of_main
	__size_of_main	equ	__end_of_main-_main
	
_main:	
;incstack = 0
	opt	stack 3
; Regs used in _main: [wreg-fsr0h+status,2+status,0+pclath+cstack]
	line	219
	
l3797:	
;main.c: 219: system_clock_init();
	fcall	_system_clock_init
	line	222
	
l3799:	
;main.c: 222: WPUA |= (1 << 0);
	bsf	status, 5	;RP0=1, select bank1
	bsf	(136)^080h+(0/8),(0)&7	;volatile
	line	225
	
l3801:	
;main.c: 225: ws2812_gpio_init();
	fcall	_ws2812_gpio_init
	line	228
	
l3803:	
;main.c: 228: effect_init();
	fcall	_effect_init
	line	231
	
l3805:	
;main.c: 231: unsigned int update_counter = 0;
	clrf	(main@update_counter)
	clrf	(main@update_counter+1)
	line	234
	
l3807:	
;main.c: 234: key_scan();
	fcall	_key_scan
	line	237
	
l3809:	
;main.c: 237: update_counter++;
	bcf	status, 5	;RP0=0, select bank0
	incf	(main@update_counter),f
	skipnz
	incf	(main@update_counter+1),f
	line	238
	
l3811:	
;main.c: 238: if (update_counter >= 10) {
	movlw	0
	subwf	(main@update_counter+1),w
	movlw	0Ah
	skipnz
	subwf	(main@update_counter),w
	skipc
	goto	u2111
	goto	u2110
u2111:
	goto	l3819
u2110:
	line	239
	
l3813:	
;main.c: 239: update_counter = 0;
	clrf	(main@update_counter)
	clrf	(main@update_counter+1)
	line	242
	
l3815:	
;main.c: 242: if (power_state) {
	movf	((_power_state)),w
	btfsc	status,2
	goto	u2121
	goto	u2120
u2121:
	goto	l1506
u2120:
	line	244
	
l3817:	
;main.c: 244: effects_update();
	fcall	_effects_update
	line	245
	
l1506:	
	line	248
;main.c: 245: }
;main.c: 248: ws2812_update_RGB(leds, 24);
	movlw	low(018h)
	movwf	(ws2812_update_RGB@num)
	movlw	(low(_leds|((0x0)<<8)))&0ffh
	fcall	_ws2812_update_RGB
	line	252
	
l3819:	
;main.c: 249: }
;main.c: 252: delay_ms(1);
	clrf	(delay_ms@ms)
	incf	(delay_ms@ms),f
	clrf	(delay_ms@ms+1)
	fcall	_delay_ms
	goto	l3807
	global	start
	ljmp	start
	opt stack 0
	line	254
GLOBAL	__end_of_main
	__end_of_main:
	signat	_main,89
	global	_ws2812_gpio_init

;; *************** function _ws2812_gpio_init *****************
;; Defined at:
;;		line 139 in file "H:\8bit-RGB\main.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;                  1    wreg      void 
;; Registers used:
;;		None
;; Tracked objects:
;;		On entry : 100/100
;;		On exit  : 100/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1
;;      Params:         0       0       0
;;      Locals:         0       0       0
;;      Temps:          0       0       0
;;      Totals:         0       0       0
;;Total ram usage:        0 bytes
;; Hardware stack levels used:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_main
;; This function uses a non-reentrant model
;;
psect	text1,local,class=CODE,delta=2,merge=1,group=0
	line	139
global __ptext1
__ptext1:	;psect for function _ws2812_gpio_init
psect	text1
	file	"H:\8bit-RGB\main.c"
	line	139
	global	__size_of_ws2812_gpio_init
	__size_of_ws2812_gpio_init	equ	__end_of_ws2812_gpio_init-_ws2812_gpio_init
	
_ws2812_gpio_init:	
;incstack = 0
	opt	stack 7
; Regs used in _ws2812_gpio_init: []
	line	141
	
l3745:	
;main.c: 141: TRISA |= (1 << 0);
	bsf	(133)^080h+(0/8),(0)&7	;volatile
	line	144
;main.c: 144: ANSEL0 &= ~(1 << 0);
	bcf	(147)^080h+(0/8),(0)&7	;volatile
	line	147
;main.c: 147: ANSEL1 &= ~(1 << 1);
	bcf	(148)^080h+(1/8),(1)&7	;volatile
	line	150
;main.c: 150: TRISB &= ~(1 << 1);
	bcf	status, 5	;RP0=0, select bank0
	bcf	(5)+(1/8),(1)&7	;volatile
	line	153
;main.c: 153: RB1 = 0;
	bcf	(49/8),(49)&7	;volatile
	line	154
	
l1474:	
	return
	opt stack 0
GLOBAL	__end_of_ws2812_gpio_init
	__end_of_ws2812_gpio_init:
	signat	_ws2812_gpio_init,89
	global	_system_clock_init

;; *************** function _system_clock_init *****************
;; Defined at:
;;		line 9 in file "H:\8bit-RGB\main.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;  i               1    0[COMMON] unsigned char 
;; Return value:  Size  Location     Type
;;                  1    wreg      void 
;; Registers used:
;;		wreg, status,2, status,0
;; Tracked objects:
;;		On entry : B00/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1
;;      Params:         0       0       0
;;      Locals:         1       0       0
;;      Temps:          0       0       0
;;      Totals:         1       0       0
;;Total ram usage:        1 bytes
;; Hardware stack levels used:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_main
;; This function uses a non-reentrant model
;;
psect	text2,local,class=CODE,delta=2,merge=1,group=0
	line	9
global __ptext2
__ptext2:	;psect for function _system_clock_init
psect	text2
	file	"H:\8bit-RGB\main.c"
	line	9
	global	__size_of_system_clock_init
	__size_of_system_clock_init	equ	__end_of_system_clock_init-_system_clock_init
	
_system_clock_init:	
;incstack = 0
	opt	stack 7
; Regs used in _system_clock_init: [wreg+status,2+status,0]
	line	12
	
l3733:	
;main.c: 12: OSCCON = 0x70;
	movlw	low(070h)
	movwf	(20)	;volatile
	line	16
	
l3735:	
;main.c: 15: unsigned char i;
;main.c: 16: for (i = 0; i < 20; i++) {
	clrf	(system_clock_init@i)
	
l1428:	
	line	17
# 17 "H:\8bit-RGB\main.c"
nop ;# 
psect	text2
	line	16
	
l3741:	
	incf	(system_clock_init@i),f
	
l3743:	
	movlw	low(014h)
	subwf	(system_clock_init@i),w
	skipc
	goto	u1971
	goto	u1970
u1971:
	goto	l1428
u1970:
	line	19
	
l1430:	
	return
	opt stack 0
GLOBAL	__end_of_system_clock_init
	__end_of_system_clock_init:
	signat	_system_clock_init,89
	global	_key_scan

;; *************** function _key_scan *****************
;; Defined at:
;;		line 161 in file "H:\8bit-RGB\main.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;  next_mode       1    6[BANK0 ] enum E587
;;  i               1    7[BANK0 ] unsigned char 
;; Return value:  Size  Location     Type
;;                  1    wreg      void 
;; Registers used:
;;		wreg, fsr0l, fsr0h, status,2, status,0, pclath, cstack
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1
;;      Params:         0       0       0
;;      Locals:         0       2       0
;;      Temps:          0       0       0
;;      Totals:         0       2       0
;;Total ram usage:        2 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    4
;; This function calls:
;;		___awmod
;;		_delay_ms
;;		_effect_execute
;;		_ws2812_update_RGB
;; This function is called by:
;;		_main
;; This function uses a non-reentrant model
;;
psect	text3,local,class=CODE,delta=2,merge=1,group=0
	line	161
global __ptext3
__ptext3:	;psect for function _key_scan
psect	text3
	file	"H:\8bit-RGB\main.c"
	line	161
	global	__size_of_key_scan
	__size_of_key_scan	equ	__end_of_key_scan-_key_scan
	
_key_scan:	
;incstack = 0
	opt	stack 3
; Regs used in _key_scan: [wreg-fsr0h+status,2+status,0+pclath+cstack]
	line	162
	
l3747:	
;main.c: 162: if (RA0 == 0) {
	bsf	status, 5	;RP0=1, select bank1
	btfsc	(1072/8)^080h,(1072)&7	;volatile
	goto	u1981
	goto	u1980
u1981:
	goto	l3783
u1980:
	line	164
	
l3749:	
;main.c: 164: if (!key_pressed) {
	bcf	status, 5	;RP0=0, select bank0
	movf	((_key_pressed)),w
	btfss	status,2
	goto	u1991
	goto	u1990
u1991:
	goto	l3759
u1990:
	line	165
	
l3751:	
;main.c: 165: delay_ms(20);
	movlw	014h
	movwf	(delay_ms@ms)
	clrf	(delay_ms@ms+1)
	fcall	_delay_ms
	line	166
	
l3753:	
;main.c: 166: if (RA0 == 0) {
	bsf	status, 5	;RP0=1, select bank1
	btfsc	(1072/8)^080h,(1072)&7	;volatile
	goto	u2001
	goto	u2000
u2001:
	goto	l1499
u2000:
	line	167
	
l3755:	
;main.c: 167: key_pressed = 1;
	bcf	status, 5	;RP0=0, select bank0
	clrf	(_key_pressed)
	incf	(_key_pressed),f
	line	168
	
l3757:	
;main.c: 168: key_press_counter = 0;
	clrf	(_key_press_counter)
	goto	l1499
	line	172
	
l3759:	
;main.c: 172: if (key_press_counter < 255) {
		incf	((_key_press_counter)),w
	btfsc	status,2
	goto	u2011
	goto	u2010
u2011:
	goto	l3763
u2010:
	line	173
	
l3761:	
;main.c: 173: key_press_counter++;
	incf	(_key_press_counter),f
	line	176
	
l3763:	
;main.c: 174: }
;main.c: 176: if (key_press_counter == 150) {
		movlw	150
	xorwf	((_key_press_counter)),w
	btfss	status,2
	goto	u2021
	goto	u2020
u2021:
	goto	l1499
u2020:
	line	178
	
l3765:	
;main.c: 178: power_state = !power_state;
	movf	((_power_state)),w
	btfsc	status,2
	goto	u2031
	goto	u2030
u2031:
	movlw	1
	goto	u2040
u2030:
	movlw	0
u2040:
	movwf	(_power_state)
	line	179
;main.c: 179: if (!power_state) {
	movf	((_power_state)),w
	btfss	status,2
	goto	u2051
	goto	u2050
u2051:
	goto	l1492
u2050:
	line	182
	
l3767:	
;main.c: 181: unsigned char i;
;main.c: 182: for (i = 0; i < 24; i++) {
	clrf	(key_scan@i)
	line	183
	
l3773:	
;main.c: 183: leds[i].r = 0;
	movf	(key_scan@i),w
	addwf	(key_scan@i),w
	addwf	(key_scan@i),w
	addlw	low(_leds|((0x0)<<8))&0ffh
	movwf	fsr0
	bcf	status, 7	;select IRP bank1
	clrf	indf
	line	184
;main.c: 184: leds[i].g = 0;
	movf	(key_scan@i),w
	addwf	(key_scan@i),w
	addwf	(key_scan@i),w
	addlw	low(_leds|((0x0)<<8)+01h)&0ffh
	movwf	fsr0
	clrf	indf
	line	185
;main.c: 185: leds[i].b = 0;
	movf	(key_scan@i),w
	addwf	(key_scan@i),w
	addwf	(key_scan@i),w
	addlw	low(_leds|((0x0)<<8)+02h)&0ffh
	movwf	fsr0
	clrf	indf
	line	182
	
l3775:	
	incf	(key_scan@i),f
	
l3777:	
	movlw	low(018h)
	subwf	(key_scan@i),w
	skipc
	goto	u2061
	goto	u2060
u2061:
	goto	l3773
u2060:
	line	187
	
l3779:	
;main.c: 186: }
;main.c: 187: ws2812_update_RGB(leds, 24);
	movlw	low(018h)
	movwf	(ws2812_update_RGB@num)
	movlw	(low(_leds|((0x0)<<8)))&0ffh
	fcall	_ws2812_update_RGB
	line	190
	
l1492:	
	bsf	status, 5	;RP0=1, select bank1
	btfss	(1072/8)^080h,(1072)&7	;volatile
	goto	u2071
	goto	u2070
u2071:
	goto	l1492
u2070:
	line	191
	
l3781:	
;main.c: 191: key_pressed = 0;
	bcf	status, 5	;RP0=0, select bank0
	clrf	(_key_pressed)
	line	192
;main.c: 192: key_press_counter = 0;
	clrf	(_key_press_counter)
	goto	l1499
	line	197
	
l3783:	
;main.c: 197: if (key_pressed) {
	bcf	status, 5	;RP0=0, select bank0
	movf	((_key_pressed)),w
	btfsc	status,2
	goto	u2081
	goto	u2080
u2081:
	goto	l1499
u2080:
	line	198
	
l3785:	
;main.c: 198: if (key_press_counter < 150) {
	movlw	low(096h)
	subwf	(_key_press_counter),w
	skipnc
	goto	u2091
	goto	u2090
u2091:
	goto	l3793
u2090:
	line	200
	
l3787:	
;main.c: 200: if (power_state) {
	movf	((_power_state)),w
	btfsc	status,2
	goto	u2101
	goto	u2100
u2101:
	goto	l3793
u2100:
	line	201
	
l3789:	
;main.c: 201: EffectMode_t next_mode = (current_effect + 1) % EFFECT_COUNT;
	movf	(_current_effect),w	;volatile
	movwf	(___awmod@dividend)
	clrf	(___awmod@dividend+1)
	incf	(___awmod@dividend),f
	skipnz
	incf	(___awmod@dividend+1),f
	movlw	07h
	movwf	(___awmod@divisor)
	clrf	(___awmod@divisor+1)
	fcall	___awmod
	movf	(0+(?___awmod)),w
	movwf	(key_scan@next_mode)
	line	202
	
l3791:	
;main.c: 202: effect_execute(next_mode);
	movf	(key_scan@next_mode),w
	fcall	_effect_execute
	line	205
	
l3793:	
;main.c: 203: }
;main.c: 204: }
;main.c: 205: key_pressed = 0;
	clrf	(_key_pressed)
	goto	l3757
	line	209
	
l1499:	
	return
	opt stack 0
GLOBAL	__end_of_key_scan
	__end_of_key_scan:
	signat	_key_scan,89
	global	_ws2812_update_RGB

;; *************** function _ws2812_update_RGB *****************
;; Defined at:
;;		line 115 in file "H:\8bit-RGB\main.c"
;; Parameters:    Size  Location     Type
;;  leds            1    wreg     PTR struct .
;;		 -> leds(72), 
;;  num             1    0[BANK0 ] unsigned char 
;; Auto vars:     Size  Location     Type
;;  leds            1    4[BANK0 ] PTR struct .
;;		 -> leds(72), 
;;  next_mode       1    2[BANK0 ] enum E587
;;  i               1    5[BANK0 ] unsigned char 
;;  key_was_pres    1    3[BANK0 ] unsigned char 
;; Return value:  Size  Location     Type
;;                  1    wreg      void 
;; Registers used:
;;		wreg, fsr0l, fsr0h, status,2, status,0, pclath, cstack
;; Tracked objects:
;;		On entry : 100/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1
;;      Params:         0       1       0
;;      Locals:         0       4       0
;;      Temps:          0       1       0
;;      Totals:         0       6       0
;;Total ram usage:        6 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    3
;; This function calls:
;;		___awmod
;;		_effect_execute
;;		_ws2812_reset
;;		_ws2812_send_color
;; This function is called by:
;;		_key_scan
;;		_main
;; This function uses a non-reentrant model
;;
psect	text4,local,class=CODE,delta=2,merge=1,group=0
	line	115
global __ptext4
__ptext4:	;psect for function _ws2812_update_RGB
psect	text4
	file	"H:\8bit-RGB\main.c"
	line	115
	global	__size_of_ws2812_update_RGB
	__size_of_ws2812_update_RGB	equ	__end_of_ws2812_update_RGB-_ws2812_update_RGB
	
_ws2812_update_RGB:	
;incstack = 0
	opt	stack 4
; Regs used in _ws2812_update_RGB: [wreg-fsr0h+status,2+status,0+pclath+cstack]
;ws2812_update_RGB@leds stored from wreg
	movwf	(ws2812_update_RGB@leds)
	line	117
	
l3699:	
;main.c: 116: unsigned char i;
;main.c: 117: unsigned char key_was_pressed = 0;
	clrf	(ws2812_update_RGB@key_was_pressed)
	line	120
	
l3701:	
;main.c: 120: if (RA0 == 0) {
	bsf	status, 5	;RP0=1, select bank1
	btfsc	(1072/8)^080h,(1072)&7	;volatile
	goto	u1911
	goto	u1910
u1911:
	goto	l1466
u1910:
	line	121
	
l3703:	
;main.c: 121: key_was_pressed = 1;
	bcf	status, 5	;RP0=0, select bank0
	clrf	(ws2812_update_RGB@key_was_pressed)
	incf	(ws2812_update_RGB@key_was_pressed),f
	line	122
	
l1466:	
	line	124
;main.c: 122: }
;main.c: 124: GIE = 0;
	bcf	(95/8),(95)&7	;volatile
	line	125
	
l3705:	
;main.c: 125: for (i = 0; i < num; i++) {
	bcf	status, 5	;RP0=0, select bank0
	clrf	(ws2812_update_RGB@i)
	goto	l3711
	line	126
	
l3707:	
;main.c: 126: ws2812_send_color(leds[i]);
	movf	(ws2812_update_RGB@i),w
	addwf	(ws2812_update_RGB@i),w
	addwf	(ws2812_update_RGB@i),w
	addwf	(ws2812_update_RGB@leds),w
	movwf	(??_ws2812_update_RGB+0)+0
	movf	0+(??_ws2812_update_RGB+0)+0,w
	movwf	fsr0
	bcf	status, 7	;select IRP bank0
	movf	indf,w
	movwf	(ws2812_send_color@color)
	incf	fsr0,f
	movf	indf,w
	movwf	(ws2812_send_color@color+1)
	incf	fsr0,f
	movf	indf,w
	movwf	(ws2812_send_color@color+2)
	fcall	_ws2812_send_color
	line	125
	
l3709:	
	bcf	status, 5	;RP0=0, select bank0
	incf	(ws2812_update_RGB@i),f
	
l3711:	
	movf	(ws2812_update_RGB@num),w
	subwf	(ws2812_update_RGB@i),w
	skipc
	goto	u1921
	goto	u1920
u1921:
	goto	l3707
u1920:
	line	128
	
l3713:	
;main.c: 127: }
;main.c: 128: ws2812_reset();
	fcall	_ws2812_reset
	line	129
	
l3715:	
;main.c: 129: GIE = 1;
	bsf	(95/8),(95)&7	;volatile
	line	132
	
l3717:	
;main.c: 132: if (key_was_pressed && RA0 == 1) {
	bcf	status, 5	;RP0=0, select bank0
	movf	((ws2812_update_RGB@key_was_pressed)),w
	btfsc	status,2
	goto	u1931
	goto	u1930
u1931:
	goto	l1471
u1930:
	
l3719:	
	bsf	status, 5	;RP0=1, select bank1
	btfss	(1072/8)^080h,(1072)&7	;volatile
	goto	u1941
	goto	u1940
u1941:
	goto	l1471
u1940:
	line	133
	
l3721:	
;main.c: 133: EffectMode_t next_mode = (current_effect + 1) % EFFECT_COUNT;
	bcf	status, 5	;RP0=0, select bank0
	movf	(_current_effect),w	;volatile
	movwf	(___awmod@dividend)
	clrf	(___awmod@dividend+1)
	incf	(___awmod@dividend),f
	skipnz
	incf	(___awmod@dividend+1),f
	movlw	07h
	movwf	(___awmod@divisor)
	clrf	(___awmod@divisor+1)
	fcall	___awmod
	movf	(0+(?___awmod)),w
	movwf	(ws2812_update_RGB@next_mode)
	line	134
	
l3723:	
;main.c: 134: effect_execute(next_mode);
	movf	(ws2812_update_RGB@next_mode),w
	fcall	_effect_execute
	line	136
	
l1471:	
	return
	opt stack 0
GLOBAL	__end_of_ws2812_update_RGB
	__end_of_ws2812_update_RGB:
	signat	_ws2812_update_RGB,8313
	global	_ws2812_send_color

;; *************** function _ws2812_send_color *****************
;; Defined at:
;;		line 104 in file "H:\8bit-RGB\main.c"
;; Parameters:    Size  Location     Type
;;  color           3    1[COMMON] struct .
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;                  1    wreg      void 
;; Registers used:
;;		wreg, status,2, status,0, pclath, cstack
;; Tracked objects:
;;		On entry : 900/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1
;;      Params:         3       0       0
;;      Locals:         0       0       0
;;      Temps:          0       0       0
;;      Totals:         3       0       0
;;Total ram usage:        3 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    1
;; This function calls:
;;		_ws2812_send_byte
;; This function is called by:
;;		_ws2812_update_RGB
;; This function uses a non-reentrant model
;;
psect	text5,local,class=CODE,delta=2,merge=1,group=0
	line	104
global __ptext5
__ptext5:	;psect for function _ws2812_send_color
psect	text5
	file	"H:\8bit-RGB\main.c"
	line	104
	global	__size_of_ws2812_send_color
	__size_of_ws2812_send_color	equ	__end_of_ws2812_send_color-_ws2812_send_color
	
_ws2812_send_color:	
;incstack = 0
	opt	stack 5
; Regs used in _ws2812_send_color: [wreg+status,2+status,0+pclath+cstack]
	line	105
	
l3129:	
;main.c: 105: ws2812_send_byte(color.r);
	movf	(ws2812_send_color@color),w
	fcall	_ws2812_send_byte
	line	106
;main.c: 106: ws2812_send_byte(color.g);
	movf	0+(ws2812_send_color@color)+01h,w
	fcall	_ws2812_send_byte
	line	107
;main.c: 107: ws2812_send_byte(color.b);
	movf	0+(ws2812_send_color@color)+02h,w
	fcall	_ws2812_send_byte
	line	108
	
l1460:	
	return
	opt stack 0
GLOBAL	__end_of_ws2812_send_color
	__end_of_ws2812_send_color:
	signat	_ws2812_send_color,4217
	global	_ws2812_send_byte

;; *************** function _ws2812_send_byte *****************
;; Defined at:
;;		line 33 in file "H:\8bit-RGB\main.c"
;; Parameters:    Size  Location     Type
;;  byte            1    wreg     unsigned char 
;; Auto vars:     Size  Location     Type
;;  byte            1    0[COMMON] unsigned char 
;; Return value:  Size  Location     Type
;;                  1    wreg      void 
;; Registers used:
;;		wreg
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1
;;      Params:         0       0       0
;;      Locals:         1       0       0
;;      Temps:          0       0       0
;;      Totals:         1       0       0
;;Total ram usage:        1 bytes
;; Hardware stack levels used:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_ws2812_send_color
;; This function uses a non-reentrant model
;;
psect	text6,local,class=CODE,delta=2,merge=1,group=0
	line	33
global __ptext6
__ptext6:	;psect for function _ws2812_send_byte
psect	text6
	file	"H:\8bit-RGB\main.c"
	line	33
	global	__size_of_ws2812_send_byte
	__size_of_ws2812_send_byte	equ	__end_of_ws2812_send_byte-_ws2812_send_byte
	
_ws2812_send_byte:	
;incstack = 0
	opt	stack 5
; Regs used in _ws2812_send_byte: [wreg]
;ws2812_send_byte@byte stored from wreg
	movwf	(ws2812_send_byte@byte)
	line	34
	
l3101:	
;main.c: 34: GIE = 0;
	bcf	(95/8),(95)&7	;volatile
	line	37
;main.c: 37: if (byte & 0x80) {
	btfss	(ws2812_send_byte@byte),(7)&7
	goto	u1251
	goto	u1250
u1251:
	goto	l1441
u1250:
	line	38
	
l3103:	
;main.c: 38: RB1 = 1; asm("nop"); asm("nop");
	bcf	status, 5	;RP0=0, select bank0
	bsf	(49/8),(49)&7	;volatile
# 38 "H:\8bit-RGB\main.c"
nop ;# 
# 38 "H:\8bit-RGB\main.c"
nop ;# 
psect	text6
	line	39
;main.c: 39: RB1 = 0; asm("nop"); asm("nop");
	bcf	status, 5	;RP0=0, select bank0
	bcf	(49/8),(49)&7	;volatile
# 39 "H:\8bit-RGB\main.c"
nop ;# 
# 39 "H:\8bit-RGB\main.c"
nop ;# 
psect	text6
	line	40
;main.c: 40: } else {
	goto	l1442
	
l1441:	
	line	41
;main.c: 41: RB1 = 1; asm("nop");
	bcf	status, 5	;RP0=0, select bank0
	bsf	(49/8),(49)&7	;volatile
# 41 "H:\8bit-RGB\main.c"
nop ;# 
psect	text6
	line	42
;main.c: 42: RB1 = 0; asm("nop"); asm("nop"); asm("nop");
	bcf	status, 5	;RP0=0, select bank0
	bcf	(49/8),(49)&7	;volatile
# 42 "H:\8bit-RGB\main.c"
nop ;# 
# 42 "H:\8bit-RGB\main.c"
nop ;# 
# 42 "H:\8bit-RGB\main.c"
nop ;# 
psect	text6
	line	43
	
l1442:	
	line	45
;main.c: 43: }
;main.c: 45: if (byte & 0x40) {
	btfss	(ws2812_send_byte@byte),(6)&7
	goto	u1261
	goto	u1260
u1261:
	goto	l1443
u1260:
	line	46
	
l3105:	
;main.c: 46: RB1 = 1; asm("nop"); asm("nop");
	bcf	status, 5	;RP0=0, select bank0
	bsf	(49/8),(49)&7	;volatile
# 46 "H:\8bit-RGB\main.c"
nop ;# 
# 46 "H:\8bit-RGB\main.c"
nop ;# 
psect	text6
	line	47
;main.c: 47: RB1 = 0; asm("nop"); asm("nop");
	bcf	status, 5	;RP0=0, select bank0
	bcf	(49/8),(49)&7	;volatile
# 47 "H:\8bit-RGB\main.c"
nop ;# 
# 47 "H:\8bit-RGB\main.c"
nop ;# 
psect	text6
	line	48
;main.c: 48: } else {
	goto	l1444
	
l1443:	
	line	49
;main.c: 49: RB1 = 1; asm("nop");
	bcf	status, 5	;RP0=0, select bank0
	bsf	(49/8),(49)&7	;volatile
# 49 "H:\8bit-RGB\main.c"
nop ;# 
psect	text6
	line	50
;main.c: 50: RB1 = 0; asm("nop"); asm("nop"); asm("nop");
	bcf	status, 5	;RP0=0, select bank0
	bcf	(49/8),(49)&7	;volatile
# 50 "H:\8bit-RGB\main.c"
nop ;# 
# 50 "H:\8bit-RGB\main.c"
nop ;# 
# 50 "H:\8bit-RGB\main.c"
nop ;# 
psect	text6
	line	51
	
l1444:	
	line	53
;main.c: 51: }
;main.c: 53: if (byte & 0x20) {
	btfss	(ws2812_send_byte@byte),(5)&7
	goto	u1271
	goto	u1270
u1271:
	goto	l1445
u1270:
	line	54
	
l3107:	
;main.c: 54: RB1 = 1; asm("nop"); asm("nop");
	bcf	status, 5	;RP0=0, select bank0
	bsf	(49/8),(49)&7	;volatile
# 54 "H:\8bit-RGB\main.c"
nop ;# 
# 54 "H:\8bit-RGB\main.c"
nop ;# 
psect	text6
	line	55
;main.c: 55: RB1 = 0; asm("nop"); asm("nop");
	bcf	status, 5	;RP0=0, select bank0
	bcf	(49/8),(49)&7	;volatile
# 55 "H:\8bit-RGB\main.c"
nop ;# 
# 55 "H:\8bit-RGB\main.c"
nop ;# 
psect	text6
	line	56
;main.c: 56: } else {
	goto	l1446
	
l1445:	
	line	57
;main.c: 57: RB1 = 1; asm("nop");
	bcf	status, 5	;RP0=0, select bank0
	bsf	(49/8),(49)&7	;volatile
# 57 "H:\8bit-RGB\main.c"
nop ;# 
psect	text6
	line	58
;main.c: 58: RB1 = 0; asm("nop"); asm("nop"); asm("nop");
	bcf	status, 5	;RP0=0, select bank0
	bcf	(49/8),(49)&7	;volatile
# 58 "H:\8bit-RGB\main.c"
nop ;# 
# 58 "H:\8bit-RGB\main.c"
nop ;# 
# 58 "H:\8bit-RGB\main.c"
nop ;# 
psect	text6
	line	59
	
l1446:	
	line	61
;main.c: 59: }
;main.c: 61: if (byte & 0x10) {
	btfss	(ws2812_send_byte@byte),(4)&7
	goto	u1281
	goto	u1280
u1281:
	goto	l1447
u1280:
	line	62
	
l3109:	
;main.c: 62: RB1 = 1; asm("nop"); asm("nop");
	bcf	status, 5	;RP0=0, select bank0
	bsf	(49/8),(49)&7	;volatile
# 62 "H:\8bit-RGB\main.c"
nop ;# 
# 62 "H:\8bit-RGB\main.c"
nop ;# 
psect	text6
	line	63
;main.c: 63: RB1 = 0; asm("nop"); asm("nop");
	bcf	status, 5	;RP0=0, select bank0
	bcf	(49/8),(49)&7	;volatile
# 63 "H:\8bit-RGB\main.c"
nop ;# 
# 63 "H:\8bit-RGB\main.c"
nop ;# 
psect	text6
	line	64
;main.c: 64: } else {
	goto	l1448
	
l1447:	
	line	65
;main.c: 65: RB1 = 1; asm("nop");
	bcf	status, 5	;RP0=0, select bank0
	bsf	(49/8),(49)&7	;volatile
# 65 "H:\8bit-RGB\main.c"
nop ;# 
psect	text6
	line	66
;main.c: 66: RB1 = 0; asm("nop"); asm("nop"); asm("nop");
	bcf	status, 5	;RP0=0, select bank0
	bcf	(49/8),(49)&7	;volatile
# 66 "H:\8bit-RGB\main.c"
nop ;# 
# 66 "H:\8bit-RGB\main.c"
nop ;# 
# 66 "H:\8bit-RGB\main.c"
nop ;# 
psect	text6
	line	67
	
l1448:	
	line	69
;main.c: 67: }
;main.c: 69: if (byte & 0x08) {
	btfss	(ws2812_send_byte@byte),(3)&7
	goto	u1291
	goto	u1290
u1291:
	goto	l1449
u1290:
	line	70
	
l3111:	
;main.c: 70: RB1 = 1; asm("nop"); asm("nop");
	bcf	status, 5	;RP0=0, select bank0
	bsf	(49/8),(49)&7	;volatile
# 70 "H:\8bit-RGB\main.c"
nop ;# 
# 70 "H:\8bit-RGB\main.c"
nop ;# 
psect	text6
	line	71
;main.c: 71: RB1 = 0; asm("nop"); asm("nop");
	bcf	status, 5	;RP0=0, select bank0
	bcf	(49/8),(49)&7	;volatile
# 71 "H:\8bit-RGB\main.c"
nop ;# 
# 71 "H:\8bit-RGB\main.c"
nop ;# 
psect	text6
	line	72
;main.c: 72: } else {
	goto	l1450
	
l1449:	
	line	73
;main.c: 73: RB1 = 1; asm("nop");
	bcf	status, 5	;RP0=0, select bank0
	bsf	(49/8),(49)&7	;volatile
# 73 "H:\8bit-RGB\main.c"
nop ;# 
psect	text6
	line	74
;main.c: 74: RB1 = 0; asm("nop"); asm("nop"); asm("nop");
	bcf	status, 5	;RP0=0, select bank0
	bcf	(49/8),(49)&7	;volatile
# 74 "H:\8bit-RGB\main.c"
nop ;# 
# 74 "H:\8bit-RGB\main.c"
nop ;# 
# 74 "H:\8bit-RGB\main.c"
nop ;# 
psect	text6
	line	75
	
l1450:	
	line	77
;main.c: 75: }
;main.c: 77: if (byte & 0x04) {
	btfss	(ws2812_send_byte@byte),(2)&7
	goto	u1301
	goto	u1300
u1301:
	goto	l1451
u1300:
	line	78
	
l3113:	
;main.c: 78: RB1 = 1; asm("nop"); asm("nop");
	bcf	status, 5	;RP0=0, select bank0
	bsf	(49/8),(49)&7	;volatile
# 78 "H:\8bit-RGB\main.c"
nop ;# 
# 78 "H:\8bit-RGB\main.c"
nop ;# 
psect	text6
	line	79
;main.c: 79: RB1 = 0; asm("nop"); asm("nop");
	bcf	status, 5	;RP0=0, select bank0
	bcf	(49/8),(49)&7	;volatile
# 79 "H:\8bit-RGB\main.c"
nop ;# 
# 79 "H:\8bit-RGB\main.c"
nop ;# 
psect	text6
	line	80
;main.c: 80: } else {
	goto	l1452
	
l1451:	
	line	81
;main.c: 81: RB1 = 1; asm("nop");
	bcf	status, 5	;RP0=0, select bank0
	bsf	(49/8),(49)&7	;volatile
# 81 "H:\8bit-RGB\main.c"
nop ;# 
psect	text6
	line	82
;main.c: 82: RB1 = 0; asm("nop"); asm("nop"); asm("nop");
	bcf	status, 5	;RP0=0, select bank0
	bcf	(49/8),(49)&7	;volatile
# 82 "H:\8bit-RGB\main.c"
nop ;# 
# 82 "H:\8bit-RGB\main.c"
nop ;# 
# 82 "H:\8bit-RGB\main.c"
nop ;# 
psect	text6
	line	83
	
l1452:	
	line	85
;main.c: 83: }
;main.c: 85: if (byte & 0x02) {
	btfss	(ws2812_send_byte@byte),(1)&7
	goto	u1311
	goto	u1310
u1311:
	goto	l1453
u1310:
	line	86
	
l3115:	
;main.c: 86: RB1 = 1; asm("nop"); asm("nop");
	bcf	status, 5	;RP0=0, select bank0
	bsf	(49/8),(49)&7	;volatile
# 86 "H:\8bit-RGB\main.c"
nop ;# 
# 86 "H:\8bit-RGB\main.c"
nop ;# 
psect	text6
	line	87
;main.c: 87: RB1 = 0; asm("nop"); asm("nop");
	bcf	status, 5	;RP0=0, select bank0
	bcf	(49/8),(49)&7	;volatile
# 87 "H:\8bit-RGB\main.c"
nop ;# 
# 87 "H:\8bit-RGB\main.c"
nop ;# 
psect	text6
	line	88
;main.c: 88: } else {
	goto	l1454
	
l1453:	
	line	89
;main.c: 89: RB1 = 1; asm("nop");
	bcf	status, 5	;RP0=0, select bank0
	bsf	(49/8),(49)&7	;volatile
# 89 "H:\8bit-RGB\main.c"
nop ;# 
psect	text6
	line	90
;main.c: 90: RB1 = 0; asm("nop"); asm("nop"); asm("nop");
	bcf	status, 5	;RP0=0, select bank0
	bcf	(49/8),(49)&7	;volatile
# 90 "H:\8bit-RGB\main.c"
nop ;# 
# 90 "H:\8bit-RGB\main.c"
nop ;# 
# 90 "H:\8bit-RGB\main.c"
nop ;# 
psect	text6
	line	91
	
l1454:	
	line	93
;main.c: 91: }
;main.c: 93: if (byte & 0x01) {
	btfss	(ws2812_send_byte@byte),(0)&7
	goto	u1321
	goto	u1320
u1321:
	goto	l1455
u1320:
	line	94
	
l3117:	
;main.c: 94: RB1 = 1; asm("nop"); asm("nop");
	bcf	status, 5	;RP0=0, select bank0
	bsf	(49/8),(49)&7	;volatile
# 94 "H:\8bit-RGB\main.c"
nop ;# 
# 94 "H:\8bit-RGB\main.c"
nop ;# 
psect	text6
	line	95
;main.c: 95: RB1 = 0; asm("nop"); asm("nop");
	bcf	status, 5	;RP0=0, select bank0
	bcf	(49/8),(49)&7	;volatile
# 95 "H:\8bit-RGB\main.c"
nop ;# 
# 95 "H:\8bit-RGB\main.c"
nop ;# 
psect	text6
	line	96
;main.c: 96: } else {
	goto	l1456
	
l1455:	
	line	97
;main.c: 97: RB1 = 1; asm("nop");
	bcf	status, 5	;RP0=0, select bank0
	bsf	(49/8),(49)&7	;volatile
# 97 "H:\8bit-RGB\main.c"
nop ;# 
psect	text6
	line	98
;main.c: 98: RB1 = 0; asm("nop"); asm("nop"); asm("nop");
	bcf	status, 5	;RP0=0, select bank0
	bcf	(49/8),(49)&7	;volatile
# 98 "H:\8bit-RGB\main.c"
nop ;# 
# 98 "H:\8bit-RGB\main.c"
nop ;# 
# 98 "H:\8bit-RGB\main.c"
nop ;# 
psect	text6
	line	99
	
l1456:	
	line	101
;main.c: 99: }
;main.c: 101: GIE = 1;
	bsf	(95/8),(95)&7	;volatile
	line	102
	
l1457:	
	return
	opt stack 0
GLOBAL	__end_of_ws2812_send_byte
	__end_of_ws2812_send_byte:
	signat	_ws2812_send_byte,4217
	global	_ws2812_reset

;; *************** function _ws2812_reset *****************
;; Defined at:
;;		line 110 in file "H:\8bit-RGB\main.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;                  1    wreg      void 
;; Registers used:
;;		wreg, status,2, status,0, pclath, cstack
;; Tracked objects:
;;		On entry : 100/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1
;;      Params:         0       0       0
;;      Locals:         0       0       0
;;      Temps:          0       0       0
;;      Totals:         0       0       0
;;Total ram usage:        0 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    1
;; This function calls:
;;		_delay_ms
;; This function is called by:
;;		_ws2812_update_RGB
;; This function uses a non-reentrant model
;;
psect	text7,local,class=CODE,delta=2,merge=1,group=0
	line	110
global __ptext7
__ptext7:	;psect for function _ws2812_reset
psect	text7
	file	"H:\8bit-RGB\main.c"
	line	110
	global	__size_of_ws2812_reset
	__size_of_ws2812_reset	equ	__end_of_ws2812_reset-_ws2812_reset
	
_ws2812_reset:	
;incstack = 0
	opt	stack 5
; Regs used in _ws2812_reset: [wreg+status,2+status,0+pclath+cstack]
	line	111
	
l3131:	
;main.c: 111: RB1 = 0;
	bcf	(49/8),(49)&7	;volatile
	line	112
	
l3133:	
;main.c: 112: delay_ms(1);
	clrf	(delay_ms@ms)
	incf	(delay_ms@ms),f
	clrf	(delay_ms@ms+1)
	fcall	_delay_ms
	line	113
	
l1463:	
	return
	opt stack 0
GLOBAL	__end_of_ws2812_reset
	__end_of_ws2812_reset:
	signat	_ws2812_reset,89
	global	_delay_ms

;; *************** function _delay_ms *****************
;; Defined at:
;;		line 22 in file "H:\8bit-RGB\main.c"
;; Parameters:    Size  Location     Type
;;  ms              2    0[COMMON] unsigned int 
;; Auto vars:     Size  Location     Type
;;  j               2    4[COMMON] unsigned int 
;;  i               2    2[COMMON] unsigned int 
;; Return value:  Size  Location     Type
;;                  1    wreg      void 
;; Registers used:
;;		wreg, status,2, status,0
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1
;;      Params:         2       0       0
;;      Locals:         4       0       0
;;      Temps:          0       0       0
;;      Totals:         6       0       0
;;Total ram usage:        6 bytes
;; Hardware stack levels used:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_ws2812_reset
;;		_key_scan
;;		_main
;; This function uses a non-reentrant model
;;
psect	text8,local,class=CODE,delta=2,merge=1,group=0
	line	22
global __ptext8
__ptext8:	;psect for function _delay_ms
psect	text8
	file	"H:\8bit-RGB\main.c"
	line	22
	global	__size_of_delay_ms
	__size_of_delay_ms	equ	__end_of_delay_ms-_delay_ms
	
_delay_ms:	
;incstack = 0
	opt	stack 5
; Regs used in _delay_ms: [wreg+status,2+status,0]
	line	24
	
l3085:	
;main.c: 23: unsigned int i, j;
;main.c: 24: for (i = 0; i < ms; i++) {
	clrf	(delay_ms@i)
	clrf	(delay_ms@i+1)
	goto	l3099
	line	25
	
l3087:	
;main.c: 25: for (j = 0; j < 1333; j++) {
	clrf	(delay_ms@j)
	clrf	(delay_ms@j+1)
	
l1435:	
	line	26
# 26 "H:\8bit-RGB\main.c"
nop ;# 
psect	text8
	line	25
	
l3093:	
	incf	(delay_ms@j),f
	skipnz
	incf	(delay_ms@j+1),f
	
l3095:	
	movlw	05h
	subwf	(delay_ms@j+1),w
	movlw	035h
	skipnz
	subwf	(delay_ms@j),w
	skipc
	goto	u1231
	goto	u1230
u1231:
	goto	l1435
u1230:
	line	24
	
l3097:	
	incf	(delay_ms@i),f
	skipnz
	incf	(delay_ms@i+1),f
	
l3099:	
	movf	(delay_ms@ms+1),w
	subwf	(delay_ms@i+1),w
	skipz
	goto	u1245
	movf	(delay_ms@ms),w
	subwf	(delay_ms@i),w
u1245:
	skipc
	goto	u1241
	goto	u1240
u1241:
	goto	l3087
u1240:
	line	29
	
l1438:	
	return
	opt stack 0
GLOBAL	__end_of_delay_ms
	__end_of_delay_ms:
	signat	_delay_ms,4217
	global	_effect_execute

;; *************** function _effect_execute *****************
;; Defined at:
;;		line 471 in file "H:\8bit-RGB\effects.c"
;; Parameters:    Size  Location     Type
;;  mode            1    wreg     enum E587
;; Auto vars:     Size  Location     Type
;;  mode            1   13[COMMON] enum E587
;; Return value:  Size  Location     Type
;;                  1    wreg      void 
;; Registers used:
;;		wreg, fsr0l, fsr0h, status,2, status,0, pclath, cstack
;; Tracked objects:
;;		On entry : 100/0
;;		On exit  : 100/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1
;;      Params:         0       0       0
;;      Locals:         1       0       0
;;      Temps:          0       0       0
;;      Totals:         1       0       0
;;Total ram usage:        1 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    2
;; This function calls:
;;		_breath_init
;;		_chase_init
;;		_expand_init
;;		_marquee_init
;;		_police_init
;;		_stack_init
;;		_twinkle_init
;; This function is called by:
;;		_ws2812_update_RGB
;;		_key_scan
;; This function uses a non-reentrant model
;;
psect	text9,local,class=CODE,delta=2,merge=1,group=0
	file	"H:\8bit-RGB\effects.c"
	line	471
global __ptext9
__ptext9:	;psect for function _effect_execute
psect	text9
	file	"H:\8bit-RGB\effects.c"
	line	471
	global	__size_of_effect_execute
	__size_of_effect_execute	equ	__end_of_effect_execute-_effect_execute
	
_effect_execute:	
;incstack = 0
	opt	stack 4
; Regs used in _effect_execute: [wreg-fsr0h+status,2+status,0+pclath+cstack]
;effect_execute@mode stored from wreg
	movwf	(effect_execute@mode)
	line	472
	
l3125:	
;effects.c: 472: current_effect = mode;
	movf	(effect_execute@mode),w
	movwf	(_current_effect)	;volatile
	line	473
	
l3127:	
;effects.c: 473: effects[mode].init();
	clrc
	rlf	(effect_execute@mode),w
	addlw	low((((_effects)-__stringbase)|8000h))
	movwf	fsr0
	fcall	stringdir
	fcall	fptable
	line	474
	
l813:	
	return
	opt stack 0
GLOBAL	__end_of_effect_execute
	__end_of_effect_execute:
	signat	_effect_execute,4217
	global	_effects_update

;; *************** function _effects_update *****************
;; Defined at:
;;		line 477 in file "H:\8bit-RGB\effects.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;                  1    wreg      void 
;; Registers used:
;;		wreg, fsr0l, fsr0h, status,2, status,0, pclath, cstack
;; Tracked objects:
;;		On entry : 100/0
;;		On exit  : 100/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1
;;      Params:         0       0       0
;;      Locals:         0       0       0
;;      Temps:          0       0       0
;;      Totals:         0       0       0
;;Total ram usage:        0 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    3
;; This function calls:
;;		_breath_update
;;		_chase_update
;;		_expand_update
;;		_marquee_update
;;		_police_update
;;		_stack_update
;;		_twinkle_update
;; This function is called by:
;;		_main
;; This function uses a non-reentrant model
;;
psect	text10,local,class=CODE,delta=2,merge=1,group=0
	line	477
global __ptext10
__ptext10:	;psect for function _effects_update
psect	text10
	file	"H:\8bit-RGB\effects.c"
	line	477
	global	__size_of_effects_update
	__size_of_effects_update	equ	__end_of_effects_update-_effects_update
	
_effects_update:	
;incstack = 0
	opt	stack 4
; Regs used in _effects_update: [wreg-fsr0h+status,2+status,0+pclath+cstack]
	line	478
	
l3729:	
;effects.c: 478: if (current_effect < EFFECT_COUNT) {
	movlw	low(07h)
	subwf	(_current_effect),w	;volatile
	skipnc
	goto	u1961
	goto	u1960
u1961:
	goto	l817
u1960:
	line	479
	
l3731:	
;effects.c: 479: effects[current_effect].update();
	clrc
	rlf	(_current_effect),w	;volatile
	addlw	low((((_effects)-__stringbase)|8000h)+01h)
	movwf	fsr0
	fcall	stringdir
	fcall	fptable
	line	481
	
l817:	
	return
	opt stack 0
GLOBAL	__end_of_effects_update
	__end_of_effects_update:
	signat	_effects_update,89
	global	_twinkle_update
	global	_breath_update
	global	_chase_update
	global	_expand_update
	global	_marquee_update
	global	_stack_update
	global	_police_update

;; *************** function _police_update *****************
;; Defined at:
;;		line 432 in file "H:\8bit-RGB\effects.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;  i               1    3[COMMON] unsigned char 
;;  b               1    2[COMMON] unsigned char 
;;  r               1    1[COMMON] unsigned char 
;;  g               1    0[COMMON] unsigned char 
;; Return value:  Size  Location     Type
;;                  1    wreg      void 
;; Registers used:
;;		wreg, fsr0l, fsr0h, status,2, status,0
;; Tracked objects:
;;		On entry : 100/0
;;		On exit  : 100/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1
;;      Params:         0       0       0
;;      Locals:         4       0       0
;;      Temps:          0       0       0
;;      Totals:         4       0       0
;;Total ram usage:        4 bytes
;; Hardware stack levels used:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_effects_update
;; This function uses a non-reentrant model
;;
psect	text11,local,class=CODE,delta=2,merge=1,group=0
	line	432
global __ptext11
__ptext11:	;psect for function _police_update
psect	text11
	file	"H:\8bit-RGB\effects.c"
	line	432
	global	__size_of_police_update
	__size_of_police_update	equ	__end_of_police_update-_police_update
	
_police_update:	
;incstack = 0
	opt	stack 6
; Regs used in _police_update: [wreg-fsr0h+status,2+status,0]
	line	433
	
l3671:	
;effects.c: 433: police_counter++;
	incf	(_police_counter),f
	line	434
	
l3673:	
;effects.c: 434: if (police_counter < 5) return;
	movlw	low(05h)
	subwf	(_police_counter),w
	skipnc
	goto	u1861
	goto	u1860
u1861:
	goto	l3677
u1860:
	goto	l800
	line	435
	
l3677:	
;effects.c: 435: police_counter = 0;
	clrf	(_police_counter)
	line	437
;effects.c: 437: unsigned char r = 0, g = 0, b = 0;
	clrf	(police_update@r)
	clrf	(police_update@g)
	clrf	(police_update@b)
	line	438
	
l3679:	
;effects.c: 438: if (police_state == 0) {
	movf	((_police_state)),w
	btfss	status,2
	goto	u1871
	goto	u1870
u1871:
	goto	l3683
u1870:
	line	439
	
l3681:	
;effects.c: 439: r = 255;
	movlw	low(0FFh)
	movwf	(police_update@r)
	line	440
;effects.c: 440: } else {
	goto	l3685
	line	441
	
l3683:	
;effects.c: 441: b = 255;
	movlw	low(0FFh)
	movwf	(police_update@b)
	line	444
	
l3685:	
;effects.c: 442: }
;effects.c: 444: for (unsigned char i = 0; i < 24; i++) {
	clrf	(police_update@i)
	line	445
	
l3691:	
;effects.c: 445: leds[i].r = r;
	movf	(police_update@i),w
	addwf	(police_update@i),w
	addwf	(police_update@i),w
	addlw	low(_leds|((0x0)<<8))&0ffh
	movwf	fsr0
	movf	(police_update@r),w
	bcf	status, 7	;select IRP bank1
	movwf	indf
	line	446
;effects.c: 446: leds[i].g = g;
	movf	(police_update@i),w
	addwf	(police_update@i),w
	addwf	(police_update@i),w
	addlw	low(_leds|((0x0)<<8)+01h)&0ffh
	movwf	fsr0
	movf	(police_update@g),w
	movwf	indf
	line	447
;effects.c: 447: leds[i].b = b;
	movf	(police_update@i),w
	addwf	(police_update@i),w
	addwf	(police_update@i),w
	addlw	low(_leds|((0x0)<<8)+02h)&0ffh
	movwf	fsr0
	movf	(police_update@b),w
	movwf	indf
	line	444
	
l3693:	
	incf	(police_update@i),f
	
l3695:	
	movlw	low(018h)
	subwf	(police_update@i),w
	skipc
	goto	u1881
	goto	u1880
u1881:
	goto	l3691
u1880:
	line	450
	
l3697:	
;effects.c: 448: }
;effects.c: 450: police_state = !police_state;
	movf	((_police_state)),w
	btfsc	status,2
	goto	u1891
	goto	u1890
u1891:
	movlw	1
	goto	u1900
u1890:
	movlw	0
u1900:
	movwf	(_police_state)
	line	451
	
l800:	
	return
	opt stack 0
GLOBAL	__end_of_police_update
	__end_of_police_update:
	signat	_police_update,89

;; *************** function _stack_update *****************
;; Defined at:
;;		line 371 in file "H:\8bit-RGB\effects.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;  i               1    2[COMMON] unsigned char 
;;  i               1    1[COMMON] unsigned char 
;; Return value:  Size  Location     Type
;;                  1    wreg      void 
;; Registers used:
;;		wreg, fsr0l, fsr0h, status,2, status,0, pclath, cstack
;; Tracked objects:
;;		On entry : 100/0
;;		On exit  : 100/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1
;;      Params:         0       0       0
;;      Locals:         2       0       0
;;      Temps:          0       0       0
;;      Totals:         2       0       0
;;Total ram usage:        2 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    1
;; This function calls:
;;		_stack_init
;; This function is called by:
;;		_effects_update
;; This function uses a non-reentrant model
;;
psect	text12,local,class=CODE,delta=2,merge=1,group=0
	line	371
global __ptext12
__ptext12:	;psect for function _stack_update
psect	text12
	file	"H:\8bit-RGB\effects.c"
	line	371
	global	__size_of_stack_update
	__size_of_stack_update	equ	__end_of_stack_update-_stack_update
	
_stack_update:	
;incstack = 0
	opt	stack 5
; Regs used in _stack_update: [wreg-fsr0h+status,2+status,0+pclath+cstack]
	line	374
	
l3615:	
;effects.c: 373: static unsigned char counter = 0;
;effects.c: 374: counter++;
	incf	(stack_update@counter),f
	line	375
	
l3617:	
;effects.c: 375: if (counter < 1) return;
	movf	((stack_update@counter)),w
	btfss	status,2
	goto	u1791
	goto	u1790
u1791:
	goto	l3621
u1790:
	goto	l779
	line	376
	
l3621:	
;effects.c: 376: counter = 0;
	clrf	(stack_update@counter)
	line	379
	
l3623:	
;effects.c: 379: if (stack_lit_count >= 24) {
	movlw	low(018h)
	subwf	(_stack_lit_count),w
	skipc
	goto	u1801
	goto	u1800
u1801:
	goto	l3633
u1800:
	line	380
	
l3625:	
;effects.c: 380: stack_delay++;
	incf	(_stack_delay),f
	line	381
	
l3627:	
;effects.c: 381: if (stack_delay > 30) {
	movlw	low(01Fh)
	subwf	(_stack_delay),w
	skipc
	goto	u1811
	goto	u1810
u1811:
	goto	l779
u1810:
	line	382
	
l3629:	
;effects.c: 382: stack_init();
	fcall	_stack_init
	goto	l779
	line	388
	
l3633:	
;effects.c: 385: }
;effects.c: 388: for (unsigned char i = 0; i < 24; i++) {
	clrf	(stack_update@i)
	line	389
	
l3639:	
;effects.c: 389: leds[i].r = 0;
	movf	(stack_update@i),w
	addwf	(stack_update@i),w
	addwf	(stack_update@i),w
	addlw	low(_leds|((0x0)<<8))&0ffh
	movwf	fsr0
	bcf	status, 7	;select IRP bank1
	clrf	indf
	line	390
;effects.c: 390: leds[i].g = 0;
	movf	(stack_update@i),w
	addwf	(stack_update@i),w
	addwf	(stack_update@i),w
	addlw	low(_leds|((0x0)<<8)+01h)&0ffh
	movwf	fsr0
	clrf	indf
	line	391
;effects.c: 391: leds[i].b = 0;
	movf	(stack_update@i),w
	addwf	(stack_update@i),w
	addwf	(stack_update@i),w
	addlw	low(_leds|((0x0)<<8)+02h)&0ffh
	movwf	fsr0
	clrf	indf
	line	388
	
l3641:	
	incf	(stack_update@i),f
	
l3643:	
	movlw	low(018h)
	subwf	(stack_update@i),w
	skipc
	goto	u1821
	goto	u1820
u1821:
	goto	l3639
u1820:
	line	395
	
l3645:	
;effects.c: 392: }
;effects.c: 395: for (unsigned char i = stack_target + 1; i < 24; i++) {
	movf	(_stack_target),w
	addlw	01h
	movwf	(stack_update@i_428)
	
l3647:	
	movlw	low(018h)
	subwf	(stack_update@i_428),w
	skipc
	goto	u1831
	goto	u1830
u1831:
	goto	l3651
u1830:
	goto	l3657
	line	396
	
l3651:	
;effects.c: 396: leds[i].r = 255;
	movf	(stack_update@i_428),w
	addwf	(stack_update@i_428),w
	addwf	(stack_update@i_428),w
	addlw	low(_leds|((0x0)<<8))&0ffh
	movwf	fsr0
	movlw	low(0FFh)
	movwf	indf
	line	397
;effects.c: 397: leds[i].g = 100;
	movf	(stack_update@i_428),w
	addwf	(stack_update@i_428),w
	addwf	(stack_update@i_428),w
	addlw	low(_leds|((0x0)<<8)+01h)&0ffh
	movwf	fsr0
	movlw	low(064h)
	movwf	indf
	line	398
;effects.c: 398: leds[i].b = 50;
	movf	(stack_update@i_428),w
	addwf	(stack_update@i_428),w
	addwf	(stack_update@i_428),w
	addlw	low(_leds|((0x0)<<8)+02h)&0ffh
	movwf	fsr0
	movlw	low(032h)
	movwf	indf
	line	395
	
l3653:	
	incf	(stack_update@i_428),f
	goto	l3647
	line	402
	
l3657:	
;effects.c: 399: }
;effects.c: 402: leds[stack_runner].r = 255;
	movf	(_stack_runner),w
	addwf	(_stack_runner),w
	addwf	(_stack_runner),w
	addlw	low(_leds|((0x0)<<8))&0ffh
	movwf	fsr0
	movlw	low(0FFh)
	movwf	indf
	line	403
;effects.c: 403: leds[stack_runner].g = 255;
	movf	(_stack_runner),w
	addwf	(_stack_runner),w
	addwf	(_stack_runner),w
	addlw	low(_leds|((0x0)<<8)+01h)&0ffh
	movwf	fsr0
	movlw	low(0FFh)
	movwf	indf
	line	404
;effects.c: 404: leds[stack_runner].b = 0;
	movf	(_stack_runner),w
	addwf	(_stack_runner),w
	addwf	(_stack_runner),w
	addlw	low(_leds|((0x0)<<8)+02h)&0ffh
	movwf	fsr0
	clrf	indf
	line	407
	
l3659:	
;effects.c: 407: stack_runner++;
	incf	(_stack_runner),f
	line	408
	
l3661:	
;effects.c: 408: if (stack_runner > stack_target) {
	movf	(_stack_runner),w
	subwf	(_stack_target),w
	skipnc
	goto	u1841
	goto	u1840
u1841:
	goto	l779
u1840:
	line	409
	
l3663:	
;effects.c: 409: stack_lit_count++;
	incf	(_stack_lit_count),f
	line	410
	
l3665:	
;effects.c: 410: if (stack_target > 0) {
	movf	((_stack_target)),w
	btfsc	status,2
	goto	u1851
	goto	u1850
u1851:
	goto	l3669
u1850:
	line	411
	
l3667:	
;effects.c: 411: stack_target--;
	decf	(_stack_target),f
	line	413
	
l3669:	
;effects.c: 412: }
;effects.c: 413: stack_runner = 0;
	clrf	(_stack_runner)
	line	415
	
l779:	
	return
	opt stack 0
GLOBAL	__end_of_stack_update
	__end_of_stack_update:
	signat	_stack_update,89

;; *************** function _marquee_update *****************
;; Defined at:
;;		line 308 in file "H:\8bit-RGB\effects.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;  pos             1   10[COMMON] unsigned char 
;;  i               1   11[COMMON] unsigned char 
;;  i               1   12[COMMON] unsigned char 
;;  b               1    9[COMMON] unsigned char 
;;  g               1    8[COMMON] unsigned char 
;;  r               1    7[COMMON] unsigned char 
;;  old_pos         1    6[COMMON] unsigned char 
;; Return value:  Size  Location     Type
;;                  1    wreg      void 
;; Registers used:
;;		wreg, fsr0l, fsr0h, status,2, status,0, pclath, cstack
;; Tracked objects:
;;		On entry : 100/0
;;		On exit  : 100/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1
;;      Params:         0       0       0
;;      Locals:         7       0       0
;;      Temps:          0       0       0
;;      Totals:         7       0       0
;;Total ram usage:        7 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    1
;; This function calls:
;;		___awmod
;; This function is called by:
;;		_effects_update
;; This function uses a non-reentrant model
;;
psect	text13,local,class=CODE,delta=2,merge=1,group=0
	line	308
global __ptext13
__ptext13:	;psect for function _marquee_update
psect	text13
	file	"H:\8bit-RGB\effects.c"
	line	308
	global	__size_of_marquee_update
	__size_of_marquee_update	equ	__end_of_marquee_update-_marquee_update
	
_marquee_update:	
;incstack = 0
	opt	stack 5
; Regs used in _marquee_update: [wreg-fsr0h+status,2+status,0+pclath+cstack]
	line	313
	
l3525:	
;effects.c: 310: static unsigned char counter = 0;
;effects.c: 311: static unsigned char color_index = 0;
;effects.c: 313: counter++;
	incf	(marquee_update@counter),f
	line	314
	
l3527:	
;effects.c: 314: if (counter < 2 * 10) return;
	movlw	low(014h)
	subwf	(marquee_update@counter),w
	skipnc
	goto	u1751
	goto	u1750
u1751:
	goto	l3531
u1750:
	goto	l747
	line	315
	
l3531:	
;effects.c: 315: counter = 0;
	clrf	(marquee_update@counter)
	line	318
;effects.c: 318: for (unsigned char i = 0; i < 24; i++) {
	clrf	(marquee_update@i)
	line	319
	
l3537:	
;effects.c: 319: leds[i].r = 0;
	movf	(marquee_update@i),w
	addwf	(marquee_update@i),w
	addwf	(marquee_update@i),w
	addlw	low(_leds|((0x0)<<8))&0ffh
	movwf	fsr0
	bcf	status, 7	;select IRP bank1
	clrf	indf
	line	320
;effects.c: 320: leds[i].g = 0;
	movf	(marquee_update@i),w
	addwf	(marquee_update@i),w
	addwf	(marquee_update@i),w
	addlw	low(_leds|((0x0)<<8)+01h)&0ffh
	movwf	fsr0
	clrf	indf
	line	321
;effects.c: 321: leds[i].b = 0;
	movf	(marquee_update@i),w
	addwf	(marquee_update@i),w
	addwf	(marquee_update@i),w
	addlw	low(_leds|((0x0)<<8)+02h)&0ffh
	movwf	fsr0
	clrf	indf
	line	318
	
l3539:	
	incf	(marquee_update@i),f
	
l3541:	
	movlw	low(018h)
	subwf	(marquee_update@i),w
	skipc
	goto	u1761
	goto	u1760
u1761:
	goto	l3537
u1760:
	line	325
	
l3543:	
;effects.c: 322: }
;effects.c: 325: unsigned char r = 0, g = 0, b = 0;
	clrf	(marquee_update@r)
	clrf	(marquee_update@g)
	clrf	(marquee_update@b)
	line	326
;effects.c: 326: switch (color_index) {
	goto	l3579
	line	327
	
l3545:	
	movlw	low(0FFh)
	movwf	(marquee_update@r)
	
l3547:	
	clrf	(marquee_update@g)
	
l3549:	
	clrf	(marquee_update@b)
	goto	l3581
	line	328
	
l3551:	
	clrf	(marquee_update@r)
	
l3553:	
	movlw	low(0FFh)
	movwf	(marquee_update@g)
	goto	l3549
	line	329
	
l3557:	
	clrf	(marquee_update@r)
	clrf	(marquee_update@g)
	
l3559:	
	movlw	low(0FFh)
	movwf	(marquee_update@b)
	goto	l3581
	line	330
	
l3561:	
	movlw	low(0FFh)
	movwf	(marquee_update@r)
	movlw	low(0FFh)
	movwf	(marquee_update@g)
	goto	l3549
	line	331
	
l3565:	
	movlw	low(0FFh)
	movwf	(marquee_update@r)
	
l3567:	
	clrf	(marquee_update@g)
	goto	l3559
	line	332
	
l3571:	
	clrf	(marquee_update@r)
	
l3573:	
	movlw	low(0FFh)
	movwf	(marquee_update@g)
	goto	l3559
	line	326
	
l3579:	
	movf	(marquee_update@color_index),w
	; Switch size 1, requested type "space"
; Number of cases is 6, Range of values is 0 to 5
; switch strategies available:
; Name         Instructions Cycles
; direct_byte           12     6 (fixed)
; simple_byte           19    10 (average)
; jumptable            260     6 (fixed)
;	Chosen strategy is direct_byte

	movwf fsr
	movlw	6
	subwf	fsr,w
skipnc
goto l3581
movlw high(S3941)
movwf pclath
	movlw low(S3941)
	addwf fsr,w
	movwf pc
psect	swtext1,local,class=CONST,delta=2
global __pswtext1
__pswtext1:
S3941:
	ljmp	l3545
	ljmp	l3551
	ljmp	l3557
	ljmp	l3561
	ljmp	l3565
	ljmp	l3571
psect	text13

	line	336
	
l3581:	
;effects.c: 336: for (unsigned char i = 0; i < 8; i++) {
	clrf	(marquee_update@i_415)
	line	337
	
l3587:	
;effects.c: 337: unsigned char pos = (marquee_pos + i) % 24;
	movf	(_marquee_pos),w
	movwf	(___awmod@dividend)
	clrf	(___awmod@dividend+1)
	movf	(marquee_update@i_415),w
	addwf	(___awmod@dividend),f
	skipnc
	incf	(___awmod@dividend+1),f
	movlw	018h
	movwf	(___awmod@divisor)
	clrf	(___awmod@divisor+1)
	fcall	___awmod
	movf	(0+(?___awmod)),w
	movwf	(marquee_update@pos)
	line	338
	
l3589:	
;effects.c: 338: leds[pos].r = r;
	movf	(marquee_update@pos),w
	addwf	(marquee_update@pos),w
	addwf	(marquee_update@pos),w
	addlw	low(_leds|((0x0)<<8))&0ffh
	movwf	fsr0
	movf	(marquee_update@r),w
	bcf	status, 7	;select IRP bank1
	movwf	indf
	line	339
	
l3591:	
;effects.c: 339: leds[pos].g = g;
	movf	(marquee_update@pos),w
	addwf	(marquee_update@pos),w
	addwf	(marquee_update@pos),w
	addlw	low(_leds|((0x0)<<8)+01h)&0ffh
	movwf	fsr0
	movf	(marquee_update@g),w
	movwf	indf
	line	340
	
l3593:	
;effects.c: 340: leds[pos].b = b;
	movf	(marquee_update@pos),w
	addwf	(marquee_update@pos),w
	addwf	(marquee_update@pos),w
	addlw	low(_leds|((0x0)<<8)+02h)&0ffh
	movwf	fsr0
	movf	(marquee_update@b),w
	movwf	indf
	line	336
	
l3595:	
	incf	(marquee_update@i_415),f
	
l3597:	
	movlw	low(08h)
	subwf	(marquee_update@i_415),w
	skipc
	goto	u1771
	goto	u1770
u1771:
	goto	l3587
u1770:
	line	344
	
l3599:	
;effects.c: 341: }
;effects.c: 344: unsigned char old_pos = marquee_pos;
	movf	(_marquee_pos),w
	movwf	(marquee_update@old_pos)
	line	345
	
l3601:	
;effects.c: 345: marquee_pos = (marquee_pos + 1) % 24;
	movf	(_marquee_pos),w
	movwf	(___awmod@dividend)
	clrf	(___awmod@dividend+1)
	incf	(___awmod@dividend),f
	skipnz
	incf	(___awmod@dividend+1),f
	movlw	018h
	movwf	(___awmod@divisor)
	clrf	(___awmod@divisor+1)
	fcall	___awmod
	movf	(0+(?___awmod)),w
	movwf	(_marquee_pos)
	line	348
	
l3603:	
;effects.c: 348: if (marquee_pos < old_pos) {
	movf	(marquee_update@old_pos),w
	subwf	(_marquee_pos),w
	skipnc
	goto	u1781
	goto	u1780
u1781:
	goto	l747
u1780:
	line	349
	
l3605:	
;effects.c: 349: color_index = (color_index + 1) % 6;
	movf	(marquee_update@color_index),w
	movwf	(___awmod@dividend)
	clrf	(___awmod@dividend+1)
	incf	(___awmod@dividend),f
	skipnz
	incf	(___awmod@dividend+1),f
	movlw	06h
	movwf	(___awmod@divisor)
	clrf	(___awmod@divisor+1)
	fcall	___awmod
	movf	(0+(?___awmod)),w
	movwf	(marquee_update@color_index)
	line	351
	
l747:	
	return
	opt stack 0
GLOBAL	__end_of_marquee_update
	__end_of_marquee_update:
	signat	_marquee_update,89

;; *************** function _expand_update *****************
;; Defined at:
;;		line 241 in file "H:\8bit-RGB\effects.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;  i               1   13[COMMON] unsigned char 
;;  right           1   12[COMMON] unsigned char 
;;  left            1   11[COMMON] unsigned char 
;;  right           1   10[COMMON] unsigned char 
;;  left            1    9[COMMON] unsigned char 
;; Return value:  Size  Location     Type
;;                  1    wreg      void 
;; Registers used:
;;		wreg, fsr0l, fsr0h, status,2, status,0, pclath, cstack
;; Tracked objects:
;;		On entry : 100/0
;;		On exit  : 100/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1
;;      Params:         0       0       0
;;      Locals:         5       0       0
;;      Temps:          0       0       0
;;      Totals:         5       0       0
;;Total ram usage:        5 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    2
;; This function calls:
;;		___awmod
;;		_random_value
;; This function is called by:
;;		_effects_update
;; This function uses a non-reentrant model
;;
psect	text14,local,class=CODE,delta=2,merge=1,group=0
	line	241
global __ptext14
__ptext14:	;psect for function _expand_update
psect	text14
	file	"H:\8bit-RGB\effects.c"
	line	241
	global	__size_of_expand_update
	__size_of_expand_update	equ	__end_of_expand_update-_expand_update
	
_expand_update:	
;incstack = 0
	opt	stack 4
; Regs used in _expand_update: [wreg-fsr0h+status,2+status,0+pclath+cstack]
	line	243
	
l3443:	
;effects.c: 242: static unsigned char counter = 0;
;effects.c: 243: counter++;
	incf	(expand_update@counter),f
	line	244
	
l3445:	
;effects.c: 244: if (counter < 1) return;
	movf	((expand_update@counter)),w
	btfss	status,2
	goto	u1651
	goto	u1650
u1651:
	goto	l3449
u1650:
	goto	l721
	line	245
	
l3449:	
;effects.c: 245: counter = 0;
	clrf	(expand_update@counter)
	line	247
	
l3451:	
;effects.c: 247: if (expand_size >= 24 / 2) {
	movlw	low(0Ch)
	subwf	(_expand_size),w
	skipc
	goto	u1661
	goto	u1660
u1661:
	goto	l3455
u1660:
	line	248
	
l3453:	
;effects.c: 248: expand_dir = -1;
	clrf	(_expand_dir)
	decf	(_expand_dir),f
	line	249
;effects.c: 249: } else if (expand_size == 0 && expand_dir < 0) {
	goto	l3489
	
l3455:	
	movf	((_expand_size)),w
	btfss	status,2
	goto	u1671
	goto	u1670
u1671:
	goto	l3489
u1670:
	
l3457:	
	btfss	(_expand_dir),7
	goto	u1681
	goto	u1680
u1681:
	goto	l3489
u1680:
	line	250
	
l3459:	
;effects.c: 250: expand_dir = 1;
	clrf	(_expand_dir)
	incf	(_expand_dir),f
	line	251
	
l3461:	
;effects.c: 251: expand_seed += 97;
	movlw	low(061h)
	addwf	(_expand_seed),f
	line	252
	
l3463:	
;effects.c: 252: expand_r = random_value(expand_seed);
	movf	(_expand_seed),w
	fcall	_random_value
	movwf	(_expand_r)
	line	253
	
l3465:	
;effects.c: 253: expand_g = random_value(expand_seed + 67);
	movf	(_expand_seed),w
	addlw	043h
	fcall	_random_value
	movwf	(_expand_g)
	line	254
	
l3467:	
;effects.c: 254: expand_b = random_value(expand_seed + 133);
	movf	(_expand_seed),w
	addlw	085h
	fcall	_random_value
	movwf	(_expand_b)
	line	255
	
l3469:	
;effects.c: 255: if (expand_r < 100 && expand_g < 100 && expand_b < 100) {
	movlw	low(064h)
	subwf	(_expand_r),w
	skipnc
	goto	u1691
	goto	u1690
u1691:
	goto	l3477
u1690:
	
l3471:	
	movlw	low(064h)
	subwf	(_expand_g),w
	skipnc
	goto	u1701
	goto	u1700
u1701:
	goto	l3477
u1700:
	
l3473:	
	movlw	low(064h)
	subwf	(_expand_b),w
	skipnc
	goto	u1711
	goto	u1710
u1711:
	goto	l3477
u1710:
	line	256
	
l3475:	
;effects.c: 256: expand_r = 200;
	movlw	low(0C8h)
	movwf	(_expand_r)
	line	258
	
l3477:	
;effects.c: 257: }
;effects.c: 258: for (unsigned char i = 0; i < 24; i++) {
	clrf	(expand_update@i)
	line	259
	
l3483:	
;effects.c: 259: leds[i].r = 0;
	movf	(expand_update@i),w
	addwf	(expand_update@i),w
	addwf	(expand_update@i),w
	addlw	low(_leds|((0x0)<<8))&0ffh
	movwf	fsr0
	bcf	status, 7	;select IRP bank1
	clrf	indf
	line	260
;effects.c: 260: leds[i].g = 0;
	movf	(expand_update@i),w
	addwf	(expand_update@i),w
	addwf	(expand_update@i),w
	addlw	low(_leds|((0x0)<<8)+01h)&0ffh
	movwf	fsr0
	clrf	indf
	line	261
;effects.c: 261: leds[i].b = 0;
	movf	(expand_update@i),w
	addwf	(expand_update@i),w
	addwf	(expand_update@i),w
	addlw	low(_leds|((0x0)<<8)+02h)&0ffh
	movwf	fsr0
	clrf	indf
	line	258
	
l3485:	
	incf	(expand_update@i),f
	
l3487:	
	movlw	low(018h)
	subwf	(expand_update@i),w
	skipc
	goto	u1721
	goto	u1720
u1721:
	goto	l3483
u1720:
	goto	l721
	line	266
	
l3489:	
;effects.c: 264: }
;effects.c: 266: if (expand_dir > 0) {
	movf	(_expand_dir),w
	xorlw	80h
	addlw	-((01h)^80h)
	skipc
	goto	u1731
	goto	u1730
u1731:
	goto	l3507
u1730:
	line	267
	
l3491:	
;effects.c: 267: unsigned char left = (12 - expand_size + 24) % 24;
	movlw	024h
	movwf	(___awmod@dividend)
	clrf	(___awmod@dividend+1)
	movf	(_expand_size),w
	subwf	(___awmod@dividend),f
	skipc
	decf	(___awmod@dividend+1),f
	movlw	018h
	movwf	(___awmod@divisor)
	clrf	(___awmod@divisor+1)
	fcall	___awmod
	movf	(0+(?___awmod)),w
	movwf	(expand_update@left)
	line	268
;effects.c: 268: unsigned char right = (12 + expand_size) % 24;
	movf	(_expand_size),w
	movwf	(___awmod@dividend)
	clrf	(___awmod@dividend+1)
	movlw	0Ch
	addwf	(___awmod@dividend),f
	skipnc
	incf	(___awmod@dividend+1),f
	movlw	018h
	movwf	(___awmod@divisor)
	clrf	(___awmod@divisor+1)
	fcall	___awmod
	movf	(0+(?___awmod)),w
	movwf	(expand_update@right)
	line	269
	
l3493:	
;effects.c: 269: leds[left].r = expand_r;
	movf	(expand_update@left),w
	addwf	(expand_update@left),w
	addwf	(expand_update@left),w
	addlw	low(_leds|((0x0)<<8))&0ffh
	movwf	fsr0
	movf	(_expand_r),w
	bcf	status, 7	;select IRP bank1
	movwf	indf
	line	270
	
l3495:	
;effects.c: 270: leds[left].g = expand_g;
	movf	(expand_update@left),w
	addwf	(expand_update@left),w
	addwf	(expand_update@left),w
	addlw	low(_leds|((0x0)<<8)+01h)&0ffh
	movwf	fsr0
	movf	(_expand_g),w
	movwf	indf
	line	271
	
l3497:	
;effects.c: 271: leds[left].b = expand_b;
	movf	(expand_update@left),w
	addwf	(expand_update@left),w
	addwf	(expand_update@left),w
	addlw	low(_leds|((0x0)<<8)+02h)&0ffh
	movwf	fsr0
	movf	(_expand_b),w
	movwf	indf
	line	272
	
l3499:	
;effects.c: 272: leds[right].r = expand_r;
	movf	(expand_update@right),w
	addwf	(expand_update@right),w
	addwf	(expand_update@right),w
	addlw	low(_leds|((0x0)<<8))&0ffh
	movwf	fsr0
	movf	(_expand_r),w
	movwf	indf
	line	273
	
l3501:	
;effects.c: 273: leds[right].g = expand_g;
	movf	(expand_update@right),w
	addwf	(expand_update@right),w
	addwf	(expand_update@right),w
	addlw	low(_leds|((0x0)<<8)+01h)&0ffh
	movwf	fsr0
	movf	(_expand_g),w
	movwf	indf
	line	274
	
l3503:	
;effects.c: 274: leds[right].b = expand_b;
	movf	(expand_update@right),w
	addwf	(expand_update@right),w
	addwf	(expand_update@right),w
	addlw	low(_leds|((0x0)<<8)+02h)&0ffh
	movwf	fsr0
	movf	(_expand_b),w
	movwf	indf
	line	275
	
l3505:	
;effects.c: 275: expand_size++;
	incf	(_expand_size),f
	line	276
;effects.c: 276: } else {
	goto	l721
	line	277
	
l3507:	
;effects.c: 277: unsigned char left = (12 - expand_size + 24) % 24;
	movlw	024h
	movwf	(___awmod@dividend)
	clrf	(___awmod@dividend+1)
	movf	(_expand_size),w
	subwf	(___awmod@dividend),f
	skipc
	decf	(___awmod@dividend+1),f
	movlw	018h
	movwf	(___awmod@divisor)
	clrf	(___awmod@divisor+1)
	fcall	___awmod
	movf	(0+(?___awmod)),w
	movwf	(expand_update@left_402)
	line	278
;effects.c: 278: unsigned char right = (12 + expand_size) % 24;
	movf	(_expand_size),w
	movwf	(___awmod@dividend)
	clrf	(___awmod@dividend+1)
	movlw	0Ch
	addwf	(___awmod@dividend),f
	skipnc
	incf	(___awmod@dividend+1),f
	movlw	018h
	movwf	(___awmod@divisor)
	clrf	(___awmod@divisor+1)
	fcall	___awmod
	movf	(0+(?___awmod)),w
	movwf	(expand_update@right_403)
	line	279
	
l3509:	
;effects.c: 279: leds[left].r = 0;
	movf	(expand_update@left_402),w
	addwf	(expand_update@left_402),w
	addwf	(expand_update@left_402),w
	addlw	low(_leds|((0x0)<<8))&0ffh
	movwf	fsr0
	bcf	status, 7	;select IRP bank1
	clrf	indf
	line	280
	
l3511:	
;effects.c: 280: leds[left].g = 0;
	movf	(expand_update@left_402),w
	addwf	(expand_update@left_402),w
	addwf	(expand_update@left_402),w
	addlw	low(_leds|((0x0)<<8)+01h)&0ffh
	movwf	fsr0
	clrf	indf
	line	281
	
l3513:	
;effects.c: 281: leds[left].b = 0;
	movf	(expand_update@left_402),w
	addwf	(expand_update@left_402),w
	addwf	(expand_update@left_402),w
	addlw	low(_leds|((0x0)<<8)+02h)&0ffh
	movwf	fsr0
	clrf	indf
	line	282
	
l3515:	
;effects.c: 282: leds[right].r = 0;
	movf	(expand_update@right_403),w
	addwf	(expand_update@right_403),w
	addwf	(expand_update@right_403),w
	addlw	low(_leds|((0x0)<<8))&0ffh
	movwf	fsr0
	clrf	indf
	line	283
	
l3517:	
;effects.c: 283: leds[right].g = 0;
	movf	(expand_update@right_403),w
	addwf	(expand_update@right_403),w
	addwf	(expand_update@right_403),w
	addlw	low(_leds|((0x0)<<8)+01h)&0ffh
	movwf	fsr0
	clrf	indf
	line	284
	
l3519:	
;effects.c: 284: leds[right].b = 0;
	movf	(expand_update@right_403),w
	addwf	(expand_update@right_403),w
	addwf	(expand_update@right_403),w
	addlw	low(_leds|((0x0)<<8)+02h)&0ffh
	movwf	fsr0
	clrf	indf
	line	285
	
l3521:	
;effects.c: 285: if (expand_size > 0) expand_size--;
	movf	((_expand_size)),w
	btfsc	status,2
	goto	u1741
	goto	u1740
u1741:
	goto	l721
u1740:
	
l3523:	
	decf	(_expand_size),f
	line	287
	
l721:	
	return
	opt stack 0
GLOBAL	__end_of_expand_update
	__end_of_expand_update:
	signat	_expand_update,89

;; *************** function _chase_update *****************
;; Defined at:
;;		line 172 in file "H:\8bit-RGB\effects.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;  pos             1   10[COMMON] unsigned char 
;;  i               1   11[COMMON] unsigned char 
;;  i               1   12[COMMON] unsigned char 
;;  b               1    9[COMMON] unsigned char 
;;  g               1    8[COMMON] unsigned char 
;;  r               1    7[COMMON] unsigned char 
;;  old_pos         1    6[COMMON] unsigned char 
;; Return value:  Size  Location     Type
;;                  1    wreg      void 
;; Registers used:
;;		wreg, fsr0l, fsr0h, status,2, status,0, pclath, cstack
;; Tracked objects:
;;		On entry : 100/0
;;		On exit  : 100/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1
;;      Params:         0       0       0
;;      Locals:         7       0       0
;;      Temps:          0       0       0
;;      Totals:         7       0       0
;;Total ram usage:        7 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    1
;; This function calls:
;;		___awmod
;; This function is called by:
;;		_effects_update
;; This function uses a non-reentrant model
;;
psect	text15,local,class=CODE,delta=2,merge=1,group=0
	line	172
global __ptext15
__ptext15:	;psect for function _chase_update
psect	text15
	file	"H:\8bit-RGB\effects.c"
	line	172
	global	__size_of_chase_update
	__size_of_chase_update	equ	__end_of_chase_update-_chase_update
	
_chase_update:	
;incstack = 0
	opt	stack 5
; Regs used in _chase_update: [wreg-fsr0h+status,2+status,0+pclath+cstack]
	line	175
	
l3353:	
;effects.c: 174: static unsigned char counter = 0;
;effects.c: 175: counter++;
	incf	(chase_update@counter),f
	line	176
	
l3355:	
;effects.c: 176: if (counter < 2 * 10) return;
	movlw	low(014h)
	subwf	(chase_update@counter),w
	skipnc
	goto	u1611
	goto	u1610
u1611:
	goto	l3359
u1610:
	goto	l680
	line	177
	
l3359:	
;effects.c: 177: counter = 0;
	clrf	(chase_update@counter)
	line	180
;effects.c: 180: for (unsigned char i = 0; i < 24; i++) {
	clrf	(chase_update@i)
	line	181
	
l3365:	
;effects.c: 181: leds[i].r = 0;
	movf	(chase_update@i),w
	addwf	(chase_update@i),w
	addwf	(chase_update@i),w
	addlw	low(_leds|((0x0)<<8))&0ffh
	movwf	fsr0
	bcf	status, 7	;select IRP bank1
	clrf	indf
	line	182
;effects.c: 182: leds[i].g = 0;
	movf	(chase_update@i),w
	addwf	(chase_update@i),w
	addwf	(chase_update@i),w
	addlw	low(_leds|((0x0)<<8)+01h)&0ffh
	movwf	fsr0
	clrf	indf
	line	183
;effects.c: 183: leds[i].b = 0;
	movf	(chase_update@i),w
	addwf	(chase_update@i),w
	addwf	(chase_update@i),w
	addlw	low(_leds|((0x0)<<8)+02h)&0ffh
	movwf	fsr0
	clrf	indf
	line	180
	
l3367:	
	incf	(chase_update@i),f
	
l3369:	
	movlw	low(018h)
	subwf	(chase_update@i),w
	skipc
	goto	u1621
	goto	u1620
u1621:
	goto	l3365
u1620:
	line	187
	
l3371:	
;effects.c: 184: }
;effects.c: 187: unsigned char r = 0, g = 0, b = 0;
	clrf	(chase_update@r)
	clrf	(chase_update@g)
	clrf	(chase_update@b)
	line	188
;effects.c: 188: switch (chase_color_idx) {
	goto	l3407
	line	189
	
l3373:	
	movlw	low(0FFh)
	movwf	(chase_update@r)
	
l3375:	
	clrf	(chase_update@g)
	
l3377:	
	clrf	(chase_update@b)
	goto	l3409
	line	190
	
l3379:	
	clrf	(chase_update@r)
	
l3381:	
	movlw	low(0FFh)
	movwf	(chase_update@g)
	goto	l3377
	line	191
	
l3385:	
	clrf	(chase_update@r)
	clrf	(chase_update@g)
	
l3387:	
	movlw	low(0FFh)
	movwf	(chase_update@b)
	goto	l3409
	line	192
	
l3389:	
	movlw	low(0FFh)
	movwf	(chase_update@r)
	movlw	low(0FFh)
	movwf	(chase_update@g)
	goto	l3377
	line	193
	
l3393:	
	movlw	low(0FFh)
	movwf	(chase_update@r)
	
l3395:	
	clrf	(chase_update@g)
	goto	l3387
	line	194
	
l3399:	
	clrf	(chase_update@r)
	
l3401:	
	movlw	low(0FFh)
	movwf	(chase_update@g)
	goto	l3387
	line	188
	
l3407:	
	movf	(_chase_color_idx),w
	; Switch size 1, requested type "space"
; Number of cases is 6, Range of values is 0 to 5
; switch strategies available:
; Name         Instructions Cycles
; direct_byte           12     6 (fixed)
; simple_byte           19    10 (average)
; jumptable            260     6 (fixed)
;	Chosen strategy is direct_byte

	movwf fsr
	movlw	6
	subwf	fsr,w
skipnc
goto l3409
movlw high(S3943)
movwf pclath
	movlw low(S3943)
	addwf fsr,w
	movwf pc
psect	swtext2,local,class=CONST,delta=2
global __pswtext2
__pswtext2:
S3943:
	ljmp	l3373
	ljmp	l3379
	ljmp	l3385
	ljmp	l3389
	ljmp	l3393
	ljmp	l3399
psect	text15

	line	198
	
l3409:	
;effects.c: 198: for (unsigned char i = 0; i < 3; i++) {
	clrf	(chase_update@i_382)
	line	199
	
l3415:	
;effects.c: 199: unsigned char pos = (chase_pos + i) % 24;
	movf	(_chase_pos),w
	movwf	(___awmod@dividend)
	clrf	(___awmod@dividend+1)
	movf	(chase_update@i_382),w
	addwf	(___awmod@dividend),f
	skipnc
	incf	(___awmod@dividend+1),f
	movlw	018h
	movwf	(___awmod@divisor)
	clrf	(___awmod@divisor+1)
	fcall	___awmod
	movf	(0+(?___awmod)),w
	movwf	(chase_update@pos)
	line	200
	
l3417:	
;effects.c: 200: leds[pos].r = r;
	movf	(chase_update@pos),w
	addwf	(chase_update@pos),w
	addwf	(chase_update@pos),w
	addlw	low(_leds|((0x0)<<8))&0ffh
	movwf	fsr0
	movf	(chase_update@r),w
	bcf	status, 7	;select IRP bank1
	movwf	indf
	line	201
	
l3419:	
;effects.c: 201: leds[pos].g = g;
	movf	(chase_update@pos),w
	addwf	(chase_update@pos),w
	addwf	(chase_update@pos),w
	addlw	low(_leds|((0x0)<<8)+01h)&0ffh
	movwf	fsr0
	movf	(chase_update@g),w
	movwf	indf
	line	202
	
l3421:	
;effects.c: 202: leds[pos].b = b;
	movf	(chase_update@pos),w
	addwf	(chase_update@pos),w
	addwf	(chase_update@pos),w
	addlw	low(_leds|((0x0)<<8)+02h)&0ffh
	movwf	fsr0
	movf	(chase_update@b),w
	movwf	indf
	line	198
	
l3423:	
	incf	(chase_update@i_382),f
	
l3425:	
	movlw	low(03h)
	subwf	(chase_update@i_382),w
	skipc
	goto	u1631
	goto	u1630
u1631:
	goto	l3415
u1630:
	line	206
	
l3427:	
;effects.c: 203: }
;effects.c: 206: unsigned char old_pos = chase_pos;
	movf	(_chase_pos),w
	movwf	(chase_update@old_pos)
	line	207
	
l3429:	
;effects.c: 207: chase_pos = (chase_pos + 1) % 24;
	movf	(_chase_pos),w
	movwf	(___awmod@dividend)
	clrf	(___awmod@dividend+1)
	incf	(___awmod@dividend),f
	skipnz
	incf	(___awmod@dividend+1),f
	movlw	018h
	movwf	(___awmod@divisor)
	clrf	(___awmod@divisor+1)
	fcall	___awmod
	movf	(0+(?___awmod)),w
	movwf	(_chase_pos)
	line	210
	
l3431:	
;effects.c: 210: if (chase_pos < old_pos) {
	movf	(chase_update@old_pos),w
	subwf	(_chase_pos),w
	skipnc
	goto	u1641
	goto	u1640
u1641:
	goto	l680
u1640:
	line	211
	
l3433:	
;effects.c: 211: chase_color_idx = (chase_color_idx + 1) % 6;
	movf	(_chase_color_idx),w
	movwf	(___awmod@dividend)
	clrf	(___awmod@dividend+1)
	incf	(___awmod@dividend),f
	skipnz
	incf	(___awmod@dividend+1),f
	movlw	06h
	movwf	(___awmod@divisor)
	clrf	(___awmod@divisor+1)
	fcall	___awmod
	movf	(0+(?___awmod)),w
	movwf	(_chase_color_idx)
	line	213
	
l680:	
	return
	opt stack 0
GLOBAL	__end_of_chase_update
	__end_of_chase_update:
	signat	_chase_update,89

;; *************** function _breath_update *****************
;; Defined at:
;;		line 23 in file "H:\8bit-RGB\effects.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;  i               1   11[COMMON] unsigned char 
;;  new_val         1   10[COMMON] unsigned char 
;;  old_val         1    9[COMMON] unsigned char 
;;  b               1    8[COMMON] unsigned char 
;;  g               1    7[COMMON] unsigned char 
;;  r               1    6[COMMON] unsigned char 
;; Return value:  Size  Location     Type
;;                  1    wreg      void 
;; Registers used:
;;		wreg, fsr0l, fsr0h, status,2, status,0, pclath, cstack
;; Tracked objects:
;;		On entry : 100/0
;;		On exit  : 100/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1
;;      Params:         0       0       0
;;      Locals:         6       0       0
;;      Temps:          0       0       0
;;      Totals:         6       0       0
;;Total ram usage:        6 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    1
;; This function calls:
;;		___awmod
;;		___bmul
;; This function is called by:
;;		_effects_update
;; This function uses a non-reentrant model
;;
psect	text16,local,class=CODE,delta=2,merge=1,group=0
	line	23
global __ptext16
__ptext16:	;psect for function _breath_update
psect	text16
	file	"H:\8bit-RGB\effects.c"
	line	23
	global	__size_of_breath_update
	__size_of_breath_update	equ	__end_of_breath_update-_breath_update
	
_breath_update:	
;incstack = 0
	opt	stack 5
; Regs used in _breath_update: [wreg-fsr0h+status,2+status,0+pclath+cstack]
	line	26
	
l3215:	
;effects.c: 25: static unsigned char counter = 0;
;effects.c: 26: counter++;
	incf	(breath_update@counter),f
	line	27
	
l3217:	
;effects.c: 27: if (counter < 10) return;
	movlw	low(0Ah)
	subwf	(breath_update@counter),w
	skipnc
	goto	u1471
	goto	u1470
u1471:
	goto	l3221
u1470:
	goto	l621
	line	28
	
l3221:	
;effects.c: 28: counter = 0;
	clrf	(breath_update@counter)
	line	30
;effects.c: 30: unsigned char r = 0, g = 0, b = 0;
	clrf	(breath_update@r)
	clrf	(breath_update@g)
	clrf	(breath_update@b)
	line	33
	
l3223:	
;effects.c: 33: if (breath_transition > 0) {
	movf	((_breath_transition)),w
	btfsc	status,2
	goto	u1481
	goto	u1480
u1481:
	goto	l3251
u1480:
	line	34
	
l3225:	
;effects.c: 34: breath_transition += 2;
	incf	(_breath_transition),f
	incf	(_breath_transition),f
	line	35
	
l3227:	
;effects.c: 35: if (breath_transition > 12) {
	movlw	low(0Dh)
	subwf	(_breath_transition),w
	skipc
	goto	u1491
	goto	u1490
u1491:
	goto	l3237
u1490:
	line	36
	
l3229:	
;effects.c: 36: breath_transition = 0;
	clrf	(_breath_transition)
	line	37
	
l3231:	
;effects.c: 37: breath_color = (breath_color + 1) % 3;
	movf	(_breath_color),w
	movwf	(___awmod@dividend)
	clrf	(___awmod@dividend+1)
	incf	(___awmod@dividend),f
	skipnz
	incf	(___awmod@dividend+1),f
	movlw	03h
	movwf	(___awmod@divisor)
	clrf	(___awmod@divisor+1)
	fcall	___awmod
	movf	(0+(?___awmod)),w
	movwf	(_breath_color)
	line	38
	
l3233:	
;effects.c: 38: breath_val = 25;
	movlw	low(019h)
	movwf	(_breath_val)
	line	39
	
l3235:	
;effects.c: 39: breath_dir = 1;
	clrf	(_breath_dir)
	incf	(_breath_dir),f
	line	43
	
l3237:	
;effects.c: 40: }
;effects.c: 43: unsigned char old_val = 25 - breath_transition;
	movf	(_breath_transition),w
	sublw	019h
	movwf	(breath_update@old_val)
	line	44
	
l3239:	
;effects.c: 44: unsigned char new_val = breath_transition;
	movf	(_breath_transition),w
	movwf	(breath_update@new_val)
	line	46
;effects.c: 46: switch (breath_color) {
	goto	l3249
	line	47
	
l3241:	
	movf	(breath_update@old_val),w
	movwf	(breath_update@r)
	movf	(breath_update@new_val),w
	movwf	(breath_update@g)
	goto	l3277
	line	48
	
l3243:	
	movf	(breath_update@old_val),w
	movwf	(breath_update@g)
	movf	(breath_update@new_val),w
	movwf	(breath_update@b)
	goto	l3277
	line	49
	
l3245:	
	movf	(breath_update@old_val),w
	movwf	(breath_update@b)
	movf	(breath_update@new_val),w
	movwf	(breath_update@r)
	goto	l3277
	line	46
	
l3249:	
	movf	(_breath_color),w
	; Switch size 1, requested type "space"
; Number of cases is 3, Range of values is 0 to 2
; switch strategies available:
; Name         Instructions Cycles
; direct_byte            9     6 (fixed)
; simple_byte           10     6 (average)
; jumptable            260     6 (fixed)
;	Chosen strategy is direct_byte

	movwf fsr
	movlw	3
	subwf	fsr,w
skipnc
goto l3277
movlw high(S3945)
movwf pclath
	movlw low(S3945)
	addwf fsr,w
	movwf pc
psect	swtext3,local,class=CONST,delta=2
global __pswtext3
__pswtext3:
S3945:
	ljmp	l3241
	ljmp	l3243
	ljmp	l3245
psect	text16

	line	55
	
l3251:	
;effects.c: 53: else {
;effects.c: 55: breath_val += breath_dir * 10;
	movlw	low(0Ah)
	movwf	(___bmul@multiplicand)
	movf	(_breath_dir),w
	fcall	___bmul
	addwf	(_breath_val),f
	line	57
	
l3253:	
;effects.c: 57: if (breath_val >= 250) {
	movlw	low(0FAh)
	subwf	(_breath_val),w
	skipc
	goto	u1501
	goto	u1500
u1501:
	goto	l3259
u1500:
	line	58
	
l3255:	
;effects.c: 58: breath_val = 250;
	movlw	low(0FAh)
	movwf	(_breath_val)
	line	59
	
l3257:	
;effects.c: 59: breath_dir = -1;
	clrf	(_breath_dir)
	decf	(_breath_dir),f
	line	60
;effects.c: 60: }
	goto	l3275
	line	61
	
l3259:	
;effects.c: 61: else if (breath_val <= 25 && breath_dir < 0) {
	movlw	low(01Ah)
	subwf	(_breath_val),w
	skipnc
	goto	u1511
	goto	u1510
u1511:
	goto	l3275
u1510:
	
l3261:	
	btfss	(_breath_dir),7
	goto	u1521
	goto	u1520
u1521:
	goto	l3275
u1520:
	line	63
	
l3263:	
;effects.c: 63: breath_transition = 1;
	clrf	(_breath_transition)
	incf	(_breath_transition),f
	line	64
	
l3265:	
;effects.c: 64: breath_val = 25;
	movlw	low(019h)
	movwf	(_breath_val)
	goto	l3275
	line	69
	
l3267:	
	movf	(_breath_val),w
	movwf	(breath_update@r)
	goto	l3277
	line	70
	
l3269:	
	movf	(_breath_val),w
	movwf	(breath_update@g)
	goto	l3277
	line	71
	
l3271:	
	movf	(_breath_val),w
	movwf	(breath_update@b)
	goto	l3277
	line	68
	
l3275:	
	movf	(_breath_color),w
	; Switch size 1, requested type "space"
; Number of cases is 3, Range of values is 0 to 2
; switch strategies available:
; Name         Instructions Cycles
; direct_byte            9     6 (fixed)
; simple_byte           10     6 (average)
; jumptable            260     6 (fixed)
;	Chosen strategy is direct_byte

	movwf fsr
	movlw	3
	subwf	fsr,w
skipnc
goto l3277
movlw high(S3947)
movwf pclath
	movlw low(S3947)
	addwf fsr,w
	movwf pc
psect	swtext4,local,class=CONST,delta=2
global __pswtext4
__pswtext4:
S3947:
	ljmp	l3267
	ljmp	l3269
	ljmp	l3271
psect	text16

	line	75
	
l3277:	
;effects.c: 73: }
;effects.c: 75: for (unsigned char i = 0; i < 24; i++) {
	clrf	(breath_update@i)
	line	76
	
l3283:	
;effects.c: 76: leds[i].r = r;
	movf	(breath_update@i),w
	addwf	(breath_update@i),w
	addwf	(breath_update@i),w
	addlw	low(_leds|((0x0)<<8))&0ffh
	movwf	fsr0
	movf	(breath_update@r),w
	bcf	status, 7	;select IRP bank1
	movwf	indf
	line	77
;effects.c: 77: leds[i].g = g;
	movf	(breath_update@i),w
	addwf	(breath_update@i),w
	addwf	(breath_update@i),w
	addlw	low(_leds|((0x0)<<8)+01h)&0ffh
	movwf	fsr0
	movf	(breath_update@g),w
	movwf	indf
	line	78
;effects.c: 78: leds[i].b = b;
	movf	(breath_update@i),w
	addwf	(breath_update@i),w
	addwf	(breath_update@i),w
	addlw	low(_leds|((0x0)<<8)+02h)&0ffh
	movwf	fsr0
	movf	(breath_update@b),w
	movwf	indf
	line	75
	
l3285:	
	incf	(breath_update@i),f
	
l3287:	
	movlw	low(018h)
	subwf	(breath_update@i),w
	skipc
	goto	u1531
	goto	u1530
u1531:
	goto	l3283
u1530:
	line	80
	
l621:	
	return
	opt stack 0
GLOBAL	__end_of_breath_update
	__end_of_breath_update:
	signat	_breath_update,89

;; *************** function _twinkle_update *****************
;; Defined at:
;;		line 110 in file "H:\8bit-RGB\effects.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;  brightness      1    3[BANK0 ] unsigned char 
;;  color           1    2[BANK0 ] unsigned char 
;;  i               1    5[BANK0 ] unsigned char 
;;  i               1    4[BANK0 ] unsigned char 
;; Return value:  Size  Location     Type
;;                  1    wreg      void 
;; Registers used:
;;		wreg, fsr0l, fsr0h, status,2, status,0, pclath, cstack
;; Tracked objects:
;;		On entry : 100/0
;;		On exit  : 100/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1
;;      Params:         0       0       0
;;      Locals:         0       4       0
;;      Temps:          0       2       0
;;      Totals:         0       6       0
;;Total ram usage:        6 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    1
;; This function calls:
;;		___awdiv
;;		___awmod
;;		___bmul
;;		___wmul
;; This function is called by:
;;		_effects_update
;; This function uses a non-reentrant model
;;
psect	text17,local,class=CODE,delta=2,merge=1,group=0
	line	110
global __ptext17
__ptext17:	;psect for function _twinkle_update
psect	text17
	file	"H:\8bit-RGB\effects.c"
	line	110
	global	__size_of_twinkle_update
	__size_of_twinkle_update	equ	__end_of_twinkle_update-_twinkle_update
	
_twinkle_update:	
;incstack = 0
	opt	stack 5
; Regs used in _twinkle_update: [wreg-fsr0h+status,2+status,0+pclath+cstack]
	line	112
	
l3301:	
;effects.c: 112: twinkle_counter++;
	incf	(_twinkle_counter),f
	line	113
	
l3303:	
;effects.c: 113: if (twinkle_counter < 5) return;
	movlw	low(05h)
	subwf	(_twinkle_counter),w
	skipnc
	goto	u1541
	goto	u1540
u1541:
	goto	l3307
u1540:
	goto	l654
	line	114
	
l3307:	
;effects.c: 114: twinkle_counter = 0;
	clrf	(_twinkle_counter)
	line	117
;effects.c: 117: for (unsigned char i = 0; i < 24; i++) {
	clrf	(twinkle_update@i)
	line	118
	
l3313:	
;effects.c: 118: leds[i].r = 0;
	movf	(twinkle_update@i),w
	addwf	(twinkle_update@i),w
	addwf	(twinkle_update@i),w
	addlw	low(_leds|((0x0)<<8))&0ffh
	movwf	fsr0
	bcf	status, 7	;select IRP bank1
	clrf	indf
	line	119
;effects.c: 119: leds[i].g = 0;
	movf	(twinkle_update@i),w
	addwf	(twinkle_update@i),w
	addwf	(twinkle_update@i),w
	addlw	low(_leds|((0x0)<<8)+01h)&0ffh
	movwf	fsr0
	clrf	indf
	line	120
;effects.c: 120: leds[i].b = 0;
	movf	(twinkle_update@i),w
	addwf	(twinkle_update@i),w
	addwf	(twinkle_update@i),w
	addlw	low(_leds|((0x0)<<8)+02h)&0ffh
	movwf	fsr0
	clrf	indf
	line	117
	
l3315:	
	incf	(twinkle_update@i),f
	
l3317:	
	movlw	low(018h)
	subwf	(twinkle_update@i),w
	skipc
	goto	u1551
	goto	u1550
u1551:
	goto	l3313
u1550:
	line	124
	
l3319:	
;effects.c: 121: }
;effects.c: 124: for (unsigned char i = 0; i < 8; i++) {
	clrf	(twinkle_update@i_369)
	line	126
	
l3325:	
;effects.c: 126: stars[i].phase += stars[i].speed;
	movf	(twinkle_update@i_369),w
	addwf	(twinkle_update@i_369),w
	addwf	(twinkle_update@i_369),w
	addlw	low(_stars|((0x0)<<8)+02h)&0ffh
	movwf	fsr0
	movf	indf,w
	movwf	(??_twinkle_update+0)+0
	movf	(twinkle_update@i_369),w
	addwf	(twinkle_update@i_369),w
	addwf	(twinkle_update@i_369),w
	addlw	low(_stars|((0x0)<<8)+01h)&0ffh
	movwf	fsr0
	movf	(??_twinkle_update+0)+0,w
	addwf	indf,f
	line	127
;effects.c: 127: if (stars[i].phase >= 100) {
	movf	(twinkle_update@i_369),w
	addwf	(twinkle_update@i_369),w
	addwf	(twinkle_update@i_369),w
	addlw	low(_stars|((0x0)<<8)+01h)&0ffh
	movwf	fsr0
	movlw	low(064h)
	subwf	indf,w
	skipc
	goto	u1561
	goto	u1560
u1561:
	goto	l3333
u1560:
	line	128
	
l3327:	
;effects.c: 128: stars[i].phase = 0;
	movf	(twinkle_update@i_369),w
	addwf	(twinkle_update@i_369),w
	addwf	(twinkle_update@i_369),w
	addlw	low(_stars|((0x0)<<8)+01h)&0ffh
	movwf	fsr0
	clrf	indf
	line	130
	
l3329:	
;effects.c: 130: stars[i].pos = (stars[i].pos + 13) % 24;
	movf	(twinkle_update@i_369),w
	addwf	(twinkle_update@i_369),w
	addwf	(twinkle_update@i_369),w
	addlw	low(_stars|((0x0)<<8))&0ffh
	movwf	fsr0
	movf	indf,w
	movwf	(___awmod@dividend)
	clrf	(___awmod@dividend+1)
	movlw	0Dh
	addwf	(___awmod@dividend),f
	skipnc
	incf	(___awmod@dividend+1),f
	movlw	018h
	movwf	(___awmod@divisor)
	clrf	(___awmod@divisor+1)
	fcall	___awmod
	movf	(0+(?___awmod)),w
	movwf	(??_twinkle_update+0)+0
	movf	(twinkle_update@i_369),w
	addwf	(twinkle_update@i_369),w
	addwf	(twinkle_update@i_369),w
	addlw	low(_stars|((0x0)<<8))&0ffh
	movwf	fsr0
	movf	(??_twinkle_update+0)+0,w
	bcf	status, 7	;select IRP bank0
	movwf	indf
	line	131
	
l3331:	
;effects.c: 131: stars[i].speed = 2 + ((stars[i].speed + i) % 4);
	movf	(twinkle_update@i_369),w
	addwf	(twinkle_update@i_369),w
	addwf	(twinkle_update@i_369),w
	addlw	low(_stars|((0x0)<<8)+02h)&0ffh
	movwf	fsr0
	movf	(twinkle_update@i_369),w
	addwf	indf,w
	andlw	03h
	addlw	02h
	movwf	(??_twinkle_update+0)+0
	movf	(twinkle_update@i_369),w
	addwf	(twinkle_update@i_369),w
	addwf	(twinkle_update@i_369),w
	addlw	low(_stars|((0x0)<<8)+02h)&0ffh
	movwf	fsr0
	movf	(??_twinkle_update+0)+0,w
	movwf	indf
	line	136
	
l3333:	
;effects.c: 132: }
;effects.c: 135: unsigned char brightness;
;effects.c: 136: if (stars[i].phase < 50) {
	movf	(twinkle_update@i_369),w
	addwf	(twinkle_update@i_369),w
	addwf	(twinkle_update@i_369),w
	addlw	low(_stars|((0x0)<<8)+01h)&0ffh
	movwf	fsr0
	movlw	low(032h)
	subwf	indf,w
	skipnc
	goto	u1571
	goto	u1570
u1571:
	goto	l3337
u1570:
	line	138
	
l3335:	
;effects.c: 138: brightness = (stars[i].phase * 5) + (stars[i].phase * 3 / 10);
	movlw	0Ah
	movwf	(___awdiv@divisor)
	clrf	(___awdiv@divisor+1)
	movf	(twinkle_update@i_369),w
	addwf	(twinkle_update@i_369),w
	addwf	(twinkle_update@i_369),w
	addlw	low(_stars|((0x0)<<8)+01h)&0ffh
	movwf	fsr0
	movf	indf,w
	movwf	(___wmul@multiplier)
	clrf	(___wmul@multiplier+1)
	movlw	03h
	movwf	(___wmul@multiplicand)
	clrf	(___wmul@multiplicand+1)
	fcall	___wmul
	movf	(1+(?___wmul)),w
	movwf	(___awdiv@dividend+1)
	movf	(0+(?___wmul)),w
	movwf	(___awdiv@dividend)
	fcall	___awdiv
	movf	(0+?___awdiv),w
	movwf	(??_twinkle_update+0)+0
	movf	(1+?___awdiv),w
	movwf	((??_twinkle_update+0)+0+1)
	movlw	low(05h)
	movwf	(___bmul@multiplicand)
	movf	(twinkle_update@i_369),w
	addwf	(twinkle_update@i_369),w
	addwf	(twinkle_update@i_369),w
	addlw	low(_stars|((0x0)<<8)+01h)&0ffh
	movwf	fsr0
	bcf	status, 7	;select IRP bank0
	movf	indf,w
	fcall	___bmul
	addwf	0+(??_twinkle_update+0)+0,w
	movwf	(twinkle_update@brightness)
	line	139
;effects.c: 139: } else {
	goto	l661
	line	141
	
l3337:	
;effects.c: 141: brightness = ((100 - stars[i].phase) * 5) + ((100 - stars[i].phase) * 3 / 10);
	movlw	0Ah
	movwf	(___awdiv@divisor)
	clrf	(___awdiv@divisor+1)
	movlw	064h
	movwf	(___wmul@multiplier)
	clrf	(___wmul@multiplier+1)
	movf	(twinkle_update@i_369),w
	addwf	(twinkle_update@i_369),w
	addwf	(twinkle_update@i_369),w
	addlw	low(_stars|((0x0)<<8)+01h)&0ffh
	movwf	fsr0
	movf	indf,w
	subwf	(___wmul@multiplier),f
	skipc
	decf	(___wmul@multiplier+1),f
	movlw	03h
	movwf	(___wmul@multiplicand)
	clrf	(___wmul@multiplicand+1)
	fcall	___wmul
	movf	(1+(?___wmul)),w
	movwf	(___awdiv@dividend+1)
	movf	(0+(?___wmul)),w
	movwf	(___awdiv@dividend)
	fcall	___awdiv
	movf	(0+?___awdiv),w
	movwf	(??_twinkle_update+0)+0
	movf	(1+?___awdiv),w
	movwf	((??_twinkle_update+0)+0+1)
	movlw	low(0FBh)
	movwf	(___bmul@multiplicand)
	movf	(twinkle_update@i_369),w
	addwf	(twinkle_update@i_369),w
	addwf	(twinkle_update@i_369),w
	addlw	low(_stars|((0x0)<<8)+01h)&0ffh
	movwf	fsr0
	bcf	status, 7	;select IRP bank0
	movf	indf,w
	fcall	___bmul
	addwf	0+(??_twinkle_update+0)+0,w
	addlw	0F4h
	movwf	(twinkle_update@brightness)
	line	142
	
l661:	
	line	145
;effects.c: 142: }
;effects.c: 145: unsigned char color = (stars[i].pos + i) % 3;
	movlw	03h
	movwf	(___awmod@divisor)
	clrf	(___awmod@divisor+1)
	movf	(twinkle_update@i_369),w
	addwf	(twinkle_update@i_369),w
	addwf	(twinkle_update@i_369),w
	addlw	low(_stars|((0x0)<<8))&0ffh
	movwf	fsr0
	bcf	status, 7	;select IRP bank0
	movf	indf,w
	addwf	(twinkle_update@i_369),w
	movwf	(___awmod@dividend)
	clrf	(___awmod@dividend)+1
	rlf	1+(___awmod@dividend),f
	
	fcall	___awmod
	movf	(0+(?___awmod)),w
	movwf	(twinkle_update@color)
	line	146
	
l3339:	
;effects.c: 146: if (color == 0) {
	movf	((twinkle_update@color)),w
	btfss	status,2
	goto	u1581
	goto	u1580
u1581:
	goto	l3343
u1580:
	line	147
	
l3341:	
;effects.c: 147: leds[stars[i].pos].r = brightness;
	movf	(twinkle_update@i_369),w
	addwf	(twinkle_update@i_369),w
	addwf	(twinkle_update@i_369),w
	addlw	low(_stars|((0x0)<<8))&0ffh
	movwf	fsr0
	bcf	status, 7	;select IRP bank0
	movf	indf,w
	addwf	indf,w
	addwf	indf,w
	addlw	low(_leds|((0x0)<<8))&0ffh
	movwf	fsr0
	movf	(twinkle_update@brightness),w
	movwf	indf
	line	148
;effects.c: 148: } else if (color == 1) {
	goto	l3349
	
l3343:	
		decf	((twinkle_update@color)),w
	btfss	status,2
	goto	u1591
	goto	u1590
u1591:
	goto	l3347
u1590:
	line	149
	
l3345:	
;effects.c: 149: leds[stars[i].pos].g = brightness;
	movf	(twinkle_update@i_369),w
	addwf	(twinkle_update@i_369),w
	addwf	(twinkle_update@i_369),w
	addlw	low(_stars|((0x0)<<8))&0ffh
	movwf	fsr0
	bcf	status, 7	;select IRP bank0
	movf	indf,w
	addwf	indf,w
	addwf	indf,w
	addlw	low(_leds|((0x0)<<8)+01h)&0ffh
	movwf	fsr0
	movf	(twinkle_update@brightness),w
	movwf	indf
	line	150
;effects.c: 150: } else {
	goto	l3349
	line	151
	
l3347:	
;effects.c: 151: leds[stars[i].pos].b = brightness;
	movf	(twinkle_update@i_369),w
	addwf	(twinkle_update@i_369),w
	addwf	(twinkle_update@i_369),w
	addlw	low(_stars|((0x0)<<8))&0ffh
	movwf	fsr0
	bcf	status, 7	;select IRP bank0
	movf	indf,w
	addwf	indf,w
	addwf	indf,w
	addlw	low(_leds|((0x0)<<8)+02h)&0ffh
	movwf	fsr0
	movf	(twinkle_update@brightness),w
	movwf	indf
	line	124
	
l3349:	
	incf	(twinkle_update@i_369),f
	
l3351:	
	movlw	low(08h)
	subwf	(twinkle_update@i_369),w
	skipc
	goto	u1601
	goto	u1600
u1601:
	goto	l3325
u1600:
	line	154
	
l654:	
	return
	opt stack 0
GLOBAL	__end_of_twinkle_update
	__end_of_twinkle_update:
	signat	_twinkle_update,89
	global	___awdiv

;; *************** function ___awdiv *****************
;; Defined at:
;;		line 6 in file "F:\Program Files\SCMCU_IDE_V2.00.16\data\sources\common\awdiv.c"
;; Parameters:    Size  Location     Type
;;  divisor         2    6[COMMON] int 
;;  dividend        2    8[COMMON] int 
;; Auto vars:     Size  Location     Type
;;  quotient        2   12[COMMON] int 
;;  sign            1   11[COMMON] unsigned char 
;;  counter         1   10[COMMON] unsigned char 
;; Return value:  Size  Location     Type
;;                  2    6[COMMON] int 
;; Registers used:
;;		wreg, status,2, status,0
;; Tracked objects:
;;		On entry : 100/0
;;		On exit  : 100/0
;;		Unchanged: 100/0
;; Data sizes:     COMMON   BANK0   BANK1
;;      Params:         4       0       0
;;      Locals:         4       0       0
;;      Temps:          0       0       0
;;      Totals:         8       0       0
;;Total ram usage:        8 bytes
;; Hardware stack levels used:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_twinkle_update
;; This function uses a non-reentrant model
;;
psect	text18,local,class=CODE,delta=2,merge=1,group=1
	file	"F:\Program Files\SCMCU_IDE_V2.00.16\data\sources\common\awdiv.c"
	line	6
global __ptext18
__ptext18:	;psect for function ___awdiv
psect	text18
	file	"F:\Program Files\SCMCU_IDE_V2.00.16\data\sources\common\awdiv.c"
	line	6
	global	__size_of___awdiv
	__size_of___awdiv	equ	__end_of___awdiv-___awdiv
	
___awdiv:	
;incstack = 0
	opt	stack 5
; Regs used in ___awdiv: [wreg+status,2+status,0]
	line	14
	
l3135:	
	clrf	(___awdiv@sign)
	line	15
	
l3137:	
	btfss	(___awdiv@divisor+1),7
	goto	u1331
	goto	u1330
u1331:
	goto	l3143
u1330:
	line	16
	
l3139:	
	comf	(___awdiv@divisor),f
	comf	(___awdiv@divisor+1),f
	incf	(___awdiv@divisor),f
	skipnz
	incf	(___awdiv@divisor+1),f
	line	17
	
l3141:	
	clrf	(___awdiv@sign)
	incf	(___awdiv@sign),f
	line	19
	
l3143:	
	btfss	(___awdiv@dividend+1),7
	goto	u1341
	goto	u1340
u1341:
	goto	l3149
u1340:
	line	20
	
l3145:	
	comf	(___awdiv@dividend),f
	comf	(___awdiv@dividend+1),f
	incf	(___awdiv@dividend),f
	skipnz
	incf	(___awdiv@dividend+1),f
	line	21
	
l3147:	
	movlw	low(01h)
	xorwf	(___awdiv@sign),f
	line	23
	
l3149:	
	clrf	(___awdiv@quotient)
	clrf	(___awdiv@quotient+1)
	line	24
	
l3151:	
	movf	((___awdiv@divisor)),w
iorwf	((___awdiv@divisor+1)),w
	btfsc	status,2
	goto	u1351
	goto	u1350
u1351:
	goto	l3171
u1350:
	line	25
	
l3153:	
	clrf	(___awdiv@counter)
	incf	(___awdiv@counter),f
	line	26
	goto	l3157
	line	27
	
l3155:	
	clrc
	rlf	(___awdiv@divisor),f
	rlf	(___awdiv@divisor+1),f
	line	28
	incf	(___awdiv@counter),f
	line	26
	
l3157:	
	btfss	(___awdiv@divisor+1),(15)&7
	goto	u1361
	goto	u1360
u1361:
	goto	l3155
u1360:
	line	31
	
l3159:	
	clrc
	rlf	(___awdiv@quotient),f
	rlf	(___awdiv@quotient+1),f
	line	32
	
l3161:	
	movf	(___awdiv@divisor+1),w
	subwf	(___awdiv@dividend+1),w
	skipz
	goto	u1375
	movf	(___awdiv@divisor),w
	subwf	(___awdiv@dividend),w
u1375:
	skipc
	goto	u1371
	goto	u1370
u1371:
	goto	l3167
u1370:
	line	33
	
l3163:	
	movf	(___awdiv@divisor),w
	subwf	(___awdiv@dividend),f
	movf	(___awdiv@divisor+1),w
	skipc
	decf	(___awdiv@dividend+1),f
	subwf	(___awdiv@dividend+1),f
	line	34
	
l3165:	
	bsf	(___awdiv@quotient)+(0/8),(0)&7
	line	36
	
l3167:	
	clrc
	rrf	(___awdiv@divisor+1),f
	rrf	(___awdiv@divisor),f
	line	37
	
l3169:	
	decfsz	(___awdiv@counter),f
	goto	u1381
	goto	u1380
u1381:
	goto	l3159
u1380:
	line	39
	
l3171:	
	movf	((___awdiv@sign)),w
	btfsc	status,2
	goto	u1391
	goto	u1390
u1391:
	goto	l3175
u1390:
	line	40
	
l3173:	
	comf	(___awdiv@quotient),f
	comf	(___awdiv@quotient+1),f
	incf	(___awdiv@quotient),f
	skipnz
	incf	(___awdiv@quotient+1),f
	line	41
	
l3175:	
	movf	(___awdiv@quotient+1),w
	movwf	(?___awdiv+1)
	movf	(___awdiv@quotient),w
	movwf	(?___awdiv)
	line	42
	
l1645:	
	return
	opt stack 0
GLOBAL	__end_of___awdiv
	__end_of___awdiv:
	signat	___awdiv,8314
	global	_random_value

;; *************** function _random_value *****************
;; Defined at:
;;		line 221 in file "H:\8bit-RGB\effects.c"
;; Parameters:    Size  Location     Type
;;  seed            1    wreg     unsigned char 
;; Auto vars:     Size  Location     Type
;;  seed            1    8[COMMON] unsigned char 
;; Return value:  Size  Location     Type
;;                  1    wreg      unsigned char 
;; Registers used:
;;		wreg, status,2, status,0, pclath, cstack
;; Tracked objects:
;;		On entry : 100/0
;;		On exit  : 100/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1
;;      Params:         0       0       0
;;      Locals:         1       0       0
;;      Temps:          2       0       0
;;      Totals:         3       0       0
;;Total ram usage:        3 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    1
;; This function calls:
;;		___wmul
;; This function is called by:
;;		_expand_update
;; This function uses a non-reentrant model
;;
psect	text19,local,class=CODE,delta=2,merge=1,group=0
	file	"H:\8bit-RGB\effects.c"
	line	221
global __ptext19
__ptext19:	;psect for function _random_value
psect	text19
	file	"H:\8bit-RGB\effects.c"
	line	221
	global	__size_of_random_value
	__size_of_random_value	equ	__end_of_random_value-_random_value
	
_random_value:	
;incstack = 0
	opt	stack 4
; Regs used in _random_value: [wreg+status,2+status,0+pclath+cstack]
;random_value@seed stored from wreg
	movwf	(random_value@seed)
	line	223
	
l3119:	
;effects.c: 222: static unsigned short rand_state = 12345;
;effects.c: 223: rand_state = rand_state * 1103515245 + seed * 257;
	movf	(random_value@seed),w
	movwf	(___wmul@multiplier)
	clrf	(___wmul@multiplier+1)
	movlw	01h
	movwf	(___wmul@multiplicand)
	movlw	01h
	movwf	((___wmul@multiplicand))+1
	fcall	___wmul
	movf	(0+?___wmul),w
	movwf	(??_random_value+0)+0
	movf	(1+?___wmul),w
	movwf	((??_random_value+0)+0+1)
	movf	(random_value@rand_state+1),w
	movwf	(___wmul@multiplier+1)
	movf	(random_value@rand_state),w
	movwf	(___wmul@multiplier)
	movlw	06Dh
	movwf	(___wmul@multiplicand)
	movlw	04Eh
	movwf	((___wmul@multiplicand))+1
	fcall	___wmul
	movf	(0+(?___wmul)),w
	addwf	0+(??_random_value+0)+0,w
	movwf	(random_value@rand_state)
	movf	(1+(?___wmul)),w
	skipnc
	incf	(1+(?___wmul)),w
	addwf	1+(??_random_value+0)+0,w
	movwf	1+(random_value@rand_state)
	line	224
	
l3121:	
;effects.c: 224: return (unsigned char)(rand_state >> 8);
	movf	0+(random_value@rand_state)+01h,w
	line	225
	
l710:	
	return
	opt stack 0
GLOBAL	__end_of_random_value
	__end_of_random_value:
	signat	_random_value,4217
	global	___awmod

;; *************** function ___awmod *****************
;; Defined at:
;;		line 6 in file "F:\Program Files\SCMCU_IDE_V2.00.16\data\sources\common\awmod.c"
;; Parameters:    Size  Location     Type
;;  divisor         2    0[COMMON] int 
;;  dividend        2    2[COMMON] int 
;; Auto vars:     Size  Location     Type
;;  sign            1    5[COMMON] unsigned char 
;;  counter         1    4[COMMON] unsigned char 
;; Return value:  Size  Location     Type
;;                  2    0[COMMON] int 
;; Registers used:
;;		wreg, status,2, status,0
;; Tracked objects:
;;		On entry : 100/0
;;		On exit  : 100/0
;;		Unchanged: 100/0
;; Data sizes:     COMMON   BANK0   BANK1
;;      Params:         4       0       0
;;      Locals:         2       0       0
;;      Temps:          0       0       0
;;      Totals:         6       0       0
;;Total ram usage:        6 bytes
;; Hardware stack levels used:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_breath_update
;;		_twinkle_update
;;		_chase_update
;;		_expand_update
;;		_marquee_update
;;		_ws2812_update_RGB
;;		_key_scan
;; This function uses a non-reentrant model
;;
psect	text20,local,class=CODE,delta=2,merge=1,group=1
	file	"F:\Program Files\SCMCU_IDE_V2.00.16\data\sources\common\awmod.c"
	line	6
global __ptext20
__ptext20:	;psect for function ___awmod
psect	text20
	file	"F:\Program Files\SCMCU_IDE_V2.00.16\data\sources\common\awmod.c"
	line	6
	global	__size_of___awmod
	__size_of___awmod	equ	__end_of___awmod-___awmod
	
___awmod:	
;incstack = 0
	opt	stack 6
; Regs used in ___awmod: [wreg+status,2+status,0]
	line	13
	
l3179:	
	clrf	(___awmod@sign)
	line	14
	
l3181:	
	btfss	(___awmod@dividend+1),7
	goto	u1401
	goto	u1400
u1401:
	goto	l3187
u1400:
	line	15
	
l3183:	
	comf	(___awmod@dividend),f
	comf	(___awmod@dividend+1),f
	incf	(___awmod@dividend),f
	skipnz
	incf	(___awmod@dividend+1),f
	line	16
	
l3185:	
	clrf	(___awmod@sign)
	incf	(___awmod@sign),f
	line	18
	
l3187:	
	btfss	(___awmod@divisor+1),7
	goto	u1411
	goto	u1410
u1411:
	goto	l3191
u1410:
	line	19
	
l3189:	
	comf	(___awmod@divisor),f
	comf	(___awmod@divisor+1),f
	incf	(___awmod@divisor),f
	skipnz
	incf	(___awmod@divisor+1),f
	line	20
	
l3191:	
	movf	((___awmod@divisor)),w
iorwf	((___awmod@divisor+1)),w
	btfsc	status,2
	goto	u1421
	goto	u1420
u1421:
	goto	l3207
u1420:
	line	21
	
l3193:	
	clrf	(___awmod@counter)
	incf	(___awmod@counter),f
	line	22
	goto	l3197
	line	23
	
l3195:	
	clrc
	rlf	(___awmod@divisor),f
	rlf	(___awmod@divisor+1),f
	line	24
	incf	(___awmod@counter),f
	line	22
	
l3197:	
	btfss	(___awmod@divisor+1),(15)&7
	goto	u1431
	goto	u1430
u1431:
	goto	l3195
u1430:
	line	27
	
l3199:	
	movf	(___awmod@divisor+1),w
	subwf	(___awmod@dividend+1),w
	skipz
	goto	u1445
	movf	(___awmod@divisor),w
	subwf	(___awmod@dividend),w
u1445:
	skipc
	goto	u1441
	goto	u1440
u1441:
	goto	l3203
u1440:
	line	28
	
l3201:	
	movf	(___awmod@divisor),w
	subwf	(___awmod@dividend),f
	movf	(___awmod@divisor+1),w
	skipc
	decf	(___awmod@dividend+1),f
	subwf	(___awmod@dividend+1),f
	line	29
	
l3203:	
	clrc
	rrf	(___awmod@divisor+1),f
	rrf	(___awmod@divisor),f
	line	30
	
l3205:	
	decfsz	(___awmod@counter),f
	goto	u1451
	goto	u1450
u1451:
	goto	l3199
u1450:
	line	32
	
l3207:	
	movf	((___awmod@sign)),w
	btfsc	status,2
	goto	u1461
	goto	u1460
u1461:
	goto	l3211
u1460:
	line	33
	
l3209:	
	comf	(___awmod@dividend),f
	comf	(___awmod@dividend+1),f
	incf	(___awmod@dividend),f
	skipnz
	incf	(___awmod@dividend+1),f
	line	34
	
l3211:	
	movf	(___awmod@dividend+1),w
	movwf	(?___awmod+1)
	movf	(___awmod@dividend),w
	movwf	(?___awmod)
	line	35
	
l1658:	
	return
	opt stack 0
GLOBAL	__end_of___awmod
	__end_of___awmod:
	signat	___awmod,8314
	global	_effect_init

;; *************** function _effect_init *****************
;; Defined at:
;;		line 464 in file "H:\8bit-RGB\effects.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;                  1    wreg      void 
;; Registers used:
;;		wreg, fsr0l, fsr0h, status,2, status,0, pclath, cstack
;; Tracked objects:
;;		On entry : 100/0
;;		On exit  : 100/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1
;;      Params:         0       0       0
;;      Locals:         0       0       0
;;      Temps:          0       0       0
;;      Totals:         0       0       0
;;Total ram usage:        0 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    2
;; This function calls:
;;		_breath_init
;;		_chase_init
;;		_expand_init
;;		_marquee_init
;;		_police_init
;;		_stack_init
;;		_twinkle_init
;; This function is called by:
;;		_main
;; This function uses a non-reentrant model
;;
psect	text21,local,class=CODE,delta=2,merge=1,group=0
	file	"H:\8bit-RGB\effects.c"
	line	464
global __ptext21
__ptext21:	;psect for function _effect_init
psect	text21
	file	"H:\8bit-RGB\effects.c"
	line	464
	global	__size_of_effect_init
	__size_of_effect_init	equ	__end_of_effect_init-_effect_init
	
_effect_init:	
;incstack = 0
	opt	stack 5
; Regs used in _effect_init: [wreg-fsr0h+status,2+status,0+pclath+cstack]
	line	466
	
l3725:	
;effects.c: 466: if (current_effect < EFFECT_COUNT) {
	movlw	low(07h)
	subwf	(_current_effect),w	;volatile
	skipnc
	goto	u1951
	goto	u1950
u1951:
	goto	l810
u1950:
	line	467
	
l3727:	
;effects.c: 467: effects[current_effect].init();
	clrc
	rlf	(_current_effect),w	;volatile
	addlw	low((((_effects)-__stringbase)|8000h))
	movwf	fsr0
	fcall	stringdir
	fcall	fptable
	line	469
	
l810:	
	return
	opt stack 0
GLOBAL	__end_of_effect_init
	__end_of_effect_init:
	signat	_effect_init,89
	global	_twinkle_init
	global	_breath_init
	global	_chase_init
	global	_expand_init
	global	_marquee_init
	global	_stack_init
	global	_police_init

;; *************** function _police_init *****************
;; Defined at:
;;		line 422 in file "H:\8bit-RGB\effects.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;  i               1    0[COMMON] unsigned char 
;; Return value:  Size  Location     Type
;;                  1    wreg      void 
;; Registers used:
;;		wreg, fsr0l, fsr0h, status,2, status,0
;; Tracked objects:
;;		On entry : 100/0
;;		On exit  : 900/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1
;;      Params:         0       0       0
;;      Locals:         1       0       0
;;      Temps:          0       0       0
;;      Totals:         1       0       0
;;Total ram usage:        1 bytes
;; Hardware stack levels used:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_effect_execute
;;		_effect_init
;; This function uses a non-reentrant model
;;
psect	text22,local,class=CODE,delta=2,merge=1,group=0
	line	422
global __ptext22
__ptext22:	;psect for function _police_init
psect	text22
	file	"H:\8bit-RGB\effects.c"
	line	422
	global	__size_of_police_init
	__size_of_police_init	equ	__end_of_police_init-_police_init
	
_police_init:	
;incstack = 0
	opt	stack 5
; Regs used in _police_init: [wreg-fsr0h+status,2+status,0]
	line	423
	
l3073:	
;effects.c: 423: police_state = 0;
	clrf	(_police_state)
	line	424
;effects.c: 424: police_counter = 0;
	clrf	(_police_counter)
	line	425
;effects.c: 425: for (unsigned char i = 0; i < 24; i++) {
	clrf	(police_init@i)
	line	426
	
l3079:	
;effects.c: 426: leds[i].r = 0;
	movf	(police_init@i),w
	addwf	(police_init@i),w
	addwf	(police_init@i),w
	addlw	low(_leds|((0x0)<<8))&0ffh
	movwf	fsr0
	bcf	status, 7	;select IRP bank1
	clrf	indf
	line	427
;effects.c: 427: leds[i].g = 0;
	movf	(police_init@i),w
	addwf	(police_init@i),w
	addwf	(police_init@i),w
	addlw	low(_leds|((0x0)<<8)+01h)&0ffh
	movwf	fsr0
	clrf	indf
	line	428
;effects.c: 428: leds[i].b = 0;
	movf	(police_init@i),w
	addwf	(police_init@i),w
	addwf	(police_init@i),w
	addlw	low(_leds|((0x0)<<8)+02h)&0ffh
	movwf	fsr0
	clrf	indf
	line	425
	
l3081:	
	incf	(police_init@i),f
	
l3083:	
	movlw	low(018h)
	subwf	(police_init@i),w
	skipc
	goto	u1221
	goto	u1220
u1221:
	goto	l3079
u1220:
	line	430
	
l796:	
	return
	opt stack 0
GLOBAL	__end_of_police_init
	__end_of_police_init:
	signat	_police_init,89

;; *************** function _stack_init *****************
;; Defined at:
;;		line 359 in file "H:\8bit-RGB\effects.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;  i               1    0[COMMON] unsigned char 
;; Return value:  Size  Location     Type
;;                  1    wreg      void 
;; Registers used:
;;		wreg, fsr0l, fsr0h, status,2, status,0
;; Tracked objects:
;;		On entry : 100/0
;;		On exit  : 900/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1
;;      Params:         0       0       0
;;      Locals:         1       0       0
;;      Temps:          0       0       0
;;      Totals:         1       0       0
;;Total ram usage:        1 bytes
;; Hardware stack levels used:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_stack_update
;;		_effect_execute
;;		_effect_init
;; This function uses a non-reentrant model
;;
psect	text23,local,class=CODE,delta=2,merge=1,group=0
	line	359
global __ptext23
__ptext23:	;psect for function _stack_init
psect	text23
	file	"H:\8bit-RGB\effects.c"
	line	359
	global	__size_of_stack_init
	__size_of_stack_init	equ	__end_of_stack_init-_stack_init
	
_stack_init:	
;incstack = 0
	opt	stack 5
; Regs used in _stack_init: [wreg-fsr0h+status,2+status,0]
	line	360
	
l3055:	
;effects.c: 360: stack_runner = 0;
	clrf	(_stack_runner)
	line	361
	
l3057:	
;effects.c: 361: stack_target = 23;
	movlw	low(017h)
	movwf	(_stack_target)
	line	362
	
l3059:	
;effects.c: 362: stack_lit_count = 0;
	clrf	(_stack_lit_count)
	line	363
	
l3061:	
;effects.c: 363: stack_delay = 0;
	clrf	(_stack_delay)
	line	364
	
l3063:	
;effects.c: 364: for (unsigned char i = 0; i < 24; i++) {
	clrf	(stack_init@i)
	line	365
	
l3067:	
;effects.c: 365: leds[i].r = 0;
	movf	(stack_init@i),w
	addwf	(stack_init@i),w
	addwf	(stack_init@i),w
	addlw	low(_leds|((0x0)<<8))&0ffh
	movwf	fsr0
	bcf	status, 7	;select IRP bank1
	clrf	indf
	line	366
;effects.c: 366: leds[i].g = 0;
	movf	(stack_init@i),w
	addwf	(stack_init@i),w
	addwf	(stack_init@i),w
	addlw	low(_leds|((0x0)<<8)+01h)&0ffh
	movwf	fsr0
	clrf	indf
	line	367
;effects.c: 367: leds[i].b = 0;
	movf	(stack_init@i),w
	addwf	(stack_init@i),w
	addwf	(stack_init@i),w
	addlw	low(_leds|((0x0)<<8)+02h)&0ffh
	movwf	fsr0
	clrf	indf
	line	364
	
l3069:	
	incf	(stack_init@i),f
	
l3071:	
	movlw	low(018h)
	subwf	(stack_init@i),w
	skipc
	goto	u1211
	goto	u1210
u1211:
	goto	l3067
u1210:
	line	369
	
l773:	
	return
	opt stack 0
GLOBAL	__end_of_stack_init
	__end_of_stack_init:
	signat	_stack_init,89

;; *************** function _marquee_init *****************
;; Defined at:
;;		line 293 in file "H:\8bit-RGB\effects.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;  i               1    1[COMMON] unsigned char 
;;  i               1    0[COMMON] unsigned char 
;; Return value:  Size  Location     Type
;;                  1    wreg      void 
;; Registers used:
;;		wreg, fsr0l, fsr0h, status,2, status,0
;; Tracked objects:
;;		On entry : 100/0
;;		On exit  : 900/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1
;;      Params:         0       0       0
;;      Locals:         2       0       0
;;      Temps:          0       0       0
;;      Totals:         2       0       0
;;Total ram usage:        2 bytes
;; Hardware stack levels used:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_effect_execute
;;		_effect_init
;; This function uses a non-reentrant model
;;
psect	text24,local,class=CODE,delta=2,merge=1,group=0
	line	293
global __ptext24
__ptext24:	;psect for function _marquee_init
psect	text24
	file	"H:\8bit-RGB\effects.c"
	line	293
	global	__size_of_marquee_init
	__size_of_marquee_init	equ	__end_of_marquee_init-_marquee_init
	
_marquee_init:	
;incstack = 0
	opt	stack 5
; Regs used in _marquee_init: [wreg-fsr0h+status,2+status,0]
	line	294
	
l3031:	
;effects.c: 294: marquee_pos = 0;
	clrf	(_marquee_pos)
	line	296
;effects.c: 296: for (unsigned char i = 0; i < 24; i++) {
	clrf	(marquee_init@i)
	line	297
	
l3037:	
;effects.c: 297: leds[i].r = 0;
	movf	(marquee_init@i),w
	addwf	(marquee_init@i),w
	addwf	(marquee_init@i),w
	addlw	low(_leds|((0x0)<<8))&0ffh
	movwf	fsr0
	bcf	status, 7	;select IRP bank1
	clrf	indf
	line	298
;effects.c: 298: leds[i].g = 0;
	movf	(marquee_init@i),w
	addwf	(marquee_init@i),w
	addwf	(marquee_init@i),w
	addlw	low(_leds|((0x0)<<8)+01h)&0ffh
	movwf	fsr0
	clrf	indf
	line	299
;effects.c: 299: leds[i].b = 0;
	movf	(marquee_init@i),w
	addwf	(marquee_init@i),w
	addwf	(marquee_init@i),w
	addlw	low(_leds|((0x0)<<8)+02h)&0ffh
	movwf	fsr0
	clrf	indf
	line	296
	
l3039:	
	incf	(marquee_init@i),f
	
l3041:	
	movlw	low(018h)
	subwf	(marquee_init@i),w
	skipc
	goto	u1191
	goto	u1190
u1191:
	goto	l3037
u1190:
	line	301
	
l3043:	
;effects.c: 300: }
;effects.c: 301: for (unsigned char i = 0; i < 8; i++) {
	clrf	(marquee_init@i_407)
	line	302
	
l3049:	
;effects.c: 302: leds[i].r = 255;
	movf	(marquee_init@i_407),w
	addwf	(marquee_init@i_407),w
	addwf	(marquee_init@i_407),w
	addlw	low(_leds|((0x0)<<8))&0ffh
	movwf	fsr0
	movlw	low(0FFh)
	movwf	indf
	line	303
;effects.c: 303: leds[i].g = 0;
	movf	(marquee_init@i_407),w
	addwf	(marquee_init@i_407),w
	addwf	(marquee_init@i_407),w
	addlw	low(_leds|((0x0)<<8)+01h)&0ffh
	movwf	fsr0
	clrf	indf
	line	304
;effects.c: 304: leds[i].b = 0;
	movf	(marquee_init@i_407),w
	addwf	(marquee_init@i_407),w
	addwf	(marquee_init@i_407),w
	addlw	low(_leds|((0x0)<<8)+02h)&0ffh
	movwf	fsr0
	clrf	indf
	line	301
	
l3051:	
	incf	(marquee_init@i_407),f
	
l3053:	
	movlw	low(08h)
	subwf	(marquee_init@i_407),w
	skipc
	goto	u1201
	goto	u1200
u1201:
	goto	l3049
u1200:
	line	306
	
l739:	
	return
	opt stack 0
GLOBAL	__end_of_marquee_init
	__end_of_marquee_init:
	signat	_marquee_init,89

;; *************** function _expand_init *****************
;; Defined at:
;;		line 227 in file "H:\8bit-RGB\effects.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;  i               1    0[COMMON] unsigned char 
;; Return value:  Size  Location     Type
;;                  1    wreg      void 
;; Registers used:
;;		wreg, fsr0l, fsr0h, status,2, status,0
;; Tracked objects:
;;		On entry : 100/0
;;		On exit  : 900/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1
;;      Params:         0       0       0
;;      Locals:         1       0       0
;;      Temps:          0       0       0
;;      Totals:         1       0       0
;;Total ram usage:        1 bytes
;; Hardware stack levels used:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_effect_execute
;;		_effect_init
;; This function uses a non-reentrant model
;;
psect	text25,local,class=CODE,delta=2,merge=1,group=0
	line	227
global __ptext25
__ptext25:	;psect for function _expand_init
psect	text25
	file	"H:\8bit-RGB\effects.c"
	line	227
	global	__size_of_expand_init
	__size_of_expand_init	equ	__end_of_expand_init-_expand_init
	
_expand_init:	
;incstack = 0
	opt	stack 5
; Regs used in _expand_init: [wreg-fsr0h+status,2+status,0]
	line	228
	
l3009:	
;effects.c: 228: expand_size = 0;
	clrf	(_expand_size)
	line	229
	
l3011:	
;effects.c: 229: expand_dir = 1;
	clrf	(_expand_dir)
	incf	(_expand_dir),f
	line	230
	
l3013:	
;effects.c: 230: expand_r = 255;
	movlw	low(0FFh)
	movwf	(_expand_r)
	line	231
	
l3015:	
;effects.c: 231: expand_g = 0;
	clrf	(_expand_g)
	line	232
	
l3017:	
;effects.c: 232: expand_b = 0;
	clrf	(_expand_b)
	line	233
	
l3019:	
;effects.c: 233: expand_seed = 1;
	clrf	(_expand_seed)
	incf	(_expand_seed),f
	line	234
	
l3021:	
;effects.c: 234: for (unsigned char i = 0; i < 24; i++) {
	clrf	(expand_init@i)
	line	235
	
l3025:	
;effects.c: 235: leds[i].r = 0;
	movf	(expand_init@i),w
	addwf	(expand_init@i),w
	addwf	(expand_init@i),w
	addlw	low(_leds|((0x0)<<8))&0ffh
	movwf	fsr0
	bcf	status, 7	;select IRP bank1
	clrf	indf
	line	236
;effects.c: 236: leds[i].g = 0;
	movf	(expand_init@i),w
	addwf	(expand_init@i),w
	addwf	(expand_init@i),w
	addlw	low(_leds|((0x0)<<8)+01h)&0ffh
	movwf	fsr0
	clrf	indf
	line	237
;effects.c: 237: leds[i].b = 0;
	movf	(expand_init@i),w
	addwf	(expand_init@i),w
	addwf	(expand_init@i),w
	addlw	low(_leds|((0x0)<<8)+02h)&0ffh
	movwf	fsr0
	clrf	indf
	line	234
	
l3027:	
	incf	(expand_init@i),f
	
l3029:	
	movlw	low(018h)
	subwf	(expand_init@i),w
	skipc
	goto	u1181
	goto	u1180
u1181:
	goto	l3025
u1180:
	line	239
	
l715:	
	return
	opt stack 0
GLOBAL	__end_of_expand_init
	__end_of_expand_init:
	signat	_expand_init,89

;; *************** function _chase_init *****************
;; Defined at:
;;		line 161 in file "H:\8bit-RGB\effects.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;  i               1    0[COMMON] unsigned char 
;; Return value:  Size  Location     Type
;;                  1    wreg      void 
;; Registers used:
;;		wreg, fsr0l, fsr0h, status,2, status,0
;; Tracked objects:
;;		On entry : 100/0
;;		On exit  : 900/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1
;;      Params:         0       0       0
;;      Locals:         1       0       0
;;      Temps:          0       0       0
;;      Totals:         1       0       0
;;Total ram usage:        1 bytes
;; Hardware stack levels used:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_effect_execute
;;		_effect_init
;; This function uses a non-reentrant model
;;
psect	text26,local,class=CODE,delta=2,merge=1,group=0
	line	161
global __ptext26
__ptext26:	;psect for function _chase_init
psect	text26
	file	"H:\8bit-RGB\effects.c"
	line	161
	global	__size_of_chase_init
	__size_of_chase_init	equ	__end_of_chase_init-_chase_init
	
_chase_init:	
;incstack = 0
	opt	stack 5
; Regs used in _chase_init: [wreg-fsr0h+status,2+status,0]
	line	162
	
l2997:	
;effects.c: 162: chase_pos = 0;
	clrf	(_chase_pos)
	line	163
;effects.c: 163: chase_color_idx = 0;
	clrf	(_chase_color_idx)
	line	165
;effects.c: 165: for (unsigned char i = 0; i < 24; i++) {
	clrf	(chase_init@i)
	line	166
	
l3003:	
;effects.c: 166: leds[i].r = 0;
	movf	(chase_init@i),w
	addwf	(chase_init@i),w
	addwf	(chase_init@i),w
	addlw	low(_leds|((0x0)<<8))&0ffh
	movwf	fsr0
	bcf	status, 7	;select IRP bank1
	clrf	indf
	line	167
;effects.c: 167: leds[i].g = 0;
	movf	(chase_init@i),w
	addwf	(chase_init@i),w
	addwf	(chase_init@i),w
	addlw	low(_leds|((0x0)<<8)+01h)&0ffh
	movwf	fsr0
	clrf	indf
	line	168
;effects.c: 168: leds[i].b = 0;
	movf	(chase_init@i),w
	addwf	(chase_init@i),w
	addwf	(chase_init@i),w
	addlw	low(_leds|((0x0)<<8)+02h)&0ffh
	movwf	fsr0
	clrf	indf
	line	165
	
l3005:	
	incf	(chase_init@i),f
	
l3007:	
	movlw	low(018h)
	subwf	(chase_init@i),w
	skipc
	goto	u1171
	goto	u1170
u1171:
	goto	l3003
u1170:
	line	170
	
l674:	
	return
	opt stack 0
GLOBAL	__end_of_chase_init
	__end_of_chase_init:
	signat	_chase_init,89

;; *************** function _breath_init *****************
;; Defined at:
;;		line 16 in file "H:\8bit-RGB\effects.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;                  1    wreg      void 
;; Registers used:
;;		wreg, status,2
;; Tracked objects:
;;		On entry : 100/0
;;		On exit  : 100/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1
;;      Params:         0       0       0
;;      Locals:         0       0       0
;;      Temps:          0       0       0
;;      Totals:         0       0       0
;;Total ram usage:        0 bytes
;; Hardware stack levels used:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_effect_execute
;;		_effect_init
;; This function uses a non-reentrant model
;;
psect	text27,local,class=CODE,delta=2,merge=1,group=0
	line	16
global __ptext27
__ptext27:	;psect for function _breath_init
psect	text27
	file	"H:\8bit-RGB\effects.c"
	line	16
	global	__size_of_breath_init
	__size_of_breath_init	equ	__end_of_breath_init-_breath_init
	
_breath_init:	
;incstack = 0
	opt	stack 5
; Regs used in _breath_init: [wreg+status,2]
	line	17
	
l2963:	
;effects.c: 17: breath_val = 25;
	movlw	low(019h)
	movwf	(_breath_val)
	line	18
	
l2965:	
;effects.c: 18: breath_dir = 1;
	clrf	(_breath_dir)
	incf	(_breath_dir),f
	line	19
	
l2967:	
;effects.c: 19: breath_color = 0;
	clrf	(_breath_color)
	line	20
	
l2969:	
;effects.c: 20: breath_transition = 0;
	clrf	(_breath_transition)
	line	21
	
l615:	
	return
	opt stack 0
GLOBAL	__end_of_breath_init
	__end_of_breath_init:
	signat	_breath_init,89

;; *************** function _twinkle_init *****************
;; Defined at:
;;		line 94 in file "H:\8bit-RGB\effects.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;  i               1   12[COMMON] unsigned char 
;;  i               1   11[COMMON] unsigned char 
;; Return value:  Size  Location     Type
;;                  1    wreg      void 
;; Registers used:
;;		wreg, fsr0l, fsr0h, status,2, status,0, pclath, cstack
;; Tracked objects:
;;		On entry : 100/0
;;		On exit  : 900/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1
;;      Params:         0       0       0
;;      Locals:         2       0       0
;;      Temps:          0       0       0
;;      Totals:         2       0       0
;;Total ram usage:        2 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    1
;; This function calls:
;;		___bmul
;;		___lwmod
;;		___wmul
;; This function is called by:
;;		_effect_execute
;;		_effect_init
;; This function uses a non-reentrant model
;;
psect	text28,local,class=CODE,delta=2,merge=1,group=0
	line	94
global __ptext28
__ptext28:	;psect for function _twinkle_init
psect	text28
	file	"H:\8bit-RGB\effects.c"
	line	94
	global	__size_of_twinkle_init
	__size_of_twinkle_init	equ	__end_of_twinkle_init-_twinkle_init
	
_twinkle_init:	
;incstack = 0
	opt	stack 4
; Regs used in _twinkle_init: [wreg-fsr0h+status,2+status,0+pclath+cstack]
	line	96
	
l2971:	
;effects.c: 96: for (unsigned char i = 0; i < 24; i++) {
	clrf	(twinkle_init@i)
	line	97
	
l2977:	
;effects.c: 97: leds[i].r = 0;
	movf	(twinkle_init@i),w
	addwf	(twinkle_init@i),w
	addwf	(twinkle_init@i),w
	addlw	low(_leds|((0x0)<<8))&0ffh
	movwf	fsr0
	bcf	status, 7	;select IRP bank1
	clrf	indf
	line	98
;effects.c: 98: leds[i].g = 0;
	movf	(twinkle_init@i),w
	addwf	(twinkle_init@i),w
	addwf	(twinkle_init@i),w
	addlw	low(_leds|((0x0)<<8)+01h)&0ffh
	movwf	fsr0
	clrf	indf
	line	99
;effects.c: 99: leds[i].b = 0;
	movf	(twinkle_init@i),w
	addwf	(twinkle_init@i),w
	addwf	(twinkle_init@i),w
	addlw	low(_leds|((0x0)<<8)+02h)&0ffh
	movwf	fsr0
	clrf	indf
	line	96
	
l2979:	
	incf	(twinkle_init@i),f
	
l2981:	
	movlw	low(018h)
	subwf	(twinkle_init@i),w
	skipc
	goto	u1151
	goto	u1150
u1151:
	goto	l2977
u1150:
	line	102
	
l2983:	
;effects.c: 100: }
;effects.c: 102: for (unsigned char i = 0; i < 8; i++) {
	clrf	(twinkle_init@i_363)
	line	103
	
l2989:	
;effects.c: 103: stars[i].pos = (system_tick_ms + i * 29) % 24;
	movf	(twinkle_init@i_363),w
	addwf	(twinkle_init@i_363),w
	addwf	(twinkle_init@i_363),w
	addlw	low(_stars|((0x0)<<8))&0ffh
	movwf	fsr0
	movlw	018h
	movwf	(___lwmod@divisor)
	clrf	(___lwmod@divisor+1)
	movf	(twinkle_init@i_363),w
	movwf	(___wmul@multiplier)
	clrf	(___wmul@multiplier+1)
	movlw	01Dh
	movwf	(___wmul@multiplicand)
	clrf	(___wmul@multiplicand+1)
	fcall	___wmul
	movf	(_system_tick_ms),w	;volatile
	addwf	(0+(?___wmul)),w
	movwf	(___lwmod@dividend)
	movf	(_system_tick_ms+1),w	;volatile
	skipnc
	incf	(_system_tick_ms+1),w	;volatile
	addwf	(1+(?___wmul)),w
	movwf	1+(___lwmod@dividend)
	fcall	___lwmod
	movf	(0+(?___lwmod)),w
	bcf	status, 7	;select IRP bank0
	movwf	indf
	line	104
;effects.c: 104: stars[i].phase = (system_tick_ms + i * 17) % 100;
	movf	(twinkle_init@i_363),w
	addwf	(twinkle_init@i_363),w
	addwf	(twinkle_init@i_363),w
	addlw	low(_stars|((0x0)<<8)+01h)&0ffh
	movwf	fsr0
	movlw	064h
	movwf	(___lwmod@divisor)
	clrf	(___lwmod@divisor+1)
	movf	(twinkle_init@i_363),w
	movwf	(___wmul@multiplier)
	clrf	(___wmul@multiplier+1)
	movlw	011h
	movwf	(___wmul@multiplicand)
	clrf	(___wmul@multiplicand+1)
	fcall	___wmul
	movf	(_system_tick_ms),w	;volatile
	addwf	(0+(?___wmul)),w
	movwf	(___lwmod@dividend)
	movf	(_system_tick_ms+1),w	;volatile
	skipnc
	incf	(_system_tick_ms+1),w	;volatile
	addwf	(1+(?___wmul)),w
	movwf	1+(___lwmod@dividend)
	fcall	___lwmod
	movf	(0+(?___lwmod)),w
	bcf	status, 7	;select IRP bank0
	movwf	indf
	line	105
;effects.c: 105: stars[i].speed = 2 + ((system_tick_ms + i * 11) % 4);
	movf	(twinkle_init@i_363),w
	addwf	(twinkle_init@i_363),w
	addwf	(twinkle_init@i_363),w
	addlw	low(_stars|((0x0)<<8)+02h)&0ffh
	movwf	fsr0
	movlw	low(0Bh)
	movwf	(___bmul@multiplicand)
	movf	(twinkle_init@i_363),w
	fcall	___bmul
	addwf	(_system_tick_ms),w	;volatile
	andlw	03h
	addlw	02h
	bcf	status, 7	;select IRP bank0
	movwf	indf
	line	102
	
l2991:	
	incf	(twinkle_init@i_363),f
	
l2993:	
	movlw	low(08h)
	subwf	(twinkle_init@i_363),w
	skipc
	goto	u1161
	goto	u1160
u1161:
	goto	l2989
u1160:
	line	107
	
l2995:	
;effects.c: 106: }
;effects.c: 107: twinkle_counter = 0;
	clrf	(_twinkle_counter)
	line	108
	
l650:	
	return
	opt stack 0
GLOBAL	__end_of_twinkle_init
	__end_of_twinkle_init:
	signat	_twinkle_init,89
	global	___wmul

;; *************** function ___wmul *****************
;; Defined at:
;;		line 15 in file "F:\Program Files\SCMCU_IDE_V2.00.16\data\sources\common\Umul16.c"
;; Parameters:    Size  Location     Type
;;  multiplier      2    0[COMMON] unsigned int 
;;  multiplicand    2    2[COMMON] unsigned int 
;; Auto vars:     Size  Location     Type
;;  product         2    4[COMMON] unsigned int 
;; Return value:  Size  Location     Type
;;                  2    0[COMMON] unsigned int 
;; Registers used:
;;		wreg, status,2, status,0
;; Tracked objects:
;;		On entry : 100/0
;;		On exit  : 100/0
;;		Unchanged: 100/0
;; Data sizes:     COMMON   BANK0   BANK1
;;      Params:         4       0       0
;;      Locals:         2       0       0
;;      Temps:          0       0       0
;;      Totals:         6       0       0
;;Total ram usage:        6 bytes
;; Hardware stack levels used:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_twinkle_init
;;		_twinkle_update
;;		_random_value
;; This function uses a non-reentrant model
;;
psect	text29,local,class=CODE,delta=2,merge=1,group=1
	file	"F:\Program Files\SCMCU_IDE_V2.00.16\data\sources\common\Umul16.c"
	line	15
global __ptext29
__ptext29:	;psect for function ___wmul
psect	text29
	file	"F:\Program Files\SCMCU_IDE_V2.00.16\data\sources\common\Umul16.c"
	line	15
	global	__size_of___wmul
	__size_of___wmul	equ	__end_of___wmul-___wmul
	
___wmul:	
;incstack = 0
	opt	stack 4
; Regs used in ___wmul: [wreg+status,2+status,0]
	line	43
	
l2913:	
	clrf	(___wmul@product)
	clrf	(___wmul@product+1)
	line	45
	
l2915:	
	btfss	(___wmul@multiplier),(0)&7
	goto	u1071
	goto	u1070
u1071:
	goto	l2919
u1070:
	line	46
	
l2917:	
	movf	(___wmul@multiplicand),w
	addwf	(___wmul@product),f
	skipnc
	incf	(___wmul@product+1),f
	movf	(___wmul@multiplicand+1),w
	addwf	(___wmul@product+1),f
	line	47
	
l2919:	
	clrc
	rlf	(___wmul@multiplicand),f
	rlf	(___wmul@multiplicand+1),f
	line	48
	
l2921:	
	clrc
	rrf	(___wmul@multiplier+1),f
	rrf	(___wmul@multiplier),f
	line	49
	
l2923:	
	movf	((___wmul@multiplier)),w
iorwf	((___wmul@multiplier+1)),w
	btfss	status,2
	goto	u1081
	goto	u1080
u1081:
	goto	l2915
u1080:
	line	52
	
l2925:	
	movf	(___wmul@product+1),w
	movwf	(?___wmul+1)
	movf	(___wmul@product),w
	movwf	(?___wmul)
	line	53
	
l1515:	
	return
	opt stack 0
GLOBAL	__end_of___wmul
	__end_of___wmul:
	signat	___wmul,8314
	global	___lwmod

;; *************** function ___lwmod *****************
;; Defined at:
;;		line 6 in file "F:\Program Files\SCMCU_IDE_V2.00.16\data\sources\common\lwmod.c"
;; Parameters:    Size  Location     Type
;;  divisor         2    6[COMMON] unsigned int 
;;  dividend        2    8[COMMON] unsigned int 
;; Auto vars:     Size  Location     Type
;;  counter         1   10[COMMON] unsigned char 
;; Return value:  Size  Location     Type
;;                  2    6[COMMON] unsigned int 
;; Registers used:
;;		wreg, status,2, status,0
;; Tracked objects:
;;		On entry : 100/0
;;		On exit  : 100/0
;;		Unchanged: 100/0
;; Data sizes:     COMMON   BANK0   BANK1
;;      Params:         4       0       0
;;      Locals:         1       0       0
;;      Temps:          0       0       0
;;      Totals:         5       0       0
;;Total ram usage:        5 bytes
;; Hardware stack levels used:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_twinkle_init
;; This function uses a non-reentrant model
;;
psect	text30,local,class=CODE,delta=2,merge=1,group=1
	file	"F:\Program Files\SCMCU_IDE_V2.00.16\data\sources\common\lwmod.c"
	line	6
global __ptext30
__ptext30:	;psect for function ___lwmod
psect	text30
	file	"F:\Program Files\SCMCU_IDE_V2.00.16\data\sources\common\lwmod.c"
	line	6
	global	__size_of___lwmod
	__size_of___lwmod	equ	__end_of___lwmod-___lwmod
	
___lwmod:	
;incstack = 0
	opt	stack 4
; Regs used in ___lwmod: [wreg+status,2+status,0]
	line	13
	
l2943:	
	movf	((___lwmod@divisor)),w
iorwf	((___lwmod@divisor+1)),w
	btfsc	status,2
	goto	u1111
	goto	u1110
u1111:
	goto	l2959
u1110:
	line	14
	
l2945:	
	clrf	(___lwmod@counter)
	incf	(___lwmod@counter),f
	line	15
	goto	l2949
	line	16
	
l2947:	
	clrc
	rlf	(___lwmod@divisor),f
	rlf	(___lwmod@divisor+1),f
	line	17
	incf	(___lwmod@counter),f
	line	15
	
l2949:	
	btfss	(___lwmod@divisor+1),(15)&7
	goto	u1121
	goto	u1120
u1121:
	goto	l2947
u1120:
	line	20
	
l2951:	
	movf	(___lwmod@divisor+1),w
	subwf	(___lwmod@dividend+1),w
	skipz
	goto	u1135
	movf	(___lwmod@divisor),w
	subwf	(___lwmod@dividend),w
u1135:
	skipc
	goto	u1131
	goto	u1130
u1131:
	goto	l2955
u1130:
	line	21
	
l2953:	
	movf	(___lwmod@divisor),w
	subwf	(___lwmod@dividend),f
	movf	(___lwmod@divisor+1),w
	skipc
	decf	(___lwmod@dividend+1),f
	subwf	(___lwmod@dividend+1),f
	line	22
	
l2955:	
	clrc
	rrf	(___lwmod@divisor+1),f
	rrf	(___lwmod@divisor),f
	line	23
	
l2957:	
	decfsz	(___lwmod@counter),f
	goto	u1141
	goto	u1140
u1141:
	goto	l2951
u1140:
	line	25
	
l2959:	
	movf	(___lwmod@dividend+1),w
	movwf	(?___lwmod+1)
	movf	(___lwmod@dividend),w
	movwf	(?___lwmod)
	line	26
	
l1862:	
	return
	opt stack 0
GLOBAL	__end_of___lwmod
	__end_of___lwmod:
	signat	___lwmod,8314
	global	___bmul

;; *************** function ___bmul *****************
;; Defined at:
;;		line 4 in file "F:\Program Files\SCMCU_IDE_V2.00.16\data\sources\common\Umul8.c"
;; Parameters:    Size  Location     Type
;;  multiplier      1    wreg     unsigned char 
;;  multiplicand    1    0[COMMON] unsigned char 
;; Auto vars:     Size  Location     Type
;;  multiplier      1    2[COMMON] unsigned char 
;;  product         1    1[COMMON] unsigned char 
;; Return value:  Size  Location     Type
;;                  1    wreg      unsigned char 
;; Registers used:
;;		wreg, status,2, status,0
;; Tracked objects:
;;		On entry : 100/0
;;		On exit  : 100/0
;;		Unchanged: 100/0
;; Data sizes:     COMMON   BANK0   BANK1
;;      Params:         1       0       0
;;      Locals:         2       0       0
;;      Temps:          0       0       0
;;      Totals:         3       0       0
;;Total ram usage:        3 bytes
;; Hardware stack levels used:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_breath_update
;;		_twinkle_init
;;		_twinkle_update
;; This function uses a non-reentrant model
;;
psect	text31,local,class=CODE,delta=2,merge=1,group=1
	file	"F:\Program Files\SCMCU_IDE_V2.00.16\data\sources\common\Umul8.c"
	line	4
global __ptext31
__ptext31:	;psect for function ___bmul
psect	text31
	file	"F:\Program Files\SCMCU_IDE_V2.00.16\data\sources\common\Umul8.c"
	line	4
	global	__size_of___bmul
	__size_of___bmul	equ	__end_of___bmul-___bmul
	
___bmul:	
;incstack = 0
	opt	stack 4
; Regs used in ___bmul: [wreg+status,2+status,0]
;___bmul@multiplier stored from wreg
	movwf	(___bmul@multiplier)
	line	6
	
l2929:	
	clrf	(___bmul@product)
	line	43
	
l2931:	
	btfss	(___bmul@multiplier),(0)&7
	goto	u1091
	goto	u1090
u1091:
	goto	l2935
u1090:
	line	44
	
l2933:	
	movf	(___bmul@multiplicand),w
	addwf	(___bmul@product),f
	line	45
	
l2935:	
	clrc
	rlf	(___bmul@multiplicand),f
	line	46
	
l2937:	
	clrc
	rrf	(___bmul@multiplier),f
	line	47
	movf	((___bmul@multiplier)),w
	btfss	status,2
	goto	u1101
	goto	u1100
u1101:
	goto	l2931
u1100:
	line	50
	
l2939:	
	movf	(___bmul@product),w
	line	51
	
l1533:	
	return
	opt stack 0
GLOBAL	__end_of___bmul
	__end_of___bmul:
	signat	___bmul,8313
global	___latbits
___latbits	equ	0
	global	fptotal
fptotal equ 28
	file ""
	line	#
psect	functab,class=ENTRY,delta=2
global __pfunctab
__pfunctab:
	global	fptable,__fptable
__fptable:
fptable:
	movwf (btemp+1)&07Fh
	movlw high(fptable)
	movwf pclath
	movf (btemp+1)&07Fh,w
	addwf pc
	global	fpbase
fpbase:
	goto fpbase	; Call via a null pointer and you will get stuck here.
	file ""
	line	#
fp__twinkle_init:
	ljmp	_twinkle_init
	file ""
	line	#
fp__breath_init:
	ljmp	_breath_init
	file ""
	line	#
fp__chase_init:
	ljmp	_chase_init
	file ""
	line	#
fp__expand_init:
	ljmp	_expand_init
	file ""
	line	#
fp__marquee_init:
	ljmp	_marquee_init
	file ""
	line	#
fp__stack_init:
entry__stack_init:
	global	entry__stack_init
	ljmp	_stack_init
	file ""
	line	#
fp__police_init:
	ljmp	_police_init
	file ""
	line	#
fp__twinkle_update:
	ljmp	_twinkle_update
	file ""
	line	#
fp__breath_update:
	ljmp	_breath_update
	file ""
	line	#
fp__chase_update:
	ljmp	_chase_update
	file ""
	line	#
fp__expand_update:
	ljmp	_expand_update
	file ""
	line	#
fp__marquee_update:
	ljmp	_marquee_update
	file ""
	line	#
fp__stack_update:
	ljmp	_stack_update
	file ""
	line	#
fp__police_update:
	ljmp	_police_update
	global __end_of__fptable
	__end_of__fptable:
	global __size_of__fptable
	__size_of__fptable	equ	__end_of__fptable-__fptable
	global	btemp
	btemp set 07Eh

	DABS	1,126,2	;btemp
	global	wtemp0
	wtemp0 set btemp+0
	end
