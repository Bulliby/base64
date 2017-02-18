#include "libft.h"
#include <stdlib.h>

static char table [] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

unsigned int		decode(char *str, char *ret)
{
	size_t			mask;
	int				i;
	int				j;
	size_t			x;
	unsigned int	retparts;
	
	mask = 0x0000FF;
	i = 0;
	x = 0;
	while (str[i])
	{
		if (!((i + 1) % 4))
		{
			retparts = 0;	
			for (j = i - 3; j != i + 1; j++)
			{
				(ft_strpos(table, str[j]) != -1) ? retparts |=\
				 ft_strpos(table, str[j]) : retparts | 0;	
				if (i != j)
					retparts <<= 6;
			}
			for (j = 2; j != -1; j--)
			{
				ret[x * 3 + j] = retparts & mask;
				retparts >>= 8;
			}
			x++;
		}
		i++;
	}
}

static void			one_more_to_encode(size_t tmp, char *ret,\
					size_t mask, size_t pos)
{
	tmp >>= 4;
	//tmp <<= 4;
	ret[pos * 4 + 1] = table[tmp & mask];
	tmp >>= 6;
	ret[pos * 4] = table[tmp & mask];
	ret[pos * 4 + 2] = '=';
	ret[pos * 4 + 3] = '=';
}

static void			two_more_to_encode(size_t tmp, char *ret,\
					size_t mask, size_t pos)
{
	tmp >>= 6;
	//tmp <<= 2;
	ret[pos * 4 + 2] = table[tmp & mask];
	tmp >>= 6;
	ret[pos * 4 + 1] = table[tmp & mask];
	tmp >>= 6;
	ret[pos * 4] = table[tmp & mask];
	ret[pos * 4 + 3] = '=';
}

void				encode(char *str, char *ret)
{
	size_t			i;
	size_t			mask;
	size_t			x;
	int				j;
	size_t			tmp;

	i = 0;
	mask = 0x00003F;
	x = 0;
	tmp = 0;
	while (str[i])
	{
		tmp |= str[i];
		if (!((i + 1) % 3))
		{
			for (j = 3; j != -1; j--)
			{
				ret[x * 4 + j] = table[tmp & mask];
				tmp >>= 6;
			}
			x++;
			tmp = 0;
		}
		tmp <<= 8;
		i++;
	}	
	if (i - x * 3 == 1)
		one_more_to_encode(tmp, ret, mask, x);
	if (i - x * 3 == 2)
		two_more_to_encode(tmp, ret, mask, x);
}	
