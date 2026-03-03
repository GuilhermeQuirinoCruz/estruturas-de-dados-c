#pragma once

int integer_size();
void *integer_new(void *value);
void integer_clone(void *src, void *dest);
void integer_clone_deep(void *src, void *dest);
void integer_clear(void *integer);
void integer_free(void *integer);
int integer_compare(void *int1, void *int2);
void integer_print(void *integer);