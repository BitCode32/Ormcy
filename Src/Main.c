#include <Hallocy/Allocator.h>
#include <libpq-fe.h>
#include <stdio.h>

int main() {
    printf("Connecting to database...\n");

    char *connection_info = "dbname=Toido user=postgres password=trstn2410 host=localhost port=5432";
    PGconn *connection = PQconnectdb(connection_info);

    if (PQstatus(connection) != CONNECTION_OK) {
        printf("Failed to connect to database with error: %s\n", PQerrorMessage(connection));
        PQfinish(connection);
        return -1;
    }

    printf("Connected to database.\n");
    printf("Retrieving data from database...\n");

    char *query = "SELECT * FROM public.\"Users\";";
    PGresult *result = PQexec(connection, query);
    
    ExecStatusType result_status = PQresultStatus(result);
    printf("Querry status: %s\n", PQresStatus(result_status));
    if (result_status != PGRES_TUPLES_OK) {
        printf("Failed to execute query: %s\n", PQerrorMessage(connection));
        PQclear(result);
        PQfinish(connection);
        return -1;
    }

    printf("Query executed successfully.\n");

    int rows = PQntuples(result);
    int columns = PQnfields(result);
    printf("The number of rows are %d and the number of columns are %d.\n", rows, columns);

    for (int i = 0; i < columns; i++) {
        printf("%s\t", PQfname(result, i));
    }
    printf("\n");

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            printf("%s\t", PQgetvalue(result, i, j));
        }
        printf("\n");
    }

    PQclear(result);

    PQfinish(connection);
    return 0;
}