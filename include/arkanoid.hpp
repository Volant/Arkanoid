#ifndef __ARKANOID_H__
#define __ARKANOID_H__

class Arkanoid {

protected:
	bool is_done;

public:
	Arkanoid () {};

	void game_loop ();

	~Arkanoid () {};
};

#endif
