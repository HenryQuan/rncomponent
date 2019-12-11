///
// rncomponent.c
// Create stateful or stateless rncomponents for flutter
// 
// 21/09/2019
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

#define TS 1
#define JS 0

int exists(char*);
char* getFileName(char*, int);
char* getClassName(char*);
int createJS(char*, char*);
int createTS(char*, char*);
void usage();
void fatal(char*);

int main(int argc, char* argv[])
{
    int returnValue = 0;

    if (argc < 3) {
        // No enough arguments
        usage();
        returnValue = 1;
    } else {
        char* option = argv[1];
        char* input = argv[2];

        char* classname = getClassName(input);
        // Make sure the first alphabet is in UPPER CASE
        classname[0] = toupper(classname[0]);
        
        if (strcmp(option, "--ts") == 0) {
            char* filename = getFileName(input, TS);
            returnValue = createTS(filename, classname);
            free(filename);
        } else if (strcmp(option, "--js") == 0) {
            char* filename = getFileName(input, JS);
            returnValue = createJS(filename, classname);
            free(filename);
        } else {
            // Invalid option
            fatal("Invalid option!\n");
        }

        // Free up memory (other languages have gc...)
        free(classname);
    }

    return returnValue;
}

// Check if file exists
int exists(char* filename) {
    if (access(filename, F_OK) != -1) {
        printf("%s exists\nNothing was created\n", filename);
        return 1;
    } else {
        return 0;
    }
}

// Append .dart to input if necessary
char* getFileName(char* input, int mode) {
    if (mode == TS) {
        char* name = malloc(sizeof(char) * (strlen(input) + 4));
        if (name == NULL) fatal("Out of memory");

        strcpy(name, input);
        strcat(name, ".tsx");

        return name;
    } else {
        char* name = malloc(sizeof(char) * (strlen(input) + 3));
        if (name == NULL) fatal("Out of memory");

        strcpy(name, input);
        strcat(name, ".js");

        return name;
    }
}

// Usually the input is like `HelloWorld` but it is also possible to have `./Henry/HelloWorld` and we need to get `HelloWorld only`
char* getClassName(char* input) {
    int length = strlen(input);
    int start = -1;
    for (int i = length; i > 0; i--) {
        // Starting from the last index
        char curr = input[i - 1];
        if (curr == '/' || curr == '\\') {
            // It should start from the next character because now it is '/' or '\'
            start = i + 1;
            break;
        }
    }

    if (start == -1) {
        // This name is valid (so no '/' or '\')
        return input;
    } else {
        char* name = malloc(sizeof(char) * (length - start + 1));
        if (name == NULL) fatal("Out of memory"); 

        // Copy it into name
        int i = 0;
        for (int j = start; j <= length; j++, i++) {
            name[i] = input[j - 1];
        }

        // Add null
        name[i] = '\0';
        return name;
    }
}

// Create a stateful rncomponent
int createTS(char* filename, char* input) {
    printf("Creating TypeScript component\n");
    if (!exists(filename)) {
        FILE *rncomponent;
        rncomponent = fopen(filename, "w");
        fprintf(rncomponent, "import React, { Component } from 'react';\n");
        fprintf(rncomponent, "import { View, Text, StyleSheet } from 'react-native';\n");
        fprintf(rncomponent, "\n");
        fprintf(rncomponent, "export interface %sProps {\n", input);
        fprintf(rncomponent, "\n");
        fprintf(rncomponent, "}\n");
        fprintf(rncomponent, "\n");
        fprintf(rncomponent, "interface %sState {\n", input);
        fprintf(rncomponent, "\n");
        fprintf(rncomponent, "}\n");
        fprintf(rncomponent, "\n");
        fprintf(rncomponent, "/**\n");
        fprintf(rncomponent, " * %s Class\n", input);
        fprintf(rncomponent, " */\n");
        fprintf(rncomponent, "class %s extends Component<%sProps, %sState> {\n", input, input, input);
        fprintf(rncomponent, "  constructor(props: %sProps) {\n", input);
        fprintf(rncomponent, "    super(props);\n");
        fprintf(rncomponent, "  }\n");
        fprintf(rncomponent, "\n");
        fprintf(rncomponent, "  render() {\n");
        fprintf(rncomponent, "    const { container } = styles;\n");
        fprintf(rncomponent, "    return (\n");
        fprintf(rncomponent, "      <View style={container}>\n");
        fprintf(rncomponent, "        <Text>%s</Text>\n", input);
        fprintf(rncomponent, "      </View>\n");
        fprintf(rncomponent, "    );\n");
        fprintf(rncomponent, "  }\n");
        fprintf(rncomponent, "}\n");
        fprintf(rncomponent, "\n");
        fprintf(rncomponent, "const styles = StyleSheet.create({\n");
        fprintf(rncomponent, "  container: {\n");
        fprintf(rncomponent, "    flex: 1\n");
        fprintf(rncomponent, "  }\n");
        fprintf(rncomponent, "});\n");
        fprintf(rncomponent, "\n");
        fprintf(rncomponent, "export { %s };\n", input);
        fclose(rncomponent);
        printf("Success\n");
        return 0;
    }

    return 1;
}

// Create a stateless rncomponent
int createJS(char* filename, char* input) {
    printf("Creating JavaScript component\n");
    if (!exists(filename)) {
        FILE *rncomponent;
        rncomponent = fopen(filename, "w");
        fprintf(rncomponent, "import React, { Component } from 'react';\n");
        fprintf(rncomponent, "import { View, Text, StyleSheet } from 'react-native';\n");
        fprintf(rncomponent, "\n");
        fprintf(rncomponent, "/**\n");
        fprintf(rncomponent, " * %s Class\n", input);
        fprintf(rncomponent, " */\n");
        fprintf(rncomponent, "class %s extends Component {\n", input);
        fprintf(rncomponent, "  constructor(props) {\n");
        fprintf(rncomponent, "    super(props);\n");
        fprintf(rncomponent, "  }\n");
        fprintf(rncomponent, "\n");
        fprintf(rncomponent, "  render() {\n");
        fprintf(rncomponent, "    const { container } = styles;\n");
        fprintf(rncomponent, "    return (\n");
        fprintf(rncomponent, "      <View style={container}>\n");
        fprintf(rncomponent, "        <Text>%s</Text>\n", input);
        fprintf(rncomponent, "      </View>\n");
        fprintf(rncomponent, "    );\n");
        fprintf(rncomponent, "  }\n");
        fprintf(rncomponent, "}\n");
        fprintf(rncomponent, "\n");
        fprintf(rncomponent, "const styles = StyleSheet.create({\n");
        fprintf(rncomponent, "  container: {\n");
        fprintf(rncomponent, "    flex: 1\n");
        fprintf(rncomponent, "  }\n");
        fprintf(rncomponent, "});\n");
        fprintf(rncomponent, "\n");
        fprintf(rncomponent, "export { %s };\n", input);

        fclose(rncomponent);
        printf("Success\n");
        return 0;
    }

    return 1;
}

// Print how to use this program
void usage() {
    printf("usage: rncomponent [option] [name]\n--ts\tcreate a TypeScript rncomponent\n--js\tcreate a JavaScript rncomponent\nname\tanything but DO NOT include .js or .tsx\n\nhttps://github.com/HenryQuan/rncomponent\n");
}

// Fatal error
void fatal(char* msg) {
    printf("%s\n", msg);
    exit(EXIT_FAILURE);
}
