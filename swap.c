#include "push_swap.h"

t_piles *swap_a(t_piles *piles)
{
	t_list *tmp_lst;
	int		tmp;

	tmp_lst = piles->list_a;
	if (tmp_lst == NULL || tmp_lst->next == NULL)
		return (piles);
	tmp = tmp_lst->next->content;
	tmp_lst->next->content = tmp_lst->content;
	tmp_lst->content = tmp;
	return (piles);
}

t_piles *swap_b(t_piles *piles)
{
	t_list *tmp_lst;
	int		tmp;

	tmp_lst = piles->list_b;
	if (tmp_lst == NULL || tmp_lst->next == NULL)
		return (piles);
	tmp = tmp_lst->next->content;
	tmp_lst->next->content = tmp_lst->content;
	tmp_lst->content = tmp;
	return (piles);
}