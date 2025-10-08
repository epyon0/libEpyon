#ifndef MISC_H
#define MISC_H

#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdint.h>

#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)   \
  ((byte) & 0x80 ? '1' : '0'), \
  ((byte) & 0x40 ? '1' : '0'), \
  ((byte) & 0x20 ? '1' : '0'), \
  ((byte) & 0x10 ? '1' : '0'), \
  ((byte) & 0x08 ? '1' : '0'), \
  ((byte) & 0x04 ? '1' : '0'), \
  ((byte) & 0x02 ? '1' : '0'), \
  ((byte) & 0x01 ? '1' : '0')

void verbose(const char *msg, const char *file, const int line, const char *func);
char* uint8tob(uint8_t i);
char* uint16tob(uint16_t i);
char* uint32tob(uint32_t i);
char* uint64tob(uint64_t i);
bool verbose_enabled = false;
void setverbose(bool value);
bool getverbose(void);
char* btos(const long long unsigned int i);

char* btos(const long long unsigned int i) { // Accepts bytes and retruns in human readable string
  static char buff[256];
  /*
  long long unsigned int base = 1024 * 1024 * 1024 * 1024 * 1024 * 1024 * 1024 * 1024;

  if (i >= base) { // Yottabyte
    snprintf(buff, sizeof(buff), "%llu YB", i / base);
    return buff;
  }
  
  base /= 1024;
  if (i >= base) { // Zettabyte
    snprintf(buff, sizeof(buff), "%llu ZB", i / base);
    return buff;
  }
  
  base /= 1024;
  if (i >= base) { // Exabyte
    snprintf(buff, sizeof(buff), "%llu EB", i / base);
    return buff;
  }
  */

  long long unsigned int base = 0x4000000000000;
  if (i >= base) { // Petabyte
    snprintf(buff, sizeof(buff), "%llu PB", i / base);
    return buff;
  }
  
  base /= 1024;
  if (i >= base) { // Terabyte
    snprintf(buff, sizeof(buff), "%llu TB", i / base);
    return buff;
  }
  

  base /= 1024;
  if (i >= base) { // Gigabyte
    snprintf(buff, sizeof(buff), "%llu GB", i / base);
    return buff;
  }
  
  base /= 1024;
  if (i >= base) { // Megabyte
    snprintf(buff, sizeof(buff), "%llu MB", i / base);
    return buff;
  }
  
  base /= 1024;
  if (i >= base) { // Kilobyte
    snprintf(buff, sizeof(buff), "%llu KB", i / base);
    return buff;
  }

  // Byte
  snprintf(buff, sizeof(buff), "%llu B", i);
  return buff;  
}

void setverbose(bool value) {
    verbose_enabled = value;
}

bool getverbose(void) {
    return verbose_enabled;
}

void verbose(const char *msg, const char *file, const int line, const char *func) {
    time_t now;
    struct tm *timeinfo;
    time(&now);
    timeinfo = localtime(&now);

    if (verbose_enabled) {
        fprintf(stderr, "%.2d:%.2d:%.2d | %s:%d | %s | DEBUG: %s\n", timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec, file, line, func, msg);
    }
}

char* uint64tob(uint64_t i) {
  static char output[65];

  snprintf(output, sizeof(output), BYTE_TO_BINARY_PATTERN""BYTE_TO_BINARY_PATTERN""BYTE_TO_BINARY_PATTERN""BYTE_TO_BINARY_PATTERN""BYTE_TO_BINARY_PATTERN""BYTE_TO_BINARY_PATTERN""BYTE_TO_BINARY_PATTERN""BYTE_TO_BINARY_PATTERN"",
  BYTE_TO_BINARY((unsigned char)(i>>56)), BYTE_TO_BINARY((unsigned char)(i>>48)), BYTE_TO_BINARY((unsigned char)(i>>40)), BYTE_TO_BINARY((unsigned char)(i>>32)), BYTE_TO_BINARY((unsigned char)(i>>24)), BYTE_TO_BINARY((unsigned char)(i>>16)), BYTE_TO_BINARY((unsigned char)(i>>8)), BYTE_TO_BINARY((unsigned char)i));

  return output;
}
char* uint32tob(uint32_t i) {
    static char output[33];

    snprintf(output, sizeof(output), BYTE_TO_BINARY_PATTERN""BYTE_TO_BINARY_PATTERN""BYTE_TO_BINARY_PATTERN""BYTE_TO_BINARY_PATTERN, 
    BYTE_TO_BINARY((unsigned char)(i>>24)), BYTE_TO_BINARY((unsigned char)(i>>16)), BYTE_TO_BINARY((unsigned char)(i>>8)), BYTE_TO_BINARY((unsigned char)i));
    return output;
}
char* uint16tob(uint16_t i) {
  static char output[17];

  snprintf(output, sizeof(output), BYTE_TO_BINARY_PATTERN""BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY((unsigned char)(i>>8)), BYTE_TO_BINARY((unsigned char)i));

  return output;
}
char* uint8tob(uint8_t i) {
  static char output[9] = {'\0'};

  snprintf(output, sizeof(output), BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY((unsigned char)i));

  return output;
}

#endif