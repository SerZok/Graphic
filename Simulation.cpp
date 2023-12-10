#include "Data.h"
#include "Simulation.h"
#include <time.h>


float last_time=0.0;
float getSimulationTime() {
	clock_t current_time = clock();
	float simulationTime = float(current_time - last_time) / CLOCKS_PER_SEC;
	last_time = current_time;
	return simulationTime;
}
void cameraSimulation(float simulationTime) {
	if (GetAsyncKeyState(VK_SHIFT)) {
		if (GetAsyncKeyState(VK_LBUTTON)) {
			int CenterW = glutGet(GLUT_WINDOW_WIDTH) / 2;
			int CenertH = glutGet(GLUT_WINDOW_HEIGHT) / 2;
			int CurPosX = glutGet(GLUT_WINDOW_X);
			int CurPosY = glutGet(GLUT_WINDOW_Y);

			float mAngleX = CenterW - MouseXY.x;
			float mAngleY = CenertH - MouseXY.y;
			float speedMouse = simulationTime / 5;

			if (GetCursorPos(&MouseXY)) {
				cam1.rotateLeftRight((mAngleX + CurPosX) * speedMouse);
				cam1.rotateUpDown((mAngleY + CurPosY) * speedMouse);
				SetCursorPos(MouseXY.x, MouseXY.y);
			}
		}
	}
	float speedKey = simulationTime * 20;

	if (GetAsyncKeyState(VK_LEFT))		cam1.rotateLeftRight(speedKey);
	if (GetAsyncKeyState(VK_RIGHT))		cam1.rotateLeftRight(-speedKey);
	if (GetAsyncKeyState(VK_ADD))		cam1.zoomInOut(-speedKey);
	if (GetAsyncKeyState(VK_SUBTRACT))	cam1.zoomInOut(speedKey);
	if (GetAsyncKeyState(VK_UP))		cam1.rotateUpDown(-speedKey);
	if (GetAsyncKeyState(VK_DOWN))		cam1.rotateUpDown(speedKey);
}

//simualtion all objects
void gameObjectSimulation(float simulationTime) {
	if (player!=nullptr) 
		player->simulate(simulationTime);

	for (int i = 0; i < 21; i++) {
		for (int j = 0; j < 21; j++) {
			if (mapObjects[i][j] != nullptr)
				mapObjects[i][j]->simulate(simulationTime);
		}
	}
}


void movePlayer(){
	float speed = 5.5f;
	if (player != nullptr) {
		ivec2 curPosPlayer = player->getPosition();
		if (GetAsyncKeyState(32) && !drawBomb) {
			bomb->setPosition(curPosPlayer);
			drawBomb = true;
			bombTimer = 3;
			passabilityMap[curPosPlayer.x][curPosPlayer.y] = 5;
		}

		//W
		if ((GetAsyncKeyState(87)) && (!player->isMoving())) {
			if (passabilityMap[curPosPlayer.x][curPosPlayer.y - 1] == 0) {
				player->move(MoveDirection::UP, speed);
			}
			else if ((passabilityMap[curPosPlayer.x][curPosPlayer.y - 1] == 1) and
				(passabilityMap[curPosPlayer.x][curPosPlayer.y - 2] == 0)) {
				passabilityMap[curPosPlayer.x][curPosPlayer.y - 1] = 0;
				passabilityMap[curPosPlayer.x][curPosPlayer.y - 2] = 1;
				mapObjects[curPosPlayer.x][curPosPlayer.y - 1]->move(MoveDirection::UP, speed / 2);
				mapObjects[curPosPlayer.x][curPosPlayer.y - 2] = mapObjects[curPosPlayer.x][curPosPlayer.y - 1];
				mapObjects[curPosPlayer.x][curPosPlayer.y - 1] = nullptr;
				player->move(MoveDirection::UP, speed / 2);
			}
			else if ((passabilityMap[curPosPlayer.x][curPosPlayer.y - 1] == 1) and
				(passabilityMap[curPosPlayer.x][curPosPlayer.y - 2] == 1) and
				(passabilityMap[curPosPlayer.x][curPosPlayer.y - 3] == 0)) {
				passabilityMap[curPosPlayer.x][curPosPlayer.y - 1] = 0;
				passabilityMap[curPosPlayer.x][curPosPlayer.y - 2] = 1;
				passabilityMap[curPosPlayer.x][curPosPlayer.y - 3] = 1;
				mapObjects[curPosPlayer.x][curPosPlayer.y - 2]->move(MoveDirection::UP, speed / 4);
				mapObjects[curPosPlayer.x][curPosPlayer.y - 1]->move(MoveDirection::UP, speed / 4);
				mapObjects[curPosPlayer.x][curPosPlayer.y - 3] = mapObjects[curPosPlayer.x][curPosPlayer.y - 2];
				mapObjects[curPosPlayer.x][curPosPlayer.y - 2] = mapObjects[curPosPlayer.x][curPosPlayer.y - 1];
				mapObjects[curPosPlayer.x][curPosPlayer.y - 1] = nullptr;
				player->move(MoveDirection::UP, speed / 4);
			}
		}
		//S
		if ((GetAsyncKeyState(83)) && (!player->isMoving())) {
			if (passabilityMap[curPosPlayer.x][curPosPlayer.y + 1] == 0) {
				player->move(MoveDirection::DOWN, speed);
			}
			else if ((passabilityMap[curPosPlayer.x][curPosPlayer.y + 1] == 1) and
				(passabilityMap[curPosPlayer.x][curPosPlayer.y + 2] == 0)) {
				passabilityMap[curPosPlayer.x][curPosPlayer.y + 1] = 0;
				passabilityMap[curPosPlayer.x][curPosPlayer.y + 2] = 1;
				mapObjects[curPosPlayer.x][curPosPlayer.y + 1]->move(MoveDirection::DOWN, speed / 2);
				mapObjects[curPosPlayer.x][curPosPlayer.y + 2] = mapObjects[curPosPlayer.x][curPosPlayer.y + 1];
				mapObjects[curPosPlayer.x][curPosPlayer.y + 1] = nullptr;
				player->move(MoveDirection::DOWN, speed / 2);
			}
			//Двигаем 2 кубика
			else if ((passabilityMap[curPosPlayer.x][curPosPlayer.y + 1] == 1) and
				(passabilityMap[curPosPlayer.x][curPosPlayer.y + 2] == 1) and
				(passabilityMap[curPosPlayer.x][curPosPlayer.y + 3] == 0)) {
				passabilityMap[curPosPlayer.x][curPosPlayer.y + 1] = 0;
				passabilityMap[curPosPlayer.x][curPosPlayer.y + 2] = 1;
				passabilityMap[curPosPlayer.x][curPosPlayer.y + 3] = 1;
				mapObjects[curPosPlayer.x][curPosPlayer.y + 2]->move(MoveDirection::DOWN, speed / 4);
				mapObjects[curPosPlayer.x][curPosPlayer.y + 1]->move(MoveDirection::DOWN, speed / 4);
				mapObjects[curPosPlayer.x][curPosPlayer.y + 3] = mapObjects[curPosPlayer.x][curPosPlayer.y + 2];
				mapObjects[curPosPlayer.x][curPosPlayer.y + 2] = mapObjects[curPosPlayer.x][curPosPlayer.y + 1];
				mapObjects[curPosPlayer.x][curPosPlayer.y + 1] = nullptr;
				player->move(MoveDirection::DOWN, speed / 4);
			}
		}
		//A
		if ((GetAsyncKeyState(65)) && (!player->isMoving())) {	//	A
			if (passabilityMap[curPosPlayer.x - 1][curPosPlayer.y] == 0) {
				player->move(MoveDirection::LEFT, speed);
			}
			else if ((passabilityMap[curPosPlayer.x - 1][curPosPlayer.y] == 1) and
				(passabilityMap[curPosPlayer.x - 2][curPosPlayer.y] == 0)) {
				passabilityMap[curPosPlayer.x - 1][curPosPlayer.y] = 0;
				passabilityMap[curPosPlayer.x - 2][curPosPlayer.y] = 1;
				mapObjects[curPosPlayer.x - 1][curPosPlayer.y]->move(MoveDirection::LEFT, speed / 2);
				mapObjects[curPosPlayer.x - 2][curPosPlayer.y] = mapObjects[curPosPlayer.x - 1][curPosPlayer.y];
				mapObjects[curPosPlayer.x - 1][curPosPlayer.y] = nullptr;
				player->move(MoveDirection::LEFT, speed / 2);
			}
			//Двигаем 2 кубика
			else if ((passabilityMap[curPosPlayer.x - 1][curPosPlayer.y] == 1) and
				(passabilityMap[curPosPlayer.x - 2][curPosPlayer.y] == 1) and
				(passabilityMap[curPosPlayer.x - 3][curPosPlayer.y] == 0)) {
				passabilityMap[curPosPlayer.x - 1][curPosPlayer.y] = 0;
				passabilityMap[curPosPlayer.x - 2][curPosPlayer.y] = 1;
				passabilityMap[curPosPlayer.x - 3][curPosPlayer.y] = 1;
				mapObjects[curPosPlayer.x - 2][curPosPlayer.y]->move(MoveDirection::LEFT, speed / 4);
				mapObjects[curPosPlayer.x - 1][curPosPlayer.y]->move(MoveDirection::LEFT, speed / 4);
				mapObjects[curPosPlayer.x - 3][curPosPlayer.y] = mapObjects[curPosPlayer.x - 2][curPosPlayer.y];
				mapObjects[curPosPlayer.x - 2][curPosPlayer.y] = mapObjects[curPosPlayer.x - 1][curPosPlayer.y];
				mapObjects[curPosPlayer.x - 1][curPosPlayer.y] = nullptr;
				player->move(MoveDirection::LEFT, speed / 4);
			}
		}
		//D
		if ((GetAsyncKeyState(68)) && (!player->isMoving())) {
			if (passabilityMap[curPosPlayer.x + 1][curPosPlayer.y] == 0) {
				player->move(MoveDirection::RIGHT, speed);
			}
			//Двигаем 1 кубик
			else if ((passabilityMap[curPosPlayer.x + 1][curPosPlayer.y] == 1) and
				(passabilityMap[curPosPlayer.x + 2][curPosPlayer.y] == 0)) {

				passabilityMap[curPosPlayer.x + 1][curPosPlayer.y] = 0;
				passabilityMap[curPosPlayer.x + 2][curPosPlayer.y] = 1;
				mapObjects[curPosPlayer.x + 1][curPosPlayer.y]->move(MoveDirection::RIGHT, speed / 2);
				mapObjects[curPosPlayer.x + 2][curPosPlayer.y] = mapObjects[curPosPlayer.x + 1][curPosPlayer.y];
				mapObjects[curPosPlayer.x + 1][curPosPlayer.y] = nullptr;
				player->move(MoveDirection::RIGHT, speed / 2);
			}
			//Двигаем 2 кубика
			else if ((passabilityMap[curPosPlayer.x + 1][curPosPlayer.y] == 1) and
				(passabilityMap[curPosPlayer.x + 2][curPosPlayer.y] == 1) and
				(passabilityMap[curPosPlayer.x + 3][curPosPlayer.y] == 0)) {
				passabilityMap[curPosPlayer.x + 1][curPosPlayer.y] = 0;
				passabilityMap[curPosPlayer.x + 2][curPosPlayer.y] = 1;
				passabilityMap[curPosPlayer.x + 3][curPosPlayer.y] = 1;
				mapObjects[curPosPlayer.x + 2][curPosPlayer.y]->move(MoveDirection::RIGHT, speed / 4);
				mapObjects[curPosPlayer.x + 1][curPosPlayer.y]->move(MoveDirection::RIGHT, speed / 4);
				mapObjects[curPosPlayer.x + 3][curPosPlayer.y] = mapObjects[curPosPlayer.x + 2][curPosPlayer.y];
				mapObjects[curPosPlayer.x + 2][curPosPlayer.y] = mapObjects[curPosPlayer.x + 1][curPosPlayer.y];
				mapObjects[curPosPlayer.x + 1][curPosPlayer.y] = nullptr;
				player->move(MoveDirection::RIGHT, speed / 4);
			}
		}
	}
	return;
}

void bombSimulate(float simulationTime) {
	if (drawBomb) {
		bombTimer -= simulationTime;
		if (bombTimer <= 0) {
			bombTimer = 0;
			ivec2 pos = bomb->getPosition();
			ivec2 playerPos;
			if (player != nullptr)
				playerPos = player->getPosition();
			passabilityMap[pos.x][pos.y] = 0;
			drawBomb = false;
			if (playerPos == pos)
				player = nullptr;
			if (playerPos == pos - ivec2(0, 1))
				player = nullptr;
			if (playerPos == pos - ivec2(0, -1))
				player = nullptr;
			if (playerPos == pos - ivec2(1, 0))
				player = nullptr;
			if (playerPos == pos - ivec2(-1, 0))
				player = nullptr;

			if (passabilityMap[pos.x - 1][pos.y] == 0 &&
				playerPos == pos - ivec2(2, 0)) {
				player = nullptr;
			}
			if (passabilityMap[pos.x + 1][pos.y] == 0 &&
				playerPos == pos - ivec2(-2, 0)) {
				player = nullptr;
			}
			if (passabilityMap[pos.x][pos.y - 1] == 0 &&
				playerPos == pos - ivec2(0, 2)) {
				player = nullptr;
			}
			if (passabilityMap[pos.x][pos.y + 1] == 0 &&
				playerPos == pos - ivec2(0, -2)) {
				player = nullptr;
			}

			if (pos.x < 19) {
				if (passabilityMap[pos.x + 1][pos.y] == 0 &&
					(passabilityMap[pos.x + 2][pos.y] == 1 ||
						passabilityMap[pos.x + 2][pos.y] == 4) &&
					playerPos != pos - ivec2(-1, 0)) {
					passabilityMap[pos.x + 2][pos.y] = 0;
					mapObjects[pos.x + 2][pos.y] = nullptr;
				}
			}
			if (pos.x > 1) {
				if (passabilityMap[pos.x - 1][pos.y] == 0 &&
					(passabilityMap[pos.x - 2][pos.y] == 1 ||
						passabilityMap[pos.x - 2][pos.y] == 4) &&
					playerPos != pos - ivec2(1, 0)) {
					passabilityMap[pos.x - 2][pos.y] = 0;
					mapObjects[pos.x - 2][pos.y] = nullptr;
				}
			}
			if (pos.y < 19) {
				if (passabilityMap[pos.x][pos.y + 1] == 0 &&
					(passabilityMap[pos.x][pos.y + 2] == 1 ||
						passabilityMap[pos.x][pos.y + 2] == 4) &&
					playerPos != pos - ivec2(0, -1)) {
					passabilityMap[pos.x][pos.y + 2] = 0;
					mapObjects[pos.x][pos.y + 2] = nullptr;
				}
			}
			if (pos.y > 1) {
				if (passabilityMap[pos.x][pos.y - 1] == 0 &&
					(passabilityMap[pos.x][pos.y - 2] == 1 ||
						passabilityMap[pos.x][pos.y + 2] == 4) &&
					playerPos != pos - ivec2(0, 1)) {
					passabilityMap[pos.x][pos.y - 2] = 0;
					mapObjects[pos.x][pos.y - 2] = nullptr;
				}
			}
			if (passabilityMap[pos.x - 1][pos.y] == 1 ||
				passabilityMap[pos.x - 1][pos.y] == 4) {
				passabilityMap[pos.x - 1][pos.y] = 0;
				mapObjects[pos.x - 1][pos.y] = nullptr;
			}
			if (passabilityMap[pos.x + 1][pos.y] == 1 ||
				passabilityMap[pos.x + 1][pos.y] == 4) {
				passabilityMap[pos.x + 1][pos.y] = 0;
				mapObjects[pos.x + 1][pos.y] = nullptr;
			}
			if (passabilityMap[pos.x][pos.y - 1] == 1 ||
				passabilityMap[pos.x][pos.y - 1] == 4) {
				passabilityMap[pos.x][pos.y - 1] = 0;
				mapObjects[pos.x][pos.y - 1] = nullptr;
			}
			if (passabilityMap[pos.x][pos.y + 1] == 1 ||
				passabilityMap[pos.x][pos.y + 1] == 4) {
				passabilityMap[pos.x][pos.y + 1] = 0;
				mapObjects[pos.x][pos.y + 1] = nullptr;
			}
		}
	}
}


float MONSTER_SPEED = 3.0f;
bool monsterMoveUp(shared_ptr<GameObject> monster, ivec2 pos) {
	if (passabilityMap[pos.x][pos.y - 1] == 0) {
		monster->move(MoveDirection::UP, MONSTER_SPEED);
		passabilityMap[pos.x][pos.y - 1] = 4;
		passabilityMap[pos.x][pos.y] = 0;
		mapObjects[pos.x][pos.y - 1] = mapObjects[pos.x][pos.y];
		mapObjects[pos.x][pos.y] = nullptr;
		return true;
	}
	else return false;
}
bool monsterMoveDown(shared_ptr<GameObject> monster, ivec2 pos) {
	if (passabilityMap[pos.x][pos.y + 1] == 0) {
		monster->move(MoveDirection::DOWN, MONSTER_SPEED);
		passabilityMap[pos.x][pos.y + 1] = 4;
		passabilityMap[pos.x][pos.y] = 0;
		mapObjects[pos.x][pos.y + 1] = mapObjects[pos.x][pos.y];
		mapObjects[pos.x][pos.y] = nullptr;
		return true;
	}
	else return false;
}
bool monsterMoveLeft(shared_ptr<GameObject> monster, ivec2 pos) {
	if (passabilityMap[pos.x - 1][pos.y] == 0) {
		monster->move(MoveDirection::LEFT, MONSTER_SPEED);
		passabilityMap[pos.x - 1][pos.y] = 4;
		passabilityMap[pos.x][pos.y] = 0;
		mapObjects[pos.x - 1][pos.y] = mapObjects[pos.x][pos.y];
		mapObjects[pos.x][pos.y] = nullptr;
		return true;
	}
	else return false;
}
bool monsterMoveRight(shared_ptr<GameObject> monster, ivec2 pos) {
	if (passabilityMap[pos.x + 1][pos.y] == 0) {
		monster->move(MoveDirection::RIGHT, MONSTER_SPEED);
		passabilityMap[pos.x + 1][pos.y] = 4;
		passabilityMap[pos.x][pos.y] = 0;
		mapObjects[pos.x + 1][pos.y] = mapObjects[pos.x][pos.y];
		mapObjects[pos.x][pos.y] = nullptr;
		return true;
	}
	else return false;
}

void monstersSimulation(float simulationTime) {
	for (int i = 0; i < monsters.size(); i++) {
		ivec2 pos = monsters[i]->getPosition();
		if (monstersLastDirection[i] == -1) monstersLastDirection[i] = rand() % 4;
		if (!monsters[i]->isMoving()) {
			bool result = true;
			int direction;
			vector<int> availableDirections;
			if ((passabilityMap[pos.x][pos.y - 1] == 0) && (monstersLastDirection[i] != 1)) availableDirections.push_back(0);
			if ((passabilityMap[pos.x][pos.y + 1] == 0) && (monstersLastDirection[i] != 0)) availableDirections.push_back(1);
			if ((passabilityMap[pos.x - 1][pos.y] == 0) && (monstersLastDirection[i] != 3)) availableDirections.push_back(2);
			if ((passabilityMap[pos.x + 1][pos.y] == 0) && (monstersLastDirection[i] != 2)) availableDirections.push_back(3);
			if (availableDirections.size() == 0) {
				switch (monstersLastDirection[i]){
				case 0: {
					direction = 1;
					break;
				}
				case 1: {
					direction = 0;
					break;
				}
				case 2: {
					direction = 3;
					break;
				}
				case 3: {
					direction = 2;
					break;
				}
				default:
					break;
				}
			}
			else {
				direction = availableDirections[rand() % availableDirections.size()];
			}
			switch (direction)
			{
			case 0: {
				result = monsterMoveUp(monsters[i], pos);
				monstersLastDirection[i] = 0;
				break;
			}
			case 1: {
				result = monsterMoveDown(monsters[i], pos);
				monstersLastDirection[i] = 1;
				break;
			}
			case 2: {
				result = monsterMoveLeft(monsters[i], pos);
				monstersLastDirection[i] = 2;
				break;
			}
			case 3: {
				result = monsterMoveRight(monsters[i], pos);
				monstersLastDirection[i] = 3;
				break;
			}
			default:
				break;
			}
			if (player != nullptr) {
				if (monsters[i]->getPosition() == player->getPosition()) {
					cout << "Game over!\n";
					player = nullptr;
				}
			}
		}

	}
}

void simulation() {
	float simulationTime = getSimulationTime();
	cameraSimulation(simulationTime);
	gameObjectSimulation(simulationTime);
	monstersSimulation(simulationTime);
	bombSimulate(simulationTime);
	movePlayer();
	glutPostRedisplay();
};