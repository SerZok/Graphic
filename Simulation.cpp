#include "Simulation.h"
#include "Data.h"

void simulation(int value) {
	glutPostRedisplay();
	glutTimerFunc(mSIMULATION_TIME, simulation, 0);
};