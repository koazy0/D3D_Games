#pragma once


class Render
{
public:
	void Initialize();
	static Render* GetInstance();

private:
	static Render* m_Instance;
};
