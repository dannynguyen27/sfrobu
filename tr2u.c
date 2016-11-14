#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
	int toLength = 0;
	int fromLength = 0;

	char* fromString = argv[1];
	char* toString = argv[2];
  	

	for (int i = 0; toString[i] != '\0'; i++)
	{
		toLength++;
	}

	for (int i = 0; fromString[i] != '\0'; i++)
	{
	    fromLength++;
	} 

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

  	if (toLength != fromLength)
  	{
    	fprintf(stderr, "Lengths of inputs are not the same\n");
    	exit(1);
  	}

  	while (1 < 2)
  	{
  		char letter[1];

  		int temp = read(0, letter, 1);

  		if (temp == 0)
  			break;

  		int hasWritten = 0;

  		for (int i = 0; i < fromLength; i++)
  		{
  			if (fromString[i] == letter[0])
  			{
  				char toPrint[1];

  				toPrint[0] = toString[i];

  				write(1, toPrint, 1);
  				hasWritten = 1;
  				break;	
  			}
  		}

  		if (!hasWritten)
  		{
  			write(1, letter, 1);
  		}
  	}

  	
}