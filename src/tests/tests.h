#ifndef SRC_TEST_H
#define SRC_TEST_H

#include <check.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "../backend/parsing.h"

Suite *test_matrix(void);
Suite *test_parsing(void);
Suite *test_transformations(void);

#endif
