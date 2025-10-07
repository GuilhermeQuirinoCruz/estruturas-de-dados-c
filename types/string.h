#pragma once

int string_size(void *string);
void *string_new(void *data);
void string_clear(void *string);
void string_free(void *string);
int string_compare(void *str1, void *str2);
void string_print(void *string);