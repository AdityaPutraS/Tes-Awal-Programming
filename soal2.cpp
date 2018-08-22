#include<iostream>
#include<vector>
#include<fstream>
#define vli vector<long long int>

using namespace std;

double normalisasi(double x, long long int fromLimLow, long long int fromLimHigh)
{
  //Asumsi : x berada diantara fromLimLow s/d fromLimHigh
  //Fungsi untuk mapping nilai x yang berada diantara fromLimLow s/d fromLimHigh ke range 0 s/d 360
  return ( (x-fromLimLow)/(fromLimHigh-fromLimLow) * 360);
}

double dataToDerajat(long long int i,int n)
{
  //Fungsi untuk mengubah data ke derajat(0-360) dengan data ukurannya sebanyak n-bit
  double derajat = normalisasi(i,0,( 1LL << n)-1); //type casting 1 jadi 1 long long agar bisa dishift lebih dari 31
  if(derajat==360){
    return 0;
  }else{
    return derajat;
  }
}

string arah(double derajat)
{
  //asumsi derajat selalu valid (0-360)
  if(derajat==0)
  {
    return "Timur";
  }
  else if(derajat<90)
  {
    return "Timur Laut";
  }
  else if(derajat==90)
  {
    return "Utara";
  }
  else if(derajat<180)
  {
    return "Barat Laut";
  }
  else if(derajat==180)
  {
    return "Barat";
  }
  else if(derajat<270)
  {
    return "Barat Daya";
  }
  else if(derajat==270)
  {
    return "Selatan";
  }
  else if(derajat<360)
  {
    return "Tenggara";
  }
}
int main()
{
  //pilih mode
  int mode;
  cout<<"Pilih mode data (16/32)-bit : ";
  cin>>mode;
  //Validasi mode
  while(mode !=16 && mode !=32)
  {
    cout<<"Mode salah, pilih 16 atau 32 : ";
    cin>>mode;
  }
  //sudah validasi
  //baca file dan masukan ke vector
  long long int temp; vli data;
  ifstream fileInput ("input2.txt");
  while(not(fileInput.eof())){
    fileInput >> temp;        //menggunakkan hex dari iostream untuk konversi
    data.push_back(temp);  //menyimpan ke vector data, menggunakkan vector karena banyak data tidak pasti
  }
  fileInput.close();

  //output ke console sesuai Mode
  cout<<endl<<"Data mode "<<mode<<"-bit\n\n";
  for(long long int i : data)
  {
    //validasi data
    if(mode==16 && i > 65535){
      cout<<i<<" diluar batas 16-bit"<<endl;
    }
    else if(mode==32 && i > 4294967295){
      cout<<i<<" diluar batas 32-bit"<<endl;
    }else{
    //data valid
    double derajat = dataToDerajat(i,mode);
    cout<<i<<" = "<<derajat<<" Derajat, Arah = "<<arah(derajat)<<endl;
    }
  }

  return 0;
}
