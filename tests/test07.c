#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TOKENS 100
#define TOKEN_SIZE 1024

typedef struct s_parse_indexes
{
	int		tkn;
	int		chr;
	int		in_quotes;
	int		last_quote;
}				t_parse_indexes;

// Function to tokenize the input string as per the specified rules
// void tokenize(char *str, char tokens[MAX_TOKENS][TOKEN_SIZE]) {
//     int tokenIndex = 0; // Index to store tokens
//     int charIndex = 0; // Index to store individual characters of a token
//     int inQuotes = 0; // Flag to indicate whether the current character is within quotes
//     int lastQuoteIndex = -2; // Initialize with -2 to handle "" at the start

//     for (int i = 0; str[i] != '\0'; i++)
// 	{
//         if (str[i] == '"') {
//             inQuotes = !inQuotes; // Toggle the inQuotes flag
//             if (i - lastQuoteIndex == 1) { // Check if the quotes are adjacent
//                 // Add an empty token if "" is encountered
//                 tokens[tokenIndex][0] = '\0'; // Mark as an empty token
//                 tokenIndex++; // Move to the next token
//             }
//             lastQuoteIndex = i;
//             continue; // Do not add quote characters to the token
//         }

//         if (str[i] == ' ' && !inQuotes) {
//             if (charIndex != 0) { // Avoid adding empty tokens due to spaces
//                 tokens[tokenIndex][charIndex] = '\0'; // Null-terminate the current token
//                 tokenIndex++; // Move to the next token
//                 charIndex = 0; // Reset character index for the new token
//             }
//         } else {
//             tokens[tokenIndex][charIndex++] = str[i]; // Add character to the current token
//         }
//     }

//     if (charIndex != 0) { // Add the last token if it exists
//         tokens[tokenIndex][charIndex] = '\0';
//     }
// }

void tokenize(char *line, char tokens[MAX_TOKENS][TOKEN_SIZE])
{
	t_parse_indexes	index;
	int				i;

	index.tkn = 0;
	index.chr = 0;
	index.in_quotes = 0;
	index.last_quote = -2;
	i = 0;

	while (line[i] != '\0')
	{
		if (line[i] == '"')
		{
			index.in_quotes = !index.in_quotes;
			if (i - index.last_quote == 1)
			{
				tokens[index.tkn][0] = '\0';
				index.tkn++;
			}
			index.last_quote = i;
			i++;
			continue ;
		}
		if (line[i] == ' ' && !index.in_quotes)
		{
			if (index.chr != 0)
			{
				tokens[index.tkn][index.chr] = '\0';
				index.tkn++;
				index.chr = 0;
			}
		}
		else
			tokens[index.tkn][index.chr++] = line[i];
		i++;
	}
	if (index.chr != 0)
		tokens[index.tkn][index.chr] = '\0';
}

int main(int argc, char **argv)
{
    char input[] = "  \"abc def ghi\"     \"\"   a\"\" ";
    char tokens[MAX_TOKENS][TOKEN_SIZE];

    // Initialize tokens array
    memset(tokens, 0, sizeof(tokens));

    // Tokenize the input string
    // tokenize(argv[1], tokens);
	tokenize(input, tokens);

    // Print tokens
    for (int i = 0; i < 3; i++) {
        printf("Token %d: %s\n", i + 1, tokens[i]);
    }

    return 0;
}
