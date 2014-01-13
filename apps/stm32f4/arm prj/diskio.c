/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for FatFs     (C)ChaN, 2013        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control module to the FatFs module with a defined API.        */
/*-----------------------------------------------------------------------*/

#include "diskio.h"		/* FatFs lower layer API */
#include <syniopsis.h>

/* Definitions of physical drive number for each media */
#define ATA		0
#define MMC		1
#define USB		2


/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */
/*-----------------------------------------------------------------------*/
DSTATUS disk_initialize(BYTE pdrv /* Physical drive nmuber (0..) */){
        if(SD_init()==0) return RES_OK;
        if(SD_init()==0) return RES_OK;
        if(SD_init()==0) return RES_OK;
        if(SD_init()==0) return RES_OK;
        if(SD_init()==0) return RES_OK;
	return STA_NOINIT;
}
/*-----------------------------------------------------------------------*/
/* Get Disk Status                                                       */
/*-----------------------------------------------------------------------*/
DSTATUS disk_status (BYTE pdrv /* Physical drive nmuber (0..) */){
        return RES_OK;
}
/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/
DRESULT disk_read (
	BYTE pdrv,		/* Physical drive nmuber (0..) */
	BYTE *buff,		/* Data buffer to store read data */
	DWORD sector,	/* Sector address (LBA) */
	BYTE count		/* Number of sectors to read (1..128) */
){
        unsigned long i;

        for(i=sector;i<count+sector;i++){
          if((SD_ReadSector(i, buff))!=0) return RES_ERROR;
          buff +=512;
        }
        return RES_OK;
}
/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/
#if _USE_WRITE
DRESULT disk_write (
	BYTE pdrv,			/* Physical drive nmuber (0..) */
	const BYTE *buff,	/* Data to be written */
	DWORD sector,		/* Sector address (LBA) */
	BYTE count			/* Number of sectors to write (1..128) */
){
        unsigned long i;
        BYTE *MyBuff;

        MyBuff = (BYTE *)(buff);
        for(i=sector;i<count+sector;i++){
          if((SD_WriteSector(i, MyBuff))!=0) return RES_ERROR;
          MyBuff +=512;
        }
        return RES_OK;
}
#endif
/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/
#if _USE_IOCTL
DRESULT disk_ioctl (
	BYTE drv,		/* Physical drive number (0) */
	BYTE ctrl,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{
	DRESULT res;
	//BYTE n, csd[16], *ptr = buff;
	//WORD csize;

        
	res = RES_OK;

        switch (ctrl) {
        case CTRL_SYNC :
          if(SD_WaitFree())res = RES_ERROR;
          return res;
          break;
          
       /* case GET_SECTOR_COUNT :	// Получить число секторов на диске 
          if ((send_cmd(CMD9, 0) == 0) && rcvr_datablock(csd, 16)) {
            if ((csd[0] >> 6) == 1) {	// SDC version 2.00
              csize = csd[9] + ((WORD)csd[8] << 8) + 1;
              *(DWORD*)buff = (DWORD)csize << 10;
            } else {            // SDC version 1.XX or MMC
              n = (csd[5] & 15) + ((csd[10] & 128) >> 7) + ((csd[9] & 3) << 1) + 2;
              csize = (csd[8] >> 6) + ((WORD)csd[7] << 2) + ((WORD)(csd[6] & 3) << 10) + 1;
              *(DWORD*)buff = (DWORD)csize << (n - 9);
            }
            res = RES_OK;
          }
          break;
          
        case GET_SECTOR_SIZE :	// Get R/W sector size (WORD)
          *(WORD*)buff = 512;
          res = RES_OK;
          break;

        case GET_BLOCK_SIZE :	// Get erase block size in unit of sector (DWORD)
          if (CardType & CT_SD2) {	// SDC version 2.00
            if (send_cmd(ACMD13, 0) == 0) {	// Read SD status
              rcvr_spi();
              if (rcvr_datablock(csd, 16)) {		// Read partial block
                for (n = 64 - 16; n; n--) rcvr_spi();	// Purge trailing data
                *(DWORD*)buff = 16UL << (csd[10] >> 4);
                res = RES_OK;
              }
            }
          } else {		// SDC version 1.XX or MMC
            if ((send_cmd(CMD9, 0) == 0) && rcvr_datablock(csd, 16)) {	// Read CSD
              if (CardType & CT_SD1) {	// SDC version 1.XX
                *(DWORD*)buff = (((csd[10] & 63) << 1) + ((WORD)(csd[11] & 128) >> 7) + 1) << ((csd[13] >> 6) - 1);
              } else {                  // MMC
                *(DWORD*)buff = ((WORD)((csd[10] & 124) >> 2) + 1) * (((csd[11] & 3) << 3) + ((csd[11] & 224) >> 5) + 1);
              }
              res = RES_OK;
            }
          }
          break;

        case CTRL_ERASE_SECTOR :	// Erase sector
          
          break;
        */
        default:
          res = RES_PARERR;
        }

        //release_spi();

	return res;
}
#endif /* _USE_IOCTL != 0 */



DWORD get_fattime (void){
  return 0;
}