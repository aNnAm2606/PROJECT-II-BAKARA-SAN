#include "Function.h"

Function::Function(void* ptr)
{
	function = ptr;
}

Function::Function() : function(nullptr)
{
}

void Function::operator=(void* ptr)
{
	function = ptr;
}
