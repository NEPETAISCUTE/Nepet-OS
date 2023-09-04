#ifndef RSDP_H
#define RSDP_H

#include <stdint.h>

typedef struct {
 char Signature[8];
 uint8_t Checksum;
 char OEMID[6];
 uint8_t Revision;
 uint32_t RsdtAddress;
} RSDPDescriptor __attribute__ ((packed));

struct RSDPDescriptor20 {
 RSDPDescriptor firstPart;
 
 uint32_t Length;
 uint64_t XsdtAddress;
 uint8_t ExtendedChecksum;
 uint8_t reserved[3];
} __attribute__ ((packed));

#endif