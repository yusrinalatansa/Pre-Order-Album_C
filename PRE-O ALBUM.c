#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//void
void seller();
void loginseller();
void berandaseller();
void addalbum();
void cutalbum();
void datapemesan();
void listalbumseller();
void pembayaran();
void buyer();
void addbuyer();
void loginbuyer();
void berandabuyer();
void keranjang();
void carialbum();
void payment();

//Kamus
struct{
    char nama[50], kontak[50], alamat[50], username[50], password[50];
}dataUser;
struct{
    char username[50], password[50], role[10];
}session_dataUser;
struct{
    char namaalbum[50],namapenyanyi[50],genre[50],deskripsi[50];
    int hargaalbum;
}dataalbum;
struct{
    char namaalbum[50],namapenyanyi[50],genre[50],deskripsi[50];
    int hargaalbum;
}dataalbum_list[50],temp;
struct{
    char usernameseller[50],usernamebuyer[50],namaalbum[50],namapenyanyi[50],genre[50],deskripsi[50];
    int hargaalbum,statuspembelian;
}buyingData;
struct{
 char usernameseller[50],usernamebuyer[50],namaalbum[50],namapenyanyi[50],genre[50],deskripsi[50];
 int hargaalbum,statuspembelian;
}buyingData_list;
int status_login,status_delete,status_buyingData;
char username[100],password[100];

//Main Program
int main(){
 int pilihan;
 system("cls");
 printf("\t\t\t === SELAMAT DATANG DI D'ALBUMS!===\n");
 printf("Masuk sebagai : \n");
 printf("[1] Seller\n[2] Buyer\n");
 printf("Pilih : ");
 scanf("%d",&pilihan); getchar();
 system("cls");
 switch(pilihan){
  case 1  : system("cls");seller();break;
  case 2  : system("cls");buyer();break;
  default : printf("\nTolong Pilih Angka dengan Benar!!\n\n");system("pause");system("cls");main();
 }
}

//Seller
void seller(){
 int pilihan;
 printf("1. Login\n2. Back\n");
 printf("Pilih Aksi : ");
 scanf("%d", &pilihan);getchar();
 switch(pilihan){
  case 1  : system("cls");loginseller();system("pause");system("cls");main();break;
  case 2  : system("cls");main();break;
  default : printf("\nTolong Pilih Angka dengan Benar!!\n\n");system("pause");system("cls");seller();
 }
}

void loginseller(){
 printf("Username\t: ");
 gets(dataUser.username);
 printf("Password\t: ");
 gets(dataUser.password);
 if(strcmp(dataUser.username,"admin")==0 && strcmp(dataUser.password,"admin")==0){
  status_login = 1;
 }
 if(status_login == 1){
  printf("\n==Login Success==\n\n");
  system("pause");
  system("cls");
  berandaseller();
  }else if(status_login == 0){
  printf("\n==Username or Password is invalid==");
  printf("\n\n");
  system("pause");
  system("cls");
  loginseller();
  }else{
  printf("\n==System Error==\n");
  exit(0);
 }
}

void berandaseller(){
 int pilihan;
 printf("==Menu Seller==\n");
 printf("1. Menambah daftar album yang dijual\n2. Mengurangi daftar album yang dijual\n3. Melihat data pemesan album\n4. Melihat list album yang dijual\n5. Logout\n");
 printf("Pilih Aksi : ");
 scanf("%d", &pilihan);getchar();
 switch(pilihan){
  case 1  : system("cls");addalbum();system("pause");system("cls");berandaseller();break;
  case 2  : system("cls");cutalbum();system("pause");system("cls");berandaseller();break;
  case 3  : system("cls");datapemesan();system("pause");system("cls");berandaseller();break;
  case 4  : system("cls");listalbumseller();system("pause");system("cls");berandaseller();break;
  case 5  : system("cls");main();break;
  default : printf("\nTolong Pilih Angka dengan Benar!!\n\n");system("pause");system("cls");berandaseller();
 }
}

void addalbum(){
 printf("==Menambah daftar album==\n");
    printf("Nama Album\t: ");
    gets(dataalbum.namaalbum);
    printf("Nama Penyanyi\t: ");
    gets(dataalbum.namapenyanyi);
    printf("Genre\t: ");
    gets(dataalbum.genre);
    printf("Harga\t\t: ");
    scanf("%d",&dataalbum.hargaalbum);getchar();
    printf("Deskripsi\t: ");
    gets(dataalbum.deskripsi);
    //===
    FILE *f_addalbum;
    f_addalbum = fopen("dataalbum.dat","ab");
    fwrite(&dataalbum,sizeof(dataalbum),1,f_addalbum);
    fclose(f_addalbum);
    system("pause");
 system("cls");
 berandaseller();
}

void cutalbum(){
 char target[50];
 listalbumseller();
 FILE *f_struktur;
 FILE *f_struktur_1;
 printf("Masukan nama album yang akan dihapus : ");
    gets(target);
    f_struktur=fopen("dataalbum.dat","rb");
    f_struktur_1=fopen("dataalbum_temp.dat","wb");
    status_delete = 0;
    while(fread(&dataalbum,sizeof(dataalbum),1,f_struktur)==1){
        if(strcmp(dataalbum.namaalbum,target)!=0){
            fwrite(&dataalbum,sizeof(dataalbum),1,f_struktur_1);
        }else{
         status_delete = 1;
  }
    }
    fclose(f_struktur);
    fclose(f_struktur_1);
    remove("dataalbum.dat");
    rename("dataalbum_temp.dat","dataalbum.dat");
    if(status_delete == 1){
     printf("\n==Data berhasil dihapus==\n");
 }else{
  printf("\n==Data tidak ditemukan==\n\n");
 }
}

void datapemesan(){
    FILE *f_getAccount;
    printf("==Data Pembelian==\n");
    int i=1;
    f_getAccount = fopen("datapembelian.dat","rb");
    while(fread(&buyingData,sizeof(buyingData),1,f_getAccount)==1){
        if(strcmp(buyingData.usernameseller,session_dataUser.username)==0 && strcmp(session_dataUser.role,"seller")==0 && buyingData.statuspembelian == 0){
            printf("%d. ",i);
            printf("   Seller \t: %s\n", buyingData.usernameseller);
            printf("   Buyer \t: %s\n", buyingData.usernamebuyer);
            printf("   Nama Album\t: %s\n", buyingData.namaalbum);
            printf("   Nama Penyanyi\t: %s\n", buyingData.namapenyanyi);
            printf("   Genre\t: %s\n", buyingData.genre);
            printf("   Harga\t: %d\n", buyingData.hargaalbum);
            printf("   Deskripsi\t: %s\n", buyingData.deskripsi);
            printf("   Status\t: %d\n", buyingData.statuspembelian);
            i++;
        }
    }
 fclose(f_getAccount);
}

void listalbumseller(){
FILE *f_getDataalbum;
 printf("==Data Album==\n");
    int n=0,i,j;
    f_getDataalbum = fopen("dataalbum.dat","rb");
    while(fread(&dataalbum,sizeof(dataalbum),1,f_getDataalbum)==1){
     strcpy(dataalbum_list[n].namaalbum,dataalbum.namaalbum);
     strcpy(dataalbum_list[n].namapenyanyi,dataalbum.namapenyanyi);
     strcpy(dataalbum_list[n].genre,dataalbum.genre);
     dataalbum_list[n].hargaalbum = dataalbum.hargaalbum;
     strcpy(dataalbum_list[n].deskripsi,dataalbum.deskripsi);
     n++;
    }
    fclose(f_getDataalbum);
 for (i = 0; i<n; i++){
     for (j = 0; j < n; j++){
         if (strcmp(dataalbum_list[j-1].namaalbum , dataalbum_list[j].namaalbum) >=0)
         {
             temp =dataalbum_list[j-1];
             dataalbum_list[j - 1] = dataalbum_list[j];
             dataalbum_list[j] = temp;
         }
     }
 }
 for (i = 0; i < n ; i++){
     printf("%d. Nama Album\t: %s\n",i+1, dataalbum_list[i].namaalbum);
     printf("   Nama Penyanyi: %s\n", dataalbum_list[i].namapenyanyi);
     printf("   Genre\t: %s\n", dataalbum_list[i].genre);
     printf("   Harga\t: %d\n", dataalbum_list[i].hargaalbum);
     printf("   Deskripsi\t: %s\n", dataalbum_list[i].deskripsi);
 }
}

void buyer(){
 int pilihan;
 printf("1. Login\n2. Register\n3. Back\n");
 printf("Pilih Aksi : ");
 scanf("%d", &pilihan);getchar();
 switch(pilihan){
  case 1  : system("cls");loginbuyer();system("pause");system("cls");main();break;
  case 2  : system("cls");addbuyer();system("pause");system("cls");buyer();break;
  case 3  : system("cls");main();break;
  default : printf("\nTolong Pilih Angka dengan Benar!!\n\n");system("pause");system("cls");seller();
 }
}

void addbuyer(){
 printf("====Tambah Buyer====\n");
 printf("Nama\t: ");
    gets(dataUser.nama);
    printf("Kontak\t: ");
    gets(dataUser.kontak);
    printf("Alamat Rumah\t: ");
    gets(dataUser.alamat);
    printf("Username\t: ");
    gets(dataUser.username);
    printf("Password\t: ");
    gets(dataUser.password);
    //=================
    FILE *f_addAccount;
    f_addAccount = fopen("dataUser.dat","ab");
    fwrite(&dataUser,sizeof(dataUser),1,f_addAccount);
    fclose(f_addAccount);
    //=================
}

void loginbuyer(){
 int percobaan_buyer = 3;
 char username[50],password[50];
 back:
 if(percobaan_buyer == 0){
  system("cls");
  main();
 }
    printf("Kesempatan Login : %d\n",percobaan_buyer);
    printf("====Login Buyer====\n");
    printf("Username\t: ");
    gets(username);
    printf("Password\t: ");
    gets(password);
    //==================
    FILE *f_getAccount;
    f_getAccount = fopen("dataUser.dat","rb");
    while(fread(&dataUser,sizeof(dataUser),1,f_getAccount)==1){
     if(strcmp(username,dataUser.username)==0 && strcmp(password,dataUser.password)==0){
      status_login = 1;
      strcpy(session_dataUser.username,dataUser.username);
      strcpy(session_dataUser.password,dataUser.password);
   break;
  }else{
   status_login = 0;
  }
    }
    fclose(f_getAccount);
    //printf("status_login : %d\n",status_login);
    if(status_login == 1){
     printf("\n====Login Success====\n\n");
     system("pause");
  system("cls");
     berandabuyer();

 }else if(status_login == 0){
  printf("\n====Username or Password is invalid====");
  printf("\n\n");
  percobaan_buyer--;
  system("pause");
  system("cls");
  goto back;
 }else{
  printf("\n====System Error====\n");
  main();
 }
}
void berandabuyer(){
 system("cls");
 int pilihan;
 printf("==Menu Buyer==\n");
 printf("1. List Album\n2. Cari Album\n3. Keranjang\n4. Pembayaran\n5. Logout\n");
 printf("Pilih Aksi : ");
 scanf("%d", &pilihan);getchar();
 system("cls");
 switch(pilihan){
  case 1  : listalbumseller();system("pause");berandabuyer();
  case 2  : carialbum();system("pause");berandabuyer();
  case 3  : keranjang();system("pause");berandabuyer();
  case 4  : pembayaran();system("pause");berandabuyer();
  case 5  : main();break;
  default : printf("\nTolong Pilih Angka dengan Benar!!\n\n");system("pause");system("cls");berandabuyer();
 }
}

void carialbum(){
	FILE *f_getDataalbum;
    int n=0,i,j, cari;
    printf("Cari album yang ingin dibeli berdasarkan genre: ");
 	scanf("%d", &dataalbum_list[n].genre);
    f_getDataalbum = fopen("dataalbum.dat","rb");
    while(fread(&dataalbum,sizeof(dataalbum),1,f_getDataalbum)==1){
        strcpy(dataalbum_list[n].namaalbum,dataalbum.namaalbum);
        strcpy(dataalbum_list[n].namapenyanyi,dataalbum.namapenyanyi);
        strcpy(dataalbum_list[n].genre,dataalbum.genre);
        dataalbum_list[n].hargaalbum = dataalbum.hargaalbum;
        strcpy(dataalbum_list[n].deskripsi,dataalbum.deskripsi);
        n++;
    }
    fclose(f_getDataalbum);
    for (i = 0; i<n; i++){
     for (j = 0; j < n; j++){
         if (strcmp(dataalbum_list[j-1].genre , dataalbum_list[j].genre) >=0)
         {
             temp=dataalbum_list[j];
             dataalbum_list[j - 1] = dataalbum_list[n];
             dataalbum_list[j] = temp;
         }
     }
 }
 for (i = 0; i < n ; i++){
     printf("%d. Nama Album\t: %s\n",i+1, dataalbum_list[i].namaalbum);
     printf("   Nama Penyanyi\t: %s\n", dataalbum_list[i].namapenyanyi);
     printf("   Genre\t: %s\n", dataalbum_list[i].genre);
     printf("   Harga\t: %d\n", dataalbum_list[i].hargaalbum);
     printf("   Deskripsi\t: %s\n", dataalbum_list[i].deskripsi);
 }
}

void keranjang(){
	FILE *f_getDataalbum;
	printf("==Keranjang==\n");
	char target[50];
    int buyStok;
    printf("Nama album yang ingin di beli : ");
    gets(target);
    f_getDataalbum = fopen("dataalbum.dat","rb");
    status_buyingData = 0;
    while(fread(&dataalbum,sizeof(dataalbum),1,f_getDataalbum)==1){
    	if(strcmp(dataalbum.namaalbum,target)==0){
	    	strcpy(buyingData.namaalbum,dataalbum.namaalbum);
	    	buyingData.hargaalbum = dataalbum.hargaalbum;
            strcpy(buyingData.usernamebuyer, session_dataUser.username);
	    	status_buyingData = 1;
	    	break;
		}
    }
}

void pembayaran(){
    //List
    printf("==Pembayaran==\n");
	FILE *f_getAccount;
    FILE *f_getTemp;
    int i=1;
    f_getAccount = fopen("datapembelian.dat","rb");
    while(fread(&buyingData,sizeof(buyingData),1,f_getAccount)==1){
    	if(strcmp(session_dataUser.username,buyingData.usernamebuyer)==0 ){
	        printf("   Penjual \t: %s\n", buyingData.usernameseller);
	        printf("   Pembeli \t: %s\n", buyingData.usernamebuyer);
	        printf("   Nama Album\t: %s\n", buyingData.namaalbum);
            printf("   Nama Penyanyi\t: %s\n", buyingData.namapenyanyi);
            printf("   Genre\t: %s\n", buyingData.genre);
            printf("   Harga\t: %d\n", buyingData.hargaalbum);
        	printf("   Deskripsi\t: %s\n", buyingData.deskripsi);
			if(buyingData.statuspembelian == 0){
	        	printf("   Status\t: Proses Pembelian \n",buyingData.statuspembelian);
			}else if(buyingData.statuspembelian == 1){
	        	printf("   Status\t: Pembelian Berhasil\n",buyingData.statuspembelian);
			}else if(buyingData.statuspembelian == 2){
	        	printf("   Status\t: Proses Refund \n",buyingData.statuspembelian);
			}else if(buyingData.statuspembelian == 3){
	        	printf("   Status\t: Refund Berhasil\n",buyingData.statuspembelian);
			}else{
				printf("   Status\t: Error \n",buyingData.statuspembelian);
			}
			printf("\n");
	        i++;
		}
    }
    fclose(f_getAccount);

    //Pilih Album
    char pilihanAlbum[50];
    char bayar;
    printf("Album yang ingin dibayar : "); gets(pilihanAlbum);
    f_getAccount = fopen("datapembelian.dat","rb");
    f_getTemp = fopen("temp.dat","wb");
    while(fread(&buyingData,sizeof(buyingData),1,f_getAccount)==1){
        if(strcmp(pilihanAlbum,buyingData.namaalbum)==0 && strcmp(session_dataUser.username,buyingData.usernamebuyer)==0 && buyingData.statuspembelian == 0){
            printf("Pesanan ditemukan!\n"
                    "Apakah sudah anda bayar?(y/n)\n");
            scanf("%c", &bayar); getchar();
            if(bayar=='y' || bayar=='Y'){
                printf("Pembayaran diterima\n");
                buyingData.statuspembelian=1;
                fwrite(&buyingData,sizeof(buyingData),1,f_getAccount);
            }
            else {
                printf("Pembayaran gagal!");
                fclose(f_getAccount); fclose(f_getTemp);
                break;
            }
        }
        else{
            fwrite(&buyingData,sizeof(buyingData),1,f_getAccount);
        }
    }
    fclose(f_getAccount); fclose(f_getTemp);
    remove("datapembelian.dat"); rename("temp.dat", "datapembelian.dat");
}
