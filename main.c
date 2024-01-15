#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <wait.h>

#define clear() printf("\033[H\033[J")

void start(){


clear();
printf("Bine ati venit la Dropbox! \n");
char * username = getenv("USER");
printf("\n Bine ai venit %s \n",username);


sleep(2);
clear();

}


// functie pentru a separata cuvintele din comanda
void sep_comanda(char * comanda, char ** comanda_separata) {
    int i;

    for (i = 0; i < 100; i++) {
        comanda_separata[i] = strsep( & comanda, " ");

        if (comanda_separata[i] == NULL)
            break;
        if (strlen(comanda_separata[i]) == 0)
            i--;
    }
}

bool process_comanda(char * comanda, char ** comanda_separata) {


    sep_comanda(comanda, comanda_separata);

    if (own_comanda(comanda_separata))
        return false;
    else
        return true;
}

bool input(char * str) {
    char * buf;

    buf = readline("\n>>> ");
	
    if (strlen(buf) != 0) {
        add_history(buf);
        strcpy(str, buf);
        return false;
    } else {
        return true;
    }
}


// change directory 
void function_cd(char ** dir){
	if(dir[1]==NULL)
	{
		printf("Nu ai specificat calea. Te rog repete comanda.");
	}
	else {
		int change_cd=chdir(dir[1]); // fucntie folosita pentru a schimba directorul
		if(change_cd==0)
			printf("Am schimbat directorul de lucru la: %s\n", dir[1]);
		else
			perror("Eroare cd!");
	}
}

//make directory
void function_mkdir(char ** name) {
    if (mkdir(name[1], 0777) == 0) // fucntie folosita pentru a crea un nou director cu toate drepturile
	{
        printf("Directorul %s  a fost creat cu succes!\n", name[1]);
    }
	else perror("Eroare mkdir");
}	

// remove a file
void function_rm(char ** name) {
    if (remove(name[1]) == 0) 
	{
        printf("Fișierul %s a fost șters cu succes.\n", name);
    } 
	else 
	{
        perror("Eroare la ștergerea fișierului");
    }
}

//remove a directory
void function_rmdir(char ** dir) {
    if (rmdir(dir[1]) == 0) 
	{
        printf("Directorul %s a fost șters cu succes.\n", dir[1]);
    } 
	else 
	{
        perror("Eroare la ștergerea directorului");
    }
}

//lists all the files and directories under a specified directory
//#include <dirent.h>
void function_ls(char ** cale) {
	DIR *director;
	struct dirent *el;
	director = opendir(cale[1]);
	if(director == NULL)
	{
		perror("Eroare la deschiderea directorului");
		return;
	}
	printf("Fisiere si directoare din %s:\n", cale[1]);
    while ((element = readdir(director)) != NULL) {
        printf("%s\n", element->d_name);
    }
	closedir(director);
}
	
//copy of a file
void function_cp(char *source, char *destination) {
    int f1 = open(source, O_RDONLY);
    if (f1 == -1) {
        perror("Eroare la deschiderea fisierului sursa");
        return;
    }

    int f2 = open(destination, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (f2 == -1) {
        perror("Eroare la deschiderea fisierului destinatie");
        close(f1);
        return;
    }

    const int BUFF_SIZE = 1024;
    char buffer[BUFF_SIZE];

    ssize_t bytesRead, bytesWritten;

    while ((bytesRead = read(f1, buffer, BUFF_SIZE)) > 0) {
        bytesWritten = write(f2, buffer, bytesRead);
        if (bytesWritten != bytesRead) {
            perror("Eroare la scrierea in fisierul destinatie");
            break;
        }
    }

    if (bytesRead == -1) {
        perror("Eroare la citirea din fisierul sursa");
    }

    close(f1);
    close(f2);
}

//move a file 
void fucntion_mv(char  *source, char *destination) {
	function_cp(source,destination);
	function_rm(source);
}

//touch 
void function_touch(char * name)
{
    open(name,O_CREAT | S_IRUSR | S_IWUSR);
}



void meniu(){

printf("Acestea sunt comenzile disponibile!\n");
printf("1.EXIT\n");
printf("2.CD\n");
printf("3.MKDIR\n");
printf("4.RM_DIR\n");
printf("5.RM\n")'
printf("6.LS\n");
printf("7.CP\n");
printf("8.MV\n");
printf("9.TOUCH\n")

char comanda_neseparata[1000],comanda_separata[1000][1000];
bool exit = false;

while(input(comanda_neseparata[1000]) && !exit){

if(process_comanda(comanda_neseparata[1000],comanda_separata[1000][1000])) continue;
else exit = true;;



if (strcmp(comanda_separata[0],"exit") ==0) {
	printf("La revedere!");
	exit = true;
}
else 
	printf("%s   ,   %s",coamda_separata[0],comanda_separata[1])
else if (strcmp(comanda_separata[0],"cd") ==0) 
	;
else if (strcmp(comanda_separata[0],"mkdir") ==0) 
	;
else if (strcmp(comanda_separata[0],"rm_dir") ==0 || strcmp(comanda_separata[0],"rmdir") ==0 ) 
	;
else if (strcmp(comanda_separata[0],"rm") ==0) 
	;
else if (strcmp(comanda_separata[0],"ls") ==0) 
	;
else if (strcmp(comanda_separata[0],"cp") ==0) 
	;
else if (strcmp(comanda_separata[0],"mv") ==0) 
	;
else if (strcmp(comanda_separata[0],"touch") ==0) 
	;
else printf("Aceasta comanda nu este definita");
}
return 0 ;
}

void citire

int main(){

start();
meniu();

return 0 ;
}