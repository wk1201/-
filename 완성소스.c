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
int Visited[4][4] = {	//�湮�� �� Ȯ�ο� �迭
	{0,0,0,0},
	{0,0,0,0},
	{0,0,0,0},
	{0,0,0,0}
};
int dir = 1; // ���� ���� 1: ���� 2: ���� 3: ����  4: ����
int a = 1;
int b = 1;	//������ġ (a,b)
int scream = 0; //������ ���̴µ� �����ϸ� 1�� ��
int goldpicked = 0;	//�� grab �ϸ� 1
int arrow = 3;
int bump = 0;	//�浹�� 1 TurnLeft TurnRight �� 0
int out = 0;	//���� ������ 1
int death = 0;    //wumpus�� ȭ���� ������ 0���� �ٲ�
int randir = 0;	//������ �������� ������ �� ����ϴ� ����
int bumpcheckvar = 0;
int GoForward() {
	Visited[a - 1][4 - b] = 1;
	if (dir == 1) {
		if (a >= 1 && a <= 3) {
			a = a + 1;
		}
		else {
			bump = 1;
			printf("���� Bump ����\n");
		}
	}
	else if (dir == 2) {
		if (b >= 2 && b <= 4) {
			b = b - 1;
		}
		else {
			bump = 1;
			printf("���� Bump ����\n");
		}
	}
	else if (dir == 3) {
		if (a >= 2 && a <= 4) {
			a = a - 1;
		}
		else {
			bump = 1;
			printf("���� Bump ����\n");
		}
	}
	else if (dir == 4) {
		if (b >= 1 && b <= 3) {
			b = b + 1;
		}
		else {
			bump = 1;
			printf("���� Bump ����\n");
		}
		
	}
	printf("Agent�� (%d, %d)�� �̵�\n", a, b);



	Visited[a - 1][4 - b] = 1;	//�湮�� �� ���
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
		printf("�������� ���� ��ȯ\n");
		break;
	case 2:
		printf("�������� ���� ��ȯ\n");
		break;
	case 3:
		printf("�������� ���� ��ȯ\n");
		break;
	case 4:
		printf("�������� ���� ��ȯ\n");
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
		printf("�������� ���� ��ȯ\n");
		break;
	case 2:
		printf("�������� ���� ��ȯ\n");
		break;
	case 3:
		printf("�������� ���� ��ȯ\n");
		break;
	case 4:
		printf("�������� ���� ��ȯ\n");
		break;
	}
}

int Grab() {
		goldpicked = 1;
		printf("���� �ֿ����ϴ�\n");
}

int Shoot() {
	if ((arrow > 0 && death == 0) && map[a - 1][4 - b][3] == 'S') {
		arrow = arrow - 1;
		printf("ȭ�� �߻�\n");
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
			printf("Agent�� Scream�� ������\n");
		}
		else {
			printf("Agent�� ȭ���� �߻������� Scream�� �������� ����\n");
		}
	}
}



int Climb() {
	if (a == 1 && b == 1 && goldpicked == 1) {
		printf("������Ʈ�� ���� ȹ���� ������ �����������ϴ�.\n");
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

	printf("Agent�� ���� ��ġ: (1, 1) ����: ����\n");


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
				printf("Wumpus�� ���� �׾����ϴ� (1, 1)���� ��Ȱ\n");
				a = 1;
				b = 1;
			}
			if (map[2][3][1] == 'P'){
				printf("Pit�� ���� �׾����ϴ� (1, 1)���� ��Ȱ\n");
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
				printf("Wumpus�� ���� �׾����ϴ� (1, 1)���� ��Ȱ\n");
				a = 1;
				b = 1;
			}
			if (map[3][3][1] == 'P') {
				printf("Pit�� ���� �׾����ϴ� (1, 1)���� ��Ȱ\n");
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
			printf("Wumpus�� ���� �׾����ϴ� (1, 1)���� ��Ȱ\n");
			a = 1;
			b = 1;
		}
		if (map[1][2][1] == 'P') {
			printf("Pit�� ���� �׾����ϴ� (1, 1)���� ��Ȱ\n");
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
			printf("Wumpus�� ���� �׾����ϴ� (1, 1)���� ��Ȱ\n");
			a = 1;
			b = 1;
		}
		if (map[2][2][1] == 'P') {
			printf("Pit�� ���� �׾����ϴ� (1, 1)���� ��Ȱ\n");
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
			printf("Wumpus�� ���� �׾����ϴ� (1, 1)���� ��Ȱ\n");
			a = 1;
			b = 1;
		}
		if (map[3][2][1] == 'P') {
			printf("Pit�� ���� �׾����ϴ� (1, 1)���� ��Ȱ\n");
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
			printf("Wumpus�� ���� �׾����ϴ� (1, 1)���� ��Ȱ\n");
			a = 1;
			b = 1;
		}
		if (map[0][1][1] == 'P') {
			printf("Pit�� ���� �׾����ϴ� (1, 1)���� ��Ȱ\n");
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
			printf("Wumpus�� ���� �׾����ϴ� (1, 1)���� ��Ȱ\n");
			a = 1;
			b = 1;
		}
		if (map[1][1][1] == 'P') {
			printf("Pit�� ���� �׾����ϴ� (1, 1)���� ��Ȱ\n");
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
			printf("Wumpus�� ���� �׾����ϴ� (1, 1)���� ��Ȱ\n");
			a = 1;
			b = 1;
		}
		if (map[2][1][1] == 'P') {
			printf("Pit�� ���� �׾����ϴ� (1, 1)���� ��Ȱ\n");
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
			printf("Wumpus�� ���� �׾����ϴ� (1, 1)���� ��Ȱ\n");
			a = 1;
			b = 1;
		}
		if (map[3][1][1] == 'P') {
			printf("Pit�� ���� �׾����ϴ� (1, 1)���� ��Ȱ\n");
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
			printf("Wumpus�� ���� �׾����ϴ� (1, 1)���� ��Ȱ\n");
			a = 1;
			b = 1;
		}
		if (map[0][0][1] == 'P') {
			printf("Pit�� ���� �׾����ϴ� (1, 1)���� ��Ȱ\n");
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
			printf("Wumpus�� ���� �׾����ϴ� (1, 1)���� ��Ȱ\n");
			a = 1;
			b = 1;
		}
		if (map[1][0][1] == 'P') {
			printf("Pit�� ���� �׾����ϴ� (1, 1)���� ��Ȱ\n");
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
			printf("Wumpus�� ���� �׾����ϴ� (1, 1)���� ��Ȱ\n");
			a = 1;
			b = 1;
		}
		if (map[2][0][1] == 'P') {
			printf("Pit�� ���� �׾����ϴ� (1, 1)���� ��Ȱ\n");
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
			printf("Wumpus�� ���� �׾����ϴ� (1, 1)���� ��Ȱ\n");
			a = 1;
			b = 1;
		}
		if (map[3][0][1] == 'P') {
			printf("Pit�� ���� �׾����ϴ� (1, 1)���� ��Ȱ\n");
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
					printf("Wumpus�� ���� �׾����ϴ� (1, 1)���� ��Ȱ\n");
					a = 1;
					b = 1;
				}
				if (map[2][3][1] == 'P') {
					printf("Pit�� ���� �׾����ϴ� (1, 1)���� ��Ȱ\n");
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
					printf("Wumpus�� ���� �׾����ϴ� (1, 1)���� ��Ȱ\n");
					a = 1;
					b = 1;
				}
				if (map[3][3][1] == 'P') {
					printf("Pit�� ���� �׾����ϴ� (1, 1)���� ��Ȱ\n");
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
				printf("Wumpus�� ���� �׾����ϴ� (1, 1)���� ��Ȱ\n");
				a = 1;
				b = 1;
			}
			if (map[1][2][1] == 'P') {
				printf("Pit�� ���� �׾����ϴ� (1, 1)���� ��Ȱ\n");
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
				printf("Wumpus�� ���� �׾����ϴ� (1, 1)���� ��Ȱ\n");
				a = 1;
				b = 1;
			}
			if (map[2][2][1] == 'P') {
				printf("Pit�� ���� �׾����ϴ� (1, 1)���� ��Ȱ\n");
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
				printf("Wumpus�� ���� �׾����ϴ� (1, 1)���� ��Ȱ\n");
				a = 1;
				b = 1;
			}
			if (map[3][2][1] == 'P') {
				printf("Pit�� ���� �׾����ϴ� (1, 1)���� ��Ȱ\n");
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
				printf("Wumpus�� ���� �׾����ϴ� (1, 1)���� ��Ȱ\n");
				a = 1;
				b = 1;
			}
			if (map[0][1][1] == 'P') {
				printf("Pit�� ���� �׾����ϴ� (1, 1)���� ��Ȱ\n");
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
				printf("Wumpus�� ���� �׾����ϴ� (1, 1)���� ��Ȱ\n");
				a = 1;
				b = 1;
			}
			if (map[1][1][1] == 'P') {
				printf("Pit�� ���� �׾����ϴ� (1, 1)���� ��Ȱ\n");
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
				printf("Wumpus�� ���� �׾����ϴ� (1, 1)���� ��Ȱ\n");
				a = 1;
				b = 1;
			}
			if (map[2][1][1] == 'P') {
				printf("Pit�� ���� �׾����ϴ� (1, 1)���� ��Ȱ\n");
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
				printf("Wumpus�� ���� �׾����ϴ� (1, 1)���� ��Ȱ\n");
				a = 1;
				b = 1;
			}
			if (map[3][1][1] == 'P') {
				printf("Pit�� ���� �׾����ϴ� (1, 1)���� ��Ȱ\n");
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
				printf("Wumpus�� ���� �׾����ϴ� (1, 1)���� ��Ȱ\n");
				a = 1;
				b = 1;
			}
			if (map[0][0][1] == 'P') {
				printf("Pit�� ���� �׾����ϴ� (1, 1)���� ��Ȱ\n");
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
				printf("Wumpus�� ���� �׾����ϴ� (1, 1)���� ��Ȱ\n");
				a = 1;
				b = 1;
			}
			if (map[1][0][1] == 'P') {
				printf("Pit�� ���� �׾����ϴ� (1, 1)���� ��Ȱ\n");
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
				printf("Wumpus�� ���� �׾����ϴ� (1, 1)���� ��Ȱ\n");
				a = 1;
				b = 1;
			}
			if (map[2][0][1] == 'P') {
				printf("Pit�� ���� �׾����ϴ� (1, 1)���� ��Ȱ\n");
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
				printf("Wumpus�� ���� �׾����ϴ� (1, 1)���� ��Ȱ\n");
				a = 1;
				b = 1;
			}
			if (map[3][0][1] == 'P') {
				printf("Pit�� ���� �׾����ϴ� (1, 1)���� ��Ȱ\n");
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