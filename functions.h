#include "structures.h"

// returns pointer to table named "table_name"
t_table *find_table(t_db *db, char *table_name);

// returns pointer to table before the table named "table_name"
t_table *find_previous_table(t_db *db, char *table_name);

// returns index of column named "column_name"
int get_column_index(t_table *t, char *col_name);

// returns pointer to initialized database with name "db_name"
t_db *INIT_DB(char *db_name);

// deletes all columns of table pointed to by t
void delete_columns(t_table *t);

// deletes all cells of line pointed to by l
void delete_intCells(t_intLine *l);

// if test == NULL, deletes all lines of table pointed to by t
// else, deletes all lines whose cell value at given index returns a true test
void delete_intLine(t_table *t, int index, char *test);

// deletes all cells of line pointed by l
void delete_floatCells(t_floatLine *l);

// if test == NULL, deletes all lines of table pointed to by t
// else, deletes all lines whose cell value at given index returns a true test
void delete_floatLine(t_table *t, int index, char *test);

// deletes all cells of line pointed by l
void delete_stringCells(t_stringLine *l);

// if test == NULL, deletes all lines of table pointed to by t
// else, deletes all lines whose cell value at given index returns a true test
void delete_stringLine(t_table *t, int index, char *test);

// returns bool value (true = 1, false = 0) of test given by [value] [op] [ref]
int test_int(int val, int ref, char *op);

// returns bool value (true = 1, false = 0) of test given by [value] [op] [ref]
int test_float(float val, float ref, char *op);

// returns bool value (true = 1, false = 0) of test given by [value] [op] [ref]
int test_string(char *val, char *ref, char *op);

// returns int value of cell located on line pointed to by l with given index
int valueof_intCell(t_intLine *l, int index);

// returns float value of cell located on line pointed to by l with given index
float valueof_floatCell(t_floatLine *l, int index);

// returns string value of cell located on line pointed to by l with given index
char *valueof_stringCell(t_stringLine *l, int index);

// if args == NULL, deletes table named "table_name"
// else, calls a delete line procedure with column name and test given by args
void DELETE(t_db *db, char *table_name, char *args);

// deletes database pointed to by db
void DELETE_DB(t_db *db);

// sets data type of table pointed to by t
void set_table_type(t_table *t, char *type);

// generates columns of table pointed to by t with given column tags
void generate_columns(t_table *t, char *col_tags);

// creates empty table named "table_name" with columns given by args
void CREATE(t_db *db, char *table_name, char *args);

// prints database pointed to by db
void PRINT_DB(t_db *db);

// if print_task == "header", prints header of table pointed to by t
// if print_task == "content", prints lines of table pointed to by t
void PRINT(t_table *t, char *print_task);

// prints only lines of table pointed to by t whose
// test given by args returns bool value 1 (true)
void SEARCH(t_table *t, char *args);

// creates cells of line pointed to by l with given values
void add_intCells(t_intLine *l, char *values);

// creates a new line in table pointed to by t with given values
void add_intLine(t_table *t, char *values);

// creates cells of line pointed to by l with given values
void add_floatCells(t_floatLine *l, char *values);

// creates a new line in table pointed to by t with given values
void add_floatLine(t_table *t, char *values);

// creates cells of line pointed to by l with given values
void add_stringCells(t_stringLine *l, char *values);

// creates a new line in table pointed to by t with given values
void add_stringLine(t_table *t, char *values);

// adds a new line to table pointed to by t, with cell values given by args
void ADD(t_table *t, char *args);

// calls a delete line procedure, deleting the lines of table pointed to by t
void CLEAR(t_table *t);