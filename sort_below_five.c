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

static int		ft_lstsize(t_list *lst)
{
	int			i;

	i = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

t_list *find_sens(t_list *tmp, int size, t_piles *piles)
{
	int i;

	i = 0;


	afficherlist(piles->list_a, 'a');
	afficherlist(piles->list_b, 'b');
	while (tmp->content < piles->list_b->content && tmp->next != NULL)
	{
		printf("tmp content %d -- b content %d\n", tmp->content, piles->list_b->content);
		tmp = tmp->next;
		i++;
	}
	printf("yo\n");

	printf("apres bouce tmp content %d -- b content %d\n", tmp->content, piles->list_b->content);
	printf("i vaut %d et size vaut %d\n", i, size);
	if (i > (size/2) || tmp->next == NULL)
		while ((size - i))
		{
			printf("reverse_a\n");
			reverse_a(piles);
			i++;
		}
	else
		while (i)
		{
			printf("rotate_a\n");
			rotate_a(piles);
			i--;
		}
	return (tmp);

}

void	sort_five(t_piles *piles)
{
	t_list *tmp;
	int i;

	i = 0;
	tmp = piles->list_a;
	tmp = find_sens(tmp, ft_lstsize(tmp), piles);
	push_a(piles);
	rotate_a(piles);
	tmp = find_sens(tmp, ft_lstsize(tmp) , piles);
	push_a(piles);
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
		i++;
	}
	while (--i)
		rotate_a(piles);
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