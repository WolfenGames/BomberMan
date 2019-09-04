#include <Swallow.hpp>

class Wall : public Swallow::GameObject
{
	public:
	Wall() = default;
	Wall(const Wall &s) = default;
	Wall &operator=(const Wall &s) = default;
	virtual ~Wall() = default;
};