#include <stdio.h>
#include <math.h>
#define n 3

void line();

int main()
{
    float name_score[n+1][5];

    for(int i=0;i<n;i++){
       for(int j=0;j<3;j++){
            scanf("%f", &name_score[i][j]);
       }
    }
    line();

    printf(" Num  Assignments  Midterm Exam  Final Exam  Raw Score  Adjusted Score \n");
    line();

    for(int i=0;i<n;i++){
        printf(" %d", i+1);
        float r=0,a=0;

        for(int j=0;j<3;j++){
                printf((j == 0)?"%15.0f":(j == 1)?"%14.0f":"%12.0f", name_score[i][j]);
                if(j<=1)
                r+=name_score[i][j]*0.3;
                else
                r+=name_score[i][j]*0.4;
        }
        name_score[i][3]=r;
        printf("%11.1f", r);
        a=pow(r,0.4)*12+25;
        name_score[i][4]=a;
        printf("%16.1f\n", a);
    }
    line();

    printf(" Avg");
    for(int h=0;h<5;h++){
        float x=0;
        for(int i=0;i<n;i++){
                x+=name_score[i][h]/3;
        }

        switch(h){
        case 0:
            printf("%13.1f", x);
            break;
        case 1:
            printf("%14.1f", x);
            break;
        case 2:
            printf("%12.1f", x);
            break;
        case 3:
            printf("%11.1f", x);
            break;
        default:
            printf("%16.1f", x);

        }

        name_score[n][h]=x;
    }

    printf("\n");

    printf(" SD");
    for(int g=0;g<5;g++){
        float y=0,b=0;
        for(int j=0;j<n;j++){
            y=name_score[j][g]-name_score[n][g];
            b+=y*y;
        }
        b/=n;
        b=pow(b,0.5);
        printf((g <= 1)?"%14.1f":(g == 2)?"%12.1f":(g == 3)?"%11.1f":"%16.1f",b);
    }

    printf("\n");

    line();
    return 0;
}

void line(){
    for(int x=0;x<71;x++)
        printf("-");
    printf("\n");
}