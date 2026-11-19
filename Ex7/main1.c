#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    int n, lotto[5][7];
    int i, j, k, num, same, temp;
    FILE *fp;
    time_t now;
    struct tm *t;
    char date[100];

    srand((unsigned int)time(NULL));

    printf("Please enter N (1~5): ");
    scanf("%d", &n);

    if (n < 1 || n > 5)
    {
        printf("Invalid input!\n");
        return 1;
    }

    // Generate lottery numbers
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < 7; j++)
        {
            do
            {
                num = rand() % 69 + 1;
                same = 0;

                for (k = 0; k < j; k++)
                {
                    if (lotto[i][k] == num)
                    {
                        same = 1;
                        break;
                    }
                }

            } while (same);

            lotto[i][j] = num;
        }

        // Sort first 6 numbers
        for (j = 0; j < 5; j++)
        {
            for (k = j + 1; k < 6; k++)
            {
                if (lotto[i][j] > lotto[i][k])
                {
                    temp = lotto[i][j];
                    lotto[i][j] = lotto[i][k];
                    lotto[i][k] = temp;
                }
            }
        }
    }

    // Get current date and time
    now = time(NULL);
    t = localtime(&now);

    strftime(date, sizeof(date),
             "%a %b %d %H:%M:%S %Y", t);

    // Open lotto.txt
    fp = fopen("lotto.txt", "w");

    if (fp == NULL)
    {
        printf("Cannot create lotto.txt!\n");
        return 1;
    }

    // Output header
    printf("========== lotto649 ==========\n");
    printf("= %s =\n", date);

    fprintf(fp, "========== lotto649 ==========\n");
    fprintf(fp, "= %s =\n", date);

    // Output 5 groups
    for (i = 0; i < 5; i++)
    {
        printf("[%d]: ", i + 1);
        fprintf(fp, "[%d]: ", i + 1);

        if (i < n)
        {
            for (j = 0; j < 7; j++)
            {
                printf("%02d ", lotto[i][j]);
                fprintf(fp, "%02d ", lotto[i][j]);
            }
        }
        else
        {
            printf("-- -- -- -- -- -- --");
            fprintf(fp, "-- -- -- -- -- -- --");
        }

        printf("\n");
        fprintf(fp, "\n");
    }

    printf("========== csie@CGU ==========\n");
    fprintf(fp, "========== csie@CGU ==========\n");

    // Save and close file
    fclose(fp);

    printf("\nlotto.txt created successfully!\n");

    return 0;
}
