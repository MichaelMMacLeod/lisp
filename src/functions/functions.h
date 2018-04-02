#ifndef INCLUDE_FUNCTIONS_FUNCTIONS_H
#define INCLUDE_FUNCTIONS_FUNCTIONS_H

struct sexpr *eval_sexpr(struct sexpr *s, struct map *package);

#include "backend/backend.h"
#include "frontend/frontend.h"

#endif
