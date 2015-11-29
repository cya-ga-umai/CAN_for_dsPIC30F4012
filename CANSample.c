/******************************************************************************
 *  ファイル名： CANSample.c
 * 　 作成日時： 2015/11/09
 * 　　　 機能： CAN通信実装テスト
 *              サンプルコードCE034 - CAN Loopbackを改良
 ******************************************************************************/

/******************************************************************************
 * ヘッダファイル
 ******************************************************************************/
#include <xc.h>
#include "mycan.h"
/******************************************************************************
 * グローバル変数
 ******************************************************************************/
unsigned int OutData0[4] = {0x5251, 0x5453, 0x5655, 0x5857};            
unsigned int OutData1[2] = {0x5A59, 0x5C5B};

unsigned int InData0[4] = {0, 0, 0, 0};
unsigned int InData1[2] = {0, 0};

/******************************************************************************
 * コンフィギュレーション設定
 ******************************************************************************/
// FOSC
#pragma config FPR = FRC_PLL16          // Primary Oscillator Mode (FRC w/ PLL 16x)
#pragma config FOS = FRC                // Oscillator Source (Internal Fast RC)
#pragma config FCKSMEN = CSW_FSCM_OFF   // Clock Switching and Monitor (Sw Disabled, Mon Disabled)

// FWDT
#pragma config FWPSB = WDTPSB_16        // WDT Prescaler B (1:16)
#pragma config FWPSA = WDTPSA_512       // WDT Prescaler A (1:512)
#pragma config WDT = WDT_OFF            // Watchdog Timer (Disabled)

// FBORPOR
#pragma config FPWRT = PWRT_64          // POR Timer Value (64ms)
#pragma config BODENV = BORV27          // Brown Out Voltage (2.7V)
#pragma config BOREN = PBOR_ON          // PBOR Enable (Enabled)
#pragma config LPOL = PWMxL_ACT_HI      // Low-side PWM Output Polarity (Active High)
#pragma config HPOL = PWMxH_ACT_HI      // High-side PWM Output Polarity (Active High)
#pragma config PWMPIN = RST_IOPIN       // PWM Output Pin Reset (Control with PORT/TRIS regs)
#pragma config MCLRE = MCLR_EN          // Master Clear Enable (Enabled)

// FGS
#pragma config GWRP = GWRP_OFF          // General Code Segment Write Protect (Disabled)
#pragma config GCP = CODE_PROT_OFF      // General Segment Code Protection (Disabled)

// FICD
#pragma config ICS = ICS_PGD            // Comm Channel Select (Use PGC/EMUC and PGD/EMUD)

/******************************************************************************
 * メイン関数
 ******************************************************************************/
int main(void) {
    /* IO設定 */
    TRISD = 0x0000; // Initialize the PORTD as output
    LATD = 0xFFFF; // Initially LEDs of dsPICDEM1.1 Plus GP Board are off 

    /* CANモジュールの初期化 */
    CAN1_init();
    
    /* マスク設定 */
    CAN1_set_mask(0, 0x7FF, 0x3FFFF, CAN_MATCH_FILTER_TYPE);
    CAN1_set_mask(1, 0x7FF, 0x3FFFF, CAN_MATCH_FILTER_TYPE);
    
    /* フィルタ設定 */
    CAN1_set_filter(0, CAN_EID_DIS, 0x2AA, 0x00);
    CAN1_set_filter(2, CAN_EID_EN, 0x555, 0x123);
    
    /* CANモジュールをループバックモードに変更 */
    CAN1_set_OPmode(CAN_REQ_OPERMODE_LOOPBK);
    //CAN1_set_OPmode(CAN_REQ_OPERMODE_NOR);
    
    /* メッセージ送信設定 */
    CAN1_send_message_16(0, CAN_EID_DIS, CAN_NOR_TX_REQ, 3, 0x2AA, 0x00, OutData0, 8);
    CAN1_send_message_16(1, CAN_EID_EN, CAN_NOR_TX_REQ, 2, 0x555, 0x123, OutData1, 4);


    CAN1_read_message_16(0, InData0);
    if ((InData0[0] == OutData0[0]) && (InData0[1] == OutData0[1]) && (InData0[2] == OutData0[2]) && (InData0[3] == OutData0[3]))
        LATDbits.LATD0 = 0;

    CAN1_read_message_16(1, InData1);
    if ((InData1[0] == OutData1[0]) && (InData1[1] == OutData1[1]))
        LATDbits.LATD1 = 0;
    while (1) {

    } //end while loop


}								//end main loop 