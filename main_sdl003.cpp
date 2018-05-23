//NEPAL FLAG

#include <SDL/SDL.h>
#include <GL/glew.h>
#include <iostream>
#include <string>
#include <cmath>

void DrawGraphics(SDL_Window* _window);
void DrawCircle(float cx, float cy, float r, int num_segments);
void DrawStar(float cx, float cy, float radius, int numPoints);
void DrawLine(float cx, float cy);

enum GameState {PLAY, EXIT};

int main(int argc, char** argv) {
	SDL_Window* _window = nullptr;
	GameState _state = PLAY;


	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "Cannot initialize the subsystem!" << std::endl;
	}
	else {
		_window = SDL_CreateWindow("Dipesh Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 700, 640, SDL_WINDOW_OPENGL);

		if (_window == nullptr) {
			std::cout << "Cannot create window" << std::endl;
		}
		else {

			SDL_GLContext glContext = SDL_GL_CreateContext(_window);
			if (glContext == nullptr) {
				std::cout << "Error creating OpenGL context" << std::endl;
			}

			glewExperimental = GL_TRUE;
			GLenum error = glewInit();
			if (error != GLEW_OK) {
				std::cout << "Doesn't support OpenGL" << std::endl;
			}

			glClearColor(0.8, 0.9, 0.9,1.0);
			glClear(GL_COLOR_BUFFER_BIT);
			SDL_GL_SwapWindow(_window);

			while (_state != EXIT) {
				
				SDL_Event evnt;

				while (SDL_PollEvent(&evnt)) {

					switch (evnt.type) {
						case SDL_QUIT:
							_state = EXIT;

							break;
					}

				}


				// drawing graphics

				DrawGraphics(_window);
			}
		}
	}
	

	return 0;
}

void DrawGraphics(SDL_Window* _window) {
	glClearDepth(1.0);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	glEnableClientState(GL_COLOR_ARRAY);

	glBegin(GL_TRIANGLES);
	//blue upper triangle
	glColor3f(0.0f, 0.0f, 1.0f);   glVertex2f(-0.5f, 0.75f);
	glColor3f(0.0f, 0.0f, 1.0f);   glVertex2f(-0.5f, 0.2f);
	glColor3f(0.0f, 0.0f, 1.0f);   glVertex2f(0.25f, 0.2f);
	//blue lower triangle
	glColor3f(0.0f, 0.0f, 1.0f);   glVertex2f(-0.5f, 0.5f);
	glColor3f(0.0f, 0.0f, 1.0f);   glVertex2f(-0.5f, -0.5f);
	glColor3f(0.0f, 0.0f, 1.0f);   glVertex2f(0.25f, -0.5f);
	//red upper triangle
	glColor3f(1.0f, 0.0f, 0.0f);   glVertex3f(-0.45f, 0.65f, 0.0f);
	glColor3f(1.0f, 0.0f, 0.0f);   glVertex3f(-0.45f, 0.25f, 0.0f);
	glColor3f(1.0f, 0.0f, 0.0f);   glVertex3f(0.10f, 0.25f, 0.0f);
	//red lower triangle
	glColor3f(1.0f, 0.0f, 0.0f);   glVertex3f(-0.45f, 0.35f, 0.0f);
	glColor3f(1.0f, 0.0f, 0.0f);   glVertex3f(-0.45f, -0.45f, 0.0f);
	glColor3f(1.0f, 0.0f, 0.0f);   glVertex3f(0.15f, -0.45f, 0.0f);

	glEnd();



	glColor3f(1.0f, 1.0f, 1.0f);
	DrawCircle(-0.30f, 0.4f, 0.07f, 10000);
	glColor3f(1.0f, 0.0f, 0.0f);
	DrawCircle(-0.30f, 0.435f, 0.07f, 10000);
	DrawStar(-0.30, 0.382, 0.05, 20);
	DrawStar(-0.28, -0.18, 0.10, 20);

	DrawLine(-0.5, 0.75);

	SDL_GL_SwapWindow(_window);
}

void DrawCircle(float cx, float cy, float r, int num_segments)
{
	glBegin(GL_TRIANGLE_FAN);

	for (int ii = 0; ii < num_segments; ii++)
	{
		float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle 
		float x = r * cosf(theta);//calculate the x component 
		float y = r * sinf(theta);//calculate the y component 
		glVertex2f(x + cx, y + cy);//output vertex 
	}
	glEnd();
}

void DrawStar(float cx, float cy, float radius, int numPoints)
{

	const float DegToRad = 3.14159 / 180;
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_TRIANGLE_FAN);
	int count = 1;
	for (int i = 0; i <= 360; i += 360 / (numPoints * 2)) {
		float DegInRad = i * 360.0 / (numPoints * 2) * DegToRad;
		if (count % 2 == 0)
			glVertex2d(cx + cos(DegInRad) * radius, cy + sin(DegInRad) * radius);
		else
			glVertex2d((cx + cos(DegInRad) * radius / 2), (cy + sin(DegInRad) * radius / 2));
		count++;
	}
	glEnd();
}

void DrawLine(float cx, float cy) {
	glEnableClientState(GL_COLOR_ARRAY);

	glLineWidth(5.0f);
	glBegin(GL_LINES);
		glColor3f(0.23f, 0.22f, 0.16f);
		glVertex2f(cx, cy);
		glVertex2f(cx, -1); 
	glEnd();
	
}
