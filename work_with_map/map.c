#include "../cub3D.h"

char	**make_map(t_list **head, int size)
{
	char	  **map = ft_calloc(size + 1, sizeof(char *));
	int		  i = -1;
	t_list	*tmp = *head;


	while (tmp)
	{
		map[++i] = ft_strdup(tmp->content);
		tmp = tmp->next;
	}
	ft_lstclear(head, &free);
	i = -1;
	return (map);
}

char **ft_read_map(char *argv1)
{
	char *str = NULL;
	t_list *head = NULL;
	const int fd = open(argv1, O_RDONLY);

	while (get_next_line(fd, &str))
	{
		ft_lstadd_back(&head, ft_lstnew(str));
		str = NULL;
	}
	close(fd);
	ft_lstadd_back(&head, ft_lstnew(str));
	str = NULL;
	return (make_map(&head, ft_lstsize(head)));
}
