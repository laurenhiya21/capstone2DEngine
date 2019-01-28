/* 2D Game Engine!
	Lauren Bratt
*/

#include <iostream> //cin & cout
#include "HeadHancho.h"

HeadHancho sysHeadHancho; // global HeadHancho for engine

int main()
{
	//std::cout << "Test!" << std::endl;

	sysHeadHancho.start();
	sysHeadHancho.run();
	sysHeadHancho.end();

	getchar();

	return 0;
}