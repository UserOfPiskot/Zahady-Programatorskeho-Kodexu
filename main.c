#include <stdio.h>
#include <windows.h>
#include <stdbool.h>
#include <conio.h>
#include <time.h>
#include <ctype.h>

 enum obtiznosti {
    LEHKA = 1,
    STREDNI,
    TEZKA
};
enum obtiznosti obtiznost;
char dialogy[][6] = {"__000", "__100", "__200"};
bool hracZemrel;
bool debugMode = 0;
bool splneneUkoly[9] = {};
/*
    1. ukol Kouzelna brana
    2. ukol Les rozcestniku
    3. ukol Poustni cyklony
    4. ukol Jeskyne nekonecna
    5. ukol Hluboky les
    6. ukol Strazce dveri
    7. ukol Magicke kruhy
    8. ukol Duch starovekeho kodera
    9. ukol Labyrint rekursivni magie
 */

void predehra() {
    for (int i = 0; i < sizeof(splneneUkoly)/sizeof(bool); i++){
        splneneUkoly[i] = 0;
    }
    hracZemrel = 0;
}
int vyberoveMenu(){
    int volba;
    do {
        printf("=====================================\n");
        printf("Vyberte si ukol:\n");
        for (int i = 0; i < 9; i++){
            switch(i){
                case 0:
                    printf("1. Kouzelna brana");
                    (splneneUkoly[i]) ? printf(" (splneno)\n"): printf("\n");
                    break;
                case 1:
                    printf("2. Les rozcestniku");
                    (splneneUkoly[i]) ? printf(" (splneno)\n"): printf("\n");
                    break;
                case 2:
                    printf("3. Poustni cyklony");
                    (splneneUkoly[i]) ? printf(" (splneno)\n"): printf("\n");
                    break;
                case 3:
                    printf("4. Jeskyne nekonecna");
                    (splneneUkoly[i]) ? printf(" (splneno)\n"): printf("\n");
                    break;
                case 4:
                    printf("5. Hluboky les");
                    (splneneUkoly[i]) ? printf(" (splneno)\n"): printf("\n");
                    break;
                case 5:
                    printf("6. Strazce dveri");
                    (splneneUkoly[i]) ? printf(" (splneno)\n"): printf("\n");
                    break;
                case 6:
                    printf("7. Magicke kruhy");
                    (splneneUkoly[i]) ? printf(" (splneno)\n"): printf("\n");
                    break;
                case 7:
                    printf("8. Duch starovekeho kodera");
                    (splneneUkoly[i]) ? printf(" (splneno)\n"): printf("\n");
                    break;
                case 8:
                    printf("9. Labyrint rekursivni magie");
                    (splneneUkoly[i]) ? printf(" (splneno)\n"): printf("\n");
                    break;
            }
        }
        printf("=====================================\n");
        if (debugMode){
            printf("Debug: Obtiznost %d\n", obtiznost);
            int j = 0;
            for (int i = 0; i < sizeof(splneneUkoly)/sizeof(bool); i++)
                if (splneneUkoly[i])
                    j++;
            printf("Debug: Splneno %d\n", j);
        }
        printf("Zadejte volbu (1-9): ");
        scanf("%d", &volba);
        system("cls");
    } while(volba < 1 || volba > 9);
    return volba;
}
int kontrolaSplneniVsechUkolu() {
    bool vsechnyUkolySplneny = 1;
    for (int i = 0; i < sizeof(splneneUkoly)/sizeof(bool); i++){
        if (!splneneUkoly[i])
            vsechnyUkolySplneny = 0;
    }
    if (vsechnyUkolySplneny)
        return 1;
    return 0;
}
void vykresleniGrafiky(FILE *fptr, int cisloDialog, char bypassDialog[]) {
    char ctenyRadek[255];
    if (bypassDialog[0] != '\0') {
        while (fgets(ctenyRadek, sizeof(ctenyRadek), fptr) != NULL) {
            ctenyRadek[strcspn(ctenyRadek, "\n")] = '\0';
            if (strcmp(ctenyRadek, bypassDialog) == 0)
                break;
        }
        fseek(fptr, 0, SEEK_SET);
    }
    if (cisloDialog != -1) {
        if (debugMode)
            printf("Debug: Looking for: %s\n", dialogy[cisloDialog]);
        while (fgets(ctenyRadek,sizeof(ctenyRadek),fptr) != NULL){
            ctenyRadek[strcspn(ctenyRadek, "\n")] = '\0';
            if (strcmp(ctenyRadek, dialogy[cisloDialog]) == 0)
                break;
        }
        while (fgets(ctenyRadek,sizeof(ctenyRadek),fptr) != NULL){
            ctenyRadek[strcspn(ctenyRadek, "\n")] = '\0';
            if (strcmp(ctenyRadek, "__") == 0)
                break;
            printf("%s\n",ctenyRadek);
        }
    }
}
void kouzelnaBrana() {
    float MAX_CAS;
    switch(obtiznost){
        case 1:
            MAX_CAS = 1;
            break;
        case 2:
            MAX_CAS = 0.75;
            break;
        case 3:
            MAX_CAS = 0.5;
            break;
    }
    int kouzloStrazce;
    int kouzloHrace;
    int hracZivoty = 3;
    int strazceZivoty = 6;
    clock_t cas;
    clock_t casKontrola;
    // Fakt hodne mluveni.
    printf("Otevres 1. stranu kodexu a vidis, ze musis porazit strazce u kouzelne brany a tak se tam vydas.\n");
    printf("Prectes si kouzelny manual a zjistis, ze:\n");
    printf("1. Strazce sesle kouzlo a ty se pred nim musis obranit.\n");
    printf("2. Strazce ma v grimoaru pouze dve kouzla: dest a fireball.\n");
    printf("3. Aby jsi se ubranil pred kouzlem, musis seslat jeho opak.\n");
    printf("4. Pokud se neubranis, ztratis zivot.\n");
    printf("5. Pokud se ubranis, strazce ztrati zivot.\n\n");
    printf("Na kouzlo dest plati fireball, ktery sesles stiskem D.\n");
    printf("Na kouzlo fireball plati dest, ktery sesles stiskem A.\n");
    printf("Mas maximalne %.2f sekund na obraneni.\n", MAX_CAS);
    system("pause");
    // Loop, ktery se bude opakovat, dokud hrac neztrati vsechny zivoty nebo strazce neztrati vsechny zivoty.
    do{
        system("cls");
        printf("Hrac ma %d zivot(y)\n", hracZivoty);
        printf("Strazce ma %d zivot(u/y)\n", strazceZivoty);
        printf("Jsi pripraven kouzlit?\n");
        system("pause");
        kouzloStrazce = rand()%2;
        printf("Strazce sesila kouzlo ");
        if(kouzloStrazce == 0){
            printf("dest\n");
        } else{
            printf("fireball\n");
        }
        cas = clock();
        casKontrola = cas;
        //
        do {
            casKontrola = clock();
            kouzloHrace = getche();
        } while (kouzloHrace != 97 && kouzloHrace != 100 && kouzloHrace != 65 && kouzloHrace != 68
        && casKontrola - cas <= MAX_CAS);
        cas = clock() - cas;
        cas /= CLOCKS_PER_SEC;
        kouzloHrace = tolower(kouzloHrace);
        switch(kouzloStrazce){
            case 0:
                kouzloStrazce = 97;
                break;
            case 1:
                kouzloStrazce = 100;
                break;
        }
        if ((float)cas <= MAX_CAS){
            (kouzloHrace != kouzloStrazce) ? strazceZivoty --: hracZivoty --;
            // Kouzelná brána (Použití Ternárního operátoru.)
        } else{
            hracZivoty --;
        }
        if(debugMode){
            printf("Debug: Straveny cas: %.2f\n", (float)cas);
            printf("Debug: Kouzlo hrace: %c\n", kouzloHrace);
            printf("Debug: Kouzlo strazce: %c\n", kouzloStrazce);
        }
    } while (hracZivoty != 0 && strazceZivoty != 0);
    if (strazceZivoty == 0){
        splneneUkoly[0] = 1;
    }
    if (hracZivoty == 0){
        hracZemrel = 1;
    }
    system("cls");
}
void lesRozcestniku() {

}
void poustniCyklony() {
    int pocetSpravnych = -1;
    char hracuvSmer;
    int DELKA_CESTY;
    int MAX_POCET_POKUSU = 10;
    switch(obtiznost){
        case 1:
            DELKA_CESTY = 4;
            break;
        case 2:
            DELKA_CESTY = 5;
            break;
        case 3:
            DELKA_CESTY = 6;
            break;
    }
    int hadanySmer[DELKA_CESTY];
    int danySmer[DELKA_CESTY];
    int cisloPokusu = 0;
    // Přiřazení čísel 0-2 do array, který bude tvořit řešení pro východ z bludiště.
    for (int i = 0; i < DELKA_CESTY; i++){
        danySmer[i] = rand()%3;
        if (debugMode && i == 0)
            printf("Debug: %d", danySmer[i]);
        if (debugMode && i != 0)
            printf("%d", danySmer[i]);
    }
    if (debugMode)
        printf("\n");
    printf("Otevres 3. stranu kodexu a vidis, ze musis projit poustni cyklony.\n");
    printf("Vydas se na cestu k nim, je to dlouha cesta. Jsou totiz az v pousti.\n");
    printf("Myslis si, ze uz tam nedojdes, kdyz v tom, se pred tebou objevi obrovske cyklony\n");
    printf("Prectes si kouzelny manual a zjistis, ze:\n");
    printf("1. Musis projit cestu, ktera je dlouha %d cyklonu.\n", DELKA_CESTY);
    printf("2. Cyklony jsou porad na stejnych mistech.\n");
    printf("3. Musis si zapamatovat cestu, kterou jsi sel.\n");
    printf("4. Kdyz se spletete, cyklony te odnesou zpet na zacatek.\n");
    printf("5. Pote co te odnesou, ti dojde kolik casti jsi usel spravne.\n\n");
    printf("Mas %d pokusu na projiti cesty.\n", MAX_POCET_POKUSU);
    printf("Mas tri moznosti, jak se cyklonum vyhnout:\n");
    printf("   A. Jit doleva\n");
    printf("   W. Jit rovne\n");
    printf("   D. Jit doprava\n");
    system("pause");
    system("cls");
    while (pocetSpravnych != DELKA_CESTY && MAX_POCET_POKUSU != cisloPokusu){ // Pouštní cyklony (Použití cyklu s podmínkou na začátku.)
        cisloPokusu++;
        printf("Toto je tvuj %d. pokus z %d.\n", cisloPokusu, MAX_POCET_POKUSU);
        pocetSpravnych = 0;
        for (int i = 0; i < DELKA_CESTY; i++){ // Loop který se postupně ptá na řešení a přiřazuje je do array na hádání v řade.
            do{ // Bude se opakovat, dokud uživatel nezadá číslo mezi 0-2 a přiřadí jej do hádací array v pořadí i.
                printf("\nKudy chces jit %d. kus cesty?: ", i+1);
                hracuvSmer = getche();
                hracuvSmer = tolower(hracuvSmer);
                switch(hracuvSmer){
                    case 97:
                        hadanySmer[i] = 0;
                        break;
                    case 119:
                        hadanySmer[i] = 1;
                        break;
                    case 100:
                        hadanySmer[i] = 2;
                        break;
                }
            } while (hadanySmer[i] < 0 || hadanySmer[i] > 2);
        }
        for (int i = 0; i < DELKA_CESTY; i++) // Loop pro kontrolu počtu správných.
            if (hadanySmer[i] == danySmer[i]) pocetSpravnych++;
        system("cls");
        if (pocetSpravnych != DELKA_CESTY){
            printf("Spatne, jeden z cyklonu te chytl a odnesl zpet na zacatek.\n");
            system("pause");
            system("cls");
            printf("(Sel jsi spravne %d z %d kusu cesty.)", pocetSpravnych, DELKA_CESTY); // Zobrazí počet správných.
        }
        if(debugMode){
            printf("Debug: Spravne cesty: ");
            for (int i = 0; i < DELKA_CESTY; i++)
                printf("%d ", danySmer[i]);
            printf("\n");
            printf("Debug: Hadane cesty: ");
            for (int i = 0; i < DELKA_CESTY; i++)
                printf("%d ", hadanySmer[i]);
            printf("\n");
        }
    }
    if (pocetSpravnych == DELKA_CESTY){ // Pokud hráč projde všemi cyklony, splní úkol.
        printf("\nUspesne jsi prosel vsechny cyklony, cimz jsi splnil jeden z ukolu\n");
        splneneUkoly[2] = 1;
    } else {
        printf("\nCyklony te tak vycerpaly, ze jsi v nich zemrel unavou.\n");
        hracZemrel = 1;
    }
}
void jeskyneNekonecna() {

}
void hlubokyLes() {

}
void strazceDveri() {
    char *filename = "imgs.txt";
    int cisloDialog = -1;
    char bypassDialog[] = {};
    FILE *fptr = NULL;
    if((fptr = fopen(filename,"r")) == NULL)
    {
        fprintf(stderr,"error opening %s\n",filename);
        system("pause");
        exit(1);
    }
    if (debugMode){
        do {
            scanf("%s", bypassDialog);
        } while (strcmp(bypassDialog, "\0") != 0);
    }
    vykresleniGrafiky(fptr, cisloDialog, bypassDialog);
    system("pause");
    fclose(fptr);
}
void magickeKruhy() {

}
void duchStarovekehoKodera() {

}
void labyrintRekursivniMagie() {

}
int main(int argc, char *argv[]) {
    if (argc >= 2){
        for (int i = 0; i < argc; i++){
            if (strcmp(argv[i], "-debug") == 0)
                debugMode = 1;
        }
    }
    if(debugMode)
        printf("===================================DEBUG===================================\n");
    srand(time(NULL));
    int volba;
    bool konecHry = 0;
    do{
        predehra();
        do{
            printf("Predtim nez zacneme, vyberte si obtiznost hry:\n");
            printf("1. Lehka\n");
            printf("2. Stredni\n");
            printf("3. Tezka\n");
            printf("Zadejte volbu (1-3):");
            scanf("%d", &obtiznost);
            system("cls");
        } while (obtiznost < 1 || obtiznost > 3);
        while (!kontrolaSplneniVsechUkolu() && !hracZemrel) {
            do {
                volba = vyberoveMenu();
                volba --;
            } while (splneneUkoly[volba]);
            switch (volba) {
                case 0:
                    kouzelnaBrana();
                    break;
                case 1:
                    lesRozcestniku();
                    break;
                case 2:
                    poustniCyklony();
                    break;
                case 3:
                    jeskyneNekonecna();
                    break;
                case 4:
                    hlubokyLes();
                    break;
                case 5:
                    strazceDveri();
                    break;
                case 6:
                    magickeKruhy();
                    break;
                case 7:
                    duchStarovekehoKodera();
                    break;
                case 8:
                    labyrintRekursivniMagie();
                    break;
            }
        }
        if(kontrolaSplneniVsechUkolu()){
            printf("\n");
            printf("Chcete hrat znovu? (1 - Ano, 0 - Ne): ");
            scanf("%d", &volba);
            if (!volba) {
                konecHry = 1;
            }
        } else if (hracZemrel) {
            printf("Hrac nebyl schopen splnit vsechny ukoly a zemrel.\n");
            printf("Chcete hrat znovu? (1 - Ano, 0 - Ne): ");
            scanf("%d", &volba);
            if (!volba) {
                konecHry = 1;
            }
        }
    } while (!konecHry);
    return 0;
}
