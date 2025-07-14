/*---------------------------------------------------------------------
        Copyright (C) 1997, 1998 Nintendo.
        
        File            rtc.h
        Coded    by     Shigeo Kimura.  Oct 14, 1997.
        Modified by     Koji Mitsunari. Jan 22, 2001.
        Comments        Real Time Clock Library
   
        $Id: rtc.h,v 1.1 2004/02/12 20:16:24 tong Exp $
   ---------------------------------------------------------------------*/
/**************************************************************************
 *
 *  $Revision: 1.1 $
 *  $Date: 2004/02/12 20:16:24 $
 *  $Source: 
 *
 **************************************************************************/
#ifndef	_rtc_h_
#define	_rtc_h_

/*-----------------------------------------------------------------------
 * 		マクロ＆定数定義
 *-----------------------------------------------------------------------*/
/* Controller type */
#define CONT_TYPE_RTC	0x1000		/* os.hに内蔵 */
#define RTC_WAIT	300

/* RTC status signed 32bits */
#define RTC_NG_NOTHING   0x8000
#define RTC_NG_WRITE     0x0100
#define RTC_NG_ADDR      0x0200
#define RTC_STATUS_BUSY  0x0080
#define RTC_STATUS_DDOWN 0x0002
#define RTC_STATUS_BDOWN 0x0001

/* RTC Error Code */
#define	CONT_ERR_RTC_BUSY	16
#define	CONT_ERR_RTC_BDOWN	17
#define	CONT_ERR_RTC_DDOWN	18
#define	CONT_ERR_RTC_BDDOWN	19

/* RTC bit status */
#define RTC_EALM 0x80
#define RTC_ALM  0x20
#define RTC_WPB1 0x02
#define RTC_WPB0 0x01
#define RTC_MOD  0x04
#define RTC_CHLD 0x02
#define RTC_ADJ  0x01

#define	RTC_ADDR_FLAG	0
#define	RTC_ADDR_RAM	1
#define	RTC_ADDR_TIME	2

typedef struct{
	u8	sec;	/* second 0-59 */
	u8	min;	/* minute 0-59 */
	u8	hour;	/* hour   0-23 */
	u8	day;	/* day    1-31 */
	u8	week;	/* week   0-6(sun,mon,..,sat) */
	u8	month;	/* month  1-12 */
	u16	year;	/* year 1901-2099 */
} OSRTCTime;

/*-----------------------------------------------------------------------
 * 		外部宣言
 *-----------------------------------------------------------------------*/
extern s32 osRTCInit(OSMesgQueue *);
extern s32 osRTCReadData(OSMesgQueue *, u8 *);
extern s32 osRTCWriteData(OSMesgQueue *, u8 *);
extern s32 osRTCGetTime(OSMesgQueue *, OSRTCTime *);
extern s32 osRTCSetTime(OSMesgQueue *, OSRTCTime *);
extern u32 osRTCGetIntervalTime(OSRTCTime *, OSRTCTime *);
extern s32 osRTCGetLaterTime(OSMesgQueue *, u32, OSRTCTime *);
extern s32 osRTCSetAlarm(OSMesgQueue *, u8, u8);
extern s32 osRTCGetAlarmStat(OSMesgQueue *, u8 *, u8 *, int *);

#endif /* _rtc_h_ */
