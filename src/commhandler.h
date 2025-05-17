#pragma once
#ifndef COMMHANDLER_H
#define COMMHANDLER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "argparse.h"
#include "commands/exit.h"
#include "commands/type.h"
#include "commands/exec.h"
#include "commands/pwd.h"
#include "commands/cd.h"
#include "commands/echo.h"

int commhandler(char *input);

#endif