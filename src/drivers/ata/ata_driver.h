// ata_driver.h

#ifndef ATA_DRIVER_H
#define ATA_DRIVER_H

#define REG_DEVSEL 6
#define REG_CYL_LO 4
#define REG_CYL_HI 5

struct DEVICE
{
  unsigned short dev_ctl;
  unsigned short base;
};

int detect_devtype(int slavebit, struct DEVICE *ctrl);

#endif // ATA_DRIVER_H
