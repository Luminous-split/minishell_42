/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soemin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 22:05:53 by soemin            #+#    #+#             */
/*   Updated: 2025/05/08 22:01:19 by soemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!lst || !f)
		return ;
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}
/*
#include <stdio.h>
void to_upper(void *content)
{
    char *str = (char *)content;
    for (int i = 0; str[i]; i++)
        if (str[i] >= 'a' && str[i] <= 'z')
            str[i] -= 32;
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
    t_list *node1 = ft_lstnew(strdup("hello"));
    t_list *node2 = ft_lstnew(strdup("world"));
    t_list *node3 = ft_lstnew(strdup("libft"));
    node1->next = node2;
    node2->next = node3;
    printf("Before ft_lstiter:\n");
    print_list(node1);
    ft_lstiter(node1, to_upper);
    printf("After ft_lstiter:\n");
    print_list(node1);
    t_list *tmp;
    while (node1)
    {
        tmp = node1->next;
        free(node1->content);
        free(node1);
        node1 = tmp;
    }
    return (0);
}
*/
