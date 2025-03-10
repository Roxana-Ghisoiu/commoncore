/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_remove_if.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 14:10:28 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/02/15 14:10:37 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

typedef struct s_list
{
    struct s_list *next;
    void *data;
} t_list;

void ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)())
{
    t_list *curent = *begin_list;
    t_list *prev = NULL;
    t_list *temp;

    while (curent)
    {
        if (cmp(curent->data, data_ref) == 0)
        {
            temp = curent->next;
            free(curent);
            curent = temp;
            if (prev)
                prev->next = temp;
            else
                *begin_list = temp;
        }
        else
        {
            prev = curent;
            curent = curent->next;
        }
    }
}


int cmp(void *a, void *b)
{
    return (*(int *)a - *(int *)b);
}

void print_list(t_list *list)
{
    while (list)
    {
        printf("%d -> ", *(int *)(list->data));
        list = list->next;
    }
    printf("NULL\n");
}

void free_list(t_list *list)
{
    t_list *temp;
    while (list)
    {
        temp = list->next;
        free(list);
        list = temp;
    }
}
/*
int main()
{
    int *a = malloc(sizeof(int));
    int *b = malloc(sizeof(int));
    int *c = malloc(sizeof(int));
    int data_ref = 2;

    *a = 1;
    *b = 2;
    *c = 3;

    t_list *n1 = malloc(sizeof(t_list));
    t_list *n2 = malloc(sizeof(t_list));
    t_list *n3 = malloc(sizeof(t_list));

    n1->data = a;
    n1->next = n2;

    n2->data = b;
    n2->next = n3;

    n3->data = c;
    n3->next = NULL;

    t_list *list = n1;

    printf("Lista inițială:\n");
    print_list(list);

    ft_list_remove_if(&list, &data_ref, cmp);

    printf("Lista după ft_list_remove_if:\n");
    print_list(list);

    // Eliberăm toată memoria rămasă
    free_list(list);
    free(a);
    free(b);
    free(c);

    return 0;
}
*/
