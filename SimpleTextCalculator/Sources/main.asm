;*****************************************************************
;* This stationery serves as the framework for a                 *
;* user application (single file, absolute assembly application) *
;* For a more comprehensive program that                         *
;* demonstrates the more advanced functionality of this          *
;* processor, please see the demonstration applications          *
;* located in the examples subdirectory of the                   *
;* Freescale CodeWarrior for the HC12 Program directory          *
;*****************************************************************


;***********************************************************************
;* Sema Köse                                                           *
;* 141044002                                                           *
;*                                                                     *
;* Notlar:                                                             *
;* Toplama yaparken integer kýsmý 2 basamaklý olmalý                   *                           
;* Çýkarma yaparken ilk sayýnýn deðerleri ikinci sayýdan büyük olmalý  *                                            
;*                                                                     *
;*                                                                     *
;*                                                                     *
;***********************************************************************


; export symbols
            XDEF Entry, _Startup            ; export 'Entry' symbol
            ABSENTRY Entry        ; for absolute assembly: mark this as application entry point



; Include derivative-specific definitions 
		INCLUDE 'derivative.inc' 

ROMStart    EQU  $4000  ; absolute address to place my code/constant data
StringStart EQU $1200 ; address to place string
IntStart EQU $1700 ; address to place integer part
DecStart EQU $1800 ; address to place decimal part

IntStart2 EQU $2000 ; address to place integer part
DecStart2 EQU $2500 ; address to place decimal part

; variable/data section

            ORG RAMStart
 ; Insert here your data definition.
Counter     DS.W 1
FiboRes     DS.W 1

Size        DC.B 0
AfterPoint  DC.B 2
Power  DC.B 10
Temp  DC.B 0
A_Temp  DC.B 0
B_Temp  DC.B 1
Count DC.B 0
Sign DC.B 0
Cnt DC.B 0
Res_1  DC.B 0
Res_2  DC.B 0
Res_3  DC.B 0
Res_4  DC.B 0
Carry  DC.B 0

            ORG StringStart      ; start from the $1200
String      fcc "10.40 + 05.10 =" ; initialize the string
                 ORG IntStart      ; start from the $1200
IntegerPart      DC.B 0 ; initialize the string
            ORG DecStart      ; start from the $1200
DecimalPart      DC.B 0 ; initialize the string
            ORG IntStart2
IntegerPart2      DC.B 0 ; initialize the string
            ORG DecStart2      ; start from the $1200
DecimalPart2      DC.B 0 ; initialize the string
; code section
            ORG   ROMStart


Entry:     LDAA $FF
           STAA DDRB
           STAA DDRA
           STAA DDRJ
           LDX #String
           LDY #IntegerPart
           
           
           
_Startup:  LDAB #$2E
           LDAA X
           INC Size
           CBA
           BEQ ReInit
           BNE LoadToInt
           
           
           
LoadToInt: STAA Y
           INC Cnt
           INX
           INY
           CBA
           BNE _Startup
           
ReInit:    DEC Size
           LDY #DecimalPart
           INX
           
LoadToDec: LDAB #$0
           LDAA X
           INC Cnt
           STAA Y
           INY
           INX
           DEC AfterPoint
           CMPB AfterPoint
           BNE LoadToDec
           LDX #IntegerPart
           LDAB Size
           
ReverseTheInt: 
           LDAA X
           SBCA #$30
           STAA X
           DECB
           INX
           CMPB 0
           BNE ReverseTheInt
           LDX #DecimalPart
           LDAB AfterPoint
           
ReverseTheDec:
           LDAA X
           SBCA #$30
           STAA X
           INCB
           INX
           LDAA #$2
           CBA
           BNE ReverseTheDec
           
           LDX #IntegerPart
           LDAB Size
           
CompSize:  LDAA #$A
           DECB
           CMPB #$0
           BLE Find_2
           STAB B_Temp
           LDAB X
           
Find_1:    MUL
           STD Temp
           INX
           LDAB B_Temp
           LDAA #$A
           JMP CompSize
            
Find_2:
            LDAB A_Temp
            LDAA X
            ABA
            STAA X
            
            LDX #DecimalPart
            
            LDAB Size
            INC Count
            LDAA Count
            CMPA #$2
            BNE CompSize
            
            LDAA Size
            LDX #IntegerPart
            LDY #DecimalPart 
            
FindRes1:   DECA
            INX
            CMPA #$0
            BNE FindRes1
            DEX
            LDAA X
            STAA Res_1
            
            LDAA #$2
            
FindRes2:   DECA
            INY
            CMPA #$0
            BNE FindRes2
            DEY
            LDAA Y
            STAA Res_2
            
            
            
            
            
                       
            LDX #String
            
            
Addr:       INX
            DEC Cnt
            LDAA #$0
            CMPA Cnt
            BNE Addr
            
            INX
            INX
            
            LDAA X
            STAA Sign
            
            INX
            INX
;;;;;;;;;;;;;;;;;;;;;;;;;;;Second Number;;;;;;;;;;;;;;;;;;;;;           
           
           
           LDY #IntegerPart2
           INC AfterPoint
           INC AfterPoint
           LDAA #$0
           STAA Size
           STAA Power
           STAA Temp
           STAA A_Temp
           STAA Count
           STAA Cnt
           LDAA #$1
           STAA B_Temp
           
_Startup2: LDAB #$2E
           LDAA X
           INC Size
           CBA
           BEQ ReInit2
           BNE LoadToInt2
           
LoadToInt2: STAA Y
           INX
           INY
           CBA
           BNE _Startup2
           
ReInit2:    DEC Size
           LDY #DecimalPart2
           INX
           
LoadToDec2: LDAB #$0
           LDAA X
           STAA Y
           INY
           INX
           DEC AfterPoint
           CMPB AfterPoint
           BNE LoadToDec2
           LDX #IntegerPart2
           LDAB Size
           
ReverseTheInt2: 
           LDAA X
           SBCA #$30
           STAA X
           DECB
           INX
           CMPB 0
           BNE ReverseTheInt2
           LDX #DecimalPart2
           LDAB AfterPoint
           
ReverseTheDec2:
           LDAA X
           SBCA #$30
           STAA X
           INCB
           INX
           LDAA #$2
           CBA
           BNE ReverseTheDec2
           
           LDX #IntegerPart2
           LDAB Size
           
CompSize2:  LDAA #$A
           DECB
           CMPB #$0
           BLE Find_22
           STAB B_Temp
           LDAB X
           
Find_12:    MUL
           STD Temp
           INX
           LDAB B_Temp
           LDAA #$A
           JMP CompSize2
            
Find_22:
            LDAB A_Temp
            
            LDAA X
            
            ABA
            STAA X
            
            LDX #DecimalPart2
            
            LDAB Size
            INC Count
            LDAA Count
            CMPA #$2
            BNE CompSize2
            
            LDAA Size
            LDX #IntegerPart2
            LDY #DecimalPart2
            
            
FindRes12:  DECA
            INX
            CMPA #$0
            BNE FindRes12
            DEX
            LDAA X
            STAA Res_3
            
            LDAA #$2
            
FindRes22:  DECA
            INY
            CMPA #$0
            BNE FindRes22
            DEY
            LDAA Y
            STAA Res_4
            
            
         
SumOrSub:   LDAA Sign
            CMPA #$2B
            BEQ Sum
            BNE Sub
            
Sum:        LDX #Carry
            LDAA Res_2
            ADCA Res_4
            LDAB Res_4
            STAA Res_2
            LDAB Res_2
            LDAA #$0
            
            LDX #$64
            IDIV
            TFR D,B
            STAB Cnt
            TFR X,B
            LDAA Res_1
            ADCA Res_3
            ABA
            LDAB #$0
            STAA Res_1
            
            LDAA Res_1
            LDAB Cnt
            
            JMP Jnk
            
Sub:        LDAA Res_2
            SUBA Res_4
            STAA Res_2
            
            LDAB Res_1
            SUBB Res_3
            STAB Res_1
            
            LDAA Res_1
            LDAB Res_2
            
            
            
Jnk:        STAA $1500
            LDAA #$2E
            STAA $1501
            STAB $1502

            STAA PORTA
            STAA PORTA
            STAA $55
           
           ;End
           

;**************************************************************
;*                 Interrupt Vectors                          *
;**************************************************************
            ORG   $FFFE
            DC.W  Entry           ; Reset Vector
