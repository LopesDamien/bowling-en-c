#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_PLAYERS 6
#define MAX_FRAMES 10

typedef struct {
	char nom[32];
	int score[MAX_FRAMES][2];
	int total;
} Player;

int NombreJoueur() {
	int LesJoueurs;
	printf("Combien de joueurs souhaitez-vous (2-%d) ? ", MAX_PLAYERS);
	scanf("%d", &LesJoueurs);
	while (LesJoueurs < 2 || LesJoueurs > MAX_PLAYERS) {
		printf("Le nombre de joueurs doit etre compris entre 2 et %d. Reessayez : ", MAX_PLAYERS);
		scanf("%d", &LesJoueurs);
	}

	return LesJoueurs;
}

void NomJoueur(Player users[], int Nb) {
	printf("Entrez les noms des joueurs :\n");
	for (int i = 0; i < Nb; i++) {
		printf("Joueur %d : ", i + 1);
		scanf("%s", users[i].nom);
	}
}

void Jeu(Player players[], int Nbr) {
	for (int i = 0; i < Nbr; i++) {
		for (int frame = 0; frame < MAX_FRAMES; frame++) {
			if (frame > 0) {
				printf("Score des lancer : %d %d\n", players[i].score[frame - 1][0], players[i].score[frame - 1][1]);
			}
			printf("%s, appuyez sur * pour lancer la boule : ", players[i].nom);
			char input;
			scanf(" %c", &input);
			int lancer1 = rand() % 11;
			int lancer2 = rand() % (11 - lancer1);


			players[i].score[frame][0] = lancer1;
			players[i].score[frame][1] = lancer2;
		}


	}
}
void calculerScores(Player players[], int Nbre) {
	for (int i = 0; i < Nbre; i++) {
		int total = 0;
		for (int frame = 0; frame < MAX_FRAMES; frame++) {
			if (players[i].score[frame][0] == 10) {
				// Strike
				total += 10 + players[i].score[frame + 1][0] * 2 + players[i].score[frame + 1][1] * 2;
			}
			else if (players[i].score[frame][0] + players[i].score[frame][1] == 10) {
				// Spare
				total += 10 + players[i].score[frame + 1][0] * 2;
			}
			else {
				total += players[i].score[frame][0] + players[i].score[frame][1];
			}
		}
	}
}
void afficherScores(Player players[], int numPlayers) {
	printf("\nScores :\n");

	for (int i = 0; i < numPlayers; i++) {
		printf("%s :\n", players[i].nom);
		int total = 0;
		for (int frame = 0; frame < MAX_FRAMES; frame++) {
			total += players[i].score[frame][0] + players[i].score[frame][1];
			if (players[i].score[frame][0] == 10) {
				printf("X ");
			}
			else {
				printf("%d ", players[i].score[frame][0]);
			}
			if (players[i].score[frame][0] + players[i].score[frame][1] == 10) {
				printf("/ ");
			}
			else {
				printf("%d ", players[i].score[frame][1]);
			}

			printf("(%d)\n", total);
		}

	}

}

int main() {
	srand(time(NULL));
	Player players[MAX_PLAYERS];
	int numPlayers = NombreJoueur();
	NomJoueur(players, numPlayers);
	Jeu(players, numPlayers);
	calculerScores(players, numPlayers);
	afficherScores(players, numPlayers);

	return 0;
}