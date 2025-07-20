#include "../../include/libasm_bonus.h"

void ft_list_remove_if_bonus_wrapper(t_list **begin_list, void *data_ref, int (*cmp)(), void (*free_fct)(void *)) {
    ft_list_remove_if(begin_list, data_ref, cmp, free_fct);
}
