#include "push_swap.h"

void			*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*d;
	char		*s;

	d = (char *)dest;
	s = (char *)src;
	if (n == 0 || dest == src)
		return (dest);
	while (n--)
		*d++ = *s++;
	return (dest);
}

t_piles 	*more_size(t_piles *piles)
{
	char *new_buff;

	new_buff = piles->action;
	piles->length += BUFFER_SIZE;
	piles->action = (char*)ft_calloc(sizeof(char), piles->length);
	if(!(piles->action))
		return (NULL);
	piles->action = ft_memcpy(piles->action, new_buff, piles->pos);
	free((void*)new_buff);
	return (piles);
}

t_piles 	*fill_buffer(t_piles *piles, char action)
{
	if (piles->pos + 1 >= piles->length)
		return (fill_buffer(more_size(piles), action));
	*(piles->action + piles->pos) = action;
	(piles->pos)++;
	return (piles);
}

int		fill_buffer_str(char *str, t_piles *piles)
{
	while (*str)
	{
		fill_buffer(piles, *str);
		if (!piles)
			return (-1);
		str++;
	}
	return (1);
}