#include "push_swap.h"

void	sort_three(t_piles *piles)
{
	if (piles->list_a->content < piles->list_a->next->content &&
		piles->list_a->next->content < piles->list_a->next->next->content)
		return ; // 1 < 2 < 3
	else if (piles->list_a->content < piles->list_a->next->content &&
		piles->list_a->content < piles->list_a->next->next->content)
	{
		swap_a(piles);
		rotate_a(piles); //1 < 3 < 2
	}
	else if (piles->list_a->content < piles->list_a->next->content)
		reverse_a(piles); //2 < 3 < 1
	else if (piles->list_a->content > piles->list_a->next->content &&
			 piles->list_a->next->content > piles->list_a->next->next->content)
	{
		swap_a(piles);
		reverse_a(piles); //3 < 2 < 1
	}
	else if (piles->list_a->content > piles->list_a->next->content &&
			 piles->list_a->content > piles->list_a->next->next->content)
		rotate_a(piles); // 3 < 1 < 2
	else
		swap_a(piles); // 2 < 1 < 3
	return ;
}

void	sort_four(t_piles *piles)
{
	t_list *tmp;
	int i;

	i = 0;
	tmp = piles->list_a;
	while (tmp->content < piles->list_b->content && --piles->size)
	{
		rotate_a(piles);
		tmp = tmp->next;
		i++;
	}
	push_a(piles);
	while (i--)
		reverse_a(piles);
}

void	sort_five(t_piles *piles)
{
	t_list *tmp;
	int i;

	i = piles->size;
	tmp = piles->list_a;
	while (tmp->content < piles->list_b->content && --piles->size)
	{
		rotate_a(piles);
		tmp = tmp->next;
	}
	push_a(piles);
	rotate_a(piles);
	piles->size--;
	while (tmp->content < piles->list_b->content && --piles->size)
	{
		rotate_a(piles);
		tmp = tmp->next;
	}
	push_a(piles);
	if (!piles->size)
		rotate_a(piles);
	else
		while (i-- > piles->size)
			reverse_a(piles);
	return ;
}

void	sort_below_five(t_piles *piles)
{
	if (piles->size == 2)
		swap_a(piles);
	else if (piles->size == 3)
		sort_three(piles);
	else if (piles->size == 4)
	{
		push_b(piles);
		sort_three(piles);
		sort_four(piles);
	}
	else if (piles->size == 5)
	{
		push_b(piles);
		push_b(piles);
		if (piles->list_b->content > piles->list_b->next->content)
			swap_b(piles);
		sort_three(piles);
		sort_five(piles);
	}
}