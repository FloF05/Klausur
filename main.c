#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TEAMS 20

typedef struct {
    char name[50];
    int points;
    int goalsScored;
    int goalsConceded;
} Team;

void initializeTable(Team teams[], int numTeams) {
    for (int i = 0; i < numTeams; i++) {
        printf("Enter the name of team %d: ", i + 1);
        scanf("%s", teams[i].name);
        teams[i].points = 0;
        teams[i].goalsScored = 0;
        teams[i].goalsConceded = 0;
    }
}

void printTable(Team teams[], int numTeams) {
    printf("\nBundesliga Table\n");
    printf("%-20s %-8s %-10s %-10s\n", "Team", "Points", "Goals For", "Goals Against");
    for (int i = 0; i < numTeams; i++) {
        printf("%-20s %-8d %-10d %-10d\n", teams[i].name, teams[i].points, teams[i].goalsScored, teams[i].goalsConceded);
    }
    printf("\n");
}

void updateTable(Team teams[], int numTeams, int team1Index, int team2Index, int goals1, int goals2) {
    // Update team1 statistics
    teams[team1Index].goalsScored += goals1;
    teams[team1Index].goalsConceded += goals2;

    // Update team2 statistics
    teams[team2Index].goalsScored += goals2;
    teams[team2Index].goalsConceded += goals1;

    // Update points based on the match result
    if (goals1 > goals2) {
        teams[team1Index].points += 3; // Team1 won
    } else if (goals1 < goals2) {
        teams[team2Index].points += 3; // Team2 won
    } else {
        teams[team1Index].points += 1; // It's a draw
        teams[team2Index].points += 1;
    }
}

int main() {
    int numTeams;

    printf("Enter the number of teams in the Bundesliga: ");
    scanf("%d", &numTeams);

    if (numTeams > MAX_TEAMS) {
        printf("Maximum number of teams allowed is %d\n", MAX_TEAMS);
        return 1;
    }

    Team teams[MAX_TEAMS];
    initializeTable(teams, numTeams);

    int numMatches = numTeams * (numTeams - 1);

    for (int i = 0; i < numMatches; i++) {
        int team1, team2, goals1, goals2;
        printf("\nEnter the details for match %d (team1 vs team2 goals1-goals2): ", i + 1);
        scanf("%d %d %d-%d", &team1, &team2, &goals1, &goals2);

        // Adjust team1 and team2 to array indices
        team1--;
        team2--;

        // Update the table based on the match result
        updateTable(teams, numTeams, team1, team2, goals1, goals2);
    }

    // Print the final table
    printTable(teams, numTeams);

    return 0;
}
