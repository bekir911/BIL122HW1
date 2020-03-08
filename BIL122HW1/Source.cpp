//Bekir Öztürk
//19120205061 16.02.2020
//BIL 122 Ödev-1
//Örnek bir yorumlama ya da değişken adı vermeyi öğretmediğiniz için ben böyle yapıyorum.
//20-25 değişkene a, b ve ab benzeri isimler vermem rağmen hiçbirini şu ana kadar kodu yazarken karıştırmadım.
//Yine de olabildiğince mantıklı, anlaşılır değişken adları vermeye çalıştım.

//Bu tip gerekli şeyleri belirtmeme gerek yoktur umarım
#include <iostream>

using namespace std;

//Fonksiyona sadece alınan sayı gönderileceği için hatalı girişi tutan değişkeni global olarak tanımladım ve ilklendirdim
int hataliGiris=0;

//Düz üçgen bastıran fonksiyon
//Başta fonksiyona gelen değerin kriterlere uyup uymadığı if statemant ile kontrol ediliyor
//Uygunsa döngüler için değişkenler ve bu değişkenlere uygun değerler atanıyor
//Dıştaki döngü satırı kontrol ederken içteki satırı kontrol ediyor

//Kriterlere uygun değilse 3 kereye kadar tekrar değer talep ediyor
//Girilen değer ile fonksiyon kendisini çağırıyor
//Hatalı giriş sayısı 3 olduğunda kullanıcı hakkını kaybediyor ve program sonlanıyor
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

//Düz üçgenden çok da farklı değil. For yerine while kullanılmış hali desek yeridir
//Aslında belirtmeseniz ilkinde satır için while kullanırdım
//Diğerindeki gibi önce boşluklar sonra yıldızlar basılıyor. Tek farkı kaç adet basıldıkları
//Hatalı giriş muhabbeti burada da mevcut
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

//Kriterleri diğerlerine göre biraz daha farklı olsa da diğer fonksiyonları çağırmaktan başka pek bir şey yapmıyor
//Hatalı girişe çok tolerans gösterdiği söylenemez
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

//Kullanıcının şekil ve o şeklin boyutunu seçmesini sağlıyor. Buna uygun fonksiyonları çağırıyor
//Kullanıcı sıfır girdiğinde direkt çıkması gerektiğini düşündüğüm için pek hoş durmadı kod
//Switch içine konabilirdi, ya da değerler fonksiyon içerisinde alınabilirdi
//Ödevden anladığım kadarıyla fonksiyonda boyut seçme olmamalıydı o yüzden böyle yaptım.
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
    case 3 :
        elmas(alinanSayi);
        break;
    default:
        cout << "Hatali tuslama yaptiniz." << endl;
    }
    return 0;
}
