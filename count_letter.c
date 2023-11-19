#include "main.h"

/**
 * long_to_string - converts a varber to a string.
 * @varber: varber to be converted in a string.
 * @string: buffer to save the varber as string.
 * @base: base to convert varber
 *
 * Return: No return value.
 */
void long_to_string(long varber, char *string, int base)
{
    int index = 0, inNegative = 0;
    long cc = varber;
    char letters[] = {"0123456789abcdef"};

    if (cc == 0)
        string[index++] = '0';

    if (string[0] == '-')
        inNegative = 1;

    while (cc)
    {
        if (cc < 0)
            string[index++] = letters[-(cc % base)];
        else
            string[index++] = letters[cc % base];
        cc /= base;
    }
    if (inNegative)
        string[index++] = '-';

    string[index] = '\0';
    str_reverse(string);
}

/**
 * _atoi - convert a string to an integer.
 *
 * @s: pointer to str origen.
 * Return: int of string or 0.
 */
int _atoi(char *s)
{
    int sign = 1;
    unsigned int var = 0;
    /*1- analisys sign*/
    while (!('0' <= *s && *s <= '9') && *s != '\0')
    {
        if (*s == '-')
            sign *= -1;
        if (*s == '+')
            sign *= +1;
        s++;
    }

    /*2 - extract the varber */
    while ('0' <= *s && *s <= '9' && *s != '\0')
    {

        var = (var * 10) + (*s - '0');
        s++;
    }
    return (var * sign);
}

/**
 * count_characters - count the coincidences of character in string.
 *
 * @string: pointer to original string.
 * @character: string with  chars to be counted
 * Return: count of string or 0.
 */
int count_characters(char *string, char *character)
{
    int i = 0, count = 0;

    for (; string[i]; i++)
    {
        if (string[i] == character[0])
            count++;
    }
    return (count);
}


