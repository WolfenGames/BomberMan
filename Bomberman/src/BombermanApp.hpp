#pragma once
#include <Swallow.hpp>


class BombermanApp : public Swallow::Application
{
public:
	BombermanApp();
	virtual ~BombermanApp();

private:
	BombermanApp(const BombermanApp &s) = default;
	BombermanApp &operator=(const BombermanApp &s) = default;

};