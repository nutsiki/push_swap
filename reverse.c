#include "push_swap.h"

t_piles 	*reverse_a(t_piles *piles)
{
	t_list *tmp_lsta;
	t_list *new;
	t_list *tmp;
	t_list *previous;

	if (piles->list_a == NULL || piles->list_a->next == NULL)
		return (piles);
	tmp_lsta = piles->list_a;
	while (tmp_lsta->next != NULL)
	{
		if (tmp_lsta->next->next == NULL)
			previous = tmp_lsta;
		tmp_lsta = tmp_lsta->next;
	}
	tmp = tmp_lsta;
	previous->next = NULL;
	tmp_lsta = NULL;
	new = piles->list_a;
	piles->list_a = tmp;
	piles->list_a->next = new;
	fill_buffer_str("rra\n",piles);

	return (piles);
}

t_piles 	*reverse_b(t_piles *piles)
{
	t_list *tmp_lstb;
	t_list *new;
	t_list *tmp;
	t_list *previous;

	if (piles->list_b == NULL || piles->list_b->next == NULL)
		return (piles);
	tmp_lstb = piles->list_b;
	while (tmp_lstb->next != NULL)
	{
		if (tmp_lstb->next->next == NULL)
			previous = tmp_lstb;
		tmp_lstb = tmp_lstb->next;
	}
	tmp = tmp_lstb;
	previous->next = NULL;
	tmp_lstb = NULL;
	new = piles->list_b;
	piles->list_b = tmp;
	piles->list_b->next = new;
	fill_buffer_str("rrb\n",piles);
	return (piles);
}