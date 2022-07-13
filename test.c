#include <errno.h>
#include <inttypes.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "eva_string.h"

int main(void)
{
    evastr test = evannew("1\02",3);
    printf("%u\n%zu\n",evalen(test),strlen(test));
    evafree(test);
    return 0;
}