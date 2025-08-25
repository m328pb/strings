#pragma once
#include <avr/io.h>

uint16_t str_find(char *str, const char *find);
uint16_t str_find(char *str, const char *find, uint8_t start);
void str_cut(char * dest, char *str, uint8_t start, uint8_t end);
void str_set(char *str, uint8_t len, char c);
void mem_set(uint8_t *mem, uint16_t len, uint8_t c);
void mem_set(uint16_t *mem, uint16_t len, uint16_t c);
uint8_t str_len(const char *str);
bool str_compare(const char *str1, const char *str2);
void str_add(char *dest, uint8_t dest_len, const char *str);
void str_copy(char *dest,uint8_t dest_len ,const char *str);
void mem_copy(uint8_t *dest, uint8_t dest_len, const uint8_t *str);
void ftos(float num, char *str, uint8_t len, uint8_t precision);
uint16_t stoi(char *str);

/**
 * Converts a binary number to a string.
 * 
 * This function takes a binary number and converts it into a string, 
 * writing the result into the provided string buffer. The binary number
 * is written in big-endian order into the string buffer, with the most
 * significant bit first. The string buffer is null-terminated.
 * 
 * @tparam T The type of the binary number. This should be an unsigned type.
 * @param num The binary number to be converted.
 * @param str A pointer to the destination buffer where the string will be written.
 */
template <typename T>
void btos(T num, char *str)
{
    uint8_t len = sizeof(T) * 8;
    for (int i = 0; i < len; i++)
    {
        str[i] = (num & (1<< i)) ? '1' : '0';
        str[len] = 0;
    }
}

/**
 * Concatenates multiple strings into a destination buffer.
 * 
 * This function takes a destination buffer and a variable number of string 
 * arguments, concatenating each string into the destination buffer. The 
 * concatenation stops when the destination buffer is full or all strings 
 * are concatenated. The destination buffer is null-terminated.
 * 
 * @tparam Args Variadic template to accept multiple string arguments.
 * @param dest A pointer to the destination buffer where the strings will 
 *             be concatenated.
 * @param dest_len The length of the destination buffer.
 * @param args The strings to be concatenated into the destination buffer.
 */
template <typename... Args>
void str_concat(char *dest, uint8_t dest_len, Args... args)
{
    ((str_add(dest, dest_len, args)), ...);
}
