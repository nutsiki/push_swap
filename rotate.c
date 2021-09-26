#include "push_swap.h"

t_piles	*rotate_a(t_piles *piles)
{
	t_list *tmp_lst;
	int		tmp;

	tmp_lst = piles->list_a;
	if (tmp_lst == NULL || tmp_lst->next == NULL)
		return (piles);
	tmp = tmp_lst->content;
	piles->list_a = tmp_lst->next;
	while (tmp_lst->next != NULL)
		tmp_lst = tmp_lst->next;
	tmp_lst->next = ft_lstnew(tmp);
	write(1,"ra\n",3);
	return (piles);
}

t_piles	*rotate_b(t_piles *piles)
{
	t_list *tmp_lst;
	int		tmp;

	tmp_lst = piles->list_b;
	if (tmp_lst == NULL || tmp_lst->next == NULL)
		return (piles);
	tmp = tmp_lst->content;
	piles->list_b = tmp_lst->next;
	while (tmp_lst->next != NULL)
		tmp_lst = tmp_lst->next;
	tmp_lst->next = ft_lstnew(tmp);
	write(1,"rb\n",3);
	return (piles);
}