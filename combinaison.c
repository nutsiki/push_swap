#include <stdio.h>
#include "push_swap.h"

void			*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*d;
	char		*s;

	d = (char *)dest;
	s = (char *)src;
	if (n == 0 || dest == src)
		return (dest);
	while (n--)
		*d++ = *s++;
	return (dest);
}

t_piles 	*more_size(t_piles *piles)
{
	char *new_buff;

	new_buff = piles->action;
	piles->length += BUFFER_SIZE;
	piles->action = (char*)calloc(sizeof(char), piles->length);
	if(!(piles->action))
		return (NULL);
	piles->action = ft_memcpy(piles->action, new_buff, piles->pos);
	free((void*)new_buff);
	return (piles);
}

t_piles 	*fill_buffer(t_piles *piles, char action)
{
	if (piles->pos + 1 >= piles->length)
		return (fill_buffer(more_size(piles), action));
	*(piles->action + piles->pos) = action;
	(piles->pos)++;
	return (piles);
}

int		fill_buffer_str(char *str, t_piles *piles)
{
	while (*str)
	{
		fill_buffer(piles, *str);
		if (!piles)
			return (-1);
		str++;
	}
	return (1);
}

t_piles *swap_a(t_piles *piles)
{
	t_list *tmp_lst;
	int		tmp;

	if (piles->list_a == NULL || piles->list_a->next == NULL)
		return (piles);
	tmp_lst = piles->list_a;
	tmp = tmp_lst->next->content;
	tmp_lst->next->content = tmp_lst->content;
	tmp_lst->content = tmp;
	fill_buffer_str("sa\n",piles);
	return (piles);
}

t_piles *swap_b(t_piles *piles)
{
	t_list *tmp_lst;
	int		tmp;

	if (piles->list_b == NULL || piles->list_b->next == NULL)
		return (piles);
	tmp_lst = piles->list_b;
	tmp = tmp_lst->next->content;
	tmp_lst->next->content = tmp_lst->content;
	tmp_lst->content = tmp;
	fill_buffer_str("sb\n",piles);
	return (piles);
}

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
	fill_buffer_str("ra\n",piles);
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
	fill_buffer_str("rb\n",piles);
	return (piles);
}

t_piles 	*push_b(t_piles *piles)
{
	t_list *tmp_lsta;
	t_list *new;
	t_list *tmp_lstb;
	int		tmp;

	if (piles->list_a == NULL)
		return (piles);
	new = NULL;
	tmp_lsta = piles->list_a;
	tmp_lstb = NULL;
	tmp = piles->list_a->content;
	if (piles->list_b)
		tmp_lstb = piles->list_b;
	new = ft_lstnew(tmp);
	piles->list_b = new;
	piles->list_b->next = tmp_lstb;
	piles->list_a = tmp_lsta->next;
	fill_buffer_str("pa\n",piles);
	return (piles);
}

t_piles 	*push_a(t_piles *piles)
{
	t_list *tmp_lsta;
	t_list *new;
	t_list *tmp_lstb;
	int		tmp;

	if (piles->list_b == NULL)
		return (piles);
	new = NULL;
	tmp_lstb = piles->list_b;
	tmp_lsta = NULL;
	tmp = piles->list_b->content;
	if (piles->list_a)
		tmp_lsta = piles->list_a;
	new = ft_lstnew(tmp);
	piles->list_a = new;
	piles->list_a->next = tmp_lsta;
	piles->list_b = tmp_lstb->next;
	fill_buffer_str("pb\n",piles);
	return (piles);
}

t_piles 	*reverse_a(t_piles *piles)
{
	t_list *tmp_lsta;
	t_list *new;
	t_list *tmp;
	t_list *previous;

	if (piles->list_a == NULL || piles->list_a->next == NULL)
		return (piles);
	tmp_lsta = piles->list_a;
	while (tmp_lsta->next != NULL)
	{
		if (tmp_lsta->next->next == NULL)
			previous = tmp_lsta;
		tmp_lsta = tmp_lsta->next;
	}
	tmp = tmp_lsta;
	previous->next = NULL;
	tmp_lsta = NULL;
	new = piles->list_a;
	piles->list_a = tmp;
	piles->list_a->next = new;
	fill_buffer_str("rra\n",piles);

	return (piles);
}

t_piles 	*reverse_b(t_piles *piles)
{
	t_list *tmp_lstb;
	t_list *new;
	t_list *tmp;
	t_list *previous;

	if (piles->list_b == NULL || piles->list_b->next == NULL)
		return (piles);
	tmp_lstb = piles->list_b;
	while (tmp_lstb->next != NULL)
	{
		if (tmp_lstb->next->next == NULL)
			previous = tmp_lstb;
		tmp_lstb = tmp_lstb->next;
	}
	tmp = tmp_lstb;
	previous->next = NULL;
	tmp_lstb = NULL;
	new = piles->list_b;
	piles->list_b = tmp;
	piles->list_b->next = new;
	fill_buffer_str("rrb\n",piles);
	return (piles);
}


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

void	sort_five(t_piles *piles)
{
	t_list *tmp;
	int i;

	i = piles->size;
	tmp = piles->list_a;
	while (tmp->content < piles->list_b->content && --piles->size)
	{
		rotate_a(piles);
		tmp = tmp->next;
	}
	push_a(piles);
	rotate_a(piles);
	piles->size--;
	while (tmp->content < piles->list_b->content && --piles->size)
	{
		rotate_a(piles);
		tmp = tmp->next;
	}
	push_a(piles);
	if (!piles->size)
		rotate_a(piles);
	else
		while (i-- > piles->size)
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
//static int	ft_strlen(const char *s)
//{
//	size_t	i;
//
//	i = 0;
//	while (*s++)
//		i++;
//	return (i);
//}
//
//static char				*ft_checkspace(char *str)
//{
//	while (*str == '\n' || *str == '\f' || *str == '\r'
//		   || *str == '\t' || *str == '\v' || *str == ' ')
//		str++;
//	return (str);
//}
//
//static int				ft_checkull(const char *str, int j)
//{
//	int					i;
//	char				*tab;
//	int					k;
//	int					m;
//
//	m = 0;
//	tab = "18446744073709551615";
//	i = ft_strlen(str);
//	k = ft_strlen(tab);
//	if (i < k)
//		return (1);
//	while (m++ < i)
//	{
//		if (!(str[m] >= '0' && str[m] <= '9'))
//			return (1);
//		if (str[m] > tab[m] && j == 1)
//			return (-1);
//		if (str[m] > tab[m] && j == -1)
//			return (0);
//	}
//	return (1);
//}

//static int						ft_atoi(const char *str)
//{
//	int					j;
//	int					k;
//	unsigned long long	nb;
//
//	j = 1;
//	nb = 0;
//	str = ft_checkspace((char*)str);
//	if (*str == '-')
//		j = -1;
//	if (*str == '+' || *str == '-')
//		str++;
//	if ((k = ft_checkull(str, j)) != 1)
//		return (k);
//	while (*str && *str >= '0' && *str <= '9')
//	{
//		nb = (nb * 10) + (*str - '0');
//		if (nb > 9223372036854775807 && j == 1)
//			return (-1);
//		if (nb > 9223372036854775807 && j == -1)
//			return (0);
//		str++;
//	}
//	return ((int)(nb * j));
//}
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
	printf("vi\n");

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
	tab = ft_calloc(6, sizeof(int));

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


static int		ft_sizen(long long n)
{
	int i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		i++;
	while (n)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static char		*ft_fillup(long long nb, char *str)
{
	char t;

	if (nb < 0)
	{
		*str++ = '-';
		nb = nb * -1;
	}
	if (nb > 9)
		str = ft_fillup(nb / 10, str);
	t = (nb % 10 + '0');
	*str = t;
	return (++str);
}

char			*ft_itoa(int n)
{
	char		*str;
	char		*str1;
	long long	nlong;

	nlong = n;
	if (!(str = (char *)malloc(sizeof(char) * (ft_sizen(nlong) + 1))))
		return (NULL);
	str1 = str;
	str = ft_fillup(nlong, str);
	*str = '\0';
	return (str1);
}

int	push_swap(int i, int j, int k, int l, int m)
{
	t_piles *piles;

	piles = init_piles();
//	if (argc < 2)
//		exit(0);
//	piles->list_a = fill_list(argc, argv);
	char *argv[5] = {ft_itoa(i), ft_itoa(j), ft_itoa(k), ft_itoa(l), ft_itoa(m)};

	printf("yo %s \n", argv[0]);
	printf("yo %s \n", argv[1]);
	printf("yo %s \n", argv[2]);
	printf("yo %s \n", argv[3]);
	printf("yo %s \n", argv[4]);
	piles->list_a = fill_list(6, argv);

	piles->size = ft_lstsize(piles->list_a);
	piles->sorted = sort_piles(piles);
	if (is_already_sorted(piles))
		return (1);
	if (piles->size <= 5)
		sort_below_five(piles);
	afficherlist(piles->list_a, 'a');
	printf("%s \n", piles->action);
	return (1);



}

int	main()
{

	int n = 5;
	int comb = 1;
	int i  = 0;

	while (n)
		comb *= n--;
	while (i < 5)
	{
		int j   = 0;

		while (j < 5)
		{
			int k = 0;

			while (k < 5)
			{
				int l = 0;

				while (l < 5)
				{
					int m  = 0;

					while (m < 5)
					{

						push_swap(i, j, k, l, m);
						m++;

					}
					l++;
				}
				k++;
			}
			j++;
		}
		i++;
	}

	return (1);
}
