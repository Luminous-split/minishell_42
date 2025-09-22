/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soemin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 22:06:38 by soemin            #+#    #+#             */
/*   Updated: 2025/05/08 22:03:20 by soemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*result;
	t_list	*tmp;

	if (lst == NULL || f == NULL)
		return (NULL);
	result = NULL;
	while (lst)
	{
		tmp = ft_lstnew((*f)(lst->content));
		if (!tmp)
		{
			ft_lstclear(&result, del);
			return (NULL);
		}
		ft_lstadd_back(&result, tmp);
		tmp = tmp->next;
		lst = lst->next;
	}
	return (result);
}
/*
#include <stdio.h>
void *to_upper_dup(void *content)
{
    char *str = (char *)content;
    char *new_str = strdup(str);
    if (!new_str)
        return NULL;

    for (int i = 0; new_str[i]; i++)
        if (new_str[i] >= 'a' && new_str[i] <= 'z')
            new_str[i] -= 32;

    return new_str;
}

void del(void *content)
{
    free(content);
}

void print_list(t_list *lst)
{
    while (lst)
    {
        printf("%s -> ", (char *)lst->content);
        lst = lst->next;
    }
    printf("NULL\n");
}

int main(void)
{
    t_list *node1 = ft_lstnew(strdup("one"));
    t_list *node2 = ft_lstnew(strdup("two"));
    t_list *node3 = ft_lstnew(strdup("three"));
    node1->next = node2;
    node2->next = node3;
    printf("Original list:\n");
    print_list(node1);
    t_list *mapped = ft_lstmap(node1, to_upper_dup, del);
    printf("Mapped list (to upper):\n");
    print_list(mapped);
    ft_lstclear(&node1, del);
    ft_lstclear(&mapped, del);
    return (0);
}
*/
