# include <stdio.h>


#define F_RAZ   0x1    // 2^0, Binary: 0000000001
#define F_DVA   0x2    // 2^1, Binary: 0000000010
#define F_TRI   0x4    // 2^2, Binary: 0000000100
#define F_CHET  0x8    // 2^3, Binary: 0000001000
#define F_PET   0x10   // 2^4, Binary: 0000010000
#define F_SHEST 0x20   // 2^5, Binary: 0000100000
#define F_SEM   0x40   // 2^6, Binary: 0001000000
#define F_VOSEM 0x80   // 2^7, Binary: 0010000000
#define F_DEVET 0x100  // 2^8, Binary: 0100000000
#define F_DESYAT 0x200 // 2^9, Binary: 1000000000

void print_flags(const int flags)
{
    if (flags & F_RAZ) printf("Raz ");
    if (flags & F_DVA) printf("Dva ");
    if (flags & F_TRI) printf("Tri ");
    if (flags & F_CHET) printf("Chetyre ");
    printf("\n");
}

int main()
{
    int flags = F_RAZ | F_TRI | F_DVA;  // Set initial flags
    print_flags(flags);

    // Add a flag
    flags |= F_CHET;
    print_flags(flags);

    // Remove a flag
    flags &= ~F_DVA;
    print_flags(flags);

    return 0;
}
