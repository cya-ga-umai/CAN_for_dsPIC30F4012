# CAN for dsPIC30F4012
dsPIC30F4012用のCAN関数です。
XC16のCAN関数が使い物にならなかったので作成。
（最低限の実装だけど……）
## 使い方
```c
void CAN1_init(void);
```

 * 機能：   CANモジュールの初期設定
 * 引数：   なし
 * 戻値：   なし

 ```c
void CAN1_set_OPmode(unsigned char mode);
 ```

 * 機能：   CANモジュールの動作モードを変更
 * 引数：   mode   動作モードを以下のマクロから選択
     * CAN_REQ_OPERMODE_NOR：通常モード
     * CAN_REQ_OPERMODE_DIS：無効
     * CAN_REQ_OPERMODE_LOOPBK：ループバックモード
     * CAN_REQ_OPERMODE_LISTENONLY：リスンオンリーモード
     * CAN_REQ_OPERMODE_CONFIG：設定モード
     * CAN_REQ_OPERMODE_LISTENALL：リスンオールモード
 * 戻値：   なし

```c
void CAN1_set_mask(unsigned char mask_no, unsigned int sid, unsigned long eid, unsigned char mide);
```

 * 機能：   CANモジュールのマスク設定
 * 引数：   mask_no    マスク番号0 - 1
 *          sid         標準メッセージID
 *          eid         拡張メッセージID
 *          mide        以下のマクロから選択
        * CAN_MATCH_FILTER_TYPE：一致したものを指定する
        * CAN_IGNORE_FILTER_TYPE：一致したものを無視する
 * 戻値：   なし

```c
void CAN1_set_filter(unsigned char filter_no, unsigned char id_type, unsigned int sid, unsigned long eid);
```

 * 機能：   CANモジュールのフィルタ設定
 * 引数：   filter_no   フィルタ番号0 - 5
 *          id_type     以下のマクロから選択
        * CAN_EID_EN：拡張メッセージID有効
        * CAN_EID_DIS：拡張メッセージID無効
 *          sid         標準メッセージID
 *          eid         拡張メッセージID
 * 戻値：   なし

```c
void CAN1_send_message_8(unsigned char buffer_no, unsigned char id_type, unsigned char msg_type, 
        unsigned char priority, unsigned int sid, unsigned long eid, unsigned char *data, unsigned char datalen);
        
void CAN1_send_message_16(unsigned char buffer_no, unsigned char id_type, unsigned char msg_type, 
        unsigned char priority, unsigned int sid, unsigned long eid, unsigned int *data, unsigned char datalen);
        
void CAN1_send_message_32(unsigned char buffer_no, unsigned char id_type, unsigned char msg_type, 
        unsigned char priority, unsigned int sid, unsigned long eid, unsigned long *data, unsigned char datalen);
```

 * 機能：   データを送信する
 * 引数：   buffer_no   バッファ番号0-2
 *          id_type     以下のマクロから選択
        * CAN_EID_EN：拡張メッセージID有効
        * CAN_EID_DIS：拡張メッセージID無効
 *          msg_type    以下のマクロから選択
        * CAN_REM_TX_REQ：リモート送信要求
        * CAN_NOR_TX_REQ：通常メッセージ
 *          priority    メッセージ優先度0-3
 *          sid         標準メッセージID
 *          eid         拡張メッセージID
 *          data        送信データへのポインタ
 *          datalen     送信データ長1-8
 * 戻値：   なし

```c
void CAN1_read_message_8(unsigned char buffer_no, unsigned char *data);

void CAN1_read_message_16(unsigned char buffer_no, unsigned int *data);

void CAN1_read_message_32(unsigned char buffer_no, unsigned long *data);
```

 * 機能：   データを受信する
 * 引数：   buffer_no   バッファ番号0-1
 *          data        受信データを格納する変数へのポインタ
 * 戻値：   なし

