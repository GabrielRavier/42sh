/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Absolute value of float
*/

#include "my.h"

float my_fabsf(float x)
{
    return (x < 0) ? -x : x;
}
