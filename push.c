#include "push_swap.h"

t_piles 	*push_b(t_piles *piles)
{
	t_list *tmp_lsta;
	t_list *new;
	t_list *tmp_lstb;
	int		tmp;

	if (piles->list_a == NULL)
		return (piles);
	new = NULL;
	tmp_lsta = piles->list_a;
	tmp_lstb = NULL;
	tmp = piles->list_a->content;
	if (piles->list_b)
		tmp_lstb = piles->list_b;
	new = ft_lstnew(tmp);
	piles->list_b = new;
	piles->list_b->next = tmp_lstb;
	piles->list_a = tmp_lsta->next;
	fill_buffer_str("pb\n",piles);
	return (piles);
}

t_piles 	*push_a(t_piles *piles)
{
	t_list *tmp_lsta;
	t_list *new;
	t_list *tmp_lstb;
	int		tmp;

	if (piles->list_b == NULL)
		return (piles);
	new = NULL;
	tmp_lstb = piles->list_b;
	tmp_lsta = NULL;
	tmp = piles->list_b->content;
	if (piles->list_a)
		tmp_lsta = piles->list_a;
	new = ft_lstnew(tmp);
	piles->list_a = new;
	piles->list_a->next = tmp_lsta;
	piles->list_b = tmp_lstb->next;
	fill_buffer_str("pa\n",piles);
	return (piles);
}