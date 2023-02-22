//主要是Hook的方法
//以及一些协助函数
	
#include "pch.h"
#include "Helpers.h"
#include <detours.h>

void Helpers::HookFunction(PVOID *Originfunc, PVOID Myfunc) {
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach(Originfunc, Myfunc);
	DetourTransactionCommit();
}

void Helpers::UnhookFunction(PVOID *Originfunc, PVOID Myfunc) {
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourDetach(Originfunc, Myfunc);
	DetourTransactionCommit();
}