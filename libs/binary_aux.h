#ifndef _BINARY_AUX_H_
#define _BINARY_AUX_H_

/**
 * @brief Converts binary value to decimal
 *
 * @result if len < 0 result is 0 else the number is returned
 *
 * @param bin_s_ptr
 * @return int
 */
int bin_to_decimal(const char *bin_s_ptr);

/**
 * @brief Checks if the n bit of given bits is set
 *
 * @param input
 * @param bit_n
 * @return int
 */
int is_bit_n_set(int input, int bit_n);

/**
 * @brief Sets the n bit to zero
 *
 * @param input
 * @param bit_to_zero
 * @return int
 */
int bit_n_to_zero(int input, int bit_to_zero);

/**
 * @brief Sets the n bit to one
 *
 * @param input
 * @param bit_to_one
 * @return int
 */
int bit_n_to_one(int input, int bit_to_one);

/**
 * @brief Counts the occurences of 1 in given binary
 *
 * @param input
 * @return int
 */
int count_ones(int input);

/**
 * @brief Flip the given n bit
 * 
 * @param input 
 * @param flip 
 * @return int 
 */
int flip_n_bit(int input, int flip);

/**
 * @brief Prints the bit into a char buffer
 * 
 * @param dst 
 * @param dst_len 
 * @param bits 
 * @return int 
 */
void bits_to_string(char *dst, int dst_len, int bits);

/**
 * @brief Examples
 * 
 */

// char out[9];
// bits_to_string(out, 9, bin_to_decimal("11001"));
// printf("Out: %s\n", out);

#endif