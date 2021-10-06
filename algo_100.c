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
	while (i++ < j)
	{
		if (max < tmp->content)
			max = tmp->content;
		tmp = tmp->next;
	}
	return (max);
}

void	prepare_b(t_piles *piles, int size)
{
	t_list *tmp;
	int i;
	int j;
	int max;

	tmp = piles->list_b;
	i = 0;
	max = find_max(piles, 0, size);
	printf("cou\n");
	while (tmp && (piles->list_a->content < tmp->content))
	{
		if (tmp->content == max)
			j = i;
		printf("a->content %d < %d tmp->content\n", piles->list_a->content, tmp->content);
		tmp = tmp->next;
		i++;
	}
	if (!tmp)
		i = j;
	afficherlist(piles->list_b, 'b');

	printf("i vaut %d\n", i);
	if (i <= size/2)
		while (i--)
		{

			printf("je rotate et %d passe derriere\n", piles->list_b->content);
			rotate_b(piles);
		}
	else if (i)
		while (i++ < size)
			reverse_b(piles);
	push_b(piles);
	afficherlist(piles->list_b, 'b');

}
int 	hold_first(t_piles *piles, int index_sorted)
{
	t_list *tmp;
	int i;
	int j;

	i = 0;
	j = 0;
	tmp = piles->list_a;

	while (tmp)
	{
		if (tmp->content < index_sorted)
		{
			j = i;
			break ;
		}
		tmp = tmp->next;
		i++;
	}
	return (j);
}
int 	hold_second(t_piles *piles, int index_sorted)
{
	t_list *tmp;
	int i;
	int j;

	i = 0;
	j = 0;
	tmp = piles->list_a;
	while (tmp)
	{
		if (tmp->content < index_sorted)
		{
			j = i;
		}
		tmp = tmp->next;
		i++;
	}
	return (j);
}

void	make_chunk(t_piles *piles, int size, int index)
{
	int index_sorted;
	int i;
	int j;

	index_sorted = get_index_sorted(piles, index);
	i = hold_first(piles, index_sorted);
	j = hold_second(piles, index_sorted);
	if ((size - j) > i)
		while (i--)
			rotate_a(piles);
	else
		while (j++ < size)
			reverse_a(piles);
	prepare_b(piles, ft_lstsize(piles->list_b));
}
void	algo_100(t_piles *piles)
{
	int i;

	i = 0;
	while (i++ < 20)
	{
		make_chunk(piles, ft_lstsize(piles->list_a), 19);

	}


	return ;
}