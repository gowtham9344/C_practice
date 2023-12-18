#include <float.h>
#include <limits.h>
#include <stdio.h>

int main() {
    printf("Ranges of various types through calculation:\n");
    printf("Signed value ranges:\n");
    printf("%ld\n",-(long) ((unsigned long) ~0));

    printf("Minimum Signed Char:%d\n", -(char) ((unsigned char) ~0 >> 1) - 1);
    printf("Maximum Signed Char:%d\n", (char) ((unsigned char) ~0 >> 1));

    printf("Minimum Signed Short:%d\n", -(short) ((unsigned short) ~0 >> 1) - 1);
    printf("Maximum Signed Short:%d\n", (short) ((unsigned short) ~0 >> 1));

    printf("Minimum Signed Int:%d\n", -(int) ((unsigned int) ~0 >> 1) - 1);
    printf("Maximum Signed Int:%d\n", (int) ((unsigned int) ~0 >> 1));

    printf("Minimum Signed Long:%ld\n", -(long) ((unsigned long) ~0 >> 1) - 1);
    printf("Maximum signed Long:%ld\n", (long) ((unsigned long) ~0 >> 1));

    printf("Unsigned value ranges:\n");
    printf("Maximum Unsigned Char:%d\n", (unsigned char) ~0);
    printf("Maximum Unsigned Short:%d\n", (unsigned short) ~0);
    printf("Maximum Unsigned Int:%u\n", (unsigned int) ~0);
    printf("Maximum Unsigned Long:%lu\n\n", (unsigned long) ~0);

    
    printf("Ranges of various types from standard headers:\n");
    printf("Signed values ranges:\n");
    printf("Minimum Signed Char:%d\n", SCHAR_MIN);
    printf("Maximum Signed Char:%d\n", SCHAR_MAX);

    printf("Minimum Signed Short:%d\n", SHRT_MIN);
    printf("Maximum Signed Short:%d\n", SHRT_MAX);

    printf("Minimum Signed Int:%d\n", INT_MIN);
    printf("Maximum Signed Int:%d\n", INT_MAX);

    printf("Minimum Signed Long:%ld\n", LONG_MIN);
    printf("Maximum signed Long:%ld\n", LONG_MAX);    

    printf("Unsigned values ranges:\n");
    printf("Maximum Unsigned Char:%d\n", UCHAR_MAX);
    printf("Maximum Unsigned Short:%d\n", USHRT_MAX);
    printf("Maximum Unsigned Int:%u\n", UINT_MAX);
    printf("Maximum Unsigned Long:%lu\n", ULONG_MAX);

    printf("FLOAT MAX:%g\n", (float) FLT_MAX);
    printf("FLOAT MIN:%g\n", (float) FLT_MIN);
    printf("DOUBLE MAX:%g\n", (double) DBL_MAX);
    printf("DOUBLE MIN:%g\n", (double) DBL_MIN);

    return 0;
}
