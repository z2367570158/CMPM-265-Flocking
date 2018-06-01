#include "VehicleSystem.h"

#define _CRTDBG_MAP_ALLOC
#define _CRTDBG_MAP_ALLOC_NEW
#include <cstdlib>
#include <crtdbg.h>
#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif

string BoolToString(bool b);

void Initialize();
void HandleInput();
Vector2f windowSize(1366, 768);

VehicleSystem vs(windowSize);

RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y), "Flocking");
Font font;
Text hintText;
RectangleShape TargetMark;

bool targetMode = false;
bool addMode = false;
bool separationMode = false;
bool alignmentMode = false;
bool cohesionMode = false;
bool distanceMode = false;

SoundBuffer BGMBuf;
Sound BGMSound;


int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF |
		_CRTDBG_LEAK_CHECK_DF);

	Initialize();


	while (window.isOpen())
	{
		HandleInput();
		
		vs.Update();

		window.clear();
		if(vs.hasTarget)
			window.draw(TargetMark);

		for (Vehicle* v : vs.flock)
			window.draw(v->shape);
		window.draw(hintText);
		window.display();
	}

	return 0;
}

void Initialize()
{
	font.loadFromFile("consola.ttf");
	window.setKeyRepeatEnabled(false);

	BGMBuf.loadFromFile("BGM.flac");
	BGMSound.setBuffer(BGMBuf);
	BGMSound.setLoop(true);

	TargetMark.setSize(Vector2f(5, 5));
	TargetMark.setFillColor(Color::Red);
	TargetMark.setOrigin(0.5f*TargetMark.getSize());
	TargetMark.setPosition(vs.target);


	hintText.setFont(font);
	hintText.setCharacterSize(20);
	hintText.setPosition(30, windowSize.y - 30);

}

void HandleInput()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();
		else if (event.type == Event::KeyPressed && event.key.code == Keyboard::Space)
		{
			targetMode = !targetMode;
			vs.hasTarget = !vs.hasTarget;
			hintText.setString("Target Change "+ BoolToString(targetMode));
		}
		else if (event.type == Event::KeyPressed && event.key.code == Keyboard::Add)
		{
			separationMode = false;
			alignmentMode = false;
			cohesionMode = false;
			addMode = !addMode;
			hintText.setString("Add Mode: " + BoolToString(addMode));
		}
		else if (event.type == Event::KeyPressed && event.key.code == Keyboard::Subtract)
		{
			vs.RemoveVehicle();
			hintText.setString("Remove Vehicle");
		}
		else if (event.type == Event::KeyPressed && event.key.code == Keyboard::Equal)
		{
			if (separationMode)
			{
				vs.separationFactor++;
				hintText.setString("Separation Factor " + to_string((int)vs.separationFactor));
			}

			if (alignmentMode)
			{
				vs.alignmentFactor++;
				hintText.setString("Alignment Factor " + to_string((int)vs.alignmentFactor));
			}

			if (cohesionMode)
			{
				vs.cohesionFactor++;
				hintText.setString("Cohesion Factor " + to_string((int)vs.cohesionFactor));
			}

			if (targetMode)
			{
				vs.targetFactor += 0.5;
				hintText.setString("Target Factor " + to_string(vs.targetFactor));
			}

			if (distanceMode)
			{
				vs.closeDistance += 5;
				hintText.setString("Affect Distance " + to_string((int)vs.closeDistance));
			}
		}
		else if (event.type == Event::KeyPressed && event.key.code == Keyboard::Dash)
		{
			if (separationMode&&vs.separationFactor-1 >= 0)
			{
				vs.separationFactor--;
				hintText.setString("Separation Factor " + to_string((int)vs.separationFactor));
			}
			
			if (alignmentMode&&vs.alignmentFactor-1 >= 0)
			{
				vs.alignmentFactor--;
				hintText.setString("Alignment Factor " + to_string((int)vs.alignmentFactor));
			}

			if (cohesionMode&&vs.cohesionFactor-1 >= 0)
			{
				vs.cohesionFactor--;
				hintText.setString("Cohesion Factor " + to_string((int)vs.cohesionFactor));
			}

			if (targetMode)
			{
				vs.targetFactor-= 0.5;
				hintText.setString("Target Factor " + to_string(vs.targetFactor));
			}


			if (distanceMode&&vs.closeDistance - 5 >= 0)
			{
				vs.closeDistance -= 5;
				hintText.setString("Affect Distance " + to_string((int)vs.closeDistance));
			}
		}
		else if (event.type == Event::KeyPressed && event.key.code == Keyboard::S)
		{
			separationMode = !separationMode;
			alignmentMode = false;
			cohesionMode = false;
			distanceMode = false;
			hintText.setString("Separation Change "+ BoolToString(separationMode));
		}
		else if (event.type == Event::KeyPressed && event.key.code == Keyboard::A)
		{
			separationMode = false;
			alignmentMode = !alignmentMode;
			cohesionMode = false;
			distanceMode = false;
			hintText.setString("Alignment Change " + BoolToString(alignmentMode));
		}
		else if (event.type == Event::KeyPressed && event.key.code == Keyboard::C)
		{
			separationMode = false;
			alignmentMode = false;
			cohesionMode = !cohesionMode;
			distanceMode = false;
			hintText.setString("Cohesion Change " + BoolToString(cohesionMode));
		}
		else if (event.type == Event::KeyPressed && event.key.code == Keyboard::D)
		{
			distanceMode = !distanceMode;
			separationMode = false;
			alignmentMode = false;
			cohesionMode = false;
			hintText.setString("Distance Change " + BoolToString(distanceMode));
		}
		else if (event.type == Event::KeyPressed && event.key.code == Keyboard::P)
		{
			BGMSound.play();
		}

	}

	if (Mouse::isButtonPressed(Mouse::Left))
	{
		if (targetMode)
		{
			vs.target.x = Mouse::getPosition(window).x;
			vs.target.y = Mouse::getPosition(window).y;
			TargetMark.setPosition(vs.target);
		}

	}
	if (Mouse::isButtonPressed(Mouse::Right))
	{
		if (addMode)
		{
			vs.AddVehicle(Mouse::getPosition(window).x, Mouse::getPosition(window).y);
		}
	}
}

inline string BoolToString(bool b)
{
	return b ? "On" : "Off";
}