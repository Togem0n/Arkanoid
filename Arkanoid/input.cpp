#include <input.h>
void GetInput(void) {

	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			exit(0);
			break;

		case SDL_KEYDOWN:
		{
			int scancode = event.key.keysym.scancode;

			keys[scancode] = true;

			if (keys[SDL_SCANCODE_ESCAPE]){
				exit(0);
				break;
			}

			break;
		}

		case SDL_KEYUP:
		{
			int scancode = event.key.keysym.scancode;
			keys[scancode] = false;

			break;
		}
		}
	}
}