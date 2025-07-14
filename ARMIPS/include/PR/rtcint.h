/*---------------------------------------------------------------------
        Copyright (C) 1997, 1998 Nintendo.
        
        File            rtcint.h
        Coded    by     Shigeo Kimura.  Oct 14, 1997.
        Modified by     Koji Mitsunari. Jan 29, 1999.
        Comments        Real Time Clock Library
   
        $Id: rtcint.h,v 1.1 2004/02/12 20:16:24 tong Exp $
   ---------------------------------------------------------------------*/
/**************************************************************************
 *
 *  $Revision: 1.1 $
 *  $Date: 2004/02/12 20:16:24 $
 *  $Source: 
 *
 **************************************************************************/

#ifndef	_rtcint_h_
#define	_rtcint_h_

/*-----------------------------------------------------------------------
 * 		マクロ＆定数定義
 *-----------------------------------------------------------------------*/
/* RTC size */
#define RTC_BLOCK_SIZE	0x08
#define RTC_MAXBLOCKS	0x03
/* RTC Command */
#define CONT_RTC_TYPE	0x06
#define CONT_RTC_WRITE	0x08
#define CONT_RTC_READ	0x07

#define	OS_BCD_TO_DEC(x)	(((x)&15)+((x)>>4)*10)
#define	OS_DEC_TO_BCD(x)	(((x)%10)+(((x)/10)<<4))

/*-----------------------------------------------------------------------
 * 		構造体定義
 *-----------------------------------------------------------------------*/
/* RTC Read/Write Format */
typedef struct {
	u8	txsize;			/* Tx size */
	u8	rxsize;			/* Rx size */
	u8	cmd;			/* commmand */
	u8	address;		/* address */
	u8	data[RTC_BLOCK_SIZE];	/* data0,..,data7 */
	u8	status;			/* status */
} __OSRTCReadWriteFormat; 

/*-----------------------------------------------------------------------
 * 		外部宣言
 *-----------------------------------------------------------------------*/
extern OSTimer		__osRtcTimer;
extern OSMesgQueue	__osRtcTimerQ;
extern OSMesg		__osRtcTimerMsg;
extern s32		__osRTCInitialize;

extern s32 __osRTCGetStatus(OSMesgQueue *, u8 *);
extern s32 __osRTCRawRead(OSMesgQueue *, u8, u8 *);
extern s32 __osRTCRawWrite(OSMesgQueue *, u8, u8 *);


#endif /* _rtcint_h_ */
