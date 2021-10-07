#include "push_swap.h"

int	get_index_sorted(t_piles *piles, int i)
{
	t_list *tmp;

	tmp = piles->sorted;
	while (i--)
		tmp = tmp->next;
	return (tmp->content);
}

int 	find_max(t_piles *piles, int i, int j)
{
	int max;
	t_list *tmp;

	if (!piles->list_b)
		return (0);
	tmp = piles->list_b;
	max = tmp->content;
	while (tmp && i++ < j)
	{
		if (max < tmp->content)
			max = tmp->content;
		tmp = tmp->next;
	}
	return (max);
}

int 	hold_first(t_piles *piles, int index)
{
	t_list *tmp;
	int i;
	int j;
	int index_sorted;

	i = 0;
	j = -1;
	index_sorted = get_index_sorted(piles, index);
	tmp = piles->list_a;

	while (tmp)
	{
		if (tmp->content <= index_sorted)
		{
			j = i;
			break ;
		}
		tmp = tmp->next;
		i++;
	}
	return (j);
}
int 	hold_second(t_piles *piles, int index)
{
	t_list *tmp;
	int i;
	int j;
	int index_sorted;

	i = 0;
	j = 0;
	index_sorted = get_index_sorted(piles, index);
	tmp = piles->list_a;
	while (tmp)
	{
		if (tmp->content <= index_sorted)
			j = i;
		tmp = tmp->next;
		i++;
	}
	return (j);
}

void	prepare_b(t_piles *piles, int size, int max)
{
	t_list *tmp;
	int i;
	int previous;

	if (!piles->list_b->next->next && (piles->list_b->content < piles->list_b->next->content))
		swap_b(piles);
	tmp = piles->list_b;
	previous = ft_lstlast(piles->list_b)->content;
	i = 0;
	while (tmp && ((piles->list_a->content < tmp->content) || (piles->list_a->content > previous)))
	{
		previous = tmp->content;
		tmp = tmp->next;
		i++;
	}
	if (!tmp && i == size)
	{
		while (piles->list_b->content != max)
			reverse_b(piles);
		push_b(piles);
		return ;
	}
	if (i <= size/2)
		while (i--)
			rotate_b(piles);
	else if (i)
		while (i++ < size)
			reverse_b(piles);
	push_b(piles);

}

void	make_chunk(t_piles *piles, int size, int index)
{
	int i;
	int j;
	int size_b;

	i = hold_first(piles, index);
	j = hold_second(piles, index);
	size_b = ft_lstsize(piles->list_b);
	if ((size - j) > i)
		while (i--)
			rotate_a(piles);
	else
		while (j++ < size)
			reverse_a(piles);
	i = find_max(piles, 0, size_b);
	if (!piles->list_b || !piles->list_b->next)
	{
		push_b(piles);
		return ;
	}
	prepare_b(piles, size_b, i);

}

void 	clean_b(t_piles *piles, int max, int size)
{
	t_list *tmp;
	int i;

	i = 0;

	tmp = piles->list_b;

	while (tmp && tmp->content != max)
	{
		tmp = tmp->next;
		i++;
	}
	if (i < size/2)
		while (i--)
			rotate_b(piles);
	else
		while (i++ < size)
			reverse_b(piles);
	return ;
}

void	algo_100(t_piles *piles)
{
	int i;

	i = 0;
	while (i++ < 20)
		make_chunk(piles, ft_lstsize(piles->list_a), 19);
	clean_b(piles, find_max(piles, 0, 20), 20);
	while (i++ < 41)
		make_chunk(piles, ft_lstsize(piles->list_a), 39);
	clean_b(piles, find_max(piles, 0, 40), 40);
	while (i++ < 62)
		make_chunk(piles, ft_lstsize(piles->list_a), 59);
	clean_b(piles, find_max(piles, 0, 60), 60);
	while (i++ < 83)
		make_chunk(piles, ft_lstsize(piles->list_a), 79);
	clean_b(piles, find_max(piles, 0, 80), 80);
	while (i++ < 101)
		make_chunk(piles, ft_lstsize(piles->list_a), 96);
	clean_b(piles, find_max(piles, 0, 97), 97);
	sort_three(piles);
	while (piles->list_b)
		push_a(piles);





	return ;
}