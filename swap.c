#include "push_swap.h"

t_piles *swap_a(t_piles *piles)
{
	t_list *tmp_lst;
	int		tmp;

	if (piles->list_a == NULL || piles->list_a->next == NULL)
		return (piles);
	tmp_lst = piles->list_a;
	tmp = tmp_lst->next->content;
	tmp_lst->next->content = tmp_lst->content;
	tmp_lst->content = tmp;
	fill_buffer_str("sa\n",piles);
	return (piles);
}

t_piles *swap_b(t_piles *piles)
{
	t_list *tmp_lst;
	int		tmp;

	if (piles->list_b == NULL || piles->list_b->next == NULL)
		return (piles);
	tmp_lst = piles->list_b;
	tmp = tmp_lst->next->content;
	tmp_lst->next->content = tmp_lst->content;
	tmp_lst->content = tmp;
	fill_buffer_str("sb\n",piles);
	return (piles);
}