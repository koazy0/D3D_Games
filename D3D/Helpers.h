#pragma once
#pragma comment(lib, "detours.lib")

class Helpers
{
public:
	static void HookFunction(PVOID *Originfunc, PVOID Myfunc);
	static void UnhookFunction(PVOID *Originfunc, PVOID Myfunc);
};

