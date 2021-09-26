#include "push_swap.h"
#include <stdio.h>

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (*s++)
		i++;
	return (i);
}

void	ft_bzero(void *s, size_t n)
{
	char *p;

	p = (char *)s;
	while (n-- > 0)
		p[n] = 0;
}

void	*ft_calloc(size_t count, size_t size)
{
	char *p;
	char *pp;

	if (!(p = (char*)malloc(count * size)))
		return (NULL);
	count *= size;
	pp = p;
	while (count--)
		*p++ = 0;
	return (pp);
}

static char				*ft_checkspace(char *str)
{
	while (*str == '\n' || *str == '\f' || *str == '\r'
		   || *str == '\t' || *str == '\v' || *str == ' ')
		str++;
	return (str);
}

static int				ft_checkull(const char *str, int j)
{
	int					i;
	char				*tab;
	int					k;
	int					m;

	m = 0;
	tab = "18446744073709551615";
	i = ft_strlen(str);
	k = ft_strlen(tab);
	if (i < k)
		return (1);
	while (m++ < i)
	{
		if (!(str[m] >= '0' && str[m] <= '9'))
			return (1);
		if (str[m] > tab[m] && j == 1)
			return (-1);
		if (str[m] > tab[m] && j == -1)
			return (0);
	}
	return (1);
}

int						ft_atoi(const char *str)
{
	int					j;
	int					k;
	unsigned long long	nb;

	j = 1;
	nb = 0;
	str = ft_checkspace((char*)str);
	if (*str == '-')
		j = -1;
	if (*str == '+' || *str == '-')
		str++;
	if ((k = ft_checkull(str, j)) != 1)
		return (k);
	while (*str && *str >= '0' && *str <= '9')
	{
		nb = (nb * 10) + (*str - '0');
		if (nb > 9223372036854775807 && j == 1)
			return (-1);
		if (nb > 9223372036854775807 && j == -1)
			return (0);
		str++;
	}
	return ((int)(nb * j));
}

char	*ft_putstr_fd_err(char *s, int fd)
{
	if (!s && fd < 0)
		return (NULL);
	write(fd, s, ft_strlen(s));
	exit(1);
	return (NULL);
}

int		ft_isdigit(int c)
{
	return ((c >= 48) && (c <= 57));
}

t_list	*ft_lstnew(int content)
{
	t_list *n;

	if (!(n = (t_list*)malloc(sizeof(t_list))))
		return (NULL);
	n->content = content;
	n->next = NULL;
	return (n);
}

int check_list(int i, char **argv, int *tab)
{
	int j;
	int nb;

	j = 0;
	while (ft_isdigit(argv[i][j]) || ((argv[i][j] == '+' || argv[i][j] == '-') && j == 0))
		j++;
	if ((size_t)j != ft_strlen(argv[i]))
		ft_putstr_fd_err("NOT DIGIT", 2);
	nb = ft_atoi(argv[i]);
	j = -1;
	while (tab[++j])
		if (tab[j] == nb)
			ft_putstr_fd_err("DOUBLON", 2);
	return (nb);
}

t_list	*fill_list(int argc, char **argv)
{
	int i;
	int *tab;
	t_list *new;
	t_list *tmp;

	i = argc - 1;
	new = NULL;
	tmp = NULL;
	tab = ft_calloc(argc - 1, sizeof(int));

	while (i > 0)
	{
		tab[(argc - 1) - i] = check_list(i, argv, tab);
		new = ft_lstnew(tab[(argc - 1) - i]);
		new->next = tmp;
		tmp = new;
		i--;
	}
	return (tmp);
}

int		ft_lstsize(t_list *lst)
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

t_piles	*init_piles(void)
{
	t_piles *piles;

	piles = (t_piles*)malloc(sizeof(t_piles));
	if (!piles)
		exit(0);
	ft_bzero(piles, sizeof(t_piles));
	return (piles);
}

void 	afficherlist(t_list *list, char i)
{
	t_list *list_tmp;
	int cpt;

	list_tmp = list;
	cpt = 0;
	while (list_tmp != NULL)
	{
		printf("element[%d] de list_%c = %d\n", cpt, i, list_tmp->content);
		list_tmp = list_tmp->next;
		cpt++;
	}
	printf("-------------------------------\n");
}

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list *ll;

	if (!alst || !new)
		return ;
	if (!*alst)
	{
		*alst = new;
		new->next = NULL;
		return ;
	}
	ll = ft_lstlast(*alst);
	ll->next = new;
	new->next = NULL;
}

t_list *fill_piles_c(t_piles *piles)
{
	t_list *c;
	t_list *tmp_a;

	c = NULL;
	tmp_a = piles->list_a;
	while (tmp_a != NULL)
	{
		ft_lstadd_back(&c, ft_lstnew(tmp_a->content));
		tmp_a = tmp_a->next;
	}
	return (c);
}

t_list *sort_piles(t_piles *piles)
{
	t_list *c;
	t_list *tmp;
	int i;
	int tmp_nb;

	c = fill_piles_c(piles);
	i = -1;
	while (i)
	{
		i = -1;
		tmp = c;
		while (tmp->next != NULL)
		{
			if (tmp->content > tmp->next->content)
			{
				tmp_nb = tmp->content;
				tmp->content = tmp->next->content;
				tmp->next->content = tmp_nb;
				i--;
			}
			tmp = tmp->next;
		}
		i++;
	}
	return (c);
}

int	is_already_sorted(t_piles *piles)
{
	t_list *tmp_a;
	t_list *tmp_c;

	tmp_a = piles->list_a;
	tmp_c = piles->sorted;
	while (tmp_a->next != NULL)
	{
		if (tmp_a->content == tmp_c->content)
		{
			tmp_a = tmp_a->next;
			tmp_c = tmp_c->next;
		}
		else
			return(0);
	}
	return (1);
}


int	main(int argc, char **argv)
{
	t_piles *piles;

	piles = init_piles();
	if (argc < 2)
		exit(0);
	piles->list_a = fill_list(argc, argv);
	piles->size = ft_lstsize(piles->list_a);
	piles->sorted = sort_piles(piles);
	if (is_already_sorted(piles))
		return (1);
	if (piles->size <= 5)
		sort_below_five(piles);
	afficherlist(piles->list_a, 'a');



}