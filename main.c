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

void 	afficherlistab(t_piles *piles, int i)
{
	t_list *list_a;
	t_list *list_b;

	list_a = piles->list_a;
	list_b = piles->list_b;

	while (list_a != NULL)
	{
		printf("%d pile a %d\n", i, list_a->content);
		list_a = list_a->next;
	}
	while (list_b != NULL)
	{
		printf("%d pile b %d\n", i, list_b->content);
		list_b = list_b->next;
	}
	printf("\n ____________________ \n");
}

int	main(int argc, char **argv)
{
	t_piles *piles;

	piles = init_piles();
	if (argc < 2)
		exit(0);
	piles->list_a = fill_list(argc, argv);
	piles->size = ft_lstsize(piles->list_a);
//	piles = swap_a(piles);
//	piles = push_b(piles);
	piles = rotate_a(piles);
	afficherlistab(piles, 1);
	piles = push_b(piles);
//	afficherlistab(piles, 2);
//	piles = swap_b(piles);
	piles = push_b(piles);
	afficherlistab(piles, 2);
	piles = rotate_b(piles);
	afficherlistab(piles, 3);

}