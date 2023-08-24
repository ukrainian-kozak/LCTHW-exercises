#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>


struct Address {
    int id;
    int set;
    char *name;
    char *email;
};

struct Database {
    size_t MAX_ROWS;
    size_t MAX_DATA;
    struct Address *rows;
};

struct Connection {
    FILE *file;
    struct Database *db;
};

void die(const char *message, struct Connection *conn) 
{
    if (errno) {
        perror(message);
    } else {
        printf("ERROR: %s\n", message);
    }

    if(conn) {
        if (conn->db) {
            if (conn->db->rows) {
                free(conn->db->rows);
            }
            free(conn->db);
        }
        free(conn);
    }

    exit(1);
}

void Database_destroy(struct Connection *conn) 
{
    if (conn) {
         if (conn->db) {
             if (conn->db->rows) {
                 for (int i = 0; i < conn->db->MAX_ROWS; ++i) {
                     if (conn->db->rows[i].name) {
                        free(conn->db->rows[i].name);
                     }
                     if (conn->db->rows[i].email) {
                        free(conn->db->rows[i].email);
                     }
                 }
             }
        }

    }
}

void Address_print(struct Address *addr)
{
    printf("%d %s %s\n", addr->id, addr->name, addr->email);
}

void Database_load(struct Connection *conn)
{
    int rc = fread(conn->db, sizeof(struct Database), 1, conn->file);
    if (rc != 1) {
        die("Failed to load database.", conn);
    }
    printf("Sizeof db: %ld\n", sizeof(conn->db));
}

struct Connection *Database_open(const char *filename, char mode) 
{
    struct Connection *conn = malloc(sizeof(struct Connection));
    if (!conn)
        die("Memory error", conn);

    conn->db = malloc(sizeof(struct Database));
    if (!conn->db)
        die("Memory error", conn);

    if (mode == 'c') {
        conn->file = fopen(filename, "w");
    } else {
        conn->file = fopen(filename, "r+");

        if (conn->file) {
            Database_load(conn);
        }
    }

    if (!conn->file)
        die("Failed to open the file", conn);
    
    return conn;
}

void Database_close(struct Connection *conn)
{
    if (conn) {
        if (conn->file)
            fclose(conn->file);
        if (conn->db) {
            if (conn->db->rows) {
                free(conn->db->rows);
            }
            free(conn->db); 
        }
        free(conn);
    }
}

void Database_write(struct Connection *conn) 
{
    rewind(conn->file);

    printf("Sizeof db: %ld\n", sizeof(conn->db));
    int rc = fwrite(conn->db, sizeof(conn->db), 1, conn->file);
    if (rc != 1)
        die("Failed to write database.", conn);

    rc = fflush(conn->file);
    if (rc == -1)
        die("Cannot flush database.", conn);
}

void Database_create(struct Connection *conn, size_t size)
{
    conn->db->MAX_ROWS = size;
    conn->db->MAX_DATA = conn->db->MAX_ROWS * 50;
    conn->db->rows = malloc(sizeof(struct Address) * conn->db->MAX_ROWS);
    if (!conn->db->rows)
        die("Memory error", conn);
    int i = 0;
    
    printf("Sizeof db: %ld\n", sizeof(conn->db));

    for (i = 0; i < conn->db->MAX_ROWS; ++i) {
        struct Address addr = {
            .id = i, 
            .set = 0,
            .name = NULL,
            .email = NULL,
            //.name = malloc(conn->db->MAX_DATA * sizeof(char)),
            //.email = malloc(conn->db->MAX_DATA * sizeof(char))
        };
       
        conn->db->rows[i] = addr;
    }

    for (i = 0; i < conn->db->MAX_ROWS; ++i) {
        printf("%d, %d, %s, %s\n", conn->db->rows[i].id, conn->db->rows[i].set,
                                 conn->db->rows[i].name, conn->db->rows[i].email);
    }
}

void Database_set(struct Connection *conn, int id, const char *name,
        const char *email)
{
    printf("We are in database_set\n");
    if (conn) printf("conn is okay\n");
    if (!conn) die("!conn", conn);
    if (conn->db) printf("conn->db is okay\n");
    if (!conn->db) die("!conn->db", conn);
    if (conn) printf("rows is okay suka\n");
    if (!conn->db->rows) die("!conn->db->rows", conn);


    conn->db->rows[id].name = "12345";
    
    struct Address *addr = &conn->db->rows[id];
    if (addr->set) {
        free(addr->name);
        free(addr->email);
    }


    addr->set = 1;
    
    addr->name = strdup(name);
    if (!addr->name)
        die("Name copy failed", conn);

    addr->email = strdup(email);
    if (!addr->email)
        die("Email copy failed", conn);

}

void Database_get(struct Connection *conn, int id) 
{
    struct Address *addr = &conn->db->rows[id];

    if (addr->set) {
        Address_print(addr);
    } else {
        die("ID is not set", conn);
    }
}

void Database_delete(struct Connection *conn, int id) 
{
    free(conn->db->rows[id].name);
    free(conn->db->rows[id].email);
    struct Address addr = {.id = id, .set = 0 };
    conn->db->rows[id] = addr;
}

void Database_list(struct Connection *conn) 
{
    int i = 0;
    struct Database *db = conn->db;

    for (i = 0; i < conn->db->MAX_ROWS; ++i) {
        struct Address *cur = &db->rows[i];

        if (cur->set) {
            Address_print(cur);
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc < 3)
        die("USAGE: ex17 <dbfile> <action> [action params]", NULL);

    char *filename = argv[1];
    char action = argv[2][0];
    struct Connection *conn = Database_open(filename, action);
    size_t id = 0;

    if (argc > 3) id = atoi(argv[3]);
    
    switch (action) {
        case 'c':
            if (argc != 4)
                die("USAGE: ./a.out <dbfile> <c> [number of rows in database].", conn);

            size_t size = atoi(argv[3]);
            Database_create(conn, size);
            Database_write(conn);
            break;

        case 'g':
            if (argc != 4)
                die("Need an id to get", conn);

            if (id >= conn->db->MAX_ROWS) 
                die("There is not that many records.", conn);

            Database_get(conn, id);
            break;

        case 's':
            if (argc != 6)
                die("Need id, name, email to set", conn);
            if (id >= conn->db->MAX_ROWS) 
                die("There is not that many records.", conn);

            printf("We are here\n");
            Database_set(conn, id, argv[4], argv[5]);
            Database_write(conn);
            break;

        case 'd':
            if (argc != 4)
                die("Need id to delete", conn);
            if (id >= conn->db->MAX_ROWS) 
                die("There is not that many records.", conn);

            Database_delete(conn, id);
            Database_write(conn);
            break;

        case 'l':
            Database_list(conn);
            break;
        default:
            die("Invalid action: c=create, g=get, d=del, l=list", conn);
    }

    Database_destroy(conn);
    Database_close(conn);

    return 0;
}






