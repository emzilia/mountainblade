#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int check_input(int value, int randint);
int accept_input(int sum);

int check_input(int value, int rand)
{
	if (value < 0) {
		puts("Eat a dick");
		exit(1);
	} else if (value > 20) {
		puts("Real wise ass huh.");
		exit(1);
	} else if (value == rand) {
		puts("You did it!");
		return 0; 
	} else {
		return 1;
	}
}

int accept_input(int sum)
{
	scanf("%d", &sum);	
	return sum;
	
}

int main()
{
	int sum;
	int randint = rand() % 20 + 1;

	while (1)
	{
		puts("Enter an integer between 1 and 20:");
		printf("Hint, it's %d\n\n", randint);

		sum = accept_input(sum);

		if (check_input(sum, randint)) {
			printf("%i is not it\n", sum);
			sum = 0;
		} else {
			randint = rand() % 21 + 1;
		}

	}
}
