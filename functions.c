#include "functions.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

t_table *find_table(t_db *db, char *table_name) {
    t_table *tp = db->tables;
    while(tp != NULL) {
        if(!strcmp(tp->name, table_name)) {
            return tp;
        }
        tp = tp->next;
    }
    return NULL;
}

t_table *find_previous_table(t_db *db, char *table_name) {
    t_table *tp = db->tables;
    if(tp != NULL) {
        while(tp->next != NULL) {
            if(!strcmp(tp->next->name, table_name)) {
                return tp;
            }
            tp = tp->next;
        }
    }
    return NULL;
}

int get_column_index(t_table *t, char *column_name) {
    t_column *cp = t->columns;
    int col_index = 0;
    while(cp != NULL) {
        col_index++;
        if(!strcmp(cp->name, column_name)) {
            return col_index;
        }
        cp = cp->next;
    }
    return 0;
}

t_db *INIT_DB(char *db_name) {
    t_db *db = (t_db *)malloc(sizeof(t_db));
    if(!db) {
        return NULL;
    }
    strcpy(db->name, db_name);
    db->tables = NULL;
    return db;
}

void delete_columns(t_table *t) {
    t_column *col = t->columns;
    while(col != NULL) {
        t_column *previous = col;
        col = col->next;
        free(previous);
        previous = NULL;
    }
}

void delete_intCells(t_intLine *l) {
    t_intCell *cp = l->cells;
    while(cp != NULL) {
        t_intCell *previous = cp;
        cp = cp->next;
        free(previous);
        previous = NULL;
    }
}

void delete_intLine(t_table *t, int index, char *test) {
    t_intLine *lp = (t_intLine *)t->lines;
    if(test != NULL) {
        char *op = strtok(test, " ");
        int ref = atoi(strtok(NULL, " "));
        if(lp != NULL) {
            t_intLine *previous = lp;
            lp = lp->next;
            while(lp != NULL) {
                if(test_int(valueof_intCell(lp, index), ref, op)) {
                    previous->next = lp->next;
                    delete_intCells(lp);
                    free(lp);
                    lp = previous->next;
                } else {
                    previous = lp;
                    lp = lp->next;
                }
            }
            lp = (t_intLine *)t->lines;
            if(test_int(valueof_intCell(lp, index), ref, op)) {
                t->lines = ((t_intLine *)t->lines)->next;
                delete_intCells(lp);
                free(lp);
            }
        }
    } else {
        while(lp != NULL) {
            t_intLine *previous = lp;
            lp = lp->next;
            delete_intCells(previous);
            free(previous);
            previous = NULL;
        }
    }
}

void delete_floatCells(t_floatLine *l) {
    t_floatCell *cp = l->cells;
    while(cp != NULL) {
        t_floatCell *previous = cp;
        cp = cp->next;
        free(previous);
        previous = NULL;
    }
}

void delete_floatLine(t_table *t, int index, char *test) {
    t_floatLine *lp = (t_floatLine *)t->lines;
    if(test != NULL) {
        char *op = strtok(test, " ");
        float ref = atof(strtok(NULL, " "));
        if(lp != NULL) {
            t_floatLine *previous = lp;
            lp = lp->next;
            while(lp != NULL) {
                if(test_float(valueof_floatCell(lp, index), ref, op)) {
                    previous->next = lp->next;
                    delete_floatCells(lp);
                    free(lp);
                    lp = previous->next;
                } else {
                    previous = lp;
                    lp = lp->next;
                }
            }
            lp = (t_floatLine *)t->lines;
            if(test_float(valueof_floatCell(lp, index), ref, op)) {
                t->lines = ((t_floatLine *)t->lines)->next;
                delete_floatCells(lp);
                free(lp);
            }
        }
    } else {
        while(lp != NULL) {
            t_floatLine *previous = lp;
            lp = lp->next;
            delete_floatCells(previous);
            free(previous);
            previous = NULL;
        }
    }
}

void delete_stringCells(t_stringLine *l) {
    t_stringCell *cp = l->cells;
    while(cp != NULL) {
        t_stringCell *previous = cp;
        cp = cp->next;
        free(previous->value);
        previous->value = NULL;
        free(previous);
        previous = NULL;
    }
}

void delete_stringLine(t_table *t, int index, char *test) {
    t_stringLine *lp = (t_stringLine *)t->lines;
    if(test != NULL) {
        char *op = strtok(test, " ");
        char *ref = strtok(NULL, " ");
        if(lp != NULL) {
            t_stringLine *previous = lp;
            lp = lp->next;
            while(lp != NULL) {
                if(test_string(valueof_stringCell(lp, index), ref, op)) {
                    previous->next = lp->next;
                    delete_stringCells(lp);
                    free(lp);
                    lp = previous->next;
                } else {
                    previous = lp;
                    lp = lp->next;
                }
            }
            lp = (t_stringLine *)t->lines;
            if(test_string(valueof_stringCell(lp, index), ref, op)) {
                t->lines = ((t_stringLine *)t->lines)->next;
                delete_stringCells(lp);
                free(lp);
            }
        }
    } else {
        while(lp != NULL) {
            t_stringLine *previous = lp;
            lp = lp->next;
            delete_stringCells(previous);
            free(previous);
            previous = NULL;
        }
    }
}

int test_int(int val, int ref, char *op) {
    if(!strcmp(op, "<") && (val < ref)) return 1;
    if(!strcmp(op, "<") && !(val < ref)) return 0;

    if(!strcmp(op, "<=") && (val <= ref)) return 1;
    if(!strcmp(op, "<=") && !(val <= ref)) return 0;

    if(!strcmp(op, "==") && (val == ref)) return 1;
    if(!strcmp(op, "==") && !(val == ref)) return 0;

    if(!strcmp(op, "!=") && (val != ref)) return 1;
    if(!strcmp(op, "!=") && !(val != ref)) return 0;

    if(!strcmp(op, ">=") && (val >= ref)) return 1;
    if(!strcmp(op, ">=") && !(val >= ref)) return 0;

    if(!strcmp(op, ">") && (val > ref)) return 1;
    if(!strcmp(op, ">") && !(val > ref)) return 0;
    
    return 0;
}

int test_float(float val, float ref, char *op) {
    if(!strcmp(op, "<") && (val < ref)) return 1;
    if(!strcmp(op, "<") && !(val < ref)) return 0;

    if(!strcmp(op, "<=") && (val <= ref)) return 1;
    if(!strcmp(op, "<=") && !(val <= ref)) return 0;

    if(!strcmp(op, "==") && (val == ref)) return 1;
    if(!strcmp(op, "==") && !(val == ref)) return 0;

    if(!strcmp(op, "!=") && (val != ref)) return 1;
    if(!strcmp(op, "!=") && !(val != ref)) return 0;

    if(!strcmp(op, ">=") && (val >= ref)) return 1;
    if(!strcmp(op, ">=") && !(val >= ref)) return 0;

    if(!strcmp(op, ">") && (val > ref)) return 1;
    if(!strcmp(op, ">") && !(val > ref)) return 0;
    
    return 0;
}

int test_string(char *val, char *ref, char *op) {
    if(!strcmp(op, "<") && (strcmp(val, ref) < 0)) return 1;
    if(!strcmp(op, "<") && !(strcmp(val, ref) < 0)) return 0;

    if(!strcmp(op, "<=") && (strcmp(val, ref) <= 0)) return 1;
    if(!strcmp(op, "<=") && !(strcmp(val, ref) <= 0)) return 0;

    if(!strcmp(op, "==") && !strcmp(val, ref)) return 1;
    if(!strcmp(op, "==") && strcmp(val, ref)) return 0;

    if(!strcmp(op, "!=") && strcmp(val, ref)) return 1;
    if(!strcmp(op, "!=") && !strcmp(val, ref)) return 0;

    if(!strcmp(op, ">=") && (strcmp(val, ref) >= 0)) return 1;
    if(!strcmp(op, ">=") && !(strcmp(val, ref) >= 0)) return 0;

    if(!strcmp(op, ">") && (strcmp(val, ref) > 0)) return 1;
    if(!strcmp(op, ">") && !(strcmp(val, ref) > 0)) return 0;

    return 0;
}

int valueof_intCell(t_intLine *l, int index) {
    int cell_index = 1;
    t_intCell *cp = l->cells;
    while(cell_index != index) {
        cell_index++;
        cp = cp->next;
    }
    return cp->value;
}

float valueof_floatCell(t_floatLine *l, int index) {
    int cell_index = 1;
    t_floatCell *cp = l->cells;
    while(cell_index != index) {
        cell_index++;
        cp = cp->next;
    }
    return cp->value;
}

char *valueof_stringCell(t_stringLine *l, int index) {
    int cell_index = 1;
    t_stringCell *cp = l->cells;
    while(cell_index != index) {
        cell_index++;
        cp = cp->next;
    }
    return cp->value;
}

void DELETE(t_db *db, char *table_name, char *args) {
    if(args == NULL) {
        t_table *tp = find_table(db, table_name);
        t_table *prev = find_previous_table(db, table_name);        
        if(prev != NULL) {
            prev->next = tp->next;            
        } else {
            db->tables = tp->next;
        }
        CLEAR(tp);
        delete_columns(tp);
        free(tp);
        tp = NULL;
    } else {
        t_table *tp = find_table(db, table_name);
        char *col_name = strtok(args, " ");
        int col_index = get_column_index(tp, col_name);
        if(col_index) {
            if(tp->type == INT) {
                delete_intLine(tp, col_index, args + strlen(col_name) + 1);
            } else if(tp->type == FLOAT) {
                delete_floatLine(tp, col_index, args + strlen(col_name) + 1);
            } else if(tp->type == STRING) {
                delete_stringLine(tp, col_index, args + strlen(col_name) + 1);
            }
        } else {
            printf("Table \"%s\" does not contain column \"%s\".\n",
                tp->name, col_name);
        }
    }
}

void DELETE_DB(t_db *db) {
    t_table *tp = db->tables;
    while(tp != NULL) {
        t_table *previous = tp;
        tp = tp->next;
        DELETE(db, previous->name, NULL);
    }
    free(db);
    db = NULL;
}

void set_table_type(t_table *t, char *type) {
    if(!strcmp(type, "INT")) {
        t->type = INT;
    }
    if(!strcmp(type, "FLOAT")) {
        t->type = FLOAT;
    }
    if(!strcmp(type, "STRING")) {
        t->type = STRING;
    }
}

void generate_columns(t_table *t, char *column_tags) {
    char *column_name = strtok(column_tags, " ");
    t_column *col;
    while(column_name) {
        t_column *new_column = (t_column *)malloc(sizeof(t_column));
        strcpy(new_column->name, column_name);
        new_column->next = NULL;
        if(t->columns == NULL) {
            t->columns = new_column;
            col = t->columns;
        } else {
            col->next = new_column;
            col = col->next;
        }
        column_name = strtok(NULL, " ");
    }
}

void CREATE(t_db *db, char *table_name, char *args) {
    char *type = strtok(args, " ");
    if(strcmp(type, "INT") && strcmp(type, "FLOAT") && strcmp(type, "STRING")) {
        printf("Unknown data type: \"%s\".\n", type);
    } else if(db->tables == NULL) {
        db->tables = (t_table *)malloc(sizeof(t_table));
        strcpy(db->tables->name, table_name);
        set_table_type(db->tables, type);
        db->tables->columns = NULL;
        generate_columns(db->tables, args + strlen(type) + 1);
        db->tables->lines = NULL;
        db->tables->next = NULL;
    } else {
        t_table *new_table = db->tables;
        while(new_table->next != NULL) {
            new_table = new_table->next;
        }
        new_table->next = (t_table *)malloc(sizeof(t_table));
        strcpy(new_table->next->name, table_name);
        set_table_type(new_table->next, type);
        new_table->next->columns = NULL;
        generate_columns(new_table->next, args + strlen(type) + 1);
        new_table->next->lines = NULL;
        new_table->next->next = NULL;
    }
}

void PRINT_DB(t_db *db) {
    printf("DATABASE: %s\n\n", db->name);
    t_table *tp = db->tables;
    while(tp != NULL) {
        PRINT(tp, "header");
        PRINT(tp, "content");
        tp = tp->next;
    }
}

void PRINT(t_table *tp, char *print_task) {
    if(!strcmp(print_task, "header")) {
        printf("TABLE: %s\n", tp->name);
        t_column *col = tp->columns;
        for( ; col != NULL; col = col->next) {
            printf("%-*s ",MAX_COLUMN_NAME_LEN, col->name);
        }
        printf("\n");
        col = tp->columns;
        for( ; col != NULL; col = col->next) {
            unsigned int padding = 0;
            for( ; padding < MAX_COLUMN_NAME_LEN; padding++) {
                printf("-");
            }
            printf(" ");
        }
        printf("\n");
    } else if(!strcmp(print_task, "content")) {
        if(tp->type == INT) {
            t_intLine *lp = (t_intLine *)tp->lines;
            for( ; lp != NULL; lp = lp->next) {
                t_intCell *cp = lp->cells;
                for( ; cp != NULL; cp = cp->next) {
                    printf("%-*d ", MAX_COLUMN_NAME_LEN, cp->value);
                }
                printf("\n");
            }
        } else if(tp->type == FLOAT) {
            t_floatLine *lp = (t_floatLine *)tp->lines;
            for( ; lp != NULL; lp = lp->next) {
                t_floatCell *cp = lp->cells;
                for( ; cp != NULL; cp = cp->next) {
                    printf("%-*f ", MAX_COLUMN_NAME_LEN, cp->value);
                }
                printf("\n");
            }
        } else if(tp->type == STRING) {
            t_stringLine *lp = (t_stringLine *)tp->lines;
            for( ; lp != NULL; lp = lp->next) {
                t_stringCell *cp = lp->cells;
                for( ; cp != NULL; cp = cp->next) {
                    printf("%-*s ", MAX_COLUMN_NAME_LEN, cp->value);
                }
                printf("\n");
            }
        }
        printf("\n");
    }
}

void SEARCH(t_table *tp, char *args) {
    char *col_name = strtok(args, " ");
    int col_index = get_column_index(tp, col_name);
    if(col_index) {
        PRINT(tp, "header");
        char *op = strtok(NULL, " ");
        if(tp->type == INT) {
            int ref = atoi(strtok(NULL, " "));
            t_intLine *lp = (t_intLine *)tp->lines;
            for( ; lp != NULL; lp = lp->next) {
                if(test_int(valueof_intCell(lp, col_index), ref, op)) {
                    t_intCell *cp = lp->cells;
                    for( ; cp != NULL; cp = cp->next) {
                        printf("%-*d ", MAX_COLUMN_NAME_LEN, cp->value);
                    }
                    printf("\n");
                }
            }
            printf("\n");
        } else if(tp->type == FLOAT) {
            float ref = atof(strtok(NULL, " "));
            t_floatLine *lp = (t_floatLine *)tp->lines;
            for( ; lp != NULL; lp = lp->next) {
                if(test_float(valueof_floatCell(lp, col_index), ref, op)) {
                    t_floatCell *cp = lp->cells;
                    for( ; cp != NULL; cp = cp->next) {
                        printf("%-*f ", MAX_COLUMN_NAME_LEN, cp->value);
                    }
                    printf("\n");
                }
            }
            printf("\n");
        } else if(tp->type == STRING) {
            char *ref = strtok(NULL, " ");
            t_stringLine *lp = (t_stringLine *)tp->lines;
            for( ; lp != NULL; lp = lp->next) {
                if(test_string(valueof_stringCell(lp, col_index), ref, op)) {
                    t_stringCell *cp = lp->cells;
                    for( ; cp != NULL; cp = cp->next) {
                        printf("%-*s ", MAX_COLUMN_NAME_LEN, cp->value);
                    }
                    printf("\n");
                }
            }
            printf("\n");
        }
    } else {
        printf("Table \"%s\" does not contain column \"%s\".\n",
            tp->name, col_name);
    }
}

void add_intCells(t_intLine *lp, char *values) {
    char *value_as_string = strtok(values, " ");
    t_intCell *cp = lp->cells;
    while(value_as_string) {
        t_intCell *new_cell = (t_intCell *)malloc(sizeof(t_intCell));
        new_cell->value = atoi(value_as_string);
        new_cell->next = NULL;
        if(lp->cells == NULL) {
            lp->cells = new_cell;
            cp = lp->cells;
        } else {
            cp->next = new_cell;
            cp = cp->next;
        }
        value_as_string = strtok(NULL, " ");
    }
}

void add_intLine(t_table *tp, char *values) {
    if(tp->lines == NULL) {
        tp->lines = (t_intLine *)malloc(sizeof(t_intLine));
        ((t_intLine *)tp->lines)->cells = NULL;
        ((t_intLine *)tp->lines)->next = NULL;
        add_intCells((t_intLine *)tp->lines, values);
    } else {
        t_intLine *lp = (t_intLine *)tp->lines;
        while(lp->next != NULL) {
            lp = lp->next;
        }
        lp->next = (t_intLine *)malloc(sizeof(t_intLine));
        lp->next->cells = NULL;
        lp->next->next = NULL;
        add_intCells(lp->next, values);
    }
}

void add_floatCells(t_floatLine *lp, char *values) {
    char *value_as_string = strtok(values, " ");
    t_floatCell *cp = lp->cells;
    while(value_as_string) {
        t_floatCell *new_cell = (t_floatCell *)malloc(sizeof(t_floatCell));
        new_cell->value = atof(value_as_string);
        new_cell->next = NULL;
        if(lp->cells == NULL) {
            lp->cells = new_cell;
            cp = lp->cells;
        } else {
            cp->next = new_cell;
            cp = cp->next;
        }
        value_as_string = strtok(NULL, " ");
    }
}

void add_floatLine(t_table *tp, char *values) {
    if(tp->lines == NULL) {
        tp->lines = (t_floatLine *)malloc(sizeof(t_floatLine));
        ((t_floatLine *)tp->lines)->cells = NULL;
        ((t_floatLine *)tp->lines)->next = NULL;
        add_floatCells((t_floatLine *)tp->lines, values);
    } else {
        t_floatLine *lp = (t_floatLine *)tp->lines;
        while(lp->next != NULL) {
            lp = lp->next;
        }
        lp->next = (t_floatLine *)malloc(sizeof(t_floatLine));
        lp->next->cells = NULL;
        lp->next->next = NULL;
        add_floatCells(lp->next, values);
    }
}

void add_stringCells(t_stringLine *lp, char *values) {
    char *value_as_string = strtok(values, " ");
    t_stringCell *cp = lp->cells;
    while(value_as_string) {
        t_stringCell *new_cell = (t_stringCell *)malloc(sizeof(t_stringCell));
        new_cell->value = (char *)malloc(MAX_CMD_LEN);
        strcpy(new_cell->value, value_as_string);
        new_cell->next = NULL;
        if(lp->cells == NULL) {
            lp->cells = new_cell;
            cp = lp->cells;
        } else {
            cp->next = new_cell;
            cp = cp->next;
        }
        value_as_string = strtok(NULL, " ");
    }
}

void add_stringLine(t_table *tp, char *values) {
    if(tp->lines == NULL) {
        tp->lines = (t_stringLine *)malloc(sizeof(t_stringLine));
        ((t_stringLine *)tp->lines)->cells = NULL;
        ((t_stringLine *)tp->lines)->next = NULL;
        add_stringCells((t_stringLine *)tp->lines, values);
    } else {
        t_stringLine *lp = (t_stringLine *)tp->lines;
        while(lp->next != NULL) {
            lp = lp->next;
        }
        lp->next = (t_stringLine *)malloc(sizeof(t_stringLine));
        lp->next->cells = NULL;
        lp->next->next = NULL;
        add_stringCells(lp->next, values);
    }
}

void ADD(t_table *tp, char *args) {
    if(tp->type == INT) {
        add_intLine(tp, args);
    } else if(tp->type == FLOAT) {
        add_floatLine(tp, args);
    } else if(tp->type == STRING) {
        add_stringLine(tp, args);
    }
}

void CLEAR(t_table *tp) {
    if(tp->type == INT) {
        delete_intLine(tp, 0, NULL);
    } else if(tp->type == FLOAT) {
        delete_floatLine(tp, 0, NULL);
    } else if(tp->type == STRING) {
        delete_stringLine(tp, 0, NULL);
    }
}