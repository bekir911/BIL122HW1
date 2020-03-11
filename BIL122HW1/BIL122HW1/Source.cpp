//Bekir Öztürk
//19120205061 16.02.2020
//BIL 122 Ödev-1

//Bu tip gerekli þeyleri belirtmeme gerek yoktur umarým
#include <iostream>

using namespace std;

//Fonksiyona sadece alýnan sayý gönderileceði için hatalý giriþi tutan deðiþkeni global olarak tanýmladým ve ilklendirdim
int hataliGiris = 0;

//Düz üçgen bastýran fonksiyon
//Baþta fonksiyona gelen deðerin kriterlere uyup uymadýðý if statemant ile kontrol ediliyor
//Uygunsa döngüler için deðiþkenler ve bu deðiþkenlere uygun deðerler atanýyor
//Dýþtaki döngü satýrý kontrol ederken içteki satýrý kontrol ediyor

//Kriterlere uygun deðilse 3 kereye kadar tekrar deðer talep ediyor
//Girilen deðer ile fonksiyon kendisini çaðýrýyor
//Hatalý giriþ sayýsý 3 olduðunda kullanýcý hakkýný kaybediyor ve program sonlanýyor

void duzUcgen(int deger) {
    if ((3 <= deger) && (deger <= 15) && (deger % 2 == 1)) {
        int jDegeri = deger / 2;
        int iDegeri = 1;
        for (int iDegeri = 1; iDegeri != deger + 2; iDegeri += 2, jDegeri--) {
            for (int j = jDegeri; j > 0; j--) {
                cout << " ";
            }
            for (int i = 0; i < iDegeri; i++) {
                cout << "*";
            }
            cout << endl;
        }
    }
    else {
        cout << "Boyut [3,15] araliginda olmali." << endl;
        hataliGiris++;
        if (hataliGiris != 3) {
            cout << "Lutfen boyut degeri girin: ";
            cin >> deger;
            duzUcgen(deger);
        }
        else {
            cout << "3 kez hatali deger girdiginiz icin program kapatiliyor...";
        }

    }
}

//Düz üçgenden çok da farklý deðil. For yerine while kullanýlmýþ hali desek yeridir
//Aslýnda belirtmeseniz ilkinde satýr için while kullanýrdým
//Diðerindeki gibi önce boþluklar sonra yýldýzlar basýlýyor. Tek farký kaç adet basýldýklarý
//Hatalý giriþ muhabbeti burada da mevcut

void tersUcgen(int deger) {
    if ((3 <= deger) && (deger <= 15) && (deger % 2 == 1)) {
        int degerTutucu = deger;
        int iDegeri = 0;
        int satir = deger / 2 + 1;
        int i = 0;
        while (satir-- > 0) {
            while (i++ < iDegeri) {
                cout << " ";
            }
            i = 0;
            while (deger-- > 0) {
                cout << "*";
            }
            cout << endl;
            iDegeri++;
            deger = degerTutucu - 2;
            degerTutucu = deger;
        }
    }
    else {
        cout << "Boyut [3,15] araliginda olmali." << endl;
        hataliGiris++;
        if (hataliGiris != 3) {
            cout << "Lutfen boyut degeri girin: ";
            cin >> deger;
            tersUcgen(deger);
        }
        else {
            cout << "3 kez hatali deger girdiginiz icin program kapatiliyor...";
        }
    }



}

//Kriterleri diðerlerine göre biraz daha farklý olsa da diðer fonksiyonlarý çaðýrmaktan baþka pek bir þey yapmýyor
//Hatalý giriþe çok tolerans gösterdiði söylenemez

void elmas(int deger) {
    if ((5 <= deger) && (deger <= 15) && (deger % 2 == 1)) {
        duzUcgen(deger);
        tersUcgen(deger);
    }
    else {
        cout << "Boyut [5,15] araliginda olmali." << endl;
        hataliGiris++;
        if (hataliGiris != 3) {
            cout << "Lutfen boyut degeri girin: ";
            cin >> deger;
            elmas(deger);
        }
        else {
            cout << "3 kez hatali deger girdiginiz icin program kapatiliyor...";
        }
    }
}

//Kullanýcýnýn þekil ve o þeklin boyutunu seçmesini saðlýyor. Buna uygun fonksiyonlarý çaðýrýyor
//Kullanýcý sýfýr girdiðinde direkt çýkmasý gerektiðini düþündüðüm için pek hoþ durmadý kod
//Switch içine konabilirdi, ya da deðerler fonksiyon içerisinde alýnabilirdi
//Ödevden anladýðým kadarýyla fonksiyonda boyut seçme olmamalýydý o yüzden böyle yaptým.

int main() {
    int secim;
    cout << "1: Duz ucgen, 2: Ters ucgen, 3: Elmas, 0: Cikis" << endl << "Lutfen sekil turunu secin: ";
    cin >> secim;
    if (secim == 0) {
        cout << "Cikis yapiliyor...";
        return 0;
    }
    int alinanSayi;
    cout << "Lutfen boyut degeri girin: ";
    cin >> alinanSayi;
    switch (secim) {
    case 1:
        duzUcgen(alinanSayi);
        break;
    case 2:
        tersUcgen(alinanSayi);
        break;
    case 3:
        elmas(alinanSayi);
        break;
    default:
        cout << "Hatali tuslama yaptiniz." << endl;
    }
    return 0;
}