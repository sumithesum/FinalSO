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

//exit
void function_exit()
{
    printf("La revedere!");
    exit(0);
}
