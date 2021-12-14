#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "binary_aux.h"

int bin_to_decimal(const char *bin_s_ptr)
{
    int result = 0;
    int count = 1;
    int len = strlen(bin_s_ptr);
    if (len == 0)
    {
        return 0;
    }

    if (len < 0)
    {
        fprintf(stderr, "No string was given or was empty");
        errno = EINVAL;
        return -1;
    }

    if (len > (int)(sizeof(int) * 8))
    {
        fprintf(stderr, "String bits exceeds the integer size");
        errno = EINVAL;
        return -1;
    }

    for (int i = len - 1; i >= 0; i--)
    {
        char var = bin_s_ptr[i];

        if (var == '1')
        {
            result += count;
        }
        else if (var != '0')
        {
            fprintf(stderr, "Invalid values found in given string");
            errno = EINVAL;
            return -1;
        }
        count = count * 2;
    }

    return result;
}

int is_bit_n_set(int input, int bit_n)
{
    return (input & (1 << bit_n)) != 0;
}

int bit_n_to_zero(int input, int bit_to_zero)
{
    return input &= ~(1 << bit_to_zero);
}

int bit_n_to_one(int input, int bit_to_one)
{
    return input |= (1 << bit_to_one);
}

int flip_n_bit(int input, int flip)
{
    return input ^ (1 << flip);
}

void bits_to_string(char *dst, int dst_len, int bits)
{
    memset(dst, 0, dst_len);

    for (int i = 0; i < dst_len - 1; i++)
    {
        dst[i] = is_bit_n_set(bits, dst_len - i - 2) ? '1' : '0';
    }
}

int count_ones(int input)
{
    int counter = 0;

    for (int i = 0; i < (int)sizeof(int); i++)
    {
        counter += is_bit_n_set(input, i);
    }

    return counter;
}

#ifdef TEST
/**
 * @brief Usage
 *
 */
void main(void)
{
    char *val = "10110011011";
    printf("%s -> %d\n", val, bin_to_decimal(val));

    printf("\n");

    int check_bits = 04;
    int check_bit = 2;
    printf("Bits: %d\n", check_bits);
    printf("Bit '%d' is set: %s\n", check_bit, is_bit_n_set(check_bits, check_bit) ? "true" : "false");

    printf("\n");
    int z_bits = 07;
    int unset_bit = 0;
    printf("Bits: %d\n", z_bits);
    printf("Changed: %d\n", bit_n_to_zero(z_bits, unset_bit));

    printf("\n");
    int o_bits = 04;
    int set_bit = 1;
    printf("Bits: %d\n", o_bits);
    printf("Changed: %d\n", bit_n_to_one(o_bits, set_bit));

    printf("\n");
    int count_ones_bits = 06;
    printf("Bits: %d\n", count_ones_bits);
    printf("Ones: %d\n", count_ones(count_ones_bits));

    printf("\n");
    int to_flip = 012; // 001 010
    int flip_bit = 0;
    printf("To flip: %d\n", to_flip);
    to_flip = flip_n_bit(to_flip, flip_bit);
    printf("Flipped: %d\n", to_flip);
    printf("Flipped: %d\n", flip_n_bit(to_flip, flip_bit));

    printf("\n");
    int bits_to_show = 012; // 001 010
    char out[9];
    bits_to_string(out, 9, bits_to_show);
    printf("Show: %s\n", out);
}

#endif