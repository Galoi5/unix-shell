#pragma once
#ifndef TYPE_H
#define TYPE_H

#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "utils.h"

void _type(char **args);
void _is_shell_builtin(char *cmd);

#endif