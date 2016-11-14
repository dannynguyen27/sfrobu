#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

typedef enum {false, true} bool;

static int numComparisons = 0;
int frobcmp(const void* a_r, const void* b_r)
{
    numComparisons++;
    const char** a_rtemp = (const char**) a_r;
    const char* a = *a_rtemp;

    const char** b_rtemp = (const char**) b_r;
    const char* b = *b_rtemp;

    int i = 0;
    int j = 0;
    
    while (true)
    {   
        // Both terms terminate at the same time.
        if (a[i] == ' ' && b[j] == ' ')
            break;

        // If a is a prefix of b, return -1 since shorter words are less than longer words
        if (a[i] == ' ')
        {
            return -1;
        }
    
        // If b is a prefix of a, return 1 since b is shorter than a
        if (b[j] == ' ')
        {
            return 1;
        }
        
        // If intial character is a newline character, don't use it for comparison
        if (a[0] == '\n')
        {
            i++;
            continue;
        }

        if (b[0] == '\n')
        {
            j++;
            continue;
        }

        // Compares defrobnicated byte
        unsigned char temp_a = a[i] ^ 42;
        unsigned char temp_b = b[j] ^ 42;
    
        // a goes before b
        if (temp_a < temp_b)
        {
            return -1;
        }

        // b goes before a
        else if (temp_a > temp_b)
        {
            return 1;
        }

        // check next character
        else
        {
            i++;
            j++;
        }
    }
    return 0;
}

int main(int argc, char* argv[]) {
    int numTerms = 0;
    char** terms;

    // Finds an address suitable for a double pointer
    terms = malloc(sizeof(char*));

    // Memory allocation failed
    if (terms == NULL)
    {
        fprintf(stderr, "Not enough memory allocation");
        exit(1);
    }

    // Too many file inputs. Send error message
    if (argc > 2)
    {
        fprintf(stderr, "Too many file inputs");
    }

    // Dealing with file input
    if (argc == 2)
    {
        int file = open(argv[1], O_RDONLY);
        if (file < 0)
        {
            fprintf(stderr, "Incorrect file path");
            exit(1);
        }
        else
        {
            struct stat buf;
            int buffer = fstat(file, &buf);
            char** list = malloc(sizeof(char*));

            if (list == NULL)
            {
                fprintf(stderr, "Not enough memory allocation");
                exit(1);
            }

            // TODO: Potential overflow?
            int sizeFile = buf.st_size;

            char* word = malloc(sizeFile);

            if (word == NULL)
            {
                fprintf(stderr, "Not enough memory allocation");
                exit(1);
            }

            int numLetters = 0;

            if (buffer == 0)
            {
               // printf("%lld bytes\n", buf.st_size);

                while (1 < 2)
                {
                    // If necessary, allocate additional memory
                    
                    if (numLetters >= sizeFile)
                    {
                        if (sizeFile == 0)
                        {
                            sizeFile = 1;
                            word = realloc(word, sizeFile);
                        }
                        else
                        {
                            sizeFile = sizeFile * 2;
                            word = realloc(word, sizeFile);    
                        }
                        

                        if (word == NULL)
                        {
                            fprintf(stderr, "Not enough memory allocation");
                            exit(1);
                        }
                    }

                    char letter[1];    


                    int temp = read(file, letter, 1);
                    
                    // Read was unsuccessful
                    if (temp == 0)
                    {
                        // Must terminate on a space character
                        if (word[numLetters - 1] != ' ')
                        {
                        //    printf("\nHello %c\n", word[numLetters - 1]);
                            if (numLetters >= sizeFile)
                            {
                                word = realloc(word, sizeFile + 1);
                            }

                            word[numLetters] = ' ';
                            numLetters++;
                        }

                        break;
                    }
                        
                    //printf("%c\n", letter[0]);

                    word[numLetters] = letter[0];

                    numLetters++;   
                    
                }
            }
            else
            {
                fprintf(stderr, "Could not get statistics from file");
            }

            // If input file has characters within, need to save the address of the first character
            if (sizeFile != 0)
            {
                char* temp = &word[0];
                list[0] = temp;
                numTerms++;
                list = realloc(list, sizeof(char*) * (numTerms + 1));

                if (list == NULL)
                {
                    fprintf(stderr, "Not enough memory allocation");
                    exit(1);
                }
            }

            // Use numLetters - 1 since the last letter should always be a ' '
            int i = 0;
            for (; i < numLetters - 1; i++)
            {
                // Check to see if value is a ' ' delimiter
                if (word[i] == ' ')
                {
                    char* temp = &word[i + 1];
                    list[numTerms] = temp;
                    numTerms++;

                    // Make enough room to insert another word if necessary
                    list = realloc(list, sizeof(char*) * (numTerms + 1));

                    if (list == NULL)
                    {
                        fprintf(stderr, "Not enough memory allocation");
                        exit(1);
                    }
                }
            }

            // Resize array to not hold an additional 8 bytes for a nonexistent last entry
            list = realloc(list, sizeof(char*) * numTerms);
            if (list == NULL)
            {
                fprintf(stderr, "Not enough memory allocation");
                exit(1);
            }

            qsort(list, numTerms, sizeof(char*), frobcmp);
            
            i = 0;
            for (; i < numTerms; i++)
            {
                int j = 0;

                while (1 < 2)
                {
                    write(1, &list[i][j], 1);    
                    if (list[i][j] == ' ')
                        break;
                    j++;
                }
            }

            free(word);
            free(list);
            fprintf(stderr, "Comparisons: %d\n", numComparisons);

        }
    }

    // Dealing with standard input
    else
    {
        // Repeat until end of file is reached
        while (true)
        {
            // Starts with a string of size 40
            int size = 40;
            char* temp = malloc(sizeof(char) * size);

            if (temp == NULL)
            {
                fprintf(stderr, "Not enough memory allocation");
                exit(1);
            }

            // Keeps track of the number of characters 
            int numLetters = 0;

            char letter[1];
            int c = read(0, letter, 1);

            // No bytes left to read
            if (c == 0)
            {
                break;
            }
                    
            while (c > 0)
            {
                // If need be, allocate additional memory
                if (numLetters >= size)
                {
                    size *= 2;
                    temp = realloc(temp, size);

                    // Not enough memory available
                    if (temp == NULL)
                    {
                        fprintf(stderr, "Not enough memory allocation");
                        exit(1);
                    }
                }
                
                // Checks for space delimiter
                if (letter[0] == ' ')
                {
                    // Appends final space character
                    temp[numLetters] = ' ';
                    break;
                }
                    
                // Adds character to array
                temp[numLetters] = letter[0];
                
                numLetters++;
                c = read(0, letter, 1);
            }

            // Reached end of file
            if (c == 0)
            {
                // If the last word does not have a final space delimiter, add it
                if (temp[numLetters-1] != ' ')
                {
                    temp[numLetters] = ' ';
                }
            }
            
            // Add string to array of Strings
            terms[numTerms] = temp;
            numTerms++;        
            
            // Allocate additional mmeory to find one more word
            terms = realloc(terms, (numTerms + 1) * sizeof(char*));

            if (terms == NULL)
            {
                fprintf(stderr, "Not enough memory allocation");
                exit(1);
            }
        } 
        
        // Allocate memory back to true size
        if (numTerms != 0)
            terms = realloc(terms, (numTerms) * sizeof(char*));  

        if (terms == NULL)
        {
            fprintf(stderr, "Not enough memory allocation");
            exit(1);
        }

        int tempCounter = 0;

        qsort(terms, numTerms, sizeof(char*), frobcmp);

        int i = 0;
        for (; i < numTerms; i++)
        {
            int j = 0;
            while (true)
            {
                // If first time has a newline character in front, don't print it out
                if ((i == 0) && (j == 0) && (terms[i][j] == '\n'))
                {
                    j++;
                    continue;
                }

                char letterToPrint[1];
                letterToPrint[0] = terms[i][j];
                if (letterToPrint[0] != ' ')
                {
                    write(1, letterToPrint, 1);
                    j++;                
                }
                else
                {
                    write(1, letterToPrint, 1);
                    break;
                }
            }
        }

        i = 0;
        for (; i < numTerms; i++)
        {
            char* tempCharPointer = (char*) terms[i];

            // Checks to see if the pointer is null
            if (tempCharPointer)
            {
                free(tempCharPointer);
                terms[i] = NULL;
            }
        }

        if (terms)
            free(terms);

        fprintf(stderr, "\nComparisons: %d\n", numComparisons);
        exit(0);
    }
}