// python
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 100
#define MAX_TOKEN_LENGTH 100

// Token types - moved before struct definitions
enum TYPE
{
    IDENTIFIER,
    KEYWORD,
    STRING_LITERAL,
    NUMERIC_CONSTANT,
    OPERATOR,
    DELIMITER,
    SPECIAL_SYMBOL,
    RELATIONAL_OPERATOR,
    INDENTATION
};

// Structure definitions
typedef struct node
{
    char *cur;
    int row, col;
    struct node *next;
    enum TYPE type;
} *Node;

typedef struct symbol
{
    char *name;
    char *data_type; // For Python, this will be determined at runtime
    struct symbol *next;
    unsigned int size;
} *Symbol;

// Global variables
Node hashTable[MAX_SIZE];
Symbol st[MAX_SIZE];

// Python keywords
char keywords[][20] = {
    "False", "None", "True", "and", "as", "assert", "async", "await",
    "break", "class", "continue", "def", "del", "elif", "else", "except",
    "finally", "for", "from", "global", "if", "import", "in", "is",
    "lambda", "nonlocal", "not", "or", "pass", "raise", "return",
    "try", "while", "with", "yield"};

// Python operators
char operators[][3] = {
    "+", "-", "*", "/", "%", "**", "//", "=", "+=", "-=", "*=", "/=",
    "%=", "**=", "//=", "&=", "|=", "^=", ">>=", "<<=", "&", "|", "^",
    "~", ">>", "<<"};

char types[][30] = {
    "IDENTIFIER", "KEYWORD", "STRING_LITERAL", "NUMERIC_CONSTANT",
    "OPERATOR", "DELIMITER", "SPECIAL_SYMBOL", "RELATIONAL_OPERATOR",
    "INDENTATION"};

// Function prototypes
int hash(int size);
void displaySymbolTable();
int searchSymbolTable(char identifier[], char data_type[]);
int searchHashTable(char buffer[], enum TYPE type);
void insertSymbolTable(char identifier[], char data_type[]);
void insertHashTable(char buffer[], int row, int col, enum TYPE type);
int isKeyword(char buffer[]);
int isOperator(char *op);
void removeComments(FILE *source, FILE *target);
int countIndentation(char *line);

// Hash function
int hash(int size)
{
    return (size % MAX_SIZE);
}

// Check if string is a Python keyword
int isKeyword(char buffer[])
{
    for (int i = 0; i < sizeof(keywords) / sizeof(keywords[0]); i++)
    {
        if (strcmp(buffer, keywords[i]) == 0)
        {
            return 1;
        }
    }
    return 0;
}

// Check if string is a Python operator
int isOperator(char *op)
{
    for (int i = 0; i < sizeof(operators) / sizeof(operators[0]); i++)
    {
        if (strcmp(op, operators[i]) == 0)
        {
            return 1;
        }
    }
    return 0;
}

// Remove Python comments and empty lines
void removeComments(FILE *source, FILE *target)
{
    char c, next;
    int in_string = 0;
    char string_char = 0;

    while ((c = fgetc(source)) != EOF)
    {
        if (c == '"' || c == '\'')
        {
            if (!in_string)
            {
                in_string = 1;
                string_char = c;
            }
            else if (c == string_char)
            {
                in_string = 0;
            }
            fputc(c, target);
        }
        else if (c == '#' && !in_string)
        {
            while ((c = fgetc(source)) != '\n' && c != EOF)
                ;
            if (c == '\n')
                fputc(c, target);
        }
        else
        {
            fputc(c, target);
        }
    }
}

// Count indentation level
int countIndentation(char *line)
{
    int spaces = 0;
    int i = 0;

    while (line[i] == ' ' || line[i] == '\t')
    {
        if (line[i] == ' ')
            spaces++;
        else if (line[i] == '\t')
            spaces += 4; // Python treats tab as 4 spaces
        i++;
    }

    return spaces / 4; // Return indentation level
}

void displaySymbolTable()
{
    printf("\nPython Symbol Table\n");
    printf("Index\tLexeme\t\tType\t\tSize\n");
    printf("----------------------------------------\n");

    int ctn = 1;
    for (int i = 0; i < MAX_SIZE; i++)
    {
        if (st[i] == NULL)
            continue;

        Symbol cur = st[i];
        while (cur)
        {
            printf("%d\t%-12s\t%-12s\t%d\n",
                   ctn,
                   cur->name,
                   cur->data_type,
                   cur->size);
            cur = cur->next;
            ctn++;
        }
    }
}

int searchSymbolTable(char identifier[], char data_type[])
{
    int index = hash(strlen(identifier));
    if (st[index] == NULL)
        return -1;

    Symbol cur = st[index];
    int i = 0;
    while (cur != NULL)
    {
        if (strcmp(identifier, cur->name) == 0)
            return i;
        cur = cur->next;
        i++;
    }
    return -1;
}

int searchHashTable(char buffer[], enum TYPE type)
{
    int index = hash(strlen(buffer));
    if (hashTable[index] == NULL)
        return 0;

    Node cur = hashTable[index];
    while (cur != NULL)
    {
        if (strcmp(cur->cur, buffer) == 0)
            return 1;
        cur = cur->next;
    }
    return 0;
}

void insertHashTable(char buffer[], int row, int col, enum TYPE type)
{
    if (type == IDENTIFIER || searchHashTable(buffer, type) == 0)
    {
        printf("<%s,%d,%d,%s>\n", buffer, row, col, types[type]);

        int index = hash(strlen(buffer));
        Node n = (Node)malloc(sizeof(struct node));
        n->cur = strdup(buffer);
        n->next = NULL;
        n->row = row;
        n->col = col;
        n->type = type;

        if (hashTable[index] == NULL)
        {
            hashTable[index] = n;
        }
        else
        {
            Node cur = hashTable[index];
            while (cur->next != NULL)
                cur = cur->next;
            cur->next = n;
        }
    }
}

void insertSymbolTable(char identifier[], char data_type[])
{
    if (searchSymbolTable(identifier, data_type) == -1)
    {
        Symbol n = (Symbol)malloc(sizeof(struct symbol));
        n->name = strdup(identifier);
        n->data_type = strdup(data_type);
        n->next = NULL;

        // In Python, everything is an object, so we'll use generic sizes
        if (strcmp(data_type, "function") == 0)
            n->size = 0;
        else if (strcmp(data_type, "class") == 0)
            n->size = 0;
        else
            n->size = 8; // Default size for Python objects

        int index = hash(strlen(identifier));

        if (st[index] == NULL)
        {
            st[index] = n;
        }
        else
        {
            Symbol cur = st[index];
            while (cur->next != NULL)
                cur = cur->next;
            cur->next = n;
        }
    }
}

int main()
{
    FILE *source = fopen("input.py", "r");
    FILE *temp = fopen("temp.py", "w");

    if (!source || !temp)
    {
        printf("Error opening files!\n");
        return 1;
    }

    // Initialize hash tables
    for (int i = 0; i < MAX_SIZE; i++)
    {
        hashTable[i] = NULL;
        st[i] = NULL;
    }

    // Remove comments first
    removeComments(source, temp);
    fclose(source);
    fclose(temp);

    // Reopen temp file for processing
    FILE *fin = fopen("temp.py", "r");
    if (!fin)
    {
        printf("Error opening temporary file!\n");
        return 1;
    }

    char line[1024];
    int row = 1;
    int in_function = 0;
    int in_class = 0;
    char current_context[100] = "";

    while (fgets(line, sizeof(line), fin))
    {
        int indent_level = countIndentation(line);
        int col = 1;
        char buffer[MAX_TOKEN_LENGTH] = "";
        int i = 0;

        // Process indentation
        if (indent_level > 0)
        {
            char indent_str[10];
            sprintf(indent_str, "%d", indent_level);
            insertHashTable(indent_str, row, 1, INDENTATION);
        }

        // Skip leading whitespace
        while (line[col - 1] == ' ' || line[col - 1] == '\t')
            col++;

        for (int pos = col - 1; line[pos] && line[pos] != '\n'; pos++)
        {
            char c = line[pos];

            if (isalpha(c) || c == '_')
            {
                // Identifier or keyword
                while (isalnum(c) || c == '_')
                {
                    buffer[i++] = c;
                    c = line[++pos];
                }
                pos--;
                buffer[i] = '\0';

                if (isKeyword(buffer))
                {
                    insertHashTable(buffer, row, col, KEYWORD);

                    // Track function and class definitions
                    if (strcmp(buffer, "def") == 0)
                    {
                        in_function = 1;
                    }
                    else if (strcmp(buffer, "class") == 0)
                    {
                        in_class = 1;
                    }
                }
                else
                {
                    insertHashTable(buffer, row, col, IDENTIFIER);

                    // Add to symbol table with appropriate type
                    if (in_function)
                    {
                        insertSymbolTable(buffer, "function");
                        in_function = 0;
                    }
                    else if (in_class)
                    {
                        insertSymbolTable(buffer, "class");
                        in_class = 0;
                    }
                    else
                    {
                        insertSymbolTable(buffer, "variable");
                    }
                }

                i = 0;
                buffer[0] = '\0';
            }
            else if (isdigit(c))
            {
                // Number constant
                while (isdigit(c) || c == '.' || c == 'e' || c == 'E' ||
                       c == '+' || c == '-')
                {
                    buffer[i++] = c;
                    c = line[++pos];
                }
                pos--;
                buffer[i] = '\0';
                insertHashTable(buffer, row, col, NUMERIC_CONSTANT);
                i = 0;
                buffer[0] = '\0';
            }
            else if (c == '"' || c == '\'')
            {
                // String literal
                char quote = c;
                buffer[i++] = c;
                c = line[++pos];
                while (c != quote && c != '\0')
                {
                    buffer[i++] = c;
                    c = line[++pos];
                }
                buffer[i++] = quote;
                buffer[i] = '\0';
                insertHashTable(buffer, row, col, STRING_LITERAL);
                i = 0;
                buffer[0] = '\0';
            }
            else if (strchr("+-*/%=<>!&|^~", c))
            {
                // Operator
                buffer[i++] = c;
                char next = line[pos + 1];
                if (next && strchr("+-*/%=<>&|^", next))
                {
                    buffer[i++] = next;
                    pos++;
                }
                buffer[i] = '\0';
                if (isOperator(buffer))
                    insertHashTable(buffer, row, col, OPERATOR);
                i = 0;
                buffer[0] = '\0';
            }
            else if (strchr("()[]{},:;", c))
            {
                // Delimiter
                buffer[i++] = c;
                buffer[i] = '\0';
                insertHashTable(buffer, row, col, DELIMITER);
                i = 0;
                buffer[0] = '\0';
            }

            col++;
        }
        row++;
    }

    displaySymbolTable();
    fclose(fin);
    remove("temp.py"); // Clean up temporary file

    return 0;
}

// js
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 100
#define MAX_TOKEN_LENGTH 100

// Token types
enum TYPE
{
    IDENTIFIER,
    KEYWORD,
    STRING_LITERAL,
    NUMERIC_CONSTANT,
    OPERATOR,
    DELIMITER,
    SPECIAL_SYMBOL,
    TEMPLATE_LITERAL,
    REGEX_LITERAL,
    BOOLEAN_LITERAL
};

// Structure definitions
typedef struct node
{
    char *cur;
    int row, col;
    struct node *next;
    enum TYPE type;
} *Node;

typedef struct symbol
{
    char *name;
    char *data_type; // For JavaScript variables
    char *scope;     // Global, Local, Block
    struct symbol *next;
    unsigned int size;
} *Symbol;

// Global variables
Node hashTable[MAX_SIZE];
Symbol st[MAX_SIZE];

// JavaScript keywords
char keywords[][20] = {
    "break", "case", "catch", "class", "const", "continue", "debugger",
    "default", "delete", "do", "else", "export", "extends", "finally",
    "for", "function", "if", "import", "in", "instanceof", "new", "null",
    "return", "super", "switch", "this", "throw", "try", "typeof",
    "var", "void", "while", "with", "yield", "let", "static", "enum",
    "await", "async", "implements", "package", "protected", "interface",
    "private", "public"};

// JavaScript operators
char operators[][4] = {
    "+", "-", "*", "/", "%", "++", "--", "=", "+=", "-=", "*=", "/=",
    "%=", "**=", "<<=", ">>=", ">>>=", "&=", "^=", "|=", "&", "|", "^",
    "~", "<<", ">>", ">>>", "==", "===", "!=", "!==", "<", "<=", ">",
    ">=", "&&", "||", "??", "?.", "?", ":", "=>", "..."};

char types[][30] = {
    "IDENTIFIER", "KEYWORD", "STRING_LITERAL", "NUMERIC_CONSTANT",
    "OPERATOR", "DELIMITER", "SPECIAL_SYMBOL", "TEMPLATE_LITERAL",
    "REGEX_LITERAL", "BOOLEAN_LITERAL"};

// Function prototypes
int hash(int size);
void displaySymbolTable();
int searchSymbolTable(char identifier[], char scope[]);
int searchHashTable(char buffer[], enum TYPE type);
void insertSymbolTable(char identifier[], char data_type[], char scope[]);
void insertHashTable(char buffer[], int row, int col, enum TYPE type);
int isKeyword(char buffer[]);
int isOperator(char *op);
void removeComments(FILE *source, FILE *target);

// Hash function
int hash(int size)
{
    return (size % MAX_SIZE);
}

// Check if string is a JavaScript keyword
int isKeyword(char buffer[])
{
    for (int i = 0; i < sizeof(keywords) / sizeof(keywords[0]); i++)
    {
        if (strcmp(buffer, keywords[i]) == 0)
        {
            return 1;
        }
    }
    return 0;
}

// Check if string is a JavaScript operator
int isOperator(char *op)
{
    for (int i = 0; i < sizeof(operators) / sizeof(operators[0]); i++)
    {
        if (strcmp(op, operators[i]) == 0)
        {
            return 1;
        }
    }
    return 0;
}

// Remove JavaScript comments (both // and /* */) and empty lines
void removeComments(FILE *source, FILE *target)
{
    char c, next;
    int in_string = 0;
    char string_char = 0;
    int in_comment = 0;

    while ((c = fgetc(source)) != EOF)
    {
        if (!in_comment && (c == '"' || c == '\'' || c == '`'))
        {
            if (!in_string)
            {
                in_string = 1;
                string_char = c;
            }
            else if (c == string_char)
            {
                in_string = 0;
            }
            fputc(c, target);
        }
        else if (!in_string && c == '/')
        {
            next = fgetc(source);
            if (next == '/')
            { // Single-line comment
                while ((c = fgetc(source)) != '\n' && c != EOF)
                    ;
                if (c == '\n')
                    fputc(c, target);
            }
            else if (next == '*')
            { // Multi-line comment
                in_comment = 1;
                while (in_comment)
                {
                    c = fgetc(source);
                    if (c == '*')
                    {
                        next = fgetc(source);
                        if (next == '/')
                        {
                            in_comment = 0;
                        }
                        else
                        {
                            fseek(source, -1, SEEK_CUR);
                        }
                    }
                }
            }
            else
            {
                fputc(c, target);
                fputc(next, target);
            }
        }
        else if (!in_comment)
        {
            fputc(c, target);
        }
    }
}

void displaySymbolTable()
{
    printf("\nJavaScript Symbol Table\n");
    printf("Index\tLexeme\t\tType\t\tScope\t\tSize\n");
    printf("------------------------------------------------\n");

    int ctn = 1;
    for (int i = 0; i < MAX_SIZE; i++)
    {
        if (st[i] == NULL)
            continue;

        Symbol cur = st[i];
        while (cur)
        {
            printf("%d\t%-12s\t%-12s\t%-12s\t%d\n",
                   ctn,
                   cur->name,
                   cur->data_type,
                   cur->scope,
                   cur->size);
            cur = cur->next;
            ctn++;
        }
    }
}

void insertSymbolTable(char identifier[], char data_type[], char scope[])
{
    if (searchSymbolTable(identifier, scope) == -1)
    {
        Symbol n = (Symbol)malloc(sizeof(struct symbol));
        n->name = strdup(identifier);
        n->data_type = strdup(data_type);
        n->scope = strdup(scope);
        n->next = NULL;

        // Set size based on type (approximate JavaScript sizes)
        if (strcmp(data_type, "function") == 0)
            n->size = 0;
        else if (strcmp(data_type, "class") == 0)
            n->size = 0;
        else if (strcmp(data_type, "number") == 0)
            n->size = 8;
        else if (strcmp(data_type, "boolean") == 0)
            n->size = 4;
        else if (strcmp(data_type, "string") == 0)
            n->size = 8; // Reference size
        else
            n->size = 8; // Default size for objects

        int index = hash(strlen(identifier));

        if (st[index] == NULL)
        {
            st[index] = n;
        }
        else
        {
            Symbol cur = st[index];
            while (cur->next != NULL)
                cur = cur->next;
            cur->next = n;
        }
    }
}

int searchSymbolTable(char identifier[], char scope[])
{
    int index = hash(strlen(identifier));
    if (st[index] == NULL)
        return -1;

    Symbol cur = st[index];
    int i = 0;
    while (cur != NULL)
    {
        if (strcmp(identifier, cur->name) == 0 && strcmp(scope, cur->scope) == 0)
            return i;
        cur = cur->next;
        i++;
    }
    return -1;
}

void insertHashTable(char buffer[], int row, int col, enum TYPE type)
{
    if (type == IDENTIFIER || searchHashTable(buffer, type) == 0)
    {
        printf("<%s,%d,%d,%s>\n", buffer, row, col, types[type]);

        int index = hash(strlen(buffer));
        Node n = (Node)malloc(sizeof(struct node));
        n->cur = strdup(buffer);
        n->next = NULL;
        n->row = row;
        n->col = col;
        n->type = type;

        if (hashTable[index] == NULL)
        {
            hashTable[index] = n;
        }
        else
        {
            Node cur = hashTable[index];
            while (cur->next != NULL)
                cur = cur->next;
            cur->next = n;
        }
    }
}

int searchHashTable(char buffer[], enum TYPE type)
{
    int index = hash(strlen(buffer));
    if (hashTable[index] == NULL)
        return 0;

    Node cur = hashTable[index];
    while (cur != NULL)
    {
        if (strcmp(cur->cur, buffer) == 0)
            return 1;
        cur = cur->next;
    }
    return 0;
}

int main()
{
    FILE *source = fopen("input.js", "r");
    FILE *temp = fopen("temp.js", "w");

    if (!source || !temp)
    {
        printf("Error opening files!\n");
        return 1;
    }

    // Initialize hash tables
    for (int i = 0; i < MAX_SIZE; i++)
    {
        hashTable[i] = NULL;
        st[i] = NULL;
    }

    // Remove comments first
    removeComments(source, temp);
    fclose(source);
    fclose(temp);

    // Reopen temp file for processing
    FILE *fin = fopen("temp.js", "r");
    if (!fin)
    {
        printf("Error opening temporary file!\n");
        return 1;
    }

    char line[1024];
    int row = 1;
    int block_level = 0;
    char current_scope[100] = "global";

    while (fgets(line, sizeof(line), fin))
    {
        int col = 1;
        char buffer[MAX_TOKEN_LENGTH] = "";
        int i = 0;

        for (int pos = 0; line[pos] && line[pos] != '\n'; pos++)
        {
            char c = line[pos];

            // Track block scope
            if (c == '{')
                block_level++;
            else if (c == '}')
                block_level--;

            if (isalpha(c) || c == '_' || c == '$')
            {
                // Identifier or keyword
                while (isalnum(c) || c == '_' || c == '$')
                {
                    buffer[i++] = c;
                    c = line[++pos];
                }
                pos--;
                buffer[i] = '\0';

                if (isKeyword(buffer))
                {
                    insertHashTable(buffer, row, col, KEYWORD);

                    // Update scope for var, let, const declarations
                    if (strcmp(buffer, "function") == 0)
                    {
                        strcpy(current_scope, "function");
                    }
                    else if (strcmp(buffer, "class") == 0)
                    {
                        strcpy(current_scope, "class");
                    }
                }
                else
                {
                    insertHashTable(buffer, row, col, IDENTIFIER);

                    // Determine variable type based on context
                    char *var_type = "undefined";
                    if (strcmp(current_scope, "function") == 0)
                    {
                        var_type = "function";
                        strcpy(current_scope, block_level > 0 ? "block" : "global");
                    }
                    else if (strcmp(current_scope, "class") == 0)
                    {
                        var_type = "class";
                        strcpy(current_scope, block_level > 0 ? "block" : "global");
                    }

                    insertSymbolTable(buffer, var_type, current_scope);
                }

                i = 0;
                buffer[0] = '\0';
            }
            else if (isdigit(c) || (c == '.' && isdigit(line[pos + 1])))
            {
                // Number constant (including decimal and scientific notation)
                while (isdigit(c) || c == '.' || c == 'e' || c == 'E' ||
                       c == '+' || c == '-' || c == 'n')
                {
                    buffer[i++] = c;
                    c = line[++pos];
                }
                pos--;
                buffer[i] = '\0';
                insertHashTable(buffer, row, col, NUMERIC_CONSTANT);
                i = 0;
                buffer[0] = '\0';
            }
            else if (c == '"' || c == '\'' || c == '`')
            {
                // String or template literal
                char quote = c;
                buffer[i++] = c;
                c = line[++pos];
                while (c != quote && c != '\0')
                {
                    if (c == '\\')
                    {
                        buffer[i++] = c;
                        c = line[++pos];
                    }
                    buffer[i++] = c;
                    c = line[++pos];
                }
                buffer[i++] = quote;
                buffer[i] = '\0';

                enum TYPE str_type = (quote == '`') ? TEMPLATE_LITERAL : STRING_LITERAL;
                insertHashTable(buffer, row, col, str_type);
                i = 0;
                buffer[0] = '\0';
            }
            else if (c == '/')
            {
                // Potential regex literal
                char next = line[pos + 1];
                if (next != '/' && next != '*')
                {
                    buffer[i++] = c;
                    c = line[++pos];
                    while (c != '/' || line[pos - 1] == '\\')
                    {
                        buffer[i++] = c;
                        c = line[++pos];
                    }
                    buffer[i++] = c;
                    // Get regex flags if any
                    while (isalpha(line[pos + 1]))
                    {
                        c = line[++pos];
                        buffer[i++] = c;
                    }
                    buffer[i] = '\0';
                    insertHashTable(buffer, row, col, REGEX_LITERAL);
                    i = 0;
                    buffer[0] = '\0';
                }
            }
            else if (strchr("+-*/%=<>!&|^~?:", c))
            {
                // Operator
                buffer[i++] = c;
                char next = line[pos + 1];
                if (next && strchr("+-*/%=<>&|^", next))
                {
                    buffer[i++] = next;
                    pos++;
                    // Check for three-character operators
                    char next2 = line[pos + 1];
                    if (next2 && strchr("=&|>", next2))
                    {
                        buffer[i++] = next2;
                        pos++;
                    }
                }
                buffer[i] = '\0';
                if (isOperator(buffer))
                    insertHashTable(buffer, row, col, OPERATOR);
                i = 0;
                buffer[0] = '\0';
            }
            else if (strchr("()[]{},.;", c))
            {
                // Delimiter
                buffer[i++] = c;
                buffer[i] = '\0';
                insertHashTable(buffer, row, col, DELIMITER);
                i = 0;
                buffer[0] = '\0';
            }
            else if (c == 't' || c == 'f')
            {
                // Check for boolean literals 'true' and 'false'
                char temp[6] = {0};
                int j = 0;
                while (isalpha(line[pos]) && j < 5)
                {
                    temp[j++] = line[pos++];
                }
                temp[j] = '\0';
                pos--;

                if (strcmp(temp, "true") == 0 || strcmp(temp, "false") == 0)
                {
                    insertHashTable(temp, row, col, BOOLEAN_LITERAL);
                    if (strcmp(temp, "true") == 0)
                    {
                        insertSymbolTable(temp, "boolean", current_scope);
                    }
                }
                else
                {
                    pos -= (j - 1); // Reset position if not a boolean literal
                    continue;
                }
            }

            col++;
        }
        row++;
    }

    displaySymbolTable();
    fclose(fin);
    remove("temp.js"); // Clean up temporary file

    return 0;
}
