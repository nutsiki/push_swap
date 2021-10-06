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

int 	find_min(t_piles *piles, int i, int j)
{
	int min;
	t_list *tmp;

	tmp = piles->sorted;
	min = tmp->content;
	while (i++ < j)
	{
		if (min > tmp->content)
			min = tmp->content;
		tmp = tmp->next;
	}
	return (min);
}

int	find_2min(t_piles *piles, int i, int j, int min)
{
	int min_2;
	t_list *tmp;

	tmp = piles->sorted;
	if (tmp->content != min)
		min_2 = tmp->content;
	else
		min_2 = tmp->next->content;
	while (i++ < j)
	{
		if (tmp->content != min && min_2 > tmp->content)
			min_2 = tmp->content;
		tmp = tmp->next;
	}
	return (min_2);
}

int find_sens(t_list **tmp, int *min, int *min_2)
{
	int i;

	i = 0;
	while ((*tmp) && ((*tmp)->content != *min && (*tmp)->content != *min_2))
	{
		(*tmp) = (*tmp)->next;
		i++;
	}
	if ((*tmp) && (*tmp)->content == *min)
		*min = *min_2;
	return (i);
}

void	sort_four(t_piles *piles)
{
	t_list *tmp;
	int i;
	int min;

	min = find_min(piles, 0, 4);
	tmp = piles->list_a;
	i = find_sens(&tmp, &min, &min);
	if (i < 2)
		while (i--)
			rotate_a(piles);
	else
		while (i++ < 4)
			reverse_a(piles);
	push_b(piles);
	return ;
}

void	before_push_b(t_piles *piles, int size)
{
	int min;
	int min_2;
	t_list *tmp;
	int i;

	tmp = piles->list_a;
	min = find_min(piles,0, size);
	min_2 = find_2min(piles,0,size, min);
	i = find_sens(&tmp, &min, &min_2);
	if (i <= 2)
		while (i--)
			rotate_a(piles);
	else if (i)
		while (i++ < 5)
			reverse_a(piles);
	push_b(piles);
	i = find_sens(&tmp, &min, &min);
	if (i && i <= 2)
		while (--i)
			rotate_a(piles);
	else if (i)
		while (i++ < 5)
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
		sort_four(piles);
		sort_three(piles);
		push_a(piles);
	}
	else if (piles->size == 5)
	{
		before_push_b(piles, 5);
		push_b(piles);
		if (piles->list_b->content < piles->list_b->next->content)
			swap_b(piles);
		sort_three(piles);
		push_a(piles);
		push_a(piles);
	}
}