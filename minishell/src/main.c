#include "minishell.h"

int main() {
 	char *input = readline("Calculate: ");
	printf("Result: %s\n", input);
    return 0;
}

