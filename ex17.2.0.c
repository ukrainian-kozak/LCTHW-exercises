#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <assert.h>





//Sort begin


void swap (char **a, char **b)
{
    char *temp = *a;
    *a = *b;
    *b = temp;
}

int partition(char **arr, int low, int high)
{
    char *pivot = arr[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; ++j) {
        if (strcmp(arr[j], pivot) <= 0) {
            ++i;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

void quicksort(char **arr, int low, int high) 
{
    if (low <= high) {
        int pi = partition(arr, low, high);

        quicksort(arr, low, pi - 1);
        quicksort(arr, pi + 1, high);
    }
}

//Sort end 











struct Address {
    int id;
    int set;
    char* name;
    char* email;
};

struct Database {
    int max_rows;
    int max_data;
    struct Address **rows;
};

struct Connection {
    FILE* file;
    struct Database *db;
};

void Database_close(struct Connection *conn);

void die(const char* message, struct Connection *conn)
{
    Database_close(conn);
    if (errno) {
        perror(message);
    } else {
        printf("ERROR: %s", message);
    }

    exit(1);
}

void Database_load(struct Connection *conn) 
{
    int rc = fread(&conn->db->max_rows, sizeof(int), 1, conn->file);
    if (rc != 1)
        die("Failed to load", conn);
    
    rc = fread(&conn->db->max_data, sizeof(int), 1, conn->file);
    if (rc != 1)
        die("Failed to load max_data", conn);

    conn->db->rows = malloc(conn->db->max_rows * sizeof(struct Address*));

    for (int i = 0; i < conn->db->max_rows; ++i) {
        struct Address *addr = malloc(sizeof(struct Address));
        rc = fread(&(addr->id), sizeof(int), 1, conn->file);
        if (rc != 1)
            die("Failed to load address->id", conn);

        rc = fread(&(addr->set), sizeof(int), 1, conn->file);
        if (rc != 1)
            die("Failed to load address->set", conn);

        addr->name = malloc(conn->db->max_data * sizeof(char));
        addr->email = malloc(conn->db->max_data * sizeof(char));

        rc = fread(addr->name, sizeof(char), conn->db->max_data, conn->file);
        if (rc != conn->db->max_data)
            die("Filed to load address->name", conn);

        rc = fread(addr->email, sizeof(char), conn->db->max_data, conn->file);
        if (rc != conn->db->max_data)
            die("Filed to load address->email", conn);

        conn->db->rows[i] = addr;
    }
}

struct Connection *Database_open(const char* filename, const char action)
{
    struct Connection *conn = malloc(sizeof(struct Connection));
    if (!conn) {
        die("Memory error", NULL);
    }

    conn->db = malloc(sizeof(struct Database));
    if (!conn->db) {
        die("Memory error", conn);
    }
    
    if (action == 'c') {   
        conn->file = fopen(filename, "w");
    } else {
        conn->file = fopen(filename, "r+");

        if (conn->file) {
            Database_load(conn);
        }
    }

    if (!conn->file) {
        die("Failed to open the file", conn);
    }

    return conn;
}

void Database_create(struct Connection *conn, const int max_rows, const int max_data)
{
    int i = 0;

    conn->db->max_rows = max_rows;
    conn->db->max_data = max_data;
    conn->db->rows = malloc(max_rows * sizeof(struct Address));

    for (i = 0; i < conn->db->max_rows; ++i) {
        struct Address *addr = malloc(sizeof(struct Address*));

        addr->id = i;
        addr->set = 0;
        addr->name = malloc(max_data * sizeof(char));
        addr->email = malloc(max_data * sizeof(char));
        
        memset(addr->name, 0, max_data * sizeof(char));
        memset(addr->email, 0, max_data * sizeof(char));
        memset(addr->name, '-', max_data * sizeof(char) - 1);
        memset(addr->email, '_', max_data * sizeof(char) - 1);

        conn->db->rows[i] = addr;
    }
}

void Database_set(struct Connection *conn, const int id, 
        const char *name, const char *email)
{
    struct Address *addr = conn->db->rows[id];

    if (addr->set)
        die("First of all delete the data from the row", conn);
    
    addr->set = 1;

    char* res = strncpy(addr->name, name, conn->db->max_data - 1);
    if (!res)
        die("Bad strcpy!", conn);
    addr->name[conn->db->max_data - 1] = '\0';
    res = strncpy(addr->email, email, conn->db->max_data - 1);
    if (!res)
        die("Bad strcpy!", conn);
    addr->email[conn->db->max_data - 1] = '\0';
}

void Database_write(struct Connection *conn) 
{
    rewind(conn->file);

    int rc;
    
    rc = fwrite(&conn->db->max_rows, sizeof(conn->db->max_rows), 1, conn->file);
    if (rc != 1)
        die("Failed to write MAX_ROWS.", conn);

    rc = fwrite(&conn->db->max_data, sizeof(conn->db->max_data), 1, conn->file);
    if (rc != 1)
        die("Failed to write MAX_DATA.", conn);

    for (int i = 0; i < conn->db->max_rows; ++i) {
        struct Address *addr = conn->db->rows[i];

        rc = fwrite(&addr->id, sizeof(addr->id), 1, conn->file);
        if (rc != 1)
            die("Failed to write address->id", conn);

        rc = fwrite(&addr->set, sizeof(addr->set), 1, conn->file);
        if (rc != 1)
            die("Failed to write addr->set", conn);

        rc = fwrite(addr->name, sizeof(char), conn->db->max_data, conn->file);
        if (rc != conn->db->max_data)
            die("Failed to write addr->name", conn);

        rc = fwrite(addr->email, sizeof(char), conn->db->max_data, conn->file);
        if (rc != conn->db->max_data)
            die("Failed to write addr->email", conn);

    }

    rc = fflush(conn->file);
    if (rc == -1)
        die("Cannot flush database.", conn);

}

void Address_print(struct Address *addr)
{
    printf("%d %s %s\n", addr->id, addr->name, addr->email);
}

void Database_get(struct Connection *conn, const int id)
{
    struct Address *addr = conn->db->rows[id];

    if (addr->set) {
        Address_print(addr);
    } else {
        die("ID is not set", conn);
    }
}

void Database_find(struct Connection *conn, const char *str)
{
    int i = 0;

    for (i = 0; i < conn->db->max_rows; ++i) {
        struct Address *addr = conn->db->rows[i];

        if (strcmp(addr->name, str) == 0) {
            Database_get(conn, addr->id);
        } else if (strcmp(addr->email, str) == 0) {
            Database_get(conn, addr->id);
        }
    }
}

void Database_delete(struct Connection *conn, const int id)
{
    struct Address *addr = conn->db->rows[id];
    addr->set = 0;
}

void Database_list(struct Connection *conn, const char mode)
{
    int i = 0;
    struct Database *db = conn->db;
    
    if (mode == 's') {
        char** names = malloc(db->max_rows * sizeof(char*));
        if (!names)
            die("Memory error", conn);

        for (i = 0; i < db->max_rows; ++i) {
            struct Address *cur = db->rows[i];

            if (cur->set) {
                names[i] = cur->name;
            } else {
                names[i] = "~~~";
            }
        }

        quicksort(names, 0, db->max_rows - 1);

        for (i = 0; i < db->max_rows; ++i) {
            if (db->rows[i]->set) {
                Database_find(conn, names[i]);
            }
        }

        free(names);
    } else {
        for (i = 0; i < db->max_rows; ++i) {
            struct Address *addr = db->rows[i];
            
            if (addr->set) {
                Address_print(addr);
            }
        }
    }
}

void Database_redact(struct Connection *conn, const int id)
{
    Database_get(conn, id);

    struct Address addr;

    addr.name = malloc(conn->db->max_data);
    if (!addr.name)
        die("Memory error", conn);

    addr.email = malloc(conn->db->max_data);
    if (!addr.email)
        die("Memory error", conn);

    addr.id = id; 

    printf("Enter your new name: ");

    fgets(addr.name, conn->db->max_data, stdin);
    addr.name[strlen(addr.name) - 1] = '\0';
    int rc = fflush(stdin);
    if (rc == -1)
        die("Flush was failed", conn);

    printf("\nEnter your new email: ");

    fgets(addr.email, conn->db->max_data, stdin);
    addr.email[strlen(addr.email) - 1] = '\0';
    rc = fflush(stdin);
    if (rc == -1)
        die("Flsuh was failed", conn);

    char* res = strncpy(conn->db->rows[id]->name, addr.name, conn->db->max_data - 1);
    if (!res)
        die("Memory wrong", conn);
    conn->db->rows[id]->name[conn->db->max_data - 1] = '\0';

    res = strncpy(conn->db->rows[id]->email, addr.email, conn->db->max_data - 1);
    if (!res)
        die("Memory wrong", conn);
    conn->db->rows[id]->email[conn->db->max_data - 1] = '\0';
}

void Database_copy(struct Connection *conn, const char *filename, 
        const int max_rows, const int max_data) 
{
    struct Connection *new_conn = Database_open(filename, 'c');


    Database_create(new_conn, max_rows, max_data);

    int size = 0;
    if (max_rows >= conn->db->max_rows) {
        size = conn->db->max_rows;
    } else {
        size = max_rows;
    }
 
    int i = 0;

    for (i = 0; i < size; ++i) {
        struct Address *addr = conn->db->rows[i];
        struct Address *new_addr = new_conn->db->rows[i];
        if (addr->set) {
            new_addr->id = addr->id;
            new_addr->set = 1;
            char* res = strncpy(new_addr->name, addr->name, max_data - 1);
            if (!res)
                die("Failed to copy new_addr->name", conn);
            new_addr->name[max_data - 1] = '\0'; 
            res = strncpy(new_addr->email, addr->email, max_data - 1);
            if (!res)
                die("Failed to copy new_addr->email", conn);
            new_addr->email[max_data - 1] = '\0';
        }
        new_conn->db->rows[i] = new_addr;
    }

    Database_write(new_conn);
}

void Database_close(struct Connection *conn)
{
    if(conn) {
        if (conn->db) {
            if (conn->db->rows) {
                int i = 0;
                for (i = 0; i < conn->db->max_rows; ++i) {
                    if (conn->db->rows[i]) {
                        free(conn->db->rows[i]->name);
                        free(conn->db->rows[i]->email);
                        free(conn->db->rows[i]);
                    }
                }
                free(conn->db->rows);
            }
            free(conn->db);
        }
        if (conn->file)
            fclose(conn->file);

        free(conn);
    }
}


int main(int argc, char* argv[]) 
{
    if (argc < 3) {
        die("USING:./a.out <dbfile> <action> [parametrs]", NULL);
    }

    char* filename = argv[1];
    char action = argv[2][0];
    struct Connection *conn = Database_open(filename, action);
    int id = 0; 
    //int max_rows = atoi(argv[2]);
    //int max_data = atoi(argv[3]);

    if (action != 'c') {
        if (argc > 3)
            id = atoi(argv[3]);
    }
    
    switch (action) {
        case 'c':
            int max_rows = atoi(argv[3]);
            int max_data = atoi(argv[4]);
            Database_create(conn, max_rows, max_data);
            Database_write(conn);
            break;

        case 'g':
            if (argc != 4)
                die("Need id to get", conn);
            Database_get(conn, id);
            break;

        case 's':
            if (argc != 6) 
                die("Need some arguments", conn);
            Database_set(conn, id, argv[4], argv[5]);
            Database_write(conn);
            break;

        case 'd':
            if (argc != 4)
                die("Need some arguments", conn);
            Database_delete(conn, id);
            Database_write(conn);
            break;

        case 'l':
            if (argc < 3)
                die("Need some arguments", conn);
            char mode = (argc == 4) ? argv[3][0] : '\0';
            Database_list(conn, mode);
            break;

        case 'f':
            if (argc != 4)
                die("Arguments are wrong", conn);
            Database_find(conn, argv[3]);
            break;

        case 'r':
            if (argc != 4)
                die("Arguments are wrong", conn);
            Database_redact(conn, id);
            Database_write(conn);
            break;

        case 'y':
            if (argc != 6)
                die("Arguments are wrong", conn);
            char* new_filename = argv[3];
            int rows = atoi(argv[4]);
            int data = atoi(argv[5]); 
            Database_copy(conn, new_filename, rows, data);
            break;
        
        default:
            die("Action is wrong!\nc=create, s=set, d=delete, g=get, l=list", conn);
    }

    Database_close(conn);

    return 0;
}
