#pragma once
#ifndef EXEC_H
#define EXEC_H

#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

int _exec(char **args);

#endif