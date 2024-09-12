#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct {
    int Id;
    char nom[50];
    char prenom[50];
    char dateNaissance[11];
    float note;
    char depNom[20];
} Student;

typedef struct {
    char depNom[20];
    float moyenne;
    int nbrLocal;
    Student Etudiants[MAX];
} Departement;

int i, j;
int choice;
int nbrTotal = 0;   // Le nombre total d'étudiants
int IdCounter = 0;  // ID counter

Student Etudiants[MAX];
Departement Deps[4];

// Add a new student
void Add() {
    Student Etudiant;
    Etudiant.Id = IdCounter++;

    printf("\n==============================\n");
    printf("       AJOUTER UN ETUDIANT\n");
    printf("==============================\n");
    printf("Nom: ");
    scanf(" %[^\n]", Etudiant.nom);
    printf("Prenom: ");
    scanf(" %[^\n]", Etudiant.prenom);
    printf("La date de naissance (format: JJ-MM-AAAA): ");
    scanf(" %[^\n]", Etudiant.dateNaissance);
    printf("La note generale: ");
    scanf("%f", &Etudiant.note);
    printf("Le departement: ");
    scanf(" %[^\n]", Etudiant.depNom);

    // Find the department
    for (i = 0; i < 4; i++) {
        if (strcmp(Deps[i].depNom, Etudiant.depNom) == 0) {

            Deps[i].Etudiants[Deps[i].nbrLocal++] = Etudiant;
            nbrTotal++;
            printf("Etudiant ajoute avec succes au departement %s.\n", Deps[i].depNom);
            return;
        }
    }
    printf("Departement non trouve.\n");
}

// Delete a student
void Delete() {
    int id;
    printf("\n==============================\n");
    printf("     SUPPRIMER UN ETUDIANT\n");
    printf("==============================\n");
    printf("Veuillez entrer l'ID de l'etudiant: ");
    scanf("%d", &id);

    if (id < 0 || id >= IdCounter) {
        printf("Etudiant non trouve.\n");
        return;
    }

    for (i = 0; i < 4; i++) {
        for (j = 0; j < Deps[i].nbrLocal; j++) {
            if (Deps[i].Etudiants[j].Id == id) {

                for (int k = j; k < Deps[i].nbrLocal - 1; k++) {
                    Deps[i].Etudiants[k] = Deps[i].Etudiants[k + 1];
                }
                Deps[i].nbrLocal--;
                nbrTotal--;
                // Vérifiez si le nbrLocal du département est cohérent (pas négatif)
                if (Deps[i].nbrLocal < 0) {
                    Deps[i].nbrLocal = 0;
                }
                printf("Etudiant supprime avec succes.\n");
                return;
            }
        }
    }
    printf("Etudiant non trouve dans aucun departement.\n");
}


// Edit a student
void Edit() {
    int id;
    printf("\n==============================\n");
    printf("     MODIFIER UN ETUDIANT\n");
    printf("==============================\n");
    printf("Veuillez entrer l'ID de l'etudiant: ");
    scanf("%d", &id);

    for (i = 0; i < 4; i++) {
        for (j = 0; j < Deps[i].nbrLocal; j++) {
            if (Deps[i].Etudiants[j].Id == id) {
                printf("Que voulez-vous changer dans cet etudiant?\n");
                printf("1. Le nom\n");
                printf("2. Le prenom\n");
                printf("3. La date de naissance\n");
                printf("4. Le departement\n");
                printf("5. La moyenne generale\n");
                printf("Selectionnez une option dans la liste ci-dessus:\n");
                scanf("%d", &choice);

                switch(choice) {
                    case 1:
                        printf("Saisir le nouveau nom: ");
                        scanf(" %[^\n]", Deps[i].Etudiants[j].nom);
                        break;
                    case 2:
                        printf("Saisir le nouveau prenom: ");
                        scanf(" %[^\n]", Deps[i].Etudiants[j].prenom);
                        break;
                    case 3:
                        printf("Saisir la nouvelle date de naissance (format: JJ-MM-AAAA): ");
                        scanf(" %[^\n]", Deps[i].Etudiants[j].dateNaissance);
                        break;
                    case 4:
                        printf("Saisir le nouveau departement: ");
                        scanf(" %[^\n]", Deps[i].Etudiants[j].depNom);
                        break;
                    case 5:
                        printf("Saisir la nouvelle moyenne generale: ");
                        scanf("%f", &Deps[i].Etudiants[j].note);
                        break;
                    default:
                        printf("Option non valide.\n");
                }
                printf("Modification effectuee avec succes.\n");
                return;
            }
        }
    }
    printf("Etudiant non trouve.\n");
}

// Display a student's information
void Display() {
    int id;
    printf("\n==============================\n");
    printf("    AFFICHER UN ETUDIANT\n");
    printf("==============================\n");
    printf("Veuillez entrer l'ID de l'etudiant: ");
    scanf("%d", &id);

    if (id < 0 || id >= nbrTotal) {
        printf("Etudiant non trouve.\n");
        return;
    }

    // Search for the student in the departments
    for (i = 0; i < 4; i++) {
        for (j = 0; j < Deps[i].nbrLocal; j++) {
            if (Deps[i].Etudiants[j].Id == id) {
                printf("\n==============================\n");
                printf("       INFORMATIONS ETUDIANT\n");
                printf("==============================\n");
                printf("ID: %d\n", Deps[i].Etudiants[j].Id);
                printf("Nom: %s\n", Deps[i].Etudiants[j].nom);
                printf("Prenom: %s\n", Deps[i].Etudiants[j].prenom);
                printf("Date de naissance: %s\n", Deps[i].Etudiants[j].dateNaissance);
                printf("Note generale: %.2f\n", Deps[i].Etudiants[j].note);
                printf("Departement: %s\n", Deps[i].Etudiants[j].depNom);
                return;
            }
        }
    }

    printf("Etudiant non trouve dans aucun departement.\n");
}

// La moyenne générale
void Average() {
    float somme[4] = {0, 0, 0, 0};
    float moyenne[4];
    float somUniv = 0;
    float moyUniv;
    
    for (i = 0; i < 4; i++) {
        for (j = 0; j < Deps[i].nbrLocal; j++) {
            somme[i] += Deps[i].Etudiants[j].note;
        }
    }

    printf("\n==============================\n");
    printf(" MOYENNE GENERALE PAR DEPARTEMENT\n");
    printf("==============================\n");
    for (i = 0; i < 4; i++) {
        if (Deps[i].nbrLocal > 0) {
            moyenne[i] = somme[i] / Deps[i].nbrLocal;
            printf("Departement de %s: %.2f\n", Deps[i].depNom, moyenne[i]);
            Deps[i].moyenne = moyenne[i];
        } else {
            printf("Departement de %s: (Vide)\n", Deps[i].depNom);
        }
    }
    int n=0;
    for (i = 0; i < 4; i++) {
        if (Deps[i].nbrLocal > 0) {
            n++;
            somUniv += Deps[i].moyenne;
        }
    }
    moyUniv = somUniv / n;
    printf("\n==============================\n");
    printf("  MOYENNE GENERALE DE L'UNIVERSITE\n");
    printf("==============================\n");
    printf("La moyenne generale de l'universite est: %.2f\n", moyUniv);
}

// Function to search students
void Search() {
    char name[50];
    int Found = 0;

    printf("\n==============================\n");
    printf("     RECHERCHER UN ETUDIANT\n");
    printf("==============================\n");
    printf("1. Rechercher un etudiant par son nom\n");
    printf("2. Afficher la liste des etudiants d'un departement\n");
    printf("Selectionnez une option dans la liste ci-dessus:\n");
    scanf("%d", &choice);

    switch (choice) {
            case 1:
                printf("Entrez le nom de l'etudiant: ");
                scanf(" %[^\n]", name);
                printf("\n==============================\n");
                printf("    RESULTATS DE RECHERCHE\n");
                printf("==============================\n");
                for (i = 0; i < 4; i++) {
                    for (j = 0; j < Deps[i].nbrLocal; j++) {
                        if (strcmp(Deps[i].Etudiants[j].nom, name) == 0) {
                            printf("\nID: %d\n", Deps[i].Etudiants[j].Id);
                            printf("Nom: %s\n", Deps[i].Etudiants[j].nom);
                            printf("Prenom: %s\n", Deps[i].Etudiants[j].prenom);
                            printf("Date de naissance: %s\n", Deps[i].Etudiants[j].dateNaissance);
                            printf("Note generale: %.2f\n", Deps[i].Etudiants[j].note);
                            printf("Departement: %s\n", Deps[i].Etudiants[j].depNom);
                            Found = 1;
                        }
                    }
                }
                if (!Found) {
                    printf("Aucun etudiant trouve avec ce nom.\n");
                }
                break;
            case 2:
                printf("Entrez le nom du departement: ");
                scanf(" %[^\n]", name);
                printf("\n==============================\n");
                printf("   LISTE DES ETUDIANTS DU DEPARTEMENT\n");
                printf("==============================\n");
                for (i = 0; i < 4; i++) {
                    if (strcmp(Deps[i].depNom, name) == 0) {
                        Found = 1;
                        for (j = 0; j < Deps[i].nbrLocal; j++) {
                            printf("\nID: %d\n", Deps[i].Etudiants[j].Id);
                            printf("Nom: %s\n", Deps[i].Etudiants[j].nom);
                            printf("Prenom: %s\n", Deps[i].Etudiants[j].prenom);
                            printf("Date de naissance: %s\n", Deps[i].Etudiants[j].dateNaissance);
                            printf("Note generale: %.2f\n", Deps[i].Etudiants[j].note);
                            printf("Departement: %s\n", Deps[i].Etudiants[j].depNom);
                        }
                    }
                }
                if (!Found) {
                    printf("Aucun etudiant trouve dans ce departement.\n");
                }
                break;
            default:
                printf("Option non valide.\n");
        }
}


void Sort() {
    printf("\n==============================\n");
    printf("       TRIAGE DES ETUDIANTS\n");
    printf("==============================\n");
    printf("1. Trier les etudiants par nom (de A -> Z ou de Z -> A)\n");
    printf("2. Trier les etudiants par moyenne generale (du plus eleve au plus faible ou inversement)\n");
    printf("3. Trier les etudiants selon leur statut de reussite (moyenne >= 10/20)\n");
    printf("Selectionnez une option dans la liste ci-dessus:\n");
    scanf("%d", &choice);

    Student tempStudents[MAX]; //Rassembler tous les élèves pour faire le tri
    int Count = 0;

    // Rassembler tous les élèves dans un seul tableau
    for (i = 0; i < 4; i++) {
        for (j = 0; j < Deps[i].nbrLocal; j++) {
            tempStudents[Count++] = Deps[i].Etudiants[j];
        }
    }

    switch (choice) {
        case 1: {
            int order;
            printf("Trier par nom (1: A -> Z, 2: Z -> A): ");
            scanf("%d", &order);
            
            // Trier par ordre alphabétique
            for (i = 0; i < Count - 1; i++) {
                for (j = 0; j < Count - i - 1; j++) {
                    if ((order == 1 && strcmp(tempStudents[j].nom, tempStudents[j + 1].nom) > 0) || (order == 2 && strcmp(tempStudents[j].nom, tempStudents[j + 1].nom) < 0)) {
                        Student temp = tempStudents[j];
                        tempStudents[j] = tempStudents[j + 1];
                        tempStudents[j + 1] = temp;
                    }
                }
            }

            printf("Etudiants tries par nom:\n");
            for (i = 0; i < Count; i++) {
                printf("%s %s | %.2f | %s \n", tempStudents[i].nom, tempStudents[i].prenom, tempStudents[i].note, tempStudents[i].depNom);
            }
            break;
        }
        case 2: {
            int order;
            printf("Trier par moyenne generale (1: Plus eleve au plus faible, 2: Plus faible au plus eleve): ");
            scanf("%d", &order);
            
            //(Count - i - 1) garantit qu'après chaque passage, la comparaison suivante n'inclut pas les éléments déjà triés à la fin.
            for (i = 0; i < Count - 1; i++) {
                for (j = 0; j < Count - i - 1; j++) {
                    if ((order == 1 && tempStudents[j].note < tempStudents[j + 1].note) || (order == 2 && tempStudents[j].note > tempStudents[j + 1].note)) {
                        Student temp = tempStudents[j];
                        tempStudents[j] = tempStudents[j + 1];
                        tempStudents[j + 1] = temp;
                    }
                }
            }

            printf("Etudiants tries par moyenne generale:\n");
            for (i = 0; i < Count; i++) {
                printf("%s %s | %.2f | %s \n", tempStudents[i].nom, tempStudents[i].prenom, tempStudents[i].note, tempStudents[i].depNom);
            }
            break;
        }
        case 3: {
            Student passedStudents[MAX];
            int passedCount = 0;

            for (i = 0; i < Count; i++) {
                if (tempStudents[i].note >= 10) {
                    passedStudents[passedCount++] = tempStudents[i];
                }
            }

            printf("Etudiants ayant reussi (note >= 10/20):\n");
            for (i = 0; i < passedCount; i++) {
                printf("%s %s | %.2f | %s \n", passedStudents[i].nom, passedStudents[i].prenom, passedStudents[i].note, passedStudents[i].depNom);
            }

            // If no students passed
            if (passedCount == 0) {
                printf("Aucun etudiant n'a reussi.\n");
            }
            break;
        }
        default:
            printf("Option non valide.\n");
    }
}


void Statistics() {
    printf("\n==============================\n");
    printf("      STATISTIQUES DES ETUDIANTS\n");
    printf("==============================\n");
    printf("1. Afficher le nombre total d'etudiants inscrits.\n");
    printf("2. Afficher le nombre d'etudiants dans chaque departement.\n");
    printf("3. Afficher les etudiants ayant une moyenne generale superieure a un certain seuil.\n");
    printf("4. Afficher les 3 etudiants ayant les meilleures notes.\n");
    printf("5. Afficher le nombre d'etudiants ayant reussi dans chaque departement (note >= 10/20).\n");
    printf("Selectionnez une option dans la liste ci-dessus:\n");
    scanf("%d", &choice);

    switch(choice) {
        case 1:
            printf("Le nombre total d'etudiants inscrits: %d\n", nbrTotal);
            break;
        case 2:
            for (i = 0; i < 4; i++) {
                printf("Le nombre d'etudiants dans %s est: %d\n", Deps[i].depNom, Deps[i].nbrLocal);
            }
            break;
        case 3: {
            float seuil;
            printf("Veuillez entrer un seuil: ");
            scanf("%f", &seuil);
            int found = 0;
            for (i = 0; i < 4; i++) {
                for (j = 0; j < Deps[i].nbrLocal; j++) {
                    if (Deps[i].Etudiants[j].note >= seuil) {
                        printf("%s %s | %.2f | %s \n", Deps[i].Etudiants[j].nom, Deps[i].Etudiants[j].prenom, Deps[i].Etudiants[j].note, Deps[i].Etudiants[j].depNom);
                        found = 1;
                    }
                }
            }
            if (!found) {
                printf("Aucun etudiant ne correspond au seuil donne.\n");
            }
            break;
        }
        case 4: {
            Student topStudents[MAX];
            int Count = 0;

            for (i = 0; i < 4; i++) {
                for (j = 0; j < Deps[i].nbrLocal; j++) {
                    topStudents[Count++] = Deps[i].Etudiants[j];
                }
            }

            // Trier les élèves par niveau par ordre décroissant
            for (i = 0; i < Count - 1; i++) {
                for (j = 0; j < Count - i - 1; j++) {
                    if (topStudents[j].note < topStudents[j + 1].note) {
                        Student temp = topStudents[j];
                        topStudents[j] = topStudents[j + 1];
                        topStudents[j + 1] = temp;
                    }
                }
            }

            printf("Les 3 etudiants ayant les meilleures notes:\n");
            for (i = 0; i < 3 && i < Count; i++) {
                printf("%s %s | %.2f\n", topStudents[i].nom, topStudents[i].prenom, topStudents[i].note);
            }
            break;
        }
        case 5: {
            printf("Nombre d'etudiants ayant reussi (note >= 10/20) dans chaque departement:\n");
            for (i = 0; i < 4; i++) {
                int count = 0;
                for (j = 0; j < Deps[i].nbrLocal; j++) {
                    if (Deps[i].Etudiants[j].note >= 10) {
                        count++;
                    }
                }
                printf("Departement %s: %d etudiants\n", Deps[i].depNom, count);
            }
            break;
        }
        default:
            printf("Option non valide.\n");
    }
}


int main() {
    // Initialize department names and set initial student counts to 0
    strcpy(Deps[0].depNom, "Informatique");
    Deps[0].nbrLocal = 0;

    strcpy(Deps[1].depNom, "Mathematiques");
    Deps[1].nbrLocal = 0;

    strcpy(Deps[2].depNom, "Physique");
    Deps[2].nbrLocal = 0;

    strcpy(Deps[3].depNom, "Chimie");
    Deps[3].nbrLocal = 0;

    IdCounter = 10; // Set this to the highest ID used by manually added students

    // Ajouter manuellement 10 étudiants
    Student students[10] = {
        {0, "Wick", "John", "01-01-2000", 15.0, "Informatique"},
        {1, "Shelby", "Thomas", "02-02-2001", 12.5, "Informatique"},
        {2, "Chapline", "Charlie", "03-03-2002", 14.0, "Mathematiques"},
        {3, "Lecter", "Hannibal", "04-04-2000", 19.0, "Mathematiques"},
        {4, "Scofield", "Michael", "05-05-1999", 18.0, "Physique"},
        {5, "Gollum", "Smeagol", "06-06-2002", 3.5, "Physique"},
        {6, "Roronoa", "Zoro", "07-07-2001", 0.0, "Chimie"},
        {7, "Sparrow", "Jack", "08-08-2000", 10.0, "Chimie"},
        {8, "Castle", "Frank", "09-09-1998", 17.5, "Informatique"},
        {9, "Lothbrok", "Ragnar", "10-10-2001", 9.5, "Mathematiques"}
    };

    // Ajouter des étudiants aux départements correspondants
    for (i = 0; i < 10; i++) {
        for (j = 0; j < 4; j++) {
            if (strcmp(students[i].depNom, Deps[j].depNom) == 0) {
                Deps[j].Etudiants[Deps[j].nbrLocal++] = students[i];
                nbrTotal++;
                break;
            }
        }
    }


    do {
        printf("\n==============================\n");
        printf("            MENU\n");
        printf("==============================\n");
        printf("1. AJOUTER UN ETUDIANT\n");
        printf("2. SUPPRIMER UN ETUDIANT\n");
        printf("3. MODIFIER LES INFORMATIONS D'UN ETUDIANT\n");
        printf("4. AFFICHIER LES INFORMATIONS D'UN ETUDIANT\n");
        printf("5. LA MOYENNE GENERALE PAR DEPARTEMENT\n");
        printf("6. RECHERCHER UN ETUDIANT\n");
        printf("7. TRIER LES ETUDIANTS\n");
        printf("8. STATISTIQUES\n");
        printf("0. QUITTER\n");
        printf("==============================\n");
        printf("Selectionnez une option dans la liste ci-dessus:\n");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                Add();
                break;
            case 2:
                Delete();
                break;
            case 3:
                Edit();
                break;
            case 4:
                Display();
                break;
            case 5:
                Average();
                break;
            case 6:
                Search();
                break;
            case 7:
                Sort();
                break;
            case 8:
                Statistics();
                break;
            case 0:
                printf("Quitter...\n");
                break;
            default:
                printf("Option non valide.\n");
        }
    } while (choice != 0);

    return 0;
}