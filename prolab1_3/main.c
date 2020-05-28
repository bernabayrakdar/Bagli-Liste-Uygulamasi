#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct sehir
{
    int plaka;
    char isim[500];
    char bolge[100];
    int komsu_sayisi;
    struct sehir *prev;
    struct komsu *komsusonraki;
    struct sehir *sehirsonraki;
};

struct komsu
{
    char komsu_isim[100];
    char komsu_bolge[100];
    int komsu_plaka;
    struct komsu *sonraki;

};

struct sehir *birinci = NULL;
struct sehir *ilk = NULL;
struct sehir *sonra = NULL;
struct sehir *once = NULL;
struct sehir *son = NULL;
struct sehir *gecis = NULL;
struct komsu *gecici = NULL;
struct komsu *ikinci = NULL;
struct komsu *sonuncu = NULL;
struct komsu *yedek = NULL;
struct sehir *sehir_yedek = NULL;

void komsu_dugum_olustur(struct sehir *sehirler, struct komsu *komsu)
{

    struct komsu *eklenecek = (struct komsu*)malloc(sizeof(struct komsu));
    struct komsu *yedek = (struct komsu*)malloc(sizeof(struct komsu));
    struct sehir *yeni_sehir = (struct sehir*)malloc(sizeof(struct sehir));

    strcpy(yeni_sehir->isim,sehirler->isim);
    yeni_sehir->plaka = sehirler->plaka;


    eklenecek->komsu_plaka = komsu->komsu_plaka;
    strcpy(eklenecek->komsu_isim,komsu->komsu_isim);
    strcpy(eklenecek->komsu_bolge,komsu->komsu_bolge);
    eklenecek->sonraki = NULL;

    if(birinci == NULL )
    {
        birinci = yeni_sehir;
        birinci->plaka = yeni_sehir->plaka;

        ikinci = eklenecek;
        sonuncu = eklenecek;

        strcpy(ikinci->komsu_isim,eklenecek->komsu_isim);
        strcpy(ikinci->komsu_bolge,eklenecek->komsu_bolge);
        ikinci->komsu_plaka = eklenecek->komsu_plaka;

        birinci->komsusonraki = ikinci;
        birinci->sehirsonraki = NULL;
        sonuncu->sonraki = NULL;

    }
    else
    {
        gecici = ikinci;

        while(gecici != NULL)
        {
            if(eklenecek->komsu_plaka < ikinci->komsu_plaka)
            {
                birinci->komsusonraki = eklenecek;
                eklenecek->sonraki = ikinci;
                ikinci = eklenecek;
                sonuncu->sonraki = NULL;
                break;
            }
            else if(eklenecek->komsu_plaka > gecici->komsu_plaka && gecici->sonraki == NULL)
            {
                gecici->sonraki = eklenecek;
                eklenecek->sonraki = NULL;
                sonuncu = eklenecek;
                gecici = eklenecek;
                break;
            }
            else if(eklenecek->komsu_plaka > gecici->komsu_plaka && eklenecek->komsu_plaka < gecici->sonraki->komsu_plaka)
            {
                yedek = gecici->sonraki;
                gecici->sonraki = eklenecek;
                eklenecek->sonraki = yedek;
                sonuncu->sonraki = NULL;
                break;
            }
            gecici = gecici->sonraki;
        }
    }
}

void sehir_dugum_olustur(struct sehir *sehirler)
{
    struct sehir *eklenecek_sehir = (struct sehir*)malloc(sizeof(struct sehir));

    strcpy(eklenecek_sehir->isim,sehirler->isim);
    strcpy(eklenecek_sehir->bolge,sehirler->bolge);

    eklenecek_sehir->plaka = sehirler->plaka;
    eklenecek_sehir->komsu_sayisi = sehirler->komsu_sayisi;

    if(ilk == NULL)
    {
        ilk = eklenecek_sehir;
        ilk->komsusonraki = ikinci;
        ilk->sehirsonraki = NULL;
        ilk->prev = NULL;
    }
    else
    {
        gecis = ilk;

        while(gecis != NULL)
        {
            eklenecek_sehir->komsusonraki = ikinci;

            if(eklenecek_sehir->plaka < ilk->plaka)
            {
                ilk->prev = eklenecek_sehir;
                eklenecek_sehir->sehirsonraki = ilk;
                eklenecek_sehir->prev = NULL;
                ilk = eklenecek_sehir;
                break;
            }
            else if(eklenecek_sehir->plaka > gecis->plaka && gecis->sehirsonraki == NULL)
            {
                gecis->sehirsonraki = eklenecek_sehir;
                eklenecek_sehir->prev = gecis;
                eklenecek_sehir->sehirsonraki = NULL;
                gecis = eklenecek_sehir;
                break;
            }
            else if(eklenecek_sehir->plaka > gecis->plaka && eklenecek_sehir->plaka < gecis->sehirsonraki->plaka)
            {
                sehir_yedek = gecis->sehirsonraki;
                gecis->sehirsonraki = eklenecek_sehir;
                eklenecek_sehir->prev = gecis;
                eklenecek_sehir->sehirsonraki = sehir_yedek;
                sehir_yedek->prev = eklenecek_sehir;
                break;
            }
            gecis = gecis->sehirsonraki;
        }
    }
}

void yaz()
{
    gecis = ilk;

    while(gecis != NULL)
    {
        printf("sehir: %d------>",gecis->plaka);
        printf("%s ",gecis->isim);

        gecici = gecis->komsusonraki;

        while(gecici != NULL)
        {
            printf("komsu : %d------>",gecici->komsu_plaka);
            printf("%s ",gecici->komsu_isim);

            gecici = gecici->sonraki;
        }

        printf("\n\n");

        birinci = NULL;
        ikinci = NULL;
        sonuncu = NULL;
        gecici = NULL;
        yedek = NULL;

        gecis = gecis->sehirsonraki;
    }

    printf("\n\n");

}
void ara(char *kelime, struct sehir *sehirler, int komsu_say)
{
    struct komsu *komsu = (struct komsu*)malloc(sizeof(struct komsu));
    char satir[100];
    struct sehir *sehirtut = (struct sehir*)malloc(sizeof(struct sehir));
    int i =0,j=0;
    const char *ayrac = "\0";

    strcpy(komsu->komsu_isim,kelime);
    sehirler->komsu_sayisi = komsu_say;
    printf("gelen komsu: %s--\n",komsu->komsu_isim);

    FILE *dosya =fopen("sehirler.txt","r");
    while(!feof(dosya))
    {

git:
        fgets(satir,100,dosya);

        for(i=0; i<100; i++)
        {
            if(satir[i] == ',')
            {
                satir[i] = ' ';

            }
        }
        sscanf(satir,"%d %s %s",&sehirtut->plaka,sehirtut->isim,sehirtut->bolge);


        if(strcmp(komsu->komsu_isim,sehirtut->isim)==0)
        {
            komsu->komsu_plaka = sehirtut->plaka;
            strcpy(komsu->komsu_isim,sehirtut->isim);
            strcpy(komsu->komsu_bolge,sehirtut->bolge);

            printf("komsu plaka-------------------------- %d\n",komsu->komsu_plaka);
            komsu_dugum_olustur(sehirler,komsu);
            break;
        }

        else if(strstr(komsu->komsu_isim,ayrac))
        {
            if(strstr(komsu->komsu_isim,sehirtut->isim))
            {
                komsu->komsu_plaka = sehirtut->plaka;
                strcpy(komsu->komsu_isim,sehirtut->isim);
                strcpy(komsu->komsu_bolge,sehirtut->bolge);

                printf("------------------------komsu plaka-------------------------- %d\n",komsu->komsu_plaka);
                komsu_dugum_olustur(sehirler,komsu);
                break;
            }
        }
        else
        {
            goto git;
        }

    }
    fclose(dosya);
}

int main()
{

    struct sehir *sehirler = (struct sehir*)malloc(sizeof(struct sehir));
    struct komsu *komsu = (struct komsu*)malloc(sizeof(struct komsu));

    char satir [100];
    int sayac=0,komsu_say=0,komsu_sayisi,sayi1,sayi2,sil_plaka;
    char *kelime = malloc(sizeof(char)*0);
    int secim,plaka,komsu_plaka;
    char *eklenecek_sehir = malloc(sizeof(char)*20);
    char *komsu_bolge = malloc(sizeof(char)*20);
    char *komsu_isim = malloc(sizeof(char)*20);
    char *sehir_isim = malloc(sizeof(char)*20);
    char *sehir_bolge = malloc(sizeof(char)*5);
    char *aranan_bolge = malloc(sizeof(char)*20);

    FILE *dosya =fopen("sehirler.txt","r");
    while(!feof(dosya))
    {
        komsu_say = 0;
        fgets(satir,100,dosya);
        const char *ayrac  = ",";
        kelime = strtok(satir,ayrac);
        while(kelime != NULL)
        {
            sayac++;
            if(sayac == 1)
            {
                sehirler->plaka = atoi(kelime);
                printf("plaka: %d\n ",sehirler->plaka);
            }

            if(sayac == 2)
            {
                strcpy(sehirler->isim,kelime);
                printf("sehir isim: %s\n",sehirler->isim);
            }

            if(sayac == 3)
            {
                strcpy(sehirler->bolge,kelime);
                printf("sehir bolge: %s\n",sehirler->bolge);
            }

            if(sayac > 3)
            {
                komsu_say++;
                ara(kelime,sehirler,komsu_say);

            }

            kelime = strtok(NULL,ayrac);
        }
        sehirler->komsu_sayisi = komsu_say;
        sehir_dugum_olustur(sehirler);
        yaz();

        sayac=0;
    }
    fclose(dosya);
    komsu_say = 0;

    FILE *cikti = fopen("cikti.txt","w");

    struct sehir *sehir_yaz  = (struct sehir*)malloc(sizeof(struct sehir));
    sehir_yaz = ilk;
    struct komsu *komsu_yaz  = (struct komsu*)malloc(sizeof(struct komsu));

    while( sehir_yaz != NULL)
    {
        fprintf(cikti,"sehir: %d ",sehir_yaz->plaka);
        fprintf(cikti,"%s %s %d------>",sehir_yaz->isim,sehir_yaz->bolge,sehir_yaz->komsu_sayisi);

        komsu_yaz = sehir_yaz->komsusonraki;

        while( komsu_yaz != NULL)
        {
            fprintf(cikti,"%d------>",komsu_yaz->komsu_plaka);

            komsu_yaz = komsu_yaz->sonraki;
        }
        fprintf(cikti,"\n\n");
        sehir_yaz = sehir_yaz->sehirsonraki;
    }

    fclose(cikti);

    while(1)
    {
        printf("-------------------\n");
        printf("\n\n1: SEHIR EKLEME. \n");
        printf("2: SEHIR ARAMA. \n");
        printf("3: BOLGE SORGULAMA. \n");
        printf("4: KOMSU SAYISINA GORE SORGULAMA. \n");
        printf("5: SEHIR SILME. \n");
        printf("6: BONUS \n");
        printf("7: KOMSULUK EKLEME \n");
        printf("8: KOMSU SILME \n");
        printf("9: CIKIS \n");
        printf("-------------------\n");

        printf("\n");
        printf("secim:");

        scanf("%d",&secim);
        printf("\n");

        if (secim == 9)
        {
            break;
        }

        switch(secim)
        {

git5:
        case 1:
        {

            FILE *cikti = fopen("cikti.txt","a");
            fprintf(cikti,"SECIM 1\n");

            printf("eklemek istediginiz sehirin adini plakasini bolgesini ve komsu sayisini girin:");
            scanf("%s %d %s %d",eklenecek_sehir,&plaka,sehir_bolge,&komsu_sayisi);
            printf("\n\n");

            fprintf(cikti,"eklenecek sehir: %s\n",eklenecek_sehir);
            fprintf(cikti,"eklenecek sehir plakasi: %d\n",plaka);
            fprintf(cikti,"eklenecek sehir bolge: %s\n",sehir_bolge);
            fprintf(cikti,"eklenecek sehir komsu sayisi: %d\n",komsu_sayisi);

            gecis = ilk;
            while(gecis != NULL)
            {
                if(plaka == gecis->plaka)
                {
                    printf("Sehir listede var eklenemez!\n");
                    fprintf(cikti,"Sehir listede var eklenemez!\n");
                    goto git;

                }
                gecis = gecis->sehirsonraki;
            }

            sehirler->plaka = plaka;
            sehirler->komsu_sayisi = komsu_sayisi;
            strcpy(sehirler->isim,eklenecek_sehir);
            strcpy(sehirler->bolge,sehir_bolge);

            sehir_dugum_olustur(sehirler);
            yaz();


            struct sehir *sehir_yaz  = (struct sehir*)malloc(sizeof(struct sehir));
            sehir_yaz=ilk;
            struct komsu *komsu_yaz  = (struct komsu*)malloc(sizeof(struct komsu));

            while(sehir_yaz != NULL)
            {

                fprintf(cikti,"sehir: %d ",sehir_yaz->plaka);
                fprintf(cikti,"%s %s %d------>",sehir_yaz->isim,sehir_yaz->bolge,sehir_yaz->komsu_sayisi);

                komsu_yaz = sehir_yaz->komsusonraki;

                while( komsu_yaz != NULL)
                {
                    fprintf(cikti,"%d------>",komsu_yaz->komsu_plaka);

                    komsu_yaz = komsu_yaz->sonraki;
                }
                fprintf(cikti,"\n\n");
                sehir_yaz = sehir_yaz->sehirsonraki;
            }
            fclose(cikti);
        }
git:
        break;
        case 2:
        {
            FILE *cikti = fopen("cikti.txt","a");
            fprintf(cikti,"SECIM 2\n");

            printf(" Aramak istediginiz sehrin plaka kodunu girin:");
            scanf("%d",&plaka);
            int sayac = 0;
            int ekle_sayi;

            fprintf(cikti,"aranacak sehrin plakasi: %d",plaka);

            gecis = ilk;
            while(gecis != NULL)
            {
                if(gecis->plaka == plaka)
                {
                    sayac++;
                    printf("plaka no: %d\n",gecis->plaka);
                    fprintf(cikti,"plaka no: %d\n",gecis->plaka);
                    printf("sehir adi: %s\n",gecis->isim);
                    fprintf(cikti,"sehir adi: %s\n",gecis->isim);
                    printf("bolgesi: %s\n",gecis->bolge);
                    fprintf(cikti,"bolgesi: %s\n",gecis->bolge);
                    printf("komsu Sayisi: %d\n",gecis->komsu_sayisi);
                    fprintf(cikti,"komsu Sayisi: %d\n",gecis->komsu_sayisi);

                    gecici = gecis ->komsusonraki;

                    while(gecici != NULL)
                    {
                        printf("Komsu: %s %d %s\n\n",gecici->komsu_isim,gecici->komsu_plaka,gecici->komsu_bolge);
                        fprintf(cikti,"Komsu: %s %d %s\n\n",gecici->komsu_isim,gecici->komsu_plaka,gecici->komsu_bolge);
                        gecici = gecici->sonraki;
                    }
                }

                gecis = gecis->sehirsonraki;
            }

            if(sayac == 0)
            {
                printf("dosyada yok eklemek icin 1 e basin");
                printf("istemiyorsaniz 2 ye basin");
                scanf("%d",&ekle_sayi);

                if(ekle_sayi == 1)
                    goto git5;
                else
                    goto git4;
            }
            fclose(cikti);
        }
git4:
        break;
        case 3:
        {
            FILE *cikti = fopen("cikti.txt","a");
            fprintf(cikti,"SECIM 3\n");

            printf("Bolge adi girin:");
            scanf("%s",aranan_bolge);

            fprintf(cikti,"Aranan bolge: %s\n",aranan_bolge);

            gecis = ilk;
            while(gecis != NULL)
            {
                if(strcmp(aranan_bolge,gecis->bolge)==0)
                {
                    printf("plaka no: %d\t",gecis->plaka);
                    fprintf(cikti,"plaka no: %d\t",gecis->plaka);
                    printf("sehir adi: %s\t",gecis->isim);
                    fprintf(cikti,"sehir adi: %s\t",gecis->isim);
                    printf("bolgesi: %s\t",gecis->bolge);
                    fprintf(cikti,"bolgesi: %s\t",gecis->bolge);
                    printf("komsu sayisi: %d\n",gecis->komsu_sayisi);
                    fprintf(cikti,"komsu sayisi: %d\n",gecis->komsu_sayisi);

                    gecici = gecis->komsusonraki;
                }
                gecis = gecis->sehirsonraki;

            }
            fclose(cikti);
        }
        break;
        case 4:
        {
            FILE *cikti = fopen("cikti.txt","a");
            fprintf(cikti,"SECIM 4\n");

            printf("Komsu sayisi girin:");
            scanf("%d",&komsu_sayisi);
            fprintf(cikti,"Komsu sayisi:%d\n",komsu_sayisi);

            gecis = ilk;
            while(gecis != NULL)
            {
                if(komsu_sayisi == gecis->komsu_sayisi || komsu_sayisi < gecis->komsu_sayisi )
                {
                    printf("sehir adi: %s\t komsu sayisi: %d\n",gecis->isim,gecis->komsu_sayisi);
                    fprintf(cikti,"sehir adi: %s\t komsu sayisi: %d\n",gecis->isim,gecis->komsu_sayisi);

                }
                gecis = gecis->sehirsonraki;
            }
            fclose(cikti);
        }
        break;
        case 5:
        {
            FILE *cikti = fopen("cikti.txt","a");
            fprintf(cikti,"SECIM 5\n");

            printf("silmek istediginiz sehrin plakasini girin:");
            scanf("%d",&sil_plaka);

            fprintf(cikti,"silinmek istenen sehrin plakasi: %d\n",sil_plaka);

            gecis = ilk ;
            while(gecis != NULL)
            {

                if(ilk->plaka == sil_plaka && ilk->prev == NULL)
                {
                    printf("bastan sil\n");
                    gecis = ilk->sehirsonraki;
                    free(ilk);
                    gecis->prev = NULL;
                    ilk = gecis;
                    sehir_dugum_olustur(gecis);
                    yaz();
                    break;

                }

                else if(gecis->plaka == sil_plaka && gecis->sehirsonraki == NULL)
                {
                    printf("\n sondan  sil\n");

                    struct sehir *silinecek = NULL;
                    silinecek = (struct sehir*)malloc(sizeof(struct sehir));

                    silinecek = gecis;
                    gecis = gecis->prev;
                    gecis->sehirsonraki = NULL;
                    free(silinecek);
                    printf("%d",gecis->prev->plaka);

                    sehir_dugum_olustur(ilk);
                    yaz();

                    break;
                }

                else  if(gecis->plaka == sil_plaka && gecis->sehirsonraki != NULL && gecis->prev != NULL)
                {
                    struct sehir *sonra = (struct sehir*)malloc(sizeof(struct sehir));
                    struct sehir *once = (struct sehir*)malloc(sizeof(struct sehir));
                    printf("aradan sil\n");
                    once = gecis->prev;
                    sonra = gecis->sehirsonraki;
                    free(gecis);
                    once->sehirsonraki =sonra;
                    once = sonra->prev;
                    printf("gecis prev: %s\n",once->isim);
                    printf("gecis sonra: %s\n",sonra->isim);
                    sehir_dugum_olustur(gecis->prev);
                    yaz();
                    break;
                }
                gecis = gecis->sehirsonraki;
            }
            struct sehir *sehir_yaz  = (struct sehir*)malloc(sizeof(struct sehir));
            sehir_yaz=ilk;
            struct komsu *komsu_yaz  = (struct komsu*)malloc(sizeof(struct komsu));

            while(sehir_yaz != NULL)
            {

                fprintf(cikti,"sehir: %d ",sehir_yaz->plaka);
                fprintf(cikti,"%s %s %d------>",sehir_yaz->isim,sehir_yaz->bolge,sehir_yaz->komsu_sayisi);

                komsu_yaz = sehir_yaz->komsusonraki;

                while( komsu_yaz != NULL)
                {
                    fprintf(cikti,"%d------>",komsu_yaz->komsu_plaka);

                    komsu_yaz = komsu_yaz->sonraki;
                }
                fprintf(cikti,"\n\n");


                sehir_yaz = sehir_yaz->sehirsonraki;

            }
            fclose(cikti);
        }
        break;
        case 6:
        {
            FILE *cikti = fopen("cikti.txt","a");
            fprintf(cikti,"SECIM 6\n");

            printf("Komsu sayilarini girin:");
            scanf("%d %d",&sayi1,&sayi2);
            printf("\n");

            fprintf(cikti,"komsu sayilari:%d %d\n",sayi1,sayi2);

            struct komsu *temp = (struct komsu*)malloc(sizeof(struct komsu));
            struct sehir *tut = NULL;
            tut = (struct sehir*)malloc(sizeof(struct sehir));

            int sayac = 0;
            gecis = ilk;
            while(gecis != NULL)
            {
                if(gecis->komsu_sayisi > sayi1 && gecis->komsu_sayisi < sayi2)
                {
                    tut = gecis->sehirsonraki;
                    while(tut != NULL)
                    {
                        if(tut->komsu_sayisi > sayi1 && tut->komsu_sayisi < sayi2)
                        {
                            gecici = gecis->komsusonraki;
                            temp = tut->komsusonraki;

                            while(gecici != NULL)
                            {
                                while(temp != NULL)
                                {
                                    if(gecici->komsu_plaka == temp->komsu_plaka)
                                    {
                                            printf("sehirler: %s %s\n",gecis->isim,tut->isim);
                                            fprintf(cikti,"sehirler: %s %s\n",gecis->isim,tut->isim);
                                            printf("ayni komsu: %s\n",gecici->komsu_isim);
                                            fprintf(cikti,"ayni komsu: %s\n",gecici->komsu_isim);
                                            break;
                                    }
                                    temp = temp->sonraki;
                                }
                                gecici = gecici->sonraki;
                                temp = tut->komsusonraki;
                            }
                        }
                        printf("\n");
                        fprintf(cikti,"\n");
                        tut = tut->sehirsonraki;
                    }
                }
                printf("\n\n");
                fprintf(cikti,"\n\n");
                gecis = gecis->sehirsonraki;
            }

        }

        fclose(cikti);

        break;
        case 7:
        {
            FILE *cikti = fopen("cikti.txt","a");
            fprintf(cikti,"SECIM 7\n");

            printf("komsuluk eklemek istediginiz sehrin bilgilerini(p/i) ve komsuluk bilgisi girin(p/i/b):");
            scanf("%d %s %d %s %s",&plaka,eklenecek_sehir,&komsu_plaka,komsu_isim,komsu_bolge);
            fprintf(cikti,"komsuluk eklenecek sehir ve komsuluk bilgileri: %d %s %d %s %s\n",plaka,eklenecek_sehir,komsu_plaka,komsu_isim,komsu_bolge);

            komsu->komsu_plaka = komsu_plaka;
            strcpy(komsu->komsu_isim,komsu_isim);
            strcpy(komsu->komsu_bolge,komsu_bolge);

            sehirler->plaka = plaka;
            strcpy(sehirler->isim,eklenecek_sehir);

            gecis = ilk;
            while(gecis != NULL)
            {
                if(gecis->plaka == sehirler->plaka)
                {
                    gecici = gecis->komsusonraki;

                    while(gecici != NULL)
                    {
                        if(gecici->komsu_plaka == komsu->komsu_plaka)
                        {
                            printf("Komsu var eklenemez!!\n");
                            fprintf(cikti,"Komsu var eklenemez!!\n");
                            goto gitt;
                        }
                        gecici = gecici->sonraki;
                    }
                }
                gecis = gecis->sehirsonraki;
            }

            struct komsu *ekle = NULL;
            ekle = (struct komsu*)malloc(sizeof(struct sehir));
            ekle = komsu;

            gecis = ilk;
            while(gecis != NULL)
            {
                if(gecis->plaka == sehirler->plaka)
                {
                    gecici = gecis->komsusonraki;

                    while(gecici != NULL)
                    {
                        if(ekle->komsu_plaka < gecici->komsu_plaka)
                        {
                            gecis->komsusonraki = ekle;
                            ekle->sonraki= gecici;
                            break;
                        }
                        else if (ekle->komsu_plaka > gecici->komsu_plaka && gecici->sonraki == NULL)
                        {
                            gecici->sonraki = ekle;
                            ekle->sonraki = NULL;
                            break;
                        }
                        else if(ekle->komsu_plaka > gecici->komsu_plaka && ekle->komsu_plaka < gecici->sonraki->komsu_plaka)
                        {
                            yedek = gecici->sonraki;
                            gecici->sonraki = ekle;
                            ekle->sonraki = yedek;
                            break;
                        }
                        gecici = gecici->sonraki;
                    }
                }
                gecis = gecis ->sehirsonraki;
            }
            sehir_dugum_olustur(sehirler);
            yaz();

            struct sehir *sehir_yaz  = (struct sehir*)malloc(sizeof(struct sehir));
            struct komsu *komsu_yaz  = (struct komsu*)malloc(sizeof(struct komsu));

            sehir_yaz=ilk;
            while(sehir_yaz != NULL)
            {

                fprintf(cikti,"sehir: %d ",sehir_yaz->plaka);
                fprintf(cikti,"%s %s %d------>",sehir_yaz->isim,sehir_yaz->bolge,sehir_yaz->komsu_sayisi);

                komsu_yaz = sehir_yaz->komsusonraki;

                while( komsu_yaz != NULL)
                {
                    fprintf(cikti,"%d------>",komsu_yaz->komsu_plaka);

                    komsu_yaz = komsu_yaz->sonraki;
                }
                fprintf(cikti,"\n\n");

                sehir_yaz = sehir_yaz->sehirsonraki;
            }
            fclose(cikti);
        }
gitt:
        break;
        case 8:
        {
            FILE *cikti = fopen("cikti.txt","a");
            fprintf(cikti,"SECIM 8\n");

            printf("sehir bilgisini ve silmek istediginiz komsunun bilgisini girin:(plaka/isim)");
            scanf("%d %s %d %s",&plaka,sehir_isim,&sil_plaka,komsu_isim);

            fprintf(cikti,"sehir bilgisini ve silmek istediginiz komsunun bilgisini girin: %d %s %d %s\n",plaka,sehir_isim,sil_plaka,komsu_isim);

            sehirler->plaka = plaka;

            gecis = ilk;
            while(gecis != NULL)
            {
                if(gecis->plaka == sehirler->plaka)
                {
                    gecici = gecis->komsusonraki;

                    while(gecici != NULL)
                    {
                        if(sil_plaka == gecici->komsu_plaka)
                        {
                            struct komsu *sil = NULL;
                            sil = (struct komsu*)malloc(sizeof(struct komsu));

                            if(gecis->komsusonraki == gecici)
                            {
                                sil = gecici;
                                gecis->komsusonraki = gecici->sonraki;
                                free(sil);
                                break;
                            }

                        }
                        else if(gecici->sonraki->sonraki == NULL)
                        {

                            if(sil_plaka == gecici->sonraki->komsu_plaka)
                            {
                                struct komsu *sil = NULL;
                                sil = (struct komsu*)malloc(sizeof(struct komsu));

                                sil = gecici->sonraki;
                                free(sil);
                                gecici->sonraki = NULL;
                                break;
                            }

                        }
                        else if(sil_plaka == gecici->sonraki->komsu_plaka && gecici->sonraki->sonraki != NULL)
                        {
                            struct komsu *yedek1 = NULL;
                            struct komsu *yedek2 = NULL;
                            struct komsu *sil = NULL;

                            sil = (struct komsu*)malloc(sizeof(struct komsu));
                            yedek1 = (struct komsu*)malloc(sizeof(struct komsu));
                            yedek2 = (struct komsu*)malloc(sizeof(struct komsu));

                            yedek1 = gecici->sonraki->sonraki;
                            yedek2 = gecici;
                            sil = gecici->sonraki;
                            free(sil);
                            yedek2->sonraki = yedek1;
                            break;

                        }
                        gecici = gecici->sonraki;
                    }
                }
                gecis = gecis->sehirsonraki;
            }
            sehir_dugum_olustur(sehirler);
            yaz();

            struct sehir *sehir_yaz  = (struct sehir*)malloc(sizeof(struct sehir));
            sehir_yaz=ilk;
            struct komsu *komsu_yaz  = (struct komsu*)malloc(sizeof(struct komsu));

            while(sehir_yaz != NULL)
            {

                fprintf(cikti,"sehir: %d ",sehir_yaz->plaka);
                fprintf(cikti,"%s %s %d------>",sehir_yaz->isim,sehir_yaz->bolge,sehir_yaz->komsu_sayisi-1);

                komsu_yaz = sehir_yaz->komsusonraki;

                while( komsu_yaz != NULL)
                {
                    fprintf(cikti,"%d------>",komsu_yaz->komsu_plaka);

                    komsu_yaz = komsu_yaz->sonraki;
                }
                fprintf(cikti,"\n\n");
                sehir_yaz = sehir_yaz->sehirsonraki;
            }
            fclose(cikti);
        }
        break;
        }
    }
    return 0;
}

