#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

char map[4][4][6] = {	//Wumpus, Pit, Gold, Stench, Breeze, Glitter
	{{ '0','0','0','0','0','0' },{ '0','0','0','0','0','0' },{ '0','0','0','0','0','0' },{ '0','0','0','0','0','0' }},
	{{ '0','0','0','0','0','0' },{ '0','0','0','0','0','0' },{ '0','0','0','0','0','0' },{ '0','0','0','0','0','0' }},
	{{ '0','0','0','0','0','0' },{ '0','0','0','0','0','0' },{ '0','0','0','0','0','0' },{ '0','0','0','0','0','0' }},
	{{ '0','0','0','0','0','0' },{ '0','0','0','0','0','0' },{ '0','0','0','0','0','0' },{ '0','0','0','0','0','0' }}	
};
char StMem[4][4][6] = {		//StatusMemory
	{{ '0','0','0','0','0','0' },{ '0','0','0','0','0','0' },{ '0','0','0','0','0','0' },{ '0','0','0','0','0','0' }},
	{{ '0','0','0','0','0','0' },{ '0','0','0','0','0','0' },{ '0','0','0','0','0','0' },{ '0','0','0','0','0','0' }},
	{{ '0','0','0','0','0','0' },{ '0','0','0','0','0','0' },{ '0','0','0','0','0','0' },{ '0','0','0','0','0','0' }},
	{{ '0','0','0','0','0','0' },{ '0','0','0','0','0','0' },{ '0','0','0','0','0','0' },{ '0','0','0','0','0','0' }}
};
int Visited[4][4] = {	//방문한 곳 확인용 배열
	{0,0,0,0},
	{0,0,0,0},
	{0,0,0,0},
	{0,0,0,0}
};
int dir = 1; // 방향 변수 1: 동쪽 2: 남쪽 3: 서쪽  4: 북쪽
int a = 1;
int b = 1;	//현재위치 (a,b)
int scream = 0; //괴물을 죽이는데 성공하면 1이 됨
int goldpicked = 0;	//금 grab 하면 1
int arrow = 3;
int bump = 0;	//충돌시 1 TurnLeft TurnRight 때 0
int out = 0;	//동굴 나가면 1
int death = 0;    //wumpus에 화살이 맞으면 0으로 바뀜
int randir = 0;	//랜덤한 방향으로 가야할 때 사용하는 변수
int bumpcheckvar = 0;
int GoForward() {
	Visited[a - 1][4 - b] = 1;
	if (dir == 1) {
		if (a >= 1 && a <= 3) {
			a = a + 1;
		}
		else {
			bump = 1;
			printf("동쪽 Bump 감지\n");
		}
	}
	else if (dir == 2) {
		if (b >= 2 && b <= 4) {
			b = b - 1;
		}
		else {
			bump = 1;
			printf("남쪽 Bump 감지\n");
		}
	}
	else if (dir == 3) {
		if (a >= 2 && a <= 4) {
			a = a - 1;
		}
		else {
			bump = 1;
			printf("서쪽 Bump 감지\n");
		}
	}
	else if (dir == 4) {
		if (b >= 1 && b <= 3) {
			b = b + 1;
		}
		else {
			bump = 1;
			printf("북쪽 Bump 감지\n");
		}
		
	}
	printf("Agent가 (%d, %d)로 이동\n", a, b);



	Visited[a - 1][4 - b] = 1;	//방문한 곳 기록
}

int TurnLeft() {
	bump = 0;
	if (dir == 1) {
		dir = 4;
	}
	else if (dir == 4) {
		dir = 3;
	}
	else if (dir == 3) {
		dir = 2;
	}
	else if (dir == 2) {
		dir = 1;
	}

	switch (dir) {
	case 1: 
		printf("동쪽으로 방향 전환\n");
		break;
	case 2:
		printf("남쪽으로 방향 전환\n");
		break;
	case 3:
		printf("서쪽으로 방향 전환\n");
		break;
	case 4:
		printf("북쪽으로 방향 전환\n");
		break;
	}
}

int TurnRight() {
	bump = 0;
	if (dir == 1) {
		dir = 2;
	}
	else if (dir == 2) {
		dir = 3;
	}
	else if (dir == 3) {
		dir = 4;
	}
	else if (dir == 4) {
		dir = 1;
	}

	switch (dir) {
	case 1:
		printf("동쪽으로 방향 전환\n");
		break;
	case 2:
		printf("남쪽으로 방향 전환\n");
		break;
	case 3:
		printf("서쪽으로 방향 전환\n");
		break;
	case 4:
		printf("북쪽으로 방향 전환\n");
		break;
	}
}

int Grab() {
		goldpicked = 1;
		printf("금을 주웠습니다\n");
}

int Shoot() {
	if ((arrow > 0 && death == 0) && map[a - 1][4 - b][3] == 'S') {
		arrow = arrow - 1;
		printf("화살 발사\n");
		int x = a;
		int y = b;

		switch (dir) {
		case 1:
			for (x = a; x < 5; x++) {
				if (map[x - 1][4 - y][0] == 'W') {
					death = 1;
					map[x - 1][4 - y][0] = '0';
					break;
				}
			}
			break;

		case 2:
			for (y = b; 0 < y; y--) {
				if (map[x - 1][4 - y][0] == 'W') {
					death = 1;
					map[x - 1][4 - y][0] = '0';
					break;
				}
			}
			break;

		case 3:
			for (x = a; 0 < x; x--) {
				if (map[x - 1][4 - y][0] == 'W') {
					death = 1;
					map[x - 1][4 - y][0] = '0';
					break;
				}
			}
			break;

		case 4:
			for (y = b; y < 5; y++) {
				if (map[x - 1][4 - y][0] == 'W') {
					death = 1;
					map[x - 1][4 - y][0] = '0';
					break;
				}
			}
			break;
		}
		if (death == 1) {
			scream = 1;
			printf("Agent가 Scream을 감지함\n");
		}
		else {
			printf("Agent가 화살을 발사했으나 Scream이 감지되지 않음\n");
		}
	}
}



int Climb() {
	if (a == 1 && b == 1 && goldpicked == 1) {
		printf("에이전트가 금을 획득해 동굴을 빠져나갔습니다.\n");
	}
	out = 1;
}

int GenWum() {	//Generate Wumpus

	int x = rand() % 5;
	int y = rand() % 5;

	if ((x == 0) || (y == 0)) {
		GenWum();
	}

	else if ((1 <= x <= 2 && 1 <= y <= 2) && (x != 2 && y != 2)) {
		GenWum();
	}

	else if ((map[x - 1][4 - y][1] == 'P') || (map[x - 1][4 - y][2] == 'G')) {
		GenWum();
	}

	else {
		map[x - 1][4 - y][0] = 'W';			//Wumpus

		if (1 <= y && y <= 3) {
			map[x - 1][3 - y][3] = 'S';
		}
		if (2 <= y && y <= 4) {
			map[x - 1][5 - y][3] = 'S';
		}
		if (2 <= x && x <= 4) {
			map[x - 2][4 - y][3] = 'S';
		}
		if (1 <= x && x <= 3) {
			map[x][4 - y][3] = 'S';
		}
	}

}

int GenGold() {	//Generate Gold

	int x = rand() % 5;
	int y = rand() % 5;

	if (x == 0 || y == 0) {
		GenGold();
	}

	else if ((1 <= x <= 2 && 1 <= y <= 2) && (x != 2 && y != 2)) {
		GenGold();
	}

	else if ((map[x - 1][4 - y][0] == 'W') || (map[x - 1][4 - y][1] == 'P')) {
		GenGold();
	}

	else {
		map[x - 1][4 - y][2] = 'G';			//Gold
		map[x - 1][4 - y][5] = 'G';			//Glitter
	}
}

int GenPit() {	//Generate Pit

	int x = rand() % 5;
	int y = rand() % 5;

	if (x == 0 || y == 0) {
		GenPit();
	}

	else if ((1 <= x <= 2 && 1 <= y <= 2) && (x != 2 && y != 2)) {
		GenPit();
	}
	else if ((map[x - 1][4 - y][0] == 'W') || (map[x - 1][4 - y][2] == 'G')) {
		GenPit();
	}

	else {
		map[x - 1][4 - y][1] = 'P';			//Pit

		if (1 <= y && y <= 3) {
			map[x - 1][3 - y][4] = 'B';
		}
		if (2 <= y && y <= 4) {
			map[x - 1][5 - y][4] = 'B';
		}
		if (2 <= x && x <= 4) {
			map[x - 2][4 - y][4] = 'B';
		}
		if (1 <= x && x <= 3) {
			map[x][4 - y][4] = 'B';
		}
	}
}

int bumpcheck() {
	if (bump == 1) {
		bumpcheckvar = 0;
		while (bumpcheckvar == 0) {
			bumpcheckvar = rand() % 5;
		}
		while (bumpcheckvar != dir) {
			TurnRight();
		}
		GoForward();

	}
}

int save() {
	StMem[a - 1][4 - b][0] = map[a - 1][4 - b][0];
	StMem[a - 1][4 - b][1] = map[a - 1][4 - b][1];
	StMem[a - 1][4 - b][2] = map[a - 1][4 - b][2];
	StMem[a - 1][4 - b][3] = map[a - 1][4 - b][3];
	StMem[a - 1][4 - b][4] = map[a - 1][4 - b][4];
	StMem[a - 1][4 - b][5] = map[a - 1][4 - b][5];
}









int main(void) {
	srand((unsigned int)time(NULL));
	GenWum();
	GenPit();
	GenPit();
	GenPit();
	GenGold();

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < 6; k++) {
				printf("%c, ", map[i][j][k]);
			}
			printf("|");
		}
		printf("\n");
	}

	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");

	printf("Agent의 현재 위치: (1, 1) 방향: 동쪽\n");


	while(goldpicked==0) {
		save();
		bumpcheck();
		if (a == 1 && b == 1) {
			randir = rand() % 2;
			if (randir == 0) {
				while (dir != 1) {
					TurnLeft();
				}
				GoForward();
			}
			else if (randir == 1) {
				while (dir != 4) {
					TurnLeft();
				}
				GoForward();
			}
		}
		else if (a == 2 && b == 1) {
			if ((StMem[a][4 - b][0] == 'W' || StMem[a][4 - b][1] == 'P') && (StMem[a - 1][3 - b][0] == 'W' || StMem[a - 1][3 - b][1] == 'P')) {
				while (dir != 3) {
					TurnLeft();
				}
				GoForward();
			}
			else if (StMem[a][4 - b][0] == 'W' || StMem[a][4 - b][1] == 'P') {
				while (dir != 3 && dir != 4) {
					TurnLeft();
				}
				GoForward();
			}
			else if (StMem[a - 1][3 - b][0] == 'W' || StMem[a - 1][3 - b][1] == 'P') {
				while (dir != 1 && dir != 3) {
					TurnLeft();
				}
				GoForward();
			}
			else {
				TurnLeft();
				GoForward();
			}
		}
		else if (a == 3 && b == 1) {
			if (map[2][3][2] == 'G') {
				Grab();
			}
			if (map[2][3][0] == 'W') {
				printf("Wumpus를 만나 죽었습니다 (1, 1)에서 부활\n");
				a = 1;
				b = 1;
			}
			if (map[2][3][1] == 'P'){
				printf("Pit에 빠져 죽었습니다 (1, 1)에서 부활\n");
				a = 1;
				b = 1;
			}
			if ((StMem[a][4 - b][0] == 'W' || StMem[a][4 - b][1] == 'P') && (StMem[a - 1][3 - b][0] == 'W' || StMem[a - 1][3 - b][1] == 'P')) {
				while (dir != 3) {
					TurnLeft();
				}
				GoForward();
			}
			else if (StMem[a][4 - b][0] == 'W' || StMem[a][4 - b][1] == 'P') {
				while (dir != 3 && dir != 4) {
					TurnLeft();
				}
				GoForward();
			}
			else if (StMem[a - 1][3 - b][0] == 'W' || StMem[a - 1][3 - b][1] == 'P') {
				while (dir != 1 && dir != 3) {
					TurnLeft();
				}
				GoForward();
			}
			else {
				TurnLeft();
				GoForward();
			}
			

			
		}
		else if (a == 4 && b == 1) {
			if (map[3][3][2] == 'G') {
				Grab();
			}
			if (map[3][3][0] == 'W') {
				printf("Wumpus를 만나 죽었습니다 (1, 1)에서 부활\n");
				a = 1;
				b = 1;
			}
			if (map[3][3][1] == 'P') {
				printf("Pit에 빠져 죽었습니다 (1, 1)에서 부활\n");
				a = 1;
				b = 1;
			}
			if (StMem[a - 1][3 - b][0] == 'W' || StMem[a - 1][3 - b][0] == 'P') {
				while (dir != 3) {
					TurnLeft();
				}
				GoForward();
			}
			else if (StMem[a - 2][4 - b][0] == 'W' || StMem[a - 2][4 - b][0] == 'P') {
				while (dir != 4) {
					TurnLeft();
				}
				GoForward();
			}
			else {
				TurnLeft();
				GoForward();
			}
			
			
		}
		else if (a == 1 && b == 2) {
			if ((StMem[a - 2][4 - b][0] == 'W' || StMem[a][4 - b][1] == 'P') && (StMem[a - 1][3 - b][0] == 'W' || StMem[a - 1][3 - b][1] == 'P')) {
				while (dir != 2) {
					TurnLeft();
				}
				GoForward();
			}
			else if (StMem[a-2][4 - b][0] == 'W' || StMem[a][4 - b][1] == 'P') {
				while (dir != 3 && dir != 4) {
					TurnLeft();
				}
				GoForward();
			}
			else if (StMem[a - 1][3 - b][0] == 'W' || StMem[a - 1][3 - b][1] == 'P') {
				while (dir != 1 && dir != 3) {
					TurnLeft();
				}
				GoForward();
			}
			else {
				TurnRight();
				GoForward();
			}
		}
		else if (a == 2 && b == 2) {
		if (map[1][2][2] == 'G') {
			Grab();
		}
		if (map[1][2][0] == 'W') {
			printf("Wumpus를 만나 죽었습니다 (1, 1)에서 부활\n");
			a = 1;
			b = 1;
		}
		if (map[1][2][1] == 'P') {
			printf("Pit에 빠져 죽었습니다 (1, 1)에서 부활\n");
			a = 1;
			b = 1;
		}
			randir = 0;
			while (randir == 0) {
			randir = rand() % 5;
			}
			while (randir != dir) {
				TurnLeft();
			}
			GoForward();
			
		
		}
		else if (a == 3 && b == 2) {
		if (map[2][2][2] == 'G') {
			Grab();
		}
		if (map[2][2][0] == 'W') {
			printf("Wumpus를 만나 죽었습니다 (1, 1)에서 부활\n");
			a = 1;
			b = 1;
		}
		if (map[2][2][1] == 'P') {
			printf("Pit에 빠져 죽었습니다 (1, 1)에서 부활\n");
			a = 1;
			b = 1;
		}
			randir = 0;
			while (randir == 0) {
			randir = rand() % 5;
			}
			while (randir != dir) {
			TurnLeft();
			}
			GoForward();
			

		}
		else if (a == 4 && b == 2) {
		if (map[3][2][2] == 'G') {
			Grab();
		}
		if (map[3][2][0] == 'W') {
			printf("Wumpus를 만나 죽었습니다 (1, 1)에서 부활\n");
			a = 1;
			b = 1;
		}
		if (map[3][2][1] == 'P') {
			printf("Pit에 빠져 죽었습니다 (1, 1)에서 부활\n");
			a = 1;
			b = 1;
		}
			if ((StMem[3][1][0] == 'W' || (StMem[3][1][1]) == 'P') && (StMem[2][2][0] == 'W' || (StMem[2][2][1]) == 'P')) {
				while (dir != 2) {
					TurnLeft();
				}
				GoForward();
			}
			else if ((StMem[2][2][0] == 'W' || (StMem[2][2][1]) == 'P') && (StMem[3][3][0] == 'W' || (StMem[3][3][1]) == 'P')) {
				while (dir != 4) {
					TurnLeft();
				}
				GoForward();
			}
			else if ((StMem[3][1][0] == 'W' || (StMem[3][1][1]) == 'P') && (StMem[3][3][0] == 'W' || (StMem[3][3][1]) == 'P')) {
				while (dir != 3) {
					TurnLeft();
				}
				GoForward();
			}
			else if (StMem[3][1][0] == 'W' || (StMem[3][1][1]) == 'P') {
				while (dir != 3 && dir != 2) {
					TurnLeft();
				}
				GoForward();
			}
			else if (StMem[2][2][0] == 'W' || (StMem[2][2][1]) == 'P') {
				while (dir != 4 && dir != 2) {
					TurnLeft();
				}
				GoForward();
			}
			else if (StMem[3][3][0] == 'W' || (StMem[3][3][1]) == 'P') {
				while (dir != 3 && dir != 4) {
					TurnLeft();
				}
				GoForward();
			}
			else {
				TurnRight();
				GoForward();
			}
			
			
		}
		else if (a == 1 && b == 3) {
		if (map[0][1][2] == 'G') {
			Grab();
		}
		if (map[0][1][0] == 'W') {
			printf("Wumpus를 만나 죽었습니다 (1, 1)에서 부활\n");
			a = 1;
			b = 1;
		}
		if (map[0][1][1] == 'P') {
			printf("Pit에 빠져 죽었습니다 (1, 1)에서 부활\n");
			a = 1;
			b = 1;
		}
			if ((StMem[0][0][0] == 'W') || (StMem[0][0][1] == 'P') && (StMem[1][1][0] == 'W') || (StMem[1][1][1] == 'P')) {
				while (dir != 2) {
					TurnLeft();
				}
				GoForward();
			}
			else if ((StMem[0][0][0] == 'W') || (StMem[0][0][1] == 'P')) {
				while (dir != 1 && dir != 2) {
					TurnLeft();
				}
				GoForward();
			}
			else if ((StMem[1][1][0] == 'W') || (StMem[1][1][1] == 'P')) {
				while (dir != 2 && dir != 4) {
					TurnLeft();
				}
				GoForward();
			}
			else {
				TurnLeft();
				GoForward();
			}
			
			
		}
		else if (a == 2 && b == 3) {
		if (map[1][1][2] == 'G') {
			Grab();
		}
		if (map[1][1][0] == 'W') {
			printf("Wumpus를 만나 죽었습니다 (1, 1)에서 부활\n");
			a = 1;
			b = 1;
		}
		if (map[1][1][1] == 'P') {
			printf("Pit에 빠져 죽었습니다 (1, 1)에서 부활\n");
			a = 1;
			b = 1;
		}
			randir = 0;
			while (randir == 0) {
			randir = rand() % 5;
			}
			while (randir != dir) {
			TurnLeft();
			}
		GoForward();
		
		
		}
		else if (a == 3 && b == 3) {
		if (map[2][1][2] == 'G') {
			Grab();
		}
		if (map[2][1][0] == 'W') {
			printf("Wumpus를 만나 죽었습니다 (1, 1)에서 부활\n");
			a = 1;
			b = 1;
		}
		if (map[2][1][1] == 'P') {
			printf("Pit에 빠져 죽었습니다 (1, 1)에서 부활\n");
		}
			a = 1;
			b = 1;
			randir = 0;
			while (randir == 0) {
			randir = rand() % 5;
			}
			while (randir != dir) {
			TurnLeft();
			}
		GoForward();
		
		
		
		}
		else if (a == 4 && b == 3) {
		if (map[3][1][2] == 'G') {
			Grab();
		}
		if (map[3][1][0] == 'W') {
			printf("Wumpus를 만나 죽었습니다 (1, 1)에서 부활\n");
			a = 1;
			b = 1;
		}
		if (map[3][1][1] == 'P') {
			printf("Pit에 빠져 죽었습니다 (1, 1)에서 부활\n");
			a = 1;
			b = 1;
		}
		if ((StMem[3][0][0] == 'W' || (StMem[3][0][1]) == 'P') && (StMem[2][1][0] == 'W' || (StMem[2][1][1]) == 'P')) {
			while (dir != 4) {
				TurnLeft();
			}
			GoForward();
		}
		else if ((StMem[2][1][0] == 'W' || (StMem[2][1][1]) == 'P') && (StMem[3][2][0] == 'W' || (StMem[3][2][1]) == 'P')) {
			while (dir != 4) {
				TurnLeft();
			}
			GoForward();
		}
		else if ((StMem[3][0][0] == 'W' || (StMem[3][0][1]) == 'P') && (StMem[3][2][0] == 'W' || (StMem[3][2][1]) == 'P')) {
			while (dir != 3) {
				TurnLeft();
			}
			GoForward();
		}
		else if (StMem[3][0][0] == 'W' || (StMem[3][0][1]) == 'P') {
			while (dir != 3 && dir != 2) {
				TurnLeft();
			}
			GoForward();
		}
		else if (StMem[2][1][0] == 'W' || (StMem[2][1][1]) == 'P') {
			while (dir != 4 && dir != 2) {
				TurnLeft();
			}
			GoForward();
		}
		else if (StMem[3][2][0] == 'W' || (StMem[3][2][1]) == 'P') {
			while (dir != 3 && dir != 4) {
				TurnLeft();
			}
			GoForward();
		}
		else {
			TurnRight();
			GoForward();
		}
		
		
		}
		else if (a == 1 && b == 4) {
		if (map[0][0][2] == 'G') {
			Grab();
		}
		if (map[0][0][0] == 'W') {
			printf("Wumpus를 만나 죽었습니다 (1, 1)에서 부활\n");
			a = 1;
			b = 1;
		}
		if (map[0][0][1] == 'P') {
			printf("Pit에 빠져 죽었습니다 (1, 1)에서 부활\n");
			a = 1;
			b = 1;
		}
		if (StMem[0][1][0] == 'W' || StMem[0][1][1] == 'P') {
			while (dir != 1) {
				TurnLeft();
			}
			GoForward();
			}
		else if (StMem[1][0][0] == 'W' || StMem[1][0][1] == 'P') {
			while (dir != 2) {
				TurnLeft();
			}
			GoForward();
		}
		else {
			TurnRight();
			GoForward();
		}
	
		
		}
		else if (a == 2 && b == 4) {
		if (map[1][0][2] == 'G') {
			Grab();
		}
		if (map[1][0][0] == 'W') {
			printf("Wumpus를 만나 죽었습니다 (1, 1)에서 부활\n");
			a = 1;
			b = 1;
		}
		if (map[1][0][1] == 'P') {
			printf("Pit에 빠져 죽었습니다 (1, 1)에서 부활\n");
			a = 1;
			b = 1;
		}
		if ((StMem[0][0][0] == 'W' || (StMem[0][0][1]) == 'P') && (StMem[1][1][0] == 'W' || (StMem[1][1][1]) == 'P')) {
			while (dir != 1) {
				TurnLeft();
			}
			GoForward();
		}
		else if ((StMem[1][1][0] == 'W' || (StMem[1][1][1]) == 'P') && (StMem[2][0][0] == 'W' || (StMem[2][0][1]) == 'P')) {
			while (dir != 3) {
				TurnLeft();
			}
			GoForward();
		}
		else if ((StMem[0][0][0] == 'W' || (StMem[0][0][1]) == 'P') && (StMem[2][0][0] == 'W' || (StMem[2][0][1]) == 'P')) {
			while (dir != 2) {
				TurnLeft();
			}
			GoForward();
		}
		else if (StMem[0][0][0] == 'W' || (StMem[0][0][1]) == 'P') {
			while (dir != 1 && dir != 2) {
				TurnLeft();
			}
			GoForward();
		}
		else if (StMem[1][1][0] == 'W' || (StMem[1][1][1]) == 'P') {
			while (dir != 1 && dir != 3) {
				TurnLeft();
			}
			GoForward();
		}
		else if (StMem[2][0][0] == 'W' || (StMem[2][0][1]) == 'P') {
			while (dir != 2 && dir != 3) {
				TurnLeft();
			}
			GoForward();
		}
		else {
			TurnLeft();
			GoForward();
		}
		
		}
		else if (a == 3 && b == 4) {
		if (map[2][0][2] == 'G') {
			Grab();
		}
		if (map[2][0][0] == 'W') {
			printf("Wumpus를 만나 죽었습니다 (1, 1)에서 부활\n");
			a = 1;
			b = 1;
		}
		if (map[2][0][1] == 'P') {
			printf("Pit에 빠져 죽었습니다 (1, 1)에서 부활\n");
			a = 1;
			b = 1;
		}
		if ((StMem[1][0][0] == 'W' || (StMem[1][0][1]) == 'P') && (StMem[2][1][0] == 'W' || (StMem[2][1][1]) == 'P')) {
			while (dir != 1) {
				TurnLeft();
			}
			GoForward();
		}
		else if ((StMem[2][1][0] == 'W' || (StMem[2][1][1]) == 'P') && (StMem[3][0][0] == 'W' || (StMem[3][0][1]) == 'P')) {
			while (dir != 3) {
				TurnLeft();
			}
			GoForward();
		}
		else if ((StMem[1][0][0] == 'W' || (StMem[1][0][1]) == 'P') && (StMem[3][0][0] == 'W' || (StMem[3][0][1]) == 'P')) {
			while (dir != 2) {
				TurnLeft();
			}
			GoForward();
		}
		else if (StMem[1][0][0] == 'W' || (StMem[1][0][1]) == 'P') {
			while (dir != 1 && dir != 2) {
				TurnLeft();
			}
			GoForward();
		}
		else if (StMem[2][1][0] == 'W' || (StMem[2][1][1]) == 'P') {
			while (dir != 1 && dir != 3) {
				TurnLeft();
			}
			GoForward();
		}
		else if (StMem[3][0][0] == 'W' || (StMem[3][0][1]) == 'P') {
			while (dir != 2 && dir != 3) {
				TurnLeft();
			}
			GoForward();
		}
		else {
			TurnRight();
			GoForward();
		}
		
		}
		else if (a == 4 && b == 4) {
		if (map[3][0][2] == 'G') {
			Grab();
		}
		if (map[3][0][0] == 'W') {
			printf("Wumpus를 만나 죽었습니다 (1, 1)에서 부활\n");
			a = 1;
			b = 1;
		}
		if (map[3][0][1] == 'P') {
			printf("Pit에 빠져 죽었습니다 (1, 1)에서 부활\n");
			a = 1;
			b = 1;
		}
		if (StMem[2][0][0] == 'W' || (StMem[2][0][1]) == 'P') {
			while (dir != 2) {
				TurnLeft();
			}
			GoForward();
			}
		else if (StMem[3][1][0] == 'W' || (StMem[3][1][1]) == 'P') {
			while (dir != 3) {
				TurnLeft();
			}
			GoForward();
		}
		else {
			TurnLeft();
			GoForward();
		}
		
		}
		Shoot();
		save();
		bumpcheck();


	
		
	}

	if (goldpicked == 1) {
		while (a != 1 || b != 1) {
			save();
			bumpcheck();
			if (a == 1 && b == 1) {
				randir = rand() % 2;
				if (randir == 0) {
					while (dir != 1) {
						TurnLeft();
					}
					GoForward();
				}
				else if (randir == 1) {
					while (dir != 4) {
						TurnLeft();
					}
					GoForward();
				}
			}
			else if (a == 2 && b == 1) {
				if ((StMem[a][4 - b][0] == 'W' || StMem[a][4 - b][1] == 'P') && (StMem[a - 1][3 - b][0] == 'W' || StMem[a - 1][3 - b][1] == 'P')) {
					while (dir != 3) {
						TurnLeft();
					}
					GoForward();
				}
				else if (StMem[a][4 - b][0] == 'W' || StMem[a][4 - b][1] == 'P') {
					while (dir != 3 && dir != 4) {
						TurnLeft();
					}
					GoForward();
				}
				else if (StMem[a - 1][3 - b][0] == 'W' || StMem[a - 1][3 - b][1] == 'P') {
					while (dir != 1 && dir != 3) {
						TurnLeft();
					}
					GoForward();
				}
				else {
					TurnLeft();
					GoForward();
				}
			}
			else if (a == 3 && b == 1) {
				if (map[2][3][0] == 'W') {
					printf("Wumpus를 만나 죽었습니다 (1, 1)에서 부활\n");
					a = 1;
					b = 1;
				}
				if (map[2][3][1] == 'P') {
					printf("Pit에 빠져 죽었습니다 (1, 1)에서 부활\n");
					a = 1;
					b = 1;
				}
				if ((StMem[a][4 - b][0] == 'W' || StMem[a][4 - b][1] == 'P') && (StMem[a - 1][3 - b][0] == 'W' || StMem[a - 1][3 - b][1] == 'P')) {
					while (dir != 3) {
						TurnLeft();
					}
					GoForward();
				}
				else if (StMem[a][4 - b][0] == 'W' || StMem[a][4 - b][1] == 'P') {
					while (dir != 3 && dir != 4) {
						TurnLeft();
					}
					GoForward();
				}
				else if (StMem[a - 1][3 - b][0] == 'W' || StMem[a - 1][3 - b][1] == 'P') {
					while (dir != 1 && dir != 3) {
						TurnLeft();
					}
					GoForward();
				}
				else {
					TurnLeft();
					GoForward();
				}


			}
			else if (a == 4 && b == 1) {
				if (map[3][3][0] == 'W') {
					printf("Wumpus를 만나 죽었습니다 (1, 1)에서 부활\n");
					a = 1;
					b = 1;
				}
				if (map[3][3][1] == 'P') {
					printf("Pit에 빠져 죽었습니다 (1, 1)에서 부활\n");
					a = 1;
					b = 1;
				}
				if (StMem[a - 1][3 - b][0] == 'W' || StMem[a - 1][3 - b][0] == 'P') {
					while (dir != 3) {
						TurnLeft();
					}
					GoForward();
				}
				else if (StMem[a - 2][4 - b][0] == 'W' || StMem[a - 2][4 - b][0] == 'P') {
					while (dir != 4) {
						TurnLeft();
					}
					GoForward();
				}
				else {
					TurnLeft();
					GoForward();
				}
			}
			else if (a == 1 && b == 2) {
				if ((StMem[a - 2][4 - b][0] == 'W' || StMem[a][4 - b][1] == 'P') && (StMem[a - 1][3 - b][0] == 'W' || StMem[a - 1][3 - b][1] == 'P')) {
					while (dir != 2) {
						TurnLeft();
					}
					GoForward();
				}
				else if (StMem[a - 2][4 - b][0] == 'W' || StMem[a][4 - b][1] == 'P') {
					while (dir != 3 && dir != 4) {
						TurnLeft();
					}
					GoForward();
				}
				else if (StMem[a - 1][3 - b][0] == 'W' || StMem[a - 1][3 - b][1] == 'P') {
					while (dir != 1 && dir != 3) {
						TurnLeft();
					}
					GoForward();
				}
				else {
					TurnRight();
					GoForward();
				}
			}
			else if (a == 2 && b == 2) {
			if (map[1][2][0] == 'W') {
				printf("Wumpus를 만나 죽었습니다 (1, 1)에서 부활\n");
				a = 1;
				b = 1;
			}
			if (map[1][2][1] == 'P') {
				printf("Pit에 빠져 죽었습니다 (1, 1)에서 부활\n");
				a = 1;
				b = 1;
			}
				randir = 0;
				while (randir == 0) {
					randir = rand() % 5;
				}
				while (randir != dir) {
					TurnLeft();
				}
				GoForward();

			}
			else if (a == 3 && b == 2) {
			if (map[2][2][0] == 'W') {
				printf("Wumpus를 만나 죽었습니다 (1, 1)에서 부활\n");
				a = 1;
				b = 1;
			}
			if (map[2][2][1] == 'P') {
				printf("Pit에 빠져 죽었습니다 (1, 1)에서 부활\n");
				a = 1;
				b = 1;
			}
				randir = 0;
				while (randir == 0) {
					randir = rand() % 5;
				}
				while (randir != dir) {
					TurnLeft();
				}
				GoForward();
			}
			else if (a == 4 && b == 2) {
			if (map[3][2][0] == 'W') {
				printf("Wumpus를 만나 죽었습니다 (1, 1)에서 부활\n");
				a = 1;
				b = 1;
			}
			if (map[3][2][1] == 'P') {
				printf("Pit에 빠져 죽었습니다 (1, 1)에서 부활\n");
				a = 1;
				b = 1;
			}
				if ((StMem[3][1][0] == 'W' || (StMem[3][1][1]) == 'P') && (StMem[2][2][0] == 'W' || (StMem[2][2][1]) == 'P')) {
					while (dir != 2) {
						TurnLeft();
					}
					GoForward();
				}
				else if ((StMem[2][2][0] == 'W' || (StMem[2][2][1]) == 'P') && (StMem[3][3][0] == 'W' || (StMem[3][3][1]) == 'P')) {
					while (dir != 4) {
						TurnLeft();
					}
					GoForward();
				}
				else if ((StMem[3][1][0] == 'W' || (StMem[3][1][1]) == 'P') && (StMem[3][3][0] == 'W' || (StMem[3][3][1]) == 'P')) {
					while (dir != 3) {
						TurnLeft();
					}
					GoForward();
				}
				else if (StMem[3][1][0] == 'W' || (StMem[3][1][1]) == 'P') {
					while (dir != 3 && dir != 2) {
						TurnLeft();
					}
					GoForward();
				}
				else if (StMem[2][2][0] == 'W' || (StMem[2][2][1]) == 'P') {
					while (dir != 4 && dir != 2) {
						TurnLeft();
					}
					GoForward();
				}
				else if (StMem[3][3][0] == 'W' || (StMem[3][3][1]) == 'P') {
					while (dir != 3 && dir != 4) {
						TurnLeft();
					}
					GoForward();
				}
				else {
					TurnRight();
					GoForward();
				}
			}
			else if (a == 1 && b == 3) {
			if (map[0][1][0] == 'W') {
				printf("Wumpus를 만나 죽었습니다 (1, 1)에서 부활\n");
				a = 1;
				b = 1;
			}
			if (map[0][1][1] == 'P') {
				printf("Pit에 빠져 죽었습니다 (1, 1)에서 부활\n");
				a = 1;
				b = 1;
			}
				if ((StMem[0][0][0] == 'W') || (StMem[0][0][1] == 'P') && (StMem[1][1][0] == 'W') || (StMem[1][1][1] == 'P')) {
					while (dir != 2) {
						TurnLeft();
					}
					GoForward();
				}
				else if ((StMem[0][0][0] == 'W') || (StMem[0][0][1] == 'P')) {
					while (dir != 1 && dir != 2) {
						TurnLeft();
					}
					GoForward();
				}
				else if ((StMem[1][1][0] == 'W') || (StMem[1][1][1] == 'P')) {
					while (dir != 2 && dir != 4) {
						TurnLeft();
					}
					GoForward();
				}
				else {
					TurnLeft();
					GoForward();
				}
			}
			else if (a == 2 && b == 3) {
			if (map[1][1][0] == 'W') {
				printf("Wumpus를 만나 죽었습니다 (1, 1)에서 부활\n");
				a = 1;
				b = 1;
			}
			if (map[1][1][1] == 'P') {
				printf("Pit에 빠져 죽었습니다 (1, 1)에서 부활\n");
				a = 1;
				b = 1;
			}
				randir = 0;
				while (randir == 0) {
					randir = rand() % 5;
				}
				while (randir != dir) {
					TurnLeft();
				}
				GoForward();
			}
			else if (a == 3 && b == 3) {
			if (map[2][1][0] == 'W') {
				printf("Wumpus를 만나 죽었습니다 (1, 1)에서 부활\n");
				a = 1;
				b = 1;
			}
			if (map[2][1][1] == 'P') {
				printf("Pit에 빠져 죽었습니다 (1, 1)에서 부활\n");
				a = 1;
				b = 1;
			}
				randir = 0;
				while (randir == 0) {
					randir = rand() % 5;
				}
				while (randir != dir) {
					TurnLeft();
				}
				GoForward();
			}
			else if (a == 4 && b == 3) {
			if (map[3][1][0] == 'W') {
				printf("Wumpus를 만나 죽었습니다 (1, 1)에서 부활\n");
				a = 1;
				b = 1;
			}
			if (map[3][1][1] == 'P') {
				printf("Pit에 빠져 죽었습니다 (1, 1)에서 부활\n");
				a = 1;
				b = 1;
			}
				if ((StMem[3][0][0] == 'W' || (StMem[3][0][1]) == 'P') && (StMem[2][1][0] == 'W' || (StMem[2][1][1]) == 'P')) {
					while (dir != 4) {
						TurnLeft();
					}
					GoForward();
				}
				else if ((StMem[2][1][0] == 'W' || (StMem[2][1][1]) == 'P') && (StMem[3][2][0] == 'W' || (StMem[3][2][1]) == 'P')) {
					while (dir != 4) {
						TurnLeft();
					}
					GoForward();
				}
				else if ((StMem[3][0][0] == 'W' || (StMem[3][0][1]) == 'P') && (StMem[3][2][0] == 'W' || (StMem[3][2][1]) == 'P')) {
					while (dir != 3) {
						TurnLeft();
					}
					GoForward();
				}
				else if (StMem[3][0][0] == 'W' || (StMem[3][0][1]) == 'P') {
					while (dir != 3 && dir != 2) {
						TurnLeft();
					}
					GoForward();
				}
				else if (StMem[2][1][0] == 'W' || (StMem[2][1][1]) == 'P') {
					while (dir != 4 && dir != 2) {
						TurnLeft();
					}
					GoForward();
				}
				else if (StMem[3][2][0] == 'W' || (StMem[3][2][1]) == 'P') {
					while (dir != 3 && dir != 4) {
						TurnLeft();
					}
					GoForward();
				}
				else {
					TurnRight();
					GoForward();
				}
			}
			else if (a == 1 && b == 4) {
			if (map[0][0][0] == 'W') {
				printf("Wumpus를 만나 죽었습니다 (1, 1)에서 부활\n");
				a = 1;
				b = 1;
			}
			if (map[0][0][1] == 'P') {
				printf("Pit에 빠져 죽었습니다 (1, 1)에서 부활\n");
				a = 1;
				b = 1;
			}
				if (StMem[0][1][0] == 'W' || StMem[0][1][1] == 'P') {
					while (dir != 1) {
						TurnLeft();
					}
					GoForward();
				}
				else if (StMem[1][0][0] == 'W' || StMem[1][0][1] == 'P') {
					while (dir != 2) {
						TurnLeft();
					}
					GoForward();
				}
				else {
					TurnRight();
					GoForward();
				}
			}
			else if (a == 2 && b == 4) {
			if (map[1][0][0] == 'W') {
				printf("Wumpus를 만나 죽었습니다 (1, 1)에서 부활\n");
				a = 1;
				b = 1;
			}
			if (map[1][0][1] == 'P') {
				printf("Pit에 빠져 죽었습니다 (1, 1)에서 부활\n");
				a = 1;
				b = 1;
			}
				if ((StMem[0][0][0] == 'W' || (StMem[0][0][1]) == 'P') && (StMem[1][1][0] == 'W' || (StMem[1][1][1]) == 'P')) {
					while (dir != 1) {
						TurnLeft();
					}
					GoForward();
				}
				else if ((StMem[1][1][0] == 'W' || (StMem[1][1][1]) == 'P') && (StMem[2][0][0] == 'W' || (StMem[2][0][1]) == 'P')) {
					while (dir != 3) {
						TurnLeft();
					}
					GoForward();
				}
				else if ((StMem[0][0][0] == 'W' || (StMem[0][0][1]) == 'P') && (StMem[2][0][0] == 'W' || (StMem[2][0][1]) == 'P')) {
					while (dir != 2) {
						TurnLeft();
					}
					GoForward();
				}
				else if (StMem[0][0][0] == 'W' || (StMem[0][0][1]) == 'P') {
					while (dir != 1 && dir != 2) {
						TurnLeft();
					}
					GoForward();
				}
				else if (StMem[1][1][0] == 'W' || (StMem[1][1][1]) == 'P') {
					while (dir != 1 && dir != 3) {
						TurnLeft();
					}
					GoForward();
				}
				else if (StMem[2][0][0] == 'W' || (StMem[2][0][1]) == 'P') {
					while (dir != 2 && dir != 3) {
						TurnLeft();
					}
					GoForward();
				}
				else {
					TurnLeft();
					GoForward();
				}
			}
			else if (a == 3 && b == 4) {
			if (map[2][0][0] == 'W') {
				printf("Wumpus를 만나 죽었습니다 (1, 1)에서 부활\n");
				a = 1;
				b = 1;
			}
			if (map[2][0][1] == 'P') {
				printf("Pit에 빠져 죽었습니다 (1, 1)에서 부활\n");
				a = 1;
				b = 1;
			}
				if ((StMem[1][0][0] == 'W' || (StMem[1][0][1]) == 'P') && (StMem[2][1][0] == 'W' || (StMem[2][1][1]) == 'P')) {
					while (dir != 1) {
						TurnLeft();
					}
					GoForward();
				}
				else if ((StMem[2][1][0] == 'W' || (StMem[2][1][1]) == 'P') && (StMem[3][0][0] == 'W' || (StMem[3][0][1]) == 'P')) {
					while (dir != 3) {
						TurnLeft();
					}
					GoForward();
				}
				else if ((StMem[1][0][0] == 'W' || (StMem[1][0][1]) == 'P') && (StMem[3][0][0] == 'W' || (StMem[3][0][1]) == 'P')) {
					while (dir != 2) {
						TurnLeft();
					}
					GoForward();
				}
				else if (StMem[1][0][0] == 'W' || (StMem[1][0][1]) == 'P') {
					while (dir != 1 && dir != 2) {
						TurnLeft();
					}
					GoForward();
				}
				else if (StMem[2][1][0] == 'W' || (StMem[2][1][1]) == 'P') {
					while (dir != 1 && dir != 3) {
						TurnLeft();
					}
					GoForward();
				}
				else if (StMem[3][0][0] == 'W' || (StMem[3][0][1]) == 'P') {
					while (dir != 2 && dir != 3) {
						TurnLeft();
					}
					GoForward();
				}
				else {
					TurnRight();
					GoForward();
				}
			}
			else if (a == 4 && b == 4) {
			if (map[3][0][0] == 'W') {
				printf("Wumpus를 만나 죽었습니다 (1, 1)에서 부활\n");
				a = 1;
				b = 1;
			}
			if (map[3][0][1] == 'P') {
				printf("Pit에 빠져 죽었습니다 (1, 1)에서 부활\n");
				a = 1;
				b = 1;
			}
				if (StMem[2][0][0] == 'W' || (StMem[2][0][1]) == 'P') {
					while (dir != 2) {
						TurnLeft();
					}
					GoForward();
				}
				else if (StMem[3][1][0] == 'W' || (StMem[3][1][1]) == 'P') {
					while (dir != 3) {
						TurnLeft();
					}
					GoForward();
				}
				else {
					TurnLeft();
					GoForward();
				}
			}
			Shoot();
			save();
			bumpcheck();
			}
		}
	

	Climb();

	system("pause");
	return 0;
}