#pragma once

class UCore
{
public:
	virtual bool	Init();
	virtual bool	Frame(float DeltaTime);
	virtual bool	PreRender(float DeltaTime);
	virtual bool	Render(float DeltaTime);
	virtual bool	PostRender(float DeltaTime);
	virtual bool	Release();
private:
	bool CoreInit();
	bool CoreFrame(float DeltaTime);
	bool CoreRender(float DeltaTime);
	bool CoreRelease();
public:
	bool Run()&;
public:
	UCore();
	virtual ~UCore();
};

