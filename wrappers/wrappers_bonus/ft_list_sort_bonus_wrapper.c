#include "../../include/libasm_bonus.h"

void ft_list_sort_bonus_wrapper(t_list **begin_list, int (*cmp)()) {
    ft_list_sort(begin_list, cmp);
}
