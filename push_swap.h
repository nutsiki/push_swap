#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <errno.h>
# include <stdio.h>

typedef struct		s_list
{
	int				content;
	struct s_list	*next;
}					t_list;

typedef struct		s_piles
{

	t_list			*list_a;
	t_list			*list_b;
	t_list 			*sorted;
	int 			size;
}					t_piles;

void 	afficherlist(t_list *list, char i);


t_list	*ft_lstnew(int content);


t_piles 	*push_b(t_piles *piles);
t_piles 	*push_a(t_piles *piles);

t_piles		*rotate_a(t_piles *piles);
t_piles		*rotate_b(t_piles *piles);


t_piles				*swap_a(t_piles *piles);
t_piles				*swap_b(t_piles *piles);

t_piles 	*reverse_a(t_piles *piles);
t_piles 	*reverse_b(t_piles *piles);

void	sort_below_five(t_piles *piles);



#endif