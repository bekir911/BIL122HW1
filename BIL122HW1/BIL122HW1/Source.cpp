//Bekir �zt�rk
//19120205061 16.02.2020
//BIL 122 �dev-1

//Bu tip gerekli �eyleri belirtmeme gerek yoktur umar�m
#include <iostream>

using namespace std;

//Fonksiyona sadece al�nan say� g�nderilece�i i�in hatal� giri�i tutan de�i�keni global olarak tan�mlad�m ve ilklendirdim
int hataliGiris = 0;

//D�z ��gen bast�ran fonksiyon
//Ba�ta fonksiyona gelen de�erin kriterlere uyup uymad��� if statemant ile kontrol ediliyor
//Uygunsa d�ng�ler i�in de�i�kenler ve bu de�i�kenlere uygun de�erler atan�yor
//D��taki d�ng� sat�r� kontrol ederken i�teki sat�r� kontrol ediyor

//Kriterlere uygun de�ilse 3 kereye kadar tekrar de�er talep ediyor
//Girilen de�er ile fonksiyon kendisini �a��r�yor
//Hatal� giri� say�s� 3 oldu�unda kullan�c� hakk�n� kaybediyor ve program sonlan�yor

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

//D�z ��genden �ok da farkl� de�il. For yerine while kullan�lm�� hali desek yeridir
//Asl�nda belirtmeseniz ilkinde sat�r i�in while kullan�rd�m
//Di�erindeki gibi �nce bo�luklar sonra y�ld�zlar bas�l�yor. Tek fark� ka� adet bas�ld�klar�
//Hatal� giri� muhabbeti burada da mevcut

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

//Kriterleri di�erlerine g�re biraz daha farkl� olsa da di�er fonksiyonlar� �a��rmaktan ba�ka pek bir �ey yapm�yor
//Hatal� giri�e �ok tolerans g�sterdi�i s�ylenemez

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

//Kullan�c�n�n �ekil ve o �eklin boyutunu se�mesini sa�l�yor. Buna uygun fonksiyonlar� �a��r�yor
//Kullan�c� s�f�r girdi�inde direkt ��kmas� gerekti�ini d���nd���m i�in pek ho� durmad� kod
//Switch i�ine konabilirdi, ya da de�erler fonksiyon i�erisinde al�nabilirdi
//�devden anlad���m kadar�yla fonksiyonda boyut se�me olmamal�yd� o y�zden b�yle yapt�m.

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