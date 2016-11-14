#include <stdio.h>
#include <stdlib.h>
int main(int argc, char* argv[])
{
	int toLength = 0;
	int fromLength = 0;
     char* fromString = argv[1];

	char* toString = argv[2];
  
     if (argc > 3)
     {
          fprintf(stderr, "Wrong number of arguments");
          exit(1);
     }

	for (int i = 0; toString[i] != '\0'; i++)
	{
		toLength++;
	}

	for (int i = 0; fromString[i] != '\0'; i++)
	{
	    fromLength++;
	} 

  // Checks for duplicate entries in to string
	for (int i = 0; i < fromLength; i++)
	{
		for (int j = i + 1; j < fromLength; j++)
		{
			if (fromString[i] == fromString[j])
			{
				fprintf(stderr, "From String has duplicate values\n");
				exit(1);
			}
		}
	}

    // Lengths of to and from string are not equal
  	if (toLength != fromLength)
  	{
    	fprintf(stderr, "Lengths of inputs are not the same\n");
    	exit(1);
  	}

  	int c = getchar();

    // Uses buffered I/O to grab characters and print them out after translating them
  	while (c != EOF)
  	{
  		char c_ascii = c;

  		int printed = 0;

  		for (int j = 0; j < fromLength; j++)
  		{
  			if (c_ascii == fromString[j])
  			{
  				putchar(toString[j]);
  				printed = 1;
  				break;
  			}
  		}

      // Checks to see if a character has already been printed in this iteration
  		if (printed)
  		{
  			c = getchar();
  			continue;
  		}
  		else
  		{
  			putchar(c_ascii);
  		}

  		c = getchar();
  	}
}