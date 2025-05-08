#include <stdio.h>
#include <string.h>

int main() {
    // NFA[state][input_symbol][next_states]
    int nfa[3][2][3] = {
        {{1, 2, -1}, {-1}},     // state 0
        {{-1}, {2, -1}},        // state 1
        {{-1}, {-1}}            // state 2 (final)
    };

    int final = 2;
    int curr[10] = {0};     // starting from state 0
    int next[10];
    int i, j, k, n, c = 1;  // c = count of current states
    char str[100];

    printf("Construction of NFA\n");
    printf("Enter the string:\n");
    scanf("%s", str);

    for (i = 0; str[i]; i++) {
        int sym = str[i] - 'a';  // convert 'a'/'b' to 0/1
        int nc = 0;              // next count

        for (j = 0; j < c; j++) {
            int st = curr[j];
            for (k = 0; nfa[st][sym][k] != -1; k++) {
                int exists = 0;
                for (n = 0; n < nc; n++)
                    if (next[n] == nfa[st][sym][k])
                        exists = 1;
                if (!exists)
                    next[nc++] = nfa[st][sym][k];
            }
        }

        if (nc == 0) {
            printf("-1\nSTRING NOT ACCEPTED\n");
            return 0;
        }

        printf("After '%c': ", str[i]);
        for (j = 0; j < nc; j++) {
            printf("%d ", next[j]);
        }
        printf("\n");

        memcpy(curr, next, sizeof(next));
        c = nc;
    }

    for (i = 0; i < c; i++) {
        if (curr[i] == final) {
            printf("STRING ACCEPTED\n");
            return 0;
        }
    }

    printf("STRING NOT ACCEPTED\n");
    return 0;
}

// ab is string accepted
// aa , abba , aba is not string accepted

