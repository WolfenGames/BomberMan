#include <Swallow.hpp>

class Flame : public Swallow::GameObject
{
	public:
	Flame();
	Flame(const Flame &s) = default;
	Flame &operator=(const Flame &s) = default;
	virtual ~Flame() = default;

	inline void Advance(Swallow::Timestep ts) { duration -= ts.GetSeconds(); }

	inline bool Out() { return duration < 0.0f; }

	private:
		float duration;
};