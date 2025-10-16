/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaruyam <hmaruyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 12:00:00 by hmaruyam          #+#    #+#             */
/*   Updated: 2025/10/11 02:43:31 by hmaruyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_overflow(unsigned long long result, int digit, int sign)
{
	unsigned long long	limit;

	if (sign == 1)
		limit = LLONG_MAX;
	else
		limit = (unsigned long long)LLONG_MAX + 1;
	if (result > limit / 10 || (result == limit / 10
			&& (unsigned long long)digit > limit % 10))
		return (1);
	return (0);
}

int	execute_conversion(char *str, int sign, unsigned char *last_status)
{
	unsigned long long	result;
	int					digit;

	result = 0;
	if (!ft_isdigit(*str))
		return (1);
	while (ft_isdigit(*str))
	{
		digit = *str - '0';
		if (is_overflow(result, digit, sign))
			return (1);
		result = result * 10 + digit;
		str++;
	}
	while (is_whitespace(*str))
		str++;
	if (*str != '\0')
		return (1);
	*last_status = (unsigned char)(result * sign);
	return (0);
}

int	strtouc_and_validate(char *str, unsigned char *last_status)
{
	int	sign;

	sign = 1;
	while (is_whitespace(*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	return (execute_conversion(str, sign, last_status));
}
