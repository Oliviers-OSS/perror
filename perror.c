#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#if __GNUC__ >= 3
# undef  inline
# define inline         inline __attribute__ ((always_inline))
# define __pure         __attribute__ ((pure))
# define __must_check   __attribute__ ((warn_unused_result))
# define likely(x)      __builtin_expect (!!(x), 1)
# define unlikely(x)    __builtin_expect (!!(x), 0)
#else
# define _  _pure         /* no pure */
# define _  _must_check   /* no warn_unused_result */
# define likely(x)      (x)
# define unlikely(x)    (x)
#endif

/* TODO make a real parser */
__pure __must_check static inline int isValidNumber(const char* argument) {
  int isValid = 1;
  int hexMarkerFound = 0;
  const char *p = argument;
  
  while ((*p != '\0') && (isValid)) {
    switch(*p) {
    case 'x':
      /* break is missing */
    case 'X':
      /* only one allowed at first or second position */
      if (((p - argument) <= 1) && (!hexMarkerFound)) {
	hexMarkerFound = 1;
      } else {
	isValid = 0;
      }
      /* break is missing */
    case '-':
      /* break is missing */
    case '+':
      /* break is missing */
    case ' ':
      /* break is missing */
    case '0' ... '9':
      /* break is missing */
    case 'A' ... 'F':
      /* break is missing */
    case 'a' ... 'f':
      p++;
      break;    
    default:
      isValid = 0;
    } /* switch(*p) */
  } /* while(*p != '\0) */
  return isValid;
}

static inline void printUsage(const char *progName) {
  fprintf(stderr,"Usage: %s <error code number>\n",progName);
}

int main(int argc, char *argv[]) {
  int error = EXIT_FAILURE;
  if (2 == argc) {
    if (isValidNumber(argv[1])) {
      const long n = strtol(argv[1],NULL,0);
      printf("%s\n",strerror(n));
      error = EXIT_SUCCESS;
    } else {
      printUsage(argv[0]);
    }
  } else {
    printUsage(argv[0]);
  }
  return error;
}
