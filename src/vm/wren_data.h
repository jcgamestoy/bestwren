#pragma once

#include "../include/wren.h"
#include "wren_primitive.h"

typedef struct {
  void *data;
  size_t size;
  size_t index;
}wrenData;

WrenForeignClassMethods wrenDataBindForeignClass(WrenVM* vm, const char* module, const char* className);
void wrenDataBindMethods(WrenVM* vm, ObjClass* dataClass);