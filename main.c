#include <stdio.h>
#include <string.h>

struct Vehicle {
    int id;
    char type[10];
    char model[20];
    int rateHour;
    int rateDay;
    int available;      
    int damageCharge;
};

/* Load vehicles from file */
int loadVehicles(struct Vehicle v[]) {
    FILE *fp = fopen("vehicle.txt", "r");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return 0;
    }

    int count = 0;
    while (fscanf(fp, "%d %s %s %d %d %d %d",
                  &v[count].id,
                  v[count].type,
                  v[count].model,
                  &v[count].rateHour,
                  &v[count].rateDay,
                  &v[count].available,
                  &v[count].damageCharge) != EOF) {
        count++;
    }

    fclose(fp);
    return count;
}

/* Save vehicles to file */
void saveVehicles(struct Vehicle v[], int n) {
    FILE *fp = fopen("vehicle.txt", "w");
    if (fp == NULL) {
        printf("Error saving file!\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        fprintf(fp, "%d %s %s %d %d %d %d\n",
                v[i].id,
                v[i].type,
                v[i].model,
                v[i].rateHour,
                v[i].rateDay,
                v[i].available,
                v[i].damageCharge);
    }

    fclose(fp);
}

int main() {
    struct Vehicle v[10];
    int n = loadVehicles(v);
    int choice;

    while (1) {
        printf("\n====== VEHICLE RENTAL SYSTEM ======\n");
        printf("1. Show Available Vehicles\n");
        printf("2. Rent Vehicle\n");
        printf("3. Return Vehicle\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        /* SHOW AVAILABLE VEHICLES */
        if (choice == 1) {
            printf("\nAvailable Vehicles:\n");
            for (int i = 0; i < n; i++) {
                if (v[i].available == 1) {
                    printf("%d. %s - %s (Rs %d/hr, Rs %d/day)\n",
                           v[i].id, v[i].type, v[i].model,
                           v[i].rateHour, v[i].rateDay);
                }
            }
        }

        /* RENT VEHICLE */
        else if (choice == 2) {
            int id, opt, hrs = 0, days = 0;
            float total = 0;
            int index = -1;

            printf("Enter Vehicle ID to Rent: ");
            scanf("%d", &id);

            for (int i = 0; i < n; i++) {
                if (v[i].id == id && v[i].available == 1) {
                    index = i;
                    break;
                }
            }

            if (index == -1) {
                printf("Vehicle not available!\n");
                continue;
            }

            printf("1. Per Hour\n2. Per Day\nChoose: ");
            scanf("%d", &opt);

            if (opt == 1) {
                printf("Enter hours: ");
                scanf("%d", &hrs);
                total = hrs * v[index].rateHour;
            } else if (opt == 2) {
                printf("Enter days: ");
                scanf("%d", &days);
                total = days * v[index].rateDay;
            } else {
                printf("Invalid option!\n");
                continue;
            }

            v[index].available = 0;
            saveVehicles(v, n);

            printf("\nVehicle Rented Successfully!");
            printf("\nTotal Amount: Rs %.2f\n", total);
        }

        /* RETURN VEHICLE */
        else if (choice == 3) {
            int id, damageOption;
            float total = 0;
            int index = -1;

            printf("Enter Vehicle ID to Return: ");
            scanf("%d", &id);

            for (int i = 0; i < n; i++) {
                if (v[i].id == id && v[i].available == 0) {
                    index = i;
                    break;
                }
            }

            if (index == -1) {
                printf("Invalid ID or vehicle not rented!\n");
                continue;
            }

            printf("Is vehicle damaged?\n1. Yes\n2. No\n");
            scanf("%d", &damageOption);

            if (damageOption == 1) {
                total = v[index].damageCharge;
                printf("Damage Charge: Rs %.2f\n", total);
            }

            v[index].available = 1;
            saveVehicles(v, n);

            printf("Vehicle Returned Successfully!\n");
        }

        /* EXIT */
        else if (choice == 4) {
            printf("Thank you!\n");
            break;
        }

        else {
            printf("Invalid choice!\n");
        }
    }

    return 0;
}
