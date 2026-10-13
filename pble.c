#include <stdio.h>

#define MAX 100

struct Package
{
    int id;
    float value;
    float weight;
    float ratio;
    float fraction;
    float selectedWeight;
    float selectedValue;
};

struct Package p[MAX];

int n = 0;
float capacity = 0;


/* Enter package details */
void enterDetails()
{
    int i;

    printf("\nEnter number of packages: ");
    scanf("%d", &n);

    if (n <= 0 || n > MAX)
    {
        printf("Invalid number of packages.\n");
        n = 0;
        return;
    }

    for (i = 0; i < n; i++)
    {
        p[i].id = i + 1;

        printf("\nPackage %d\n", i + 1);

        printf("Enter value/profit: ");
        scanf("%f", &p[i].value);

        printf("Enter weight: ");
        scanf("%f", &p[i].weight);

        if (p[i].weight <= 0 || p[i].value < 0)
        {
            printf("Invalid value or weight. Enter again.\n");
            i--;
        }
    }

    printf("\nEnter maximum vehicle capacity: ");
    scanf("%f", &capacity);

    printf("\nPackage details entered successfully.\n");
}


/* Display package details */
void displayDetails()
{
    int i;

    if (n == 0)
    {
        printf("\nPlease enter package details first.\n");
        return;
    }

    printf("\n-----------------------------------------------------\n");
    printf("Package\tValue\tWeight\tRatio\n");
    printf("-----------------------------------------------------\n");

    for (i = 0; i < n; i++)
    {
        printf("%d\t%.2f\t%.2f\t%.2f\n",
               p[i].id,
               p[i].value,
               p[i].weight,
               p[i].ratio);
    }
}


/* Calculate Value/Weight ratio */
void calculateRatio()
{
    int i;

    if (n == 0)
    {
        printf("\nPlease enter package details first.\n");
        return;
    }

    for (i = 0; i < n; i++)
    {
        p[i].ratio = p[i].value / p[i].weight;
    }

    printf("\nValue/Weight ratio calculated successfully.\n");

    displayDetails();
}


/* Sort packages by decreasing ratio */
void sortPackages()
{
    int i, j;
    struct Package temp;

    if (n == 0)
    {
        printf("\nPlease enter package details first.\n");
        return;
    }

    /* Make sure ratios are calculated */
    for (i = 0; i < n; i++)
    {
        p[i].ratio = p[i].value / p[i].weight;
    }

    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (p[j].ratio < p[j + 1].ratio)
            {
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }

    printf("\nPackages sorted by decreasing Value/Weight ratio.\n");

    displayDetails();
}


/* Find maximum value */
void findMaximumValue()
{
    int i;

    float remainingCapacity;
    float totalValue = 0;
    float totalWeight = 0;

    if (n == 0)
    {
        printf("\nPlease enter package details first.\n");
        return;
    }

    /* Calculate ratio */
    for (i = 0; i < n; i++)
    {
        p[i].ratio = p[i].value / p[i].weight;
        p[i].fraction = 0;
        p[i].selectedWeight = 0;
        p[i].selectedValue = 0;
    }

    /* Sort */
    sortPackages();

    remainingCapacity = capacity;

    for (i = 0; i < n; i++)
    {
        if (remainingCapacity <= 0)
            break;

        /* Complete package */
        if (p[i].weight <= remainingCapacity)
        {
            p[i].fraction = 1;

            p[i].selectedWeight = p[i].weight;

            p[i].selectedValue = p[i].value;

            remainingCapacity =
                remainingCapacity - p[i].weight;

            totalWeight =
                totalWeight + p[i].weight;

            totalValue =
                totalValue + p[i].value;
        }

        /* Fraction of package */
        else
        {
            p[i].fraction =
                remainingCapacity / p[i].weight;

            p[i].selectedWeight =
                remainingCapacity;

            p[i].selectedValue =
                p[i].ratio * remainingCapacity;

            totalWeight =
                totalWeight + remainingCapacity;

            totalValue =
                totalValue + p[i].selectedValue;

            remainingCapacity = 0;
        }
    }

    printf("\n============================================\n");
    printf("       FRACTIONAL KNAPSACK RESULT\n");
    printf("============================================\n");

    printf("Vehicle Capacity : %.2f\n", capacity);
    printf("Total Weight Used : %.2f\n", totalWeight);
    printf("Maximum Value     : %.2f\n", totalValue);
}


/* Display selected packages */
void displaySelectedPackages()
{
    int i;

    if (n == 0)
    {
        printf("\nPlease enter package details first.\n");
        return;
    }

    printf("\n-------------------------------------------------------------\n");
    printf("Package\tFraction\tWeight Used\tValue Obtained\n");
    printf("-------------------------------------------------------------\n");

    for (i = 0; i < n; i++)
    {
        if (p[i].fraction > 0)
        {
            printf("%d\t%.2f\t\t%.2f\t\t%.2f\n",
                   p[i].id,
                   p[i].fraction,
                   p[i].selectedWeight,
                   p[i].selectedValue);
        }
    }
}


/* Main function */
int main()
{
    int choice;

    do
    {
        printf("\n\n============================================\n");
        printf("       SMART DELIVERY PLANNING\n");
        printf("       FRACTIONAL KNAPSACK\n");
        printf("============================================\n");

        printf("1. Enter Package Details\n");
        printf("2. Display Package Details\n");
        printf("3. Calculate Value/Weight Ratio\n");
        printf("4. Sort Packages by Ratio\n");
        printf("5. Find Maximum Value\n");
        printf("6. Display Selected Packages\n");
        printf("7. Exit\n");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                enterDetails();
                break;

            case 2:
                displayDetails();
                break;

            case 3:
                calculateRatio();
                break;

            case 4:
                sortPackages();
                break;

            case 5:
                findMaximumValue();
                break;

            case 6:
                displaySelectedPackages();
                break;

            case 7:
                printf("\nProgram exited successfully.\n");
                break;

            default:
                printf("\nInvalid choice! Please enter 1-7.\n");
        }

    } while (choice != 7);

    return 0;
}
