#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

int main()
{

    char dosyaadi[30]="bos";
    int aldeger,diziuzunluk;



    printf("hangi dosyada islem yapacaginizi seciniz 10lukliste=>1/100lukliste=>2/100000lik liste=>3 olarak:");
    scanf("%d",&aldeger);

    switch (aldeger){

        case 1:
            strcpy(dosyaadi ,"10lukliste.txt");
            diziuzunluk=10;
            puts(dosyaadi);
            printf("\n\n");
            break;
        case 2:
            strcpy(dosyaadi ,"100lukliste.txt");
            diziuzunluk=100;
            puts(dosyaadi);
            printf("\n\n");
            break;

        case 3:
            strcpy(dosyaadi ,"100000likliste.txt");
            diziuzunluk=100000;
            puts(dosyaadi);
            printf("\n\n");
            break;
        default:
            printf("case hatasi");
    }

    //-------------------------------------------------------

    FILE *acdosya=fopen(dosyaadi,"r");

    if(acdosya==NULL){
        printf("dosya bulunamadi");
        return 0;
    }

    float sayi;
    float alinandizi[diziuzunluk][2];
    float ondalikkisim,ondalik;
    int tamkisim,birler,onlar,yuzler,binler;
    float ondalikbir,ondalikon,ondalikyuz;
    int dizibasamakli[diziuzunluk][9];


    //SAYININ TXT DOSYASINDAN OKUNMASI
    for(int i=0;i<diziuzunluk;i++){
    fscanf(acdosya,"%f",&sayi);

    //SAYININ TAM KISMINI VE ONDALIK AYIRDIK
    tamkisim =sayi;
    ondalik=sayi-tamkisim;
    ondalikkisim=(ondalik*1000);


    //SAYININ ONDALIK KISMINI BASAMAKLARA AYIRDIK
    ondalikbir=ondalikkisim-(floor(ondalikkisim/10)*10);
    //ondalikbir=ondalikkisim-(floor(ondalikkisim/10)*10);
    ondalikyuz=floor((ondalikkisim-ondalikbir)/100);
    ondalikon=(ondalikkisim-((ondalikyuz*100)+ondalikbir))/10;

    //SAYININ TAM KISMINI BASAMAKLARA AYIRDIK
    birler=tamkisim%10;
    onlar=((tamkisim-birler)/10)%10;
    yuzler=((tamkisim-((onlar*10)+birler))/100)%10;
    binler=(tamkisim-((yuzler*100)+(onlar*10)+birler))/1000;

    //TAM VE ONDALIK KISIMLARI ATADIK
    alinandizi[i][0]=tamkisim;
    alinandizi[i][1]=ondalikkisim;

    //BÜTÜN BASAMAKLARIN OLDUĞU DİZİ
    dizibasamakli[i][0]=tamkisim;
    dizibasamakli[i][1]=round(ondalikkisim);        //son olarak bu kısım düzeltildi
    dizibasamakli[i][2]=binler;
    dizibasamakli[i][3]=yuzler;
    dizibasamakli[i][4]=onlar;
    dizibasamakli[i][5]=birler;
    dizibasamakli[i][6]=ondalikyuz;
    dizibasamakli[i][7]=ondalikon;
    dizibasamakli[i][8]=round(ondalikbir);          //son olarak burası düzeeltildi

    }

    printf("liste baslangic durumu\n");
   DiziGoster(diziuzunluk,dizibasamakli);
        clock_t start_t,end_t;
    for(int siraladongu=8;siraladongu>=2;siraladongu--){

            start_t=clock();
        DiziSirala(diziuzunluk,dizibasamakli,siraladongu);
        if(siraladongu==2){printf("!!------RADIX SORT ILE SIRALANMIS LISTE-----!!\n");}
        DiziGoster(diziuzunluk,dizibasamakli);
            end_t=clock();
    }
    printf("radix siralama islemi %.2f saniyede gerceklesti",(double)(end_t-start_t)/CLOCKS_PER_SEC);

    fclose(acdosya);
    return 0;
}

void DiziSirala(int diziboy,int diziyaz[][9],int basdegeri){        //RADİX ALGORİTMASI İLE SIRALAMA

    int gecicidizim[1][9];

    int i, j;
    for (i = 1; i < diziboy; i++) {

            for(int say1=8;say1>=0;say1--){

        gecicidizim[0][say1] = diziyaz[i][say1];
            }

        j = i - 1;

        while (j >= 0 && diziyaz[j][basdegeri] > gecicidizim[0][basdegeri]) {

                for(int say2=8;say2>=0;say2--){

        diziyaz[j + 1][say2] = diziyaz[j][say2];
            }

            j = j - 1;
        }
        for(int say3=8;say3>=0;say3--){

        diziyaz[j + 1][say3] = gecicidizim[0][say3];
            }

    }

}

void DiziGoster(int diziboy, int diziyaz[][9]){

        printf("---dizi yazdiriliyor---\n");

    for(int k=0;k<diziboy;k++){
/*
        printf("atanmis dizi sayinin tam kisimi: %d\n",diziyaz[k][0]);
        printf("atanmis dizi sayinin kusurat kisimi: %d\n",diziyaz[k][1]);
        printf("atanmis dizi binler bas: %d\n",diziyaz[k][2]);
        printf("atanmis dizi yuzler bas: %d\n",diziyaz[k][3]);
        printf("atanmis dizi onlar bas: %d\n",diziyaz[k][4]);
        printf("atanmis dizi birler bas: %d\n",diziyaz[k][5]);
        printf("atanmis dizi ondalikyuzler bas: %d\n",diziyaz[k][6]);
        printf("atanmis dizi ondalikonlar bas: %d\n",diziyaz[k][7]);
        printf("atanmis dizi ondalikbirler bas: %d\n",diziyaz[k][8]);

*/
        if(diziyaz[k][1]>0){
            printf("Sayinin Kendisi: %d.%d\n\n",diziyaz[k][0],diziyaz[k][1]);
        }
        else{
            printf("Sayinin Kendisi: %d\n\n",diziyaz[k][0]);
        }

    }

}
