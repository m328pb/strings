#include "strings.h"

uint16_t str_find(char *str, const char *find, uint8_t start) {
  uint8_t len = str_len(str);
  if (start >= len)
    return 0;
  uint8_t find_len = str_len(find);
  for (uint8_t i = start; i < len; i++) {
    if (str[i] == find[0]) {
      for (uint8_t j = 0; j < find_len; j++) {
        if (str[i + j] != find[j])
          break;
        if (j == find_len - 1)
          return i;
      }
    }
  }
  return 0;
}

uint16_t str_find(char *str, const char *find) {
  return str_find(str, find, 0);
}

/**
 * Copies a part of a string to a destination buffer.
 *
 * This function copies a part of a string to a destination buffer, starting
 * at the given start index and ending at the given end index. The copied
 * string is null-terminated.
 *
 * @param dest A pointer to the destination buffer. Must be large enough to
 *             hold the substring.
 * @param str A pointer to the string to be cut.
 * @param start The starting index of the substring to be copied.
 * @param end The ending index of the substring to be copied.
 */
void str_cut(char *dest, char *str, uint8_t start, uint8_t end) {
  uint8_t len = end - start;
  for (int i = 0; i < len; i++)
    dest[i] = str[start + i];
  dest[len] = 0x00;
}

/**
 * Fills a string with a character.
 *
 * This function fills a string with a character until the string is
 * len characters long. The string is null-terminated.
 *
 * @param str A pointer to the string to be filled. Must be large enough to hold
 * len characters + 1.
 * @param len The length of the string. Without the null character.
 * @param c The character to fill the string with.
 */
void str_set(char *str, uint8_t len, char c) {
  for (int i = 0; i < len; i++) {
    str[i] = c;
  }
  str[len] = 0x00;
}

/**
 * Fills a memory block with a specified value.
 *
 * This function sets each byte in a memory block to a specified value.
 *
 * @param mem A pointer to the memory block to be filled.
 * @param len The number of bytes to fill in the memory block.
 * @param c The value to fill the memory block with.
 */

void mem_set(uint8_t *mem, uint16_t len, uint8_t c) {
  for (uint16_t i = 0; i < len; i++)
    mem[i] = c;
}

void mem_set(uint16_t *mem, uint16_t len, uint16_t c) {
  for (uint16_t i = 0; i < len; i++)
    mem[i] = c;
}

/**
 * Calculates the length of a string.
 *
 * This function calculates the length of a string until a null character
 * is found. The length is the number of characters until the null character
 *
 * @param str A pointer to the string to be measured.
 * @returns The length of the string, in characters. Not including the null
 * character.
 */
uint8_t str_len(const char *str) {
  uint8_t len = 0;
  while (*str++)
    len++;
  return len;
}

/**
 * Compares two strings for equality.
 *
 * This function compares two null-terminated strings to determine if they
 * are equal. It first checks if the lengths of the two strings are the same.
 * If not, it returns `false`. If the lengths are equal, it compares each
 * character in the strings. If any character differs, the function returns
 * `false`. If all characters match, the function returns `true`.
 *
 * @param str1 A pointer to the first string to be compared.
 * @param str2 A pointer to the second string to be compared.
 * @returns `true` if the strings are equal, `false` otherwise.
 */
bool str_compare(const char *str1, const char *str2) {
  uint8_t len1 = str_len(str1);
  uint8_t len2 = str_len(str2);
  if (len1 != len2) {
    return false;
  };
  for (int i = 0; i < len1; i++) {
    if (str1[i] != str2[i]) {
      return false;
    };
  };
  return true;
}

/**
 * Copies a string to a destination buffer.
 *
 * This function copies the content of the input string to the destination
 * buffer up to dest_len characters. If the input string is longer than
 * dest_len, it will be truncated to fit the destination buffer. The
 * destination string is null-terminated.
 *
 * @param dest A pointer to the destination buffer.
 * @param dest_len The maximum length of the destination buffer including the
 * null terminator.
 * @param str A pointer to the input string to be copied. Must be terminated
 * with '\0'.
 */
void str_copy(char *dest, uint8_t dest_len, const char *str) {
  uint8_t len = str_len(str);
  if (len > dest_len)
    len = dest_len; // Not enough space in the output buffer

  for (int i = 0; i < len; i++)
    dest[i] = *str++;

  dest[len] = 0x00;
}

/**
 * Copies a block of memory to a destination buffer.
 *
 * This function copies the content of the input memory block to the destination
 * buffer up to dest_len bytes. If the input memory block is longer than
 * dest_len, it will be truncated to fit the destination buffer.
 *
 * @param dest A pointer to the destination buffer. Must be large enough to hold
 * str_len bytes.
 * @param src_len The maximum length of the src buffer.
 * @param src A pointer to the input memory block to be copied.
 */
void mem_copy(uint8_t *dest, uint8_t src_len, const uint8_t *src) {
  for (int i = 0; i < src_len; i++)
    dest[i] = *src++;
}

void str_add(char *dest, uint8_t dest_len, const char *str) {
  uint8_t len = str_len(str);
  uint8_t start = str_len(dest);
  uint8_t end = start + len;
  if (end > dest_len)
    end = dest_len; // Not enough space in the output buffer

  for (int i = start; i < end; i++)
    dest[i] = *str++;

  dest[dest_len] = 0x00;
}

/**
 * Convert a float to a string, with a given number of decimal places.
 *
 * This function does not use sprintf or similar functions, as they
 * are not available for float by default (see know-how.ipynb).
 * Instead, it does the conversion manually, so it is smaller and
 * faster.
 *
 * @param num The number to convert
 * @param str The string to store the result in
 * @param len The length of the string, including null terminator
 * @param precision The number of decimal places to use
 */
void ftos(float num, char *str, uint8_t len, uint8_t precision) {
  // sprintf family do not recognize float by defoult (see know-how.ipynb)
  // mmka sure that num is in the range
  // 999 > num > 0
  // len is total length of str, including dot and null terminator
  // len must be at least 2
  // can be used to convert ints, when precision == 0
  if (len < 2) {
    for (int i = 0; i < len; i++)
      str[i] = 0x00;
    return;
  };

  uint8_t dot;
  precision != 0 ? dot = 1 : dot = 0;
  if (num < 0 || num > 999) {
    str[0] = '<';
    str[1] = 0x00;
    return;
  };

  char *str_start = str;

  // Extract the integer part
  uint16_t intPart = static_cast<uint16_t>(num);
  num -= intPart;

  // Convert integer part to string, max 3 digits
  uint8_t intLen = 0; // number of int digits
  char temp[3];       // Temporary buffer
  char *p = temp;     // Pointer to temporary buffer
  do {
    *p++ = '0' + intPart % 10;
    intPart /= 10;
    intLen++;
  } while (intPart > 0);

  if (intLen > len - precision - dot - 1) // one for dot, one for null
  {
    // Not enough space in the output buffer
    str_start[0] = '?';
    str_start[1] = 0x00;
    return;
  }

  // Reverse the string and copy to the output
  while (p != temp)
    *str++ = *(--p);

  if (precision == 0) { // no decimal part
    *str++ = 0x00;      // add null terminator
    return;
  }

  // Add decimal point
  *str++ = '.';

  // Extract the fractional part and convert to string
  for (int i = 0; i < precision; i++) {
    num *= 10;
    uint8_t digit = static_cast<uint8_t>(num);
    *str++ = '0' + digit;
    num -= digit;
  }

  // Null-terminate the string
  *str = 0x00;
}

uint16_t stoi(char *str) {
  uint16_t num = 0;
  while (*str != 0) {
    num *= 10;
    num += *str - '0';
    str++;
  }
  return num;
}
