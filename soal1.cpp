#include<iostream>
#include<vector>
#include<fstream>
#include<iomanip>
#define vi vector<int>

using namespace std;

void merge(vi &data,int bawah, int tengah, int atas);

void mergeSort(vi &data,int bawah, int atas)
{
    //pisah jadi kiri dan kanan, sort masing masing secara rekursif, lalu digabung dengan fungsi merge
    //Cara pakai : mergeSort(vectornya, index bawah sorting, index akhir sorting)
    if(bawah<atas)
    {
      int tengah = (bawah+atas)/2;
      mergeSort(data,bawah,tengah);
      mergeSort(data,tengah+1,atas);
      merge(data,bawah,tengah,atas);
    }
}

void merge(vi &data,int bawah, int tengah, int atas)
{
    //helper function untuk mergeSort yang berguna untuk menggabungkan 2 vector

    //buat vector temporary untuk ngemerge kedua bagian tersebut
    vi kiri, kanan;
    for(int i=bawah;i<=tengah;i++)
    {
      kiri.push_back(data[i]);
    }
    for(int i=tengah+1;i<=atas;i++)
    {
      kanan.push_back(data[i]);
    }
    //kiri berisi data dari bawah s/d tengah, kanan berisi data dari tengah+1 s/d atas
    //mulai gabungkan hingga salah satu vector habis
    while(kiri.size()>0 && kanan.size()>0)
    {
      /*cara kerja : mengecek nilai paling depan di kedua vector, lalu menginput yang paling kecil ke data,
       kemudian data terkecil tersebut dihapus dari vector asalnya*/
      if(kiri[0]<=kanan[0])
      {
        data[bawah] = kiri[0];
        kiri.erase(kiri.begin()); //hapus elemen paling depan di vector kiri
      }else{
        data[bawah] = kanan[0];
        kanan.erase(kanan.begin()); //hapus elemen paling depan di vector kanan
      }
      bawah++; //memanfaatkan variable bawah sebagai iterator index vector untuk memasukan hasil yang benar ke data
    }
    //habiskan sisa vectornya
    while(kiri.size()>0)
    {
      data[bawah] = kiri[0];
      bawah++; kiri.erase(kiri.begin());
    }
    while(kanan.size()>0)
    {
      data[bawah] = kanan[0];
      bawah++; kanan.erase(kanan.begin());
    }
    //Selesai merge, tidak usah free memori bekas vector kiri kanan karena sudah automatis terhapus memorinya
}

float median(vi &data)
{
  //jika data genap, ambil nilai rata rata dari floor(tengah) dan ceil(tengah), jika ganjil langsung ambil nilai tengahnya
  if(data.size()>0){
    int tengah = data.size()/2;
    if(data.size() % 2 == 0)
    {
      return (data[tengah-1]+data[tengah])/2.0; //tengah-1 karena index vector mulai dari 0
    }else{
      return data[tengah];
    }
  }else{
    //Tidak Valid
    cout<<"Data Kosong";
    return -1;
  }
}

int modus(vi &data)
{
  int curModus, banyak, tempModus, tempBanyak,i;
  banyak = 0;i = 0;
  /* asumsi vector sudah terurut maka tinggal iterasi setiap elemen, hitung banyak muncul elemen tersebut,
  lalu bandingkan dengan modus yang ada, jika lebih besar, modus berubah menjadi banyak elemen tersebut */
  while(i<data.size()){
    tempModus = data[i];i++;
    tempBanyak = 0;

    //menghitung banyak kemunculan elemen tersebut dengan looping hingga ketemu elemen yang beda
    while(data[i]==tempModus)
    {
      tempBanyak++; //naikan nilai tempBanyak selama elemennya masih sama
      i++;
    }//stop condition : elemennya sudah beda

    //bandingkan dengan modus sebelumnya
    if(tempBanyak>banyak)
    {
      banyak = tempBanyak;
      curModus = tempModus;
    }
  }
  return curModus;
}

int main(){
      vi data;
      int temp,banyak;
      float sum;
      sum = 0;banyak=0;

      //Baca data dari file
      ifstream fileInput ("input1.txt");
      while(not(fileInput.eof())){
        fileInput >> hex >> temp;        //menggunakkan hex dari iostream untuk konversi
        data.push_back(temp);  //menyimpan ke vector data, menggunakkan vector karena banyak data tidak pasti
        sum += temp;
        banyak += 1;
      }
      fileInput.close();

      //urutkan data agar gampang menghitung median dan modus
      mergeSort(data,0,banyak-1);
      //Hitung rata rata
      float rataRata = sum / banyak;
      cout<<"Mean   : "<<rataRata<<endl;
      //output median dan modus
      cout<<"Median : "<<median(data)<<endl;
      cout<<"Modus  : "<<modus(data)<<endl;

      return 0;
}
