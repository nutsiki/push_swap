#include "push_swap.h"

int	get_index_sorted(t_piles *piles, int i)
{
	t_list *tmp;

	tmp = piles->sorted;
	while (i--)
		tmp = tmp->next;
	return (tmp->content);
}

void	algo_100(t_piles *piles)
{
	t_list *tmp;

	tmp = piles->list_a;
	while (tmp->content >= get_index_sorted(piles, 19))
		tmp = tmp->next;

	return ;
}