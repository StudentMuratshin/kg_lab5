#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
using namespace sf;
using namespace std;

void DrawAxes()
{
	//AXES

	glColor3f(0, 0, 0);
	glLineWidth(2);
	glBegin(GL_LINE_STRIP);
	glVertex3f(-10, 0, 0);
	glVertex3f(10, 0, 0);
	glEnd();

	glColor3f(0, 0, 0);
	glLineWidth(2);
	glBegin(GL_LINE_STRIP);
	glVertex3f(0, -10, 0);
	glVertex3f(0, 10, 0);
	glEnd();

	glColor3f(0, 0, 0);
	glLineWidth(2);
	glBegin(GL_LINE_STRIP);
	glVertex3f(0, 0, -10);
	glVertex3f(0, 0, 10);

	glEnd();
}

int main()
{
	sf::Window window(sf::VideoMode(1000, 1000), "Opengl ");
	window.setVerticalSyncEnabled(true);
	glClearColor(1, 1, 1, 1);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(-10, 10, -10, 10, -10, 10);
	glViewport(0, 0, 1000, 1000);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	glShadeModel(GL_FLAT);
	glEnable(GL_CULL_FACE);

	GLfloat vertexArray[12][3] = {};
	for (int i = 0; i < 5; i++)
	{
		vertexArray[i][0] = 8 * cos(i * 2 * 3.14 / 5);
		vertexArray[i][1] = 8 * sin(i * 2 * 3.14 / 5);
		vertexArray[i + 5][0] = 4 * cos(i * 2 * 3.14 / 5 + 3.14 / 5);
		vertexArray[i + 5][1] = 4 * sin(i * 2 * 3.14 / 5 + 3.14 / 5);
	}
	vertexArray[10][2] = 5;
	vertexArray[11][2] = -5;

	/*GLfloat vertexArray[5][3] = {
	{-1, 6,1}, {1, 6,1},{1, -5,-1}, {-1, -5,-1},{-8, 0,0}
	};*/

	/*GLfloat colorArray[5][3] = {
	{1,0,0},{0,1,0}, {0,0,1},{1,1,0},{0,1,1}
	};*/

	GLfloat colorArray[11][3] = {
	{1,0,0},{1,0,0}, {1,0,0},{1,0,0},{1,0,0},
	{1,0.6,0},{1,0.6,0}, {1,0.6,0},{1,0.6,0},{1,0.6,0},{1,1,0}
	};

	GLfloat cubeVertexArray[8][3] = {
	-1, -1, -1,
	-1, -1, 1,
	-1, 1, -1,
	-1, 1, 1,
	 1, -1, -1,
	 1, -1, 1,
	 1, 1, -1,
	 1, 1, 1 };

	GLfloat cubeColorArray[8][3] = {
		1,0,0,
		0,1,0,
		0,0,1,
		1,1,0,
		0,1,1,
		1,0,1,
		0.5,0.5,0.5,
		0,0,0
	};

	glVertexPointer(3, GL_FLOAT, 0, vertexArray);
	glColorPointer(3, GL_FLOAT, 0, colorArray);

	//glVertexPointer(3, GL_FLOAT, 0, cubeVertexArray);
	//glColorPointer(3, GL_FLOAT, 0, cubeColorArray);

	

	//GLubyte triangleIndexArray[3] = { 0,1,2 };
	GLubyte quadIndexArray[4] = { 0,2,3,4 };
	//GLubyte lineIndexArray[5] = { 0,1,2,3,4 };
	GLubyte emptyStarIndexArray[10] = { 0,5,1,6,2,7,3,8,4,9 };
	GLubyte simpleStarIndexArray[10] = { 0,2,4,1,3 };
	GLubyte FullStarIndexArray[10][3] = {};
	GLubyte FullStar2IndexArray[10][3] = {};
	for (int i = 0; i < 5; i++)
	{
		FullStarIndexArray[i][0] = 10;
		FullStarIndexArray[i][1] = i;
		FullStarIndexArray[i][2] = (i + 5) % 10;

		FullStarIndexArray[i + 5][0] = 10;
		FullStarIndexArray[i + 5][1] = (i + 5);
		FullStarIndexArray[i + 5][2] = (i + 1) % 5;
	}
	
	for (int i = 0; i < 5; i++)
	{
		FullStar2IndexArray[i][0] = 11;
		FullStar2IndexArray[i][2] = i;
		FullStar2IndexArray[i][1] = (i + 5) % 10;

		FullStar2IndexArray[i + 5][0] = 11;
		FullStar2IndexArray[i + 5][2] = (i + 5);
		FullStar2IndexArray[i + 5][1] = (i + 1) % 5;
	}
	
	GLubyte cubeIndexArray[6][4] = {
		1,5,7,3,
		5,4,6,7,
		4,0,2,6,
		3,2,0,1,
		3,7,6,2,
		4,5,1,0
	};

	int rotation[3] = {};
	int Move[3] = {};
	float Scale[3] = {1,1,1};

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == Event::Resized)
				glViewport(0, 0, event.size.width, event.size.height);
			if (Keyboard::isKeyPressed(Keyboard::Escape))
				window.close();
			if (event.type == Event::KeyPressed)
			{
				if (event.key.code == Keyboard::A)
				{
					rotation[1] += 1;
				}
				if (event.key.code == Keyboard::D)
				{
					rotation[1] -= 1;
				}
				if (event.key.code == Keyboard::W)
				{
					rotation[0] += 1;
				}
				if (event.key.code == Keyboard::S)
				{
					rotation[0] -= 1;
				}

				if (event.key.code == Keyboard::Left)
				{
					Move[0] -= 1;
				}
				if (event.key.code == Keyboard::Right)
				{
					Move[0] += 1;
				}
				if (event.key.code == Keyboard::Up)
				{
					Move[1] += 1;
				}
				if (event.key.code == Keyboard::Down)
				{
					Move[1] -= 1;
				}

				if (event.key.code == Keyboard::O)
				{
					Scale[0] -= 0.1;
				}
				if (event.key.code == Keyboard::P)
				{
					Scale[0] += 0.1;
				}
				
			}
		}
		glClear(GL_COLOR_BUFFER_BIT);
		/*glDrawElements(GL_TRIANGLES,3,GL_UNSIGNED_BYTE,triangleIndexArray);

		glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, quadIndexArray);*/

		glPushMatrix();
		glRotatef(rotation[1], 0, 1, 0);
		glRotatef(rotation[0], 1, 0, 0);
		glRotatef(rotation[2], 0, 0, 1);

		glTranslatef(0, Move[1], 0);
		glTranslatef(Move[0], 0, 0);

		glScalef(Scale[0], Scale[0], Scale[0]);

		glDrawElements(GL_TRIANGLES, 30, GL_UNSIGNED_BYTE, FullStarIndexArray);
		glDrawElements(GL_TRIANGLES, 30, GL_UNSIGNED_BYTE, FullStar2IndexArray);
		//glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, cubeIndexArray);

		glPopMatrix();
		DrawAxes();

		window.display();
	}

	return 0;
}