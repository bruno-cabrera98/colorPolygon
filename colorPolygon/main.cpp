#include <SDL.h>
#include <SDL_opengl.h>
#include <FreeImage.h>
#include <iostream>
#include <GL/glu.h>

int main(int argc, char* argv[]) {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cerr << "There was an error\n";
		exit(1);
	}

	SDL_Window* win = SDL_CreateWindow("firstPolygon",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		640, 480, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	SDL_GLContext context = SDL_GL_CreateContext(win);

	glClearColor(0.0, 0.0, 0.0, 1);

	glMatrixMode(GL_PROJECTION);
	gluPerspective(45, 640 / 480.f, 0.1, 100);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);

	SDL_Event event;

	bool full = false;

	do {
		glMatrixMode(GL_MODELVIEW);
		glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_DEPTH_BUFFER_BIT);

		glLoadIdentity();
		gluLookAt(0, 0, 6, 0, 0, 0, 0, 1, 0);

		glBegin(GL_TRIANGLES); // ------------------
		glColor3f(1.0, 0.0, 0.0);
		glVertex3f(-1.5, 1, -6);
		glColor3f(0, 1.0, 0.0);
		glVertex3f(-2.5, -1, -6);
		glColor3f(0.0, 0.0, 1.0);
		glVertex3f(-0.5, -1, -6);
		glEnd(); // --------------------------------

		glBegin(GL_QUADS); // ----------------------
		glColor3f(0.0, 1.0, 1.0);
		glVertex3f(0.5, 1, -6);
		glVertex3f(2.5, 1, -6);
		glVertex3f(2.5, -1, -6);
		glVertex3f(0.5, -1, -6);
		glEnd(); // --------------------------------

		glPointSize(10.0);
		glBegin(GL_POINTS);
		glVertex3f(0, 0, 0);
		glEnd();

		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_KEYDOWN) {
				switch (event.key.keysym.sym) {
				case SDLK_ESCAPE:
					return 0;
					break;
				case SDLK_F11:
					glMatrixMode(GL_PROJECTION);
					if (full) {
						SDL_SetWindowFullscreen(win, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
						full = false;
					} else {
						SDL_SetWindowFullscreen(win, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN);
						full = true;
						std::cout << "FULL";
					}
					break;
				default:
					break;
				}
			}
		}

		SDL_GL_SwapWindow(win);
	} while (true);

	return 0;

}

