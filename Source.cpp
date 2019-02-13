#include <cstdio>
#include <iostream>
#include <ctime>

using namespace std;

int roll(int x) {
	if (x == 0) return 0;
	return roll(x - 1) + (rand() % 2);
}

class Creature {
protected:
	int maxHP;
public:
	int HP, ATK, DEF;
	void attack(Creature*);
	bool isDead() {
		if (HP <= 0) return true;
		else return false;
	}
	int getMaxHP() {
		return maxHP;
	}
};

void Creature::attack(Creature* defender) {
	int x = roll(ATK);
	if (x == 0) {
		// Critical Failure
		HP -= ATK;
	}
	else {
		if (x == ATK) {
			// Critical Success
			(*defender).HP -= ATK;
		}
		else {
			if ((*defender).DEF < x) {
				(*defender).HP -= (x - (*defender).DEF);
			}
		}
	}
}

class Monster : public Creature {
public:
	int LVL;
	Monster(int level) {
		LVL = level;
		maxHP = level * 2;
		HP = maxHP;
		ATK = level;
		DEF = level;
	}
};


class Hero : public Creature {
public:
	Hero(int Health, int Attack, int Defense) {
		HP = Health;
		ATK = Attack;
		DEF = Defense;
	}
};

int main() {
	srand(time(0));
	int q1, q2, q3, q4;
	cout << "Enter Hero stats (Health, Attack and Defense):\n";
	cin >> q1 >> q2 >> q3;
	Creature* hero = new Hero(q1, q2, q3);
	cout << "Enter Monster level:\n";
	cin >> q4;
	int chance = 0;
	for (int i = 0; i < 100000; i++) {
		Creature* hero = new Hero(q1, q2, q3);
		Creature* dragon = new Monster(q1);
		while (!(*hero).isDead() && !(*dragon).isDead()) {
			(*hero).attack(dragon);
			(*dragon).attack(hero);
		}
		if ((*dragon).isDead()) chance++;
	}
	cout << chance << " out of " << 100000 << " tries were succesful";
	return 0;
}