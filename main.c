#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void putDown(int *numbers, int root, int bottom)
{
  int maxChild;
  int done = 0;
  while ((root * 2 <= bottom) && (!done)) {
    if (root * 2 == bottom){
        maxChild = root * 2;
    } else if (numbers[root * 2] > numbers[root * 2 + 1]){
        maxChild = root * 2;
    } else {
        maxChild = root * 2 + 1;
    }
    if (numbers[root] < numbers[maxChild]){
        int temp = numbers[root];
        numbers[root] = numbers[maxChild];
        numbers[maxChild] = temp;
        root = maxChild;
    } else{
        done = 1;
    }
  }
}

void sort (int *numbers, int array_size){
  for (int i = (array_size / 2) - 1; i >= 0; i--){
    putDown(numbers, i, array_size - 1);
  }
  for (int i = array_size - 1; i >= 1; i--){
    int temp = numbers[0];
    numbers[0] = numbers[i];
    numbers[i] = temp;
    putDown(numbers, 0, i - 1);
  }
}

struct Mount {
    char name[80];
    char connections[40][80];
    int NOC;
};


struct Mount create (){
    struct Mount *s;
    s = malloc(sizeof(struct Mount));
    s->NOC = 0;
    return *s;
};

void start_init (struct Mount *s, int am){
    int brek = 1;
    int check = 0;
    char ans[80];
    printf("Enter names of mounts\n");
    for (unsigned int i = 0; i < am; i++){
        scanf("%s", s[i].name);
    }
    for (unsigned int i = 0; i < am; i++){
        printf("Enter connections for mount %s or '0' to exit \n", s[i].name);
        while (check < am - 1){
            scanf("%s", &ans);
            if (strcmpi("0", ans) == 0){
                break;
            }
            for (unsigned int j = 0; j < am; j++){
                if (strcmpi(ans, s[i].name) == 0){
                    printf("Mount can't be assigned to itself\n");
                    break;
                } else if (strcmpi(ans, s[j].name) == 0){
                    for (unsigned int l = 0; l < s[j].NOC; l++){
                        if (strcmpi(s[i].name, s[j].connections[l]) == 0){
                            printf("This mount is already assigned\n");
                            brek = 0;
                        }
                    }
                    if (brek){
                        strcpy(s[i].connections[check], ans);
                        check++;
                        s[i].NOC++;
                    }
                }
                brek = 1;
            }
        }
        check = 0;
    }
}

void Construction(struct Mount *s, int am){
    FILE *f;
    f = fopen("graphs/graph.gv", "w");
    if (f == NULL){
        printf("Error: Not opened\n");
        exit(2);
    }
    fputs("graph graphname {\n", f);
    for (unsigned int i = 0; i < am; i++){
        fputs(s[i].name, f);
        fputs(";\n", f);
    }
    for (unsigned int i = 0; i < am; i++){
        for (unsigned int j = 0; j < s[i].NOC; j++){
            fputs(s[i].name, f);
            fputs("--", f);
            fputs(s[i].connections[j], f);
            fputs(";\n", f);
        }
    }
    fputs("}", f);
    if (fclose(f) == EOF){
        printf("Error: Not closed\n");
        exit(3);
    }
}

void Construction_sorted(int *ms, int am){
    int changer = 0;
    char str[80];
    FILE *f;
    f = fopen("graphs/graph_sorted.gv", "w");
    if (f == NULL){
        printf("Error: Not opened\n");
        exit(2);
    }
    fputs("graph graphname {\n", f);
    for (unsigned int i = 0; i < am; i++){
        itoa(ms[i], str, 10);
        fputs(str, f);
        fputs(";\n", f);
    }
    for (unsigned int i = 0; i < am; i++){
        if ((((i+1)*2) - 1) > am - 1){
            break;
        }
        itoa(ms[i], str, 10);
        fputs(str, f);
        fputs("--", f);
        itoa(ms[((i+1)*2) - 1], str, 10);
        fputs(str, f);
        fputs(";\n", f);
        if (((i+1)*2) > am){
            fputs(";\n", f);
            break;
        }
        itoa(ms[i], str, 10);
        fputs(str, f);
        fputs("--", f);
        itoa(ms[(i+1)*2], str, 10);
        fputs(str, f);
        fputs(";\n", f);
    }
    fputs("}", f);
    if (fclose(f) == EOF){
        printf("Error: Not closed\n");
        exit(3);
    }
}

void adjacency(struct Mount *s, int am){
    int mounts = am;
    int ribbons = 0;
    for (unsigned int i = 0; i < am; i++){
        ribbons += s[i].NOC;
    }
    if (ribbons > ((am-1)*(am - 2))/2){
        printf("This graph is connected one\n");
    } else {
        printf("This graph isn't connected one\n");
    }
}

int make_mas (struct Mount *s, int am){
    /*
    for (int i = 0; i < s[0].NOC; i++){
        printf("%s ", s[0].connections[i]);
    }
    */
    int flag = 1;
    int numb_of_mount = 0;
    int *m;
    int k = 0;
    char ans1[80];
    char ans2[80];
    m = malloc((am - 2) * sizeof(int));
    printf("Enter mounts to delete: \n");
    scanf("%s", &ans1);

    for (int i = 0; i < am; i++){
        if (strcmpi(s[i].name, ans1) == 0){
            numb_of_mount = i;
        }
    }
/*
    printf("%s \n", s[0].name);
    printf("\n%d\n\n", numb_of_mount);
*/
    while (flag){
        printf("Enter connected mount: \n");
        scanf("%s", &ans2);
        for (unsigned int i = 0; i < s[numb_of_mount].NOC; i++){
            if (strcmpi(s[numb_of_mount].connections[i], ans2) == 0){
                flag = 0;
                break;
            }
        }
    }
    for (unsigned int i = 0; i < am; i++){
        if ((strcmpi(s[i].name, ans1) != 0) && (strcmpi(s[i].name, ans2) != 0)){
            m[k] = atoi(s[i].name);
            k++;
        }
    }
    return m;
}

int main (void){
    int amount;
    int off = 1;
    char answer[80];
    struct Mount *p;
    printf("Enter number of mounts\n");
    while (scanf("%d", &amount) != 1){
        scanf("%*[^\n]");
    }
    if (!(p = malloc(amount * sizeof(struct Mount)))){
        printf("memory allocation error");
        exit(1);
    }
    for (unsigned int i = 0; i < amount; i++){
        p[i] = create(amount);
    }
    start_init(p, amount);
    Construction(p, amount);
    adjacency(p, amount);
    int *mas = make_mas(p, amount);
    sort(mas, (amount - 2));
    if (((amount - 2) == 3) &&(mas[1] > mas[2])){
        int k = mas[1];
        mas[1] = mas[2];
        mas[2] = k;
    }
    Construction_sorted(mas, (amount - 2));
    free(p);
    return 0;
}
