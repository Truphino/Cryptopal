#include "stdio.h"
#include "stdlib.h"
#include "string.h"

int  hexpos(char hex)
{
  char  hex_data[16] = "0123456789abcdef";
  int   i;

  i = 0;
  while (hex_data[i])
  {
    if (hex == hex_data[i])
      return (i);
    i++;
  }
  return (0);
}

char  *alloc_result(char const *to_convert)
{
  size_t  len;
  char    *base_64;

  len = strlen(to_convert);
  if (len % 6 > 0)
    len += 6 - (len % 6);
  len = (len / 6 * 4) + 1;
  base_64 = (char *)malloc(sizeof(char) * len);
  memset(base_64, 0, len);

  return (base_64);
}

char  *put_base_64_char(char *base_64, int data, int padding_equal)
{
  char    base_64_char[64] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
  size_t  offset;

  offset = strlen(base_64);
  base_64[offset] = base_64_char[(data & (63 << 18)) >> 18];
  base_64[offset + 1] = base_64_char[(data & (63 << 12)) >> 12];
  base_64[offset + 2] = (padding_equal - 1 > 0) ? '=' : base_64_char[(data & (63 << 6)) >> 6];
  base_64[offset + 3] = (padding_equal > 0) ? '=' : base_64_char[(data & (63))];

  return (base_64);
}

char  *hexto64(char const *to_convert)
{
  char    *base_64;
  int     len;
  int     i;
  int     hex_value;
  int     data;

  base_64 = alloc_result(to_convert);
  len = (int)strlen(to_convert);
  printf("%d\n", len);
  while (len > 0)
  {
    i = 0;
    data = 0;
    hex_value = 0;

    while (i < 6)
    {
      if (i >= len)
        hex_value = 0;
      else
        hex_value = hexpos(to_convert[i]);
      data += (hex_value & 15) << (4 * (5 - i));
      i++;
    }
    base_64 = put_base_64_char(base_64, data, 3 - (len / 2));
    len -= 6;
    if (len > 0)
      to_convert += 6;
  }

  return (base_64);
}

int main(void)
{
  char to_convert[] = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
  char *res;
  res = hexto64(to_convert);
  printf("%s\n", res);

  return (0);
}
