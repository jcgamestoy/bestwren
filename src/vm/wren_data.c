#include "wren_data.h"

static void dataAllocate(WrenVM* vm)
{
  wrenData* d = (wrenData*)wrenSetSlotNewForeign(vm, 0, 0, sizeof(wrenData));
  if(wrenGetSlotCount(vm) == 1) {
    d->size = 256;
    d->data = malloc(d->size);
  } else {
    d->size = wrenGetSlotDouble(vm, 1);
    d->data=malloc(d->size);
  }

  d->index = 0;
}

static void dataFinallizer(void *data) {
  wrenData *d=(wrenData*)data;
  if(d->data) free(d->data);
}

WrenForeignClassMethods wrenDataBindForeignClass(WrenVM* vm, const char* module, const char* className) {
  WrenForeignClassMethods methods;
  methods.allocate = dataAllocate;
  methods.finalize = dataFinallizer;
  return methods;
}

DEF_PRIMITIVE(data_add)
{
  if (!validateString(vm, args[1], "Right operand")) return false;
  
  ObjForeign* f=AS_FOREIGN(args[0]);  
  wrenData* d=(wrenData*)f->data;

  ObjString* string = AS_STRING(args[1]);

  // Corner case: Can't parse an empty string.
  if (string->length == 0) RETURN_NULL;

  const size_t l=d->index + string->length;
  if(l > d->size) {
    d->size<<=1;
    d->size=(d->size>l?d->size:l);
    d->data = realloc(d->data, d->size);
  }

  memcpy(d->data+d->index, string->value, string->length);
  d->index+=string->length;
  
  RETURN_OBJ(f);
}

DEF_PRIMITIVE(data_toString) {
  ObjForeign* f=AS_FOREIGN(args[0]);  
  wrenData* d=(wrenData*)f->data;
  
  RETURN_VAL(OBJ_VAL(wrenNewStringFromData(vm,d->data,d->index)));
}

DEF_PRIMITIVE(data_length) {
  ObjForeign* f=AS_FOREIGN(args[0]);  
  wrenData* d=(wrenData*)f->data;
  RETURN_NUM(d->index);
}

DEF_PRIMITIVE(data_capacity) {
  ObjForeign* f=AS_FOREIGN(args[0]);  
  wrenData* d=(wrenData*)f->data;
  RETURN_NUM(d->size);
}

void wrenDataBindMethods(WrenVM* vm, ObjClass* dataClass) {
  PRIMITIVE(dataClass, "add(_)",  data_add);
  PRIMITIVE(dataClass, "toString", data_toString);
  PRIMITIVE(dataClass, "length", data_length);
  PRIMITIVE(dataClass, "capacity", data_capacity);
}