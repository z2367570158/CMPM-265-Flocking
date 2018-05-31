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
			hintText.setString("Target Mode: "+BoolToString(vs.hasTarget));
		}
		else if (event.type == Event::KeyPressed && event.key.code == Keyboard::Equal)
		{
			addMode = !addMode;
			hintText.setString("Add Mode: " + BoolToString(addMode));
		}
		else if (event.type == Event::KeyPressed && event.key.code == Keyboard::Dash)
		{
			vs.RemoveVehicle();
			hintText.setString("Remove Vehicle");
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