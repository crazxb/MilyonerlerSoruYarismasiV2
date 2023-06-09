/*Programlama ve Algoritmaya Giriş Şube 1
Hasan Arif Doğan 22181617016 , Erdem Tarık Güral 22181617002 , Furkan Emir KAYA 22181617011 
*/
#include <stdio.h>//FILE,NULL gibi değişken ve makroları atayabilmek için   <<
#include <time.h> //Sleep(); komutu için    <<
#include <stdbool.h>//Boolean integer kullanabilmek için    <<
#include <stdlib.h>//system("pause"); komutu için   <<
#include <locale.h>//Program çalışırken setlocale komutu ile yerel ayarları utf8 formatında ayarlamak için  <<
#include <Windows.h> //Terminalde Unicode yazı gösterebilmek için   <<
#include <conio.h> //getch fonksiyonu için  <<
#include <ctype.h> //toupper fonksiyonu için   <<
#define CVP_ANAHTAR_U 76 //CEVAP ANAHTARI DİZİLERİNİN UZUNLUĞU  << 
#define MAX_SATIR 2048//.txt dosyasındaki okunacak maksimum satır sayısını belirten sabit   <<

int soru_sayaci=1; //YARIŞMACININ KAÇINCI SORUDA OLDUĞUNU TAKİP EDECEK SAYAÇ    <<

int random_deger=0; //RANDOM DEĞERİN TUTULUP/ATANACAĞI DEĞİŞKEN (ÇEKİLEN SORUNUN SATIR NUMARASI BU DEĞŞİKENDE YANİ CEVAP DİZİSİNİN İNDİSİ OLARAK BUNU KULLANDIK) <<

int yyJokeri_sayaci=0; //Yarı yarıya jokeri kontrolü yy     <<
int icJokeri_sayaci=0; //iki cevap jokeri kontrolü ic       <<
int ysJokeri_sayaci=0; //Yeni soru jokeri kontrolü ys       <<

char isim[16]; //OYUNU OYNAYAN KULLANICININ ADI   <<
char cevap[3]; //KULLANICININ SORUYA GİRDİĞİ CEVAP (ic,ys,yy,A,a,B,b,C,c,D,d) GİRİLEBİLİR   <<
char CVPA[CVP_ANAHTAR_U]={'D','A','A','A','B','C','B','A','A','D','D','B','A','D','B','B','B','A','D','C','A','C','B','C','C','A','B','C','B','A','D','B','A','D','A','A','D','D','B','C','A','A','B','D','A','D','C','B','C','A','C','B','C','D','B','C','A','C','D','C','D','A','C','B','A','D','C','A','C','A','C','C','B','D','C'}; //Cevap Anahtarı    <<
//---FONKSİYONLARIN PROTOTİPLERİ/AÇIKLAMASI---
void tanitim(void);   //   <<
void cevapAl_Byap(void);   //KULLANICI CEVAp ALIP BÜYÜK HARFE DÖNDÜRÜR   <<

void yariYariJ(void); //YARI YARIYA JOKERİ  
void ikiCevapJ(void); //İKİ CEVAP JOKERİ -BU JOKER 7. SORU DOĞRU BİLİNDİYSE KULLANILABİLİR-   <<
void yeniSoruJ(void); //YENİ SORU JOKERİ (AYNI ZORLUKTA YENİ SORU GETİRİR)   <<


void yonlendir(void); //RANDOM SAYIYI OLUŞTURUR VE soru_sayaciA GÖRE AKIŞI kRandSoru()/oRandSoru()/zRandSoru()' YA GÖNDERİR    <<

void RandSoru(void); //Sorular.txt DOSYASINDAN RANDOM SORU ÇEKER   <<
void Siklar(void); //Cevaplar.txt DOSYASINDAN ÇEKİLEN SORUNUN ŞIKLARINI YAZDIRIR   <<


int CVPkontrol(void); //KULLANICI CEVABINI KONTROL EDER (ÇEKİLİP ÇEKİLMEDİĞİNİ,KULLANACAĞI JOKERLER, SORU ŞIKLARINI) 
int parEkle(int *); //soru_sayaci A GÖRE KAZANDIĞI PARAYI EKLER//(POİNTER KULLANILDI)   <<

//---MAİN FONKSİYONU---
int main(){
    SetConsoleOutputCP(65001);
    setlocale(LC_ALL, ".utf8");
    srand(time(NULL));

    char tekrar; //Yarışmayı tekrarlama değişkeni

    do{ //Oyunu tekrar oynamamıza yarayan do while döngüsü
        int para=0; //YARIŞMACININ KAZANDIĞI PARA MİKTARI
        int *pp=&para; //Para değişkenin adresini tutan pointer
        int x; //CVPkontrol() ÜN RETURN DEĞERİNİ TUTAR

        tanitim();
        
        do{  //10. soruya kadar soruları döndüren do while döngüsü
            yonlendir();
            x=CVPkontrol();
            if(x==1){
                parEkle(pp);
                soru_sayaci++;
                if(soru_sayaci<11){
                    printf("=================================\nŞu anki kazanılan para:%d\n=================================\n\n\n",para);
        
                    printf("Çekilmek istiyor musun %s?(E/H)\n\a",isim);
                    do{ //Çekilmek isteme sırasında farklı bir veri girildiğinde tekrardan soran do while döngüsü 
                    cevapAl_Byap();
                    } while(cevap[0] != 'E' && cevap[0] != 'H');
                        if(cevap[0] == 'E'){
                            break; 
                        system("cls");
                        continue;
                    }          
                }   
            }
            else if(x==0){
            printf("Cevabınız yanlış.Kaybettiniz.\nMalesef %d ₺ ile seni yolluyoruz %s.\n",para/2,isim);
            break; 
            }        
        } while (soru_sayaci!=11 && x!=0);
    
        if(soru_sayaci==11){
            printf("Tebrikler! 10. soruyu cevaplayarak 1.000.000 ₺'nin sahibi oldun %s!\n\n\a\a\a\a",isim);
            printf("Tekrar oynamak ister misiniz? Evet(E) veya Hayır(H) tuşlayınız.\t\n\n");
            tekrar=getch();
            tekrar=toupper(tekrar);
            soru_sayaci=1, yyJokeri_sayaci=0, icJokeri_sayaci=0, ysJokeri_sayaci=0;
        }    
        else if(cevap[0]=='E'){
            printf("Yarışmadan %d ₺ ile çekildiniz.\n",para);
        }
        else if(x==0){
            printf("Tekrar oynamak ister misiniz? Evet(E) veya Hayır(H) tuşlayınız.\t\n\n");
            tekrar=getch();
            tekrar=toupper(tekrar);
            soru_sayaci=1, yyJokeri_sayaci=0, icJokeri_sayaci=0, ysJokeri_sayaci=0;
        }
    } while (tekrar == 'E');
    system("pause");
    return 0;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<fONKSİYONLATRIN TANIMLAMALARI>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void tanitim(){
    system("CLS");
    printf("\nMerhaba! Kim Milyoner Olmak İster Yarışmasına Hoşgeldin!\nSeni daha iyi tanıyabilmemiz için lütfen adını gir: ");   
    gets(isim);
    Sleep(500); 
    system("CLS"); 
    printf("\t\t\t\t\tMerhaba "); 
    puts(isim);
    printf("\t\t\t\tYarışmada toplamda 10 soru bulunmakta.\n\t\t\tHer doğru cevabın için ödül havuzunda paran birikir.\n\tYanlış cevabında ise bu havuzundaki paranın sadece 1/2'sini alabilirsin ve ardından yarışma sona erer.\n\t\tJokerlerin için Yarı Yarıya(yy), İki Cevap(ic), Yeni Soru(ys) yazabilirsin.\n");
    printf("\t\t\t\t\tHaydi başlayalım!");
    Sleep(10000); 
    system("CLS");
}

void cevapAl_Byap(){
    gets(cevap);
    for(int i=0;i<3;i++){    
        cevap[i]=toupper(cevap[i]);
    }
}
//-------------------------------------------------------------------------------------JOKER FONKSİYONLARI---------------------------------------------------------------------------------------
void yariYariJ(){
    
    int random_deger2=0; //Rastgele  şık eleme 
    char secenekEle[4];

    int temp=0;
    random_deger2=rand()%3;

    if(yyJokeri_sayaci==0){
        yyJokeri_sayaci++;

        if(soru_sayaci>=1 && soru_sayaci<=3){
            switch(CVPA[random_deger-1]){
                case 'A': secenekEle[0]='B';secenekEle[1]='C';secenekEle[2]='D';break;
                case 'B': secenekEle[0]='A';secenekEle[1]='C';secenekEle[2]='D';break;
                case 'C': secenekEle[0]='A';secenekEle[1]='B';secenekEle[2]='D';break;
                case 'D': secenekEle[0]='A';secenekEle[1]='B';secenekEle[2]='C';break;
            }
        }
        else if(soru_sayaci>3 && soru_sayaci<=7){
            switch(CVPA[random_deger-1]){
                case 'A': secenekEle[0]='B';secenekEle[1]='C';secenekEle[2]='D';break;
                case 'B': secenekEle[0]='A';secenekEle[1]='C';secenekEle[2]='D';break;
                case 'C': secenekEle[0]='A';secenekEle[1]='B';secenekEle[2]='D';break;
                case 'D': secenekEle[0]='A';secenekEle[1]='B';secenekEle[2]='C';break;
            }
        }
        else if(soru_sayaci>7 && soru_sayaci<=10){
            switch(CVPA[random_deger-1]){
                case 'A': secenekEle[0]='B';secenekEle[1]='C';secenekEle[2]='D';break;
                case 'B': secenekEle[0]='A';secenekEle[1]='C';secenekEle[2]='D';break;
                case 'C': secenekEle[0]='A';secenekEle[1]='B';secenekEle[2]='D';break;
                case 'D': secenekEle[0]='A';secenekEle[1]='B';secenekEle[2]='C';break;
            }
        }
        
        printf("\n%c ve ",secenekEle[random_deger2]);
        temp=random_deger2;
        do{
        random_deger2=rand()%3;
        }while(secenekEle[random_deger2]==secenekEle[temp]);
        printf("%c şıkkı yanlıştır.\n",secenekEle[random_deger2]);
        cevapAl_Byap();
        CVPkontrol();
    }
    
    else{
        printf("Bu jokeri tekrar kullanamazsın.\n");
        cevapAl_Byap();
        CVPkontrol();
    }
}

void ikiCevapJ(){
    
    if(icJokeri_sayaci==0) 
    {        
        if(soru_sayaci>7){ //Cevap yanlışsa tekrar cevap hakkı tanı CVPKontrol() fonk yolla. soru_sayacina göre bakıp ona uygun cevap anahtarını seçer girdiği şık yanlışsa tekrar hak tanır. 
            icJokeri_sayaci++;
            cevapAl_Byap();
           
            if (cevap[0]!=CVPA[random_deger-1]){
                printf("Cevabınız yanlış,cevabı tekrar giriniz.\n");
                cevapAl_Byap();
                CVPkontrol();
            }
        }
        else{
            printf("Şu anda kullanamazsın;7. soruya ulaşıp doğru bilirsen kullanabilirsin.\n");
            cevapAl_Byap();
            CVPkontrol();
        }
    }
    else{
        printf("Bu jokeri tekrar kullanamazsın.\n");
        cevapAl_Byap();
        CVPkontrol();
    }
}

void yeniSoruJ(){
    
    if(ysJokeri_sayaci==0) //Yönlendir fonk git (soru_sayacia bak soru_sayacia göre uygun random soru çeken fonksşyona git )
    {
        ysJokeri_sayaci++;
        system("cls");
        yonlendir();
        CVPkontrol();
    }
    else{
        printf("Bu jokeri tekrar kullanamazsın.\n");
        cevapAl_Byap();
        CVPkontrol(); 
    }
}
//----------------------------------------------------------------------------------YÖNLENDİRME FONKSİYONU-----------------------------------------------------------------------------------------
void yonlendir(){

    if(soru_sayaci>=1 && soru_sayaci<=3){
        random_deger=1+rand()%25;
        system("CLS");
        printf("\nŞu anda %d. sorudasın\n",soru_sayaci);
        RandSoru();
        Siklar();
        printf("\nJokerler için Yeni Soru Jokeri:ys/YS Yarı Yarıya Jokeri:yy/YY İki Cevap Jokeri:ic/İC\n");
        cevapAl_Byap();
    }
    else if(soru_sayaci>3 && soru_sayaci<=7){
        random_deger=1+rand()%25;
        if(random_deger <= 25){
            random_deger=random_deger+25;
        }
        system("CLS");
        printf("\nŞu anda %d. sorudasın\n",soru_sayaci);
        RandSoru();
        Siklar();
        printf("\nJokerler için Yeni Soru Jokeri:ys/YS Yarı Yarıya Jokeri:yy/YY İki Cevap Jokeri:ic/İC\n");
        cevapAl_Byap();
    }
    else if(soru_sayaci>7 && soru_sayaci<=10){
        random_deger=1+rand()%25;
        if(random_deger <= 50){
            random_deger=random_deger+50;
        }
        system("CLS");
        printf("\nŞu anda %d. sorudasın\n",soru_sayaci);    
        RandSoru();
        Siklar();
        printf("\nJokerler için Yeni Soru Jokeri:ys/YS Yarı Yarıya Jokeri:yy/YY İki Cevap Jokeri:ic/İC\n");
        cevapAl_Byap();
    }
}
//----------------------------------------------------------------------------------SORU/ŞIK ÇEKME FONKSİYONLARI-----------------------------------------------------------------------------
void RandSoru(){
    
    FILE *dosya;
    char gecici[MAX_SATIR];

    dosya=fopen("Sorular.txt","r");

    if(dosya == NULL) //Dosyayı bulamazsa uyarı verip programı sonlandırır
    {
        printf("Dosya açılamadı.\n");
        exit(1);
    }

    bool oku_devam = true;
    int okunan_satır = 1;

    do
    {
        fgets(gecici,MAX_SATIR,dosya);
        if(feof(dosya)) //feof() dosya sonuna geldiğinde 0 döndürür
        {
            oku_devam=false;
        }
        else if(okunan_satır==random_deger)
        {
            oku_devam=false;
            printf("%s\n",gecici);
        }

        okunan_satır++;

    }while(oku_devam);

    fclose(dosya); 
}

void Siklar(){

    FILE *dosya;
    char gecici[MAX_SATIR];

    dosya=fopen("Cevaplar.txt","r");

    if(dosya == NULL) //Dosyayı bulamazsa uyarı verip programı sonlandırır
    {
        printf("Dosya açılamadı.\n");
        exit(1);
    }

    bool oku_devam = true;
    int okunan_satır = 1;

    do
    {
        fgets(gecici,MAX_SATIR,dosya);
        if(feof(dosya)) //feof() dosya sonuna geldiğinde 0 döndürür
        {
            oku_devam=false;
        }
        else if(okunan_satır==random_deger)
        {
            oku_devam=false;
            printf("%s\n",gecici);
        }

        okunan_satır++;

    }while(oku_devam);

    fclose(dosya);
}
//-------------------------------------------------------------------------------CEVAP KONTROL FONKSİYONU------------------------------------------------------------------------------------------
int CVPkontrol(void){
    if(cevap[0]=='Y' && cevap[1]=='S'){    
        yeniSoruJ();
    }
    else if(cevap[0]=='I' && cevap[1]=='C'){
        ikiCevapJ();
    }
    else if(cevap[0]=='Y' && cevap[1]=='Y'){
        yariYariJ();
    }

    { //Sorunun sorulduğu zorluğun cevap anahtarıyla cevabı karşılaştır,Doğruysa 1, yanlışsa 0 döndürecek
        if (soru_sayaci>=1 && soru_sayaci<=3){
            if(cevap[0]==CVPA[random_deger-1])
            return 1;
            else if(cevap[0]!=CVPA[random_deger-1])     
            return 0;     
        }
            
        if(soru_sayaci>3 && soru_sayaci<=7){
            if(cevap[0]==CVPA[random_deger-1])
                return 1;
            else return 0;
        }
        if (soru_sayaci>7 && soru_sayaci<=10){
            if(cevap[0]==CVPA[random_deger-1])
                return 1;
            else return 0;
        }
    }

return 5; //Burda döndürülen değerin bir önemi yok
}
//--------------------------------------------------------------------------------PARA EKLEME FONKSİYONU------------------------------------------------------------------------------------------
int parEkle(int *pp){
    switch(soru_sayaci){
        case 1:
            *pp=1000;break;
        case 2:
            *pp=3000;break;
        case 3:
            *pp=5000;break;
        case 4:
            *pp=7000;break;
        case 5:
            *pp=15000;break;
        case 6:
            *pp=30000;break;
        case 7:
            *pp=60000;break;
        case 8:
            *pp=125000;break;
        case 9:
            *pp=250000;break;
        case 10:
            *pp=1000000;break;
    }
return *pp;
}