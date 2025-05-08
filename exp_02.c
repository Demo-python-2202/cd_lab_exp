#include <stdio.h>

int main() {
    FILE *fp = fopen("dfa.txt", "r");
    int Fa[10][10];               // DFA transition table
    int states[3][10];            // 0: start state, 1: final states, 2: optional
    int row = 0, col = 0, sr = 0, sc = 0;
    int in, curr, i, j, flag = 0;
    char str[100], k;

    if (!fp) {
        printf("File could not be found\n");
        return 1;
    }

    // Initialize states array
    for (i = 0; i < 3; i++)
        for (j = 0; j < 10; j++)
            states[i][j] = -1;

    // Read file
    while (fscanf(fp, "%d", &in) != EOF) {
        k = fgetc(fp);
        if (flag)
            states[sr][sc++] = in;
        else
            Fa[row][col++] = in;

        if (k == '\n') {
            if (flag) {
                sr++;
                sc = 0;
            } else {
                row++;
                col = 0;
            }
        } else if (k == '#') {
            flag = 1;
        }
    }

    fclose(fp);

    while (1) {
        printf("\n Construction of DFA");
        printf("\nEnter the string: ");
        scanf("%s", str);
        curr = states[0][0];  // start state
        printf("%d", curr);

        for (i = 0; str[i] != '\0'; i++) {
            int next = Fa[curr][str[i] - 'a'];
            printf(" %c %d", str[i], next);
            if (next == -1) break;
            curr = next;
        }

        flag = 0;
        for (i = 0; i < 10 && states[1][i] != -1; i++) {
            if (curr == states[1][i]) {
                flag = 1;
                break;
            }
        }

        printf("\nSTRING %s\n", flag ? "ACCEPTED" : "NOT ACCEPTED");
    }

    return 0;
}

// aab is string accepted
// aba, abbb, abaa, abbb, bbbb is not string accepted
