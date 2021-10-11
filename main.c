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
	piles->action = ft_calloc(sizeof(char),BUFFER_SIZE);
	piles->pos = 0;
	piles->length = BUFFER_SIZE;
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

int		ft_strcmp(const char *s1, const char *s2)
{
	unsigned char *ps1;
	unsigned char *ps2;

	ps1 = (unsigned char *)s1;
	ps2 = (unsigned char *)s2;
	while (*ps1 != '\0' && *ps2 != '\0' && *ps1 == *ps2)
	{
		ps1++;
		ps2++;
	}
	return (*ps1 - *ps2);
}

char	*ft_strcpy(char *dest, const char *src)
{
	char *p;
	char *srcc;

	p = dest;
	srcc = (char *)src;
	while (*srcc)
		*p++ = *srcc++;
	*p = '\0';
	return (dest);
}

void	write_action(int k, int j, char buffer[4])
{
	int i;
	char action[1];

	i = 0;
	action[0] = '\0';
	if (!k && j == 1)
		write(1,buffer,4);
	else
	{
		while (k-- && j-- && buffer[i] != 'a' && buffer[i] != 'b')
		{
			action[0] = buffer[i];
			write(1, action, 1);
			i++;

		}
		write(1, action, 1);
	}
	write(1, "\n", 1);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char			*ph;
	char			*pn;
	char			*p;
	unsigned int	i;

	ph = (char *)haystack;
	p = (char *)haystack;
	if (*needle == 0)
		return (p);
	while (len--)
	{
		ph = p;
		pn = (char *)needle;
		while (*ph == *pn && i--)
		{
			pn++;
			ph++;
			if (*pn == '\0')
				return (p);
		}
		i = len;
		p++;
	}
	return (NULL);
}

char	*ft_strchr(const char *s, int c)
{
	char *ps;

	ps = (char*)s;
	while (1)
	{
		if (*ps == (char)c)
			return (ps);
		if (!*ps)
			break ;
		ps++;
	}
	return (NULL);
}

int		ft_strncmp(const char *s1, const char *s2, unsigned int n)
{
	unsigned int	i;
	unsigned char	*ps1;
	unsigned char	*ps2;

	ps1 = (unsigned char *)s1;
	ps2 = (unsigned char *)s2;
	i = 0;
	if (n == 0)
		return (0);
	while (ps1[i] != '\0' && ps2[i] != '\0' && i < n - 1 && ps1[i] == ps2[i])
	{
		i++;
	}
	return (ps1[i] - ps2[i]);
}

void	write_fusion(int cpt, int old_cpt, char *buffer)
{
	char action;

	action = *buffer;
	if (*buffer == *(buffer + 1))
	{
		while (cpt && old_cpt)
		{
			write(1,"rrr\n", 4);
			cpt--;
			old_cpt--;
		}
		if (*(buffer + 2) == 'a')
		{
			while (cpt--)
				write(1, buffer, 4);
			while (old_cpt--)
				write(1, "rrb\n",4);
		}
		else
		{
			while (cpt--)
				write(1, buffer, 4);
			while (old_cpt--)
				write(1, "rra\n",4);
		}
	}
	else if (action == 's')
	{
		while (cpt && old_cpt)
		{
			write(1, "ss\n", 3);
			cpt--;
			old_cpt--;
		}
		if (*(buffer + 1) == 'a')
		{
			while (cpt--)
				write(1, buffer, 3);
			while (old_cpt--)
				write(1, "sb\n",3);
		}
		else
		{
			while (cpt--)
				write(1, buffer, 3);
			while (old_cpt--)
				write(1, "sa\n",3);
		}
	}
	else if (action == 'r')
	{
		while (cpt && old_cpt)
		{
			write(1, "rr\n", 3);
			cpt--;
			old_cpt--;
		}
		if (*(buffer + 1) == 'a')
		{
			while (cpt--)
				write(1, buffer, 3);
			while (old_cpt--)
				write(1, "rb\n",3);
		}
		else
		{
			while (cpt--)
				write(1, buffer, 3);
			while (old_cpt--)
				write(1, "ra\n",3);
		}
	}
}

void	clean_action(t_piles *piles)
{
	int cpt;
	int old_cpt;
	char *previous;
	char *str;

	cpt = 1;
	old_cpt = 0;
	str = NULL;
	previous = NULL;
//	piles->action = "rra\npb\nra\npb\nrb\npb\nrra\nrra\nrra\nrrb\npb\nrra\nrra\nrra\nrra\nrra\nrra\nrra\nrra\nrra\nrb\npb\nrra\nrra\nrra\nrra\nrra\nrra\nrra\nrra\npb\nrra\nrra\nrrb\nrrb\npb";
	while (*piles->action)
	{
//		printf("cpt vaut %d old vaut %d str vaut %s\n", cpt, old_cpt, str);
		if (str && !ft_strncmp(piles->action, str, 3))
			cpt++;
		else if (str && !old_cpt && (*str != *piles->action || *piles->action == 'p'))
		{
//			printf("str vaut %s\n", str);
			while (cpt--)
				write(1, str, ft_strlen(str));
			cpt = 1;
		}
		else if (str && (strncmp(piles->action, str, 3) == -1 || strncmp(piles->action, str, 3) == 1) && (*piles->action == *str))
		{
			old_cpt = cpt;
			cpt = 1;
		}
		else if (old_cpt)
		{
			write_fusion(cpt, old_cpt, str);
			old_cpt = 0;
			cpt = 1;
		}
		if (str && *str)
			free(str);
		previous = ft_calloc(sizeof(char), 5);
		str = previous;
		while (piles->action && *piles->action != '\n')
			*previous++ = *piles->action++;
		*previous = '\n';
		piles->action++;
		if (!*piles->action)
			while (cpt--)
				write(1, str, 3);
	}
	return ;
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
	else if (piles->size == 100)
		algo_100(piles);
	else if (piles->size == 500)
		algo_500(piles);
//	printf("action\n%s\n", piles->action);
	clean_action(piles);
//	afficherlist(piles->list_a, 'a');
}