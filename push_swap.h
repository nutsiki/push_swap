#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <errno.h>

typedef struct		s_list
{
	int				content;
	struct s_list	*next;
}					t_list;

typedef struct		s_piles
{

	t_list			*list_a;
	t_list			*list_b;
	t_list			*list_c;
	int 			size;
}					t_piles;

t_list	*ft_lstnew(int content);


t_piles 	*push_b(t_piles *piles);
t_piles 	*push_a(t_piles *piles);

t_piles		*rotate_a(t_piles *piles);
t_piles		*rotate_b(t_piles *piles);


t_piles				*swap_a(t_piles *piles);
t_piles				*swap_b(t_piles *piles);


#endif