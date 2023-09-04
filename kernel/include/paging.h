
typedef enum {
    PAGING_FLAG_PRESENT = 1<<0,
    PAGING_FLAG_RW = 1<<1,
    PAGING_FLAG_US = 1<<2,
    PAGING_FLAG_PWT = 1<<3,
    PAGING_FLAG_PCD = 1<<4,
    PAGING_FLAG_A = 1<<5,
    PAGING_FLAG_D = 1<<6,
    PAGING_FLAG_PAT = 1<<7,
    PAGING_FLAG_G = 1<<8,
    PAGING_FLAG_XD = 1<<63
} pagingFlags;

void *get_physaddr(void *virtualaddr);
void map_page(void *physaddr, void *virtualaddr, unsigned int flags);